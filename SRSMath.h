namespace SRS22 {

	float SRSFastSqrt(float x);

	/// <summary>
	/// FreqCyclesPerSec must be FreqCyclesPerSec <= SRS22SAMPLEFREQ / 2
	/// 
	/// Return is range 0.0 to 1.0
	/// </summary>
	/// <param name="data">Linear data (not uLaw or other encoding)</param>
	/// <param name="bufSize"></param>
	/// <param name="FreqCyclesPerSec"></param>
	/// <returns></returns>
	float SingleFreqDetect(const char* data, const int bufSize, const int FreqCyclesPerSec);

	int ulaw2linear(unsigned char ulawbyte);
}