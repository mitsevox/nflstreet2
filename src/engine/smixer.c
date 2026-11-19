/* Software mixer (smixer.c): creates and destroys the main-CPU mixer, starts, plays and stops voices
   through their filter chains, ramps and sets their dry and wet gains and mixes each audio slice.
   Names from the GoldenEye: Rogue Agent and Medal of Honor: European Assault symbol sets (smixer.c). */

#include "engine/sndlib.h"

extern int lbl_803A6E58;
extern void (*lbl_803B5020)(void **outputs, int count);

extern "C" {
void MIXI_interpolateto0(float *last, float *dst);
void MIXI_interpolatemix(float *src, float *dst, float from, float to);
int SNDMIXI_volramp(Record_803B5010 *record);
}

void MIXI_interpolateto0(float *last, float *dst)
{
    dst[0] += *last * 0.9411765f;
    dst[1] += *last * 0.88235295f;
    dst[2] += *last * 0.8235294f;
    dst[3] += *last * 0.7647059f;
    dst[4] += *last * 0.7058824f;
    dst[5] += *last * 0.64705884f;
    dst[6] += *last * 0.5882353f;
    dst[7] += *last * 0.5294118f;
    dst[8] += *last * 0.47058824f;
    dst[9] += *last * 0.4117647f;
    dst[10] += *last * 0.3529412f;
    dst[11] += *last * 0.29411766f;
    dst[12] += *last * 0.23529412f;
    dst[13] += *last * 0.1764706f;
    dst[14] += *last * 0.11764706f;
    dst[15] += *last * 0.05882353f;
    *last = 0.0f;
}

void MIXI_interpolatemix(float *src, float *dst, float from, float to)
{
    float step = (to - from) * 0.05882353f;

    dst[0] += src[0] * (from + step * 1.0f);
    dst[1] += src[1] * (from + step * 2.0f);
    dst[2] += src[2] * (from + step * 3.0f);
    dst[3] += src[3] * (from + step * 4.0f);
    dst[4] += src[4] * (from + step * 5.0f);
    dst[5] += src[5] * (from + step * 6.0f);
    dst[6] += src[6] * (from + step * 7.0f);
    dst[7] += src[7] * (from + step * 8.0f);
    dst[8] += src[8] * (from + step * 9.0f);
    dst[9] += src[9] * (from + step * 10.0f);
    dst[10] += src[10] * (from + step * 11.0f);
    dst[11] += src[11] * (from + step * 12.0f);
    dst[12] += src[12] * (from + step * 13.0f);
    dst[13] += src[13] * (from + step * 14.0f);
    dst[14] += src[14] * (from + step * 15.0f);
    dst[15] += src[15] * (from + step * 16.0f);
}

void SNDMIX_setmasterlowpass(float value)
{
}

int SNDMIXI_volramp(Record_803B5010 *record)
{
    // FAKEMATCH: unused stack object; reproduces the target frame (8 bytes below the saved registers)
    volatile int spare[2];
    int i;

    if (record->m40->m0(record->m40, 16, (float *)lbl_803B4E34.mB0[0], (float *)lbl_803B4E34.mB0[1], 0) <= 0) {
        for (i = 0; i < lbl_8030002C; i++) {
            record->m34[i] = record->m38[i];
        }
        for (i = 0; i < lbl_803B4E34.m0.m9; i++) {
            record->m4[i] = record->m1C[i];
        }
        return 0;
    }
    record->m3C = ((float *)lbl_803B4E34.mB0[1])[15];
    for (i = 0; i < lbl_8030002C; i++) {
        if (lbl_803B4E34.m14[i] != 0) {
            if (record->m34[i] != record->m38[i]) {
                MIXI_interpolatemix((float *)lbl_803B4E34.mB0[1], lbl_803B4E24.m0[i], record->m34[i], record->m38[i]);
                record->m34[i] = record->m38[i];
            } else if (record->m38[i] != 0.0f) {
                lbl_803B4E34.m1E0(16, (float *)lbl_803B4E34.mB0[1], lbl_803B4E24.m0[i], record->m38[i]);
            }
        }
    }
    for (i = 0; i < lbl_803B4E34.m0.m9; i++) {
        if (record->m4[i] != record->m1C[i]) {
            MIXI_interpolatemix((float *)lbl_803B4E34.mB0[1], (float *)lbl_803B4E34.mD0[i], record->m4[i], record->m1C[i]);
            record->m4[i] = record->m1C[i];
        } else if (record->m1C[i] != 0.0f) {
            lbl_803B4E34.m1E0(16, (float *)lbl_803B4E34.mB0[1], (float *)lbl_803B4E34.mD0[i], record->m1C[i]);
        }
    }
    return 16;
}

void *SNDI_New(int size)
{
    return SNDMEMI_allocz(size);
}

void SNDI_Delete(void *p)
{
    SNDMEMI_free(p);
}

void MIX_create(Setup_80272EC4 *setup)
{
    int i;

    fn_802797F4(SNDI_New);
    fn_80279800(SNDI_Delete);
    fn_8027980C(SNDI_memcpy);
    lbl_803B4E34.m0 = *setup;
    SNDSYS_entercritical();
    MIX_createFxglobals();
    for (i = 0; i < lbl_8030002C; i++) {
        lbl_803B4E34.m14[i] = 0;
    }
    for (i = 0; i < 2; i++) {
        void *buffer = SNDMEMI_allocz(2748);

        lbl_803B4E34.mA8[i] = buffer;
        lbl_803B4E34.mB0[i] = (int *)buffer + 2;
        while ((u32)lbl_803B4E34.mB0[i] & 0x3F) {
            lbl_803B4E34.mB0[i]++;
        }
    }
    for (i = 0; i < lbl_803B4E34.m0.m9; i++) {
        void *buffer = SNDMEMI_allocz(704);

        lbl_803B4E34.mB8[i] = buffer;
        lbl_803B4E34.mD0[i] = (int *)buffer;
        while ((u32)lbl_803B4E34.mD0[i] & 0x3F) {
            lbl_803B4E34.mD0[i]++;
        }
    }
    if (lbl_803B4E34.m0.m8 != 0) {
        float *p;

        lbl_803B4E34.m1DC = (Record_803B5010 *)SNDMEMI_allocz(
            lbl_803B4E34.m0.m8 * sizeof(Record_803B5010) + lbl_8030002C * sizeof(float) * lbl_803B4E34.m0.m8 +
            lbl_8030002C * sizeof(float) * lbl_803B4E34.m0.m8);
        memset(lbl_803B4E34.m1DC, 0,
               lbl_803B4E34.m0.m8 * sizeof(Record_803B5010) + lbl_8030002C * sizeof(float) * lbl_803B4E34.m0.m8 +
            lbl_8030002C * sizeof(float) * lbl_803B4E34.m0.m8);
        p = (float *)&lbl_803B4E34.m1DC[lbl_803B4E34.m0.m8];
        for (i = 0; i < lbl_803B4E34.m0.m8; i++) {
            lbl_803B4E34.m1DC[i].m34 = p;
            p += lbl_8030002C;
            lbl_803B4E34.m1DC[i].m38 = p;
            p += lbl_8030002C;
        }
    }
    SNDSYS_leavecritical();
    MIXI_initunpack16();
    MIXI_initunpackxa();
    MIXI_initunpackmt();
    MIX_reset();
    for (i = 0; i < lbl_803B4E34.m0.m9; i++) {
        lbl_803B4E34.m104[i] = 0;
        SFILTER_ft24_32init(&lbl_803B4E34.m134[i]);
        lbl_803B4E34.m134[i].m18 = 0;
        lbl_803B4E34.m134[i].m1A = 0;
        SFILTER_add(&lbl_803B4E34.m104[i], &lbl_803B4E34.m134[i]);
        memset(lbl_803B4E34.mD0[i], 0, 640);
    }
}

void MIX_destroy(void)
{
    int i;

    SNDSYS_entercritical();
    MIX_destroyFxglobals();
    if (lbl_803B4E34.m1DC != 0) {
        SNDMEMI_free(lbl_803B4E34.m1DC);
        lbl_803B4E34.m1DC = 0;
    }
    for (i = 0; i < 2; i++) {
        if (lbl_803B4E34.mA8[i] != 0) {
            SNDMEMI_free(lbl_803B4E34.mA8[i]);
            lbl_803B4E34.mA8[i] = 0;
        }
    }
    for (i = 0; i < lbl_803B4E34.m0.m9; i++) {
        if (lbl_803B4E34.mB8[i] != 0) {
            SNDMEMI_free(lbl_803B4E34.mB8[i]);
            lbl_803B4E34.mB8[i] = 0;
        }
    }
    SNDMIX_setmasterlowpass(2.0f);
    SNDSYS_leavecritical();
}

void MIX_reset(void)
{
    lbl_803B4E34.m1E0 = mixc;
    lbl_803B4E34.m1E4 = decode16x87;
    lbl_803B4E34.mC = 320;
}

void MIX_playinit(int index, int type, int mode, int a, int b, void *data, int c, int d, int e, int f, int g, int h,
                 int k, int slot)
{
    Record_803B5010 *record = &lbl_803B4E34.m1DC[index];
    Params_80275F80 params;
    int table = 0;
    int kind;

    record->m40 = 0;
    record->m48 = 0;
    record->m50 = 0;
    record->m54 = 0;
    record->m58 = 0;
    record->m4C = 0;
    params.m18 = 1;
    params.m28 = 0;
    kind = -1;
    if (type == 7) {
        kind = 0;
    } else if (type == 10) {
        kind = 1;
    } else if (type == 4) {
        kind = 2;
    } else if (type == 22) {
        kind = 3;
    } else if (type == 16) {
        kind = 4;
    } else if (type == 23) {
        kind = 5;
    }
    if (mode == 1) {
        if (f > 0) {
            table = 1;
        }
    } else if (mode == 0) {
        table = 2;
    }
    if (lbl_803B4E34.m18[kind][table] != 0) {
        record->m48 = (Node_80279D90 *)SNDMEMI_allocz(lbl_803B4E34.m60[kind][table]);
        params.m0 = a;
        params.m24 = k;
        params.m4 = b;
        params.m8 = c;
        params.mC = d;
        params.m10 = e;
        params.m14 = f;
        params.m20 = lbl_803A6C24.m16F;
        params.m1C = index;
        record->m48->m4 = 0;
        record->m48->m18 = 240;
        record->m48->m1A = slot;
        lbl_803B4E34.m18[kind][table](record->m48, &params);
        record->m44 = params.m28;
        SFILTER_add(&record->m40, record->m48);
    }
    if (data != 0) {
        if (mode != 0) {
            index = -1;
        }
        record->m4C = (Node_80279D90 *)SNDMEMI_allocz(6196);
        record->m4C->m4 = 0;
        record->m4C->m18 = 200;
        record->m4C->m1A = slot;
        SFILTER_timestretchinit(record->m4C, (unsigned char *)data, index);
        SFILTER_add(&record->m40, record->m4C);
    }
    record->m0 = 1;
}

void MIX_play(int index)
{
    Record_803B5010 *record = &lbl_803B4E34.m1DC[index];
    int i;

    record->m1 = 0;
    record->m3C = 0.0f;
    for (i = 0; i < lbl_8030002C; i++) {
        record->m34[i] = record->m38[i];
    }
    for (i = 0; i < lbl_803B4E34.m0.m9; i++) {
        record->m4[i] = record->m1C[i];
    }
    record->m0 = 2;
}

void MIXI_stop(int index)
{
    MIX_stop(index);
    lbl_803B4E34.m0.m4(index);
}

void MIX_stop(int index)
{
    Record_803B5010 *record = &lbl_803B4E34.m1DC[index];
    Node_80279D90 *next;
    int i;

    for (i = 0; i < lbl_8030002C; i++) {
        lbl_803B4E34.m100[i] += record->m34[i] * record->m3C;
    }
    for (i = 0; i < lbl_803B4E34.m0.m9; i++) {
        lbl_803B4E34.mE8[i] += record->m4[i] * record->m3C;
    }
    do {
        if (record->m40->m4 != 0) {
            record->m40->m4(record->m40);
        }
        next = record->m40->m8;
        SNDMEMI_free(record->m40);
        record->m40 = next;
    } while (next != 0);
    record->m0 = 0;
}

void SNDMIX_setdrygain(int index, int channel, float value)
{
    lbl_803B4E34.m1DC[index].m1C[channel] = value;
    lbl_803B4E34.m1DC[index].m1 = 1;
}

void SNDMIX_setwetgain(int index, int slot, float value)
{
    lbl_803B4E34.m1DC[index].m38[slot] = value;
    lbl_803B4E34.m1DC[index].m1 = 1;
}

void MIX_audioslice(void **outputs, int count)
{
    // FAKEMATCH: unused stack object; reproduces the target frame (8 bytes below the saved registers)
    volatile int spare[2];
    Record_803B5010 *record;
    int done;
    int left;
    int n;
    int i;
    int j;

    for (i = 0; i < lbl_8030002C; i++) {
        if (lbl_803B4E34.m14[i] != 0 && lbl_803B4E34.m100[i] != 0.0f) {
            MIXI_interpolateto0(&lbl_803B4E34.m100[i], lbl_803B4E24.m0[i]);
        }
    }
    for (i = 0; i < lbl_803B4E34.m0.m9; i++) {
        memset(lbl_803B4E34.mD0[i], 0, count * 4);
        if (lbl_803B4E34.mE8[i] != 0.0f) {
            MIXI_interpolateto0(&lbl_803B4E34.mE8[i], (float *)lbl_803B4E34.mD0[i]);
        }
    }
    for (i = 0; i < lbl_803B4E34.m0.m8; i++) {
        record = &lbl_803B4E34.m1DC[i];
        if (record->m0 == 2) {
            if (record->m1 != 0) {
                done = SNDMIXI_volramp(record);
                record->m1 = 0;
                left = count - done;
            } else {
                done = 0;
                left = count;
            }
            if (left != 0) {
                n = record->m40->m0(record->m40, left, (float *)lbl_803B4E34.mB0[0], (float *)lbl_803B4E34.mB0[1], 0);
                if (n < 0) {
                    MIXI_stop(i);
                } else if (n != 0) {
                    record->m3C = ((float *)lbl_803B4E34.mB0[1])[n - 1];
                    for (j = 0; j < lbl_803B4E34.m0.m9; j++) {
                        if (record->m1C[j] != 0.0f) {
                            lbl_803B4E34.m1E0(n, (float *)lbl_803B4E34.mB0[1], (float *)lbl_803B4E34.mD0[j] + done,
                                              record->m1C[j]);
                        }
                    }
                    for (j = 0; j < lbl_8030002C; j++) {
                        if (lbl_803B4E34.m14[j] != 0 && record->m38[j] != 0.0f) {
                            lbl_803B4E34.m1E0(n, (float *)lbl_803B4E34.mB0[1], lbl_803B4E24.m0[j] + done, record->m38[j]);
                            lbl_803B4E24.m4 = 0;
                        }
                    }
                }
            }
        }
    }
    if (lbl_803B4E34.m10 != 0) {
        lbl_803B4E34.m10(count);
    }
    for (i = 0; i < lbl_803B4E34.m0.m9; i++) {
        if (lbl_803B4E34.m11C[i] != 0) {
            lbl_803B4E34.m11C[i]->m0(lbl_803B4E34.m11C[i], count, (float *)lbl_803B4E34.mD0[i], (float *)lbl_803B4E34.mB0[0], 0);
            lbl_803B4E34.m104[i]->m0(lbl_803B4E34.m104[i], count, (float *)lbl_803B4E34.mB0[0], (float *)outputs[i], 0);
        } else {
            lbl_803B4E34.m104[i]->m0(lbl_803B4E34.m104[i], count, (float *)lbl_803B4E34.mD0[i], (float *)outputs[i], 0);
        }
    }
    if (lbl_803A6E58 != 0) {
        lbl_803B5020(outputs, count);
    }
}
