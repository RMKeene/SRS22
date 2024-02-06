#include "../../SRS22pch.h"
#include "ScreenAttnSpotMap.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../HardwareIO/ScreenAttnSpotIO.h"
#include "ScreenMotionXYMap.h"
#include "../../Brain.h"

namespace SRS22 {
	ScreenAttnSpotMap::ScreenAttnSpotMap(Brain* br) :
		ConceptMap(br, MapUidE::SCREENATTNSPOT_MAP, "ScreenAttnSpotMap",
			ScreenAttnSpotMap_Width, 0.0f,
			"Raw pixel map of center of screen fovea in color.") {
		displayMode = SRSUnitDisplayModes::TWOVALUECAMERA;
	}

	ScreenAttnSpotMap::~ScreenAttnSpotMap() {
	}

	void ScreenAttnSpotMap::ComputeNextState() {
		ConceptMap::ComputeNextState();

		// TODO - Currently hardwired with no blending.
		auto motionXYSptr = myBrain->FindMapByName("ScreenMotionXYMap").value();
		float X = motionXYSptr.get()->get(0);
		float Y = motionXYSptr.get()->get(1);
		nextM.at<float>(0) += motionXYSptr.get()->get(0);
		nextM.at<float>(1) += motionXYSptr.get()->get(1);

		auto screenVideo = IOCommon::GetIO<ScreenInputIO>();
		float xx = get(0) * screenVideo->GetScreenWidth();
		float yy = get(1) * screenVideo->GetScreenHeight();

		auto fovea = IOCommon::GetIO<ScreenAttnSpotIO>();
		fovea->SetPt(xx, yy);
	}

	void ScreenAttnSpotMap::LatchNewState() {
		ConceptMap::LatchNewState();
	}
}