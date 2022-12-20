#pragma once

#include "IOCommon.h"
#include "WhiteboardPt.h"

namespace SRS22 {
	class WhiteboardOutIO : IOCommon
	{
	public:
		static std::recursive_mutex mtx;
		static std::list<WhiteboardPt> outputQueue;

		WhiteboardOutIO();
		~WhiteboardOutIO();

		virtual bool Init();
		virtual void Shutdown();

		/// <summary>
		/// Called for each IOCommon at the start of tick in Brain.
		/// </summary>
		virtual void PreTick();
		/// <summary>
		/// Called for each IOCommon at the end of tick in Brain.
		/// </summary>
		virtual void PostTick();

		void UnitTest();

		static void EnqueuePoint(WhiteboardPt pt) {
			std::lock_guard<std::recursive_mutex> lk(mtx);
			outputQueue.push_front(pt);
		}

		static bool GetNextQueuedPt(WhiteboardPt& pt /* out */) {
			std::lock_guard<std::recursive_mutex> lk(mtx);
			if (outputQueue.size() > 0) {
				pt = outputQueue.back();
				outputQueue.pop_back();
				return true;
			}
			return false;
		}
	};
}
