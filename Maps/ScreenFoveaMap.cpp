#include "../pch.h"
#include "ScreenFoveaMap.h"
#include "../HardwareIO/IOCommon.h"
#include "../HardwareIO/ScreenInputIO.h"
#include "../HardwareIO/ScreenAttnSpotIO.h"

namespace SRS22 {

	ScreenFoveaMap::ScreenFoveaMap() : 
		SRSUnit("ScreenFoveaMap", 
			ConnectivityTriple(0.10f, 0.75f, 0.15f, 100), 
			cv::Vec3f(0.0, 0.0, 0.0), 
			3, 8, 8, 
			"Raw pixel map of center of screen fovea in color.") {
	}

	ScreenFoveaMap::~ScreenFoveaMap() {

	}

	void ScreenFoveaMap::ComputeNextState() {
		SRSUnit::ComputeNextState();

		auto screenIn = IOCommon::GetIO<ScreenInputIO>();
		auto fovea = IOCommon::GetIO<ScreenAttnSpotIO>();
		screenIn->GetSubRect(nextM.charges, Rect(Width(), Height(), fovea->GetPt()));
		//std::string ss = CVMatrixInfo(nextM.charges);
		//ss = CVMatrixInfo(screenIn->currentScreen);
	}

	void ScreenFoveaMap::LatchNewState() {
		SRSUnit::LatchNewState();
	}

}
