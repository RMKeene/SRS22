#include "pch.h"
#include "GlobalWorld.h"

namespace SRS22 {

	GlobalWorld GlobalWorld::GlobalWorldInstance;

	void GlobalWorld::TickAll() {
		for (int i = 0; i < brains.size(); i++) {
			brains[i]->Tick();
		}
	}
}