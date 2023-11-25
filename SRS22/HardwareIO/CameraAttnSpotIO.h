#pragma once
#include "AttnSpotBaseIO.h"
#include "../Rect.h"

/// <summary>
/// Designates the attention spot, much like steering the camera with motors.
/// Lets the CameraFoveaMap know where we are looking.
/// </summary>
namespace SRS22 {
	class CameraAttnSpotIO : public AttnSpotBaseIO
	{
	public:
		static bool freezeAttnSpotPosition;
		CameraAttnSpotIO();
		CameraAttnSpotIO(Point p, int w, int h, Rect cameraRect);
		~CameraAttnSpotIO();

		virtual bool Init(Point p, int w, int h, Rect cameraRect) override;
		virtual void Shutdown() override;

		/// <summary>
		/// Called for each IOCommon at the start of tick in Brain.
		/// </summary>
		virtual void PreTickHardwareAndIO() override;
		/// <summary>
		/// Called for each IOCommon at the end of tick in Brain.
		/// </summary>
		virtual void PostTickHardwareAndUI() override;

		virtual void ForceToBeSubclassed() override;

		void UnitTest();
	};
}
