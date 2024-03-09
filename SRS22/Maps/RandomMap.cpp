#include "../SRS22pch.h"
#include "RandomMap.h"
#include "../HardwareIO/IOCommon.h"
#include "../HardwareIO/ScreenInputIO.h"
#include "../HardwareIO/ScreenAttnSpotIO.h"
#include "../TimeHelpers.h"

namespace SRS22 {
	RandomMap::RandomMap(Brain* br) :
		ConceptMap(br, MapUidE::RANDOM_MAP, "RandomMap",
			RandomMap_Width, RandomMap_Height, 1.0f,
			"A map that is always randomized every tick. A source of noise if needed.") {
	}

	RandomMap::~RandomMap() {
	}

	void RandomMap::ComputeNextState() {
		ConceptMap::ComputeNextState();

		cv::setRNGSeed(cv::getTickCount());
		cv::randu(nextM, 0.0f, 1.0f);
	}

	void RandomMap::LatchNewState() {
		ConceptMap::LatchNewState();
	}
}