#include "../../SRS22pch.h"
#include <memory>
#include "CameraAttnSpotMap.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../HardwareIO/CameraAttnSpotIO.h"
#include "CameraMotionXYMap.h"
#include "../../Brain.h"

namespace SRS22 {
	CameraAttnSpotMap::CameraAttnSpotMap(Brain* br, bool computeNextStateEnabled) :
		ConceptMap(br, MapUidE::CAMERAATTNSPOT_MAP, "CameraAttnSpotMap", computeNextStateEnabled,
			CameraAttnSpotMap_Width, 0.0f,
			"Raw pixel map of center of camera fovea in color.") {
		displayMode = SRSUnitDisplayModes::TWOVALUECAMERA;
	}

	CameraAttnSpotMap::~CameraAttnSpotMap() {
	}

	void CameraAttnSpotMap::ComputeNextState(boolean doParallel) {
		ConceptMap::ComputeNextState(doParallel);

		auto motionXY = std::dynamic_pointer_cast<CameraMotionXYMap>(myBrain->FindMapByName("CameraMotionXYMap").value());
		float X = motionXY->M.at<float>(0, 0, 0);
		float Y = motionXY->M.at<float>(0, 0, 1);
		nextM.at<float>(0, 0, 0) += motionXY->M.at<float>(0, 0, 0);
		nextM.at<float>(0, 0, 1) += motionXY->M.at<float>(0, 0, 1);

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