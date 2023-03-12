#include "pch.h"
#include "CortexChunk.h"
#include "Pattern.h"
#include "FastRand.h"
#include "Brain.h"

namespace SRS22 {

	void CortexChunk::ComputeNextState() {
		for (auto& p : patterns) {
			p->ComputeNextState();
		}
	}

	void CortexChunk::LatchNewState() {

	}

	int CortexChunk::GetRandomLinearOffset() {
		return fastRand() % patterns.size();
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

	void CortexChunk::PostCreate(Brain& brain) {
		FillNearAndFarChunkCache(brain);
	}

	void CortexChunk::FillNearAndFarChunkCache(SRS22::Brain& brain)
	{
		const float near2 = brain.maxNearDistance * brain.maxNearDistance;
		const float far2 = brain.minFarDistance * brain.minFarDistance;
		// Fill nearChunks and farChunks
		for (auto ch = brain.cortexChunks.begin(); ch != brain.cortexChunks.end(); ch++) {
			if (ch->get() != this) {
				if (this->distanceSquared(**ch) < near2) {
					nearChunks.push_back(*ch);
				}
				else if (this->distanceSquared(**ch) > far2) {
					farChunks.push_back(*ch);
				}
			}
		}
	}
}