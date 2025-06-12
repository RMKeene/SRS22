#pragma once
#include "../../ConceptArray.h"

/// Just an X,Y value in the map.
#define ScreenMotionXYMap_Width 2

namespace SRS22 {
	/// <summary>
	/// A lower resolution version of the screen view processed for frame to frame motion differences.
	/// 1 x 64 x 48
	/// </summary>
	class ScreenMotionXYMap : public ConceptArray
	{
	public:
		/// <summary>
		/// Implemented as
		/// ConceptArray("ScreenMotionXYMap",
		/// ConnectivityTriple(0.10f, 0.75f, 0.15f, 100),
		/// 	cv::Vec3f(0.0, 0.0, 0.0),
		/// 	ScreenMotionXYMap_Width,
		/// 	"The XY location of the maximum frame to frame difference.")
		/// </summary>
		ScreenMotionXYMap(Brain* br);
		~ScreenMotionXYMap();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};
}
