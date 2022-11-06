#pragma once
#include "pch.h"

#include <utility>
#include <cassert>

namespace SRS22 {
	/// See paper Connectivity Triples ⅄, and Brain maxNearDistance and minFarDistance
	class ConnectivityTriple
	{
	public:
		/// <summary>
		/// Fraction (0.0 to 1.0) if connections to SRSUnit self.
		/// A + B + C must equal 1.0f.
		/// </summary>
		const float selfFract;
		/// <summary>
		/// Fraction (0.0 to 1.0) if connections to neaby SRSUnits.
		/// </summary>
		const float nearbyFract;
		/// <summary>
		/// Fraction (0.0 to 1.0) if connections to far SRSUnits.
		/// </summary>
		const float farFract;

		/// <summary>
		/// How many connections this map should have generated on setup.
		/// You may get less than or equal to that many connections.
		/// May be zero to turn off connectivity to other maps.
		/// </summary>
		const int desiredConnectionCount;

		ConnectivityTriple(float selfFraction, float nearbyFraction, float farFraction, int desiredConnectionCount) :
			selfFract(selfFraction), nearbyFract(nearbyFraction), farFract(farFraction), desiredConnectionCount(desiredConnectionCount) {
			// A + B + C must equal 1.0f
			assert(selfFraction + nearbyFraction + farFraction > 0.99f && selfFraction + nearbyFraction + farFraction < 1.01f);
			assert(desiredConnectionCount >= 0);
		}

		bool IsUnconnected() { return desiredConnectionCount == 0; }
	};
}
