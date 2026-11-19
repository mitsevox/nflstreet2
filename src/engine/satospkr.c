/* Azimuth to speaker gains (satospkr.c): the speaker layout setup and the table that turns a voice's
   azimuth into per-speaker volumes: equal-power gains between the two speakers that enclose each of
   256 azimuth steps. Names from the GoldenEye: Rogue Agent, Medal of Honor: European Assault and
   NASCAR 2005 symbol sets (satospkr.c, SNDGAINPAIR). */

#include "engine/sndsys.h"

extern "C" {

typedef struct SndGainPair_t {
    float m0;
    float m4;
} SndGainPair_t;

extern float lbl_803A7714[5];
extern unsigned char lbl_803A7728;
extern void *lbl_803B5044;
extern unsigned char *lbl_803B5048[6];

void SNDI_equalpower(SndGainPair_t *pair, float a, float b, float azimuth)
{
    // FAKEMATCH: unused stack object; reproduces the target frame (8 bytes below the saved registers)
    volatile int spare[2];
    float angle = (azimuth * 0.017453294f - b * 0.017453294f) / (a * 0.017453294f - b * 0.017453294f) * 1.5707964f;

    pair->m0 = SNDI_sin(angle);
    pair->m4 = SNDI_cos(angle);
}

static inline int SNDI_gain(float x)
{
    float v = x * 255.0f;

    if (!(v < 0.0f)) {
        v += 0.5f;
    } else {
        v -= 0.5f;
    }
    return v;
}

#define STORE(dst, x) dst = SNDI_gain(x);

void SNDI_precalcaztospkrvol(void)
{
    SndGainPair_t pair;
    float angle;
    int az;
    int i;

    SNDSYS_entercritical();
    lbl_803B5044 = SNDMEMI_allocz(lbl_803A6C24.m1C.m23 << 8);
    SNDSYS_leavecritical();
    for (i = 0; i < lbl_803A6C24.m1C.m23; i++) {
        lbl_803B5048[i] = (unsigned char *)lbl_803B5044 + (i << 8);
    }
    for (az = 0; az < 256; az++) {
        angle = (unsigned int)((az << 8) & 0xFFFF) * 0.005493164f;
        if (lbl_803A6C24.m1C.m23 == 1) {
            lbl_803B5048[0][az] = 127;
            continue;
        }
        for (i = 0; i < lbl_803A6C24.m1C.m23; i++) {
            lbl_803B5048[i][az] = 0;
        }
        if (!(angle > lbl_803A7714[0])) {
            if (lbl_803A6C24.m1C.m23 > 4) {
                SNDI_equalpower(&pair, lbl_803A7714[0], lbl_803A7714[1], angle);
                STORE(lbl_803B5048[0][az], pair.m0);
                STORE(lbl_803B5048[1][az], pair.m4);
            } else {
                SNDI_equalpower(&pair, lbl_803A7714[0], lbl_803A7714[lbl_803A6C24.m1C.m23 - 1] - 360.0f, angle);
                STORE(lbl_803B5048[0][az], pair.m0);
                STORE(lbl_803B5048[lbl_803A6C24.m1C.m23 - 1][az], pair.m4);
            }
        } else if (!(angle < lbl_803A7714[lbl_803A6C24.m1C.m23 - 1])) {
            SNDI_equalpower(&pair, lbl_803A7714[0], lbl_803A7714[lbl_803A6C24.m1C.m23 - 1] - 360.0f, angle - 360.0f);
            STORE(lbl_803B5048[0][az], pair.m0);
            STORE(lbl_803B5048[lbl_803A6C24.m1C.m23 - 1][az], pair.m4);
        } else {
            for (i = 0; i < lbl_803A6C24.m1C.m23; i++) {
                if (!(angle < lbl_803A7714[i]) && !(angle > lbl_803A7714[i + 1])) {
                    SNDI_equalpower(&pair, lbl_803A7714[i], lbl_803A7714[i + 1], angle);
                    STORE(lbl_803B5048[i][az], pair.m0);
                    STORE(lbl_803B5048[i + 1][az], pair.m4);
                }
            }
        }
    }
}

void SNDI_aztospkrvol(int azimuth, float *levels)
{
    int index = (unsigned char)(azimuth >> 8);
    int i;

    for (i = 0; i < lbl_803A6C24.m1C.m23; i++) {
        levels[i] = (unsigned int)lbl_803B5048[i][index] * 0.003921569f;
    }
    if (lbl_803A772C == 3) {
        levels[5] = 0.0f;
    }
}

void SNDI_freespkrtable(void)
{
    SNDSYS_entercritical();
    if (lbl_803B5048 != 0) {
        SNDMEMI_free(lbl_803B5044);
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
