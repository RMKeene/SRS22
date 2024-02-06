#include "../../SRS22pch.h"
#include "CameraFoveaMap.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../HardwareIO/CameraInIO.h"
#include "../../HardwareIO/CameraAttnSpotIO.h"

namespace SRS22 {
	CameraFoveaMap::CameraFoveaMap(Brain* br) :
		ConceptMap(br, MapUidE::CAMERAFOVEA_MAP, "CameraFoveaMap",
			3, CameraFoveaMap_Height, CameraFoveaMap_Width, 0.0f,
			"Raw pixel map of center of camera fovea in color.") {
	}

	CameraFoveaMap::~CameraFoveaMap() {
	}

	void CameraFoveaMap::ComputeNextState() {
		ConceptMap::ComputeNextState();

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		nextM = cameraIn->fovea.clone();
	}

	void CameraFoveaMap::LatchNewState() {
		ConceptMap::LatchNewState();
	}
}