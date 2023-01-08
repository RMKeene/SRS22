#pragma once

#define FIT_FFT_FORWARD 0
#define FIT_FFT_REVERSE 1

namespace SRS22 {

	/*
	  fix_fft() - perform forward/inverse fast Fourier transform.
	  fr[n],fi[n] are real and imaginary arrays, both INPUT AND
	  RESULT (in-place FFT), with 0 <= n < 2**m; set inverse to
	  0 for forward transform (FFT), or 1 for iFFT.

	  The return value is the scale of the resulting data.  If values are
	  going to overflow 16 bit signed then it down shifts. So after returning from fix_fftr
	  If it is not 0 then you have to upshift the data by the returned shift count and it is then more than 16 bit
	  wide results.

	*/
	int fix_fft(short fr[], short fi[], short m, short inverse);

	/*
	  fix_fftr() - forward/inverse FFT on array of real numbers.
	  Real FFT/iFFT using half-size complex FFT by distributing
	  even/odd samples into real/imaginary arrays respectively.
	  In order to save data space (i.e. to avoid two arrays, one
	  for real, one for imaginary samples), we proceed in the
	  following two steps: a) samples are rearranged in the real
	  array so that all even samples are in places 0-(N/2-1) and
	  all imaginary samples in places (N/2)-(N-1), and b) fix_fft
	  is called with fr and fi pointing to index 0 and index N/2
	  respectively in the original array. The above guarantees
	  that fix_fft "sees" consecutive real samples as alternating
	  real and imaginary samples in the complex array.

	  The return value is the scale of the resulting data.  If values are
	  going to overflow 16 bit signed then it down shifts. So after returning from fix_fftr 
	  If it is not 0 then you have to upshift the data by the returned shift count and it is then more than 16 bit
	  wide results.

	*/
	int fix_fftr(short f[], int m, int inverse);
}