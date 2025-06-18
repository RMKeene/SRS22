#include "SRS22pch.h"
#include "Cortex.h"
#include "SRSMath.h"
#include <ppl.h>

namespace SRS22 {

	void Cortex::ResetStats() {
		stats.reset();
	}

	void Cortex::PostProcessStats() {
		stats.averageNeuronCharge = (float)(stats.sumOfC / stats.countOfNeuronsProcessed);
		stats.averageConfidence = (float)(stats.sumOfConfidence / stats.countOfConfidence);
	}

	void Cortex::ComputeNextState(boolean doParallel) {
#if DONANCHECKS
		doNanScan();
#endif
		PreComputeNextStateSingleNeurons();
		if (doParallel) {
			Concurrency::combinable<CortexThreadStats> threadStats;
			Concurrency::parallel_for(0, TOTAL_NEURONS, [&](size_t i) {
				ComputeNextStateSingleNeuron(i, threadStats.local());
				});
			threadStats.combine_each([&](CortexThreadStats threadStats) {
				stats.SumInNoLock(threadStats);
				});
		}
		else {
			CortexThreadStats threadStats;
			for (int i = 0; i < TOTAL_NEURONS; i++) {
				ComputeNextStateSingleNeuron(i, threadStats);
			}
			stats.SumInNoLock(threadStats);
		}
		PostComputeNextStateSingleNeurons();
#if DONANCHECKS
		doNanScan();
#endif
	}

	void Cortex::ComputeNextStateSingleNeuron(const size_t i, CortexThreadStats& threadStats)
	{
		if (neurons.state[i] == NeuronType::IS_INPUT) {
			// Input neurons are not predicted, they are hard set to a value by hardware IO or 
			// ConceptTransform hard coded algorithms. 
			// Their NeuronLinks are not used. So no learning to do.
			return;
		}
		float C = neurons.getCurrent(i);

		UpdateProcessedStatCounts(threadStats, C);

		// Cache settings values used multiple times
		const float linkActivityDecayRate = settings.linkActivityDecayRate();
		const float linkStimulusToActivityFactor = settings.linkStimulusToActivityFactor();
		const float throttleFactor = NEURON_UPSTREAM_LINKS_INVERSE * settings.connectionThrottle();

		// We are adding stimulus from upstream neurons.
		float stimulusSum = C;
		for (int k = 0; k < NEURON_UPSTREAM_LINKS; ++k) {
			NeuronLink& L = neurons.link[i][k];

			if (L.otherIdx == NEURON_LINK_UNCONNECTED)
				continue;

#ifndef NDEBUG
			if (L.otherIdx < 0 || L.otherIdx >= TOTAL_NEURONS)
				throw std::out_of_range(std::format("L.otherIdx out of range: {0}", L.otherIdx));
#endif

			if (C > 0.03f)
				++threadStats.countOfNeuronsFired;

			// Stimulus. Charge of a Neuron can range between 0.0f and 1.0f
			// Weight can range between -1.0 and 1.0. So no need to clamp the result.
			const float stimulus = get(L.otherIdx) * L.weight * throttleFactor;

			// Add link stimulus. Gets clamped later,
			stimulusSum += stimulus;
			// Add into activity for short term general activity level.
			L.activity = std::clamp(L.activity * linkActivityDecayRate + stimulus * linkStimulusToActivityFactor, 0.0f, 1.0f);
		}

		// Now clamp the resulting total stimulus.
		neurons.setNext(i, std::clamp(stimulusSum * settings.chargeDepletionRate(), 0.0f, 1.0f));

#ifndef NDEBUG
		checkNanByIdx(i);
#endif
	}

	/// <summary>
	/// Increments the global tick indicies for Neuron. Next becomes current state, current state becomes previous state.
	/// </summary>
	void Cortex::LatchNewState(boolean doParallel) {
		// Tick the indicies for (static indicies) all neurons.
		TickIndicies();
	}

	void Cortex::LearningPhase(boolean doParallel) {

		const float learnFactor = brain.learningRate;
		if (doParallel) {
			Concurrency::combinable<CortexThreadStats> threadStats;

			Concurrency::parallel_for(0, TOTAL_NEURONS, [&](size_t i) {
				DoLearningSingleNeuron(i, threadStats.local());
				});

			threadStats.combine_each([&](CortexThreadStats threadStats) {
				stats.SumInNoLock(threadStats);
				});
		}
		else {
			CortexThreadStats threadStats;
			for (int i = 0; i < TOTAL_NEURONS; i++) {
				DoLearningSingleNeuron(i, threadStats);
			}
			stats.SumInNoLock(threadStats);
		}
	}

	void Cortex::DoLearningSingleNeuron(const size_t i, CortexThreadStats& threadStats) {
		// Input neurons are not predicted, they are hard set to a value by hardware IO.  
		// Their NeuronLinks are not used. So there is no learning to do.
		if (neurons.state[i] == NeuronType::IS_INPUT)
			return;

		const float C = neurons.getCurrent(i);
		const float CDelta = C - 0.5f;

		// Deplete some metabolism
		if (neurons.state[i] == NeuronType::REGULAR) {
			neurons.energyCeiling[i] = std::clamp(neurons.energyCeiling[i]
				// Deplete energy
				- C * settings.energyDepletionOnFire()
				// Recover energy
				+ settings.energyRechargeRate(), 0.0f, settings.maxEnergy());
		}

		// Neuroplasticity: Learn to predict the future state of this neuron.
		// Enhanced learning due to endorphins, "goodness" Range is +-1 
		// So 1.0 goodness here is no enhancement nor inhibition of learning rate.
		const float learningRateDueToGoodness = 1.0f + brain.overallGoodness * settings.learningRateGoodnessFactor();

		for (int k = 0; k < NEURON_UPSTREAM_LINKS; k++) {
			NeuronLink& L = neurons.link[i][k];
			threadStats.sumOfConfidence += L.confidence;
			threadStats.countOfConfidence++;

			L.age++;
			const int ageLog = logBase2_U64(L.age) + 1;
			const float ageLogInverse = 1.0f / (float)ageLog;

			if (ShouldReroute(i, L, ageLog)) {
				RerouteLink(L, i, threadStats);
			}
			else {
				DoLinkLearning(ageLogInverse, L, ageLog, CDelta, learningRateDueToGoodness);
			}
		}
	}

	void Cortex::DoLinkLearning(const float ageLogInverse, SRS22::NeuronLink& L, const int ageLog, const float CDelta, const float learningRateDueToGoodness)
	{
		// Newer links learn much faster
		const float learningRateDueToNewnessOfL = 1.0f + ageLogInverse * settings.learningRateAgeFactor();
		// Active link learn a little faster.
		const float learningRateDueToActivityOfL = L.activity * settings.linkActivityLearningFactor();
		// How fast to forget. 1 is no forgetting, 0.5 is ultra rapid forgetting. Values lik 0.99999 are good.
		const float forgetFactor = settings.learningRateForgetFactor() * (1.0f - (1.0 / ((double)ageLog + settings.learningRateForgetLogOffset())));

		// We are trying to train to predict the future. So use other's charge N ticks ago.
		const float otherCPast = neurons.getPast(L.otherIdx, NEURON_HISTORY - settings.learningRateTicksOffset());
		const float otherPastInfluence = CDelta * otherCPast;
		L.weight = std::clamp(L.weight + -otherPastInfluence *
			settings.overallLearnRate() *
			learningRateDueToNewnessOfL *
			learningRateDueToActivityOfL *
			learningRateDueToGoodness, -1.0f, 1.0f) * forgetFactor;

		// Confidence is how well weight and otherCPast was a correct influence.
		L.confidence = L.confidence +
			otherPastInfluence *
			L.weight *
			settings.confidenceForgetFactor() * (1.0f - (1.0 / ((double)ageLog + settings.confidenceForgetLogOffset())));
	}

	void Cortex::RerouteLink(SRS22::NeuronLink& L, const int neuronIdx, CortexThreadStats& threadStats)
	{
		threadStats.countOfReRoutes++;
		// Reroute the link to a random neuron that is not this neuron 
		// nor any of its links including L.otherIdx.
		int newOtherIdx = GetRandomLinearOffsetExcept(neuronIdx);
		while (!NotIn(newOtherIdx, neurons.link[neuronIdx]) || newOtherIdx == L.otherIdx) {
			newOtherIdx = GetRandomLinearOffsetExcept(neuronIdx);
		}
		L.otherIdx = newOtherIdx;
		L.confidence = 0.01f; // Reset confidence to a low value.
		// Reset weight to a random value, either -1 or 1.
		if (fastRandFloat() < 0.5f)
			L.weight = -1.0f; 
		else 
			L.weight = 1.0f; 

		L.age = 0; // Reset age.
		L.activity = 0.5f; // Reset activity.
	}

	bool Cortex::ShouldReroute(const int neuronIdx, const SRS22::NeuronLink& L, const int ageLog) {
		// TODO - Implement progressive growth where we start off with little of the free cortex available
		// and then grow slowly.
	
		// Reroute Probability is small, like 0.01. Overall goodness is -1 to +1
		if (fastRandFloat() > settings.rerouteProbability() * brain.overallGoodness) {
			return false;
		}
		
		// Reroute if the link is not connected or if the Weight is near zero.
		// As the link gets older the reroute probability decreases.
		if (L.otherIdx == NEURON_LINK_UNCONNECTED || 
			// What other settings are needed here.
			L.confidence * std::abs(L.weight) * (float)ageLog < settings.rerouteThreshold()) {
			return true;
		}
		return false;
	}

	void Cortex::PostCreate() {

	}

}
