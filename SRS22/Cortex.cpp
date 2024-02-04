#include "SRS22pch.h"
#include "Cortex.h"
#include "FastRand.h"
#include "Brain.h"
#include "SRS22LogTaker.h"

namespace SRS22 {

	void Cortex::ComputeNextState() {
		for(int i=0; i< TOTAL_NEURONS; i++) {
			// TODO Neuron next state
		}

		if (brain.ShouldLearn())
			growthSum += growthRate * brain.overallGoodnessRateOfChange;
	}

	void Cortex::LatchNewState() {
		memcpy_s(neuronCharges, sizeof(neuronCharges), neuronChargesNext, sizeof(neuronChargesNext));
	}

	void Cortex::LearningPhase() {
	}

	void Cortex::PostCreate() {
		
	}

	bool Cortex::ShouldAddNewPattern() {
		return brain.TheWorldIsGettingBetter();
	}

}