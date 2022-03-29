#pragma once
#include "SRS22UIgen.h"
class TopVideoFrame :
    public TopVideoFrameGen
{
public:
    TopVideoFrame(wxWindow* parent);
    ~TopVideoFrame();

    void OnClose(wxCloseEvent& event) override;
};

