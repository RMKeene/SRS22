#pragma once
#include "../ConceptMap.h"

#define RandomMap_Width 15
#define RandomMap_Height 15

namespace SRS22 {
	/// <summary>
	/// Raw pixel map of center of screen fovea in color. 8x8 in the center of the ScreenAttnSpot.
	/// </summary>
	class RandomMap : public ConceptMap
	{
	public:
		RandomMap(Brain* br);
		~RandomMap();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};
}
