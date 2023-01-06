#pragma once
#include <mmeapi.h>

namespace SRS22 {
	class WaveInputHelper
	{
	public:
		static int lastPacketSize;
		static int totalBytesIn;
		static int callbackCounter;
		WAVEFORMATEX waveInFormat;
		HWAVEIN waveInHandle;
		// WAVEWHDR is also a single buffer of some length.
		// We use two so the underlying system will automatically ping-pong them smoothly.
		WAVEHDR waveHeader1;		
		WAVEHDR waveHeader2;

		WaveInputHelper();
		~WaveInputHelper();

		void Init();

		int SetWaveFormat(WAVEFORMATEX* wf, int wFormatTag, int nChannels, int nSamplesPerSec,
			int nBlockAlign, int wBitsPerSample, int cbSize);

		// Prepare Wave In Header and allocate memory and add the buffer.  
		// If called multiple times will just keep adding more buffers
		// that get ping ponged.
		int PrepareWaveIn(HWAVEIN* hWaveIn, WAVEHDR* waveHeader, DWORD dataSize);

		// Start recording speech
		int StartRecord(HWAVEIN* hWaveIn);

		// Stop recording speech
		int StopRecord(HWAVEIN* hWaveIn, MMTIME* mmTime);

		// Save recorded speech to file
		int SaveRecordtoFile(const char* fileName, WAVEFORMATEX* wf, HWAVEIN* hWaveIn, WAVEHDR* waveHeader, MMTIME* mmTime);

		// Close Wave in channel
		int CloseWaveIn(HWAVEIN* hWaveIn);

		void TakeInputEvent(HDRVR hdrvr, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);

		void TakeWaveDataIn(PWAVEHDR h);

		// str2num
		DWORD FCC(LPSTR lpStr);

		// Print function in debug mode
		void _debug_print(const char* content, int flag = 0);
	};
}
