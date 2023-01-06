#pragma once

#include "../pch.h"
#include "IOCommon.h"
#include "PhonemesE.h"
#include <soloud_wav.h>
#include "../HardwareRaw/WaveInputHelper.h"

namespace SRS22 {
	class Phoneme {
	public:
		PhonemeE key;
		SoLoud::Wav* wav;
		std::string fileName;

		Phoneme(PhonemeE key, std::string name);
		~Phoneme();
	};

	typedef std::shared_ptr<Phoneme> PhonemeH;

	class PhonemesIO;
	typedef std::shared_ptr<PhonemesIO> PhonemesH;

	class PhonemesIO : IOCommon {
	public:
		std::map<PhonemeE, PhonemeH> cache;

		PhonemesIO();
		~PhonemesIO();

		virtual bool Init();
		virtual void Shutdown();

		/// <summary>
		/// Called for each IOCommon at the start of tick in Brain.
		/// </summary>
		virtual void PreTick();
		/// <summary>
		/// Called for each IOCommon at the end of tick in Brain.
		/// </summary>
		virtual void PostTick();

		void PlayPhoneme(PhonemeE key);

	private:
		void InitPhoneme(PhonemeE key, std::string file);
	};
}