#include "../../pch.h"
#include "CameraAttnSpotMap.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../HardwareIO/CameraAttnSpotIO.h"
#include "CameraMotionXYMap.h"
#include "../../Brain.h"

namespace SRS22 {
	CameraAttnSpotMap::CameraAttnSpotMap(Brain* br) :
		ConceptMap(br, MapUidE::CAMERAATTNSPOT_MAP, true, "CameraAttnSpotMap",
			cv::Vec3f(0.0, 0.0, 0.0),
			CameraAttnSpotMap_Width,
			"Raw pixel map of center of camera fovea in color.") {
		displayMode = SRSUnitDisplayModes::TWOVALUECAMERA;
		SetDecayFactors(0.0f);
	}

	CameraAttnSpotMap::~CameraAttnSpotMap() {
	}

	void CameraAttnSpotMap::ComputeNextState() {
		ConceptMap::ComputeNextState();

		auto motionXY = static_cast<CameraMotionXYMap*>(myBrain->FindMapByName("CameraMotionXYMap").value().get());
		float X = motionXY->M.get(0);
		float Y = motionXY->M.get(1);
		nextM.charges.at<float>(0) += motionXY->M.get(0);
		nextM.charges.at<float>(1) += motionXY->M.get(1);

		auto cameraVideo = IOCommon::GetIO<CameraInIO>();
		float xx = M.get(0) * cameraVideo->GetCameraWidth();
		float yy = M.get(1) * cameraVideo->GetCameraHeight();

		auto fovea = IOCommon::GetIO<CameraAttnSpotIO>();
		fovea->SetPt(xx, yy);
	}

	void CameraAttnSpotMap::LatchNewState() {
		ConceptMap::LatchNewState();
	}
}