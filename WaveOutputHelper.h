#pragma once
#include <mmeapi.h>

typedef PVOID HWAVELIB;

namespace SRS22 {

	class WaveOutputHelper
	{
    public:
        typedef struct {

            UCHAR IdentifierString[4];
            DWORD dwLength;

        } RIFF_CHUNK, * PRIFF_CHUNK;


        typedef struct {

            WORD  wFormatTag;         // Format category
            WORD  wChannels;          // Number of channels
            DWORD dwSamplesPerSec;    // Sampling rate
            DWORD dwAvgBytesPerSec;   // For buffer estimation
            WORD  wBlockAlign;        // Data block size
            WORD  wBitsPerSample;


        } WAVE_FILE_HEADER, * PWAVE_FILE_HEADER;


        typedef struct _wave_sample {

            WAVEFORMATEX WaveFormatEx;
            char* pSampleData;
            UINT Index;
            UINT Size;
            DWORD dwId;
            DWORD bPlaying;
            struct _wave_sample* pNext;

        } WAVE_SAMPLE, * PWAVE_SAMPLE;

#define SAMPLE_SIZE    (2*2*2000) 

        // The user defined struct passed to callbacks. Given in the waveOutOpen windows call.
        typedef struct {

            HWAVEOUT hWaveOut;
            HANDLE hEvent;
            HANDLE hThread;
            WAVE_SAMPLE WaveSample;
            BOOL bWaveShouldDie;
            WAVEHDR WaveHdr[8];
            char AudioBuffer[8][SAMPLE_SIZE];
            BOOL bPaused;
            void* pWaveOutputHelper;

        } WAVELIB, * PWAVELIB;

		WaveOutputHelper();
		~WaveOutputHelper();

        HWAVELIB Init(PCHAR pWaveFile, BOOL bPause);
        void UnInit(HWAVELIB hWaveLib);
        void Pause(HWAVELIB hWaveLib, BOOL bPause);

    private:
        static void CALLBACK WaveOutputCallback(HWAVEOUT hwo, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);
        static BOOL OpenWaveSample(CHAR* pFileName, PWAVE_SAMPLE pWaveSample);
        static void WaveOpen(HWAVEOUT hWaveOut, PWAVELIB pWaveLib);
        static void WaveDone(HWAVEOUT hWaveOut, PWAVELIB pWaveLib);
        static DWORD WINAPI AudioThread(PVOID pDataInput);
        static void CreateThread(PWAVELIB pWaveLib);
        static void SetupAudio(PWAVELIB pWaveLib);
        static void WaveClose(HWAVEOUT hWaveOut, PWAVELIB pWaveLib);
        static void AudioBuffer(PWAVELIB pWaveLib, UINT Index);
	};

}
