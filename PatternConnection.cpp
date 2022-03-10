#include "pch.h"
#include "PatternConnection.h"
#include "SRSUnit.h"
   
namespace SRS22 {

	PatternConnection::PatternConnection(std::shared_ptr<SRSUnit> map, int mapIdx) :
		map(map), mapIdx(mapIdx) {

	}

}
