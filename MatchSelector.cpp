#include "pch.h"

#include "MatchSelector.h"
#include "PatternMatchingSystem.h"

namespace SRS22 {
	SelectionResult MatchSelector::Select(std::shared_ptr<ConceptState> conceptMap, PatternMatchingSystem* patterns)
	{
		SelectionResult ret(nullptr, 0.0f);

		for (auto m : patterns->knownPatterns)
		{
			float f = m.second.Compare(conceptMap);
		}

		return ret;
	}
}