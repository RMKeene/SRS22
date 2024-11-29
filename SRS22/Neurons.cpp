#include "Neurons.h"

namespace SRS22 {

	int Neurons::neuronChargesCurrentIdx = 0;
	int Neurons::neuronChargesNextIdx = NEURON_HISTORY - 1;

	void Neurons::StaticTick() {
		neuronChargesCurrentIdx = (neuronChargesCurrentIdx + 1) % NEURON_HISTORY;
		neuronChargesNextIdx = (neuronChargesNextIdx + 1) % NEURON_HISTORY;
	}
}