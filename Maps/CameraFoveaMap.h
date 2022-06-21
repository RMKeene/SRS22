#pragma once
#include "../SRSUnit.h"

#define CameraFoveaMap_Width 15
#define CameraFoveaMap_Height 15

namespace SRS22 {
	/// <summary>
	/// Raw pixel map of center of camera fovea in color. 8x8 in the center of the ScreenAttnSpot.
	/// </summary>
	class CameraFoveaMap : public SRSUnit
	{
	public:
		/// <summary>
		/// implemented as 
		/// SRSUnit("CameraFoveaMap", ctrip, location, 3, CameraFoveaMap_Width, CameraFoveaMap_Height, 
		///     "Raw pixel map of center of camera fovea in color.") {
		/// </summary>
		CameraFoveaMap();
		~CameraFoveaMap();

		virtual void ComputeNextState() override;
		virtual void LatchNewState() override;
	};

}
