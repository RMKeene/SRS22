#include "../pch.h"
#include "RandomMap.h"
#include "../HardwareIO/IOCommon.h"
#include "../HardwareIO/ScreenInputIO.h"
#include "../HardwareIO/ScreenAttnSpotIO.h"
#include "../TimeHelpers.h"

namespace SRS22 {

	RandomMap::RandomMap(Brain* br) :
		SRSUnit(br, "RandomMap", 
			ConnectivityTriple(0.1f, 0.1f, 0.8f, 0), 
			cv::Vec3f(0.0, 0.0, 0.0), 
			3, RandomMap_Width, RandomMap_Height,
			"A map that is always randomized every tick. A source of noise if needed.") {
	}

	RandomMap::~RandomMap() {

	}

	void RandomMap::ComputeNextState() {
		SRSUnit::ComputeNextState();

		cv::setRNGSeed(cv::getTickCount());
		cv::randu(nextM.charges, 0.0f, 1.0f);
	}

	void RandomMap::LatchNewState() {
		SRSUnit::LatchNewState();
	}

}
