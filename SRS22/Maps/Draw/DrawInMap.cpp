#include "../../pch.h"
#include "DrawInMap.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../HardwareIO/WhiteboardInIO.h"

namespace SRS22 {
	DrawInMap::DrawInMap(Brain* br) :
		ConceptMap(br, MapUidE::DRAWIN_MAP, true, "DrawInMap",
			cv::Vec3f(0.0, 0.0, 0.0),
			DrawInMap_Width,
			"Whiteboard pen in from screen. The SRS \"feels\" when you draw.") {
		SetDecayFactors(true, 0.9f);
	}

	DrawInMap::~DrawInMap() {
	}

	void DrawInMap::ComputeNextState() {
		ConceptMap::ComputeNextState();

		auto whiteboard = IOCommon::GetIO<WhiteboardInIO>();
		WhiteboardPt pt;
		if (whiteboard->GetNextQueuedPt(pt)) {
			nextM.put(ColorUByteToCharge(pt.r), DrawInMap_R);
			nextM.put(ColorUByteToCharge(pt.g), DrawInMap_G);
			nextM.put(ColorUByteToCharge(pt.b), DrawInMap_B);
			nextM.put(pt.blend, DrawInMap_Blend);
			nextM.put(pt.x, DrawInMap_X);
			nextM.put(pt.y, DrawInMap_Y);
		}
	}

	const float DrawInMap::ColorUByteToCharge(const unsigned char c)
	{
		return (float)c / 255.0f;
	}

	void DrawInMap::LatchNewState() {
		ConceptMap::LatchNewState();
	}
}