#pragma once
#pragma once

#include "FastRand.h"
#include "Brain.h"
#include "Tickable.h"
#include "SRS22Constants.h"
#include "SRSMath.h"
#include "CortexStats.h"
#include "CortexSettings.h"
#include "Neurons.h"

namespace SRS22 {

	/// <summary>
	/// A large block of Neurons.
	/// </summary>
	class Cortex : public Tickable
	{
	public:
		const Brain& brain;

		Neurons neurons;

		CortexSettings settings;

		CortexStats stats;

		Cortex(Brain& brain) :
			brain(brain)
		{
			// Connect all neuron inputs to random other neurons.
			for (int i = 0; i < TOTAL_NEURONS; i++) {
				neurons.energy[i] = fastRandFloat();
				neurons.enabled[i] = NeuronState::ENABLED;;
				for (int h = 0; h < NEURON_HISTORY; h++) {
					neurons.charge[h][i] = fastRandFloat() * 0.5f;
				}
				for (int k = 0; k < NEURON_UPSTREAM_LINKS; k++) {
					neurons.link[i]->otherIdx = NEURON_LINK_UNCONNECTED;
				}
				for (int k = 0; k < NEURON_UPSTREAM_LINKS; k++) {
					NeuronLink& L = neurons.link[i][k];
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

		inline void checkNan(const float val) {
#ifdef VALIDATE_NEURONS
			if (!isfinite((val)))
				SRS22DebugBreak(val);
#endif
		}

		inline void checkNanByIdx(const int idx) {
#ifdef VALIDATE_NEURONS
			checkNan(idx, neurons[idx].getCurrentCharge());
#endif
		}

		inline void checkPastOffset(const int offset) {
#ifdef VALIDATE_NEURONS
			if (offset < 0 || offset > NEURON_HISTORY_MAX_PAST)
				SRS22DebugBreak(offset);
#endif
		}

		inline void checkNanByIdxNext(const int idx) {
#ifdef VALIDATE_NEURONS
			checkNan(idx, neurons[idx].getNextCharge());
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

		inline void checkZeroToOne(float v) {
#ifdef VALIDATE_NEURONS
			if (v < 0.0f || v > 1.0f) {
				__debugbreak();
			}
#endif
		}

		inline float& operator[](int idx) {
			checkNeuronIdx(idx);
			return neurons.getCurrentRef(idx);
		}

		void doNanScan() {
			for (int i = 0; i < TOTAL_NEURONS; i++) {
				for (int h = 0; h < NEURON_HISTORY; h++) {
					if (isnan(neurons.charge[h][i])) {
						__debugbreak();
					}
					if (neurons.charge[h][i] < -0.1f || neurons.charge[h][i] > 1.1f) {
						__debugbreak();
					}
				}
			}
		}

		inline void clampNeuron(int idx, int historyIdx) {
			neurons.charge[historyIdx][idx] = clamp<float>(neurons.charge[historyIdx][idx], 0.0f, 1.0f);
		}

		inline void put(int idx, float val) {
			checkNan(idx, val);
			neurons.getCurrentRef(idx) = val;
			checkNeuronCharge(idx);
		}

		inline float get(int idx) {
			checkNeuronIdx(idx);
			return neurons.getCurrent(idx);
		}

		inline void putNext(int idx, float val) {
			checkNan(idx, val);
			checkNeuronIdx(idx);
			neurons.setNext(idx, val);
		}

		inline float getNext(int idx) {
			checkNeuronIdx(idx);
			checkNanByIdxNext(idx);
			return neurons.getNext(idx);
		}

		inline float getPast(int idx, int ticksAgo) {
			checkNeuronIdx(idx);
			checkNanByIdx(idx);
			checkPastOffset(ticksAgo);
			return neurons.getPast(idx, ticksAgo);
		}		

		/// <summary>
		/// Simply Neuron::StaticTick();
		/// </summary>
		inline void TickIndicies() {
			Neurons::StaticTick();
		}

		void PostCreate();

		void ResetStats();

		void PostProcessStats();

		void ComputeNextState(boolean doParallel) override;

		void PreComputeNextStateSingleNeurons();
		void ComputeNextStateSingleNeuron(const size_t i, CortexThreadStats& threadStats);
		void PostComputeNextStateSingleNeurons();

		/// <summary>
		/// Set self match true, count in stats, deduct metabolism, and add link's vote.
		/// </summary>
		/// <param name="L"></param>
		/// <param name="threadStats"></param>
		/// <param name="N"></param>
		/// <param name="selfDeltaC"></param>
		inline void FireConnection(int neuronIdx, int linkIdx, SRS22::CortexThreadStats& threadStats, const float otherMatchStrength)
		{
			NeuronLink& L = neurons.link[neuronIdx][linkIdx];
			L.wasMatch = true;
			neurons.wasMatch[neuronIdx] = true;
			threadStats.countOfNeuronsFired++;

			DeductFiringMetabolism(neuronIdx);
			AddLinkVote(L, otherMatchStrength);
		}

		/// <summary>
		/// Get the factor from 0 to 1 that represents how much the learned charge matches the current actual charge.
		/// settings.selfDeltaSteepness is how quickly this falls to 0 as the difference between the two charges increases.
		/// </summary>
		/// <param name="L"></param>
		/// <param name="C"></param>
		/// <returns></returns>
		inline const float& LinkOtherMatchStrength(NeuronLink& L)
		{
			const float& otherC = neurons.getCurrent(L.otherIdx);
			float dC = fabs(L.selfCharge - otherC);
			if(dC < 1.0f / settings.linkMatchSharpness)
				return clamp<float>(1.0f - settings.linkMatchSharpness * dC, 0.0f, 1.0f);
			return 0.0f;
		}

		inline void ResetVote(int neuronIdx) {
			neurons.neuronChargesAverageDeltaSum[neuronIdx] = 0.0f;
			neurons.neuronChargesAverageCount[neuronIdx] = 0.0f;
		}
		/// <summary>
		/// Add this connections 
		/// </summary>
		/// <param name="otherNeuron"></param>
		/// <param name="L"></param>
		inline void AddLinkVote(const NeuronLink& L, const float otherMatchStrength)
		{
			const float strength = L.confidence * otherMatchStrength;
			// Weighted average sum in.
			neurons.neuronChargesAverageDeltaSum[L.otherIdx] += L.otherCharge * strength;
			neurons.neuronChargesAverageCount[L.otherIdx] += strength;
		}

		inline bool ConsumeVote(int neuronIdx)
		{
			// If there are no votes, then the neuron will not change.
			if (neurons.neuronChargesAverageCount[neuronIdx] > 0.0001f) {
				// The average of the votes is the new charge.
				neurons.setNext(neuronIdx, neurons.neuronChargesAverageDeltaSum[neuronIdx] / neurons.neuronChargesAverageCount[neuronIdx]);
				stats.countStimulus++;
				return true;
			}
			return false;
		}

		/// <summary>
		/// Deduct settings.energyDepletionOnFire from energy, 
		/// then disables if energy is below settings.lowEnergyThreshold
		/// </summary>
		/// <param name="N"></param>
		inline void DeductFiringMetabolism(int idx)
		{
			// Metabolic cost to fire.
			neurons.energy[idx] -= settings.energyDepletionOnFire;
			if (neurons.energy[idx] < settings.lowEnergyThreshold) {
				// We set this false but that will not be read until the next tick.
				neurons.enabled[idx] = NeuronState::DISABLED;
			}
		}

		/// <summary>
		/// Add in firing count, and zero and one count if C is close to 0 or 1.
		/// </summary>
		/// <param name="threadStats"></param>
		/// <param name="C"></param>
		inline void UpdateProcessedStatCounts(SRS22::CortexThreadStats& threadStats, const float C)
		{
			threadStats.countOfNeuronsProcessed++;
			threadStats.sumOfC += C;
			if (C >= 0.99999f)
				threadStats.countOfOnes++;
			else if (C <= 0.00001f)
				threadStats.countOfZeros++;
		}

		/// <summary>
		/// If currently disabled , add energy.
		/// If that gets energy above settings.highEnergyThreshold, then set enable true.
		/// </summary>
		/// <param name="N"></param>
		inline void RechargeMetabolismIf(int idx)
		{
			if (neurons.enabled[idx] == NeuronState::DISABLED) {
				neurons.energy[idx] += settings.energyRechargePerTick;
				if (neurons.energy[idx] >= settings.highEnergyThreshold)
					neurons.enabled[idx] = NeuronState::ENABLED;
			}
		}

		void LatchNewState(boolean doParallel) override;

		void LearningPhase(boolean doParallel) override;

		void DoLearningSingleNeuron(const size_t i, CortexThreadStats& threadStats);

		inline int GetRandomLinearOffset() {
			return fastRange0Plus() % TOTAL_NEURONS;
		}

		/// <summary>
		/// neuronIdx if is not in the links[linksCount] array return true.
		/// links may be null, then returns true.
		/// </summary>
		/// <param name="neuronIdx"></param>
		/// <param name="links"></param>
		/// <param name="linksCount"></param>
		/// <returns></returns>
		inline bool NotIn(int neuronIdx, NeuronLink* links) {
			if (links == nullptr)
				return true;
			for (int i = 0; i < NEURON_UPSTREAM_LINKS; i++) {
				if (links[i].otherIdx == neuronIdx)
					return false;
			}
			return true;
		}

		/// <summary>
		/// Gets a random index in TOTAL_NEURONS but never returns notThisIdx, nor any values in neurons.link[notThisIdx][NEURON_UPSTREAM_LINKS].
		/// Thus, do not connect to self or duplicate upstream links.
		/// If links is null it gets ignored.
		/// </summary>
		/// <param name="notThisIdx"></param>
		/// <param name="links"></param>
		/// <returns></returns>
		inline int GetRandomLinearOffsetExcept(int notThisIdx) {
			int i = fastRange0Plus() % TOTAL_NEURONS;
			while (true) {
				i = fastRand() % TOTAL_NEURONS;
				if (i != notThisIdx && NotIn(i, neurons.link[i]))
					break;

			}
			return i;
		}

	};
}