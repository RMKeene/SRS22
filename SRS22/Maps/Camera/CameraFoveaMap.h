#pragma once
#include "../../ConceptMap.h"

#define CameraFoveaMap_Width 15
#define CameraFoveaMap_Height 15

namespace SRS22 {
	/// <summary>
	/// Raw pixel map of center of camera fovea in color. 8x8 in the center of the CameraAttnSpot.
	/// </summary>
	class CameraFoveaMap : public ConceptMap
	{
	public:
		/// <summary>
		/// Implemented as
		/// ConceptMap("CameraFoveaMap",
		/// ConnectivityTriple(0.10f, 0.75f, 0.15f, 100),
		/// 	cv::Vec3f(0.0, 0.0, 0.0),
		/// 	1, CameraFoveaMap_Height, CameraFoveaMap_Width,
		/// 	"Raw pixel map of center of camera fovea in color.")
		/// </summary>
		CameraFoveaMap(Brain* br);
		~CameraFoveaMap();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};
}
