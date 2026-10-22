#include <string.h>
#include "engine/t3db_table.h"

void fn_8020CD2C(HuffNode_8020CD2C *pTree, unsigned char *pBits, int count, unsigned char *pOut)
{
    int i = 0;
    unsigned char bit = 8;

    do {
        unsigned int node = 0;

        do {
            int b;

            if (bit == 0) {
                bit = 8;
                pBits++;
            }
            bit--;
            b = (*pBits >> bit) & 1;
            node = pTree[node].mChild[b][0] | (pTree[node].mChild[b][1] << 8);
        } while (!(node & 0xFF00));
        pOut[i++] = node >> 8;
    } while (count != i);
}

void fn_8020CD9C(TDbTable_801FAA00 *pTable, TDbColumn_801FAA00 *pColumn, void *pRow, unsigned char *pOut)
{
    int offset;
    unsigned int len;

    fn_80201D94(pRow, pColumn->mBitOffset, 32, (unsigned int *)&offset, 0);
    len = 0;
    if (offset != -1) {
        switch (pColumn->mType) {
        case 15:
            len = pTable->mUnknown18[offset++] << 24;
            len |= pTable->mUnknown18[offset++] << 16;
        case 14:
            len |= pTable->mUnknown18[offset++] << 8;
        case 13:
            len |= pTable->mUnknown18[offset++];
        }
        if (pTable->mFlags & 0x40) {
            fn_8020CD2C((HuffNode_8020CD2C *)pTable->mUnknown18, pTable->mUnknown18 + offset, len, pOut);
        } else {
            memcpy(pOut, pTable->mUnknown18 + offset, len);
        }
    }
    pOut[len] = 0;
}
