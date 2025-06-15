#pragma once
#include "../../ConceptArray.h"

/// Just an X,Y value in the map.
#define CameraMotionXYArray_Width 2

namespace SRS22 {
	/// <summary>
	/// A lower resolution version of the camera view processed for frame to frame motion differences.
	/// 1 x 64 x 48
	/// </summary>
	class CameraMotionXYArray : public ConceptArray
	{
	public:
		CameraMotionXYArray(Brain* br);
		~CameraMotionXYArray();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};
}
