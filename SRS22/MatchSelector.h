#pragma once
#include "ClassPredefines.h"

#include "ConceptState.h"

namespace SRS22 {
	typedef std::pair<std::shared_ptr<ConceptState>, float> SelectionResult;

	class MatchSelector
	{
	public:
		virtual SelectionResult Select(std::shared_ptr<ConceptState> conceptMap, PatternMatchingSystem* patterns);
	};
}
