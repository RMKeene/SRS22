#include "../../SRS22pch.h"
#include "TextOutArray.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../Brain.h"

namespace SRS22 {
	TextOutArray::TextOutArray(Brain* br) :
		ConceptArray(br, ArrayUidE::TEXTOUT_MAP, "TextOutArray", NeuronType::IS_OUTPUT,
			TextOutArray_Width,
			TextOutArray_Height, 0.98f,
			"The \"Keyboard\" out the text window.") {
		displayMode = SRSUnitDisplayModes::TWOVALUECAMERA;
	}

	TextOutArray::~TextOutArray() {
	}

	void TextOutArray::ComputeNextState(boolean doParallel) {
		ConceptArray::ComputeNextState(doParallel);

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

	void TextOutArray::LatchNewState(boolean doParallel) {
		ConceptArray::LatchNewState(doParallel);
	}
}