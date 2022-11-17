#include "../../pch.h"
#include "TextOutMap.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../Brain.h"

namespace SRS22 {
	TextOutMap::TextOutMap(Brain* br) :
		SRSUnit(br, "TextOutMap",
			ConnectivityTriple(0.10f, 0.75f, 0.15f, 100),
			cv::Vec3f(0.0, 0.0, 0.0),
			TextOutMap_Width,
			TextOutMap_Height,
			"The \"Keyboard\" out the the text window.") {
		displayMode = SRSUnitDisplayModes::TWOVALUECAMERA;
		SetDecayFactors(true, 0.98f);
	}

	TextOutMap::~TextOutMap() {
	}

	void TextOutMap::ComputeNextState() {
		SRSUnit::ComputeNextState();

		auto textOutUI = IOCommon::GetIO<TextOutIO>();

		int row;
		int col;
		int depth;
		float v;
		if (M.FindMaxValue(0.25f, col, row, depth, v)) {
			nextM.put(0.0f, row, col);
			TextIOType c = ((row & 0x00FF) << 8) | (col & 0x00FF);
			textOutUI->TakeCharacter(c);
		}
	}

	void TextOutMap::LatchNewState() {
		SRSUnit::LatchNewState();
	}
}