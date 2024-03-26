#include "SRS22pch.h"
#include "Cortex.h"
#include "FastRand.h"
#include "Brain.h"
#include "SRS22LogTaker.h"
#include <ppl.h>

namespace SRS22 {

	void Cortex::ComputeNextState(boolean doParallel) {
		if (doParallel) {
			Concurrency::parallel_for(0, TOTAL_NEURONS, [&](size_t i) {
				float sum = 0.0f;
				for (int k = 0; k < NEURON_INPUTS; k++) {
					sum += get(neuronInputIdxs[i][k]) * neuronInputCharge[i][k];
				}
				sumToNext(i, clamp(sum, 0.0f, 1.0f));
				});
		}
		else {
			for (int i = 0; i < TOTAL_NEURONS; i++) {
				float sum = 0.0f;
				for (int k = 0; k < NEURON_INPUTS; k++) {
					sum += get(neuronInputIdxs[i][k]) * neuronInputCharge[i][k];
				}
				sumToNext(i, clamp(sum, 0.0f, 1.0f));
			}
		}

		if (brain.ShouldLearn())
			growthSum += growthRate * brain.overallGoodnessRateOfChange;
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
				multiplyNextToNext(i, neuronChargeDecayFactor);
				});
		}
		else {
			for (int i = 0; i < TOTAL_NEURONS; i++) {
				multiplyNextToNext(i, neuronChargeDecayFactor);
			}
		}
	}

	void Cortex::LearningPhase(boolean doParallel) {
		float learnFactor = brain.learningRate;
		if (brain.ShouldLearn()) {
			if (doParallel) {
				Concurrency::parallel_for(0, TOTAL_NEURONS, [&](size_t i) {
					float C = get(i);
					for (int k = 0; k < NEURON_INPUTS; k++) {
						float delta = C - get(neuronInputIdxs[i][k]);
						neuronInputCharge[i][k] += growthSum;
					}
					});
			}
			else {
				for (int i = 0; i < TOTAL_NEURONS; i++) {
					for (int k = 0; k < NEURON_INPUTS; k++) {
						neuronInputCharge[i][k] += growthSum;
					}
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