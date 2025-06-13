#include "../../SRS22pch.h"
#include "CameraFoveaArray.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../HardwareIO/CameraInIO.h"
#include "../../HardwareIO/CameraAttnSpotIO.h"

namespace SRS22 {
	CameraFoveaArray::CameraFoveaArray(Brain* br) :
		ConceptArray(br, ArrayUidE::CAMERAFOVEA_MAP, "CameraFoveaArray", true,
			3, CameraFoveaArray_Height, CameraFoveaArray_Width, 0.0f,
			"Raw pixel map of center of camera fovea in color.") {
	}

	CameraFoveaArray::~CameraFoveaArray() {
	}

	void CameraFoveaArray::ComputeNextState(boolean doParallel) {
		ConceptArray::ComputeNextState(doParallel);

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		cameraIn->fovea.copyTo(nextM);
	}

	void CameraFoveaArray::LatchNewState(boolean doParallel) {
		ConceptArray::LatchNewState(doParallel);
	}
}