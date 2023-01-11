#include "../../pch.h"
#include "HearingMap.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../Brain.h"

namespace SRS22 {
	HearingMap::HearingMap(Brain* br) :
		SRSUnit(br, MapUidE::HEARING_MAP, "HearingMap",
			ConnectivityTriple(0.10f, 0.75f, 0.15f, 100),
			cv::Vec3f(0.0, 0.0, 0.0),
			HearingMap_Width,
			"The \"Hearing\" input from the audio system.") {
		displayMode = SRSUnitDisplayModes::GRAY;
		SetDecayFactors(true, 0.98f);
	}

	HearingMap::~HearingMap() {
	}

	void HearingMap::ComputeNextState() {
		SRSUnit::ComputeNextState();

		auto waveIn = IOCommon::GetIO<AudioCaptureIO>();
		for (int i = 0; i < SRS22FFTRESULTSIZE; i++) {
			nextM.put(waveIn->inputHelper.frequencyAmplitudes[i], i);
		}
	}

	void HearingMap::LatchNewState() {
		SRSUnit::LatchNewState();
	}
}