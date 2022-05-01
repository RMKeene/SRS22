#pragma once
#include <mmeapi.h>
#include "soloud.h"
#include <soloud_wav.h>

typedef PVOID HWAVELIB;

namespace SRS22 {

	class WaveOutputHelper
	{
		SoLoud::Soloud soloudInst;
	public:
		SoLoud::Wav sampleTest;
		SoLoud::Wav sampleTest2;

	public:
		WaveOutputHelper();
		~WaveOutputHelper();

		void Init();
		void UnInit();

		void Play(SoLoud::Wav& wav);
	};

}
