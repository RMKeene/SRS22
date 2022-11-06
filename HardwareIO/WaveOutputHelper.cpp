#include "WaveOutputHelper.h"
#include "../StringConversionHelpers.h"
#include "soloud.h"

namespace SRS22 {
	SoLoud::Soloud soloudInst;

	WaveOutputHelper::WaveOutputHelper() {
	}

	WaveOutputHelper::~WaveOutputHelper() {
	}

	void WaveOutputHelper::Init() {
		soloudInst.init();
		sampleTest.load("C:\\SRS22\\SRS22\\train.wav");
		sampleTest2.load("C:\\SRS22\\SRS22\\mysound.wav");
	}

	void WaveOutputHelper::UnInit() {
		soloudInst.deinit();
	}

	void WaveOutputHelper::Play(SoLoud::Wav& wav) {
		soloudInst.play(wav);
	}
}