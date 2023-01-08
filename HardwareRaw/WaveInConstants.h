#pragma once

#define SRS22SAMPLEFREQ 11025
// Size of the audio input buffer in samples. 
// Must be power of 2. 
// 1k is about 1/10th sec of audio which is about as realtime as Windows gets.
#define SRS22FFTSIZE 1024
// 2^10 = 1024 so we want the 10 there.
#define SRS22FFTEXP 10
// Size of the outpout buffer in floats. Half of SRS22FFTSIZE
#define SRS22FFTRESULTSIZE 512

