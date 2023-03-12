#include "WaveOutputHelper.h"
#include "../StringConversionHelpers.h"
#include "soloud.h"
#include <stdexcept>

namespace SRS22 {
	SoLoud::Soloud soloudInst;

	WaveOutputHelperH WaveOutputHelper::globalSingleton = nullptr;

	WaveOutputHelper::WaveOutputHelper() {
		globalSingleton = this;
	}

	WaveOutputHelper::~WaveOutputHelper() {
	}

	void WaveOutputHelper::Init() {
		soloudInst.init();
	}

	void WaveOutputHelper::UnInit() {
		soloudInst.deinit();
	}

	SoLoud::Wav* WaveOutputHelper::LoadSoLoudWav(std::string fileName) {
		SoLoud::Wav* w = new SoLoud::Wav();
		SoLoud::result res = w->load(fileName.c_str());
		if (res != 0)
			throw std::logic_error(std::string("Invalid WAV file name: ") + fileName);
		return w;
	}

	void WaveOutputHelper::Play(SoLoud::Wav& wav) {
		soloudInst.play(wav);
	}
}