#include "../../SRS22pch.h"
#include "CameraFoveaArray.h"
#include "CameraFoveaEdgesArray.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../HardwareIO/CameraInIO.h"
#include "../../HardwareIO/CameraAttnSpotIO.h"
#include "../../Brain.h"

namespace SRS22 {
	CameraFoveaEdgesArray::CameraFoveaEdgesArray(Brain* br) :
		ConceptArray(br, ArrayUidE::CAMERAFOVEAEDGE_MAP, "CameraFoveaEdgesArray", true,
			3, CameraFoveaArray_Height, CameraFoveaArray_Width, 0.0f,
			"Camera edges in fovea.") {
	}

	CameraFoveaEdgesArray::~CameraFoveaEdgesArray() {
	}

	void CameraFoveaEdgesArray::ComputeNextState(boolean doParallel) {
		ConceptArray::ComputeNextState(doParallel);

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		cameraIn->foveaEdges.copyTo(nextM);
	}

	void CameraFoveaEdgesArray::LatchNewState(boolean doParallel) {
		ConceptArray::LatchNewState(doParallel);
	}
}