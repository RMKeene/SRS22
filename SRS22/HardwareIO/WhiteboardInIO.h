#pragma once

#include "IOCommon.h"
#include "WhiteboardPt.h"

namespace SRS22 {
	class WhiteboardInIO : IOCommon
	{
	public:
		static std::recursive_mutex mtx;
		static std::list<WhiteboardPt> inputQueue;

		WhiteboardInIO();
		~WhiteboardInIO();

		virtual bool Init();
		virtual void Shutdown();

		/// <summary>
		/// Called at the start of tick in Brain.
		/// </summary>
		virtual void PreTickHardwareAndIO();
		/// <summary>
		/// Called at the end of tick in Brain.
		/// </summary>
		virtual void PostTickHardwareAndUI();

		virtual void UnitTest();

		static void EnqueuePoint(WhiteboardPt pt) {
			std::lock_guard<std::recursive_mutex> lk(mtx);
			inputQueue.push_front(pt);
		}

		static bool GetNextQueuedPt(WhiteboardPt& pt /* out */) {
			std::lock_guard<std::recursive_mutex> lk(mtx);
			if (inputQueue.size() > 0) {
				pt = inputQueue.back();
				inputQueue.pop_back();
				return true;
			}
			return false;
		}
	};
}
