#include "HistogramWidget.h"
#include <wx/dcbuffer.h>

namespace SRS22 {

	wxBEGIN_EVENT_TABLE(HistogramWidget, wxPanel)
		EVT_PAINT(HistogramWidget::OnPaint)
		wxEND_EVENT_TABLE();

	HistogramWidget::HistogramWidget(wxWindow* parent, SRS22::Histogram* histogram, const wxString& title)
		: wxPanel(parent), m_histogram(histogram), m_title(title)
	{
		SetBackgroundStyle(wxBG_STYLE_PAINT);
		SetMinSize(wxSize(200, 80));
		SetMaxSize(wxSize(1400, 80));
	}

	void HistogramWidget::SetHistogram(SRS22::Histogram* histogram)
	{
		m_histogram = histogram;
		Refresh();
	}

	void HistogramWidget::RefreshHistogram()
	{
		Refresh();
	}

	void HistogramWidget::SetTitle(const wxString& title)
	{
		m_title = title;
		Refresh();
	}

	void HistogramWidget::OnPaint(wxPaintEvent& event)
	{
		if (!m_histogram) return;

		wxAutoBufferedPaintDC dc(this);
		wxSize size = GetClientSize();
		dc.Clear();

		wxFont titleFont = GetFont();
		int pts = titleFont.GetPointSize();
		int topMargin = 2;
		int bottomMargin = 2;
		int totalTopMargin = topMargin + pts + bottomMargin;
		int binCount = m_histogram->getBinCount();
		int totalCount = m_histogram->getSumOfBins();
		int maxBin = m_histogram->getMaxBinCount();
		std::string titleText = m_histogram->name + " - Total: " + std::to_string(totalCount) + ", Max: " + std::to_string(maxBin);

		// Draw the title at the top center
		if (!m_title.IsEmpty()) {
			titleFont.SetPointSize(pts);
			titleFont.SetWeight(wxFONTWEIGHT_NORMAL);
			dc.SetFont(titleFont);

			int textWidth, textHeight;
			dc.GetTextExtent(titleText, &textWidth, &textHeight);
			int x = (size.GetWidth() - textWidth) / 2;
			int y = 1; // Small margin from the top
			dc.DrawText(titleText, x, y);
		}

		if (binCount == 0) return;

		// Find max bin value for scaling
		int maxValue = m_histogram->getMaxBinCount();
		if (maxValue == 0) maxValue = 1;

		int barAreaHeight = size.GetHeight() - totalTopMargin;
		int barWidth = size.GetWidth() / binCount;

		for (int i = 0; i < binCount; ++i)
		{
			int binValue = m_histogram->getBinValue(i);
			int barHeight = (binValue * barAreaHeight) / maxValue;
			dc.SetBrush(*wxBLUE_BRUSH);
			dc.SetPen(*wxTRANSPARENT_PEN);
			dc.DrawRectangle(i * barWidth, size.GetHeight() - barHeight, barWidth - 2, barHeight);
		}
	}

} // namespace SRS22