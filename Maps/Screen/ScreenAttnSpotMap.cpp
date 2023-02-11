#include "../../pch.h"
#include "ScreenAttnSpotMap.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../HardwareIO/ScreenAttnSpotIO.h"
#include "ScreenMotionXYMap.h"
#include "../../Brain.h"

namespace SRS22 {
	ScreenAttnSpotMap::ScreenAttnSpotMap(Brain* br) :
		ConceptMap(br, MapUidE::SCREENATTNSPOT_MAP, "ScreenAttnSpotMap",
			cv::Vec3f(0.0, 0.0, 0.0),
			ScreenAttnSpotMap_Width,
			"Raw pixel map of center of screen fovea in color.") {
		displayMode = SRSUnitDisplayModes::TWOVALUECAMERA;
		SetDecayFactors(false);
	}

	ScreenAttnSpotMap::~ScreenAttnSpotMap() {
	}

	void ScreenAttnSpotMap::ComputeNextState() {
		ConceptMap::ComputeNextState();

		// TODO - Currently hardwired with no blending.
		auto motionXYSptr = myBrain->FindMapByName("ScreenMotionXYMap").value();
		float X = motionXYSptr.get()->M.get(0);
		float Y = motionXYSptr.get()->M.get(1);
		nextM.charges.at<float>(0) = motionXYSptr.get()->M.get(0);
		nextM.charges.at<float>(1) = motionXYSptr.get()->M.get(1);

		auto screenVideo = IOCommon::GetIO<ScreenInputIO>();
		float xx = M.get(0) * screenVideo->GetScreenWidth();
		float yy = M.get(1) * screenVideo->GetScreenHeight();

		auto fovea = IOCommon::GetIO<ScreenAttnSpotIO>();
		fovea->SetPt(xx, yy);
	}

	void ScreenAttnSpotMap::LatchNewState() {
		ConceptMap::LatchNewState();
	}
}