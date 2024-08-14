#pragma once
#include "../../ConceptMap.h"

#define TextCurrentCharMap_Width 16
#define TextCurrentCharMap_Height 16

namespace SRS22 {
	/// <summary>
	/// Map of entered text last character in the Text entry window.
	/// Coded as X is lower 4 bits, Y is upper 4 bits. Just sets the single value on input, then it fades over time.
	/// </summary>
	class TextCurrentCharMap : public ConceptMap
	{
	public:
		/// <summary>
		/// implemented as
		/// ConceptMap("TextCurrentCharMap",
		///     ConnectivityTriple(0.10f, 0.75f, 0.15f, 100),
		/// 	cv::Vec3f(0.0, 0.0, 0.0),
		/// 	TextCurrentCharMap_Width,
		///     TextCurrentCharMap_Height,
		/// 	"Last entered character ASCII Code")
		/// </summary>
		TextCurrentCharMap(Brain* br, bool computeNextStateEnabled = true);
		~TextCurrentCharMap();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};
}
