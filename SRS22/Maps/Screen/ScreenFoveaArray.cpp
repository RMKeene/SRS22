#include "../../SRS22pch.h"
#include "ScreenFoveaArray.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../HardwareIO/ScreenInputIO.h"
#include "../../HardwareIO/ScreenAttnSpotIO.h"

namespace SRS22 {
	ScreenFoveaArray::ScreenFoveaArray(Brain* br) :
		ConceptArray(br, ArrayUidE::SCREENFOVEA_MAP, "ScreenFoveaArray", true,
			3, ScreenFoveaArray_Height, ScreenFoveaArray_Width, 0.0f,
			"Raw pixel map of center of screen fovea in color.") {
	}

	ScreenFoveaArray::~ScreenFoveaArray() {
	}

	void ScreenFoveaArray::ComputeNextState(boolean doParallel) {
		ConceptArray::ComputeNextState(doParallel);

		auto screenIn = IOCommon::GetIO<ScreenInputIO>();
		auto fovea = IOCommon::GetIO<ScreenAttnSpotIO>();
		Rect r(Width(), Height(), fovea->GetPt());
		screenIn->GetSubRect(nextM, r);
	}

	void ScreenFoveaArray::LatchNewState(boolean doParallel) {
		ConceptArray::LatchNewState(doParallel);
	}
}