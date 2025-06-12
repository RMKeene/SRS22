#include "../../SRS22pch.h"
#include "ScreenFoveaMap.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../HardwareIO/ScreenInputIO.h"
#include "../../HardwareIO/ScreenAttnSpotIO.h"

namespace SRS22 {
	ScreenFoveaMap::ScreenFoveaMap(Brain* br) :
		ConceptArray(br, MapUidE::SCREENFOVEA_MAP, "ScreenFoveaMap", true,
			3, ScreenFoveaMap_Height, ScreenFoveaMap_Width, 0.0f,
			"Raw pixel map of center of screen fovea in color.") {
	}

	ScreenFoveaMap::~ScreenFoveaMap() {
	}

	void ScreenFoveaMap::ComputeNextState(boolean doParallel) {
		ConceptArray::ComputeNextState(doParallel);

		auto screenIn = IOCommon::GetIO<ScreenInputIO>();
		auto fovea = IOCommon::GetIO<ScreenAttnSpotIO>();
		Rect r(Width(), Height(), fovea->GetPt());
		screenIn->GetSubRect(nextM, r);
	}

	void ScreenFoveaMap::LatchNewState(boolean doParallel) {
		ConceptArray::LatchNewState(doParallel);
	}
}