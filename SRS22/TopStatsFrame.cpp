#include "TopStatsFrame.h"
#include "HistogramWidget.h"
#include "GlobalWorld.h"

namespace SRS22 {

    TopStatsFrame::TopStatsFrame(wxWindow* parent) :
    StatsFrameGen(parent) {
    BrainH brain = GlobalWorld::GlobalWorldInstance.brains[0];
    m_chargeHist = new HistogramWidget(this, &brain->neuronChargeHist, brain->neuronChargeHist.name);
	m_chargeHist->SetBackgroundColour(wxColour(230, 240, 230)); 
    m_statsDataLayout->Add(this->m_chargeHist, 0, wxEXPAND | wxALL, wxBORDER_DEFAULT);
    SetSizer(this->m_statsDataLayout);
    Layout();
    }

	TopStatsFrame::~TopStatsFrame() {
	}

}