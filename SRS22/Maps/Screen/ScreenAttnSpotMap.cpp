#include "../../SRS22pch.h"
#include "ScreenAttnSpotMap.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../HardwareIO/ScreenAttnSpotIO.h"
#include "ScreenMotionXYMap.h"
#include "../../Brain.h"

namespace SRS22 {
	ScreenAttnSpotMap::ScreenAttnSpotMap(Brain* br, bool computeNextStateEnabled) :
		ConceptMap(br, MapUidE::SCREENATTNSPOT_MAP, "ScreenAttnSpotMap", computeNextStateEnabled,
			ScreenAttnSpotMap_Width, 0.0f,
			"Raw pixel map of center of screen fovea in color.") {
		displayMode = SRSUnitDisplayModes::TWOVALUECAMERA;
	}

	ScreenAttnSpotMap::~ScreenAttnSpotMap() {
	}

	void ScreenAttnSpotMap::ComputeNextState(boolean doParallel) {
		ConceptMap::ComputeNextState(doParallel);

		auto screenVideo = IOCommon::GetIO<ScreenInputIO>();
		float xx = get(0) * screenVideo->GetScreenWidth();
		float yy = get(1) * screenVideo->GetScreenHeight();

		auto fovea = IOCommon::GetIO<ScreenAttnSpotIO>();
		fovea->SetPt(xx, yy);
	}

	void ScreenAttnSpotMap::LatchNewState(boolean doParallel) {
		ConceptMap::LatchNewState(doParallel);
	}
}