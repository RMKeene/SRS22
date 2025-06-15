#pragma once
#include "../../ConceptArray.h"

/// Just an X,Y value in the map.
#define ScreenMotionXYArray_Width 2

namespace SRS22 {
	/// <summary>
	/// A lower resolution version of the screen view processed for frame to frame motion differences.
	/// 1 x 64 x 48
	/// </summary>
	class ScreenMotionXYArray : public ConceptArray
	{
	public:
		ScreenMotionXYArray(Brain* br);
		~ScreenMotionXYArray();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};
}
