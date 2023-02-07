#include "pch.h"
#include "PatternConnection.h"
#include "ConceptMap.h"

namespace SRS22 {
	PatternConnection::PatternConnection(std::shared_ptr<ConceptMap> map, int mapIdx) :
		map(map), mapIdx(mapIdx) {
	}
}