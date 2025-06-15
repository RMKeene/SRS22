#include "../SRS22pch.h"
#include "RandomArray.h"
#include "../HardwareIO/IOCommon.h"
#include "../HardwareIO/ScreenInputIO.h"
#include "../HardwareIO/ScreenAttnSpotIO.h"
#include "../TimeHelpers.h"

namespace SRS22 {
	RandomArray::RandomArray(Brain* br) :
		ConceptArray(br, ArrayUidE::RANDOM_MAP, "RandomArray", NeuronType::IS_INPUT,
			RandomArray_Width, RandomArray_Height, 1.0f,
			"A map that is always randomized every tick. A source of noise if needed.") {
	}

	RandomArray::~RandomArray() {
	}

	void RandomArray::ComputeNextState(boolean doParallel) {
		ConceptArray::ComputeNextState(doParallel);

		cv::setRNGSeed(cv::getTickCount());
		cv::randu(nextM, 0.0f, 1.0f);
	}

	void RandomArray::LatchNewState(boolean doParallel) {
		ConceptArray::LatchNewState(doParallel);
	}
}