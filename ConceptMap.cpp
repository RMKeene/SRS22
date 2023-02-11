#include "pch.h"
#include "ConceptMap.h"
#include "ConnectivityTriple.h"
#include "Brain.h"
#include "BrainLocatable.h"

namespace SRS22 {
	ConceptMap::ConceptMap(Brain* br, MapUidE UID, std::string MapName, const cv::Vec3f location, int cols, std::string MapDescription) :
		BrainLocatable(location),
		myBrain(br),
		MapName(MapName),
		UID(UID),
		M(cols), nextM(cols),
		MapDescription(MapDescription) {
	}

	ConceptMap::ConceptMap(Brain* br, MapUidE UID, std::string MapName, const cv::Vec3f location, int rows, int cols, std::string MapDescription) :
		BrainLocatable(location),
		myBrain(br),
		MapName(MapName),
		UID(UID),
		M(rows, cols), nextM(rows, cols),
		MapDescription(MapDescription) {
	}

	ConceptMap::ConceptMap(Brain* br, MapUidE UID, std::string MapName, const cv::Vec3f location, int layers, int rows, int cols, std::string MapDescription) :
		BrainLocatable(location),
		myBrain(br),
		MapName(MapName),
		UID(UID),
		M(layers, rows, cols), nextM(layers, rows, cols),
		MapDescription(MapDescription) {
	}

	ConceptMap::~ConceptMap() {
	}

	const cv::MatSize ConceptMap::matSize() {
		return M.matSize();
	}

	const int ConceptMap::entriesCount() {
		return M.entriesCount();
	}

	const int ConceptMap::byteCount() {
		return M.byteCount();
	}

	void ConceptMap::PostCreate(Brain& b) {

	}

	void ConceptMap::ComputeNextState() {
		if (doDecay)
			nextM.charges = M.charges * decayFactor;
	}

	void ConceptMap::LatchNewState() {
		ConceptState::Copy(nextM, M);
	}

	std::string ConceptMap::Debug() {
		std::string ret = M.Debug();
		return ret;
	}
}