#pragma once
#include <windows.h>
#include "IOCommon.h"
#include "../Rect.h"

namespace SRS22 {
	class ScreenInputIO : public IOCommon
	{
		HBITMAP snapshotData = NULL;
		BITMAPINFOHEADER snapshotDataHeader;
		HANDLE snapshotDataHeaderDIB = NULL;

		BITMAPINFOHEADER CreateBitmapHeader(int width, int height);
		// From Microsoft's web site for more generic image dump.
		PBITMAPINFO CreateBitmapInfoStruct(HBITMAP hBmp);
		// From Microsoft's web site for more generic image dump.
		// 0 on success, else error number.
		int CreateBMPFile(LPTSTR pszFile, PBITMAPINFO pbi, HBITMAP hBMP, HDC hDC);
		int w;
		int h;

	public:

		std::recursive_mutex snapshotDataLock;

		// 8UC4 : dims=2 rows=1080 cols=2560"
		cv::Mat currentScreen;
		cv::Mat previousScreen;

		// 8UC4 : dims=2 rows=270 cols=640"
		cv::Mat currentScreenLowRes;
		cv::Mat previousScreenLowRes;
		cv::Mat currentAbsDifferenceLowRes;

		// My (R Keene) screen is 2560 x 1080
		static const int AbsDiffWidth = 2560 / 4;
		static const int AbsDiffHeight = 1080 / 4;

		ScreenInputIO();
		~ScreenInputIO();

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

		/// <summary>
		/// Get the screen size from Win32 calls. Not a cached answer.
		/// </summary>
		/// <returns></returns>
		int GetScreenWidthWin32();
		int GetScreenHeightWin32();

		/// <summary>
		/// Get screen size, as cached. Init sets up the cached values.
		/// </summary>
		/// <returns></returns>
		int GetScreenWidth() { return w; }
		int GetScreenHeight() { return h; }
		Rect GetScreenRect() { return Rect(0, 0, w, h); }

		/// <summary>
		/// Snaps the whole screen into  HBITMAP snapshotData.
		/// Can do 100 snapshots in about 3 seconds on my machine.
		/// AMD Ryzen 9 3900X 12-Core Processor, 3793 Mhz, 12 Cores, 24 Logical Processors)
		/// NVIDIA GeForce RTX 2070 SUPER.
		///
		/// Called in Brain::Tick() in PreTick() where screenInput PreTick gets called.
		/// </summary>
		/// <returns></returns>
		bool TakeScreenSnapshot();

		bool IsCorrectSize(cv::Mat& m);
		cv::Mat GetCorrectSizeMat();
		/// <summary>
		/// COPY currentScreen snapshot to outMat.
		/// </summary>
		/// <param name="outMat"></param>
		void GetCurrentScreen(cv::Mat& outMat);

		/// <summary>
		/// Gets a reference to the currentScreen Matrix. Treat this as read only!
		/// </summary>
		/// <returns></returns>
		cv::Mat& GetCurrentScreenRaw();
		/// <summary>
		/// CV_8UC3 640(cols) x 480(rows)
		/// </summary>
		cv::Mat GetPreviousScreen() { return previousScreen; }
		/// <summary>
		/// CV_8UC3 64(cols) x 48(rows)
		/// </summary>
		cv::Mat GetCurrentScreenLowRes() { return currentScreenLowRes; }
		/// <summary>
		/// CV_8UC3 64(cols) x 48(rows)
		/// </summary>
		cv::Mat GetPreviousScreenLowRes() { return previousScreenLowRes; }
		/// <summary>
		/// Copy a sub rectangle from current screen to outM.
		/// </summary>
		/// <param name="outM"></param>
		/// <param name="centerPoint"></param>
		void GetSubRect(cv::Mat& outM, const Rect& region);

		/// <summary>
		/// Does a cv::imshow on the current screen.
		/// </summary>
		void DebugCurrentScreen() {
			cv::imshow(std::string("Debug Current Scrren"), currentScreen);
		}
	};
}
