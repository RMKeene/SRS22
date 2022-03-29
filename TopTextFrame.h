#pragma once
#include "SRS22UIgen.h"

class TopTextFrame :
	public TopTextFrameGen
{
public:
	TopTextFrame(wxWindow* parent);
	~TopTextFrame();

	void OnClose(wxCloseEvent& event) override;
};

