#pragma once
#include "../../ConceptArray.h"

namespace SRS22 {
	/// <summary>
	/// A lower resolution version of the camera view processed for frame to frame motion differences.
	/// 1 x 64 x 48
	/// </summary>
	class CameraDifferenceArray : public ConceptArray
	{
	public:
		CameraDifferenceArray(Brain* br);
		~CameraDifferenceArray();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};
}
