#pragma once
#include "../../ConceptMap.h"

/// x, y, blend, r, g, b
#define DrawOutMap_Width 6

#define DrawOutMap_MinBlend 0.25f

#define DrawOUtMap_X 0
#define DrawOUtMap_Y 1
#define DrawOUtMap_Blend 2
#define DrawOUtMap_R 3
#define DrawOUtMap_G 4
#define DrawOUtMap_B 5

namespace SRS22 {
	/// <summary>
	/// Map of output to the drawing whiteboard. Uses WhiteboardOutPt.
	///  x, y, blend, r, g, b which is 6 elements matching DrawOutMap_Width
	/// All being range 0.0 to 1.0 charge vales. Every tick if bland is > BLEND_MIN it outputs to the drawing board, then clears all to 0.0
	/// </summary>
	class DrawOutMap : public ConceptMap
	{
	public:
		/// <summary>
		/// implemented as
		/// ConceptMap("DrawOutMap",
		///     ConnectivityTriple(0.10f, 0.75f, 0.15f, 100),
		/// 	cv::Vec3f(0.0, 0.0, 0.0),
		/// 	DrawOutMap_Width,
		/// 	"Whiteboard pen out to screen.")
		/// </summary>
		DrawOutMap(Brain* br);
		~DrawOutMap();

		virtual void ComputeNextState(boolean doParallel) override;
		const unsigned char ChargeToColorUByte(const size_t MIndex);
		virtual void LatchNewState(boolean doParallel) override;
	};
}
