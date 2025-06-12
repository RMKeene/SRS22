#pragma once

#include "ConceptArray.h"
#include "ClassPredefines.h"

namespace SRS22 {
	/// <summary>
	/// This knows how to display a ConceptArray for debug and monitoring.
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
		static void DrawInDC(Gdiplus::Graphics& g, Gdiplus::Rect& rect, std::shared_ptr<ConceptArray> u, bool showLabel = true, bool preClearToBlack = true);
	};
}
