#pragma once
#include "SRS22UIgen.h"
class WhiteboardFrame :
    public WhiteboardFrameGen
{
public:
    WhiteboardFrame(wxWindow* parent);
    ~WhiteboardFrame();

    void OnClose(wxCloseEvent& event) override;
};

