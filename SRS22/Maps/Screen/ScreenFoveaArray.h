#pragma once
#include "../../ConceptArray.h"

#define ScreenFoveaArray_Width 15
#define ScreenFoveaArray_Height 15

namespace SRS22 {
	/// <summary>
	/// Raw pixel map of center of screen fovea in color. 8x8 in the center of the ScreenAttnSpot.
	/// </summary>
	class ScreenFoveaArray : public ConceptArray
	{
	public:
		ScreenFoveaArray(Brain* br);
		~ScreenFoveaArray();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};
}
