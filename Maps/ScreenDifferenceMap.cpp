#include "../pch.h"
#include "ScreenDifferenceMap.h"
#include "../HardwareIO/IOCommon.h"
#include "../HardwareIO/ScreenInputIO.h"
#include "../HardwareIO/ScreenAttnSpotIO.h"

namespace SRS22 {

	ScreenDifferenceMap::ScreenDifferenceMap(Brain* br) :
		SRSUnit(br, "ScreenDifferenceMap",
			ConnectivityTriple(0.10f, 0.75f, 0.15f, 100),
			cv::Vec3f(0.0, 0.0, 0.0),
			3, ScreenInputIO::AbsDiffHeight, ScreenInputIO::AbsDiffWidth,
			"A low resolution version of the screen view processed for frame to frame motion differences.") {
	}

	ScreenDifferenceMap::~ScreenDifferenceMap() {

	}

	void ScreenDifferenceMap::ComputeNextState() {
		SRSUnit::ComputeNextState();

		auto screenIn = IOCommon::GetIO<ScreenInputIO>();
		if (screenIn->currentAbsDifferenceLowRes.empty() == false) {
			screenIn->currentAbsDifferenceLowRes.copyTo(nextM.charges);
		}
	}

	void ScreenDifferenceMap::LatchNewState() {
		SRSUnit::LatchNewState();
	}

}
