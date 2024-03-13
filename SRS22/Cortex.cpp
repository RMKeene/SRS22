#include "SRS22pch.h"
#include "Cortex.h"
#include "FastRand.h"
#include "Brain.h"
#include "SRS22LogTaker.h"
#include <ppl.h>

namespace SRS22 {

	void Cortex::ComputeNextState() {
		//for(int i=0; i< TOTAL_NEURONS; i++) {
			// TODO Neuron next state
		//}

		if (brain.ShouldLearn())
			growthSum += growthRate * brain.overallGoodnessRateOfChange;
	}

	/// <summary>
	/// Copys the neuron charges next state to current state.
	/// </summary>
	void Cortex::LatchNewState() {
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

	void Cortex::LearningPhase() {
	}

	void Cortex::PostCreate() {

	}

	bool Cortex::ShouldAddNewPattern() {
		return brain.TheWorldIsGettingBetter();
	}

}