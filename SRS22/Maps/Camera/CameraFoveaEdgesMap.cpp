#include "../../SRS22pch.h"
#include "CameraFoveaMap.h"
#include "CameraFoveaEdgesMap.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../HardwareIO/CameraInIO.h"
#include "../../HardwareIO/CameraAttnSpotIO.h"
#include "../../Brain.h"

namespace SRS22 {
	CameraFoveaEdgesMap::CameraFoveaEdgesMap(Brain* br) :
		ConceptArray(br, MapUidE::CAMERAFOVEAEDGE_MAP, "CameraFoveaEdgesMap", true,
			3, CameraFoveaMap_Height, CameraFoveaMap_Width, 0.0f,
			"Camera edges in fovea.") {
	}

	CameraFoveaEdgesMap::~CameraFoveaEdgesMap() {
	}

	void CameraFoveaEdgesMap::ComputeNextState(boolean doParallel) {
		ConceptArray::ComputeNextState(doParallel);

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		cameraIn->foveaEdges.copyTo(nextM);
	}

	void CameraFoveaEdgesMap::LatchNewState(boolean doParallel) {
		ConceptArray::LatchNewState(doParallel);
	}
}