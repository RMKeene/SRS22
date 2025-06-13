#pragma once
#include "../../ConceptArray.h"
#include "../../HardwareRaw/WaveInConstants.h"

#define HearingArray_Width SRS22FFTRESULTSIZE

namespace SRS22 {
	/// <summary>
	/// Map each tick picks the most charged neuron, outputs that character, and zeros that charge to zero.
	/// There is a threshold for minimal charge to fire off a character.
	/// Coded as X is lower 4 bits, Y is upper 4 bits ASCII.
	/// </summary>
	class HearingArray : public ConceptArray
	{
	public:
		/// <summary>
		/// implemented as
		/// ConceptArray("HearingArray",
		///     ConnectivityTriple(0.10f, 0.75f, 0.15f, 100),
		/// 	cv::Vec3f(0.0, 0.0, 0.0),
		/// 	HearingArray_Width,
		/// 	"The \"Hearing\" input from the audio system.")
		/// </summary>
		HearingArray(Brain* br);
		~HearingArray();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};
}
