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
        IOCommon::PreTick();
    }

    void TextInIO::PostTick() {
        IOCommon::PostTick();
    }

    void TextInIO::UnitTest() {

    }
}
