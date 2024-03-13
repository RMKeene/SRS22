#pragma once

#include "FastRand.h"
#include "Brain.h"
#include "Tickable.h"
#include "SRS22Constants.h"

namespace SRS22 {

	/// <summary>
	/// A large block of Neurons.
	/// </summary>
	class Cortex : public Tickable
	{
	public:
		/// <summary>
		/// On big chunk of Neurons in consecutive memory. This allows super fast copy from current to next state.
		/// Amenable to CUDA implementation. There is no Neuron class object.
		/// </summary>
		float neuronCharges[TOTAL_NEURONS];
		float neuronChargesNext[TOTAL_NEURONS];
		int neuronTargets[TOTAL_NEURONS];
		int neuronInputs[TOTAL_NEURONS][NEURON_INPUTS];
		float neuronInputWeights[TOTAL_NEURONS][NEURON_INPUTS];

		/// <summary>
		/// growthRate * brain.overallGoodnessRateOfChange added every tick if brain.ShouldLearn. 
		/// When growthSum hits 1.0 then growthSum is reset to 0.0 and a new Pattern is acquired.
		/// Moderated by global goodness factor.
		/// </summary>
		float growthRate;
		/// <summary>
		/// See growthRate.
		/// </summary>
		float growthSum = 0.0f;

		float neuronChargeDecayFactor = 0.95f;

		Brain& brain;

		Cortex(Brain& brain, const float growthRate) :
			brain(brain),
			growthRate(growthRate)
		{
			// Connect all neurons to random other targets, and random inputs.
			for (int i = 0; i < TOTAL_NEURONS; i++) {
				neuronTargets[i] = GetRandomLinearOffsetExcept(i);
				neuronCharges[i] = 0.0f;
				neuronChargesNext[i] = 0.0f;
				for (int k = 0; k < NEURON_INPUTS; k++) {
					neuronInputs[i][k] = GetRandomLinearOffsetExcept(k);
					neuronInputWeights[i][k] = fastRandFloatPM();
				}
			}
		}

		~Cortex() {
		}

		inline void put(int idx, float val) { neuronCharges[idx] = val; }
		inline float get(int idx) { return neuronCharges[idx]; }

		inline void putNext(int idx, float val) { neuronChargesNext[idx] = val; }
		inline float getNext(int idx) { return neuronChargesNext[idx]; }


		void PostCreate();

		void ComputeNextState() override;

		void LatchNewState() override;
		void DecayNextTowardZero(boolean doParallel);

		void LearningPhase() override;

		inline int GetRandomLinearOffset() {
			return fastRand() % TOTAL_NEURONS;
		}

		inline int GetRandomLinearOffsetExcept(int notThisIdx) {
			int i = fastRand() % TOTAL_NEURONS;
			while (i == notThisIdx) {
				i = fastRand() % TOTAL_NEURONS;
			}
			return i;
		}

		/// <summary>
		/// True if you should try to add a new pattern in this Chunk. False if you shouldn't.
		/// </summary>
		/// <returns></returns>
		bool ShouldAddNewPattern();

	};
}