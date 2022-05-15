#include "pch.h"
#include "SRSUnit.h"
#include "ConnectivityTriple.h"
#include "Brain.h"


namespace SRS22 {

	unsigned short SRSUnit::nextUID = 0;

	SRSUnit::SRSUnit(std::string MapName, ConnectivityTriple ctrip, cv::Vec3f location, int w, std::string MapDescription) :
		MapName(MapName),
		UID(nextUID++),  
		ctrip(ctrip), location(location), M(w), nextM(w),
		MapDescription(MapDescription) {
	}

	SRSUnit::SRSUnit(std::string MapName, ConnectivityTriple ctrip, cv::Vec3f location, int w, int h, std::string MapDescription) :
		MapName(MapName),
		UID(nextUID++),
		ctrip(ctrip), location(location), M(w, h), nextM(w, h),
		MapDescription(MapDescription) {

	}

	SRSUnit::SRSUnit(std::string MapName, ConnectivityTriple ctrip, cv::Vec3f location, int w, int h, int d, std::string MapDescription) :
		MapName(MapName),
		UID(nextUID++),
		ctrip(ctrip), location(location), M(w, h, d), nextM(w, h, d),
		MapDescription(MapDescription) {

	}

	SRSUnit::~SRSUnit() {

	}

	const int SRSUnit::size() {
		return M.size;
	}

	void SRSUnit::PostCreate(Brain& b) {
		nearMaps.clear();
		farMaps.clear();

		std::list<std::shared_ptr<SRSUnit>> nearMapsList;
		std::list<std::shared_ptr<SRSUnit>> farMapsList;

		float near2 = b.maxNearDistance * b.maxNearDistance;
		float far2 = b.minFarDistance * b.minFarDistance;
		for (auto u : b.conceptMaps) {
			cv::Vec3f d = u->location - location;
			const float d2 = d[0] * d[0] + d[1] * d[1] + d[2] * d[2];
			if (u->UID != UID) { 
				if (d2 <= near2) {
					nearMapsList.push_back(u);
				}
				else if (d2 <= far2) {
					farMapsList.push_back(u);
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
		ConceptState::Copy(M, nextM);
	}
}