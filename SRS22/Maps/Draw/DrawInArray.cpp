#include "../../SRS22pch.h"
#include "DrawInArray.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../HardwareIO/WhiteboardInIO.h"

namespace SRS22 {
	DrawInArray::DrawInArray(Brain* br) :
		ConceptArray(br, ArrayUidE::DRAWIN_MAP, "DrawInArray", NeuronType::IS_INPUT,
			DrawInArray_Width, 0.5f,
			"Whiteboard pen in from screen. The SRS \"feels\" when you draw.") {
	}

	DrawInArray::~DrawInArray() {
	}

	void DrawInArray::ComputeNextState(boolean doParallel) {
		ConceptArray::ComputeNextState(doParallel);

		auto whiteboard = IOCommon::GetIO<WhiteboardInIO>();
		WhiteboardPt pt;
		if (whiteboard->GetNextQueuedPt(pt)) {
			putNext(DrawInArray_R, ColorUByteToCharge(pt.r));
			putNext(DrawInArray_G, ColorUByteToCharge(pt.g));
			putNext(DrawInArray_B, ColorUByteToCharge(pt.b));
			putNext(DrawInArray_Blend, pt.blend);
			putNext(DrawInArray_X, pt.x);
			putNext(DrawInArray_Y, pt.y);
		}
	}

	const float DrawInArray::ColorUByteToCharge(const unsigned char c)
	{
		return (float)c / 255.0f;
	}

	void DrawInArray::LatchNewState(boolean doParallel) {
		ConceptArray::LatchNewState(doParallel);
	}
}