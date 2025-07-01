#pragma once

#include "SRS22UIgen.h"



namespace SRS22 {

	class HistogramWidget;

	class TopStatsFrame :
		public StatsFrameGen
	{
	public:
		HistogramWidget* m_chargeHist;
		HistogramWidget* m_energyHist;
		HistogramWidget* m_weightHist;
		HistogramWidget* m_activityHist;
		HistogramWidget* m_ageHist;
		HistogramWidget* m_confidenceHist;

		TopStatsFrame(wxWindow* parent);
		~TopStatsFrame();
	};

}