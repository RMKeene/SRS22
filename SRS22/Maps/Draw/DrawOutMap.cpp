#include "../../SRS22pch.h"
#include "DrawOutMap.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../HardwareIO/WhiteboardOutIO.h"

namespace SRS22 {
	DrawOutMap::DrawOutMap(Brain* br) :
		ConceptMap(br, MapUidE::DRAWOUT_MAP, "DrawOutMap",
			DrawOutMap_Width, 0.0f,
			"Whiteboard pen out to screen.") {
	}

	DrawOutMap::~DrawOutMap() {
	}

	void DrawOutMap::ComputeNextState(boolean doParallel) {
		ConceptMap::ComputeNextState(doParallel);

		if (get(DrawOUtMap_Blend) < DrawOutMap_MinBlend)
			return;

		auto whiteboard = IOCommon::GetIO<WhiteboardOutIO>();
		WhiteboardPt pt(get(DrawOUtMap_R), get(DrawOUtMap_G), get(DrawOUtMap_B),
			get(DrawOUtMap_Blend), get(DrawOUtMap_X), get(DrawOUtMap_Y));

		whiteboard->EnqueuePoint(pt);

		put(DrawOUtMap_R, 0.0f);
		put(DrawOUtMap_G, 0.0f);
		put(DrawOUtMap_B, 0.0f);
		put(DrawOUtMap_Blend, 0.0f);
		put(DrawOUtMap_X, 0.0f);
		put(DrawOUtMap_Y, 0.0f);
	}

	const unsigned char DrawOutMap::ChargeToColorUByte(const size_t MIndex)
	{
		return static_cast<unsigned char>(std::clamp(get(MIndex) * 255.0f, 0.0f, 255.0f));
	}

	void DrawOutMap::LatchNewState(boolean doParallel) {
		ConceptMap::LatchNewState(doParallel);
	}
}