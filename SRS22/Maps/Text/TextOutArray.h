#pragma once
#include "../../ConceptArray.h"

#define TextOutArray_Width 16
#define TextOutArray_Height 16

namespace SRS22 {
	/// <summary>
	/// Map each tick picks the most charged neuron, outputs that character, and zeros that charge to zero.
	/// There is a threshold for minimal charge to fire off a character.
	/// Coded as X is lower 4 bits, Y is upper 4 bits ASCII.
	/// </summary>
	class TextOutArray : public ConceptArray
	{
	public:
		/// <summary>
		/// implemented as
		/// ConceptArray("TextOutArray",
		///     ConnectivityTriple(0.10f, 0.75f, 0.15f, 100),
		/// 	cv::Vec3f(0.0, 0.0, 0.0),
		/// 	TextOutArray_Width,
		///     TextOutArray_Height,
		/// 	"The \"Keyboard\" out the text window.")
		/// </summary>
		TextOutArray(Brain* br);
		~TextOutArray();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};
}
