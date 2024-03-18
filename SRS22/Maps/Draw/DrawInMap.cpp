#include "../../SRS22pch.h"
#include "DrawInMap.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../HardwareIO/WhiteboardInIO.h"

namespace SRS22 {
	DrawInMap::DrawInMap(Brain* br) :
		ConceptMap(br, MapUidE::DRAWIN_MAP, "DrawInMap",
			DrawInMap_Width, 0.5f,
			"Whiteboard pen in from screen. The SRS \"feels\" when you draw.") {
	}

	DrawInMap::~DrawInMap() {
	}

	void DrawInMap::ComputeNextState(boolean doParallel) {
		ConceptMap::ComputeNextState(doParallel);

		auto whiteboard = IOCommon::GetIO<WhiteboardInIO>();
		WhiteboardPt pt;
		if (whiteboard->GetNextQueuedPt(pt)) {
			putNext(DrawInMap_R, ColorUByteToCharge(pt.r));
			putNext(DrawInMap_G, ColorUByteToCharge(pt.g));
			putNext(DrawInMap_B, ColorUByteToCharge(pt.b));
			putNext(DrawInMap_Blend, pt.blend);
			putNext(DrawInMap_X, pt.x);
			putNext(DrawInMap_Y, pt.y);
		}
	}

	const float DrawInMap::ColorUByteToCharge(const unsigned char c)
	{
		return (float)c / 255.0f;
	}

	void DrawInMap::LatchNewState(boolean doParallel) {
		ConceptMap::LatchNewState(doParallel);
	}
}