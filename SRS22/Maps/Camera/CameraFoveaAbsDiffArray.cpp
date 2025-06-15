#include "../../SRS22pch.h"
#include "../../OpenCVHelpers.h"
#include "CameraFoveaAbsDiffArray.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../HardwareIO/CameraInIO.h"
#include "CameraFoveaArray.h"

namespace SRS22 {
	CameraFoveaAbsDiffArray::CameraFoveaAbsDiffArray(Brain* br) :
		ConceptArray(br, ArrayUidE::FOVEAABSDIFF_MAP, "CameraFoveaAbsDiffArray", NeuronType::IS_INPUT,
			3, CameraFoveaArray_Height, CameraFoveaArray_Height, 0.0f,
			"The attention spot of the fovea, diff since last frame.") {
	}

	CameraFoveaAbsDiffArray::~CameraFoveaAbsDiffArray() {
	}

	void CameraFoveaAbsDiffArray::ComputeNextState(boolean doParallel) {
		ConceptArray::ComputeNextState(doParallel);

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		if (cameraIn->foveaAbsDifference.empty() == false) {
			string ss5 = OpenCVHelpers::CVMatrixInfo(cameraIn->foveaAbsDifference);
			string ss6 = OpenCVHelpers::CVMatrixInfo(nextM);
			cameraIn->foveaAbsDifference.copyTo(nextM);
			OpenCVHelpers::ClampMatrix(nextM, 0.0f, 1.0f);
		}
	}

	void CameraFoveaAbsDiffArray::LatchNewState(boolean doParallel) {
		ConceptArray::LatchNewState(doParallel);
	}
}