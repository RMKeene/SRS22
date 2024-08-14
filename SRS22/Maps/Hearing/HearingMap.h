#pragma once
#include "../../ConceptMap.h"
#include "../../HardwareRaw/WaveInConstants.h"

#define HearingMap_Width SRS22FFTRESULTSIZE

namespace SRS22 {
	/// <summary>
	/// Map each tick picks the most charged neuron, outputs that character, and zeros that charge to zero.
	/// There is a threshold for minimal charge to fire off a character.
	/// Coded as X is lower 4 bits, Y is upper 4 bits ASCII.
	/// </summary>
	class HearingMap : public ConceptMap
	{
	public:
		/// <summary>
		/// implemented as
		/// ConceptMap("HearingMap",
		///     ConnectivityTriple(0.10f, 0.75f, 0.15f, 100),
		/// 	cv::Vec3f(0.0, 0.0, 0.0),
		/// 	HearingMap_Width,
		/// 	"The \"Hearing\" input from the audio system.")
		/// </summary>
		HearingMap(Brain* br, bool computeNextStateEnabled = true);
		~HearingMap();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};
}
