#include "../pch.h"
#include "ScreenFoveaMap.h"
#include "../HardwareIO/IOCommon.h"
#include "../HardwareIO/ScreenInputIO.h"
#include "../HardwareIO/ScreenAttnSpotIO.h"

namespace SRS22 {

	ScreenFoveaMap::ScreenFoveaMap() : 
		SRSUnit("ScreenFoveaMap", 
			ConnectivityTriple(0.10, 0.75, 0.15, 100), 
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

		cv::Mat screen;
		if (!screenIn->IsCorrectSize(screen))
			screen = screenIn->GetCorrectSizeMat();
		screenIn->GetCurrentScreen(screen);
		screenIn->GetSubRect(nextM.charges, fovea->GetRect());
	}

	void ScreenFoveaMap::LatchNewState() {
		SRSUnit::LatchNewState();

	}

}
