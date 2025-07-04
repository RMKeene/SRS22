#pragma once
#include "../../ConceptArray.h"

/// Just an X,Y value in the map.
#define ScreenAttnSpotArray_Width 2

namespace SRS22 {
	/// <summary>
	/// Map of 2 values, X and Y of where the ScreenAttnSpotIO is directed.
	/// </summary>
	class ScreenAttnSpotArray : public ConceptArray
	{
	public:
		ScreenAttnSpotArray(Brain* br);
		~ScreenAttnSpotArray();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};
}
