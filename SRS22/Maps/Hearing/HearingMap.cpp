#include "../../../SRS22pch.h"
#include "HearingMap.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../Brain.h"
#include "../../ConceptMap.h"

namespace SRS22 {
	HearingMap::HearingMap(Brain* br, bool computeNextStateEnabled) :
		ConceptMap(br, MapUidE::HEARING_MAP, "HearingMap", computeNextStateEnabled,
			HearingMap_Width, 0.98f,
			"The \"Hearing\" input from the audio system.") {
		displayMode = SRSUnitDisplayModes::GRAY;
	}

	HearingMap::~HearingMap() {
	}

	void HearingMap::ComputeNextState(boolean doParallel) {
		ConceptMap::ComputeNextState(doParallel);

		auto waveIn = IOCommon::GetIO<AudioCaptureIO>();
		for (int i = 0; i < SRS22FFTRESULTSIZE; i++) {
			addNext(i, waveIn->inputHelper.frequencyAmplitudes[i]);
		}
	}

	void HearingMap::LatchNewState(boolean doParallel) {
		ConceptMap::LatchNewState(doParallel);
	}
}