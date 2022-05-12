#pragma once
#include <Windows.h>
#include <dshow.h>

#include "IOCommon.h"
#include "WaveOutputHelper.h"

namespace SRS22 {
	class AudioOutIO : IOCommon
	{
	public:
		WaveOutputHelper outHelper;

		AudioOutIO();
		~AudioOutIO();

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

		void CaptureSegment();

		void UnitTest();
	};

}

