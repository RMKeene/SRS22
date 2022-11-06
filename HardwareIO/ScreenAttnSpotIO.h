#pragma once
#include "AttnSpotBaseIO.h"
#include "../Rect.h"

/// <summary>
/// Designates the screen attention spot, much like steering the eye around the screen.
/// Lets the ScreenFoveaMap know where we are looking. Currently 128x128
/// </summary>
namespace SRS22 {
	class ScreenAttnSpotIO : public AttnSpotBaseIO
	{
	public:

		ScreenAttnSpotIO();
		ScreenAttnSpotIO(Point p, int w, int h, Rect screenRect);
		~ScreenAttnSpotIO();

		virtual bool Init(Point p, int w, int h, Rect screenRect) override;
		virtual void Shutdown() override;

		/// <summary>
		/// Called for each IOCommon at the start of tick in Brain.
		/// </summary>
		virtual void PreTick() override;
		/// <summary>
		/// Called for each IOCommon at the end of tick in Brain.
		/// </summary>
		virtual void PostTick() override;

		virtual void ForceToBeSubclassed() override;

		void UnitTest();
	};
}
