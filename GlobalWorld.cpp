#include "pch.h"
#include "GlobalWorld.h"

namespace SRS22 {

	GlobalWorld GlobalWorld::GlobalWorldInstance;

	void GlobalWorld::TickAll() {
		if (!isExiting) {
			for (int i = 0; i < brains.size(); i++) {
				brains[i]->Tick();
			}
		}
	}

	void GlobalWorld::Exit() {
		isExiting = true;
		Sleep(1000);
		for (int i = 0; i < brains.size(); i++) {
			brains[i]->Shutdown();
		}
	}
}