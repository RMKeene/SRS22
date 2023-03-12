#include "pch.h"
#include "Pattern.h"
#include "ConnectivityTriple.h"
#include "Brain.h"

namespace SRS22 {
	Pattern::Pattern() {
	}

	Pattern::~Pattern() {
	}

	void Pattern::ComputeNextState() {
		// Compute the next state of the charge.
		// This is a simple summation of the fabs(input charges - expected charge).
		// The output charges are computed in the output connections.
		float sum = 0.0f;
		for (auto& conn : inputConnections) {
			if (conn->target != nullptr) {
				sum += fabs(conn->target->GetChargeValue(conn->linearOffset) - conn->ExpectedCharge);
			}
		}
		nextCharge = sum;
	}

	void Pattern::LatchNewState() {
		charge = nextCharge;
	}

	void Pattern::MakeSemiRandomInputConnections(Brain& brain, CortexChunk& ct, const int patternSelfOffset) {
		if (inputConnections.size() != ct.ctrip.desiredConnectionCount) {
			// Clear the list and start over. Saves on reallocating.
			inputConnections.clear();
		}
		for (int i = ct.ctrip.desiredConnectionCount; i > 0; i--) {
			// Choose by fractions of ctrip
			std::shared_ptr<PatternConnection> conn = std::make_shared<PatternConnection>();
			if (!brain.GetRandomConnectionPoint(ct, patternSelfOffset, conn)) {
				// Failed to find a connection point, so mark it as invalid and keep going.
				conn->target = nullptr;
			}
			inputConnections.push_front(conn);
		}
	}

	void Pattern::MakeSemiRandomOutputConnections(Brain& brain, CortexChunk& ct, const int patternSelfOffset) {
		if (outputConnections.size() != ct.ctrip.desiredConnectionCount) {
			// Clear the list and start over. Saves on reallocating.
			outputConnections.clear();
		}
		for (int i = ct.ctrip.desiredConnectionCount; i > 0; i--) {
			// Choose by fractions of ctrip
			std::shared_ptr<PatternConnection> conn = std::make_shared<PatternConnection>();
			if (!brain.GetRandomConnectionPoint(ct, patternSelfOffset, conn)) {
				// Failed to find a connection point, so mark it as invalid and keep going.
				conn->target = nullptr;
			}
			outputConnections.push_front(conn);
		}
	}
}