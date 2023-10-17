#include "../../pch.h"
#include "CameraFoveaMap.h"
#include "CameraFoveaAngleMap.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../HardwareIO/CameraInIO.h"
#include "../../HardwareIO/CameraAttnSpotIO.h"
#include "../../Brain.h"

namespace SRS22 {
	CameraFoveaAngleMap::CameraFoveaAngleMap(Brain* br) :
		ConceptMap(br, MapUidE::CAMERAFOVEAANGLE_MAP, false, "CameraFoveaAngleMap",
			cv::Vec3f(0.0, 0.0, 0.0),
			3, CameraFoveaMap_Height, CameraFoveaMap_Width, 0.0f,
			"Camera fovea center edge angles.") {
	}

	CameraFoveaAngleMap::~CameraFoveaAngleMap() {
	}

	void CameraFoveaAngleMap::ComputeNextState() {
		ConceptMap::ComputeNextState();

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		cameraIn->foveaAngles.copyTo(nextM.charges);
	}

	void CameraFoveaAngleMap::LatchNewState() {
		ConceptMap::LatchNewState();
	}
}