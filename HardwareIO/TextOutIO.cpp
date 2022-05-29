#include "TextOutIO.h"

namespace SRS22 {
    TextOutIO::TextOutIO() : IOCommon() {
        IOCOMMON_SETCLASSNAME;

    }

    TextOutIO::~TextOutIO() {

    }

    bool TextOutIO::Init() {
        IOCommon::Init();
        return true;
    }

    void TextOutIO::Shutdown() {
        IOCommon::Shutdown();
    }

    void TextOutIO::PreTick() {
        IOCommon::PreTick();
    }

    void TextOutIO::PostTick() {
        IOCommon::PostTick();
    }

    void TextOutIO::UnitTest() {

    }
}
