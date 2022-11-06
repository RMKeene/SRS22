#pragma once
#pragma once
#include "../../SRSUnit.h"

/// Just an X,Y value in the map.
#define ScreenAttnSpotMap_Width 2

namespace SRS22 {
	/// <summary>
	/// Map of 2 values, X and Y of where the ScreenAttnSpotIO is directed.
	/// </summary>
	class ScreenAttnSpotMap : public SRSUnit
	{
	public:
		/// <summary>
		/// implemented as
		/// SRSUnit("ScreenAttnSpotMap",
		///     ConnectivityTriple(0.10f, 0.75f, 0.15f, 100),
		/// 	cv::Vec3f(0.0, 0.0, 0.0),
		/// 	ScreenAttnSpotMap_Width,
		/// 	"Raw pixel map of center of screen fovea in color.")
		/// </summary>
		ScreenAttnSpotMap(Brain* br);
		~ScreenAttnSpotMap();

		virtual void ComputeNextState() override;
		virtual void LatchNewState() override;
	};
}
