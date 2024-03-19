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
					sum += neuronCharges[neuronInputs[i][k]] * neuronInputWeights[i][k];
				}
				neuronChargesNext[i] += clamp(sum, 0.0f, 1.0f);
				});
		}
		else {
			for (int i = 0; i < TOTAL_NEURONS; i++) {
				float sum = 0.0f;
				for (int k = 0; k < NEURON_INPUTS; k++) {
					sum += neuronCharges[neuronInputs[i][k]] * neuronInputWeights[i][k];
				}
				neuronChargesNext[i] += clamp(sum, 0.0f, 1.0f);
			}
		}

		if (brain.ShouldLearn())
			growthSum += growthRate * brain.overallGoodnessRateOfChange;
	}

	/// <summary>
	/// Copys the neuron charges next state to current state.
	/// </summary>
	void Cortex::LatchNewState(boolean doParallel) {
		memcpy_s(neuronCharges, sizeof(neuronCharges), neuronChargesNext, sizeof(neuronChargesNext));

	}

	void Cortex::DecayNextTowardZero(boolean doParallel) {
		if (doParallel) {
			Concurrency::parallel_for(0, TOTAL_NEURONS, [&](size_t i) {
				neuronChargesNext[i] *= neuronChargeDecayFactor;
				});
		}
		else {
			for (int i = 0; i < TOTAL_NEURONS; i++) {
				neuronChargesNext[i] *= neuronChargeDecayFactor;
			}
		}
	}

	void Cortex::LearningPhase(boolean doParallel) {
		if (brain.ShouldLearn()) {
			if (doParallel) {
				Concurrency::parallel_for(0, TOTAL_NEURONS, [&](size_t i) {
					for (int k = 0; k < NEURON_INPUTS; k++) {
						neuronInputWeights[i][k] += growthSum;
					}
					});
			}
			else {
				for (int i = 0; i < TOTAL_NEURONS; i++) {
					for (int k = 0; k < NEURON_INPUTS; k++) {
						neuronInputWeights[i][k] += growthSum;
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