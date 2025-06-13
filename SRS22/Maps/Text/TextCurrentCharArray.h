#pragma once
#include "../../ConceptArray.h"

#define TextCurrentCharArray_Width 16
#define TextCurrentCharArray_Height 16

namespace SRS22 {
	/// <summary>
	/// Map of entered text last character in the Text entry window.
	/// Coded as X is lower 4 bits, Y is upper 4 bits. Just sets the single value on input, then it fades over time.
	/// </summary>
	class TextCurrentCharArray : public ConceptArray
	{
	public:
		/// <summary>
		/// implemented as
		/// ConceptArray("TextCurrentCharArray",
		///     ConnectivityTriple(0.10f, 0.75f, 0.15f, 100),
		/// 	cv::Vec3f(0.0, 0.0, 0.0),
		/// 	TextCurrentCharArray_Width,
		///     TextCurrentCharArray_Height,
		/// 	"Last entered character ASCII Code")
		/// </summary>
		TextCurrentCharArray(Brain* br);
		~TextCurrentCharArray();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};
}
