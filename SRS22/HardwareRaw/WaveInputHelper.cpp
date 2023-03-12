#include "WaveInputHelper.h"
#include <codecvt>
#include "../StringConversionHelpers.h"
#include <stdlib.h>
#include "WaveInConstants.h"
#include "../SRSMath.h"
#include <algorithm>
#include <mmreg.h>

namespace SRS22 {
	// As single buffer of data. We shoot for 1/10th second of audio. We have 2 of these so they ping pong smoothly.
	typedef struct WAV_HEADER {
		/* RIFF Chunk Descriptor */
		uint8_t RIFF[4] = { 'R', 'I', 'F', 'F' }; // RIFF Header Magic header
		uint32_t ChunkSize;                     // RIFF Chunk Size
		uint8_t WAVE[4] = { 'W', 'A', 'V', 'E' }; // WAVE Header
		/* "fmt" sub-chunk */
		uint8_t fmt[4] = { 'f', 'm', 't', ' ' }; // FMT header
		uint32_t Subchunk1Size = 16;           // Size of the fmt chunk
		uint16_t AudioFormat = 6; // Audio format 1=PCM, 6=mulaw, 7=alaw, 257=IBM
								  // Mu-Law, 258=IBM A-Law, 259=ADPCM
		uint16_t NumOfChan = 1;   // Number of channels 1=Mono 2=Stereo
		uint32_t SamplesPerSec = SRS22SAMPLEFREQ;   // Sampling Frequency in Hz
		uint32_t bytesPerSec = SRS22SAMPLEFREQ; // bytes per second
		uint16_t blockAlign = 1;          // 2=16-bit mono, 4=16-bit stereo
		uint16_t bitsPerSample = 8;      // Number of bits per sample
		/* "data" sub-chunk */
		uint8_t Subchunk2ID[4] = { 'd', 'a', 't', 'a' }; // "data"  string
		uint32_t Subchunk2Size = SRS22FFTSIZE; // Sampled data length
	} wav_hdr;

	using SRS22::StringConversionHelpers;

	int WaveInputHelper::lastPacketSize = -1;
	int WaveInputHelper::totalBytesIn = 0;
	int WaveInputHelper::callbackCounter = 0;

	WaveInputHelper::WaveInputHelper() {
	}

	WaveInputHelper::~WaveInputHelper() {
	}

	void WaveInputHelper_Callback(HDRVR hdrvr, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2) {
		WaveInputHelper* theThisPtr = (WaveInputHelper*)dwUser;
		theThisPtr->TakeInputEvent(hdrvr, uMsg, dwUser, dw1, dw2);
	}

	void WaveInputHelper::Init() {
		int res;
		char lpTemp[256];

		for (int i = 0; i < SRS22FFTRESULTSIZE; i++)
			frequencyAmplitudes[i] = 0.0f;

		res = waveInGetNumDevs();
		if (!res)
		{
			printf("Access WaveIn channel FAILED!");
			return;
		}
		else
		{
			printf("Access WaveIn channel SUCCEED!");
		}

		SetWaveFormat(&waveInFormat, WAVE_FORMAT_MULAW, 1, SRS22SAMPLEFREQ, 1, 8, 0);

		res = waveInOpen(&waveInHandle, WAVE_MAPPER, &waveInFormat, (DWORD_PTR)&WaveInputHelper_Callback, (DWORD_PTR)this, CALLBACK_FUNCTION);
		if (res != MMSYSERR_NOERROR)
		{
			sprintf(lpTemp, "Open wave input channel FAILED: Error_Code = 0x%x", res);
			printf(lpTemp);
			return;
		}
		else
		{
			printf("Open wave input channel SUCCEED!");
		}
		StartRecord(&waveInHandle);
	}

	// Set wave format when sampling the audio
	// Typical call SetWaveFormat(&waveInFormat, 1, 1, SRS22SAMPLEFREQ, 1, 8, 0);
	int WaveInputHelper::SetWaveFormat(WAVEFORMATEX* wf, int wFormatTag, int nChannels, int nSamplesPerSec,
		int nBlockAlign, int wBitsPerSample, int cbSize)
	{
		wf->wFormatTag = wFormatTag;
		wf->nChannels = nChannels;
		wf->nSamplesPerSec = nSamplesPerSec;
		wf->nBlockAlign = nBlockAlign;
		wf->wBitsPerSample = wBitsPerSample;
		wf->cbSize = cbSize;
		wf->nAvgBytesPerSec = nSamplesPerSec * wBitsPerSample / 8;
		return 0;
	}

	int WaveInputHelper::PrepareWaveIn(HWAVEIN* hWaveIn, WAVEHDR* waveHeader, DWORD dataSize)
	{
		int res;

		waveHeader->dwBufferLength = dataSize;
		waveHeader->dwBytesRecorded = 0;
		waveHeader->dwUser = 0;
		waveHeader->dwFlags = 0;
		waveHeader->dwLoops = 0;
		waveHeader->lpData = (char*)GlobalLock(GlobalAlloc(GMEM_MOVEABLE | GMEM_SHARE, dataSize));
		memset(waveHeader->lpData, 0, dataSize);

		// Prepare Header
		res = waveInPrepareHeader(*hWaveIn, waveHeader, sizeof(WAVEHDR));
		if (res != MMSYSERR_NOERROR)
		{
			char lpTemp[256];
			sprintf(lpTemp, "Cannot prepare wave in header: Error_Code = 0x%03X", res);
			_debug_print(lpTemp, 1);
			return -1;
		}
		else
		{
			//_debug_print("Prepare wave in header SUCCEED!");
		}

		res = waveInAddBuffer(*hWaveIn, waveHeader, sizeof(WAVEHDR));
		if (res != MMSYSERR_NOERROR)
		{
			char lpTemp[256];
			sprintf(lpTemp, "Cannot add buffer for wave in: Error_Code = 0x%03X", res);
			_debug_print(lpTemp, 1);
			return -1;
		}
		else
		{
			//_debug_print("Add buffer for wave in SUCCEED!");
		}
		return 0;
	}

	// Start recording speech
	int WaveInputHelper::StartRecord(HWAVEIN* hWaveIn)
	{
		int res;

		// Prepare twice to ping pong. At SRS22SAMPLEFREQ  samples per sec we want 10 buffers per second so SRS22FFTSIZE (1024) samples.
		res = PrepareWaveIn(&waveInHandle, &waveHeader1, SRS22FFTSIZE);
		if (res != MMSYSERR_NOERROR)
		{
			_debug_print("PrepareWaveIn FAILED!", 1);
			return -1;
		}
		else
		{
			//_debug_print("PrepareWaveIn ok.", 1);
		}
		res = PrepareWaveIn(&waveInHandle, &waveHeader2, SRS22FFTSIZE);
		if (res != MMSYSERR_NOERROR)
		{
			_debug_print("PrepareWaveIn FAILED!", 1);
			return -1;
		}
		else
		{
			//_debug_print("PrepareWaveIn ok.", 1);
		}
		res = waveInStart(*hWaveIn);
		if (res != MMSYSERR_NOERROR)
		{
			_debug_print("Start recording FAILED!", 1);
			return -1;
		}
		else
		{
			//_debug_print("Start recording...", 1);
		}
		return 0;
	}

	// Stop recording speech
	int WaveInputHelper::StopRecord(HWAVEIN* hWaveIn, MMTIME* mmTime)
	{
		int res;

		res = waveInStop(*hWaveIn);
		if (res != MMSYSERR_NOERROR)
		{
			_debug_print("Stop recording FAILED!", 1);
			return -1;
		}
		//_debug_print("Stop recording SUCCEED!");

		res = waveInReset(*hWaveIn);
		if (res != MMSYSERR_NOERROR)
		{
			_debug_print("Reset wave in memory FAILED!", 1);
			return -1;
		}
		//_debug_print("Reset wave in memory SUCCEED!");

		return 0;
	}

	void WaveInputHelper::TakeInputEvent(HDRVR hdrvr, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2) {
		callbackCounter++;
		PWAVEHDR h = (PWAVEHDR)dw1;

		switch (uMsg) {
		case WIM_OPEN:
			break;
		case WIM_CLOSE:
			break;
		case WIM_DATA:
			TakeWaveDataIn(h);
			break;
		default:
			break;
		}
	}

	void WaveInputHelper::TakeWaveDataIn(PWAVEHDR h) {
		if (h->dwBytesRecorded <= 0) {
			return;
		}
		lastPacketSize = h->dwBytesRecorded;
		totalBytesIn += lastPacketSize;

		for (int i = 0; i < SRS22FFTSIZE; i++) {
			fftTempBuffer[i] = ulaw2linear(h->lpData[i]);
			fftTempBuffer[i] = h->lpData[i];
		}
		// In place computation.
		int fftscale = fix_fftr(fftTempBuffer, SRS22FFTEXP, FIT_FFT_FORWARD);
		// Since we called the real only the result is interleaved real and immaginary parts.
		// So convert to amplitude
		for (int i = 0; i < SRS22FFTRESULTSIZE; i++) {
			const int realIdx = i * 2;
			const int realPart = fftTempBuffer[realIdx];
			const int immaginaryPart = fftTempBuffer[realIdx + 1];
			const float a2 = realPart * realPart + immaginaryPart * immaginaryPart;
			const float a = SRSFastSqrt(a2) / 40.0f;
			frequencyAmplitudes[i] = std::clamp(a, 0.0f, 1.0f);
		}

		// Add in the same buffer again so it is the next after the current.
		// This gives us continuous recording forever.
		int res = waveInAddBuffer(waveInHandle, h, sizeof(WAVEHDR));
		if (res != MMSYSERR_NOERROR)
		{
			char lpTemp[256];
			sprintf(lpTemp, "Cannot add buffer for wave in: Error_Code = 0x%03X", res);
			_debug_print(lpTemp, 1);
		}
	}

	// Save recorded speech to file
	int WaveInputHelper::SaveRecordtoFile(const char* fileName, WAVEFORMATEX* wf, HWAVEIN* hWaveIn, WAVEHDR* waveHeader, MMTIME* mmTime)
	{
		static wchar_t fnameW[1024];
		StringConversionHelpers::CharToWChar(fileName, fnameW, 1024);

		waveHeader->dwBytesRecorded = mmTime->u.cb;

		std::ofstream out(fileName, std::ios::binary);

		wav_hdr wav;
		wav.ChunkSize = waveHeader->dwBytesRecorded + sizeof(wav_hdr) - 8;
		wav.Subchunk2Size = waveHeader->dwBytesRecorded;
		out.write(reinterpret_cast<const char*>(&wav), sizeof(wav_hdr));
		out.write(reinterpret_cast<char*>(waveHeader->lpData), waveHeader->dwBytesRecorded);
		out.flush();
		out.close();

		//_debug_print("SaveRecordtoFile SUCCEED!", 1);

		return 0;
	}

	// Close Wave in channel
	int WaveInputHelper::CloseWaveIn(HWAVEIN* hWaveIn)
	{
		int res;

		res = waveInClose(*hWaveIn);
		if (res != MMSYSERR_NOERROR)
		{
			_debug_print("Close wave in FAILED!", 1);
		}
		else
		{
			//_debug_print("Close wave in SUCCEED!");
		}
		return 0;
	}

	// str2num
	DWORD WaveInputHelper::FCC(LPSTR lpStr)
	{
		DWORD Number = lpStr[0] + lpStr[1] * 0x100 + lpStr[2] * 0x10000 + lpStr[3] * 0x1000000;
		return Number;
	}

	// Print function in debug mode
	void WaveInputHelper::_debug_print(const char* content, int flag)
	{
		if (flag)
		{
#ifdef _CONSOLE_APP_
			printf("%s\r\n", content);
#else _GUI_APP_
			static wchar_t contentW[1024];
			StringConversionHelpers::CharToWChar(content, contentW, 1024);
			static wchar_t titleW[128];
			StringConversionHelpers::CharToWChar("Debug Message", titleW, 128);
			MessageBox(NULL, contentW, titleW, MB_OK);
#endif
		}
		else
		{
#ifdef _DEBUG_
#ifdef _CONSOLE_APP_
			printf("%s\r\n", content);
#else _WINDOWS_APP_
			MessageBox(NULL, CString(content), CString("Hint"), MB_OK);
#endif
#endif
		}
	}
}