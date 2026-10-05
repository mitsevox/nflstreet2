#include "game/fn_802372EC.h"

struct Table_800680A8 {
    char mUnknown0[4];
    int mUnknown4;
    unsigned int mUnknown8;
    int mUnknownC;
    unsigned int mUnknown10;
};

typedef int (*Callback_800680A8)(int index, int operand, int value, unsigned short *pRow);

static Callback_800680A8 lbl_803EA678 = 0;

extern "C" {
int fn_80067F18(int index, unsigned short code, short value, unsigned short *pRow)
{
    int result = 0;
    int operand = code << 19;

    operand >>= 19;
    switch (code & 0xE000) {
    case 0x2000:
        if (value > operand) {
            result = 1;
        }
        break;
    case 0xE000:
        result = 1;
        break;
    case 0x4000:
        if (value < operand) {
            result = 1;
        }
        break;
    case 0x6000:
        if (value != operand) {
            result = 1;
        }
        break;
    case 0x0000:
        if (value == operand) {
            result = 1;
        }
        break;
    case 0x8000:
        if (lbl_803EA678 != 0) {
            result = lbl_803EA678(index, operand, value, pRow);
        } else if (value == operand) {
            result = 1;
        }
        break;
    case 0xA000:
        if ((short)fn_802372EC(1, value) < operand) {
            result = 1;
        }
        break;
    }
    return result;
}

int fn_80068030(unsigned int count, unsigned short *pCodes, short *pValues, unsigned short *pRow)
{
    int result = 1;
    unsigned int i;

    for (i = 0; i < count; i++) {
        if (!fn_80067F18(i, *pCodes, *pValues, pRow)) {
            result = 0;
            break;
        }
        pCodes++;
        pValues++;
    }
    return result;
}

unsigned int fn_800680A8(Table_800680A8 *pTable, short *pValues, unsigned short **ppOut, unsigned int max,
                         Callback_800680A8 pCallback)
{
    unsigned short *pRow = (unsigned short *)((char *)pTable + pTable->mUnknown4);
    unsigned int found = 0;
    unsigned int i;

    lbl_803EA678 = pCallback;
    for (i = 0; i < pTable->mUnknown8; i++) {
        if (fn_80068030(pTable->mUnknown10, pRow + pTable->mUnknownC, pValues, pRow)) {
            ppOut[found] = pRow;
            if (++found >= max) {
                break;
            }
        }
        pRow += pTable->mUnknownC + pTable->mUnknown10;
    }
    return found;
}
}
