#pragma once
#include "../../ConceptArray.h"

#define CameraFoveaArray_Width 15
#define CameraFoveaArray_Height 15

namespace SRS22 {
	/// <summary>
	/// Raw pixel map of center of camera fovea in color. 8x8 in the center of the CameraAttnSpot.
	/// </summary>
	class CameraFoveaArray : public ConceptArray
	{
	public:
		/// <summary>
		/// Implemented as
		/// ConceptArray("CameraFoveaArray",
		/// ConnectivityTriple(0.10f, 0.75f, 0.15f, 100),
		/// 	cv::Vec3f(0.0, 0.0, 0.0),
		/// 	1, CameraFoveaArray_Height, CameraFoveaArray_Width,
		/// 	"Raw pixel map of center of camera fovea in color.")
		/// </summary>
		CameraFoveaArray(Brain* br);
		~CameraFoveaArray();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};
}
