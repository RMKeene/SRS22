#pragma once
#include "../../ConceptMap.h"

namespace SRS22 {
	/// <summary>
	/// A lower resolution version of the camera view processed for frame to frame motion differences.
	/// 1 x 64 x 48
	/// </summary>
	class CameraDifferenceMap : public ConceptMap
	{
	public:
		/// <summary>
		/// Implemented as
		/// ConceptMap("CameraDifferenceMap",
		/// ConnectivityTriple(0.10f, 0.75f, 0.15f, 100),
		/// 	cv::Vec3f(0.0, 0.0, 0.0),
		/// 	3, CameraInIO::AbsDiffHeight, CameraInIO::AbsDiffWidth,
		///		"A lower resolution version of the camera view processed for frame to frame motion differences.")
		/// </summary>
		CameraDifferenceMap(Brain* br, bool computeNextStateEnabled = true);
		~CameraDifferenceMap();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};
}
