#include "engine/tmlib.h"

extern void fn_80201D94(void *pRecord, int bitOffset, int bitSize, void *pValue, int bSigned);

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

void fn_8020CD9C(TDbTable_8020B564 *pTable, TDbField_8020B564 *pField, void *pRecord, unsigned char *pOut)
{
    int offset;
    unsigned int len;

    fn_80201D94(pRecord, pField->mOffset, 32, &offset, 0);
    len = 0;
    if (offset != -1) {
        switch (pField->mType) {
        case 15:
            len = pTable->mpBlob[offset++] << 24;
            len |= pTable->mpBlob[offset++] << 16;
        case 14:
            len |= pTable->mpBlob[offset++] << 8;
        case 13:
            len |= pTable->mpBlob[offset++];
        }
        if (pTable->mFlags & 0x40) {
            fn_8020CD2C((HuffNode_8020CD2C *)pTable->mpBlob, pTable->mpBlob + offset, len, pOut);
        } else {
            memcpy(pOut, pTable->mpBlob + offset, len);
        }
    }
    pOut[len] = 0;
}
