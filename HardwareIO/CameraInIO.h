#pragma once
#include "IOCommon.h"
#include "../Rect.h"
#include "../HardwareRaw/VideoHelper.h"

namespace SRS22 {
	class CameraInIO : IOCommon
	{
	public:
		VideoHelper vidHelper;

		int w = 0;
		int h = 0;

		/// 3 x 480(rows) x 640(cols) range 0.0 to 1.0 for RGB colors.
		cv::Mat currentFrame;
		cv::Mat previousFrame;

		/// 3 x 48(rows) x 64(cols) range 0.0 to 1.0 for RGB colors.
		cv::Mat currentFrameLowRes;
		cv::Mat previousFrameLowRes;
		cv::Mat currentAbsDifferenceLowRes;

		static const int AbsDiffWidth = 64;
		static const int AbsDiffHeight = 48;

		CameraInIO();
		~CameraInIO();

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

		/// <summary>
		/// Get the camera size from Win32 calls. Not a cached answer. Returns 0 on fail.
		/// </summary>
		/// <returns></returns>
		int GetCameraWidthWin32();
		int GetCameraHeightWin32();

		/// <summary>
		/// Get camera size as cached.
		/// </summary>
		/// <returns></returns>
		int GetCameraWidth() { return w; }
		int GetCameraHeight() { return h; }
		Rect GetCameraRect() { return Rect(0, 0, w, h); }

		bool AcquireFrame();
		/// <summary>
		/// CV_8UC3 640(cols) x 480(rows)
		/// </summary>
		cv::Mat getCurrentImage() { return vidHelper.currentImage3UC8; }
		/// <summary>
		/// CV_8UC3 640(cols) x 480(rows)
		/// </summary>
		cv::Mat getPreviousImage() { return vidHelper.previousImage3UC8; }
		/// <summary>
		/// CV_8UC3 64(cols) x 48(rows)
		/// </summary>
		cv::Mat getCurrentImageLowRes() { return vidHelper.currentImageLowRes3UC8; }
		/// <summary>
		/// CV_8UC3 64(cols) x 48(rows)
		/// </summary>
		cv::Mat getPreviousImageLowRes() { return vidHelper.previousImageLowRes3UC8; }

		/// <summary>
		/// Copy a sub rectangle from screen to outM.
		/// </summary>
		/// <param name="outM"></param>
		/// <param name="centerPoint"></param>
		void GetSubRect(cv::Mat& outM, const SRS22::Rect& region);

		/// <summary>
		/// Does a cv::imshow on the current screen.
		/// </summary>
		void DebugCurrentScreen() {
			cv::imshow(std::string("Debug Current Scrren"), vidHelper.currentImage3UC8);
		}

		void UnitTest();
	};
}
