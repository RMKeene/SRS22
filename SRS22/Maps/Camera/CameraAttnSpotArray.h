#pragma once
#pragma once
#include "../../ConceptArray.h"

/// Just an X,Y value in the map.
#define CameraAttnSpotArray_Width 2

namespace SRS22 {
	/// <summary>
	/// Map of 2 values, X and Y of where the CameraFovea is located. Updates the CameraInIO fovea each tick. 
	/// </summary>
	class CameraAttnSpotArray : public ConceptArray
	{
	public:
		/// <summary>
		/// implemented as
		/// CameraAttnSpotArray("CameraAttnSpotArray",
		///     ConnectivityTriple(0.10f, 0.75f, 0.15f, 100),
		/// 	cv::Vec3f(0.0, 0.0, 0.0),
		/// 	CameraAttnSpotArray_Width,
		/// 	"Raw pixel map of center of camera fovea in color.")
		/// </summary>
		CameraAttnSpotArray(Brain* br);
		~CameraAttnSpotArray();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};
}
