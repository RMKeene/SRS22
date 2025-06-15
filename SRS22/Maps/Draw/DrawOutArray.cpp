#include "../../SRS22pch.h"
#include "DrawOutArray.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../HardwareIO/WhiteboardOutIO.h"

namespace SRS22 {
	DrawOutArray::DrawOutArray(Brain* br) :
		ConceptArray(br, ArrayUidE::DRAWOUT_MAP, "DrawOutArray", NeuronType::IS_OUTPUT,
			DrawOutArray_Width, 0.0f,
			"Whiteboard pen out to screen.") {
	}

	DrawOutArray::~DrawOutArray() {
	}

	void DrawOutArray::ComputeNextState(boolean doParallel) {
		ConceptArray::ComputeNextState(doParallel);

		if (get(DrawOUtArray_Blend) < DrawOutArray_MinBlend)
			return;

		auto whiteboard = IOCommon::GetIO<WhiteboardOutIO>();
		WhiteboardPt pt(get(DrawOUtArray_R), get(DrawOUtArray_G), get(DrawOUtArray_B),
			get(DrawOUtArray_Blend), get(DrawOUtArray_X), get(DrawOUtArray_Y));

		whiteboard->EnqueuePoint(pt);

		put(DrawOUtArray_R, 0.0f);
		put(DrawOUtArray_G, 0.0f);
		put(DrawOUtArray_B, 0.0f);
		put(DrawOUtArray_Blend, 0.0f);
		put(DrawOUtArray_X, 0.0f);
		put(DrawOUtArray_Y, 0.0f);
	}

	const unsigned char DrawOutArray::ChargeToColorUByte(const size_t MIndex)
	{
		return static_cast<unsigned char>(std::clamp(get(MIndex) * 255.0f, 0.0f, 255.0f));
	}

	void DrawOutArray::LatchNewState(boolean doParallel) {
		ConceptArray::LatchNewState(doParallel);
	}
}