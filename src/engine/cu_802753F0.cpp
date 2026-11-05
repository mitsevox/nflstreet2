/* Sound mixer set-up (neutral file name): the mixer tables and the callbacks the driver installs,
   then each voice's play, stop and gain records. */

#include "engine/sndlib.h"


float *fn_802753F0(int index)
{
    return lbl_803B4E24[index];
}

void fn_80275404(void)
{
    int size = lbl_8030002C * sizeof(float *) + lbl_8030002C * sizeof(int) + lbl_8030002C * sizeof(float);
    float **buffer = (float **)fn_8026B5D4(size);

    lbl_803B4E24 = buffer;
    lbl_803B4E34.m14 = (int *)(buffer + lbl_8030002C);
    lbl_803B4E34.m100 = (float *)(lbl_803B4E34.m14 + lbl_8030002C);
    memset(buffer, 0, size);
    lbl_803B4E20 = (Node_803B4E20 **)fn_8026B5D4(lbl_8030002C * 4);
    memset(lbl_803B4E20, 0, lbl_8030002C * 4);
    lbl_80300E98 = 1;
}

void fn_802754A8(void)
{
    int i;

    if (lbl_80300E98 != 0) {
        fn_8026B7D8(lbl_803B4E24);
        for (i = 0; i < lbl_8030002C; i++) {
            if (lbl_803B4E20[i] != 0) {
                Node_803B4E20 *node = lbl_803B4E20[i];

                do {
                    Node_803B4E20 *next = node->m0;

                    fn_8026B7D8(node);
                    node = next;
                } while (node != 0);
            }
        }
        fn_8026B7D8(lbl_803B4E20);
        lbl_80300E98 = 0;
    }
}

void fn_8027555C(void)
{
    lbl_803B5028 = fn_80275BBC;
    lbl_803B502C = fn_80275E7C;
    lbl_803B5030 = fn_802763E0;
    lbl_803B5034 = fn_80275F80;
    lbl_803B5038 = fn_80276194;
    lbl_803B503C = fn_80276278;
    lbl_803B5040 = fn_80276A84;
}

void fn_80275948(float value)
{
}

void *fn_80275B7C(int size)
{
    return fn_8026B5D4(size);
}

void fn_80275B9C(void *p)
{
    fn_8026B7D8(p);
}

void fn_80275BBC(Setup_80272EC4 *setup)
{
    int i;

    fn_802797F4(fn_80275B7C);
    fn_80279800(fn_80275B9C);
    fn_8027980C(fn_8026B2E0);
    lbl_803B4E34.m0 = *setup;
    fn_8026D0AC();
    fn_80275404();
    for (i = 0; i < lbl_8030002C; i++) {
        lbl_803B4E34.m14[i] = 0;
    }
    for (i = 0; i < 2; i++) {
        void *buffer = fn_8026B5D4(2748);

        lbl_803B4E34.mA8[i] = buffer;
        lbl_803B4E34.mB0[i] = (int *)buffer + 2;
        while ((u32)lbl_803B4E34.mB0[i] & 0x3F) {
            lbl_803B4E34.mB0[i]++;
        }
    }
    for (i = 0; i < lbl_803B4E34.m0.m9; i++) {
        void *buffer = fn_8026B5D4(704);

        lbl_803B4E34.mB8[i] = buffer;
        lbl_803B4E34.mD0[i] = (int *)buffer;
        while ((u32)lbl_803B4E34.mD0[i] & 0x3F) {
            lbl_803B4E34.mD0[i]++;
        }
    }
    if (lbl_803B4E34.m0.m8 != 0) {
        float *p;

        lbl_803B4E34.m1DC = (Record_803B5010 *)fn_8026B5D4(
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
    fn_8026D0EC();
    fn_8027A7FC();
    fn_8027A8A4();
    fn_8027A844();
    fn_80275F54();
    for (i = 0; i < lbl_803B4E34.m0.m9; i++) {
        lbl_803B4E34.m104[i] = 0;
        fn_80279C20(&lbl_803B4E34.m134[i]);
        lbl_803B4E34.m134[i].m18 = 0;
        lbl_803B4E34.m134[i].m1A = 0;
        fn_80279D90(&lbl_803B4E34.m104[i], &lbl_803B4E34.m134[i]);
        memset(lbl_803B4E34.mD0[i], 0, 640);
    }
}

void fn_80275F54(void)
{
    lbl_803B4E34.m1E0 = fn_8027A8EC;
    lbl_803B4E34.m1E4 = fn_802774C8;
    lbl_803B4E34.mC = 320;
}

void fn_80275F80(int index, int type, int mode, int a, int b, void *data, int c, int d, int e, int f, int g, int h,
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
        record->m48 = (Node_80279D90 *)fn_8026B5D4(lbl_803B4E34.m60[kind][table]);
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
        record->m4C = (Node_80279D90 *)fn_8026B5D4(6196);
        record->m4C->m4 = 0;
        record->m4C->m18 = 200;
        record->m4C->m1A = slot;
        fn_80277404(record->m4C, data, index);
        fn_80279D90(&record->m40, record->m4C);
    }
    record->m0 = 1;
}

void fn_80276238(int index)
{
    fn_80276278(index);
    lbl_803B4E34.m0.m4(index);
}

void fn_80276278(int index)
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
        fn_8026B7D8(record->m40);
        record->m40 = next;
    } while (next != 0);
    record->m0 = 0;
}

void fn_80276378(int index, int channel, float value)
{
    lbl_803B4E34.m1DC[index].m1C[channel] = value;
    lbl_803B4E34.m1DC[index].m1 = 1;
}

void fn_802763AC(int index, int slot, float value)
{
    lbl_803B4E34.m1DC[index].m38[slot] = value;
    lbl_803B4E34.m1DC[index].m1 = 1;
}

void fn_80276798(int index, int slot, Desc_80276798 *desc)
{
    Record_803B5010 *record = &lbl_803B4E34.m1DC[index];
    Node_80279D90 *node = (Node_80279D90 *)fn_8026B5D4(desc->m4);

    desc->mC(node, desc->m0, slot);
    node->m18 = desc->mA;
    node->m0 = desc->m10;
    node->m4 = desc->m14;
    node->m1A = 0;
    fn_80279D90(&record->m40, node);
}

int fn_80276820(int index)
{
    Record_803B5010 *record = &lbl_803B4E34.m1DC[index];

    if (record->m44 != 0) {
        return record->m44(record->m48);
    }
    return -1;
}

void fn_80276868(int index, int value)
{
    Record_803B5010 *record = &lbl_803B4E34.m1DC[index];
    Node_80279D90 *node;
    Params_80279D0C params;

    if (value > 0) {
        node = record->m58;
        if (node == 0) {
            record->m58 = (Node_80279D90 *)fn_8026B5D4(88);
            record->m58->m4 = 0;
            record->m58->m18 = 80;
            record->m58->m1A = 0;
            fn_80279CB8(record->m58);
            fn_80279D90(&record->m40, record->m58);
        }
        params.m0 = value << 8;
        params.m4 = lbl_803A6C24.m1C.mA << 8;
        fn_80279D0C(record->m58, &params);
    } else if (record->m58 != 0) {
        fn_80279DF8(&record->m40, record->m58);
        fn_8026B7D8(record->m58);
        record->m58 = 0;
    }
}

void fn_80276A84(int index, int value)
{
    Record_803B5010 *record = &lbl_803B4E34.m1DC[index];
    Node_80279D90 *node;
    int flag = 0;

    if (value > 0x40000) {
        value = 0x40000;
    }
    node = record->m50;
    if (node == 0) {
        record->m50 = (Node_80279D90 *)fn_8026B5D4(60);
        if (lbl_803B4E34.mE > 49) {
            flag = 1;
        }
        record->m50->m4 = 0;
        record->m50->m18 = 160;
        record->m50->m1A = 0;
        fn_8027A7A0(record->m50, lbl_803A6C24.m16F, flag);
        fn_80279D90(&record->m40, record->m50);
    }
    fn_8027A4C0(record->m50, value);
}

void fn_80276B40(int index, int value)
{
    Record_803B5010 *record = &lbl_803B4E34.m1DC[index];

    if (record->m4C != 0) {
        fn_80277240(record->m4C);
    }
}
