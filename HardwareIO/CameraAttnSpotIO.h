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

		const Rect& GetCameraRect() { return _cameraRect; }
		/// <summary>
		/// Where we are looking at in the Camera Rect.
		/// </summary>
		/// <returns></returns>
		const Rect& GetRect() { return rect; }
		/// <summary>
		/// Where we are loolking within Camera Rect. The center point of rect.
		/// </summary>
		Point GetPt() { return Point(rect.CenterX(), rect.CenterY()); }
		/// <summary>
		/// Set the centr of attention in the camera.
		/// </summary>
		/// <param name="pt"></param>
		void SetPt(Point& pt);
		/// <summary>
		/// Set the centr of attention in the camera.
		/// </summary>
		/// <param name="pt"></param>
		void SetPt(const int x, const int y);
		/// <summary>
		/// Set the center of attention in the camera.
		/// </summary>
		/// <param name="pt"></param>
		void SetPt(const float x, const float y);
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

