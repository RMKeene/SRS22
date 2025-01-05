#include "../../SRS22pch.h"
#include "CameraFoveaMap.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../HardwareIO/CameraInIO.h"
#include "../../HardwareIO/CameraAttnSpotIO.h"

namespace SRS22 {
	CameraFoveaMap::CameraFoveaMap(Brain* br) :
		ConceptMap(br, MapUidE::CAMERAFOVEA_MAP, "CameraFoveaMap", true,
			3, CameraFoveaMap_Height, CameraFoveaMap_Width, 0.0f,
			"Raw pixel map of center of camera fovea in color.") {
	}

	CameraFoveaMap::~CameraFoveaMap() {
	}

	void CameraFoveaMap::ComputeNextState(boolean doParallel) {
		ConceptMap::ComputeNextState(doParallel);

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		cameraIn->fovea.copyTo(nextM);
	}

	void CameraFoveaMap::LatchNewState(boolean doParallel) {
		ConceptMap::LatchNewState(doParallel);
	}
}