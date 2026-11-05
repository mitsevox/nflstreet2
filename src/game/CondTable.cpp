/* Condition tables: each row carries coded tests (equal, greater, less, not
   equal, random, custom); finds the rows whose tests all pass for a set of
   values. */

#include "game/fn_802372EC.h"

struct CondTable_t {
    char mUnknown0[4];
    int mUnknown4;
    unsigned int mUnknown8;
    int mUnknownC;
    unsigned int mUnknown10;
};

typedef int (*CondTableTestFn_t)(unsigned int index, int operand, int value, unsigned short *pRow);

static CondTableTestFn_t _CondTable_pfnTest = 0;

extern "C" {
int CondTableTestCode(int index, unsigned short code, short value, unsigned short *pRow)
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
        if (_CondTable_pfnTest != 0) {
            result = _CondTable_pfnTest(index, operand, value, pRow);
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

int CondTableTestRow(unsigned int count, unsigned short *pCodes, short *pValues, unsigned short *pRow)
{
    int result = 1;
    unsigned int i;

    for (i = 0; i < count; i++) {
        if (!CondTableTestCode(i, *pCodes, *pValues, pRow)) {
            result = 0;
            break;
        }
        pCodes++;
        pValues++;
    }
    return result;
}

unsigned int CondTableFindRows(CondTable_t *pTable, short *pValues, unsigned short **ppOut, unsigned int max,
                         CondTableTestFn_t pCallback)
{
    unsigned short *pRow = (unsigned short *)((char *)pTable + pTable->mUnknown4);
    unsigned int found = 0;
    unsigned int i;

    _CondTable_pfnTest = pCallback;
    for (i = 0; i < pTable->mUnknown8; i++) {
        if (CondTableTestRow(pTable->mUnknown10, pRow + pTable->mUnknownC, pValues, pRow)) {
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
