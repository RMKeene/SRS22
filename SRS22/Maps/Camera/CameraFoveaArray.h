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
		CameraFoveaArray(Brain* br);
		~CameraFoveaArray();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};
}
