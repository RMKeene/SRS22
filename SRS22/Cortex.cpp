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
#if DONANCHECKS
		doNanScan();
#endif
	}

	void Cortex::ComputeNextStateSingleNeuron(const size_t i, CortexThreadStats& threadStats)
	{
		if (neurons.enabled[i] == NeuronState::IS_INPUT)
			return;
		const float C = neurons.getCurrent(i);

		RechargeMetabolismIf(i);
		UpdateProcessedStatCounts(threadStats, C);

		for (int k = 0; k < NEURON_UPSTREAM_LINKS; k++) {
			NeuronLink& L = neurons.link[i][k];
			L.wasMatch = false;
			// Input neurons are not predicted, they are hard set to a value by hardware IO.  Their NeuronLinks are not used.
			if (L.otherIdx == NEURON_LINK_UNCONNECTED)
				continue;
#ifdef _DEBUG
			if (L.otherIdx < NEURON_LINK_UNCONNECTED || L.otherIdx >= TOTAL_NEURONS)
				throw std::out_of_range(std::format("L.otherIdx out of range: {0}", L.otherIdx));
#endif

			// Check whether the upstream neurons match the link's otherCharge closely enough.  (See linkMatchSharpness)
			const float otherDeltaC = LinkOtherMatchStrength(L);
			if (otherDeltaC > 0.0f) {
				// By 'fire' we mean vote for this neurons state to change to L.selfCharge.
				// Vote weight is the confidence of the link times the closeness of the match.
				// The weighted average of all the votes is the new next state, but softened by the connectionThrottle.
				FireConnection(i, k, threadStats, otherDeltaC);
			}
		}
	}

	/// <summary>
	/// Increments the global tick indicies for Neuron.
	/// </summary>
	void Cortex::LatchNewState(boolean doParallel) {
		// Tick the indicies for (static indicies) all neurons.
		TickIndicies();
	}

	void Cortex::LearningPhase(boolean doParallel) {
		float learnFactor = brain.learningRate;
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
		if (neurons.enabled[i] == NeuronState::IS_INPUT)
			return;

		const float C = neurons.getCurrent(i);

		// Neuroplasticity: Learn to predict the future state of this neuron.
		for (int k = 0; k < NEURON_UPSTREAM_LINKS; k++) {
			NeuronLink& L = neurons.link[i][k];
			threadStats.sumOfConfidence += L.confidence;
			threadStats.countOfConfidence++;

			if (L.confidence <= settings.rerouteThreshold && fastRandFloat() < settings.rerouteProbability) { // Useless connection, reroute.
				threadStats.countOfReRoutes++;
				L.confidence = settings.rerouteConfidenceSet;
				L.otherIdx = GetRandomLinearOffsetExcept(i);
				L.otherCharge = get(L.otherIdx);
				L.selfCharge = C;
			}
			else if (!L.wasMatch) { // Forget very slightly
				//Lose confidence in this connection.
				L.confidence *= settings.confidenceAdjustmentDownRate;
			}
			else { // Learn - This link had a match this tick.

				// We are skewed in time by one or more ticks singe we are trying to predict future states 
				// and get ahead of reality as a survivfal trait. React in advanhce of threats or desired outcomes.

				// We adjust L.selfCharge toward this neurons current charge.
				L.selfCharge += (L.selfCharge - C) * settings.lowLearnRate;

				// We adjust L.otherCharge toward the upstream neuron's past charge.
				L.otherCharge += (L.otherCharge - getPast(L.otherIdx, NEURON_HISTORY_DEFAULT_PAST_OFFSET)) * settings.lowLearnRate;

				L.confidence += (1.0f - L.confidence) * settings.confidenceAdjustmentUpRate;
			}
		}
	}

	void Cortex::PostCreate() {

	}

}