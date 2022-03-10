#pragma once
#include "pch.h"
#include "ClassPredefines.h"

namespace SRS22 {

	class PatternConnection
	{
	public:
		std::shared_ptr<SRSUnit> map;
		/// <summary>
		/// Linear index in map.M.charges
		/// </summary>
		const int mapIdx;
		float NeuronStateAtT;

		PatternConnection(std::shared_ptr<SRSUnit> map, int mapIdx);
	};

}
