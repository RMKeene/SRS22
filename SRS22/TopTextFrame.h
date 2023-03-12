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
		void OnTextInChar(wxKeyEvent& event) override;
		void OnTextOutClearButton(wxCommandEvent& event) override;
		void TextWindowTick(wxTimerEvent& event) override;

		void OnClose(wxCloseEvent& event) override;
	};
}
