#pragma once
#include "../../ConceptArray.h"
#include "../../HardwareIO/PhonemesE.h"

#define PhonemeArray_Width ((int)PhonemeE::MAXENUM)

namespace SRS22 {
	/// <summary>
	/// Map each tick picks the most charged neuron, outputs that character, and zeros that charge to zero.
	/// There is a threshold for minimal charge to fire off a character.
	/// Coded as X is lower 4 bits, Y is upper 4 bits ASCII.
	/// </summary>
	class PhonemeArray : public ConceptArray
	{
	public:
		/// <summary>
		/// implemented as
		/// ConceptArray("PhonemeArray",
		///     ConnectivityTriple(0.10f, 0.75f, 0.15f, 100),
		/// 	cv::Vec3f(0.0, 0.0, 0.0),
		/// 	PhonemeArray_Width,
		/// 	"The \"Voice\" out the audio system.")
		/// </summary>
		PhonemeArray(Brain* br);
		~PhonemeArray();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};
}
