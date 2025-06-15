#pragma once
#include "../../ConceptArray.h"

/// x, y, blend, r, g, b
#define DrawOutArray_Width 6

#define DrawOutArray_MinBlend 0.25f

#define DrawOUtArray_X 0
#define DrawOUtArray_Y 1
#define DrawOUtArray_Blend 2
#define DrawOUtArray_R 3
#define DrawOUtArray_G 4
#define DrawOUtArray_B 5

namespace SRS22 {
	/// <summary>
	/// Map of output to the drawing whiteboard. Uses WhiteboardOutPt.
	///  x, y, blend, r, g, b which is 6 elements matching DrawOutArray_Width
	/// All being range 0.0 to 1.0 charge vales. Every tick if bland is > BLEND_MIN it outputs to the drawing board, then clears all to 0.0
	/// </summary>
	class DrawOutArray : public ConceptArray
	{
	public:
		DrawOutArray(Brain* br);
		~DrawOutArray();

		virtual void ComputeNextState(boolean doParallel) override;
		const unsigned char ChargeToColorUByte(const size_t MIndex);
		virtual void LatchNewState(boolean doParallel) override;
	};
}
