#include "pch.h"
#include "ConceptMap.h"
#include "Brain.h"
#include <string>
#include <format>
#include "MapUIDs.h"
#include <opencv2/core/mat.hpp>
#include <opencv2/core/hal/interface.h>

namespace SRS22 {
	ConceptMap::ConceptMap(Brain* br, MapUidE UID, std::string MapName, int cols, float decayFactor, std::string MapDescription) :
		myBrain(br),
		MapName(MapName),
		UID(UID),
		cols(cols),
		rows(1),
		depth(1),
		totalSize(cols),
		decayFactor(decayFactor),
		MapDescription(MapDescription) {
		numDims[0] = depth;
		numDims[1] = rows;
		numDims[2] = cols;

	}

	ConceptMap::ConceptMap(Brain* br, MapUidE UID, std::string MapName, int rows, int cols, float decayFactor, std::string MapDescription) :
		myBrain(br),
		MapName(MapName),
		UID(UID),
		cols(cols),
		rows(rows),
		depth(1),
		totalSize(cols* rows),
		decayFactor(decayFactor),
		MapDescription(MapDescription) {
		numDims[0] = depth;
		numDims[1] = rows;
		numDims[2] = cols;
	}

	ConceptMap::ConceptMap(Brain* br, MapUidE UID, std::string MapName, int depth, int rows, int cols, float decayFactor, std::string MapDescription) :
		myBrain(br),
		MapName(MapName),
		UID(UID),
		cols(cols),
		rows(rows),
		depth(depth),
		totalSize(cols* rows* depth),
		decayFactor(decayFactor),
		MapDescription(MapDescription) {
		numDims[0] = depth;
		numDims[1] = rows;
		numDims[2] = cols;
	}

	ConceptMap::~ConceptMap() {
	}

	void ConceptMap::setupCVMatMirrors() {
		cortexAsMat = cv::Mat(3, numDims, CV_32FC1, &myBrain->cortex->neuronCharges[cortexStartIndex]);
		cortexNextAsMat = cv::Mat(3, numDims, CV_32FC1, &myBrain->cortex->neuronChargesNext[cortexStartIndex]);
	}

	void ConceptMap::PostCreate(Brain& b) {

	}

	void ConceptMap::ComputeNextState() {
	}

	/// <summary>
	/// Decay and then add nextM to M. The set nextM to zeros.
	/// </summary>
	void ConceptMap::LatchNewState() {
		// Cortex does the next state transfer of nextCharge to charge.
	}

	std::string ConceptMap::Debug() {
		return std::format("");
	}

}