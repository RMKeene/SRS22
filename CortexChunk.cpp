#include "pch.h"
#include "CortexChunk.h"
#include "FastRand.h"

namespace SRS22 {

	void CortexChunk::ComputeNextState() {

	}

	void CortexChunk::LatchNewState() {

	}

	int CortexChunk::GetRandomLinearOffset() {
		return fastRand() % patterns.size();
	}

	float CortexChunk::GetChargeValue(const int linearOffset) {

	}

	void CortexChunk::SetChargeValue(const int linearOffset, const float c) {

	}

	void CortexChunk::AddToChargeValue(const int linearOffset, const float c) {

	}

}