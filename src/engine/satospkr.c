/* Sets up the speaker layout and turns a voice's azimuth into per-speaker volumes.
   The table stores equal-power gains between the speakers that enclose each of 256 azimuths. */

#include "engine/sndsys.h"

extern "C" {

typedef struct SndGainPair_t {
    float mFirstGain;
    float mSecondGain;
} SndGainPair_t;

extern float lbl_803A7714[5];
extern unsigned char lbl_803A7728;
static void *sndaztospkr_buf;
static unsigned char *sndaztospkr[6];

void SNDI_equalpower(SndGainPair_t *pair, float firstAngle, float secondAngle, float azimuth)
{
    float angle = (azimuth * 0.017453294f - secondAngle * 0.017453294f) /
                  (firstAngle * 0.017453294f - secondAngle * 0.017453294f) * 1.5707964f;

    pair->mFirstGain = SNDI_sin(angle);
    pair->mSecondGain = SNDI_cos(angle);
}

static inline int _SNDIRoundSpeakerGain(float level)
{
    float gain = level * 255.0f;
    return (int)(!(gain < 0.0f) ? gain + 0.5f : gain - 0.5f);
}

#define STORE_SPEAKER_GAIN(dst, level) { \
    int converted = _SNDIRoundSpeakerGain(level); \
    (dst) = converted; \
}

void SNDI_precalcaztospkrvol(void)
{
    SndGainPair_t pair;
    float angle;
    int az;
    int i;

    SNDSYS_entercritical();
    sndaztospkr_buf = SNDMEMI_allocz(lbl_803A6C24.m1C.m23 << 8);
    SNDSYS_leavecritical();
    for (i = 0; i < lbl_803A6C24.m1C.m23; i++) {
        sndaztospkr[i] = (unsigned char *)sndaztospkr_buf + (i << 8);
    }
    for (az = 0; az < 256; az++) {
        angle = (unsigned int)((az << 8) & 0xFFFF) * 0.005493164f;
        if (lbl_803A6C24.m1C.m23 == 1) {
            sndaztospkr[0][az] = 127;
            continue;
        }
        for (i = 0; i < lbl_803A6C24.m1C.m23; i++) {
            sndaztospkr[i][az] = 0;
        }
        if (!(angle > lbl_803A7714[0])) {
            if (lbl_803A6C24.m1C.m23 > 4) {
                SNDI_equalpower(&pair, lbl_803A7714[0], lbl_803A7714[1], angle);
                STORE_SPEAKER_GAIN(sndaztospkr[0][az], pair.mFirstGain);
                STORE_SPEAKER_GAIN(sndaztospkr[1][az], pair.mSecondGain);
            } else {
                SNDI_equalpower(&pair, lbl_803A7714[0], lbl_803A7714[lbl_803A6C24.m1C.m23 - 1] - 360.0f, angle);
                STORE_SPEAKER_GAIN(sndaztospkr[0][az], pair.mFirstGain);
                STORE_SPEAKER_GAIN(sndaztospkr[lbl_803A6C24.m1C.m23 - 1][az], pair.mSecondGain);
            }
        } else if (!(angle < lbl_803A7714[lbl_803A6C24.m1C.m23 - 1])) {
            SNDI_equalpower(&pair, lbl_803A7714[0], lbl_803A7714[lbl_803A6C24.m1C.m23 - 1] - 360.0f, angle - 360.0f);
            STORE_SPEAKER_GAIN(sndaztospkr[0][az], pair.mFirstGain);
            STORE_SPEAKER_GAIN(sndaztospkr[lbl_803A6C24.m1C.m23 - 1][az], pair.mSecondGain);
        } else {
            for (i = 0; i < lbl_803A6C24.m1C.m23; i++) {
                if (!(angle < lbl_803A7714[i]) && !(angle > lbl_803A7714[i + 1])) {
                    SNDI_equalpower(&pair, lbl_803A7714[i], lbl_803A7714[i + 1], angle);
                    STORE_SPEAKER_GAIN(sndaztospkr[i][az], pair.mFirstGain);
                    STORE_SPEAKER_GAIN(sndaztospkr[i + 1][az], pair.mSecondGain);
                }
            }
        }
    }
}

#undef STORE_SPEAKER_GAIN

void SNDI_aztospkrvol(int azimuth, float *levels)
{
    int index = (unsigned char)(azimuth >> 8);
    int i;

    for (i = 0; i < lbl_803A6C24.m1C.m23; i++) {
        levels[i] = (unsigned int)sndaztospkr[i][index] * 0.003921569f;
    }
    if (lbl_803A772C == 3) {
        levels[5] = 0.0f;
    }
}

void SNDI_freespkrtable(void)
{
    SNDSYS_entercritical();
    if (sndaztospkr != 0) {
        SNDMEMI_free(sndaztospkr_buf);
    }
    SNDSYS_leavecritical();
}

void SNDI_spkrconfig(void)
{
    if (lbl_803A7728 == 1) {
        lbl_803A772C = 0;
        lbl_803A7714[0] = 0.0f;
    } else if (lbl_803A7728 == 2) {
        lbl_803A772C = 1;
        lbl_803A7714[0] = 90.0f;
        lbl_803A7714[1] = 270.0f;
    } else if (lbl_803A7728 == 4) {
        lbl_803A772C = 2;
        lbl_803A7714[0] = 45.0f;
        lbl_803A7714[1] = 135.0f;
        lbl_803A7714[2] = 225.0f;
        lbl_803A7714[3] = 315.0f;
    } else if (lbl_803A7728 == 6) {
        lbl_803A772C = 3;
        lbl_803A7714[0] = 0.0f;
        lbl_803A7714[1] = 45.0f;
        lbl_803A7714[2] = 135.0f;
        lbl_803A7714[3] = 225.0f;
        lbl_803A7714[4] = 315.0f;
    }
    if (lbl_803A6C24.m1C.m23 == 2) {
        lbl_803A6C24.m1D8[1][0] = -16384;
        lbl_803A6C24.m1D8[1][1] = 16384;
    } else {
        lbl_803A6C24.m1D8[1][0] = -8192;
        lbl_803A6C24.m1D8[1][1] = 8192;
    }
    lbl_803A6C24.m1D8[2][0] = lbl_803A6C24.m1C.m70;
    lbl_803A6C24.m1D8[2][1] = lbl_803A6C24.m1C.m6C;
    lbl_803A6C24.m1D8[2][2] = lbl_803A6C24.m1C.m6E;
    lbl_803A6C24.m1D8[3][0] = -8192;
    lbl_803A6C24.m1D8[3][1] = 8192;
    lbl_803A6C24.m1D8[3][2] = -24576;
    lbl_803A6C24.m1D8[3][3] = 24576;
    lbl_803A6C24.m1D8[4][0] = -8192;
    lbl_803A6C24.m1D8[4][1] = 0;
    lbl_803A6C24.m1D8[4][2] = 8192;
    lbl_803A6C24.m1D8[4][3] = -24576;
    lbl_803A6C24.m1D8[4][4] = 24576;
    lbl_803A6C24.m1D8[5][0] = -8192;
    lbl_803A6C24.m1D8[5][1] = 0;
    lbl_803A6C24.m1D8[5][2] = 8192;
    lbl_803A6C24.m1D8[5][3] = -24576;
    lbl_803A6C24.m1D8[5][4] = 24576;
    lbl_803A6C24.m1D8[5][5] = 0;
}

}
