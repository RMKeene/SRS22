#include "AudioCaptureIO.h"

namespace SRS22 {
    AudioCaptureIO::AudioCaptureIO() : IOCommon() {

    }

    AudioCaptureIO::~AudioCaptureIO() {

    }

    bool AudioCaptureIO::Init() {
        IOCommon::Init();
        inputHelper.Init();
        return true;
    }

    void AudioCaptureIO::Shutdown() {
        IOCommon::Shutdown();
    }

    void AudioCaptureIO::PreTick() {

    }

    void AudioCaptureIO::PostTick() {

    }

    void AudioCaptureIO::UnitTest() {

    }

    void AudioCaptureIO::CaptureSegment() {

    }

}
