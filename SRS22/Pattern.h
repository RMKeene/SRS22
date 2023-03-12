#pragma once
#include "pch.h"
#include "ClassPredefines.h"
#include "PatternConnection.h"
#include "CortexChunk.h"

namespace SRS22 {
	/// <summary>
	/// The state of the entire Brain some delta T before the associated ConceptState in a Pattern Matching System.
	/// Plus, the state of some subset of the Brain a **few ticks later**. So two full snapshots of the entire brain state.
	/// 
	/// But...
	/// 
	/// Since one can not snapshot the entire brain a few 100k times, we instead
	/// snapshot sparse representations.
	/// We do a three way ratio of very near, near and far Brain state. 
	/// The three way balance is called a Connectivity Triple in the CortexChunk that owns
	/// this Pattern. And Delta T comes from the CortexChunk.
	/// 
	/// The Pattern has a Charge which is how well it matched on the previous tick.
	/// 
	/// 
	/// </summary>
	class Pattern : public Tickable
	{
	public:

		/// <summary>
		/// Input Connections and what their state was at time T.
		/// </summary>
		std::list<std::shared_ptr<PatternConnection>> inputConnections;
		/// <summary>
		/// Output connections and what their state was at time T + delta.
		/// </summary>
		std::list<std::shared_ptr<PatternConnection>> outputConnections;

		float charge = 0.0f;
		float nextCharge = 0.0f;

		Pattern();
		~Pattern();

		virtual void ComputeNextState() override;
		virtual void LatchNewState() override;

		/// <summary>
		/// Fill the input connections list with a sparse snapshot of
		/// the entire Brain state, moderated by the Connectivity Triple ctrip.
		/// This is the state seen "now".
		/// </summary>
		void MakeSemiRandomInputConnections(Brain& brain, CortexChunk& ct, const int patternSelfOffset);

		/// <summary>
		/// It is now T + DeltaT so snapshot the current local SRS22 ConceptState 
		/// moderated by the Connectivity Triple ctrip.
		/// This is the state seen "in the future".
		/// </summary>
		void MakeSemiRandomOutputConnections(Brain& brain, CortexChunk& ct, const int patternSelfOffset);

	};
}
