#pragma once
#pragma once

#include "FastRand.h"
#include "Brain.h"
#include "Tickable.h"
#include "SRS22Constants.h"
#include "SRSMath.h"
#include "CortexStats.h"

#define neuronChargeValue(idx) neuronCharge[neuronChargesCurrentIdx][(idx)]
#define neuronChargeValueNext(idx) neuronCharge[neuronChargesNextIdx][(idx)]

// Turns on neuron index, range, and NaN validation.
//#define VALIDATE_NEURONS

namespace SRS22 {

	/// <summary>
	/// A link from a "other" neuron to this neuron with expected values for a 'match'.
	/// When the other neuron's charge is close to the otherCharge, and this neuron's
	/// charge is close to the selfCharge, then it is a match and stimulation happens according to the 
	/// confidence. The overall goal is that the link is predicting this neuron's future state.
	/// </summary>
	struct NeuronLink {
		int otherIdx;
		float otherCharge;
		float confidence;
		float selfCharge;
	};

	/// <summary>
	/// A large block of Neurons.
	/// </summary>
	class Cortex : public Tickable
	{
	public:

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
		NeuronLink link[TOTAL_NEURONS][NEURON_INPUTS];

		int neuronChargesCurrentIdx = 0;
		int neuronChargesNextIdx = 1;

		CortexStats stats;

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

		/// <summary>
		/// When other stimulates this toward the expected match value, this is how much stimulus overall is allowed.
		/// If there are 40 inputs to neurons it is possible the the overall sum of stimulus could be 40.0 and flood the system.
		/// So to achieve a activity balance tick to tick we throttle the stimulus down some ro up some if not enough activity.
		/// </summary>
		float connectionThrottle = 2.0f;

		/// <summary>
		/// If confidence is below this then the link is stale and has a probability of a reroute.
		/// </summary>
		float rerouteThreshold = 0.001f;
		float rerouteProbability = 0.01f;
		float lowLearnThreshold = 0.25f;
		float lowLearnRate = 0.01f;
		float hiLearnRate = 0.05f;
		float confidenceAdjustmentRate = 0.01f;
		float minimumConfidence = 0.0001f;
		float maximumConfidence = 0.9999f;
		/// <summary>
		/// When a reroute happens this is what the confidence is set to.
		/// </summary>
		float rerouteConfidenceSet = 0.5f;

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
					NeuronLink& L = link[i][k];
					L.otherIdx = GetRandomLinearOffsetExcept(i);
					L.confidence = fastRandFloat() * 0.01f;
					L.otherCharge = fastRandFloat();
					L.selfCharge = fastRandFloat();
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

		inline void multiplyToNext(int idx, float val) {
			checkNan(idx, val);
			neuronCharge[neuronChargesNextIdx][idx] *= val;
			checkNan(idx, neuronCharge[neuronChargesNextIdx][idx]);
		}

		/// <summary>
		/// Apply the stimulus that other should give to this.
		/// 
		/// Some math:  If a neuron connects to other neurons, and the connectivity is 40 incoming connections to one neuron,
		/// then every tick if there is a linear falloff of match at a ratio of 1:1 for deltaC and otherDeltaC.
		/// So an average stimulus strength if 50% for the otherNeuron, multiplied by the 50% for the self neuron.
		/// Both are determined by deltaC and otherDeltaC. So the stimulus per tick is 40.0 * 0.5 * 0.5 = 10.0.
		/// This is a lot of stimulus, and if all neurons are connected to all other neurons then the system will be flooded
		/// by stimulus and all the C will max out and clip at 1.0.
		/// 
		/// So to prevent this we throttle the stimulus down by otherInfluenceSoftness. which in the above 
		/// case would be 0.1 for a neutral and stable system.
		/// 
		/// But, we can have tighter selectivity and instead of a 1:1 fall off of stimulus by deltaC we can make it higher.
		/// If we have a fall off of 10:1 then the stimulus is 40.0 * 0.5 * 0.1 = 2.0. This is a much more stable system.
		/// It also has lots of neurons that are off, and a few that are on, so has more pattern sensitivity.
		/// 
		/// There are other factors like neural fatigue where over used neurons rest for a bit and that will also reduce overall activity.
		/// 
		///
		inline float applyOtherStimulus(int cortexIdx, int inputIdx, CortexThreadStats& threadStats) {
			// How steeply to reduce connection influence as deltaC and otherDeltaC get larger and it is not a pattern match.
			const float otherDeltaSteepness = 10.0f;
			const float selfDeltaSteepness = 10.0f;
			checkNeuronIdx(cortexIdx);
			NeuronLink& L = link[cortexIdx][inputIdx];

			checkNeuronIdx(L.otherIdx);
			const float otherCharge = neuronCharge[neuronChargesCurrentIdx][L.otherIdx];
			const float otherChargeTarget = L.otherCharge;
			const float otherDelta = otherChargeTarget - otherCharge;
			const float otherAbsDelta = fabs(otherDelta);
			const float otherAbsDeltaC = clamp(1.0f - otherDeltaSteepness * otherAbsDelta, 0.0f, 1.0f);
			checkChargeRange(cortexIdx, otherAbsDeltaC);
			if (otherAbsDeltaC <= 0.0f) {
				return 0.0f;
			}			
			const float otherInfluence = L.confidence * otherAbsDeltaC;
			checkChargeRange(cortexIdx, otherInfluence);
			if(otherInfluence <= 0.0f) {
				return 0.0f;
			}

			// What this connection expects selfC to be if otherC is at otherCharge.
			const float selfCharge = get(cortexIdx);
			const float selfChargeTarget = L.selfCharge;
			const float selfDelta = selfChargeTarget - selfCharge;
			const float selfAbsDeltaC = fabs(selfDelta);
			const float selfDeltaC = clamp(1.0f - selfDeltaSteepness * selfAbsDeltaC, 0.0f, 1.0f);
			checkChargeRange(cortexIdx, selfDeltaC);
			if (selfDeltaC <= 0.0f) {
				return 0.0f;
			}
			threadStats.countOfNeuronsFired++;
			// How much to move C toward the expected value.
			const float f = selfDelta * otherAbsDeltaC * connectionThrottle;
			checkNan(cortexIdx, f);
			sumToNext(cortexIdx, f);
			checkNan(cortexIdx, f);
			return f;
		}

		inline void tickIndicies() {
			neuronChargesCurrentIdx = (neuronChargesCurrentIdx + 1) % NEURON_HISTORY;
			neuronChargesNextIdx = (neuronChargesCurrentIdx + 1) % NEURON_HISTORY;
		}

		void PostCreate();

		void ResetStats();
		
		void PostProcessStats();

		void ComputeNextState(boolean doParallel) override;

		void ComputeNextStateSingleNeuron(const size_t i, CortexThreadStats& threadStats);

		void LatchNewState(boolean doParallel) override;

		void LearningPhase(boolean doParallel) override;

		void DoLearningSingleNeuron(const size_t i, CortexThreadStats& threadStats);

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

	};
}