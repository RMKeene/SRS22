#include "../SRS22pch.h"
#include "RandomMap.h"
#include "../HardwareIO/IOCommon.h"
#include "../HardwareIO/ScreenInputIO.h"
#include "../HardwareIO/ScreenAttnSpotIO.h"
#include "../TimeHelpers.h"

namespace SRS22 {
	RandomMap::RandomMap(Brain* br, bool computeNextStateEnabled) :
		ConceptMap(br, MapUidE::RANDOM_MAP, "RandomMap", computeNextStateEnabled,
			RandomMap_Width, RandomMap_Height, 1.0f,
			"A map that is always randomized every tick. A source of noise if needed.") {
	}

	RandomMap::~RandomMap() {
	}

	void RandomMap::ComputeNextState(boolean doParallel) {
		ConceptMap::ComputeNextState(doParallel);

		cv::setRNGSeed(cv::getTickCount());
		cv::randu(nextM, 0.0f, 1.0f);
	}

	void RandomMap::LatchNewState(boolean doParallel) {
		ConceptMap::LatchNewState(doParallel);
	}
}