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

	m_energyHist = new HistogramWidget(this, &brain->neuronEnergyHist, brain->neuronEnergyHist.name);
	m_energyHist->SetBackgroundColour(wxColour(240, 230, 230));
	m_statsDataLayout->Add(this->m_energyHist, 0, wxEXPAND | wxALL, wxBORDER_DEFAULT);

	m_weightHist = new HistogramWidget(this, &brain->linkWeightHist, brain->linkWeightHist.name);
	m_weightHist->SetBackgroundColour(wxColour(230, 230, 240));
	m_statsDataLayout->Add(this->m_weightHist, 0, wxEXPAND | wxALL, wxBORDER_DEFAULT);

	m_activityHist = new HistogramWidget(this, &brain->linkActivityHist, brain->linkActivityHist.name);
	m_activityHist->SetBackgroundColour(wxColour(240, 240, 230));
	m_statsDataLayout->Add(this->m_activityHist, 0, wxEXPAND | wxALL, wxBORDER_DEFAULT);

	m_ageHist = new HistogramWidget(this, &brain->linkAgeHist, brain->linkAgeHist.name);
	m_ageHist->SetBackgroundColour(wxColour(230, 240, 240));
	m_statsDataLayout->Add(this->m_ageHist, 0, wxEXPAND | wxALL, wxBORDER_DEFAULT);

	m_confidenceHist = new HistogramWidget(this, &brain->linkConfidenceHist, brain->linkConfidenceHist.name);
	m_confidenceHist->SetBackgroundColour(wxColour(240, 230, 240));
	m_statsDataLayout->Add(this->m_confidenceHist, 0, wxEXPAND | wxALL, wxBORDER_DEFAULT);	

    SetSizer(this->m_statsDataLayout);
    Layout();
    }

	TopStatsFrame::~TopStatsFrame() {
	}

}