#include "../../SRS22pch.h"
#include <memory>
#include "CameraAttnSpotMap.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../HardwareIO/CameraAttnSpotIO.h"
#include "CameraMotionXYMap.h"
#include "../../Brain.h"

namespace SRS22 {
	CameraAttnSpotMap::CameraAttnSpotMap(Brain* br) :
		ConceptMap(br, MapUidE::CAMERAATTNSPOT_MAP, "CameraAttnSpotMap", false,
			CameraAttnSpotMap_Width, 0.0f,
			"Output where the camera attantion spot is located.") {
		displayMode = SRSUnitDisplayModes::TWOVALUECAMERA;
	}

	CameraAttnSpotMap::~CameraAttnSpotMap() {
	}

	void CameraAttnSpotMap::ComputeNextState(boolean doParallel) {
		ConceptMap::ComputeNextState(doParallel);

		auto cameraVideo = IOCommon::GetIO<CameraInIO>();
		float xx = M.at<float>(0, 0, 0) * cameraVideo->GetCameraWidth();
		float yy = M.at<float>(0, 0, 1) * cameraVideo->GetCameraHeight();

		auto fovea = IOCommon::GetIO<CameraAttnSpotIO>();
		fovea->SetPt(xx, yy);
	}

	void CameraAttnSpotMap::LatchNewState(boolean doParallel) {
		ConceptMap::LatchNewState(doParallel);
	}
}