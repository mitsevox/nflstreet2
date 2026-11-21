/* Software mixer (smixer.c): creates and destroys the main-CPU mixer, starts, plays and stops voices
   through their filter chains, ramps and sets their dry and wet gains and mixes each audio slice.
   Names from the GoldenEye: Rogue Agent and Medal of Honor: European Assault symbol sets (smixer.c). */

#include "engine/sndlib.h"
#include "engine/sndutil.h"

extern int lbl_803A6E58;

extern "C" {
void MIXI_interpolateto0(float *last, float *dst);
void MIXI_interpolatemix(float *src, float *dst, float from, float to);
int SNDMIXI_volramp(Record_803B5010 *record);
}

/* The mixer state: the setup, the filter-chain creators and sizes, the bus buffers, the voice records
   and the mix and decode functions. */
Struct_803B4E34 sndmix;
int sndmixwritelog;
/* Called with the output buffers after each audio slice while the sound system's flag +0x234 is set. */
void (*MIXoutputfn)(void **outputs, int count);
// FAKEMATCH: an unused word that keeps the mixer hooks below at their target offsets; nothing in this
// build reads or writes it.
int _Mix_iUnused;

/* The mixer hooks the sound driver calls, installed by SNDSYS_linkmaincpumixer. */
void (*MIXinitfn)(Setup_80272EC4 *setup);
void (*MIXrestorefn)(void);
void (*MIXaudioslicefn)(void **buffers, int count);
void (*MIXplayinitfn)(int index, int a, int b, int c, int d, void *p, int count, int e, int f, int g, int h,
                      int j, int k, int slot);
void (*MIXplayfn)(int index);
void (*MIXstopfn)(int index);
void (*MIXsetpitchfn)(int index, int value);

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
    int i;

    if (record->m40->m0(record->m40, 16, (float *)sndmix.mB0[0], (float *)sndmix.mB0[1], 0) <= 0) {
        for (i = 0; i < lbl_8030002C; i++) {
            record->m34[i] = record->m38[i];
        }
        for (i = 0; i < sndmix.m0.m9; i++) {
            record->m4[i] = record->m1C[i];
        }
        return 0;
    }
    record->m3C = ((float *)sndmix.mB0[1])[15];
    for (i = 0; i < lbl_8030002C; i++) {
        if (sndmix.m14[i] != 0) {
            if (record->m34[i] != record->m38[i]) {
                MIXI_interpolatemix((float *)sndmix.mB0[1], sndfx.m0[i], record->m34[i], record->m38[i]);
                record->m34[i] = record->m38[i];
            } else if (record->m38[i] != 0.0f) {
                sndmix.m1E0(16, (float *)sndmix.mB0[1], sndfx.m0[i], record->m38[i]);
            }
        }
    }
    for (i = 0; i < sndmix.m0.m9; i++) {
        if (record->m4[i] != record->m1C[i]) {
            MIXI_interpolatemix((float *)sndmix.mB0[1], (float *)sndmix.mD0[i], record->m4[i], record->m1C[i]);
            record->m4[i] = record->m1C[i];
        } else if (record->m1C[i] != 0.0f) {
            sndmix.m1E0(16, (float *)sndmix.mB0[1], (float *)sndmix.mD0[i], record->m1C[i]);
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

    Snd::CODASetNew((void *(*)(unsigned int))SNDI_New);
    Snd::CODASetDelete(SNDI_Delete);
    Snd::Coda::System::SetMemCpy((void *(*)(void *, const void *, unsigned int))SNDI_memcpy);
    sndmix.m0 = *setup;
    SNDSYS_entercritical();
    MIX_createFxglobals();
    for (i = 0; i < lbl_8030002C; i++) {
        sndmix.m14[i] = 0;
    }
    for (i = 0; i < 2; i++) {
        void *buffer = SNDMEMI_allocz(2748);

        sndmix.mA8[i] = buffer;
        sndmix.mB0[i] = (int *)buffer + 2;
        while ((u32)sndmix.mB0[i] & 0x3F) {
            sndmix.mB0[i]++;
        }
    }
    for (i = 0; i < sndmix.m0.m9; i++) {
        void *buffer = SNDMEMI_allocz(704);

        sndmix.mB8[i] = buffer;
        sndmix.mD0[i] = (int *)buffer;
        while ((u32)sndmix.mD0[i] & 0x3F) {
            sndmix.mD0[i]++;
        }
    }
    if (sndmix.m0.m8 != 0) {
        float *p;

        sndmix.m1DC = (Record_803B5010 *)SNDMEMI_allocz(
            sndmix.m0.m8 * sizeof(Record_803B5010) + lbl_8030002C * sizeof(float) * sndmix.m0.m8 +
            lbl_8030002C * sizeof(float) * sndmix.m0.m8);
        memset(sndmix.m1DC, 0,
               sndmix.m0.m8 * sizeof(Record_803B5010) + lbl_8030002C * sizeof(float) * sndmix.m0.m8 +
            lbl_8030002C * sizeof(float) * sndmix.m0.m8);
        p = (float *)&sndmix.m1DC[sndmix.m0.m8];
        for (i = 0; i < sndmix.m0.m8; i++) {
            sndmix.m1DC[i].m34 = p;
            p += lbl_8030002C;
            sndmix.m1DC[i].m38 = p;
            p += lbl_8030002C;
        }
    }
    SNDSYS_leavecritical();
    MIXI_initunpack16();
    MIXI_initunpackxa();
    MIXI_initunpackmt();
    MIX_reset();
    for (i = 0; i < sndmix.m0.m9; i++) {
        sndmix.m104[i] = 0;
        SFILTER_ft24_32init(&sndmix.m134[i]);
        sndmix.m134[i].m18 = 0;
        sndmix.m134[i].m1A = 0;
        SFILTER_add(&sndmix.m104[i], &sndmix.m134[i]);
        memset(sndmix.mD0[i], 0, 640);
    }
}

void MIX_destroy(void)
{
    int i;

    SNDSYS_entercritical();
    MIX_destroyFxglobals();
    if (sndmix.m1DC != 0) {
        SNDMEMI_free(sndmix.m1DC);
        sndmix.m1DC = 0;
    }
    for (i = 0; i < 2; i++) {
        if (sndmix.mA8[i] != 0) {
            SNDMEMI_free(sndmix.mA8[i]);
            sndmix.mA8[i] = 0;
        }
    }
    for (i = 0; i < sndmix.m0.m9; i++) {
        if (sndmix.mB8[i] != 0) {
            SNDMEMI_free(sndmix.mB8[i]);
            sndmix.mB8[i] = 0;
        }
    }
    SNDMIX_setmasterlowpass(2.0f);
    SNDSYS_leavecritical();
}

void MIX_reset(void)
{
    sndmix.m1E0 = mixc;
    sndmix.m1E4 = decode16x87;
    sndmix.mC = 320;
}

void MIX_playinit(int index, int type, int mode, int a, int b, void *data, int c, int d, int e, int f, int g, int h,
                 int k, int slot)
{
    Record_803B5010 *record = &sndmix.m1DC[index];
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
    if (sndmix.m18[kind][table] != 0) {
        record->m48 = (Node_80279D90 *)SNDMEMI_allocz(sndmix.m60[kind][table]);
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
        sndmix.m18[kind][table](record->m48, &params);
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
    Record_803B5010 *record = &sndmix.m1DC[index];
    int i;

    record->m1 = 0;
    record->m3C = 0.0f;
    for (i = 0; i < lbl_8030002C; i++) {
        record->m34[i] = record->m38[i];
    }
    for (i = 0; i < sndmix.m0.m9; i++) {
        record->m4[i] = record->m1C[i];
    }
    record->m0 = 2;
}

void MIXI_stop(int index)
{
    MIX_stop(index);
    sndmix.m0.m4(index);
}

void MIX_stop(int index)
{
    Record_803B5010 *record = &sndmix.m1DC[index];
    Node_80279D90 *next;
    int i;

    for (i = 0; i < lbl_8030002C; i++) {
        sndmix.m100[i] += record->m34[i] * record->m3C;
    }
    for (i = 0; i < sndmix.m0.m9; i++) {
        sndmix.mE8[i] += record->m4[i] * record->m3C;
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
    sndmix.m1DC[index].m1C[channel] = value;
    sndmix.m1DC[index].m1 = 1;
}

void SNDMIX_setwetgain(int index, int slot, float value)
{
    sndmix.m1DC[index].m38[slot] = value;
    sndmix.m1DC[index].m1 = 1;
}

void MIX_audioslice(void **outputs, int count)
{
    Record_803B5010 *record;
    int done;
    int left;
    int n;
    int i;
    int j;

    for (i = 0; i < lbl_8030002C; i++) {
        if (sndmix.m14[i] != 0 && sndmix.m100[i] != 0.0f) {
            MIXI_interpolateto0(&sndmix.m100[i], sndfx.m0[i]);
        }
    }
    for (i = 0; i < sndmix.m0.m9; i++) {
        memset(sndmix.mD0[i], 0, count * 4);
        if (sndmix.mE8[i] != 0.0f) {
            MIXI_interpolateto0(&sndmix.mE8[i], (float *)sndmix.mD0[i]);
        }
    }
    for (i = 0; i < sndmix.m0.m8; i++) {
        record = &sndmix.m1DC[i];
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
                n = record->m40->m0(record->m40, left, (float *)sndmix.mB0[0], (float *)sndmix.mB0[1], 0);
                if (n < 0) {
                    MIXI_stop(i);
                } else if (n != 0) {
                    record->m3C = ((float *)sndmix.mB0[1])[n - 1];
                    for (j = 0; j < sndmix.m0.m9; j++) {
                        if (record->m1C[j] != 0.0f) {
                            sndmix.m1E0(n, (float *)sndmix.mB0[1], (float *)sndmix.mD0[j] + done,
                                              record->m1C[j]);
                        }
                    }
                    for (j = 0; j < lbl_8030002C; j++) {
                        if (sndmix.m14[j] != 0 && record->m38[j] != 0.0f) {
                            sndmix.m1E0(n, (float *)sndmix.mB0[1], sndfx.m0[j] + done, record->m38[j]);
                            sndfx.m4 = 0;
                        }
                    }
                }
            }
        }
    }
    if (sndmix.m10 != 0) {
        sndmix.m10(count);
    }
    for (i = 0; i < sndmix.m0.m9; i++) {
        if (sndmix.m11C[i] != 0) {
            sndmix.m11C[i]->m0(sndmix.m11C[i], count, (float *)sndmix.mD0[i], (float *)sndmix.mB0[0], 0);
            sndmix.m104[i]->m0(sndmix.m104[i], count, (float *)sndmix.mB0[0], (float *)outputs[i], 0);
        } else {
            sndmix.m104[i]->m0(sndmix.m104[i], count, (float *)sndmix.mD0[i], (float *)outputs[i], 0);
        }
    }
    if (lbl_803A6E58 != 0) {
        MIXoutputfn(outputs, count);
    }
}
