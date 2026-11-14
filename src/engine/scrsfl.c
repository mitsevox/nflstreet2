/* Sound resampler (scrsfl.c): linear-interpolation sample-rate conversion of a float buffer with a
   16.16 fixed-point step; the resampling filter installs it as its conversion routine. */

extern "C" {

typedef union SndResamplePhase_t {
    unsigned int mWord;
    unsigned short mHalf[2];
} SndResamplePhase_t;

void rsflc(int count, float *src, float *dst, int *pos, SndResamplePhase_t *phase, unsigned int stepHi,
                 unsigned int stepLo)
{
    unsigned int step;
    int i;

    phase->mWord = phase->mHalf[0];
    step = (stepHi << 16) | (stepLo >> 16);
    for (i = 0; i < count; i++) {
        dst[i] = src[*pos] + phase->mWord * 1.5258e-5f * (src[*pos + 1] - src[*pos]);
        phase->mWord += step;
        *pos += phase->mWord >> 16;
        phase->mWord = phase->mHalf[1];
    }
    phase->mWord <<= 16;
}

}
