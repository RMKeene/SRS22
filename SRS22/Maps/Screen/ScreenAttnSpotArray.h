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
		/// <summary>
		/// implemented as
		/// ConceptArray("ScreenAttnSpotArray",
		///     ConnectivityTriple(0.10f, 0.75f, 0.15f, 100),
		/// 	cv::Vec3f(0.0, 0.0, 0.0),
		/// 	ScreenAttnSpotArray_Width,
		/// 	"Raw pixel map of center of screen fovea in color.")
		/// </summary>
		ScreenAttnSpotArray(Brain* br);
		~ScreenAttnSpotArray();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};
}
