#include "HistogramWidget.h"
#include <wx/dcbuffer.h>

namespace SRS22 {

	wxBEGIN_EVENT_TABLE(HistogramWidget, wxPanel)
		EVT_PAINT(HistogramWidget::OnPaint)
	wxEND_EVENT_TABLE()

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
		wxAutoBufferedPaintDC dc(this);
		wxSize size = GetClientSize();
		dc.Clear();

		// Draw the title at the top center
		if (!m_title.IsEmpty()) {
			wxFont titleFont = GetFont();
			titleFont.SetPointSize(titleFont.GetPointSize() + 2);
			titleFont.SetWeight(wxFONTWEIGHT_BOLD);
			dc.SetFont(titleFont);

			int textWidth, textHeight;
			dc.GetTextExtent(m_title, &textWidth, &textHeight);
			int x = (size.GetWidth() - textWidth) / 2;
			int y = 4; // Small margin from the top
			dc.DrawText(m_title, x, y);
		}

		if (!m_histogram) return;

		int binCount = m_histogram->getBinCount();
		if (binCount == 0) return;

		// Find max bin value for scaling
		int maxValue = 0;
		for (int i = 0; i < binCount; ++i)
			maxValue = std::max(maxValue, m_histogram->getBinValue(i));
		if (maxValue == 0) maxValue = 1;

		// Leave space for the title
		int topMargin = 28;
		int barAreaHeight = size.GetHeight() - topMargin;
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