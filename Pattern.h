#pragma once
#include "pch.h"
#include "ClassPredefines.h"
#include "PatternConnection.h"

namespace SRS22 {
	/// <summary>
	/// The state of the entire Brain some delta T before the associated ConceptState in a Pattern Matching System.
	/// Since one can not snapshot the entire brain a few 100k times, we instead
	/// snapshot some of the ConceptState, some of nearby ConceptMap, and some of far ConceptMaps.
	/// The three way balance is called a Connectivity Triple (in the Concept Map that owns
	/// this Pattern Matching System) and thus this Pattern. And Delta T comes from the ConceptMap.
	/// </summary>
	class Pattern
	{
	public:
		int localCMapOffset;
		int localCMapSkip;

		/// <summary>
		/// Connections and their state at time T.
		/// </summary>
		std::list<std::shared_ptr<PatternConnection>> connections;

		/// <summary>
		/// What state the owner SRS22 was in at T plus DeltaT after connection was snapped.
		/// </summary>
		std::shared_ptr< ConceptState> stateAtTPlusDeltaT;

		Pattern();
		~Pattern();

		/// <summary>
		/// Fill the connections list with a sparse snapshot of
		/// the entire Brain state, moderated by the Connedctivity Triple ctrip.
		/// </summary>
		void MakeSemiRandomConnections(Brain& brain, std::shared_ptr<ConceptMap> map);

		/// <summary>
		/// It is now T + DeltaT so snapshot the current local SRS22 ConceptState.
		/// </summary>
		void SnapSRS22MapState(std::shared_ptr<ConceptMap> map);
	};
}
