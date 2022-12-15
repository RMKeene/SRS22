#pragma once

#include "../pch.h"
#include "PhonemesE.h"
#include <soloud_wav.h>
#include "WaveInputHelper.h"

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

	class Phonemes;
	typedef std::shared_ptr<Phonemes> PhonemesH;

	class Phonemes {
	public:
		std::map<PhonemeE, PhonemeH> cache;

		void Init();
		void InitPhoneme(PhonemeE key, std::string file);
		void PlayPhoneme(PhonemeE key);
		
		static PhonemesH globalPhonemes;
	};


}