#pragma once
#include "../../ConceptMap.h"

/// x, y, blend, r, g, b
#define DrawInMap_Width 6

#define DrawInMap_MinBlend 0.25f

#define DrawInMap_X 0
#define DrawInMap_Y 1
#define DrawInMap_Blend 2
#define DrawInMap_R 3
#define DrawInMap_G 4
#define DrawInMap_B 5

namespace SRS22 {
	/// <summary>
	/// Map of output to the drawing whiteboard. Uses WhiteboardOutPt.
	///  x, y, blend, r, g, b which is 6 elements matching DrawInMap_Width
	/// All being range 0.0 to 1.0 charge vales. Every tick if bland is > BLEND_MIN it outputs to the drawing board, then clears all to 0.0
	/// </summary>
	class DrawInMap : public ConceptMap
	{
	public:
		/// <summary>
		/// implemented as
		/// ConceptMap("DrawInMap",
		///     ConnectivityTriple(0.10f, 0.75f, 0.15f, 100),
		/// 	cv::Vec3f(0.0, 0.0, 0.0),
		/// 	DrawInMap_Width,
		/// 	"Whiteboard pen out to screen.")
		/// </summary>
		DrawInMap(Brain* br);
		~DrawInMap();

		virtual void ComputeNextState(boolean doParallel) override;
		const float ColorUByteToCharge(const unsigned char c);
		virtual void LatchNewState(boolean doParallel) override;
	};
}
