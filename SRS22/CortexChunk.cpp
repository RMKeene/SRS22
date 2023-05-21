#include "pch.h"
#include "CortexChunk.h"
#include "Pattern.h"
#include "FastRand.h"
#include "Brain.h"
#include "SRS22LogTaker.h"

namespace SRS22 {

	void CortexChunk::ComputeNextState() {
		int i = 0;
		for (auto& p : patterns) {
			if (p->tickCountdownUntilLearnOutputs > 0) {
				p->tickCountdownUntilLearnOutputs--;
				if (p->tickCountdownUntilLearnOutputs == 0) {
					SRS22LogTaker::LogInfo("Finish new pattern in chunk " + name);
					p->MakeSemiRandomOutputConnections(brain, *this, i);
					p->tickCountdownUntilLearnOutputs = -1; // Turn off counter.
				}
			}
			p->ComputeNextState();

			i++;
		}
		if (brain.ShouldLearn())
			growthSum += growthRate * brain.overallGoodnessRateOfChange;
	}

	void CortexChunk::LatchNewState() {

	}

	void CortexChunk::LearningPhase() {
		if (growthSum >= 1.0f) {
			growthSum = 0.0f;
			TryToAddNewPattern();
		}
	}

	int CortexChunk::GetRandomLinearOffset() {
		return fastRand() % patterns.size();
	}

	/// <summary>
	/// Get offset to either a unused pattern, or if all in use ( isPopulated() ) to the least used pattern.
	/// </summary>
	/// <returns></returns>
	optional<int> CortexChunk::GetLinearOffsetToPopulate() {
		optional<int> maxStaleOffset = nullopt;
		float maxStaleValue = -20000.0f;
		for (int i = 0; i < patterns.size(); i++) {
			const bool isNPop = !patterns.at(i)->isPopulated();
			if (isNPop || patterns.at(i)->staleness > maxStaleValue) {
				if (isNPop)
					return i;
				maxStaleOffset = i;
				maxStaleValue = patterns.at(i)->staleness;
			}
		}

		return maxStaleOffset;
	}

	float CortexChunk::GetChargeValue(const int linearOffset) {
		return patterns.at(linearOffset)->charge;
	}

	void CortexChunk::SetChargeValue(const int linearOffset, const float c) {
		patterns.at(linearOffset)->charge = c;
	}

	void CortexChunk::AddToChargeValue(const int linearOffset, const float c) {
		patterns.at(linearOffset)->charge += c;
	}

	void CortexChunk::PostCreate() {
		FillNearAndFarChunkCache();
	}

	void CortexChunk::FillNearAndFarChunkCache()
	{
		const float near2 = brain.maxNearDistance * brain.maxNearDistance;
		const float far2 = brain.minFarDistance * brain.minFarDistance;
		// Fill nearChunks and farChunks
		for (auto ch = brain.cortexChunks.begin(); ch != brain.cortexChunks.end(); ch++) {
			if (ch->get() != this) {
				if (this->distanceSquared(**ch) <= near2) {
					nearChunks.push_back(*ch);
				}
				else if (this->distanceSquared(**ch) >= far2) {
					farChunks.push_back(*ch);
				}
			}
		}
	}

	bool CortexChunk::ShouldAddNewPattern() {
		return brain.TheWorldIsGettingBetter();
	}

	bool CortexChunk::TryToAddNewPattern() {
		if (ShouldAddNewPattern()) {
			optional<int> i = GetLinearOffsetToPopulate();
			if (i.has_value()) {
				if (patterns.at(i.value()).get() == nullptr) {
					patterns.at(i.value()) = std::make_shared<Pattern>();
				}
				patterns.at(i.value())->MakeSemiRandomInputConnections(brain, *this, i.value());
				patterns.at(i.value())->BeginLearningDelay(*this);
				SRS22LogTaker::LogInfo("Created new pattern in chunk " + name);
				return true;
			}
			else {
				return false;
			}
		}
		return false;
	}


}