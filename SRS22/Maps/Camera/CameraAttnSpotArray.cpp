#include "../../SRS22pch.h"
#include <memory>
#include "CameraAttnSpotArray.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../HardwareIO/CameraAttnSpotIO.h"
#include "CameraMotionXYArray.h"
#include "../../Brain.h"

namespace SRS22 {
	CameraAttnSpotArray::CameraAttnSpotArray(Brain* br) :
		ConceptArray(br, ArrayUidE::CAMERAATTNSPOT_MAP, "CameraAttnSpotArray", false,
			CameraAttnSpotArray_Width, 0.0f,
			"Output where the camera attantion spot is located.") {
		displayMode = SRSUnitDisplayModes::TWOVALUECAMERA;
	}

	CameraAttnSpotArray::~CameraAttnSpotArray() {
	}

	void CameraAttnSpotArray::ComputeNextState(boolean doParallel) {
		ConceptArray::ComputeNextState(doParallel);

		auto cameraVideo = IOCommon::GetIO<CameraInIO>();
		float xx = M.at<float>(0, 0, 0) * cameraVideo->GetCameraWidth();
		float yy = M.at<float>(0, 0, 1) * cameraVideo->GetCameraHeight();

		auto fovea = IOCommon::GetIO<CameraAttnSpotIO>();
		fovea->SetPt(xx, yy);
	}

	void CameraAttnSpotArray::LatchNewState(boolean doParallel) {
		ConceptArray::LatchNewState(doParallel);
	}
}