#pragma once
#include "SRS22UIgen.h"

namespace SRS22 {

	class TopTextFrame :
		public TopTextFrameGen
	{
	public:
		TopTextFrame(wxWindow* parent);
		~TopTextFrame();

		void OnClose(wxCloseEvent& event) override;
	};

}
