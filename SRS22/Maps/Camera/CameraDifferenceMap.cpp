#include "../../pch.h"
#include "CameraDifferenceMap.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../HardwareIO/CameraInIO.h"
#include "../../HardwareIO/CameraAttnSpotIO.h"

namespace SRS22 {
	CameraDifferenceMap::CameraDifferenceMap(Brain* br) :
		ConceptMap(br, MapUidE::CAMERADIFFERENCE_MAP, "CameraDifferenceMap",
			3, CameraInIO::AbsDiffHeight, CameraInIO::AbsDiffWidth, 0.0f,
			"A low resolution version of the camera view processed for frame to frame motion differences.") {
	}

	CameraDifferenceMap::~CameraDifferenceMap() {
	}

	void CameraDifferenceMap::ComputeNextState() {
		ConceptMap::ComputeNextState();

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		if (cameraIn->currentAbsDifferenceLowRes.empty() == false) {
			nextM.charges += cameraIn->currentAbsDifferenceLowRes;
		}
	}

	void CameraDifferenceMap::LatchNewState() {
		ConceptMap::LatchNewState();
	}
}