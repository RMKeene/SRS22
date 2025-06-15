#include "../../SRS22pch.h"
#include "ScreenAttnSpotArray.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../HardwareIO/ScreenAttnSpotIO.h"
#include "ScreenMotionXYArray.h"
#include "../../Brain.h"

namespace SRS22 {
	ScreenAttnSpotArray::ScreenAttnSpotArray(Brain* br) :
		ConceptArray(br, ArrayUidE::SCREENATTNSPOT_MAP, "ScreenAttnSpotArray", NeuronType::IS_OUTPUT,
			ScreenAttnSpotArray_Width, 0.0f,
			"Output where the screen attention spot is located.") {
		displayMode = SRSUnitDisplayModes::TWOVALUECAMERA;
	}

	ScreenAttnSpotArray::~ScreenAttnSpotArray() {
	}

	void ScreenAttnSpotArray::ComputeNextState(boolean doParallel) {
		ConceptArray::ComputeNextState(doParallel);

		auto screenVideo = IOCommon::GetIO<ScreenInputIO>();
		float xx = get(0) * screenVideo->GetScreenWidth();
		float yy = get(1) * screenVideo->GetScreenHeight();

		auto fovea = IOCommon::GetIO<ScreenAttnSpotIO>();
		fovea->SetPt(xx, yy);
	}

	void ScreenAttnSpotArray::LatchNewState(boolean doParallel) {
		ConceptArray::LatchNewState(doParallel);
	}
}