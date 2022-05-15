#pragma once
#include "IOCommon.h"
#include "../Rect.h"

/// <summary>
/// Designates the screen attention spot, much like stearing the eye around the screen.
/// Lets the ScreenFoveaMap know where we are looking.
/// </summary>
namespace SRS22 {
	class ScreenAttnSpotIO : IOCommon
	{
		Rect _rect;
		Point _p;
	public:

		ScreenAttnSpotIO();
		ScreenAttnSpotIO(Point p, Rect screenRect);
		~ScreenAttnSpotIO();

		/// <summary>
		/// Where we are loolking within cameraRect.
		/// </summary>
		Point getPt() { return _p; }
		Point setPt(Point& pt) { _p = pt; _rect.Clamp(_p);  return _p; }
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

		void UnitTest();
	};

}

