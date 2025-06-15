#include "../../SRS22pch.h"
#include "TextCurrentCharArray.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../Brain.h"

namespace SRS22 {
	TextCurrentCharArray::TextCurrentCharArray(Brain* br) :
		ConceptArray(br, ArrayUidE::TEXTCCURRENTCHAR_MAP, "TextCurrentCharArray", NeuronType::IS_INPUT,
			TextCurrentCharArray_Width,
			TextCurrentCharArray_Height, 0.98f,
			"Last entered character ASCII Code.") {
		displayMode = SRSUnitDisplayModes::TWOVALUECAMERA;
	}

	TextCurrentCharArray::~TextCurrentCharArray() {
	}

	void TextCurrentCharArray::ComputeNextState(boolean doParallel) {
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

	void TextCurrentCharArray::LatchNewState(boolean doParallel) {
		ConceptArray::LatchNewState(doParallel);
	}
}