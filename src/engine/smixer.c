/* Software mixer (smixer.c): creates and destroys the main-CPU mixer, starts, plays and stops voices
   through their filter chains, sets their dry and wet gains and mixes each audio slice. */

#include "engine/sndlib.h"

void SNDMIX_setmasterlowpass(float value)
{
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
    fn_8027A7FC();
    fn_8027A8A4();
    fn_8027A844();
    MIX_reset();
    for (i = 0; i < lbl_803B4E34.m0.m9; i++) {
        lbl_803B4E34.m104[i] = 0;
        fn_80279C20(&lbl_803B4E34.m134[i]);
        lbl_803B4E34.m134[i].m18 = 0;
        lbl_803B4E34.m134[i].m1A = 0;
        fn_80279D90(&lbl_803B4E34.m104[i], &lbl_803B4E34.m134[i]);
        memset(lbl_803B4E34.mD0[i], 0, 640);
    }
}

void MIX_reset(void)
{
    lbl_803B4E34.m1E0 = fn_8027A8EC;
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
        fn_80279D90(&record->m40, record->m48);
    }
    if (data != 0) {
        if (mode != 0) {
            index = -1;
        }
        record->m4C = (Node_80279D90 *)SNDMEMI_allocz(6196);
        record->m4C->m4 = 0;
        record->m4C->m18 = 200;
        record->m4C->m1A = slot;
        fn_80277404(record->m4C, data, index);
        fn_80279D90(&record->m40, record->m4C);
    }
    record->m0 = 1;
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
