#pragma once

#include "SRSUnit.h"
#include "ClassPredefines.h"

namespace SRS22 {
	/// <summary>
	/// This knows how to display a SRSUnit for debug and monitoring.
	/// </summary>
	class SRSUnitDisplay
	{
	public:

		/// <summary>
		/// Draws some represntation of u to hDC scaled to fit rect.
		/// </summary>
		/// <param name="dc"></param>
		/// <param name="rect"></param>
		/// <param name="u"></param>
		static void DrawInDC(Gdiplus::Graphics& g, Gdiplus::Rect& rect, std::shared_ptr<SRSUnit> u, bool showLabel = true, bool preClearToBlack = true);
	};
}
