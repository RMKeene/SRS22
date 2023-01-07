#pragma once

#define SRS22SAMPLEFREQ 11025
// Must be power of 2
#define SRS22FFTSIZE 1024
#define HALFINTERVAL(hzPerSec) (SRS22SAMPLEFREQ / ((hzPerSec) * 2))
#define SRS22SAMPLEMAXFREQ (SRS22SAMPLEFREQ / (SRS22FFTSIZE / 2))
#define SRS22SAMPLEMINFREQ (SRS22FFTSIZE / 2)

// How many frequencies we track in the input audio.
#define SRS22FREQCOUNT 32
// The frequencies as a array of integer in C++
// Must match SRS22FREQCOUNT in count of entries. Max freq is SRS22SAMPLEMAXFREQ thus 5012 Hz to 21 Hz
#define SRS22FREQS {22, 150, 300, 450, 600, 750, 900, 1100,    1200, 1350, 1500, 1650, 1800, 2000, 2150, 2300,    2500, 2650, 2800, 2950, 3100, 3250, 3450, 3600,    3800, 3900, 4100, 4250, 4400, 4600, 4800, 5012}