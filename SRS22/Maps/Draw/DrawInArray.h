#pragma once
#include "../../ConceptArray.h"

/// x, y, blend, r, g, b
#define DrawInArray_Width 6

#define DrawInArray_MinBlend 0.25f

#define DrawInArray_X 0
#define DrawInArray_Y 1
#define DrawInArray_Blend 2
#define DrawInArray_R 3
#define DrawInArray_G 4
#define DrawInArray_B 5

namespace SRS22 {
	/// <summary>
	/// Map of output to the drawing whiteboard. Uses WhiteboardOutPt.
	///  x, y, blend, r, g, b which is 6 elements matching DrawInArray_Width
	/// All being range 0.0 to 1.0 charge vales. Every tick if bland is > BLEND_MIN it outputs to the drawing board, then clears all to 0.0
	/// </summary>
	class DrawInArray : public ConceptArray
	{
	public:
		/// <summary>
		/// implemented as
		/// ConceptArray("DrawInArray",
		///     ConnectivityTriple(0.10f, 0.75f, 0.15f, 100),
		/// 	cv::Vec3f(0.0, 0.0, 0.0),
		/// 	DrawInArray_Width,
		/// 	"Whiteboard pen out to screen.")
		/// </summary>
		DrawInArray(Brain* br);
		~DrawInArray();

		virtual void ComputeNextState(boolean doParallel) override;
		const float ColorUByteToCharge(const unsigned char c);
		virtual void LatchNewState(boolean doParallel) override;
	};
}
