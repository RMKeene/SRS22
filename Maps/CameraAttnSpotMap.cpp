#include "../pch.h"
#include "CameraAttnSpotMap.h"
#include "../HardwareIO/IOCommon.h"
#include "../HardwareIO/CameraAttnSpotIO.h"

namespace SRS22 {

	CameraAttnSpotMap::CameraAttnSpotMap() :
		SRSUnit("CameraAttnSpotMap",
			ConnectivityTriple(0.10f, 0.75f, 0.15f, 100),
			cv::Vec3f(0.0, 0.0, 0.0),
			CameraAttnSpotMap_Width,
			"Raw pixel map of center of camera fovea in color.") {
	}

	CameraAttnSpotMap::~CameraAttnSpotMap() {

	}

	void CameraAttnSpotMap::ComputeNextState() {
		SRSUnit::ComputeNextState();

		auto fovea = IOCommon::GetIO<CameraAttnSpotIO>();
		fovea->SetPt(
			M.get(0) * fovea->GetRect().width,
			M.get(1) * fovea->GetRect().height);
	}

	void CameraAttnSpotMap::LatchNewState() {
		SRSUnit::LatchNewState();
	}

}
