///////////////////////////////////////////////////////////////////////////////
// Name:        convertmattowxbmp.h
// Purpose:     Converts OpenCV bitmap (Mat) stored as BGR CVU8 to wxBitmap
// Author:      PB
// Created:     2020-09-16
// Copyright:   (c) 2020 PB
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////


#ifndef CONVERTMATTOWXBMP_H
#define CONVERTMATTOWXBMP_H

#include "SRSUnitDisplayModes.h"

// forward declarations
namespace cv { class Mat; }
class wxBitmap;

/**
    @param matBitmap
        Its data must be encoded as BGR CV_8UC3, which is
        probably the most common format for OpenCV images.
    @param bitmap
        It must be initialized to the same width and height as matBitmap
        and its depth must be 24.
    @return @true if the conversion succeeded, @false otherwise.


    On MS Windows, a MSW-optimized version is used if possible,
    the portable one otherwise. In my testing on MSW with
    3840x2160 image in the Release build, the optimized version
    was about 25% faster then the portable one. MSW-optimized version
    is used when bitmap is a DIB and its width modulo 4 is 0.

    In my testing on MSW with MSVS using 3840x2160 image, the portable
    version of conversion function in the Debug build was more then
    60 times slower than in the Release build.

    At least on MSW, initializing a wxBitmap takes quite some
    time. If you are processing images of the same size in a loop
    (e.g., frames of a video file), I recommend initializing the
    wxBitmap outside the loop and reusing it in the loop instead
    of creating it every time inside the loop.
*/
bool ConvertMatBitmapTowxBitmap_CV_8UC3(const cv::Mat& matBitmap, wxBitmap& bitmap);

/// <summary>
/// pixelScale is the pixel value conversion, e.g. convert neuron 0.0 to 1.0 to RGB 0 to 255.
/// scaleX and scaleY are how much the image is scalled. Default is 1.0 for both, but you can
/// scale very small concept maps up for the UI. See use in MonitorFrame.cpp
/// </summary>
/// <param name="matBitmap"></param>
/// <param name="w"></param>
/// <param name="h"></param>
/// <param name="bitmap"></param>
/// <param name="pixelScale"></param>
/// <param name="scaleX"></param>
/// <param name="scaleY"></param>
/// <returns></returns>
bool ConvertMatBitmapTowxBitmap_CV_32FC1(const cv::Mat& matBitmap, const int w, const int h, 
    wxBitmap& bitmap, 
    const float pixelScale = 255.0f, const float scaleX = 1.0f, const float scaleY = 1.0f, 
    const SRS22::SRSUnitDisplayModes UIHint = SRS22::SRSUnitDisplayModes::COLOR);

/// <summary>
/// Make a bitmap that is black with a dot where the two values as an X,Y coordinate are.
/// 0,0 is the upper left.
/// </summary>
/// <param name="matBitmap"></param>
/// <param name="w"></param>
/// <param name="h"></param>
/// <param name="bitmap"></param>
/// <returns></returns>
bool Convert2ValueMatBitmapTowxBitmap_CV_32FC1(
    const cv::Mat& matBitmap, const int w, const int h, wxBitmap& bitmap,
    const float pixelScale = 255.0f, const float scaleX = 1.0f, const float scaleY = 1.0f,
    const SRS22::SRSUnitDisplayModes UIHint = SRS22::SRSUnitDisplayModes::COLOR);

#endif // #ifndef CONVERTMATTOWXBMP_H