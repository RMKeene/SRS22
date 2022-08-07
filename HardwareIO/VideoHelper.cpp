#include "VideoHelper.h"
#include <Mmsystem.h>
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <Wmcodecdsp.h>
#include <assert.h>
#include <Dbt.h>
#include <shlwapi.h>

#pragma comment(lib, "mf")
#pragma comment(lib, "mfplat")

namespace SRS22 {

	const float VideoHelper::lowResScale = 0.1f;

	VideoHelper::VideoHelper() {
	}

	VideoHelper::~VideoHelper() {
		Shutdown();
	}

	void VideoHelper::Shutdown() {
		if (cap) {
			cap->release();
			cap = nullptr;
		}
	}

	int VideoHelper::GetCameraWidthWin32() {
		if (cap == nullptr)
			cap = new VideoCapture(0);
		if (!cap->isOpened()) {
			return 0;
		}
		return cap->get(CAP_PROP_FRAME_WIDTH);
	}

	int VideoHelper::GetCameraHeightWin32() {
		if (cap == nullptr)
			cap = new VideoCapture(0);
		if (!cap->isOpened()) {
			return 0;
		}

		return cap->get(CAP_PROP_FRAME_HEIGHT);
	}

	bool VideoHelper::CaptureFrame() {
		if (cap == nullptr)
			cap = new VideoCapture(0);
		if (!cap->isOpened()) {
			return false;
		}

		// 640 x 480 color CV_8UC3 depth 24 bits BGR
		currentImage3UC8.copyTo(previousImage3UC8);
		currentImageLowRes3UC8.copyTo(previousImageLowRes3UC8);
		*cap >> currentImage3UC8;
		if (!currentImage3UC8.empty()) {
			//cv::String ts = cv::typeToString(currentImage.type()); // "CV_8UC3"
			//imshow(ts, currentImage);

			cv::Size sz = currentImage3UC8.size();
			int imageWidth = sz.width;
			int imageHeight = sz.height;
			cv::cvtColor(currentImage3UC8, currentImage3UC8, cv::COLOR_RGB2BGR);
			// Genertate low res RGB.
			cv::Size size(currentImage3UC8.cols * lowResScale, currentImage3UC8.rows * lowResScale);
			cv::resize(currentImage3UC8, currentImageLowRes3UC8, size);
			return true;
		}
		return false;
	}

	HRESULT VideoHelper::EnumerateDevices()
	{
		HRESULT hr = S_OK;
		IMFAttributes* pAttributes = NULL;
		UINT32      m_cDevices = 0; // contains the number of devices
		IMFActivate** m_ppDevices = NULL; // contains properties about each device

		listedDevices.clear();

		// Initialize an attribute store. We will use this to
		// specify the enumeration parameters.
		std::cout << "Enumerate devices" << std::endl;
		hr = MFCreateAttributes(&pAttributes, 1);

		// Ask for source type = video capture devices
		if (SUCCEEDED(hr))
		{
			std::cout << "Enumerate devices" << std::endl;
			hr = pAttributes->SetGUID(
				MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE,
				MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_GUID
			);
		}
		// Enumerate devices.
		if (SUCCEEDED(hr))
		{
			hr = MFEnumDeviceSources(pAttributes, &m_ppDevices, &m_cDevices);
			std::cout << "Enumerate devices count:" << m_cDevices << std::endl;
		}

		for (UINT32 i = 0; i < m_cDevices; i++) {
			IMFActivate* a = m_ppDevices[i];
			WCHAR Value[1024];
			Value[0] = '\0';
			UINT32  cchBufSize = 1024;
			UINT32 cchLength = 0;
			hr = a->GetString(MF_DEVSOURCE_ATTRIBUTE_FRIENDLY_NAME, Value, cchBufSize, &cchLength);
			std::cout << "   Device:" << Value << std::endl;
			if (SUCCEEDED(hr)) {
				listedDevices.push_back(std::wstring(Value));
			}
		}

		if (pAttributes) {
			pAttributes->Release();
		}

		return hr;
	}

}
