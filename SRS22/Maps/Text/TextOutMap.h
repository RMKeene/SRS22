#pragma once
#include "../../ConceptMap.h"

#define TextOutMap_Width 16
#define TextOutMap_Height 16

namespace SRS22 {
	/// <summary>
	/// Map each tick picks the most charged neuron, outputs that character, and zeros that charge to zero.
	/// There is a threshold for minimal charge to fire off a character.
	/// Coded as X is lower 4 bits, Y is upper 4 bits ASCII.
	/// </summary>
	class TextOutMap : public ConceptMap
	{
	public:
		/// <summary>
		/// implemented as
		/// ConceptMap("TextOutMap",
		///     ConnectivityTriple(0.10f, 0.75f, 0.15f, 100),
		/// 	cv::Vec3f(0.0, 0.0, 0.0),
		/// 	TextOutMap_Width,
		///     TextOutMap_Height,
		/// 	"The \"Keyboard\" out the text window.")
		/// </summary>
		TextOutMap(Brain* br);
		~TextOutMap();

		virtual void ComputeNextState() override;
		virtual void LatchNewState() override;
	};
}
