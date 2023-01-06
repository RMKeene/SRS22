namespace SRS22 {

    float SRSFastSqrt(float x)
    {
        const float xhalf = 0.5f * x;
        int i = *(int*)&x;
        i = 0x5f375a84 - (i >> 1);
        x = *(float*)&i;

        x = x * (1.5f - xhalf * x * x);
        return 1.0f / x;
    }


    float SingleFreqDetect(char* ulawData, int bufSize, int freqHalfLengthInSamples) {
        return 0.0f;
    }

}