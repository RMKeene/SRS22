#include "AudioCaptureIO.h"

namespace SRS22 {
    AudioCaptureIO::AudioCaptureIO() : IOCommon(std::string("AudioCaptureIO")) {

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
        IOCommon::PreTick();
    }

    void AudioCaptureIO::PostTick() {
        IOCommon::PostTick();
    }

    void AudioCaptureIO::UnitTest() {

    }

    void AudioCaptureIO::CaptureSegment() {

    }

}
