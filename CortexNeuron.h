#pragma once
#include "pch.h"
#include <opencv2/core.hpp>

namespace SRS22 {
	/// <summary>
	/// A target that CortexNeurons are tyring to predect and influence. This will point ot eithyer a ConceptMap single float charge value
	/// or to the charge (nextM of a ConceptMap's  ConceptState's single element) of a CortexNeuron.
	/// </summary>
	typedef float* BrainTarget;

	/// <summary>
	/// A single neuron in a CortexChunk.  Has a single target to predict, and many inputs with weights to monitor and adjust the weights.
	/// </summary>
	class CortexNeuron
	{
	public:
		const BrainTarget target;
		const int inputCount;
		BrainTarget* inputTargets = nullptr;
		float* inputWeights = nullptr;

		CortexNeuron(BrainTarget t, const int inputCount) :
			target(t),
			inputCount(inputCount) {
			inputTargets = (BrainTarget*)malloc(inputCount * sizeof(BrainTarget));
			inputWeights = (float*)malloc(inputCount * sizeof(float));
		}

		~CortexNeuron() {
		}
	};
}
