#include "../../pch.h"
#include "CameraFoveaMap.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../HardwareIO/CameraInIO.h"
#include "../../HardwareIO/CameraAttnSpotIO.h"

namespace SRS22 {
	CameraFoveaMap::CameraFoveaMap(Brain* br) :
		ConceptMap(br, MapUidE::CAMERAFOVEA_MAP, false, "CameraFoveaMap",
			cv::Vec3f(0.0, 0.0, 0.0),
			3, CameraFoveaMap_Height, CameraFoveaMap_Width, 0.0f,
			"Raw pixel map of center of camera fovea in color.") {
	}

	CameraFoveaMap::~CameraFoveaMap() {
	}

	void CameraFoveaMap::ComputeNextState() {
		ConceptMap::ComputeNextState();

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		auto fovea = IOCommon::GetIO<CameraAttnSpotIO>();
		Rect r(Width(), Height(), fovea->GetPt());
		nextM.charges = cameraIn->fovea.clone();
	}

	void CameraFoveaMap::LatchNewState() {
		ConceptMap::LatchNewState();
	}
}