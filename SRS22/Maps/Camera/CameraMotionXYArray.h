#pragma once
#include "../../ConceptArray.h"

/// Just an X,Y value in the map.
#define CameraMotionXYArray_Width 2

namespace SRS22 {
	/// <summary>
	/// A lower resolution version of the camera view processed for frame to frame motion differences.
	/// 1 x 64 x 48
	/// </summary>
	class CameraMotionXYArray : public ConceptArray
	{
	public:
		/// <summary>
		/// Implemented as
		/// ConceptArray("CameraMotionXYArray",
		/// ConnectivityTriple(0.10f, 0.75f, 0.15f, 100),
		/// 	cv::Vec3f(0.0, 0.0, 0.0),
		/// 	CameraMotionXYArray_Width,
		/// 	"The XY location of the maximum frame to frame difference.")
		/// </summary>
		CameraMotionXYArray(Brain* br);
		~CameraMotionXYArray();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};
}
