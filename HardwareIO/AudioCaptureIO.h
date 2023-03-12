#pragma once
#include <Windows.h>
#include <dshow.h>

#include "IOCommon.h"
#include "../HardwareRaw/WaveInputHelper.h"

namespace SRS22 {
	class AudioCaptureIO : IOCommon
	{
	public:
		WaveInputHelper inputHelper;
		void* buffer = NULL;
		int bufferSize = 0;

		AudioCaptureIO();
		~AudioCaptureIO();

		virtual bool Init();
		virtual void Shutdown();

		/// <summary>
		/// Called for each IOCommon at the start of tick in Brain.
		/// </summary>
		virtual void PreTickHardwareAndIO();
		/// <summary>
		/// Called for each IOCommon at the end of tick in Brain.
		/// </summary>
		virtual void PostTickHardwareAndUI();

		void CaptureSegment();

		void UnitTest();

		void DebugAudioInputDevices();
		HRESULT EnumerateDevices(IEnumMoniker** ppEnum);
		void DisplayDeviceInformation(IEnumMoniker* pEnum);
	};
}
