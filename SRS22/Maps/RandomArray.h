#pragma once
#include "../ConceptArray.h"

#define RandomArray_Width 15
#define RandomArray_Height 15

namespace SRS22 {
	/// <summary>
	/// Raw pixel map of center of screen fovea in color. 8x8 in the center of the ScreenAttnSpot.
	/// </summary>
	class RandomArray : public ConceptArray
	{
	public:
		RandomArray(Brain* br);
		~RandomArray();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};
}
