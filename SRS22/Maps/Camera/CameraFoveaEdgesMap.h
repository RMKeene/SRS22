#pragma once
#include "../../ConceptMap.h"
#include "CameraFoveaMap.h"

namespace SRS22 {
	class CameraFoveaEdgesMap : public ConceptMap
	{
	public:
		CameraFoveaEdgesMap(Brain* br, bool computeNextStateEnabled = true);
		~CameraFoveaEdgesMap();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};

}
