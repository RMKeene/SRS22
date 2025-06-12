#include "../../SRS22pch.h"
#include "PhonemeMap.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../Brain.h"
#include "../../SRS22LogTaker.h"

namespace SRS22 {
	PhonemeMap::PhonemeMap(Brain* br) :
		ConceptArray(br, MapUidE::PHONEME_MAP, "PhonemeMap", false,
			PhonemeMap_Width, 0.98f,
			"The \"Voice\" out the audio system.") {
		displayMode = SRSUnitDisplayModes::TWOVALUECAMERA;
	}

	PhonemeMap::~PhonemeMap() {
	}

	void PhonemeMap::ComputeNextState(boolean doParallel) {
		ConceptArray::ComputeNextState(doParallel);

		auto phonemesOut = IOCommon::GetIO<PhonemesIO>();

		int row;
		int col;
		int depth;
		float v;
		if (FindMaxValue(0.25f, col, row, depth, v)) {
			putNext(row, col , -0.25f);
			PhonemeE c = (PhonemeE)(col & 0x00FF);
			SRS22LogTaker::LogInfo("PhonemesMap::ComputeNextState : " + phonemesOut->keyToString(c));
			phonemesOut->PlayPhoneme(c);
		}
	}

	void PhonemeMap::LatchNewState(boolean doParallel) {
		ConceptArray::LatchNewState(doParallel);
	}
}