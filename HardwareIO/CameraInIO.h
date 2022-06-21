#pragma once
#include "IOCommon.h"
#include "../Rect.h"
#include "VideoHelper.h"

namespace SRS22 {
	class CameraInIO : IOCommon
	{
	public:
		VideoHelper vidHelper;

		int w = 0;
		int h = 0;

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
		cv::Mat getCurrentImage() { return vidHelper.currentImage; }
		cv::Mat getPreviousImage() { return vidHelper.previousImage; }

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
			cv::imshow(std::string("Debug Current Scrren"), vidHelper.currentImage);
		}


		void UnitTest();
	};

}

