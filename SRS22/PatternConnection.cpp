#include "pch.h"
#include "PatternConnection.h"

namespace SRS22 {

	PatternConnection::PatternConnection(BrainConnectable* target, int linearOffset) :
		target(target), linearOffset(linearOffset), ExpectedCharge(0.0f) {
	}

}