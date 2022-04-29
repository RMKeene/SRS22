#include "WaveOutputHelper.h"
#include "StringConversionHelpers.h"

namespace SRS22 {

	SRS22::WaveOutputHelper::PWAVELIB WaveOutputHelper::pWaveLib = NULL;

	WaveOutputHelper::WaveOutputHelper() {

	}

	WaveOutputHelper::~WaveOutputHelper() {

	}

	HWAVELIB WaveOutputHelper::Init(PCHAR pWaveFile, BOOL bPause) {
		if (pWaveLib = (PWAVELIB)LocalAlloc(LMEM_ZEROINIT, sizeof(WAVELIB)))
		{
			pWaveLib->bPaused = bPause;
			pWaveLib->pWaveOutputHelper = this;

			if (OpenWaveSample(pWaveFile, &pWaveLib->WaveSample))
			{
				if (waveOutOpen(&pWaveLib->hWaveOut, WAVE_MAPPER, &pWaveLib->WaveSample.WaveFormatEx, (DWORD_PTR)WaveOutputCallback, (DWORD_PTR)pWaveLib, CALLBACK_FUNCTION) != MMSYSERR_NOERROR)
				{
					UnInit((HWAVELIB)pWaveLib);
					pWaveLib = NULL;
				}
				else
				{

					if (pWaveLib->bPaused)
					{
						waveOutPause(pWaveLib->hWaveOut);
					}

					CreateThread(pWaveLib);
				}
			}
			else
			{
				UnInit((HWAVELIB)pWaveLib);
				pWaveLib = NULL;
			}
		}

		return (HWAVELIB)pWaveLib;
	}

	void WaveOutputHelper::UnInit(HWAVELIB hWaveLib) {
		PWAVELIB pWaveLib = (PWAVELIB)hWaveLib;
		WaveOutputHelper* wvh = (WaveOutputHelper*)(pWaveLib->pWaveOutputHelper);
		if (pWaveLib)
		{
			if (pWaveLib->hThread)
			{
				pWaveLib->bWaveShouldDie = TRUE;

				SetEvent(pWaveLib->hEvent);
				WaitForSingleObject(pWaveLib->hThread, INFINITE);

				CloseHandle(pWaveLib->hEvent);
				CloseHandle(pWaveLib->hThread);
			}

			if (pWaveLib->hWaveOut)
			{
				waveOutClose(pWaveLib->hWaveOut);
			}


			if (pWaveLib->WaveSample.pSampleData)
			{
				LocalFree(pWaveLib->WaveSample.pSampleData);
			}

			LocalFree(pWaveLib);
		}
	}

	void WaveOutputHelper::Pause(HWAVELIB hWaveLib, BOOL bPause) {
		PWAVELIB pWaveLib = (PWAVELIB)hWaveLib;
		WaveOutputHelper* wvh = (WaveOutputHelper*)(pWaveLib->pWaveOutputHelper);

		pWaveLib->bPaused = bPause;

		if (pWaveLib->bPaused)
		{
			waveOutPause(pWaveLib->hWaveOut);
		}
		else
		{
			waveOutRestart(pWaveLib->hWaveOut);
		}
	}


	void CALLBACK WaveOutputHelper::WaveOutputCallback(HWAVEOUT hwo, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2) {
		WaveOutputHelper* wvh = (WaveOutputHelper*)(pWaveLib->pWaveOutputHelper);

		switch (uMsg)
		{
		case WOM_OPEN:
			wvh->WaveOpen(hwo, pWaveLib);
			break;

		case WOM_DONE:
			wvh->WaveDone(hwo, pWaveLib);
			break;

		case WOM_CLOSE:
			wvh->WaveClose(hwo, pWaveLib);
			break;
		}
	}

	BOOL WaveOutputHelper::OpenWaveSample(CHAR* pFileName, PWAVE_SAMPLE pWaveSample) {
		BOOL bSampleLoaded = FALSE;
		HANDLE hFile;
		RIFF_CHUNK RiffChunk = { 0 };
		DWORD dwBytes, dwReturnValue;
		WAVE_FILE_HEADER WaveFileHeader;
		DWORD dwIncrementBytes;

		wchar_t wfname[512];
		StringConversionHelpers::CharToWChar(pFileName, wfname, 512);
		if (hFile = CreateFile(wfname, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL))
		{
			char szIdentifier[5] = { 0 };

			SetFilePointer(hFile, 12, NULL, FILE_CURRENT);


			ReadFile(hFile, &RiffChunk, sizeof(RiffChunk), &dwBytes, NULL);
			ReadFile(hFile, &WaveFileHeader, sizeof(WaveFileHeader), &dwBytes, NULL);

			pWaveSample->WaveFormatEx.wFormatTag = WaveFileHeader.wFormatTag;
			pWaveSample->WaveFormatEx.nChannels = WaveFileHeader.wChannels;
			pWaveSample->WaveFormatEx.nSamplesPerSec = WaveFileHeader.dwSamplesPerSec;
			pWaveSample->WaveFormatEx.nAvgBytesPerSec = WaveFileHeader.dwAvgBytesPerSec;
			pWaveSample->WaveFormatEx.nBlockAlign = WaveFileHeader.wBlockAlign;
			pWaveSample->WaveFormatEx.wBitsPerSample = WaveFileHeader.wBitsPerSample;
			pWaveSample->WaveFormatEx.cbSize = 0;

			dwIncrementBytes = dwBytes;

			do {
				SetFilePointer(hFile, RiffChunk.dwLength - dwIncrementBytes, NULL, FILE_CURRENT);

				dwReturnValue = GetLastError();

				if (dwReturnValue == 0)
				{
					dwBytes = ReadFile(hFile, &RiffChunk, sizeof(RiffChunk), &dwBytes, NULL);

					dwIncrementBytes = 0;

					memcpy(szIdentifier, RiffChunk.IdentifierString, 4);
				}

			} while (_stricmp(szIdentifier, "data") && dwReturnValue == 0);

			if (dwReturnValue == 0)
			{
				pWaveSample->pSampleData = (char*)LocalAlloc(LMEM_ZEROINIT, RiffChunk.dwLength);

				pWaveSample->Size = RiffChunk.dwLength;

				ReadFile(hFile, pWaveSample->pSampleData, RiffChunk.dwLength, &dwBytes, NULL);

				CloseHandle(hFile);

				bSampleLoaded = TRUE;
			}
		}

		return bSampleLoaded;
	}

	void WaveOutputHelper::WaveOpen(HWAVEOUT hWaveOut, PWAVELIB pWaveLib) {
		// Do Nothing
	}

	void WaveOutputHelper::WaveDone(HWAVEOUT hWaveOut, PWAVELIB pWaveLib) {
		SetEvent(pWaveLib->hEvent);
	}

	DWORD WINAPI WaveOutputHelper::AudioThread(PVOID pDataInput) {
		PWAVELIB pWaveLib = (PWAVELIB)pDataInput;
		WaveOutputHelper* wvh = (WaveOutputHelper*)(pWaveLib->pWaveOutputHelper);
		DWORD dwReturnValue = 0;
		UINT Index;

		wvh->SetupAudio(pWaveLib);

		while (!pWaveLib->bWaveShouldDie)
		{
			WaitForSingleObject(pWaveLib->hEvent, INFINITE);

			for (Index = 0; Index < 8; Index++)
			{
				if (pWaveLib->WaveHdr[Index].dwFlags & WHDR_DONE)
				{
					wvh->AudioBuffer(pWaveLib, Index);
					waveOutWrite(pWaveLib->hWaveOut, &pWaveLib->WaveHdr[Index], sizeof(WAVEHDR));
				}
			}
		}

		waveOutReset(pWaveLib->hWaveOut);

		return dwReturnValue;
	}

	void WaveOutputHelper::CreateThread(PWAVELIB pWaveLib) {
		DWORD dwThreadId;

		pWaveLib->hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		pWaveLib->hThread = ::CreateThread(NULL, 0, AudioThread, pWaveLib, 0, &dwThreadId);
	}

	void WaveOutputHelper::SetupAudio(PWAVELIB pWaveLib) {
		WaveOutputHelper* wvh = (WaveOutputHelper*)(pWaveLib->pWaveOutputHelper);
		UINT Index = 0;

		for (Index = 0; Index < 8; Index++)
		{
			pWaveLib->WaveHdr[Index].dwBufferLength = SAMPLE_SIZE;
			pWaveLib->WaveHdr[Index].lpData = pWaveLib->AudioBuffer[Index];

			waveOutPrepareHeader(pWaveLib->hWaveOut, &pWaveLib->WaveHdr[Index], sizeof(WAVEHDR));

			wvh->AudioBuffer(pWaveLib, Index);

			waveOutWrite(pWaveLib->hWaveOut, &pWaveLib->WaveHdr[Index], sizeof(WAVEHDR));
		}
	}

	void WaveOutputHelper::WaveClose(HWAVEOUT hWaveOut, PWAVELIB pWaveLib) {
		// Do Nothing
	}

	void WaveOutputHelper::AudioBuffer(PWAVELIB pWaveLib, UINT Index) {
		WaveOutputHelper* wvh = (WaveOutputHelper*)(pWaveLib->pWaveOutputHelper);
		UINT uiBytesNotUsed = SAMPLE_SIZE;

		pWaveLib->WaveHdr[Index].dwFlags &= ~WHDR_DONE;

		if (pWaveLib->WaveSample.Size - pWaveLib->WaveSample.Index < uiBytesNotUsed)
		{
			memcpy(pWaveLib->AudioBuffer[Index], pWaveLib->WaveSample.pSampleData + pWaveLib->WaveSample.Index, pWaveLib->WaveSample.Size - pWaveLib->WaveSample.Index);

			uiBytesNotUsed -= (pWaveLib->WaveSample.Size - pWaveLib->WaveSample.Index);

			memcpy(pWaveLib->AudioBuffer[Index], pWaveLib->WaveSample.pSampleData, uiBytesNotUsed);

			pWaveLib->WaveSample.Index = uiBytesNotUsed;

			uiBytesNotUsed = 0;
		}
		else
		{
			memcpy(pWaveLib->AudioBuffer[Index], pWaveLib->WaveSample.pSampleData + pWaveLib->WaveSample.Index, uiBytesNotUsed);

			pWaveLib->WaveSample.Index += SAMPLE_SIZE;
			uiBytesNotUsed = 0;
		}

		pWaveLib->WaveHdr[Index].lpData = pWaveLib->AudioBuffer[Index];
		pWaveLib->WaveHdr[Index].dwBufferLength = SAMPLE_SIZE - uiBytesNotUsed;
	}


}
