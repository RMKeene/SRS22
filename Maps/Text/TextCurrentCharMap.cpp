#include "../../pch.h"
#include "TextCurrentCharMap.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../Brain.h"

namespace SRS22 {
	TextCurrentCharMap::TextCurrentCharMap(Brain* br) :
		SRSUnit(br, "TextCurrentCharMap",
			ConnectivityTriple(0.10f, 0.75f, 0.15f, 100),
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
		SRSUnit::ComputeNextState();

		auto textInUI = IOCommon::GetIO<TextInIO>();
		TextIOType c;
		if (textInUI->GetCharacterIn(c)) {
			uint x = c & 0x000F;
			uint y = (c >> 4) & 0x000F;
			nextM.put(1.0f, y, x);
		}
	}

	void TextCurrentCharMap::LatchNewState() {
		SRSUnit::LatchNewState();
	}
}