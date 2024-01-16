#include "../../pch.h"
#include "AudioOutIO.h"

namespace SRS22 {
	AudioOutIO::AudioOutIO() : IOCommon() {
		IOCOMMON_SETCLASSNAME;
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

	void AudioOutIO::PreTickHardwareAndIO() {
		IOCommon::PreTickHardwareAndIO();
	}

	void AudioOutIO::PostTickHardwareAndUI() {
		IOCommon::PostTickHardwareAndUI();
	}

	void AudioOutIO::UnitTest() {
	}

	void AudioOutIO::PlayWav(SoLoud::Wav& w) {
		outHelper.Play(w);
	}
}