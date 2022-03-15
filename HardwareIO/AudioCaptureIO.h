#pragma once
#include <Windows.h>
#include <dshow.h>

#include "IOCommon.h"

namespace SRS22 {
	class AudioCaptureIO : IOCommon
	{
	public:
		AudioCaptureIO();
		~AudioCaptureIO();

		virtual bool Init();
		virtual void Shutdown();
		void CaptureSegment();

		void UnitTest();

		HRESULT EnumerateDevices(IEnumMoniker** ppEnum);
		void DisplayDeviceInformation(IEnumMoniker* pEnum);
	};

}

