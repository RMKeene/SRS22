#include "../../SRS22pch.h"
#include "PhonemeArray.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../Brain.h"
#include "../../SRS22LogTaker.h"

namespace SRS22 {
	PhonemeArray::PhonemeArray(Brain* br) :
		ConceptArray(br, ArrayUidE::PHONEME_MAP, "PhonemeArray", false,
			PhonemeArray_Width, 0.98f,
			"The \"Voice\" out the audio system.") {
		displayMode = SRSUnitDisplayModes::TWOVALUECAMERA;
	}

	PhonemeArray::~PhonemeArray() {
	}

	void PhonemeArray::ComputeNextState(boolean doParallel) {
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

	void PhonemeArray::LatchNewState(boolean doParallel) {
		ConceptArray::LatchNewState(doParallel);
	}
}