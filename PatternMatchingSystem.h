#pragma once
#include "pch.h"
#include "ClassPredefines.h"

#include "MatchSelector.h"
#include "ConceptState.h"
#include "Pattern.h"
#include "Reaper.h"

namespace SRS22 {
	class PatternMatchingSystem
	{
	public:
		/// <summary>
		/// The concept state is the privious state of the Concept Map
		/// that was present some delta T before
		/// the patter was snap shotted.
		/// </summary>
		std::list<std::pair<Pattern, ConceptState>> knownPatterns;
		MatchSelector selector;
		Reaper reaper;

		virtual SelectionResult Select(std::shared_ptr<ConceptState> conceptMap);
	};
}
