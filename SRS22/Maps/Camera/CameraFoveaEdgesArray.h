#pragma once
#include "../../ConceptArray.h"
#include "CameraFoveaArray.h"

namespace SRS22 {
	class CameraFoveaEdgesArray : public ConceptArray
	{
	public:
		CameraFoveaEdgesArray(Brain* br);
		~CameraFoveaEdgesArray();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};

}
