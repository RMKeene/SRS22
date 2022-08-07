#include "pch.h"
#include "SRSUnit.h"
#include "ConnectivityTriple.h"
#include "Brain.h"


namespace SRS22 {

	unsigned short SRSUnit::nextUID = 0;

	SRSUnit::SRSUnit(Brain* br, std::string MapName, ConnectivityTriple ctrip, cv::Vec3f location, int cols, std::string MapDescription) :
		myBrain(br),
		MapName(MapName),
		UID(nextUID++),  
		ctrip(ctrip), location(location), M(cols), nextM(cols),
		MapDescription(MapDescription) {
	}

	SRSUnit::SRSUnit(Brain* br, std::string MapName, ConnectivityTriple ctrip, cv::Vec3f location, int rows, int cols, std::string MapDescription) :
		myBrain(br),
		MapName(MapName),
		UID(nextUID++),
		ctrip(ctrip), location(location), M(rows, cols), nextM(rows, cols),
		MapDescription(MapDescription) {

	}

	SRSUnit::SRSUnit(Brain* br, std::string MapName, ConnectivityTriple ctrip, cv::Vec3f location, int layers, int rows, int cols, std::string MapDescription) :
		myBrain(br),
		MapName(MapName),
		UID(nextUID++),
		ctrip(ctrip), location(location), M(layers, rows, cols), nextM(layers, rows, cols),
		MapDescription(MapDescription) {

	}

	SRSUnit::~SRSUnit() {

	}

	const cv::MatSize SRSUnit::matSize() {
		return M.matSize();
	}

	const int SRSUnit::entriesCount() {
		return M.entriesCount();
	}

	const int SRSUnit::byteCount() {
		return M.byteCount();
	}

	void SRSUnit::PostCreate(Brain& b) {
		nearMaps.clear();
		farMaps.clear();

		std::list<std::shared_ptr<SRSUnit>> nearMapsList;
		std::list<std::shared_ptr<SRSUnit>> farMapsList;

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

	void SRSUnit::ComputeNextState() {
	}

	void SRSUnit::LatchNewState() {
		ConceptState::Copy(nextM, M);
	}

	std::string SRSUnit::Debug() {
		std::string ret = M.Debug();
		return ret;
	}
}