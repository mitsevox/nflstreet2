/* Reads variable-length string and blob columns out of T3DB tables, Huffman-decoding them when
   the table stores them compressed. */

#include <string.h>
#include "engine/t3db_table.h"

static void _TDbBlobHuffDecode(TDbHuffNode_t *pTree, unsigned char *pBits, int count, unsigned char *pOut)
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

void _TDbBlobGetData(TDbTable_t *pTable, TDbColumn_t *pColumn, void *pRow, unsigned char *pOut)
{
    int offset;
    unsigned int len;

    _TDbDataGetBitData(pRow, pColumn->mBitOffset, 32, (unsigned int *)&offset, 0);
    len = 0;
    if (offset != -1) {
        switch (pColumn->mType) {
        case 15:
            len = pTable->mExtraData[offset++] << 24;
            len |= pTable->mExtraData[offset++] << 16;
        case 14:
            len |= pTable->mExtraData[offset++] << 8;
        case 13:
            len |= pTable->mExtraData[offset++];
        }
        if (pTable->mFlags & 0x40) {
            _TDbBlobHuffDecode((TDbHuffNode_t *)pTable->mExtraData, pTable->mExtraData + offset, len, pOut);
        } else {
            memcpy(pOut, pTable->mExtraData + offset, len);
        }
    }
    pOut[len] = 0;
}
