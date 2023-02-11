#pragma once
#include "pch.h"
#include <opencv2/core.hpp>

#include "BrainLocatable.h"
#include "CortexNeuron.h"
#include "ConnectivityTriple.h"

namespace SRS22 {
	class ConceptMap;

	/// <summary>
	/// A cluster of neurons in the cortex.
	/// All neurons have the same location (BrainLocatable).
	/// All neurons in a chunk are considered "near" distance from each other.
	/// </summary>
	class CortexChunk : public BrainLocatable
	{
	public:
		const int maxNeurons;
		const ConnectivityTriple ctrip;
		/// <summary>
		/// How many neurons currently in this chunk. Not shared_ptr as this will likely end up in the GPU.
		/// neurons points to a buffer of size maxNeurons but neuronsCount is how many are currently instanced.
		/// </summary>
		int neuronCount;
		CortexNeuron* neurons;
		std::vector<std::shared_ptr<ConceptMap>> nearMaps;
		std::vector<std::shared_ptr<ConceptMap>> farMaps;

		CortexChunk(const cv::Vec3f location, const int maxNeurons, const ConnectivityTriple ctrip) :
			BrainLocatable(location),
			neuronCount(0),
			maxNeurons(maxNeurons),
			ctrip(ctrip)
		{
			neurons = (CortexNeuron*)malloc(maxNeurons * sizeof(CortexNeuron));
			for (int i = 0; i < maxNeurons; i++) {
				new (&(neurons[i])) CortexNeuron(nullptr, ctrip.desiredConnectionCount);
			}
		}

		~CortexChunk() {
			for (int i = 0; i < neuronCount; i++) {
				neurons[i].~CortexNeuron();
			}
		}
	};
}