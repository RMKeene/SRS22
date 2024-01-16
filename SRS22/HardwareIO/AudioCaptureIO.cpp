#include "../../pch.h"
#include "AudioCaptureIO.h"

namespace SRS22 {
	AudioCaptureIO::AudioCaptureIO() : IOCommon() {
		IOCOMMON_SETCLASSNAME;
	}

	AudioCaptureIO::~AudioCaptureIO() {
	}

	bool AudioCaptureIO::Init() {
		IOCommon::Init();
		buffer = NULL;
		bufferSize = 0;
		inputHelper.Init();
		DebugAudioInputDevices();
		return true;
	}

	void AudioCaptureIO::Shutdown() {
		MMTIME mmt;
		inputHelper.StopRecord(&inputHelper.waveInHandle, &mmt);
		inputHelper.CloseWaveIn(&inputHelper.waveInHandle);
		IOCommon::Shutdown();
	}

	void AudioCaptureIO::PreTickHardwareAndIO() {
		IOCommon::PreTickHardwareAndIO();
		CaptureSegment();
	}

	void AudioCaptureIO::PostTickHardwareAndUI() {
		IOCommon::PostTickHardwareAndUI();
	}

	void AudioCaptureIO::UnitTest() {
	}

	void AudioCaptureIO::CaptureSegment() {
		//int bytesRead = inputHelper.CaptureToBuffer(&buffer, &bufferSize);
	}

#pragma comment(lib, "strmiids")

	void AudioCaptureIO::DebugAudioInputDevices() {
		IEnumMoniker* pEnum;
		HRESULT res = EnumerateDevices(&pEnum);
		DisplayDeviceInformation(pEnum);
	}

	HRESULT AudioCaptureIO::EnumerateDevices(IEnumMoniker** ppEnum)
	{
		REFGUID category = CLSID_AudioInputDeviceCategory;
		// Create the System Device Enumerator.
		ICreateDevEnum* pDevEnum;
		HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL,
			CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pDevEnum));

		if (SUCCEEDED(hr))
		{
			// Create an enumerator for the category.
			hr = pDevEnum->CreateClassEnumerator(category, ppEnum, 0);
			if (hr == S_FALSE)
			{
				hr = VFW_E_NOT_FOUND;  // The category is empty. Treat as an error.
			}
			pDevEnum->Release();
		}
		return hr;
	}

	void AudioCaptureIO::DisplayDeviceInformation(IEnumMoniker* pEnum)
	{
		IMoniker* pMoniker = NULL;

		while (pEnum->Next(1, &pMoniker, NULL) == S_OK)
		{
			IPropertyBag* pPropBag;
			HRESULT hr = pMoniker->BindToStorage(0, 0, IID_PPV_ARGS(&pPropBag));
			if (FAILED(hr))
			{
				pMoniker->Release();
				continue;
			}

			VARIANT var;
			VariantInit(&var);

			// Get description or friendly name.
			hr = pPropBag->Read(L"Description", &var, 0);
			if (FAILED(hr))
			{
				hr = pPropBag->Read(L"FriendlyName", &var, 0);
			}
			if (SUCCEEDED(hr))
			{
				printf("%S\n", var.bstrVal);
				VariantClear(&var);
			}

			hr = pPropBag->Write(L"FriendlyName", &var);

			// WaveInID applies only to audio capture devices.
			hr = pPropBag->Read(L"WaveInID", &var, 0);
			if (SUCCEEDED(hr))
			{
				printf("WaveIn ID: %d\n", var.lVal);
				VariantClear(&var);
			}

			hr = pPropBag->Read(L"DevicePath", &var, 0);
			if (SUCCEEDED(hr))
			{
				// The device path is not intended for display.
				printf("Device path: %S\n", var.bstrVal);
				VariantClear(&var);
			}

			pPropBag->Release();
			pMoniker->Release();
		}
	}
}