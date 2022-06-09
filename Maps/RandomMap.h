#pragma once
#include "../SRSUnit.h"

#define RandomMap_Width 15
#define RandomMap_Height 15

namespace SRS22 {
	/// <summary>
	/// Raw pixel map of center of screen fovea in color. 8x8 in the center of the ScreenAttnSpot.
	/// </summary>
	class RandomMap : public SRSUnit
	{
	public:
		RandomMap();
		~RandomMap();

		virtual void ComputeNextState() override;
		virtual void LatchNewState() override;
	};

}
