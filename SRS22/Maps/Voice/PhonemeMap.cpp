#include "../../SRS22pch.h"
#include "PhonemeMap.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../Brain.h"
#include "../../SRS22LogTaker.h"

namespace SRS22 {
	PhonemeMap::PhonemeMap(Brain* br) :
		ConceptMap(br, MapUidE::PHONEME_MAP, "PhonemeMap",
			PhonemeMap_Width, 0.98f,
			"The \"Voice\" out the audio system.") {
		displayMode = SRSUnitDisplayModes::TWOVALUECAMERA;
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
			nextM.put(-0.25f, row, col);
			PhonemeE c = (PhonemeE)(col & 0x00FF);
			SRS22LogTaker::LogInfo("PhonemesMap::ComputeNextState : " + phonemesOut->keyToString(c));
			phonemesOut->PlayPhoneme(c);
		}
	}

	void PhonemeMap::LatchNewState() {
		ConceptMap::LatchNewState();
	}
}