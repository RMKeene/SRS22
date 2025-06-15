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
		HearingArray(Brain* br);
		~HearingArray();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};
}
