#include "../pch.h"
#include "CameraFoveaMap.h"
#include "../HardwareIO/IOCommon.h"
#include "../HardwareIO/CameraInIO.h"
#include "../HardwareIO/CameraAttnSpotIO.h"

namespace SRS22 {

	CameraFoveaMap::CameraFoveaMap() :
		SRSUnit("CameraFoveaMap", 
			ConnectivityTriple(0.10f, 0.75f, 0.15f, 100), 
			cv::Vec3f(0.0, 0.0, 0.0), 
			3, CameraFoveaMap_Height, CameraFoveaMap_Width,
			"Raw pixel map of center of camera fovea in color.") {
	}

	CameraFoveaMap::~CameraFoveaMap() {

	}

	void CameraFoveaMap::ComputeNextState() {
		SRSUnit::ComputeNextState();

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		auto fovea = IOCommon::GetIO<CameraAttnSpotIO>();
		Point pp = fovea->GetPt();
		Rect r(Width(), Height(), fovea->GetPt());
		cameraIn->GetSubRect(nextM.charges, r);
		//std::string ss = CVMatrixInfo(nextM.charges);
		//ss = CVMatrixInfo(cameraIn->currentScreen);
	}

	void CameraFoveaMap::LatchNewState() {
		SRSUnit::LatchNewState();
	}

}
