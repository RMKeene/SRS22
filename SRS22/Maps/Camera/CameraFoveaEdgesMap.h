#pragma once
#include "../../ConceptMap.h"
#include "CameraFoveaMap.h"

namespace SRS22 {
	class CameraFoveaEdgesMap : public ConceptMap
	{
	public:
		CameraFoveaEdgesMap(Brain* br);
		~CameraFoveaEdgesMap();

		virtual void ComputeNextState() override;
		virtual void LatchNewState() override;
	};

}
