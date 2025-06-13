#pragma once
#include "../../ConceptArray.h"

namespace SRS22 {
	/// <summary>
	/// A lower resolution version of the screen view processed for frame to frame motion differences.
	/// 1 x 64 x 48
	/// </summary>
	class ScreenDifferenceArray : public ConceptArray
	{
	public:
		/// <summary>
		/// Implemented as
		/// ConceptArray("ScreenDifferenceArray",
		/// ConnectivityTriple(0.10f, 0.75f, 0.15f, 100),
		/// 	cv::Vec3f(0.0, 0.0, 0.0),
		/// 	3, ScreenInIO::AbsDiffHeight, ScreenInIO::AbsDiffWidth,
		///		"A lower resolution version of the screen view processed for frame to frame motion differences.")
		/// </summary>
		ScreenDifferenceArray(Brain* br);
		~ScreenDifferenceArray();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};
}
