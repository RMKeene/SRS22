#include "AudioCaptureIO.h"

namespace SRS22 {
	AudioCaptureIO::AudioCaptureIO() : IOCommon() {
		IOCOMMON_SETCLASSNAME;
	}

	AudioCaptureIO::~AudioCaptureIO() {
	}

	bool AudioCaptureIO::Init() {
		IOCommon::Init();
		inputHelper.Init();
		return true;
	}

	void AudioCaptureIO::Shutdown() {
		MMTIME mmt;
		inputHelper.StopRecord(&inputHelper.waveInHandle, &mmt);
		inputHelper.CloseWaveIn(&inputHelper.waveInHandle);
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