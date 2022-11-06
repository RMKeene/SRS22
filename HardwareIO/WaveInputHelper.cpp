#include "WaveInputHelper.h"
#include <codecvt>
#include "../StringConversionHelpers.h"

namespace SRS22 {
	typedef struct WAV_HEADER {
		/* RIFF Chunk Descriptor */
		uint8_t RIFF[4] = { 'R', 'I', 'F', 'F' }; // RIFF Header Magic header
		uint32_t ChunkSize;                     // RIFF Chunk Size
		uint8_t WAVE[4] = { 'W', 'A', 'V', 'E' }; // WAVE Header
		/* "fmt" sub-chunk */
		uint8_t fmt[4] = { 'f', 'm', 't', ' ' }; // FMT header
		uint32_t Subchunk1Size = 16;           // Size of the fmt chunk
		uint16_t AudioFormat = 1; // Audio format 1=PCM, 6=mulaw, 7=alaw, 257=IBM
								  // Mu-Law, 258=IBM A-Law, 259=ADPCM
		uint16_t NumOfChan = 1;   // Number of channels 1=Mono 2=Stereo
		uint32_t SamplesPerSec = 12000;   // Sampling Frequency in Hz
		uint32_t bytesPerSec = 12000; // bytes per second
		uint16_t blockAlign = 1;          // 2=16-bit mono, 4=16-bit stereo
		uint16_t bitsPerSample = 8;      // Number of bits per sample
		/* "data" sub-chunk */
		uint8_t Subchunk2ID[4] = { 'd', 'a', 't', 'a' }; // "data"  string
		uint32_t Subchunk2Size; // Sampled data length
	} wav_hdr;

	using SRS22::StringConversionHelpers;

	WaveInputHelper::WaveInputHelper() {
	}

	WaveInputHelper::~WaveInputHelper() {
	}

	void WaveInputHelper::Init() {
		int res;
		char lpTemp[256];

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

		SetWaveFormat(&waveInFormat, 1, 1, 12000, 1, 8, 0);

		res = waveInOpen(&waveInHandle, WAVE_MAPPER, &waveInFormat, (DWORD)NULL, 0L, CALLBACK_WINDOW);
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
	}

	// Set wave format when sampling the audio
	int WaveInputHelper::SetWaveFormat(WAVEFORMATEX* wf, int wFormatTag, int nChannels, int nSamplesPerSec,
		int nBlockAlign, int wBitsPerSample, int cbSize)
	{
		//int res;

		wf->wFormatTag = wFormatTag;
		wf->nChannels = nChannels;
		wf->nSamplesPerSec = nSamplesPerSec;
		wf->nBlockAlign = nBlockAlign;
		wf->wBitsPerSample = wBitsPerSample;
		wf->cbSize = cbSize;
		wf->nAvgBytesPerSec = nSamplesPerSec * wBitsPerSample / 8;

		// IAudioClient *pIAudioClient = NULL;
		//res = pIAudioClient->IsFormatSupported( AUDCLNT_SHAREMODE_EXCLUSIVE, (const PWAVEFORMATEX)wf, NULL);
		//if ( res != MMSYSERR_NOERROR )
		//{
		//	_debug_print("Access WaveIn channel FAILED!",1);
		//	return -1;
		//}
		//else
		//{
		//	_debug_print("Access WaveIn channel SUCCEED!");
		//}
		return 0;
	}

	// Open wave input channel
	int WaveInputHelper::OpenWaveIn(HWAVEIN* hWaveIn, WAVEFORMATEX* wf)
	{
		int res;
		char lpTemp[256];

		res = waveInGetNumDevs();
		if (!res)
		{
			_debug_print("Access WaveIn channel FAILED!", 1);
			return -1;
		}
		else
		{
			_debug_print("Access WaveIn channel SUCCEED!");
		}

		// Open wave input channel
		res = waveInOpen(hWaveIn, WAVE_MAPPER, wf, (DWORD)NULL, 0L, CALLBACK_WINDOW);
		if (res != MMSYSERR_NOERROR)
		{
			sprintf(lpTemp, "Open wave input channel FAILED£¬Error_Code = 0x%x", res);
			_debug_print(lpTemp, 1);
			return -1;
		}
		else
		{
			_debug_print("Open wave input channel SUCCEED!");
		}
		return 0;
	}

	// Prepare Wave In Header and allocate memory
	int WaveInputHelper::PrepareWaveIn(HWAVEIN* hWaveIn, WAVEHDR* waveHeader, DWORD dataSize)
	{
		int res;
		char lpTemp[256];

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
			sprintf(lpTemp, "Cannot prepare wave in header£¬Error_Code = 0x%03X", res);
			_debug_print(lpTemp, 1);
			return -1;
		}
		else
		{
			_debug_print("Prepare wave in header SUCCEED!");
		}

		res = waveInAddBuffer(*hWaveIn, waveHeader, sizeof(WAVEHDR));
		if (res != MMSYSERR_NOERROR)
		{
			sprintf(lpTemp, "Cannot add buffer for wave in£¬Error_Code = 0x%03X", res);
			_debug_print(lpTemp, 1);
			return -1;
		}
		else
		{
			_debug_print("Add buffer for wave in SUCCEED!");
		}
		return 0;
	}

	// Start recording speech
	int WaveInputHelper::StartRecord(HWAVEIN* hWaveIn)
	{
		int res;

		res = waveInStart(*hWaveIn);
		if (res != MMSYSERR_NOERROR)
		{
			_debug_print("Start recording FAILED!", 1);
			return -1;
		}
		else
		{
			_debug_print("Start recording...", 1);
		}
		return 0;
	}

	// Stop recording speech
	int WaveInputHelper::StopRecord(HWAVEIN* hWaveIn, MMTIME* mmTime)
	{
		int res;

		res = waveInGetPosition(*hWaveIn, mmTime, sizeof(MMTIME));
		if (res != MMSYSERR_NOERROR)
		{
			_debug_print("Get Position of wave in FAILED!", 1);
			return -1;
		}
		else
		{
			_debug_print("Get Position of wave in SUCCEED!");
		}

		res = waveInStop(*hWaveIn);
		if (res != MMSYSERR_NOERROR)
		{
			_debug_print("Stop recording FAILED!", 1);
			return -1;
		}
		else
		{
			_debug_print("Stop recording SUCCEED!");
		}

		res = waveInReset(*hWaveIn);
		if (res != MMSYSERR_NOERROR)
		{
			_debug_print("Reset wave in memory FAILED!", 1);
			return -1;
		}
		else
		{
			_debug_print("Reset wave in memory SUCCEED!");
		}

		return 0;
	}

	// Save recorded speech to file
	int WaveInputHelper::SaveRecordtoFile(const char* fileName, WAVEFORMATEX* wf, HWAVEIN* hWaveIn, WAVEHDR* waveHeader, MMTIME* mmTime)
	{
		//int res;
		DWORD NumToWrite = 0;
		DWORD dwNumber = 0;
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

		_debug_print("SaveRecordtoFile SUCCEED!", 1);

		return 0;
	}

	// Release wave in memory
	int WaveInputHelper::ReleaseWaveIn(HWAVEIN* hWaveIn, WAVEHDR* waveHeader)
	{
		long long res;

		res = waveInUnprepareHeader(*hWaveIn, waveHeader, sizeof(WAVEHDR));
		if (res != MMSYSERR_NOERROR)
		{
			_debug_print("UnPrepare Wave In Header FAILED!", 1);
			return -1;
		}
		else
		{
			_debug_print("UnPrepare Wave In Header SUCCEED!");
		}

		res = (long long)GlobalFree(GlobalHandle(waveHeader->lpData));
		if (res != MMSYSERR_NOERROR)
		{
			_debug_print("Global Free FAILED!", 1);
			return -1;
		}
		else
		{
			_debug_print("Global Free SUCCEED!");
		}

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
			_debug_print("Close wave in SUCCEED!");
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