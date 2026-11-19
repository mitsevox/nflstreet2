/* MT block decoder (mtdecf.cpp): decodes MT (MicroTalk) compressed sample blocks into a 432-sample
   float buffer for the MT unpack filters: allocation, the bit reader, the stream header, the
   excitation, reflection-coefficient and LPC synthesis stages of each frame, sample delivery and the
   decoder's state save/restore. */

#include "engine/sndsys.h"
#include "engine/sndutil.h"

namespace Snd {

/* One row of the multi-pulse sample code table: the index_table row for the next code, the bits the
   code uses and the sample value it produces. */
struct MtCommand_t {
    int m0;
    int m4;
    float m8;
};

/* Low-bit masks for 0 to 8 bits (getbits). */
static unsigned int bitmask[9] = { 0, 1, 3, 7, 15, 31, 63, 127, 255 };

/* Reflection-coefficient quantizer levels (decodemut). */
static float coeff_table[64] = {
    0.0f, -0.996776f, -0.990327f, -0.983879f, -0.977431f, -0.970982f, -0.964534f, -0.958085f,
    -0.951637f, -0.930754f, -0.90496f, -0.879167f, -0.853373f, -0.827579f, -0.801786f, -0.775992f,
    -0.750198f, -0.724405f, -0.698611f, -0.670635f, -0.619048f, -0.56746f, -0.515873f, -0.464286f,
    -0.412698f, -0.361111f, -0.309524f, -0.257937f, -0.206349f, -0.154762f, -0.103175f, -0.051587f,
    0.0f, 0.051587f, 0.103175f, 0.154762f, 0.206349f, 0.257937f, 0.309524f, 0.361111f,
    0.412698f, 0.464286f, 0.515873f, 0.56746f, 0.619048f, 0.670635f, 0.698611f, 0.724405f,
    0.750198f, 0.775992f, 0.801786f, 0.827579f, 0.853373f, 0.879167f, 0.90496f, 0.930754f,
    0.951637f, 0.958085f, 0.964534f, 0.970982f, 0.977431f, 0.983879f, 0.990327f, 0.996776f
};

/* Next-code lookup by the low 8 bits of the bit buffer, one table per code row (readsamples). */
static unsigned char index_table[2][256] = {
    {
        4, 6, 5, 9, 4, 6, 5, 13, 4, 6, 5, 10, 4, 6, 5, 17,
        4, 6, 5, 9, 4, 6, 5, 14, 4, 6, 5, 10, 4, 6, 5, 21,
        4, 6, 5, 9, 4, 6, 5, 13, 4, 6, 5, 10, 4, 6, 5, 18,
        4, 6, 5, 9, 4, 6, 5, 14, 4, 6, 5, 10, 4, 6, 5, 25,
        4, 6, 5, 9, 4, 6, 5, 13, 4, 6, 5, 10, 4, 6, 5, 17,
        4, 6, 5, 9, 4, 6, 5, 14, 4, 6, 5, 10, 4, 6, 5, 22,
        4, 6, 5, 9, 4, 6, 5, 13, 4, 6, 5, 10, 4, 6, 5, 18,
        4, 6, 5, 9, 4, 6, 5, 14, 4, 6, 5, 10, 4, 6, 5, 0,
        4, 6, 5, 9, 4, 6, 5, 13, 4, 6, 5, 10, 4, 6, 5, 17,
        4, 6, 5, 9, 4, 6, 5, 14, 4, 6, 5, 10, 4, 6, 5, 21,
        4, 6, 5, 9, 4, 6, 5, 13, 4, 6, 5, 10, 4, 6, 5, 18,
        4, 6, 5, 9, 4, 6, 5, 14, 4, 6, 5, 10, 4, 6, 5, 26,
        4, 6, 5, 9, 4, 6, 5, 13, 4, 6, 5, 10, 4, 6, 5, 17,
        4, 6, 5, 9, 4, 6, 5, 14, 4, 6, 5, 10, 4, 6, 5, 22,
        4, 6, 5, 9, 4, 6, 5, 13, 4, 6, 5, 10, 4, 6, 5, 18,
        4, 6, 5, 9, 4, 6, 5, 14, 4, 6, 5, 10, 4, 6, 5, 2
    },
    {
        4, 11, 7, 15, 4, 12, 8, 19, 4, 11, 7, 16, 4, 12, 8, 23,
        4, 11, 7, 15, 4, 12, 8, 20, 4, 11, 7, 16, 4, 12, 8, 27,
        4, 11, 7, 15, 4, 12, 8, 19, 4, 11, 7, 16, 4, 12, 8, 24,
        4, 11, 7, 15, 4, 12, 8, 20, 4, 11, 7, 16, 4, 12, 8, 1,
        4, 11, 7, 15, 4, 12, 8, 19, 4, 11, 7, 16, 4, 12, 8, 23,
        4, 11, 7, 15, 4, 12, 8, 20, 4, 11, 7, 16, 4, 12, 8, 28,
        4, 11, 7, 15, 4, 12, 8, 19, 4, 11, 7, 16, 4, 12, 8, 24,
        4, 11, 7, 15, 4, 12, 8, 20, 4, 11, 7, 16, 4, 12, 8, 3,
        4, 11, 7, 15, 4, 12, 8, 19, 4, 11, 7, 16, 4, 12, 8, 23,
        4, 11, 7, 15, 4, 12, 8, 20, 4, 11, 7, 16, 4, 12, 8, 27,
        4, 11, 7, 15, 4, 12, 8, 19, 4, 11, 7, 16, 4, 12, 8, 24,
        4, 11, 7, 15, 4, 12, 8, 20, 4, 11, 7, 16, 4, 12, 8, 1,
        4, 11, 7, 15, 4, 12, 8, 19, 4, 11, 7, 16, 4, 12, 8, 23,
        4, 11, 7, 15, 4, 12, 8, 20, 4, 11, 7, 16, 4, 12, 8, 28,
        4, 11, 7, 15, 4, 12, 8, 19, 4, 11, 7, 16, 4, 12, 8, 24,
        4, 11, 7, 15, 4, 12, 8, 20, 4, 11, 7, 16, 4, 12, 8, 3
    }
};

/* The multi-pulse codes indexed by index_table (readsamples). */
static MtCommand_t decode_table[29] = {
    { 1, 8, 0.0f },
    { 1, 7, 0.0f },
    { 0, 8, 0.0f },
    { 0, 7, 0.0f },
    { 0, 2, 0.0f },
    { 0, 2, -1.0f },
    { 0, 2, 1.0f },
    { 0, 3, -1.0f },
    { 0, 3, 1.0f },
    { 1, 4, -2.0f },
    { 1, 4, 2.0f },
    { 1, 3, -2.0f },
    { 1, 3, 2.0f },
    { 1, 5, -3.0f },
    { 1, 5, 3.0f },
    { 1, 4, -3.0f },
    { 1, 4, 3.0f },
    { 1, 6, -4.0f },
    { 1, 6, 4.0f },
    { 1, 5, -4.0f },
    { 1, 5, 4.0f },
    { 1, 7, -5.0f },
    { 1, 7, 5.0f },
    { 1, 6, -5.0f },
    { 1, 6, 5.0f },
    { 1, 8, -6.0f },
    { 1, 8, 6.0f },
    { 1, 7, -6.0f },
    { 1, 7, 6.0f }
};

void *CMTBLKDecf::operator new(unsigned int size)
{
    return CODANew(size);
}

void CMTBLKDecf::operator delete(void *p)
{
    CODADelete(p);
}

}

namespace Snd {

unsigned int getbits(UTALKSTATE_CODA *bits, int count)
{
    unsigned int value;

    value = bits->m4 & bitmask[count];
    bits->m4 >>= count;
    bits->m8 -= count;
    if (bits->m8 <= 7) {
        bits->m4 |= *bits->m0++ << bits->m8;
        bits->m8 += 8;
    }
    return value;
}

void discardbits(UTALKSTATE_CODA *bits, int count)
{
    bits->m4 >>= count;
    bits->m8 -= count;
    if (bits->m8 <= 7) {
        bits->m4 |= *bits->m0++ << bits->m8;
        bits->m8 += 8;
    }
}

void readsamples(UTALKSTATE_CODA *s, int multipulse, float *out, int stride)
{
    // FAKEMATCH: unused stack object; reproduces the target frame (0x58, conversion slot at 0x18)
    volatile int spare;
    int i;
    int model;
    int cnt;
    int x;
    int n;
    int len;

    if (multipulse) {
        model = 0;
        i = 0;
        while (i < 108) {
            cnt = index_table[model][s->m4 & 0xFF];
            model = decode_table[cnt].m0;
            discardbits(s, decode_table[cnt].m4);
            if (cnt > 3) {
                out[i] = decode_table[cnt].m8;
                i += stride;
            } else if (cnt > 1) {
                n = getbits(s, 6) + 7;
                if (i + stride * n > 108) {
                    n = (108 - i) / stride;
                }
                for (x = 0; x < n; x++) {
                    out[i] = 0.0f;
                    i += stride;
                }
            } else {
                x = 7;
                while (getbits(s, 1) == 1) {
                    x++;
                }
                if (getbits(s, 1) == 1) {
                    out[i] = x;
                } else {
                    out[i] = -x;
                }
                i += stride;
            }
        }
    } else {
        x = 0;
        // FAKEMATCH: sample count held in a local; keeps the loop test at cmpwi 108/blt (a literal folds to <= 107)
        len = 108;
        do {
            i = s->m4 & 3;
            if (i == 1) {
                out[x] = -2.0f;
                discardbits(s, 2);
            } else if (i == 3) {
                out[x] = 2.0f;
                discardbits(s, 2);
            } else {
                out[x] = 0.0f;
                discardbits(s, 1);
            }
        } while ((x += stride) < len);
    }
}

void interpolate(float *p)
{
    int i;

    for (i = 0; i < 108; i += 2) {
        p[i] = (p[i - 1] + p[i + 1]) * 0.59738594f + (p[i - 3] + p[i + 3]) * -0.11459156f
            + (p[i - 5] + p[i + 5]) * 0.018032679f;
    }
}

void reftolpc(float *rc, float *lpc)
{
    int i;
    int j;
    float x;
    float tmp2[12];
    float tmp1[12];

    for (j = 10; j >= 0; j--) {
        tmp2[j + 1] = rc[j];
    }
    tmp2[0] = 1.0f;
    for (i = 0; i < 12; i++) {
        x = -rc[11] * tmp2[11];
        for (j = 10; j >= 0; j--) {
            x -= rc[j] * tmp2[j];
            tmp2[j + 1] = rc[j] * x + tmp2[j];
        }
        tmp1[i] = tmp2[0] = x;
        for (j = 0; j < i; j++) {
            x -= lpc[j] * tmp1[i - j - 1];
        }
        lpc[i] = x;
    }
}

void filter(UTALKSTATE_CODA *p, int offset, int count)
{
    float lpc[12];
    float *out;
    int i;

    out = &p->m684[offset];
    reftolpc(p->m114, lpc);
    for (i = 0; i < count; i++) {
        out[0] = p->m144[11] = out[0] + lpc[0] * p->m144[0] + lpc[1] * p->m144[1] + lpc[2] * p->m144[2] + lpc[3] * p->m144[3]
            + lpc[4] * p->m144[4] + lpc[5] * p->m144[5] + lpc[6] * p->m144[6] + lpc[7] * p->m144[7]
            + lpc[8] * p->m144[8] + lpc[9] * p->m144[9] + lpc[10] * p->m144[10] + lpc[11] * p->m144[11];
        out[1] = p->m144[10] = out[1] + lpc[0] * p->m144[11] + lpc[1] * p->m144[0] + lpc[2] * p->m144[1] + lpc[3] * p->m144[2]
            + lpc[4] * p->m144[3] + lpc[5] * p->m144[4] + lpc[6] * p->m144[5] + lpc[7] * p->m144[6]
            + lpc[8] * p->m144[7] + lpc[9] * p->m144[8] + lpc[10] * p->m144[9] + lpc[11] * p->m144[10];
        out[2] = p->m144[9] = out[2] + lpc[0] * p->m144[10] + lpc[1] * p->m144[11] + lpc[2] * p->m144[0] + lpc[3] * p->m144[1]
            + lpc[4] * p->m144[2] + lpc[5] * p->m144[3] + lpc[6] * p->m144[4] + lpc[7] * p->m144[5]
            + lpc[8] * p->m144[6] + lpc[9] * p->m144[7] + lpc[10] * p->m144[8] + lpc[11] * p->m144[9];
        out[3] = p->m144[8] = out[3] + lpc[0] * p->m144[9] + lpc[1] * p->m144[10] + lpc[2] * p->m144[11] + lpc[3] * p->m144[0]
            + lpc[4] * p->m144[1] + lpc[5] * p->m144[2] + lpc[6] * p->m144[3] + lpc[7] * p->m144[4]
            + lpc[8] * p->m144[5] + lpc[9] * p->m144[6] + lpc[10] * p->m144[7] + lpc[11] * p->m144[8];
        out[4] = p->m144[7] = out[4] + lpc[0] * p->m144[8] + lpc[1] * p->m144[9] + lpc[2] * p->m144[10] + lpc[3] * p->m144[11]
            + lpc[4] * p->m144[0] + lpc[5] * p->m144[1] + lpc[6] * p->m144[2] + lpc[7] * p->m144[3]
            + lpc[8] * p->m144[4] + lpc[9] * p->m144[5] + lpc[10] * p->m144[6] + lpc[11] * p->m144[7];
        out[5] = p->m144[6] = out[5] + lpc[0] * p->m144[7] + lpc[1] * p->m144[8] + lpc[2] * p->m144[9] + lpc[3] * p->m144[10]
            + lpc[4] * p->m144[11] + lpc[5] * p->m144[0] + lpc[6] * p->m144[1] + lpc[7] * p->m144[2]
            + lpc[8] * p->m144[3] + lpc[9] * p->m144[4] + lpc[10] * p->m144[5] + lpc[11] * p->m144[6];
        out[6] = p->m144[5] = out[6] + lpc[0] * p->m144[6] + lpc[1] * p->m144[7] + lpc[2] * p->m144[8] + lpc[3] * p->m144[9]
            + lpc[4] * p->m144[10] + lpc[5] * p->m144[11] + lpc[6] * p->m144[0] + lpc[7] * p->m144[1]
            + lpc[8] * p->m144[2] + lpc[9] * p->m144[3] + lpc[10] * p->m144[4] + lpc[11] * p->m144[5];
        out[7] = p->m144[4] = out[7] + lpc[0] * p->m144[5] + lpc[1] * p->m144[6] + lpc[2] * p->m144[7] + lpc[3] * p->m144[8]
            + lpc[4] * p->m144[9] + lpc[5] * p->m144[10] + lpc[6] * p->m144[11] + lpc[7] * p->m144[0]
            + lpc[8] * p->m144[1] + lpc[9] * p->m144[2] + lpc[10] * p->m144[3] + lpc[11] * p->m144[4];
        out[8] = p->m144[3] = out[8] + lpc[0] * p->m144[4] + lpc[1] * p->m144[5] + lpc[2] * p->m144[6] + lpc[3] * p->m144[7]
            + lpc[4] * p->m144[8] + lpc[5] * p->m144[9] + lpc[6] * p->m144[10] + lpc[7] * p->m144[11]
            + lpc[8] * p->m144[0] + lpc[9] * p->m144[1] + lpc[10] * p->m144[2] + lpc[11] * p->m144[3];
        out[9] = p->m144[2] = out[9] + lpc[0] * p->m144[3] + lpc[1] * p->m144[4] + lpc[2] * p->m144[5] + lpc[3] * p->m144[6]
            + lpc[4] * p->m144[7] + lpc[5] * p->m144[8] + lpc[6] * p->m144[9] + lpc[7] * p->m144[10]
            + lpc[8] * p->m144[11] + lpc[9] * p->m144[0] + lpc[10] * p->m144[1] + lpc[11] * p->m144[2];
        out[10] = p->m144[1] = out[10] + lpc[0] * p->m144[2] + lpc[1] * p->m144[3] + lpc[2] * p->m144[4] + lpc[3] * p->m144[5]
            + lpc[4] * p->m144[6] + lpc[5] * p->m144[7] + lpc[6] * p->m144[8] + lpc[7] * p->m144[9]
            + lpc[8] * p->m144[10] + lpc[9] * p->m144[11] + lpc[10] * p->m144[0] + lpc[11] * p->m144[1];
        out[11] = p->m144[0] = out[11] + lpc[0] * p->m144[1] + lpc[1] * p->m144[2] + lpc[2] * p->m144[3] + lpc[3] * p->m144[4]
            + lpc[4] * p->m144[5] + lpc[5] * p->m144[6] + lpc[6] * p->m144[7] + lpc[7] * p->m144[8]
            + lpc[8] * p->m144[9] + lpc[9] * p->m144[10] + lpc[10] * p->m144[11] + lpc[11] * p->m144[0];
        out += 12;
    }
}

void CMTBLKDecf::initmut(unsigned char *data, UTALKSTATE_CODA *p, int flag)
{
    // FAKEMATCH: unused stack object; reproduces the target frame (0x28, conversion slot at 0x10)
    volatile int spare;
    int i;
    float mult;

    p->m0 = data + 1;
    p->m8 = 8;
    p->m4 = p->m0[-1];
    if (flag != 0) {
        p->mC = getbits(p, 1);
        p->m10 = 32 - getbits(p, 4);
        p->m14[0] = (float)(getbits(p, 4) + 1) * 8.0f;
        mult = (float)getbits(p, 6) * 0.001f + 1.04f;
        for (i = 1; i < 64; i++) {
            p->m14[i] = p->m14[i - 1] * mult;
        }
        for (i = 0; i < 12; i++) {
            p->m114[i] = 0.0f;
            p->m144[i] = 0.0f;
        }
        for (i = 0; i < 324; i++) {
            p->m174[i] = 0.0f;
        }
    }
}

void decodemut(UTALKSTATE_CODA *p)
{
    float excitation[118];
    float delta[12];
    // FAKEMATCH: unused stack object; reproduces the target frame (0x280, 16-byte hole above delta)
    float spare[4];
    int multipulse;
    int idx;
    int i;
    int k;
    int lag;
    int base;
    int align;
    int zero;
    float fixedGain;
    float pitchGain;

    idx = getbits(p, 6);
    multipulse = idx < p->m10;
    delta[0] = (coeff_table[idx] - p->m114[0]) * 0.25f;
    for (i = 1; i < 4; i++) {
        delta[i] = (coeff_table[getbits(p, 6)] - p->m114[i]) * 0.25f;
    }
    for (i = 4; i < 12; i++) {
        delta[i] = (coeff_table[getbits(p, 5) + 16] - p->m114[i]) * 0.25f;
    }
    for (k = 0; k < 4; k++) {
        lag = (k + 2) * 108 - getbits(p, 8);
        pitchGain = (float)getbits(p, 4) * 0.06666667f;
        fixedGain = p->m14[getbits(p, 6)];
        if (p->mC == 0) {
            readsamples(p, multipulse, &excitation[5], 1);
        } else {
            align = getbits(p, 1);
            zero = getbits(p, 1);
            readsamples(p, multipulse, &excitation[5 + align], 2);
            if (zero != 0) {
                for (i = 0; i < 108; i += 2) {
                    // FAKEMATCH: pointer-plus spelling of excitation[i - (align - 6)]; keeps align - 6 out of the
                    // index reassociation (target: subi before the loop, subf i - t inside it)
                    *(excitation + (i - (align - 6))) = 0.0f;
                }
            } else {
                for (i = 0; i < 5; i++) {
                    excitation[i] = 0.0f;
                }
                for (i = 113; i < 118; i++) {
                    excitation[i] = 0.0f;
                }
                interpolate(excitation - (align - 6));
                fixedGain *= 0.5f;
            }
        }
        // FAKEMATCH: subframe offset held in a local and the pitch term written first (both chosen for the
        // target's register use: k * 108 stays in one register through the loop)
        base = k * 108;
        for (i = 0; i < 108; i++) {
            p->m684[base + i] = pitchGain * p->m174[lag + i] + fixedGain * excitation[5 + i];
        }
    }
    Coda::gpMemCpy(p->m174, &p->m684[108], 1296);
    for (i = 0; i < 12; i++) {
        p->m114[i] += delta[i];
    }
    filter(p, 0, 1);
    for (i = 0; i < 12; i++) {
        p->m114[i] += delta[i];
    }
    filter(p, 12, 1);
    for (i = 0; i < 12; i++) {
        p->m114[i] += delta[i];
    }
    filter(p, 24, 1);
    for (i = 0; i < 12; i++) {
        p->m114[i] += delta[i];
    }
    filter(p, 36, 33);
}

}

namespace Snd {

CMTBLKDecf::CMTBLKDecf()
{
    mD44 = 0;
    mD54 = 0;
    mD58 = 0;
    mD50 = 0;
    mD52 = 0;
    mD5C = 0;
    mD60 = 0;
    mD64 = 1;
}

int CMTBLKDecf::Feed(void *data, int size, int count)
{
    if (data == 0 || mD54 != 0) {
        return -1;
    }
    mD54 = count;
    mD58 = size;
    mD44 = 0;
    mD48 = (unsigned char *)data;
    if (mD64 == 1) {
        if (*(unsigned char *)data == 0xEE) {
            mD60 = 1;
        } else {
            mD60 = 0;
        }
        initmut((unsigned char *)data + 1, this, mD5C);
    } else {
        initmut((unsigned char *)data, this, mD5C);
    }
    return 0;
}

int CMTBLKDecf::Decode(float **dst, int count)
{
    int total;
    int left;
    int n;
    unsigned char *src;
    float *out;
    short i;
    short value;
    unsigned char *d;
    unsigned char *e;
    unsigned char *f;

    n = mD44;
    if (mD54 == 0) {
        return 0;
    }
    mD4C = *dst;
    total = mD54;
    if (total > count) {
        total = count;
    }
    left = total;
    while (left > 0) {
        if (left < n) {
            n = left;
        }
        Coda::gpMemCpy(mD4C, &m684[432 - mD44], n * 4);
        left -= n;
        mD4C += n;
        mD44 -= n;
        if (left <= 0) {
            break;
        }
        decodemut(this);
        mD44 = 432;
        n = 432;
        if (mD64 == 1) {
            mD48 = m0 - 1;
            src = mD48;
            if (mD60 != 0) {
                d = (unsigned char *)&mD52;
                d[0] = src[0];
                d[1] = src[1];
                src += 2;
                e = (unsigned char *)&mD50;
                e[0] = src[0];
                e[1] = src[1];
                src += 2;
                mD48 = mD48 + mD50 * 2 + 4;
                m0 = mD48 + 1;
                out = &m684[mD52];
                for (i = 0; i < mD50; i++) {
                    f = (unsigned char *)&value;
                    f[0] = src[0];
                    f[1] = src[1];
                    src += 2;
                    *out++ = value;
                }
                mD60 = 0;
            }
            if (*mD48 == 0xEE) {
                mD60 = 1;
            }
            m8 = 8;
            m4 = *m0;
            m0++;
        }
    }
    mD54 -= total;
    return total;
}

MTFSTATE CMTBLKDecf::GetState()
{
    MTFSTATE format;

    format.m0 = m4;
    format.m8 = mD5C;
    format.m4 = mD44;
    return format;
}

void CMTBLKDecf::SetState(MTFSTATE *format, int flags)
{
    m4 = format->m0;
    mD5C = format->m8;
    mD44 = format->m4;
}

void CMTBLKDecf::SetCodecVersion(int version)
{
    mD64 = version;
}

}
