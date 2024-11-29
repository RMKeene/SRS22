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
		const float C = neurons.getCurrent(i);

		RechargeMetabolismIf(i);
		UpdateProcessedStatCounts(threadStats, C);

		for (int k = 0; k < NEURON_OUTPUTS; k++) {
			NeuronLink& L = neurons.link[i][k];
			L.wasSelfMatch = false;
			if (L.otherIdx == NEURON_LINK_UNCONNECTED)
				continue;
#ifdef _DEBUG
			if (L.otherIdx < NEURON_LINK_UNCONNECTED || L.otherIdx >= TOTAL_NEURONS)
				throw std::out_of_range(std::format("L.otherIdx out of range: {0}", L.otherIdx));
#endif

			const float selfDeltaC = SelfMatchStrength(L, C);
			if (selfDeltaC > 0.0f) {

				FireConnection(i, k, threadStats, selfDeltaC);
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
		const float C = neurons.getCurrent(i);

		for (int k = 0; k < NEURON_OUTPUTS; k++) {
			NeuronLink& L = neurons.link[i][k];
			threadStats.sumOfConfidence += L.confidence;
			threadStats.countOfConfidence++;
			if (L.confidence <= settings.rerouteThreshold && fastRandFloat() < settings.rerouteProbability) {
				threadStats.countOfReRoutes++;
				L.confidence = settings.rerouteConfidenceSet;
				L.otherIdx = GetRandomLinearOffsetExcept(i);
				L.otherCharge = get(L.otherIdx);
				L.selfCharge = C;
			}
			else if (L.wasSelfMatch && !L.wasSelfMatch) {
				//Lose confidence in this connection.
				L.confidence *= settings.confidenceAdjustmentDownRate;
			}
			else {
				float selfDelta = L.selfCharge - C;
				float absSelfDelta = fabsf(selfDelta);
				float learnDelta = selfDelta * settings.lowLearnRate;

				float otherC = get(L.otherIdx);
				float otherDelta = L.otherCharge - otherC;
				float absOtherDelta = fabsf(otherDelta);
				float learnOtherDelta = otherDelta * settings.lowLearnRate;

				putNext(i, C + learnDelta);
				putNext(L.otherIdx, otherC + learnOtherDelta);

				// The closer the confidence is to 1.0 the slower we adjust.
				// The closer the C's are to the expected charge, the less we adjust.
				float confidenceDelta = (absSelfDelta + absOtherDelta) * (1.0f - L.confidence);
				L.confidence += confidenceDelta * settings.confidenceAdjustmentUpRate;
				if (L.confidence < settings.minimumConfidence) {
					L.confidence = settings.minimumConfidence;
				}
				else if (L.confidence > settings.maximumConfidence) {
					L.confidence = settings.maximumConfidence;
				}
			}
		}
	}

	void Cortex::PostCreate() {

	}

}