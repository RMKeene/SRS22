#include "PhonemesE.h"
#include "PhonemesIO.h"
#include "WaveOutputHelper.h"

namespace SRS22 {
	PhonemesIO::PhonemesIO() : IOCommon() {
		IOCOMMON_SETCLASSNAME;
	}

	PhonemesIO::~PhonemesIO() {
	}

	void PhonemesIO::Shutdown() {
		IOCommon::Shutdown();
	}

	void PhonemesIO::PreTick() {
		IOCommon::PreTick();
	}

	void PhonemesIO::PostTick() {
		IOCommon::PostTick();
	}

	bool PhonemesIO::Init() {
		IOCommon::Init();
		std::string phonemesPath = "./phonemes/";
		InitPhoneme(PhonemeE::A, phonemesPath + "a.wav");
		InitPhoneme(PhonemeE::AE, phonemesPath + "ae.wav");
		InitPhoneme(PhonemeE::AH, phonemesPath + "ah.wav");
		InitPhoneme(PhonemeE::B, phonemesPath + "b.wav");
		InitPhoneme(PhonemeE::D, phonemesPath + "d.wav");
		InitPhoneme(PhonemeE::DH, phonemesPath + "dh.wav");
		InitPhoneme(PhonemeE::E, phonemesPath + "e.wav");
		InitPhoneme(PhonemeE::EE, phonemesPath + "ee.wav");
		InitPhoneme(PhonemeE::F, phonemesPath + "f.wav");
		InitPhoneme(PhonemeE::G, phonemesPath + "g.wav");
		InitPhoneme(PhonemeE::I, phonemesPath + "i.wav");
		InitPhoneme(PhonemeE::IE, phonemesPath + "ie.wav");
		InitPhoneme(PhonemeE::K, phonemesPath + "k.wav");
		InitPhoneme(PhonemeE::L, phonemesPath + "l.wav");
		InitPhoneme(PhonemeE::M, phonemesPath + "m.wav");
		InitPhoneme(PhonemeE::N, phonemesPath + "n.wav");
		InitPhoneme(PhonemeE::NY, phonemesPath + "ny.wav");
		InitPhoneme(PhonemeE::OH, phonemesPath + "oh.wav");
		InitPhoneme(PhonemeE::OO, phonemesPath + "oo.wav");
		InitPhoneme(PhonemeE::P, phonemesPath + "p.wav");
		InitPhoneme(PhonemeE::R, phonemesPath + "r.wav");
		InitPhoneme(PhonemeE::S, phonemesPath + "s.wav");
		InitPhoneme(PhonemeE::SH, phonemesPath + "sh.wav");
		InitPhoneme(PhonemeE::T, phonemesPath + "t.wav");
		InitPhoneme(PhonemeE::TH, phonemesPath + "th.wav");
		InitPhoneme(PhonemeE::V, phonemesPath + "v.wav");
		InitPhoneme(PhonemeE::W, phonemesPath + "w.wav");
		InitPhoneme(PhonemeE::X, phonemesPath + "x.wav");
		InitPhoneme(PhonemeE::Z, phonemesPath + "z.wav");
		InitPhoneme(PhonemeE::ZH, phonemesPath + "zh.wav");

		return true;
	}

	void PhonemesIO::PlayPhoneme(PhonemeE key) {
		if (key != PhonemeE::SPACE) {
			WaveOutputHelper::globalSingleton->Play(*(cache[key]->wav));
		}
	}

	void PhonemesIO::InitPhoneme(PhonemeE key, std::string file) {
		cache[key] = std::make_shared<Phoneme>(key, file);
	}

	Phoneme::Phoneme(PhonemeE key, std::string fileName) {
		this->key = key;
		this->fileName = fileName;
		// Kluge code, we don't ever delete these.
		this->wav = WaveOutputHelper::globalSingleton->LoadSoLoudWav(fileName);
	}

	Phoneme::~Phoneme() {
	}
}