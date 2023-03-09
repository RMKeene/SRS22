#include "pch.h"
#include "CortexChunk.h"
#include "Pattern.h"
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
		return patterns.at(linearOffset)->charge;
	}

	void CortexChunk::SetChargeValue(const int linearOffset, const float c) {
		patterns.at(linearOffset)->charge = c;
	}

	void CortexChunk::AddToChargeValue(const int linearOffset, const float c) {
		patterns.at(linearOffset)->charge += c;
	}

}