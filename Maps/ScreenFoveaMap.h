#pragma once
#include "../SRSUnit.h"

#define ScreenFoveaMap_Width 15
#define ScreenFoveaMap_Height 15

namespace SRS22 {
	/// <summary>
	/// Raw pixel map of center of screen fovea in color. 8x8 in the center of the ScreenAttnSpot.
	/// </summary>
	class ScreenFoveaMap : public SRSUnit
	{
	public:
		/// <summary>
		/// implemented as 
		/// SRSUnit("ScreenFoveaMap", ctrip, location, 3, ScreenFoveaMap_Width, ScreenFoveaMap_Height, 
		///     "Raw pixel map of center of screen fovea in color.") {
		/// </summary>
		ScreenFoveaMap();
		~ScreenFoveaMap();

		virtual void ComputeNextState() override;
		virtual void LatchNewState() override;
	};

}
