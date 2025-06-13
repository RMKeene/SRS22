#include "../../../SRS22pch.h"
#include "HearingArray.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../Brain.h"
#include "../../ConceptArray.h"

namespace SRS22 {
	HearingArray::HearingArray(Brain* br) :
		ConceptArray(br, ArrayUidE::HEARING_MAP, "HearingArray", true,
			HearingArray_Width, 0.98f,
			"The \"Hearing\" input from the audio system.") {
		displayMode = SRSUnitDisplayModes::GRAY;
	}

	HearingArray::~HearingArray() {
	}

	void HearingArray::ComputeNextState(boolean doParallel) {
		ConceptArray::ComputeNextState(doParallel);

		auto waveIn = IOCommon::GetIO<AudioCaptureIO>();
		for (int i = 0; i < SRS22FFTRESULTSIZE; i++) {
			putNext(i, waveIn->inputHelper.frequencyAmplitudes[i]);
		}
	}

	void HearingArray::LatchNewState(boolean doParallel) {
		ConceptArray::LatchNewState(doParallel);
	}
}