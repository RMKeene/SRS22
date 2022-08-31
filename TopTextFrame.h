#pragma once
#include "SRS22UIgen.h"

namespace SRS22 {

	class TopTextFrame :
		public TopTextFrameGen
	{
	public:
		TopTextFrame(wxWindow* parent);
		~TopTextFrame();

		void OnTextInClearButton(wxCommandEvent& event) override;
		void OnInputTextKeyDown(wxKeyEvent& event) override;
		void OnInputText(wxCommandEvent& event) override;
		void OnInputTextEnter(wxCommandEvent& event) override;
		void OnInputTextMaxLen(wxCommandEvent& event) override;
		void OnTextOutClearButton(wxCommandEvent& event) override;

		void OnClose(wxCloseEvent& event) override;
	};

}
