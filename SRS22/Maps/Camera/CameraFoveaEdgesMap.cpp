#include "../../pch.h"
#include "CameraFoveaMap.h"
#include "CameraFoveaEdgesMap.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../HardwareIO/CameraInIO.h"
#include "../../HardwareIO/CameraAttnSpotIO.h"
#include "../../Brain.h"

namespace SRS22 {
	CameraFoveaEdgesMap::CameraFoveaEdgesMap(Brain* br) :
		ConceptMap(br, MapUidE::CAMERAFOVEAANGLE_MAP, false, "CameraEdgesMap",
			cv::Vec3f(0.0, 0.0, 0.0),
			3, CameraFoveaMap_Height, CameraFoveaMap_Width, 0.0f,
			"Camera edges in fovea.") {
	}

	CameraFoveaEdgesMap::~CameraFoveaEdgesMap() {
	}

	void CameraFoveaEdgesMap::ComputeNextState() {
		ConceptMap::ComputeNextState();

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		cameraIn->foveaEdges.copyTo(nextM.charges);
	}

	void CameraFoveaEdgesMap::LatchNewState() {
		ConceptMap::LatchNewState();
	}
}