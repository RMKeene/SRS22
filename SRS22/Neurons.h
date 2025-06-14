#pragma once

#include "SRS22Constants.h"
#include "NeuronLink.h"
#include "FastRand.h"

namespace SRS22 {
	/// <summary>
	/// All the neurons in a cortex. This is separation of concerns for the Cortex lets us
	/// think better about neurons as objects. But... it is a bit of a leaky abstraction because we need the charge array and possibly
	/// other data to be amenable to memory pointer sharing to OpenCV Mat and CUDA.
	/// This also improves memory locality and lets us use things like memset for super fast clears.
	/// 
	/// Our neuron model is not pulse and charge sum based.  It is simply a value between 0 and 1.0. Each neuron has a list of 
	/// NeuronLink to other upstream neurons. The idea is that the Links learn what cortex state results in a future state of the single Neuron.
	/// </summary>
	class Neurons {
	private:
		/// <summary>
		/// This is a circulating index for the charge history.
		/// neuronChargesCurrentIdx is the current tick we are on.
		/// neuronChargesNextIdx is the next tick we are predicting. It is always ahead of the current tick by 1
		/// modulo NEURON_HISTORY. Thus always one behind neuronChargesCurrentIdx modulo NEURON_HISTORY.
		/// Possibly we will use various time offsets as the model evolves.
		/// </summary>
		static int neuronChargesCurrentIdx;
		static int neuronChargesNextIdx;
	public:
		static void StaticTick();
		static int GetNeuronChargesCurrentIdx() { return neuronChargesCurrentIdx; }
		static int GetNeuronChargesNextIdx() { return neuronChargesNextIdx; }

		/// <summary>
		/// The charge of this neuron, range 0.0f to 0.0f. 
		/// Represent time averaged pulses. (See "The Feathers Problem")
		/// We want to keep a past history of the charge so we can learn relative to what was going to be the future charge.
		/// neuronChargesCurrentIdx is the current circular index in the history.
		/// </summary>
		float charge[NEURON_HISTORY][TOTAL_NEURONS];

		/// <summary>
		/// The weighted count of the delta sum.
		/// </summary>
		float neuronChargesAverageCount[TOTAL_NEURONS];

		/// <summary>
		/// The limit on charge due to fatigue. Can be greater than 1.0 so there is reserve metabolism, but still
		/// gets clamped to 1.0 for applying as a charge factor. See settings.maxEnergy etc.
		/// </summary>
		float energyCeiling[TOTAL_NEURONS];

		/// <summary>
		/// Either Regular or Input or Output
		/// </summary>
		NeuronType state[TOTAL_NEURONS];

		/// <summary>
		/// Links to other neurons used to predict this neuron's next state.
		/// </summary>
		NeuronLink link[TOTAL_NEURONS][NEURON_UPSTREAM_LINKS];

		void InitialSetup() {
			for (size_t i = 0; i < TOTAL_NEURONS; i++) {
				energyCeiling[i] = 1.0f;
				for (size_t h = 0; h < NEURON_HISTORY; h++) {
					charge[h][i] = fastRandFloat() * 0.5f;
				}
				for (size_t k = 0; k < NEURON_UPSTREAM_LINKS; k++) {
					link[i][k].otherIdx = GetRandomLinearOffsetExcept(i);
					link[i][k].confidence = fastRandFloat() * 0.002f;
				}
			}
		}

		inline float getCurrent(size_t i) const {
			return charge[neuronChargesCurrentIdx][i];
		}

		inline float getNext(size_t i) const {
			return charge[neuronChargesNextIdx][i];
		}

		inline void setCurrent(size_t i, float value) {
			charge[neuronChargesCurrentIdx][i] = value;
		}

		inline void setNext(size_t i, float value) {
			charge[neuronChargesNextIdx][i] = value;
		}

		inline float& getCurrentRef(size_t i) {
			return charge[neuronChargesCurrentIdx][i];
		}

		inline float& getNextRef(size_t i) {
			return charge[neuronChargesNextIdx][i];
		}

		inline float* getCurrentPointer(size_t i) {
			return &charge[neuronChargesCurrentIdx][i];
		}

		inline float* getNextPointer(size_t i) {
			return &charge[neuronChargesNextIdx][i];
		}

		inline float getPast(size_t i, int ticksAgo) {
			// Lookout, subtracting and getting a negative and then modulo will not work.
			// So we add NEURON_HISTORY to make it positive.
			return charge[(neuronChargesCurrentIdx - ticksAgo + NEURON_HISTORY) % NEURON_HISTORY][i];
		}

		inline float& getPastRef(size_t i, int ticksAgo) {
			return charge[(neuronChargesCurrentIdx - ticksAgo + NEURON_HISTORY) % NEURON_HISTORY][i];
		}

		inline float* getPastPointer(size_t i, int ticksAgo) {
			return &charge[(neuronChargesCurrentIdx - ticksAgo + NEURON_HISTORY) % NEURON_HISTORY][i];
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
		/// Gets a random index in TOTAL_NEURONS but never returns notThisIdx, nor any values in links[NEURON_UPSTREAM_LINKS].
		/// If links is null it gets ignored.
		/// </summary>
		/// <param name="notThisIdx"></param>
		/// <param name="links"></param>
		/// <returns></returns>
		inline int GetRandomLinearOffsetExcept(int notThisIdx) {
			int i = fastRange0Plus() % TOTAL_NEURONS;
			while (true) {
				i = fastRand() % TOTAL_NEURONS;
				if (i != notThisIdx && NotIn(i, link[i]))
					break;

			}
			return i;
		}


	};
}