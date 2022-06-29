#include "../pch.h"
#include "CameraDifferenceMap.h"
#include "../HardwareIO/IOCommon.h"
#include "../HardwareIO/CameraInIO.h"
#include "../HardwareIO/CameraAttnSpotIO.h"

namespace SRS22 {

	CameraDifferenceMap::CameraDifferenceMap() :
		SRSUnit("CameraDifferenceMap", 
			ConnectivityTriple(0.10f, 0.75f, 0.15f, 100), 
			cv::Vec3f(0.0, 0.0, 0.0), 
			3, CameraInIO::AbsDiffHeight, CameraInIO::AbsDiffWidth,
			"A low resolution version of the camera view processed for frame to frame motion differences.") {
	}

	CameraDifferenceMap::~CameraDifferenceMap() {

	}

	void CameraDifferenceMap::ComputeNextState() {
		SRSUnit::ComputeNextState();

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		if (cameraIn->currentAbsDifferenceLowRes.empty() == false) {
			cameraIn->currentAbsDifferenceLowRes.copyTo(nextM.charges);
		}
	}

	void CameraDifferenceMap::LatchNewState() {
		SRSUnit::LatchNewState();
	}

}
