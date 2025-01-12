#include "Neurons.h"

namespace SRS22 {

	int Neurons::neuronChargesCurrentIdx = 0;
	int Neurons::neuronChargesNextIdx = 1;

	void Neurons::StaticTick() {
		// Order here is important.
		neuronChargesCurrentIdx = (neuronChargesCurrentIdx + 1) % NEURON_HISTORY;
		neuronChargesNextIdx = (neuronChargesCurrentIdx + 1) % NEURON_HISTORY;
	}
}