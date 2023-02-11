#include "../../pch.h"
#include "ScreenFoveaMap.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../HardwareIO/ScreenInputIO.h"
#include "../../HardwareIO/ScreenAttnSpotIO.h"

namespace SRS22 {
	ScreenFoveaMap::ScreenFoveaMap(Brain* br) :
		ConceptMap(br, MapUidE::SCREENFOVEA_MAP, "ScreenFoveaMap",
			cv::Vec3f(0.0, 0.0, 0.0),
			3, ScreenFoveaMap_Height, ScreenFoveaMap_Width,
			"Raw pixel map of center of screen fovea in color.") {
		SetDecayFactors(false);
	}

	ScreenFoveaMap::~ScreenFoveaMap() {
	}

	void ScreenFoveaMap::ComputeNextState() {
		ConceptMap::ComputeNextState();

		auto screenIn = IOCommon::GetIO<ScreenInputIO>();
		auto fovea = IOCommon::GetIO<ScreenAttnSpotIO>();
		Rect r(Width(), Height(), fovea->GetPt());
		screenIn->GetSubRect(nextM.charges, r);
		//std::string ss = CVMatrixInfo(nextM.charges);
		//ss = CVMatrixInfo(screenIn->currentScreen);
	}

	void ScreenFoveaMap::LatchNewState() {
		ConceptMap::LatchNewState();
	}
}