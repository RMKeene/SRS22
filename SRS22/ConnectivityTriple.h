#pragma once

#include <utility>
#include <cassert>

namespace SRS22 {
	/// This is the inverted ⅄ connectivity triple mentioned in the paper.
	/// We assume all neurons in a CortexChunk or Concept map have
	/// the same location for connectivity distance purposes.
	/// See paper Connectivity Triples ⅄, and Brain maxNearDistance and minFarDistance
	class ConnectivityTriple
	{
	public:
		/// <summary>
		/// Fraction (0.0 to 1.0) if connections to CortexChunk self.
		/// A + B + C must equal 1.0f.
		/// </summary>
		const float selfFraction;
		/// <summary>
		/// Fraction (0.0 to 1.0) if connections to nearby CortexChunk and/or ConceptMaps.
		/// </summary>
		const float nearbyFraction;
		/// <summary>
		/// Fraction (0.0 to 1.0) if connections to far CortexChunk and/or ConceptMaps.
		/// </summary>
		const float farFraction;

		/// <summary>
		/// How many connections this CortexNeuron should have generated on setup.
		/// You may get less than or equal to that many connections.
		/// May be zero to turn off connectivity to other maps.
		/// </summary>
		const int desiredConnectionCount;

		const int learningDeltaT;

		ConnectivityTriple(float selfFraction, float nearbyFraction, float farFraction, int desiredConnectionCount, int learningDeltaT) :
			selfFraction(selfFraction), nearbyFraction(nearbyFraction), farFraction(farFraction),
			desiredConnectionCount(desiredConnectionCount), learningDeltaT(learningDeltaT) {
			// A + B + C must equal 1.0f
			assert(fabs(1.0f - (selfFraction + nearbyFraction + farFraction)) < 0.0001f);
			assert(desiredConnectionCount >= 0);
			assert(learningDeltaT >= 0);
		}

		bool IsUnconnected() { return desiredConnectionCount == 0; }
	};
}
