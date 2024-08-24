#pragma once

#include "FastRand.h"
#include "Brain.h"
#include "Tickable.h"
#include "SRS22Constants.h"
#include "SRSMath.h"

#define neuronChargeValue(idx) neuronCharge[neuronChargesCurrentIdx][(idx)]
#define neuronChargeValueNext(idx) neuronCharge[neuronChargesNextIdx][(idx)]

// Turns on neuron index, range, and NaN validation.
//#define VALIDATE_NEURONS

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
		/// The neurons this neuron is listening to in order to predict the future state of its self.
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
			// Connect all neuron inputs to random other neurons.
			for (int i = 0; i < TOTAL_NEURONS; i++) {
				for (int h = 0; h < NEURON_HISTORY; h++) {
					neuronCharge[h][i] = fastRandFloat() * 0.5f;
					checkChargeRange(i, neuronCharge[h][i]);
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

		inline void checkNeuronIdx(const int idx) {
#ifdef VALIDATE_NEURONS
			if (idx < 0 || idx >= TOTAL_NEURONS)
				SRS22DebugBreak(idx, 0.0f);
#endif
		}

		inline void checkNan(const int idx, const float val) {
#ifdef VALIDATE_NEURONS
			if (!isfinite((val)))
				SRS22DebugBreak(idx, val);
#endif
		}

		inline void checkNanByIdx(const int idx) {
#ifdef VALIDATE_NEURONS
			checkNan(idx, neuronChargeValue(idx));
#endif
		}

		inline void checkNanByIdxNext(const int idx) {
#ifdef VALIDATE_NEURONS
			checkNan(idx, neuronChargeValueNext(idx));
#endif
		}

		inline void checkChargeRange(const int idx, const float val) {
#ifdef VALIDATE_NEURONS
			checkNan(idx, val);
			if (val < -0.1f || val > 1.1f)
				SRS22DebugBreak(idx, val);
#endif
		}

		inline void checkChargeRangeLiberal(const int idx, const float val) {
#ifdef VALIDATE_NEURONS
			checkNan(idx, val);
			if (val < -10.0f || val > 10.5f)
				SRS22DebugBreak(idx, val);
#endif
		}

		inline void checkNeuronCharge(const int idx) {
#ifdef VALIDATE_NEURONS
			checkNeuronIdx(idx);
			checkChargeRangeLiberal(idx, neuronChargeValue(idx));
#endif
		}

		void doNanScan() {
			for (int i = 0; i < TOTAL_NEURONS; i++) {
				for (int h = 0; h < NEURON_HISTORY; h++) {
					if (isnan(neuronCharge[h][i])) {
						__debugbreak();
					}
					if (neuronCharge[h][i] < -0.1f || neuronCharge[h][i] > 1.1f) {
						__debugbreak();
					}
				}
			}
		}

		inline void clampNeuronNext(int idx) {
			neuronChargeValue(idx) = clamp<float>(neuronChargeValueNext(idx), 0.0f, 1.0f);
		}

		inline void put(int idx, float val) {
			checkNeuronCharge(idx);
			checkNan(idx, val);
			neuronChargeValue(idx) = val;
			checkNeuronCharge(idx);

		}
		inline float get(int idx) {
			checkNeuronIdx(idx);
			checkNan(idx, neuronChargeValue(idx));
			return neuronChargeValue(idx);
		}

		inline void putNext(int idx, float val) {
			checkNan(idx, val);
			checkNeuronIdx(idx);
			neuronChargeValueNext(idx) = clamp(val, 0.0f, 1.0f);
			checkNanByIdxNext(idx);
		}
		inline float getNext(int idx) {
			checkNeuronIdx(idx);
			checkNanByIdxNext(idx);
			return neuronCharge[neuronChargesNextIdx][idx];
		}

		/// <summary>
		/// agoTicks must be 1 >= agoTicks < NEURON_HISTORY, and it is asserted.
		/// </summary>
		/// <param name="idx"></param>
		/// <param name="agoTicks"></param>
		/// <returns></returns>
		inline float getAgo(int idx, int agoTicks) {
			checkNeuronIdx(idx);
			assert(agoTicks >= 1 && agoTicks < NEURON_HISTORY);
			checkNan(idx, neuronCharge[(neuronChargesCurrentIdx - agoTicks) % NEURON_HISTORY][idx]);
			return neuronCharge[(neuronChargesCurrentIdx - agoTicks) % NEURON_HISTORY][idx];
		}

		inline void sumToNext(int idx, float val) {
			checkNeuronCharge(idx);
			neuronCharge[neuronChargesNextIdx][idx] += val;
			checkNeuronCharge(idx);
		}
		inline void multiplyNextToNext(int idx, float val) {
			checkNan(idx, val);
			neuronCharge[neuronChargesNextIdx][idx] *= val;
			checkNan(idx, neuronCharge[neuronChargesNextIdx][idx]);
		}

		/// <summary>
		/// The "delta factor" is how far off the pattern  neuron charge is from the expected charge.  If it is the same then the factor is 1.0, and if
		/// completely different then 0.0.
		/// Confidence * (1 - abs(expected - actual))
		inline float neuronDeltaFactor(int cortexIdx, int inputIdx, int agoTicks) {
			checkNeuronIdx(cortexIdx);
			float f = neuronInputConfidence[cortexIdx][inputIdx] * (1.0f - fabs(neuronInputCharge[cortexIdx][inputIdx] - neuronCharge[neuronChargesCurrentIdx][neuronInputIdxs[cortexIdx][inputIdx]]));
			checkNan(cortexIdx, f);
			return f;
		}

		/// <summary>
		/// The "delta factor" is how far off the target neuron charge is from the desired charge.  If it is the same then the factor is 1.0, and if
		/// completely different then 0.0.
		/// 1 - abs(desired - actual)
		inline float targetNeuronDeltaFactor(int cortexIdx) {
			//checkNeuronCharge(cortexIdx);
			//checkNeuronIdx(neuronTarget[cortexIdx]);
			//checkChargeRangeLiberal((neuronTarget[cortexIdx]), neuronChargeValue(neuronTarget[cortexIdx]));
			//checkNeuronCharge(neuronTarget[cortexIdx]);
			//checkChargeRangeLiberal(cortexIdx, neuronTargetCharge[cortexIdx]);
			//float f = 1.0f - fabs(neuronTargetCharge[cortexIdx] - neuronCharge[neuronChargesCurrentIdx][neuronTarget[cortexIdx]]);
			//checkNeuronCharge(cortexIdx);
			//return f;
			return 0.0f;
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