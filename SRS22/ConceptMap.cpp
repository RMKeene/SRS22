#include "pch.h"
#include "ConceptMap.h"
#include "Brain.h"
#include <string>
#include <format>
#include "MapUIDs.h"

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

	}

	ConceptMap::ConceptMap(Brain* br, MapUidE UID, std::string MapName, int layers, int rows, int cols, float decayFactor, std::string MapDescription) :
		myBrain(br),
		MapName(MapName),
		UID(UID),
		cols(cols),
		rows(rows),
		depth(layers),
		totalSize(cols* rows* layers),
		decayFactor(decayFactor),
		MapDescription(MapDescription) {
	}

	ConceptMap::~ConceptMap() {
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