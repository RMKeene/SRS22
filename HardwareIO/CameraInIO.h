#pragma once
#include "IOCommon.h"
#include "VideoHelper.h"

namespace SRS22 {
	class CameraInIO : IOCommon
	{
	public:
		VideoHelper vidHelper;

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

		bool AcquireFrame();
		cv::Mat getCurrentImage() { return vidHelper.currentImage; }
		cv::Mat getPreviousImage() { return vidHelper.previousImage; }

		void UnitTest();
	};

}

