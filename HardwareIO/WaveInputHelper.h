#pragma once
#include <mmeapi.h>

namespace SRS22 {

	class WaveInputHelper
	{
	public:
		WAVEFORMATEX waveInFormat;
		HWAVEIN waveInHandle;
		WAVEHDR waveHeader;

		WaveInputHelper();
		~WaveInputHelper();

		void Init();

		int SetWaveFormat(WAVEFORMATEX* wf, int wFormatTag, int nChannels, int nSamplesPerSec,
			int nBlockAlign, int wBitsPerSample, int cbSize);

		// Open wave input channel
		int OpenWaveIn(HWAVEIN*, WAVEFORMATEX*);

		// Prepare Wave In Header and allocate memory
		int PrepareWaveIn(HWAVEIN* hWaveIn, WAVEHDR* waveHeader, DWORD dataSize);

		// Start recording speech
		int StartRecord(HWAVEIN* hWaveIn);

		// Stop recording speech
		int StopRecord(HWAVEIN* hWaveIn, MMTIME* mmTime);

		// Save recorded speech to file
		int SaveRecordtoFile(const char* fileName, WAVEFORMATEX* wf, HWAVEIN* hWaveIn, WAVEHDR* waveHeader, MMTIME* mmTime);

		// Release wave in memory
		int ReleaseWaveIn(HWAVEIN* hWaveIn, WAVEHDR* waveHeader);

		// Close Wave in channel
		int CloseWaveIn(HWAVEIN* hWaveIn);

		// str2num
		DWORD FCC(LPSTR lpStr);

		// Print function in debug mode
		void _debug_print(const char* content, int flag = 0);
	};

}
