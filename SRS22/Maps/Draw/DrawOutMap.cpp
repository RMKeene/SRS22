#include "../../pch.h"
#include "DrawOutMap.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../HardwareIO/WhiteboardOutIO.h"

namespace SRS22 {
	DrawOutMap::DrawOutMap(Brain* br) :
		ConceptMap(br, MapUidE::DRAWOUT_MAP, true, "DrawOutMap",
			cv::Vec3f(0.0, 0.0, 0.0),
			DrawOutMap_Width,
			"Whiteboard pen out to screen.") {
		SetDecayFactors(0.0f);
	}

	DrawOutMap::~DrawOutMap() {
	}

	void DrawOutMap::ComputeNextState() {
		ConceptMap::ComputeNextState();

		if (M.get(DrawOUtMap_Blend) < DrawOutMap_MinBlend)
			return;

		auto whiteboard = IOCommon::GetIO<WhiteboardOutIO>();
		WhiteboardPt pt(M.get(DrawOUtMap_R), M.get(DrawOUtMap_G), M.get(DrawOUtMap_B),
			M.get(DrawOUtMap_Blend), M.get(DrawOUtMap_X), M.get(DrawOUtMap_Y));

		whiteboard->EnqueuePoint(pt);

		M.put(0.0f, DrawOUtMap_R);
		M.put(0.0f, DrawOUtMap_G);
		M.put(0.0f, DrawOUtMap_B);
		M.put(0.0f, DrawOUtMap_Blend);
		M.put(0.0f, DrawOUtMap_X);
		M.put(0.0f, DrawOUtMap_Y);
	}

	const unsigned char DrawOutMap::ChargeToColorUByte(const size_t MIndex)
	{
		return static_cast<unsigned char>(std::clamp(M.get(MIndex) * 255.0f, 0.0f, 255.0f));
	}

	void DrawOutMap::LatchNewState() {
		ConceptMap::LatchNewState();
	}
}