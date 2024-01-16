#include "../../pch.h"
#include "PhonemesE.h"
#include "PhonemesIO.h"
#include "../HardwareRaw/WaveOutputHelper.h"

namespace SRS22 {
	PhonemesIO::PhonemesIO() : IOCommon() {
		IOCOMMON_SETCLASSNAME;
	}

	PhonemesIO::~PhonemesIO() {
	}

	void PhonemesIO::Shutdown() {
		IOCommon::Shutdown();
	}

	void PhonemesIO::PreTickHardwareAndIO() {
		IOCommon::PreTickHardwareAndIO();
	}

	void PhonemesIO::PostTickHardwareAndUI() {
		IOCommon::PostTickHardwareAndUI();
	}

	bool PhonemesIO::Init() {
		IOCommon::Init();
		std::string phonemesPath = "./phonemes/";
		// 0.010 seconds of silence.
		InitPhoneme(PhonemeE::SPACE, "SPACE", phonemesPath + "space010.wav");
		InitPhoneme(PhonemeE::A, "A", phonemesPath + "a.wav");
		InitPhoneme(PhonemeE::AE, "AE", phonemesPath + "ae.wav");
		InitPhoneme(PhonemeE::AH, "AH", phonemesPath + "ah.wav");
		InitPhoneme(PhonemeE::B, "B", phonemesPath + "b.wav");
		InitPhoneme(PhonemeE::D, "D", phonemesPath + "d.wav");
		InitPhoneme(PhonemeE::DH, "DH", phonemesPath + "dh.wav");
		InitPhoneme(PhonemeE::E, "E", phonemesPath + "e.wav");
		InitPhoneme(PhonemeE::EE, "EE", phonemesPath + "ee.wav");
		InitPhoneme(PhonemeE::F, "F", phonemesPath + "f.wav");
		InitPhoneme(PhonemeE::G, "G", phonemesPath + "g.wav");
		InitPhoneme(PhonemeE::I, "I", phonemesPath + "i.wav");
		InitPhoneme(PhonemeE::IE, "IE", phonemesPath + "ie.wav");
		InitPhoneme(PhonemeE::K, "K", phonemesPath + "k.wav");
		InitPhoneme(PhonemeE::L, "L", phonemesPath + "l.wav");
		InitPhoneme(PhonemeE::M, "M", phonemesPath + "m.wav");
		InitPhoneme(PhonemeE::N, "N", phonemesPath + "n.wav");
		InitPhoneme(PhonemeE::NY, "NY", phonemesPath + "ny.wav");
		InitPhoneme(PhonemeE::OH, "OH", phonemesPath + "oh.wav");
		InitPhoneme(PhonemeE::OO, "OO", phonemesPath + "oo.wav");
		InitPhoneme(PhonemeE::P, "P", phonemesPath + "p.wav");
		InitPhoneme(PhonemeE::R, "R", phonemesPath + "r.wav");
		InitPhoneme(PhonemeE::S, "S", phonemesPath + "s.wav");
		InitPhoneme(PhonemeE::SH, "SH", phonemesPath + "sh.wav");
		InitPhoneme(PhonemeE::T, "T", phonemesPath + "t.wav");
		InitPhoneme(PhonemeE::TH, "TH", phonemesPath + "th.wav");
		InitPhoneme(PhonemeE::V, "V", phonemesPath + "v.wav");
		InitPhoneme(PhonemeE::W, "W", phonemesPath + "w.wav");
		InitPhoneme(PhonemeE::X, "X", phonemesPath + "x.wav");
		InitPhoneme(PhonemeE::Z, "Z", phonemesPath + "z.wav");
		InitPhoneme(PhonemeE::ZH, "ZH", phonemesPath + "zh.wav");

		return true;
	}

	void PhonemesIO::PlayPhoneme(PhonemeE key) {
		if (key != PhonemeE::SPACE) {
			WaveOutputHelper::globalSingleton->Play(*(cache[key]->wav));
		}
	}

	std::string PhonemesIO::keyToString(PhonemeE key) {
		return std::string("Phoneme: ") + this->cache[key]->fileName;
	}

	void PhonemesIO::InitPhoneme(PhonemeE key, std::string name, std::string file) {
		cache[key] = std::make_shared<Phoneme>(key, name, file);
	}

	Phoneme::Phoneme(PhonemeE key, std::string name, std::string fileName) {
		this->key = key;
		this->fileName = fileName;
		this->name = name;
		// Kluge code, we don't ever delete these.
		this->wav = WaveOutputHelper::globalSingleton->LoadSoLoudWav(fileName);
	}

	Phoneme::~Phoneme() {
	}
}