#include "../../SRS22pch.h"
#include "CameraFoveaAbsDiffMap.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../HardwareIO/CameraInIO.h"
#include "CameraFoveaMap.h"

namespace SRS22 {
	CameraFoveaAbsDiffMap::CameraFoveaAbsDiffMap(Brain* br) :
		ConceptMap(br, MapUidE::FOVEAABSDIFF_MAP, "CameraFoveaAbsDiffMap",
			3, CameraFoveaMap_Height, CameraFoveaMap_Height, 0.0f,
			"The attention spot of the fovea, diff since last frame.") {
	}

	CameraFoveaAbsDiffMap::~CameraFoveaAbsDiffMap() {
	}

	void CameraFoveaAbsDiffMap::ComputeNextState(boolean doParallel) {
		ConceptMap::ComputeNextState(doParallel);

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		if (cameraIn->foveaAbsDifference.empty() == false) {
			nextM += cameraIn->foveaAbsDifference;
		}
	}

	void CameraFoveaAbsDiffMap::LatchNewState(boolean doParallel) {
		ConceptMap::LatchNewState(doParallel);
	}
}