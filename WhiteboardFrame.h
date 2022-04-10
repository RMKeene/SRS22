#pragma once
#include "SRS22UIgen.h"
#include "canvas.h"

namespace SRS22 {

	class WhiteboardFrame :
		public WhiteboardFrameGen
	{
	public:
		wxBrush whiteboardBrush;
		MyCanvas canvas;

		WhiteboardFrame(wxWindow* parent);
		~WhiteboardFrame();

		void OnClose(wxCloseEvent& event) override;

		void OnWhiteButton(wxCommandEvent& event) override;
		void OnBlackButton(wxCommandEvent& event) override;
		void OnRedButton(wxCommandEvent& event) override;
		void OnGreenButton(wxCommandEvent& event) override;
		void OnBlueButton(wxCommandEvent& event) override;
		void OnYellowButton(wxCommandEvent& event) override;
		void OnCyanButton(wxCommandEvent& event) override;
		void OnMagentaButton(wxCommandEvent& event) override;
		void OnWhiteboardClearButton(wxCommandEvent& event) override;

	};

}
