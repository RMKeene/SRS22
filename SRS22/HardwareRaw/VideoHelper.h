#pragma once
#include "../pch.h"
#include "../HardwareIO/IOCommon.h"

using namespace cv;

namespace SRS22 {
	class VideoHelper
	{
	public:
		static const float lowResScale;
		/// <summary>
		/// RGB Image from camera. 3UC8 640(cols) x 480(rows)
		/// </summary>
		cv::Mat previousImage3UC8;
		cv::Mat currentImage3UC8;
		/// <summary>
		/// The low res images are scaled down with interpolation and RGB. See lowResScale above.
		/// Currently 1/10th scale so 64 x 48 RGB floats range 0.0 to 1.0
		/// </summary>
		cv::Mat previousImageLowRes3UC8;
		cv::Mat currentImageLowRes3UC8;
		cv::VideoCapture* cap = nullptr;

		std::string failureReason;

		std::list<std::wstring> listedDevices = std::list<std::wstring>();

		VideoHelper();
		~VideoHelper();

		void Shutdown();

		/// <summary>
		/// Hardware get witdth. Returns 0 on fail.
		/// </summary>
		/// <returns></returns>
		int GetCameraWidthWin32();
		int GetCameraHeightWin32();

		/// <summary>
		/// The whole open and capture. Only opens if needed.
		/// First call is rather sloooooow, then fast after that.
		/// Copies currentImage and currentImageLowRes to their respective last... versions.
		/// Sets currentImage to what the camer sees. Also scales and sets currentImageLowRes.
		/// </summary>
		bool CaptureFrame();

		HRESULT EnumerateDevices();
	};
}
