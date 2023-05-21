#include "../../pch.h"
#include "PhonemeMap.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../Brain.h"

namespace SRS22 {
	PhonemeMap::PhonemeMap(Brain* br) :
		ConceptMap(br, MapUidE::PHONEME_MAP, true, "PhonemeMap",
			cv::Vec3f(0.0, 0.0, 0.0),
			PhonemeMap_Width,
			"The \"Voice\" out the audio system.") {
		displayMode = SRSUnitDisplayModes::TWOVALUECAMERA;
		SetDecayFactors(0.98f);
	}

	PhonemeMap::~PhonemeMap() {
	}

	void PhonemeMap::ComputeNextState() {
		ConceptMap::ComputeNextState();

		auto phonemesOut = IOCommon::GetIO<PhonemesIO>();

		int row;
		int col;
		int depth;
		float v;
		if (M.FindMaxValue(0.25f, col, row, depth, v)) {
			nextM.put(0.0f, row, col);
			PhonemeE c = (PhonemeE)(col & 0x00FF);
			phonemesOut->PlayPhoneme(c);
		}
	}

	void PhonemeMap::LatchNewState() {
		ConceptMap::LatchNewState();
	}
}