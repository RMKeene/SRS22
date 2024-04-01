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
		int neuronChargesCurrentIdx = 0;
		int neuronChargesNextIdx = 1;

		/// <summary>
		/// On big chunk of Neurons in consecutive memory.
		/// Amenable to CUDA implementation. There is no Neuron class object.
		/// 
		/// NEURON_HISTORY is the circular queue of charge history.
		/// neuronCharges[N][neuronChargesCurrentIdx] is the current charge.
		/// neuronCharges[N][neuronChargesCurrentId+1] is the next charge being calculated.
		/// If NEURON_HISTORY is greater than 2 then neuronCharges[N][neuronChargesCurrentIdx - 1] is what the current charge was 1 tick ago, etc.
		/// Thus neuronChargesCurrentIdx gets incremented modulo NEURON_HISTORY every tick, and neuronChargesNextIdx is always neuronChargesCurrentIdx + 1 modulo NURON_HISTORY.
		/// 
		/// Laid out in memory as such that all the charges for a a ConceptMap are contiguous for a given neuronChargesCurrentIdx.
		/// </summary>
		float neuronCharge[NEURON_HISTORY][TOTAL_NEURONS];
		/// <summary>
		/// What target neuron this neuron is trying to predict.
		/// </summary>
		int neuronTarget[TOTAL_NEURONS];
		/// <summary>
		/// The charge value of the target neuron when we have a match.
		/// </summary>
		float neuronTargetCharge[TOTAL_NEURONS];
		/// <summary>
		/// The neurons this neuron is listening to in order to predict the future state of the target.
		/// </summary>
		int neuronInputIdxs[TOTAL_NEURONS][NEURON_INPUTS];
		/// <summary>
		/// How confident we are that the input neuron is relevant to the output target's charge.
		/// </summary>
		float neuronInputConfidence[TOTAL_NEURONS][NEURON_INPUTS];
		/// <summary>
		/// The charge of the input neuron when we have a match. Thus the "expected charge".
		/// </summary>
		float neuronInputCharge[TOTAL_NEURONS][NEURON_INPUTS];

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
				neuronTarget[i] = GetRandomLinearOffsetExcept(i);
				for (int k = 0; k < NEURON_HISTORY; k++) {
					neuronCharge[i][k] = fastRandFloat() * 0.5f;
				}
				for (int k = 0; k < NEURON_INPUTS; k++) {
					neuronInputIdxs[i][k] = GetRandomLinearOffsetExcept(i);
					neuronInputConfidence[i][k] = fastRandFloat() * 0.01f;
					neuronInputCharge[i][k] = fastRandFloat();
				}
			}
		}

		~Cortex() {
		}

		inline void clampNeuronNext(int idx) {
			neuronCharge[idx][neuronChargesNextIdx] = clamp(neuronCharge[idx][neuronChargesNextIdx], 0.0f, 1.0f);
		}

		inline void put(int idx, float val) { neuronCharge[idx][neuronChargesCurrentIdx] = val; }
		inline float get(int idx) { return neuronCharge[idx][neuronChargesCurrentIdx]; }

		inline void putNext(int idx, float val) { neuronCharge[idx][neuronChargesNextIdx] = clamp(val, 0.0f, 1.0f); }
		inline float getNext(int idx) { return neuronCharge[idx][neuronChargesNextIdx]; }

		/// <summary>
		/// agoTicks must be 1 >= agoTicks < NEURON_HISTORY, and it is asserted.
		/// </summary>
		/// <param name="idx"></param>
		/// <param name="agoTicks"></param>
		/// <returns></returns>
		inline float getAgo(int idx, int agoTicks) { 
			assert(agoTicks >= 1 && agoTicks < NEURON_HISTORY);
			return neuronCharge[idx][(neuronChargesCurrentIdx - agoTicks) % NEURON_HISTORY]; 
		}

		inline void sumToNext(int idx, float val) { neuronCharge[idx][neuronChargesNextIdx] += val; }
		inline void multiplyNextToNext(int idx, float val) { neuronCharge[idx][neuronChargesNextIdx] *= val; }

		/// <summary>
		/// The "delta factor" is how far off the pattern neuron charge is from the expected charge.  If it is the same then the factor is 1.0, and if
		/// completely different then 0.0.
		/// Confidence * (1 - abs(expected - actual))
		inline float neuronDeltaFactor(int cortexIdx, int inputIdx, int agoTicks) {
			return neuronInputConfidence[cortexIdx][inputIdx] * (1.0f - fabs(neuronInputCharge[cortexIdx][inputIdx] - neuronCharge[neuronInputIdxs[cortexIdx][inputIdx]][neuronChargesCurrentIdx]));
		}

		/// <summary>
		/// The "delta factor" is how far off the target neuron charge is from the desired charge.  If it is the same then the factor is 1.0, and if
		/// completely different then 0.0.
		/// 1 - abs(desired - actual)
		inline float targetNeuronDeltaFactor(int cortexIdx) {
			return 1.0f - fabs(neuronTargetCharge[cortexIdx] - neuronCharge[neuronTarget[cortexIdx]][neuronChargesCurrentIdx]);
		}

		inline void tickIndicies() {
			neuronChargesCurrentIdx = (neuronChargesCurrentIdx + 1) % NEURON_HISTORY;
			neuronChargesNextIdx = (neuronChargesCurrentIdx + 1) % NEURON_HISTORY;
		}


		void PostCreate();

		void ComputeNextState(boolean doParallel) override;

		void ComputeNextStateSingleNeuron(const size_t& i);

		void LatchNewState(boolean doParallel) override;
		void DecayNextTowardZero(boolean doParallel);

		void LearningPhase(boolean doParallel) override;

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