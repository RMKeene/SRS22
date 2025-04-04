#include "SRS22pch.h"
#include "Cortex.h"
#include "SRSMath.h"
#include <ppl.h>

namespace SRS22 {

	void Cortex::ResetStats() {
		stats.reset();
	}

	void Cortex::PostProcessStats() {
		stats.averageNeuronCharge = (float)(stats.sumOfC / stats.countOfNeuronsProcessed);
		stats.averageConfidence = (float)(stats.sumOfConfidence / stats.countOfConfidence);
	}

	void Cortex::ComputeNextState(boolean doParallel) {
#if DONANCHECKS
		doNanScan();
#endif
		PreComputeNextStateSingleNeurons();
		if (doParallel) {
			Concurrency::combinable<CortexThreadStats> threadStats;
			Concurrency::parallel_for(0, TOTAL_NEURONS, [&](size_t i) {
				ComputeNextStateSingleNeuron(i, threadStats.local());
				});
			threadStats.combine_each([&](CortexThreadStats threadStats) {
				stats.SumInNoLock(threadStats);
				});
		}
		else {
			CortexThreadStats threadStats;
			for (int i = 0; i < TOTAL_NEURONS; i++) {
				ComputeNextStateSingleNeuron(i, threadStats);
			}
			stats.SumInNoLock(threadStats);
		}
		PostComputeNextStateSingleNeurons();
#if DONANCHECKS
		doNanScan();
#endif
	}

	void Cortex::ComputeNextStateSingleNeuron(const size_t i, CortexThreadStats& threadStats)
	{
		float C = neurons.getCurrent(i);

		UpdateProcessedStatCounts(threadStats, C);

		for (int k = 0; k < NEURON_UPSTREAM_LINKS; k++) {
			NeuronLink& L = neurons.link[i][k];

			if (L.otherIdx == NEURON_LINK_UNCONNECTED)
				continue;

#ifdef _DEBUG
			if (L.otherIdx < 0 || L.otherIdx >= TOTAL_NEURONS)
				throw std::out_of_range(std::format("L.otherIdx out of range: {0}", L.otherIdx));
#endif

			if (C > 0.001f)
				threadStats.countOfNeuronsFired++;

			// Stimulus. Charge of a Neuron can range between 0.0f and 1.0f
			// Weight can range between -1.0 and 1.0. So no need to clamp the result.
			const float stimulus =
				get(L.otherIdx) * L.weight *
				NEURON_UPSTREAM_LINKS_INVERSE *
				settings.connectionThrottle;

			// Add link stimulus. Gets clamped later,
			neurons.getNextRef(i) += C + stimulus;
		}

		// Now clamp the result.
		neurons.setNext(i, std::clamp(neurons.getNext(i), 0.0f, 1.0f));
		checkNanByIdx(i);
	}

	/// <summary>
	/// Increments the global tick indicies for Neuron. Next becomes current state, current state becomes previous state.
	/// </summary>
	void Cortex::LatchNewState(boolean doParallel) {
		// Tick the indicies for (static indicies) all neurons.
		TickIndicies();
	}

	void Cortex::LearningPhase(boolean doParallel) {

		float learnFactor = brain.learningRate;
		if (doParallel) {
			Concurrency::combinable<CortexThreadStats> threadStats;

			Concurrency::parallel_for(0, TOTAL_NEURONS, [&](size_t i) {
				DoLearningSingleNeuron(i, threadStats.local());
				});

			threadStats.combine_each([&](CortexThreadStats threadStats) {
				stats.SumInNoLock(threadStats);
				});
		}
		else {
			CortexThreadStats threadStats;
			for (int i = 0; i < TOTAL_NEURONS; i++) {
				DoLearningSingleNeuron(i, threadStats);
			}
			stats.SumInNoLock(threadStats);
		}
	}

	void Cortex::DoLearningSingleNeuron(const size_t i, CortexThreadStats& threadStats) {
		// Input neurons are not predicted, they are hard set to a value by hardware IO.  
		// Their NeuronLinks are not used. So there is no learning to do.
		if (neurons.state[i] == NeuronState::IS_INPUT)
			return;

		const float C = neurons.getCurrent(i);

		// Deplete some metabolism
		neurons.energyCeiling[i] = std::clamp(neurons.energyCeiling[i] 
			// Deplete energy
			- C * settings.energyDepletionOnFire
			// Recover energy
			+ settings.energyRechargePerTick, 0.0f, settings.maxEnergy);

		// Neuroplasticity: Learn to predict the future state of this neuron.
		for (int k = 0; k < NEURON_UPSTREAM_LINKS; k++) {
			NeuronLink& L = neurons.link[i][k];
			threadStats.sumOfConfidence += L.confidence;
			threadStats.countOfConfidence++;
			here
			// TODO - Hebian learning
		}
	}

	void Cortex::PostCreate() {

	}

}