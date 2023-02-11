#include "../../pch.h"
#include "TextCurrentCharMap.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../Brain.h"

namespace SRS22 {
	TextCurrentCharMap::TextCurrentCharMap(Brain* br) :
		ConceptMap(br, MapUidE::TEXTCCURRENTCHAR_MAP, "TextCurrentCharMap",
			cv::Vec3f(0.0, 0.0, 0.0),
			TextCurrentCharMap_Width,
			TextCurrentCharMap_Height,
			"Last entered character ASCII Code.") {
		displayMode = SRSUnitDisplayModes::TWOVALUECAMERA;
		SetDecayFactors(true, 0.98f);
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
			nextM.put(1.0f, y, x);
		}
	}

	void TextCurrentCharMap::LatchNewState() {
		ConceptMap::LatchNewState();
	}
}