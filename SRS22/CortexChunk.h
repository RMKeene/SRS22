#pragma once
#include "pch.h"
#include <opencv2/core.hpp>

#include "ClassPredefines.h"
#include "ConnectivityTriple.h"
#include "BrainLocatable.h"
#include "BrainConnectable.h"
#include "Tickable.h"

namespace SRS22 {

	/// <summary>
	/// A cluster of Patterns in the cortex.
	/// All Patterns have the same location (BrainLocatable).
	/// All Patterns in a chunk are considered "very near" or "self" distance from each other.
	/// </summary>
	class CortexChunk : public BrainLocatable, public BrainConnectable, public Tickable
	{
	public:
		/// <summary>
		/// Once we hit this then we start replacing the most stale Pattern with a new one on growth tick.
		/// </summary>
		const int maxPatterns;
		/// <summary>
		/// Triple ratio of how much very near, near and far to get input patterns and output pattern from.
		/// </summary>
		const ConnectivityTriple ctrip;
		/// <summary>
		/// Added every tick. When growthSum hits 1.0 then growthSum is reset to 0 and a new Pattern is acquired.
		/// Moderated by global goodness factor.
		/// </summary>
		const float growthRate;
		/// <summary>
		/// How many patterns currently in this chunk. 
		/// </summary>
		std::vector<std::shared_ptr <Pattern>> patterns;

		Brain& brain;

		/// <summary>
		/// Cached lists of which ConceptMaps and/or CortexChunks are nearby in concept 3d space.
		/// </summary>
		std::vector<std::shared_ptr<BrainConnectable>> nearChunks;
		std::vector<std::shared_ptr<BrainConnectable>> farChunks;

		CortexChunk(Brain& brain,const cv::Vec3f location, const int maxPatterns, const ConnectivityTriple ctrip, const float growthRate) :
			brain(brain),
			BrainLocatable(location),
			maxPatterns(maxPatterns),
			ctrip(ctrip),
			growthRate(growthRate)
		{
		}

		~CortexChunk() {
			nearChunks.clear();
			farChunks.clear();
			patterns.clear();
		}
		
		void PostCreate();

		void FillNearAndFarChunkCache();

		void ComputeNextState() override;

		void LatchNewState() override;

		int GetRandomLinearOffset() override;
		/// <summary>
		/// Get firstly an unused offset, or if all used, get the most stale.
		/// </summary>
		/// <returns></returns>
		std::optional<int> GetLinearOffsetToPopulate();

		float GetChargeValue(const int linearOffset) override;
		void SetChargeValue(const int linearOffset, const float c) override;
		void AddToChargeValue(const int linearOffset, const float c) override;

		/// <summary>
		/// True if you should try to add a new pattern in this Chunk. False if you shouldn't.
		/// </summary>
		/// <returns></returns>
		bool ShouldAddNewPattern();

		/// <summary>
		/// Try to add a pattern. Returns true if successful.
		/// </summary>
		/// <returns></returns>
		bool TryToAddNewPattern();

	};
}