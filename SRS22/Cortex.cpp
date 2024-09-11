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
			Concurrency::parallel_for(0, TOTAL_NEURONS, [&](size_t i) {
				CortexThreadStats threadStats;
				ComputeNextStateSingleNeuron(i, threadStats);
				stats.SumIn(threadStats);
				});
		}
		else {
			CortexThreadStats threadStats;
			for (int i = 0; i < TOTAL_NEURONS; i++) {
				ComputeNextStateSingleNeuron(i, threadStats);
			}
			stats.SumIn(threadStats);
		}
#if DONANCHECKS
		doNanScan();
#endif
	}

	void Cortex::ComputeNextStateSingleNeuron(const size_t i, CortexThreadStats& threadStats)
	{
		threadStats.countOfNeuronsProcessed++;
		const float C = get(i);
		threadStats.sumOfC += C;
		if (C >= 0.99999f)
			threadStats.countOfOnes++;
		else if (C <= 0.00001f)
			threadStats.countOfZeros++;

		for (int k = 0; k < NEURON_INPUTS; k++) {
			applyOtherStimulus(i, k, threadStats);
		}
	}

	/// <summary>
	/// Increments the tick indicies.
	/// </summary>
	void Cortex::LatchNewState(boolean doParallel) {
		tickIndicies();
	}

	void Cortex::LearningPhase(boolean doParallel) {
		float learnFactor = brain.learningRate;
		if (doParallel) {
			Concurrency::parallel_for(0, TOTAL_NEURONS, [&](size_t i) {
				CortexThreadStats threadStats;
				DoLearningSingleNeuron(i, threadStats);
				stats.SumIn(threadStats);
				});
		}
		else {
			CortexThreadStats threadStats;
			for (int i = 0; i < TOTAL_NEURONS; i++) {
				DoLearningSingleNeuron(i, threadStats);
			}
			stats.SumIn(threadStats);
		}
	}

	void Cortex::DoLearningSingleNeuron(const size_t i, CortexThreadStats& threadStats) {
		const float C = get(i);

		for (int k = 0; k < NEURON_INPUTS; k++) {
			NeuronLink& L = link[i][k];
			threadStats.sumOfConfidence += L.confidence;
			threadStats.countOfConfidence++;
			if (L.confidence <= rerouteThreshold && fastRandFloat() < rerouteProbability) {
				threadStats.countOfReRoutes++;
				L.confidence = rerouteConfidenceSet;
				L.otherIdx = GetRandomLinearOffsetExcept(i);
				L.otherCharge = fastRandFloat();
				L.selfCharge = fastRandFloat();
			} else {
				float selfDelta = L.selfCharge - C;
				float absSelfDelta = fabsf(selfDelta);
				float learnDelta = selfDelta * lowLearnRate;

				float otherC = get(L.otherIdx);
				float otherDelta = L.otherCharge - otherC;
				float absOtherDelta = fabsf(otherDelta);
				float learnOtherDelta = otherDelta * lowLearnRate;

				putNext(i, C + learnDelta);
				putNext(L.otherIdx, otherC + learnOtherDelta);

				// The closer the confidence is to 1.0 the slower we adjust.
				// The closer the C's are to the expected charge, the less we adjust.
				float confidenceDelta = (selfDelta + otherDelta) * (1.0f - L.confidence);
				L.confidence += confidenceDelta * confidenceAdjustmentRate;
				if(L.confidence < minimumConfidence) {
					L.confidence = minimumConfidence;
				} else if(L.confidence > maximumConfidence) {
					L.confidence = maximumConfidence;
				}
			}
		}
	}

	void Cortex::PostCreate() {

	}

}