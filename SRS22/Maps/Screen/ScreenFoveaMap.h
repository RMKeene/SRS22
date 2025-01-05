#pragma once
#include "../../ConceptMap.h"

#define ScreenFoveaMap_Width 15
#define ScreenFoveaMap_Height 15

namespace SRS22 {
	/// <summary>
	/// Raw pixel map of center of screen fovea in color. 8x8 in the center of the ScreenAttnSpot.
	/// </summary>
	class ScreenFoveaMap : public ConceptMap
	{
	public:
		/// <summary>
		/// implemented as
		/// ConceptMap("ScreenFoveaMap", ctrip, location, 3, ScreenFoveaMap_Height, ScreenFoveaMap_Width,
		///     "Raw pixel map of center of screen fovea in color.") {
		/// </summary>
		ScreenFoveaMap(Brain* br);
		~ScreenFoveaMap();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};
}
