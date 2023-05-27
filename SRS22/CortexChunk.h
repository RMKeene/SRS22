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
		/// Arbitrary name so it is easier to comprehend and debug what is foing on.
		/// </summary>
		const std::string name;
		/// <summary>
		/// Once we hit this then we start replacing the most stale Pattern with a new one on growth tick.
		/// </summary>
		const int maxPatterns;
		/// <summary>
		/// Triple ratio of how much very near, near and far to get input patterns and output pattern from.
		/// </summary>
		const ConnectivityTriple ctrip;
		/// <summary>
		/// growthRate * brain.overallGoodnessRateOfChange added every tick if brain.ShouldLearn. 
		/// When growthSum hits 1.0 then growthSum is reset to 0.0 and a new Pattern is acquired.
		/// Moderated by global goodness factor.
		/// </summary>
		const float growthRate;
		/// <summary>
		/// See growthRate.
		/// </summary>
		float growthSum = 0.0f;
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

		/// <summary>
		/// A chunk of the cortex.
		/// </summary>
		/// <param name="brain">Owner</param>
		/// <param name="name_or_emptyStr">Either a human friendly name or "" for "NoName"</param>
		/// <param name="location">The concept coordinates of the Chunk.</param>
		/// <param name="maxPatterns"></param>
		/// <param name="ctrip"></param>
		/// <param name="growthRate"></param>
		CortexChunk(Brain& brain, std::string name_or_emptyStr, const cv::Vec3f location, const int maxPatterns, const ConnectivityTriple ctrip, const float growthRate) :
			name(name_or_emptyStr.length() > 0 ? name_or_emptyStr : "NoName"),
			brain(brain),
			BrainLocatable(location),
			maxPatterns(maxPatterns),
			ctrip(ctrip),
			growthRate(growthRate)
		{
			for (int i = 0; i < maxPatterns; i++)
				patterns.push_back(std::make_shared<Pattern>());
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

		void LearningPhase() override;

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