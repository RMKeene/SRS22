#pragma once
#include "SRS22UIgen.h"
#include "canvas.h"
#include <Mmsystem.h>
#include "ClassPredefines.h"
#include <wx/dcclient.h>

namespace SRS22 {

    class TopVideoFrame :
        public TopVideoFrameGen, MyCanvasPainter
    {
    public:
        MyCanvas canvas;

        TopVideoFrame(wxWindow* parent);
        ~TopVideoFrame();

        void TakeImage(Brain& brain);

        void OnActivate(wxActivateEvent& event) override;
        void OnClose(wxCloseEvent& event) override;

        void OnPostPaint(wxPaintDC* DC, wxPaintEvent& event) override;
    };

}
