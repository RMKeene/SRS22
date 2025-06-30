#pragma once

#include <wx/wx.h>
#include "Histogram.h"

namespace SRS22 {
	class HistogramWidget : public wxPanel
	{
	public:
		HistogramWidget(wxWindow* parent, SRS22::Histogram* histogram, const wxString& title = wxEmptyString);

		void SetHistogram(SRS22::Histogram* histogram);
		void RefreshHistogram();
		void SetTitle(const wxString& title);

	protected:
		void OnPaint(wxPaintEvent& event);

	private:
		SRS22::Histogram* m_histogram;
		wxString m_title;

		wxDECLARE_EVENT_TABLE();
	};
}