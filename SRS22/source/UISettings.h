#pragma once
#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>



/// <summary>
/// Rather than define the many settings in WxWidgets UI editor, we instead define them here and add them programmatically on startup.
/// </summary>

namespace SRS22 {

	class LabeledTextCtrl : public wxBoxSizer {
	public:
		int padding = 5;
		const wxString& m_label;
		wxTextCtrl* m_textCtrl;

		LabeledTextCtrl(wxWindow* parent, int orientation, const wxString& label) :
			wxBoxSizer(orientation),
			m_label(label)
		{
			wxStaticText* staticText = new wxStaticText(parent, wxID_ANY, label);
			Add(staticText, 0, wxALL | wxALIGN_CENTER_VERTICAL, padding);
			m_textCtrl = new wxTextCtrl(parent, wxID_ANY, "", wxDefaultPosition, wxSize(50, -1));
			Add(m_textCtrl, 0, wxALL | wxALIGN_CENTER_VERTICAL, padding);
			SetMinSize(wxSize(20, 12));
		}

		void SetError() {
			m_textCtrl->SetBackgroundColour(wxColor(255, 50, 50));
		}

		void SetOk() {
			m_textCtrl->SetBackgroundColour(wxColor(255, 255, 255));
		}
	};

	class IntLabeledTextCtrl : public LabeledTextCtrl {
	public:
		int* m_value;
		int m_minValue;
		int m_maxValue;

		IntLabeledTextCtrl(wxWindow* parent, const wxString& label, int* value, int minValue, int maxValue, int defaultValue) :
			LabeledTextCtrl(parent, wxHORIZONTAL, label),
			m_value(value),
			m_minValue(minValue),
			m_maxValue(maxValue)
		{
			m_textCtrl->SetValue(wxString::Format("%d", defaultValue));
		}

		bool Validate() {
			long f;
			if (!m_textCtrl->GetValue().ToLong(&f) || f < m_minValue || f > m_maxValue) {
				SetError();
				return false;
			}
			SetOk();
			*m_value = (int)f;
			return true;
		}
	};

	class FloatLabeledTextCtrl : public LabeledTextCtrl { 
	public:
		float* m_value;
		float m_minValue;
		float m_maxValue;
		FloatLabeledTextCtrl(wxWindow* parent, const wxString& label, float* value, float minValue, float maxValue, float defaultValue) :
			LabeledTextCtrl(parent, wxHORIZONTAL, label),
			m_value(value),
			m_minValue(minValue),
			m_maxValue(maxValue)
		{
			m_textCtrl->SetValue(wxString::Format("%g", defaultValue));
		}
		bool Validate() {
			double f;
			if (!m_textCtrl->GetValue().ToDouble(&f) || f < m_minValue || f > m_maxValue) {
				SetError();
				return false;
			}
			SetOk();
			*m_value = (float)f;
			return true;
		}
	};

	class DoubleLabeledTextCtrl : public LabeledTextCtrl {
	public:
		double* m_value;
		double m_minValue;
		double m_maxValue;
		DoubleLabeledTextCtrl(wxWindow* parent, const wxString& label, double* value, double minValue, double maxValue, double defaultValue) :
			LabeledTextCtrl(parent, wxHORIZONTAL, label),
			m_value(value),
			m_minValue(minValue),
			m_maxValue(maxValue)
		{
			m_textCtrl->SetValue(wxString::Format("%g", defaultValue));
		}
		bool Validate() {
			double f;
			if (!m_textCtrl->GetValue().ToDouble(&f) || f < m_minValue || f > m_maxValue) {
				SetError();
				return false;
			}
			SetOk();
			*m_value = f;
			return true;
		}
	};

}