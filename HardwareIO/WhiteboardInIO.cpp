#include "WhiteboardInIO.h"

namespace SRS22 {
    WhiteboardInIO::WhiteboardInIO() : IOCommon() {

    }

    WhiteboardInIO::~WhiteboardInIO() {

    }

    bool WhiteboardInIO::Init() {
        IOCommon::Init();
        return true;
    }

    void WhiteboardInIO::Shutdown() {
        IOCommon::Shutdown();
    }

    void WhiteboardInIO::PreTick() {

    }

    void WhiteboardInIO::PostTick() {

    }

    void WhiteboardInIO::UnitTest() {

    }
}
