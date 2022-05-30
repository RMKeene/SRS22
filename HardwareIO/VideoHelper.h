#pragma once
#include "../pch.h"
#include "IOCommon.h"

using namespace cv;

namespace SRS22 {
    class VideoHelper
    {
    public:
        cv::Mat previousImage;
        cv::Mat currentImage;
        cv::VideoCapture* cap = nullptr;

        std::string failureReason;

        VideoHelper();
        ~VideoHelper();

        void Shutdown();

        /// <summary>
        /// The whole open and capture. Only opes if needed. First call is rather sloooooow, then fast after that.
        /// </summary>
        bool CaptureFrame();
    };
}

