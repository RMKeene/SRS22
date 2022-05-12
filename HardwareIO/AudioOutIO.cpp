#include "AudioOutIO.h"

namespace SRS22 {
    AudioOutIO::AudioOutIO() : IOCommon() {

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

    }

    void AudioOutIO::PostTick() {

    }

    void AudioOutIO::UnitTest() {

    }

    void AudioOutIO::CaptureSegment() {

    }


}
