#pragma once
#include "../../ConceptArray.h"
#include "CameraFoveaMap.h"

namespace SRS22 {
	class CameraFoveaEdgesMap : public ConceptArray
	{
	public:
		CameraFoveaEdgesMap(Brain* br);
		~CameraFoveaEdgesMap();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};

}
