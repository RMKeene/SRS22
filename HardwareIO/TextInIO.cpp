#include "TextInIO.h"

namespace SRS22 {
    TextInIO::TextInIO() : IOCommon() {

    }

    TextInIO::~TextInIO() {

    }

    bool TextInIO::Init() {
        IOCommon::Init();
        return true;
    }

    void TextInIO::Shutdown() {
        IOCommon::Shutdown();
    }

    void TextInIO::PreTick() {

    }

    void TextInIO::PostTick() {

    }

    void TextInIO::UnitTest() {

    }
}
