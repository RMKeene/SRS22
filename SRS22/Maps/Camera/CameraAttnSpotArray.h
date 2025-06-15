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
		CameraAttnSpotArray(Brain* br);
		~CameraAttnSpotArray();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};
}
