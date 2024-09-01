#include "SRS22pch.h"
#include "Cortex.h"
#include "SRSMath.h"
#include <ppl.h>

namespace SRS22 {

	void Cortex::ComputeNextState(boolean doParallel) {
#if DONANCHECKS
		doNanScan();
#endif

		if (doParallel) {
			Concurrency::parallel_for(0, TOTAL_NEURONS, [&](size_t i) {
				ComputeNextStateSingleNeuron(i);
				});
		}
		else {
			for (int i = 0; i < TOTAL_NEURONS; i++) {
				ComputeNextStateSingleNeuron(i);
			}
		}
#if DONANCHECKS
		doNanScan();
#endif


		if (brain.ShouldLearn())
			growthSum += growthRate * brain.overallGoodnessRateOfChange;

#if DONANCHECKS
		doNanScan();
#endif
	}

	void Cortex::ComputeNextStateSingleNeuron(const size_t i)
	{
		for (int k = 0; k < NEURON_INPUTS; k++) {
			applyOtherStimulus(i, k);
		}
	}

	/// <summary>
	/// Increments the tick indicies.
	/// </summary>
	void Cortex::LatchNewState(boolean doParallel) {
		tickIndicies();
	}

	void Cortex::DecayNextTowardZero(boolean doParallel) {
		if (doParallel) {
			Concurrency::parallel_for(0, TOTAL_NEURONS, [&](size_t i) {
				multiplyToNext(i, neuronChargeDecayFactor);
				});
		}
		else {
			for (int i = 0; i < TOTAL_NEURONS; i++) {
				multiplyToNext(i, neuronChargeDecayFactor);
			}
		}
	}

	void Cortex::LearningPhase(boolean doParallel) {
		float learnFactor = brain.learningRate;
		if (doParallel) {
			Concurrency::parallel_for(0, TOTAL_NEURONS, [&](size_t i) {
				float C = get(i);
				for (int k = 0; k < NEURON_INPUTS; k++) {
					float delta = C - get(link[i][k].otherIdx);
					link[i][k].otherCharge += growthSum;
				}
				});
		}
		else {
			for (int i = 0; i < TOTAL_NEURONS; i++) {
				float C = get(i);
				for (int k = 0; k < NEURON_INPUTS; k++) {
					float delta = C - get(link[i][k].otherIdx);
					link[i][k].otherCharge += growthSum;
				}
			}
		}
	}

	void Cortex::PostCreate() {

	}

	bool Cortex::ShouldAddNewPattern() {
		return brain.TheWorldIsGettingBetter();
	}

}