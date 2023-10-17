#pragma once
#include "../../ConceptMap.h"
#include "CameraFoveaMap.h"

namespace SRS22 {
	/// <summary>
	/// Edges of camera fovea in color. 8x8 in the center of the ScreenAttnSpot. Canny edge detection.
	/// </summary>
	class CameraFoveaEdgesMap : public ConceptMap
	{
	public:
		/// <summary>
		/// Implemented as
		/// ConceptMap("CameraEdgesMap",
		/// ConnectivityTriple(0.10f, 0.75f, 0.15f, 100),
		/// 	cv::Vec3f(0.0, 0.0, 0.0),
		/// 	1, CameraFoveaMap_Height, CameraFoveaMap_Width,
		/// 	"Edges of camera fovea in color.")
		/// </summary>
		CameraFoveaEdgesMap(Brain* br);
		~CameraFoveaEdgesMap();

		virtual void ComputeNextState() override;
		virtual void LatchNewState() override;
	};
}
