#pragma once
#include "../../ConceptArray.h"

namespace SRS22 {
	/// <summary>
	/// A lower resolution version of the camera view processed for frame to frame motion differences.
	/// 1 x 64 x 48
	/// </summary>
	class CameraFoveaAbsDiffArray : public ConceptArray
	{
	public:

		CameraFoveaAbsDiffArray(Brain* br);
		~CameraFoveaAbsDiffArray();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};
}
