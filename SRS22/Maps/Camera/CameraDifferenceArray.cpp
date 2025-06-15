#include "../../SRS22pch.h"
#include "CameraDifferenceArray.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../HardwareIO/CameraInIO.h"
#include "../../HardwareIO/CameraAttnSpotIO.h"
#include "../../OpenCVHelpers.h"

namespace SRS22 {
	CameraDifferenceArray::CameraDifferenceArray(Brain* br) :
		ConceptArray(br, ArrayUidE::CAMERADIFFERENCE_MAP, "CameraDifferenceArray", NeuronType::IS_INPUT,
			3, CameraInIO::AbsDiffHeight, CameraInIO::AbsDiffWidth, 0.0f,
			"A low resolution version of the camera view processed for frame to frame motion differences.") {
	}

	CameraDifferenceArray::~CameraDifferenceArray() {
	}

	void CameraDifferenceArray::ComputeNextState(boolean doParallel) {
		ConceptArray::ComputeNextState(doParallel);

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		if (cameraIn->currentAbsDifferenceLowRes.empty() == false) {
			std::string ss5 = OpenCVHelpers::CVMatrixInfo(cameraIn->currentAbsDifferenceLowRes);
			cameraIn->currentAbsDifferenceLowRes.copyTo(nextM);
			//imshow("CameraDifferenceArray", cameraIn->currentAbsDifferenceLowRes);
			OpenCVHelpers::ClampMatrix(nextM, 0.0f, 1.0f);
		}
	}

	void CameraDifferenceArray::LatchNewState(boolean doParallel) {
		ConceptArray::LatchNewState(doParallel);
	}
}