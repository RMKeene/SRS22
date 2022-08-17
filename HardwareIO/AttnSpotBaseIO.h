#pragma once
#include "IOCommon.h"
#include "../Rect.h"

/// <summary>
/// Designates an attention spot within some view, much like steering the camera with motors.
/// Lets the CameraFoveaMap and ScreenFoveaMap know where we are looking.
/// We use "view" here to mean whatever view we are looking at. 
/// It could be a camera, or a screen, or a web browser view etc.
/// 
/// A virtual class. Can not be instanced directly.
/// </summary>
namespace SRS22 {
	class AttnSpotBaseIO : public IOCommon
	{
		/// <summary>
		/// Overall view rect we must stay inside of.
		/// </summary>
		SRS22::Rect _viewRect;

		void ForceOnScreen();
	public:
		Rect rect;

		AttnSpotBaseIO();
		AttnSpotBaseIO(Point p, int w, int h, Rect viewRect);
		~AttnSpotBaseIO();

		const Rect& GetViewRect() { return _viewRect; }
		/// <summary>
		/// Where we are looking at in the Camera Rect.
		/// </summary>
		/// <returns></returns>
		const Rect& GetRect() { return rect; }
		/// <summary>
		/// Where we are loolking within View Rect. The center point of rect.
		/// </summary>
		Point GetPt() { return Point(rect.CenterX(), rect.CenterY()); }
		/// <summary>
		/// Set the centr of attention in the view.
		/// </summary>
		/// <param name="pt"></param>
		void SetPt(Point& pt);
		/// <summary>
		/// Set the centr of attention in the view.
		/// </summary>
		/// <param name="pt"></param>
		void SetPt(const int x, const int y);
		/// <summary>
		/// Set the center of attention in the view.
		/// </summary>
		/// <param name="pt"></param>
		void SetPt(const float x, const float y);
		virtual bool Init(Point p, int w, int h, Rect viewRect);
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
		/// We just have this to make it impossible to instance this class without subclassing.
		/// Is there a better way?
		/// </summary>
		virtual void ForceToBeSubclassed() = 0;

		void UnitTest();
	};

}
