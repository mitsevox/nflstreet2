#include "engine/fn_801F7BD4.h"
#include "engine/fn_801F8014.h"
#include "game/fn_801D2B7C.h"

extern unsigned char lbl_803EBD7C;
extern Lock_801F8014 lbl_8039ADF4;
extern unsigned int lbl_803ECF58;
extern unsigned int lbl_803ECF5C;
extern unsigned int lbl_803ECF60;
extern unsigned int lbl_803ECF64;
extern unsigned int lbl_803ECF68;
extern unsigned char *lbl_803ECF6C;
extern unsigned int lbl_803ED5EC;
extern unsigned char lbl_803EBD6C[8];

void *fn_801C1FBC();
int fn_801D34D0(void *p, unsigned int size, int value, int flags);

int fn_801EC1B4(unsigned int numTables, unsigned int numEntries, unsigned int numInputs)
{
    int err = 0;

    if (lbl_803EBD7C == 0) {
        fn_801F7FA8(&lbl_8039ADF4);
        fn_801F8014(&lbl_8039ADF4);
        lbl_803ECF58 = numTables;
        lbl_803ECF5C = numEntries;
        lbl_803ECF60 = numInputs;
        lbl_803ECF6C = 0;
        lbl_803ECF64 = numEntries * numInputs * 2;
        lbl_803ECF68 = lbl_803ECF64 * numTables;
        if (lbl_803ECF68 != 0) {
            lbl_803ECF6C = fn_801D2BB0(1, lbl_803ECF68, 0, 0);
            if (lbl_803ECF6C == 0) {
                err = fn_801F7C88();
            } else {
                fn_801D34D0(lbl_803ECF6C, lbl_803ECF68, 0, 2);
                lbl_803EBD7C = 1;
            }
        } else {
            lbl_803EBD7C = 1;
        }
        fn_801F809C(&lbl_8039ADF4);
    } else {
        err = 0x180001;
    }
    fn_801F7BD4(err);
    return err;
}

int fn_801EC298(void)
{
    int err = 0;

    if (lbl_803EBD7C != 0) {
        fn_801F8014(&lbl_8039ADF4);
        if (lbl_803ECF6C != 0) {
            fn_801D2BD0(lbl_803ECF6C);
        }
        fn_801F809C(&lbl_8039ADF4);
        fn_801F80D0(&lbl_8039ADF4);
        lbl_803EBD7C = 0;
    } else {
        err = 0x180002;
    }
    fn_801F7BD4(err);
    return err;
}

int fn_801EC314(unsigned int table, unsigned int start, unsigned int count, void *pData)
{
    int err = 0;

    if (start + count <= lbl_803ECF5C && table < lbl_803ECF58 && count != 0) {
        fn_801C1FBC((unsigned short *)(lbl_803ECF6C + table * lbl_803ECF64) + start * lbl_803ECF60, pData,
                    count * lbl_803ECF60 * sizeof(unsigned short));
    } else {
        err = 0x180003;
    }
    fn_801F7BD4(err);
    return err;
}

int fn_801EC3B8(unsigned int dst, unsigned int src)
{
    int err = 0x180003;

    if (src < lbl_803ECF58 && dst < lbl_803ECF58) {
        fn_801EC314(dst, 0, lbl_803ECF5C, lbl_803ECF6C + src * lbl_803ECF64);
        err = 0;
    }
    return err;
}

float fn_801EC418(unsigned int table, unsigned int entry, unsigned char *pInputs)
{
    int err = 0;
    float result = 0.0f;
    float value;
    unsigned short *pCode;
    unsigned int code;
    unsigned char index;
    unsigned int i;

    if (table < lbl_803ECF58 && entry < lbl_803ECF5C) {
        pCode = (unsigned short *)(lbl_803ECF6C + table * lbl_803ECF64) + entry * lbl_803ECF60;
        for (i = 0; i < lbl_803ECF60; i++) {
            code = pCode[i];
            if (code == 0) {
                break;
            }
            if (code & 0x2000) {
                value = ((float)(signed char)pInputs[code & 0xFF] + 128.0f) * (1.0f / 255.0f);
            } else if (code & 0x4000) {
                value = (float)(signed char)pInputs[code & 0xFF] * (1.0f / 127.0f);
            } else {
                index = code & 0xFF;
                if (lbl_803EBD6C[index & 7] & pInputs[lbl_803ED5EC + (index >> 3)]) {
                    value = 1.0f;
                } else {
                    value = 0.0f;
                }
            }
            if (code & 0x100) {
                if (value != 0.0f) {
                    value = 0.0f;
                } else {
                    value = 1.0f;
                }
            }
            if (code & 0x200) {
                value = -value;
            }
            if (code & 0x400) {
                if (!(value >= 0.0f)) {
                    value = 0.0f;
                }
            }
            if (code & 0x800) {
                if (!(value <= 0.0f)) {
                    value = 0.0f;
                }
            }
            if ((code & 0x1000) && i != 0) {
                if (value == 0.0f) {
                    value = 1.0f;
                } else if (result == 0.0f) {
                    result = 1.0f;
                }
            }
            if (i == 0) {
                result = value;
            } else {
                result *= value;
            }
        }
    } else {
        err = 0x180003;
        result = 0.0f;
    }
    fn_801F7BD4(err);
    return result;
}
