#pragma once
#include "SRS22UIgen.h"
#include "canvas.h"
#include <Mmsystem.h>

namespace SRS22 {

    class TopVideoFrame :
        public TopVideoFrameGen
    {
    public:
        MyCanvas canvas;
        cv::Mat previousImage;
        cv::Mat currentImage;
        cv::VideoCapture* cap;

        TopVideoFrame(wxWindow* parent);
        ~TopVideoFrame();

        void TakeImage();

        void OnActivate(wxActivateEvent& event) override;
        void OnClose(wxCloseEvent& event) override;
    };

}
