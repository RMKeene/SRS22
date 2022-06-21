#pragma once
#include "IOCommon.h"
#include "../Rect.h"

/// <summary>
/// Designates the screen attention spot, much like steering the eye around the screen.
/// Lets the ScreenFoveaMap know where we are looking. Currently 128x128
/// </summary>
namespace SRS22 {
	class ScreenAttnSpotIO : IOCommon
	{
		/// <summary>
		/// Overall screen rect we must stay inside of.
		/// </summary>
		SRS22::Rect _screenRect;

		void ForceOnScreen();
	public:
		Rect rect;

		ScreenAttnSpotIO();
		ScreenAttnSpotIO(Point p, int w, int h, Rect screenRect);
		~ScreenAttnSpotIO();

		const SRS22::Rect& GetScreenRect() { return _screenRect; }
		const SRS22::Rect& GetRect() { return rect; }

		/// <summary>
		/// Where we are loolking within screenRect.
		/// </summary>
		Point GetPt() { return Point(rect.X, rect.Y); }
		void SetPt(Point& pt);
		bool Init(Point p, int w, int h, Rect screenRect);
		virtual void Shutdown();

		/// <summary>
		/// Called for each IOCommon at the start of tick in Brain.
		/// </summary>
		virtual void PreTick();
		/// <summary>
		/// Called for each IOCommon at the end of tick in Brain.
		/// </summary>
		virtual void PostTick();

		void UnitTest();
	};

}

