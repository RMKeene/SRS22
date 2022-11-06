#pragma once
#pragma once
#include "../../SRSUnit.h"

/// Just an X,Y value in the map.
#define CameraAttnSpotMap_Width 2

namespace SRS22 {
	/// <summary>
	/// Map of 2 values, X and Y of where the CameraAttnSpotIO is directed.
	/// </summary>
	class CameraAttnSpotMap : public SRSUnit
	{
	public:
		/// <summary>
		/// implemented as
		/// SRSUnit("CameraAttnSpotMap",
		///     ConnectivityTriple(0.10f, 0.75f, 0.15f, 100),
		/// 	cv::Vec3f(0.0, 0.0, 0.0),
		/// 	CameraAttnSpotMap_Width,
		/// 	"Raw pixel map of center of camera fovea in color.")
		/// </summary>
		CameraAttnSpotMap(Brain* br);
		~CameraAttnSpotMap();

		virtual void ComputeNextState() override;
		virtual void LatchNewState() override;
	};
}
