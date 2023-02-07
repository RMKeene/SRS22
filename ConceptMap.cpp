#include "pch.h"
#include "ConceptMap.h"
#include "ConnectivityTriple.h"
#include "Brain.h"
#include "BrainLocatable.h"

namespace SRS22 {

	ConceptMap::ConceptMap(Brain* br, MapUidE UID, std::string MapName, ConnectivityTriple ctrip, const cv::Vec3f location, int cols, std::string MapDescription) :
		BrainLocatable(location),
		myBrain(br),
		MapName(MapName),
		UID(UID),
		ctrip(ctrip), M(cols), nextM(cols),
		MapDescription(MapDescription) {
	}

	ConceptMap::ConceptMap(Brain* br, MapUidE UID, std::string MapName, ConnectivityTriple ctrip, const cv::Vec3f location, int rows, int cols, std::string MapDescription) :
		BrainLocatable(location), 
		myBrain(br),
		MapName(MapName),
		UID(UID),
		ctrip(ctrip),  M(rows, cols), nextM(rows, cols),
		MapDescription(MapDescription) {
	}

	ConceptMap::ConceptMap(Brain* br, MapUidE UID, std::string MapName, ConnectivityTriple ctrip, const cv::Vec3f location, int layers, int rows, int cols, std::string MapDescription) :
		BrainLocatable(location), 
		myBrain(br),
		MapName(MapName),
		UID(UID),
		ctrip(ctrip), M(layers, rows, cols), nextM(layers, rows, cols),
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
		nearMaps.clear();
		farMaps.clear();

		std::list<std::shared_ptr<ConceptMap>> nearMapsList;
		std::list<std::shared_ptr<ConceptMap>> farMapsList;

		float near2 = b.maxNearDistance * b.maxNearDistance;
		float far2 = b.minFarDistance * b.minFarDistance;
		for (auto u : b.conceptMaps) {
			cv::Vec3f d = u.second->location - location;
			const float d2 = d[0] * d[0] + d[1] * d[1] + d[2] * d[2];
			if (u.second->UID != UID) {
				if (d2 <= near2) {
					nearMapsList.push_back(u.second);
				}
				else if (d2 <= far2) {
					farMapsList.push_back(u.second);
				}
			}
		}
		// Convert to solid array.
		nearMaps.assign(nearMapsList.begin(), nearMapsList.end());
		farMaps.assign(farMapsList.begin(), farMapsList.end());
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