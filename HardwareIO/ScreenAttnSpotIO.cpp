#include "ScreenAttnSpotIO.h"

namespace SRS22 {
    ScreenAttnSpotIO::ScreenAttnSpotIO() : IOCommon() {

    }

    ScreenAttnSpotIO::ScreenAttnSpotIO(Point p, Rect screenRect) : IOCommon(), _p(p), _rect(screenRect)
    {
        _rect.Clamp(_p);
    }

    ScreenAttnSpotIO::~ScreenAttnSpotIO() {

    }

    bool ScreenAttnSpotIO::Init() {
        IOCommon::Init();
        return true;
    }

    void ScreenAttnSpotIO::Shutdown() {
        IOCommon::Shutdown();
    }

    void ScreenAttnSpotIO::PreTick() {
        IOCommon::PreTick();
    }

    void ScreenAttnSpotIO::PostTick() {
        IOCommon::PostTick();
    }

    void ScreenAttnSpotIO::UnitTest() {

    }



}
