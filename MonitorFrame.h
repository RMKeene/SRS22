#pragma once
#include "SRS22UIgen.h"
class MonitorFrame :
    public MonitorFrameGen
{
public:
	MonitorFrame(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("SRS22 - Monitor - Debug"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(1189, 739), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);
	~MonitorFrame();

};

