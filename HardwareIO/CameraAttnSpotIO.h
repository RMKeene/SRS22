#pragma once
#include "IOCommon.h"
#include "../Rect.h"

/// <summary>
/// Designates the attention spot, much like stearing the camera with motors.
/// Lets the CameraFoveaMap know where we are looking.
/// </summary>
namespace SRS22 {
	class CameraAttnSpotIO : IOCommon
	{
		Point _p;
		/// <summary>
		/// The whole camera scene rectangle, e.g. 640 x 480
		/// </summary>
		Rect _rect;

	public:
		CameraAttnSpotIO();
		CameraAttnSpotIO(Point p, Rect cameraRect);
		~CameraAttnSpotIO();

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

