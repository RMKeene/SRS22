#pragma once
#include "../../ConceptMap.h"

#define CameraFoveaMap_Width 15
#define CameraFoveaMap_Height 15

namespace SRS22 {
	/// <summary>
	/// Raw pixel map of center of camera fovea in color. 8x8 in the center of the ScreenAttnSpot.
	/// </summary>
	class CameraFoveaAngleMap : public ConceptMap
	{
	public:
		/// <summary>
		/// Implemented as
		/// ConceptMap("CameraFoveaAngleMap",
		/// ConnectivityTriple(0.10f, 0.75f, 0.15f, 100),
		/// 	cv::Vec3f(0.0, 0.0, 0.0),
		/// 	1, CameraFoveaMap_Height, CameraFoveaMap_Width,
		/// 	"Camera fovea radial edge map.")
		/// </summary>
		CameraFoveaAngleMap(Brain* br);
		~CameraFoveaAngleMap();

		virtual void ComputeNextState() override;
		virtual void LatchNewState() override;
	};
}
