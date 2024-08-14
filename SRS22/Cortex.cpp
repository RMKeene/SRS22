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

	void Cortex::ComputeNextStateSingleNeuron(const size_t& i)
	{
		// How much are you matching the inputs?
		float sum = 0.0f;
		for (int k = 0; k < NEURON_INPUTS; k++) {
			sum += neuronDeltaFactor(i, k, NEURON_HISTORY_MINUS_ONE);
		}

		float excitation = sum / NEURON_MATCH_SOFTNESS;
		sumToNext(i, excitation);
		clampNeuronNext(i);

		// So stimulate the target.
		float f1 = get(i);
		float f2 = get(neuronTarget[i]);
		float f3 = targetNeuronDeltaFactor(i);
		float f4 = NEURON_TARGET_STIMULATION_FACTOR;
		float f5 = f1 * f3 * f4;
		float f6 = f2 + f5;

		float tndf = targetNeuronDeltaFactor(i);
		float g = get(i);
		float val = get(i) * targetNeuronDeltaFactor(i) * NEURON_TARGET_STIMULATION_FACTOR;
		sumToNext(neuronTarget[i], get(i) * targetNeuronDeltaFactor(i) * NEURON_TARGET_STIMULATION_FACTOR);
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