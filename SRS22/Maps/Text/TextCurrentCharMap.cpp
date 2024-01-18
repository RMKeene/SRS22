#include "../../pch.h"
#include "TextCurrentCharMap.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../Brain.h"

namespace SRS22 {
	TextCurrentCharMap::TextCurrentCharMap(Brain* br) :
		ConceptMap(br, MapUidE::TEXTCCURRENTCHAR_MAP, "TextCurrentCharMap",
			TextCurrentCharMap_Width,
			TextCurrentCharMap_Height, 0.98f,
			"Last entered character ASCII Code.") {
		displayMode = SRSUnitDisplayModes::TWOVALUECAMERA;
	}

	TextCurrentCharMap::~TextCurrentCharMap() {
	}

	void TextCurrentCharMap::ComputeNextState() {
		ConceptMap::ComputeNextState();

		auto textInUI = IOCommon::GetIO<TextInIO>();
		TextIOType c;
		if (textInUI->GetCharacterIn(c)) {
			uint x = c & 0x000F;
			uint y = (c >> 4) & 0x000F;
			nextM.put(nextM.get(y, x) + 1.0f, y, x);
		}
	}

	void TextCurrentCharMap::LatchNewState() {
		ConceptMap::LatchNewState();
	}
}