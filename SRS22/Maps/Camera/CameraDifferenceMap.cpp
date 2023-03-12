#include "../../pch.h"
#include "CameraDifferenceMap.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../HardwareIO/CameraInIO.h"
#include "../../HardwareIO/CameraAttnSpotIO.h"

namespace SRS22 {
	CameraDifferenceMap::CameraDifferenceMap(Brain* br) :
		ConceptMap(br, MapUidE::CAMERADIFFERENCE_MAP, false, "CameraDifferenceMap",
			cv::Vec3f(0.0, 0.0, 0.0),
			3, CameraInIO::AbsDiffHeight, CameraInIO::AbsDiffWidth,
			"A low resolution version of the camera view processed for frame to frame motion differences.") {
		SetDecayFactors(false);
	}

	CameraDifferenceMap::~CameraDifferenceMap() {
	}

	void CameraDifferenceMap::ComputeNextState() {
		ConceptMap::ComputeNextState();

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		if (cameraIn->currentAbsDifferenceLowRes.empty() == false) {
			cameraIn->currentAbsDifferenceLowRes.copyTo(nextM.charges);
		}
	}

	void CameraDifferenceMap::LatchNewState() {
		ConceptMap::LatchNewState();
	}
}