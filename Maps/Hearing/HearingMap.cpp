#include "../../pch.h"
#include "HearingMap.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../Brain.h"

namespace SRS22 {
	HearingMap::HearingMap(Brain* br) :
		SRSUnit(br, "HearingMap",
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

		//auto phonemesOut = IOCommon::GetIO<PhonemesIO>();
		//
		//int row;
		//int col;
		//int depth;
		//float v;
		//if (M.FindMaxValue(0.25f, col, row, depth, v)) {
		//	nextM.put(0.0f, row, col);
		//	PhonemeE c = (PhonemeE)(col & 0x00FF);
		//	phonemesOut->PlayPhoneme(c);
		//}
	}

	void HearingMap::LatchNewState() {
		SRSUnit::LatchNewState();
	}
}