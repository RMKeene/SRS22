#include "../../SRS22pch.h"
#include "CameraDifferenceMap.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../HardwareIO/CameraInIO.h"
#include "../../HardwareIO/CameraAttnSpotIO.h"
#include "../../OpenCVHelpers.h"

namespace SRS22 {
	CameraDifferenceMap::CameraDifferenceMap(Brain* br) :
		ConceptArray(br, MapUidE::CAMERADIFFERENCE_MAP, "CameraDifferenceMap", true,
			3, CameraInIO::AbsDiffHeight, CameraInIO::AbsDiffWidth, 0.0f,
			"A low resolution version of the camera view processed for frame to frame motion differences.") {
	}

	CameraDifferenceMap::~CameraDifferenceMap() {
	}

	void CameraDifferenceMap::ComputeNextState(boolean doParallel) {
		ConceptArray::ComputeNextState(doParallel);

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		if (cameraIn->currentAbsDifferenceLowRes.empty() == false) {
			std::string ss5 = OpenCVHelpers::CVMatrixInfo(cameraIn->currentAbsDifferenceLowRes);
			cameraIn->currentAbsDifferenceLowRes.copyTo(nextM);
			//imshow("CameraDifferenceMap", cameraIn->currentAbsDifferenceLowRes);
			OpenCVHelpers::ClampMatrix(nextM, 0.0f, 1.0f);
		}
	}

	void CameraDifferenceMap::LatchNewState(boolean doParallel) {
		ConceptArray::LatchNewState(doParallel);
	}
}