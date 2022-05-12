#pragma once
#include <windows.h>
#include "IOCommon.h"

namespace SRS22 {

	class ScreenInputIO : public IOCommon
	{
		BITMAPINFOHEADER CreateBitmapHeader(int width, int height);
		// From Microsoft's web site for more generic image dump.
		PBITMAPINFO CreateBitmapInfoStruct(HBITMAP hBmp);
		// From Microsoft's web site for more generic image dump.
		// 0 on success, else error number.
		int CreateBMPFile(LPTSTR pszFile, PBITMAPINFO pbi, HBITMAP hBMP, HDC hDC);
	public:
		int w;
		int h;
		HBITMAP snapshotData = NULL;
		BITMAPINFOHEADER snapshotDataHeader;
		HANDLE snapshotDataHeaderDIB = NULL;
		std::recursive_mutex snapshotDataLock;

		ScreenInputIO();
		~ScreenInputIO();

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

		int GetScreenWidth();
		int GetScreenHeight();
		/// <summary>
		/// Snaps the whole screen into  HBITMAP snapshotData.
		/// Can do 100 snapshots in about 3 seconds on my machine.
		/// AMD Ryzen 9 3900X 12-Core Processor, 3793 Mhz, 12 Cores, 24 Logical Processors)
		/// NVIDIA GeForce RTX 2070 SUPER
		/// </summary>
		/// <returns></returns>
		bool TakeScreenSnapshot();

		void DumpCurrentScreenSnapshot(LPCTSTR fname);
	};

}
