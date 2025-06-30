#pragma once

#include "SRS22UIgen.h"



namespace SRS22 {

	class HistogramWidget;

	class TopStatsFrame :
		public StatsFrameGen
	{
	public:
		HistogramWidget* m_chargeHist;

		TopStatsFrame(wxWindow* parent);
		~TopStatsFrame();
	};

}