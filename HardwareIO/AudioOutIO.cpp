#include "AudioOutIO.h"

namespace SRS22 {
    AudioOutIO::AudioOutIO() : IOCommon(std::string("AudioOutIO")) {

    }

    AudioOutIO::~AudioOutIO() {

    }

    bool AudioOutIO::Init() {
        IOCommon::Init();
        outHelper.Init();
        return true;
    }

    void AudioOutIO::Shutdown() {
        outHelper.UnInit();
        IOCommon::Shutdown();
    }

    void AudioOutIO::PreTick() {
        IOCommon::PreTick();
    }

    void AudioOutIO::PostTick() {
        IOCommon::PostTick();
    }

    void AudioOutIO::UnitTest() {

    }

    void AudioOutIO::CaptureSegment() {

    }


}
