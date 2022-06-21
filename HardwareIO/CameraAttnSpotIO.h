#pragma once
#include "IOCommon.h"
#include "../Rect.h"

/// <summary>
/// Designates the attention spot, much like steering the camera with motors.
/// Lets the CameraFoveaMap know where we are looking.
/// </summary>
namespace SRS22 {
	class CameraAttnSpotIO : IOCommon
	{
		/// <summary>
		/// Overall camera rect we must stay inside of.
		/// </summary>
		SRS22::Rect _cameraRect;

		void ForceOnScreen();
	public:
		Rect rect;

		CameraAttnSpotIO();
		CameraAttnSpotIO(Point p, int w, int h, Rect cameraRect);
		~CameraAttnSpotIO();

		const SRS22::Rect& GetScreenRect() { return _cameraRect; }
		const SRS22::Rect& GetRect() { return rect; }

		/// <summary>
		/// Where we are loolking within cameraRect.
		/// </summary>
		Point GetPt() { return Point(rect.X, rect.Y); }
		void SetPt(Point& pt);
		bool Init(Point p, int w, int h, Rect cameraRect);
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

