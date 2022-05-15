#include "WhiteboardOutIO.h"

namespace SRS22 {
    WhiteboardOutIO::WhiteboardOutIO() : IOCommon() {

    }

    WhiteboardOutIO::~WhiteboardOutIO() {

    }

    bool WhiteboardOutIO::Init() {
        IOCommon::Init();
        return true;
    }

    void WhiteboardOutIO::Shutdown() {
        IOCommon::Shutdown();
    }

    void WhiteboardOutIO::PreTick() {
        IOCommon::PreTick();
    }

    void WhiteboardOutIO::PostTick() {
        IOCommon::PostTick();
    }

    void WhiteboardOutIO::UnitTest() {

    }
}
