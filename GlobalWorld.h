#pragma once
#include "Brain.h"

namespace SRS22 {
	/// <summary>
	/// The global world that holds one or more Brains, and may have other world simulation attibutes.
	/// The current (05/2022) implementation has a UI nad the world is the real world via camera, screen, microphone etc.
	/// But there could be more than one Brain in some simulated world too.
	/// </summary>
	class GlobalWorld
	{
		bool isExiting = false;
	public:
		static GlobalWorld GlobalWorldInstance;

		std::array <std::shared_ptr<Brain>, 1> brains;

		GlobalWorld() {
			brains[0] = make_shared<Brain>();
			brains[0]->Init();
		}

		~GlobalWorld() {

		}

		void Exit();

		/// <summary>
		/// Idx starts at 0. No error checking. Assumes at least one Brain exists.
		/// </summary>
		/// <param name="idx"></param>
		/// <returns></returns>
		std::shared_ptr<Brain> GetBrain(int idx) { return brains[idx]; }

		int GetBrainCount() { return brains.size(); }

		void TickAll();
	};
}

