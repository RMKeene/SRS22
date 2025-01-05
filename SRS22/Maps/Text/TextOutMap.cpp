#include "../../SRS22pch.h"
#include "TextOutMap.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../Brain.h"

namespace SRS22 {
	TextOutMap::TextOutMap(Brain* br) :
		ConceptMap(br, MapUidE::TEXTOUT_MAP, "TextOutMap", false,
			TextOutMap_Width,
			TextOutMap_Height, 0.98f,
			"The \"Keyboard\" out the text window.") {
		displayMode = SRSUnitDisplayModes::TWOVALUECAMERA;
	}

	TextOutMap::~TextOutMap() {
	}

	void TextOutMap::ComputeNextState(boolean doParallel) {
		ConceptMap::ComputeNextState(doParallel);

		auto textOutUI = IOCommon::GetIO<TextOutIO>();

		int row;
		int col;
		int depth;
		float v;
		if (FindMaxValue(0.25f, col, row, depth, v)) {
			putNext(row, col, 0.0f);
			TextIOType c = ((row & 0x00FF) << 8) | (col & 0x00FF);
			textOutUI->TakeCharacter(c);
		}
	}

	void TextOutMap::LatchNewState(boolean doParallel) {
		ConceptMap::LatchNewState(doParallel);
	}
}