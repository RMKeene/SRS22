#pragma once
#include "../SRSUnit.h"

namespace SRS22 {
	/// <summary>
	/// Raw pixel map of center of screen fovea in color. 8x8 in the center of the ScreenAttnSpot.
	/// </summary>
	class ScreenFoveaMap : public SRSUnit
	{
	public:
		/// <summary>
		/// implemented as 
		/// SRSUnit("ScreenFoveaMap", ctrip, location, 3, 8, 8, 
		///     "Raw pixel map of center of screen fovea in color.") {
		/// </summary>
		ScreenFoveaMap();
		~ScreenFoveaMap();

		virtual void ComputeNextState();
		virtual void LatchNewState();
	};

}
