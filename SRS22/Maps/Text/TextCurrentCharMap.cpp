#include "../../SRS22pch.h"
#include "TextCurrentCharMap.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../Brain.h"

namespace SRS22 {
	TextCurrentCharMap::TextCurrentCharMap(Brain* br) :
		ConceptArray(br, MapUidE::TEXTCCURRENTCHAR_MAP, "TextCurrentCharMap", true,
			TextCurrentCharMap_Width,
			TextCurrentCharMap_Height, 0.98f,
			"Last entered character ASCII Code.") {
		displayMode = SRSUnitDisplayModes::TWOVALUECAMERA;
	}

	TextCurrentCharMap::~TextCurrentCharMap() {
	}

	void TextCurrentCharMap::ComputeNextState(boolean doParallel) {
		ConceptArray::ComputeNextState(doParallel);

		RelaxTowardZero(0.9f);

		auto textInUI = IOCommon::GetIO<TextInIO>();
		TextIOType c;
		if (textInUI->GetCharacterIn(c)) {
			uint x = c & 0x000F;
			uint y = (c >> 4) & 0x000F;
			putNext(y, x, 1.0f);
		}
	}

	void TextCurrentCharMap::LatchNewState(boolean doParallel) {
		ConceptArray::LatchNewState(doParallel);
	}
}