#include "../../pch.h"
#include "ScreenAttnSpotMap.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../HardwareIO/ScreenAttnSpotIO.h"
#include "ScreenMotionXYMap.h"
#include "../../Brain.h"

namespace SRS22 {
	ScreenAttnSpotMap::ScreenAttnSpotMap(Brain* br) :
		SRSUnit(br, "ScreenAttnSpotMap",
			ConnectivityTriple(0.10f, 0.75f, 0.15f, 100),
			cv::Vec3f(0.0, 0.0, 0.0),
			ScreenAttnSpotMap_Width,
			"Raw pixel map of center of screen fovea in color.") {
		displayMode = SRSUnitDisplayModes::TWOVALUECAMERA;
	}

	ScreenAttnSpotMap::~ScreenAttnSpotMap() {
	}

	void ScreenAttnSpotMap::ComputeNextState() {
		SRSUnit::ComputeNextState();

		// TODO - Currently hardwired with no blending.
		auto motionXY = static_cast<ScreenMotionXYMap*>(myBrain->FindMapByName("ScreenMotionXYMap").value().get());
		float X = motionXY->M.get(0);
		float Y = motionXY->M.get(1);
		nextM.charges.at<float>(0) = motionXY->M.get(0);
		nextM.charges.at<float>(1) = motionXY->M.get(1);

		auto screenVideo = IOCommon::GetIO<ScreenInputIO>();
		float xx = M.get(0) * screenVideo->GetScreenWidth();
		float yy = M.get(1) * screenVideo->GetScreenHeight();

		auto fovea = IOCommon::GetIO<ScreenAttnSpotIO>();
		fovea->SetPt(xx, yy);
	}

	void ScreenAttnSpotMap::LatchNewState() {
		SRSUnit::LatchNewState();
	}
}