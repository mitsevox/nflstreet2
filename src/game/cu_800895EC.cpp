#include "game/fn_801D2B7C.h"
extern "C" {
}

struct Object_803EC87C {
    unsigned int *mpTable;
    unsigned int mValue;
};

static Object_803EC87C lbl_803EC87C;

extern "C" {
static unsigned int fn_800895EC(unsigned int value)
{
    unsigned char bit = 8;

    do {
        if (value & 1) {
            value = (value >> 1) ^ 0xEDB88320;
        } else {
            value >>= 1;
        }
    } while (--bit != 0);
    return value;
}

static void fn_80089620(unsigned int *pTable)
{
    unsigned int i;

    for (i = 0; i < 256; i++) {
        pTable[i] = fn_800895EC(i);
    }
}

void fn_80089668(void)
{
    lbl_803EC87C.mpTable = (unsigned int *)fn_801D2B7C(1024, 0, 0);
    fn_80089620(lbl_803EC87C.mpTable);
    lbl_803EC87C.mValue = 0xFFFFFFFF;
}

void fn_800896A8(void *pData, unsigned int size)
{
    unsigned int crc = lbl_803EC87C.mValue;
    unsigned int i;

    for (i = 0; i < size; i++) {
        crc = (crc >> 8) ^ lbl_803EC87C.mpTable[(crc & 0xFF) ^ ((unsigned char *)pData)[i]];
    }
    lbl_803EC87C.mValue = crc;
}

void fn_800896EC(unsigned int *pResult)
{
    fn_801D2BD0(lbl_803EC87C.mpTable);
    lbl_803EC87C.mpTable = 0;
    if (pResult != 0) {
        *pResult = ~lbl_803EC87C.mValue;
    }
}
}
