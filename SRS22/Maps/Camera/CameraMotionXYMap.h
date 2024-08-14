#pragma once
#include "../../ConceptMap.h"

/// Just an X,Y value in the map.
#define CameraMotionXYMap_Width 2

namespace SRS22 {
	/// <summary>
	/// A lower resolution version of the camera view processed for frame to frame motion differences.
	/// 1 x 64 x 48
	/// </summary>
	class CameraMotionXYMap : public ConceptMap
	{
	public:
		/// <summary>
		/// Implemented as
		/// ConceptMap("CameraMotionXYMap",
		/// ConnectivityTriple(0.10f, 0.75f, 0.15f, 100),
		/// 	cv::Vec3f(0.0, 0.0, 0.0),
		/// 	CameraMotionXYMap_Width,
		/// 	"The XY location of the maximum frame to frame difference.")
		/// </summary>
		CameraMotionXYMap(Brain* br, bool computeNextStateEnabled = true);
		~CameraMotionXYMap();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};
}
