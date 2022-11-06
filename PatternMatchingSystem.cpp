#include "pch.h"
#include "PatternMatchingSystem.h"

namespace SRS22 {
	SelectionResult PatternMatchingSystem::Select(std::shared_ptr<ConceptState> conceptState) {
		return selector.Select(conceptState, this);
	}
}