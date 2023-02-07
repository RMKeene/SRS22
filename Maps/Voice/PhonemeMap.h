#pragma once
#include "../../ConceptMap.h"
#include "../../HardwareIO/PhonemesE.h"

#define PhonemeMap_Width ((int)PhonemeE::MAXENUM)

namespace SRS22 {
	/// <summary>
	/// Map each tick picks the most charged neuron, outputs that character, and zeros that charge to zero.
	/// There is a threshold for minimal charge to fire off a character.
	/// Coded as X is lower 4 bits, Y is upper 4 bits ASCII.
	/// </summary>
	class PhonemeMap : public ConceptMap
	{
	public:
		/// <summary>
		/// implemented as
		/// ConceptMap("PhonemeMap",
		///     ConnectivityTriple(0.10f, 0.75f, 0.15f, 100),
		/// 	cv::Vec3f(0.0, 0.0, 0.0),
		/// 	PhonemeMap_Width,
		/// 	"The \"Voice\" out the audio system.")
		/// </summary>
		PhonemeMap(Brain* br);
		~PhonemeMap();

		virtual void ComputeNextState() override;
		virtual void LatchNewState() override;
	};
}
