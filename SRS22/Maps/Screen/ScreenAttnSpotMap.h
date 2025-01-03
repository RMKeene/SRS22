#pragma once
#include "../../ConceptMap.h"

/// Just an X,Y value in the map.
#define ScreenAttnSpotMap_Width 2

namespace SRS22 {
	/// <summary>
	/// Map of 2 values, X and Y of where the ScreenAttnSpotIO is directed.
	/// </summary>
	class ScreenAttnSpotMap : public ConceptMap
	{
	public:
		/// <summary>
		/// implemented as
		/// ConceptMap("ScreenAttnSpotMap",
		///     ConnectivityTriple(0.10f, 0.75f, 0.15f, 100),
		/// 	cv::Vec3f(0.0, 0.0, 0.0),
		/// 	ScreenAttnSpotMap_Width,
		/// 	"Raw pixel map of center of screen fovea in color.")
		/// </summary>
		ScreenAttnSpotMap(Brain* br, bool computeNextStateEnabled = true);
		~ScreenAttnSpotMap();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};
}
