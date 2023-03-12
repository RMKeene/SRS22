#pragma once
#include <mmeapi.h>
#include "soloud.h"
#include <soloud_wav.h>
#include <memory>
#include <string>

typedef PVOID HWAVELIB;

namespace SRS22 {
	class WaveOutputHelper;
	typedef WaveOutputHelper* WaveOutputHelperH;

	class WaveOutputHelper
	{
		SoLoud::Soloud soloudInst;
	public:
		static WaveOutputHelperH globalSingleton;

		WaveOutputHelper();
		~WaveOutputHelper();

		void Init();
		void UnInit();

		SoLoud::Wav* LoadSoLoudWav(std::string fileName);

		void Play(SoLoud::Wav& wav);
	};
}
