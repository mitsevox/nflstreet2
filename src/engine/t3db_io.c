#include <string.h>
#include "engine/t3db.h"

unsigned int lbl_802F9548[256] = { 0 };

extern void fn_8020C5C8(TDbTable_801FAA00 *pTable, unsigned short count);
int fn_801FAEDC(TDbTable_801FAA00 *pTable, TDbIOStream_801FA8C8 *pStream, int mode);
int fn_801FB5C0(TDbTable_801FAA00 *pTable, TDbIOStream_801FA8C8 *pStream, int mode);

static inline unsigned short TDbTableFree_801FAAF8(TDbTable_801FAA00 *pTable)
{
    return pTable->mCapacity - pTable->mRowCount;
}

static inline void TDbRowSetBit_801FAEDC(TDbTable_801FAA00 *pTable, unsigned int row)
{
    unsigned char *pRow = pTable->mRows + pTable->mRowSize * row;
    unsigned int bit = pTable->mDeletedBit;

    pRow += bit >> 3;
    *pRow |= 1 << (7 - (bit & 7));
}

void fn_801FA870(void)
{
    unsigned short i;
    unsigned short j;
    int crc;

    for (i = 0; i <= 0xFF; i++) {
        crc = i << 24;
        for (j = 8; j != 0; j--) {
            crc = crc < 0 ? (crc << 1) ^ 0x04C11DB7 : crc << 1;
        }
        lbl_802F9548[i] = crc;
    }
}

int fn_801FA8C8(TDbIOStream_801FA8C8 *pStream, void *pData, unsigned int size)
{
    unsigned int done;
    int err;

    err = pStream->mDevice->mWrite(pStream->mHandle, pData, size, &done);
    if (err == 0) {
        if (size != done) {
            err = 0x24;
        } else {
            pStream->mOffset += size;
            pStream->mCrcA = fn_801FC950(pData, size, pStream->mCrcA);
            pStream->mCrcB = fn_801FC950(pData, size, pStream->mCrcB);
        }
    }
    return err;
}

int fn_801FA964(TDbIOStream_801FA8C8 *pStream, void *pData, unsigned int size)
{
    unsigned int done;
    int err;

    err = pStream->mDevice->mRead(pStream->mHandle, pData, size, &done);
    if (err == 0) {
        if (size != done) {
            err = 0x24;
        } else {
            pStream->mOffset += size;
            pStream->mCrcA = fn_801FC950(pData, size, pStream->mCrcA);
            pStream->mCrcB = fn_801FC950(pData, size, pStream->mCrcB);
        }
    }
    return err;
}

unsigned int fn_801FAA00(TDbDatabase_801FAA00 *pDb, unsigned int *pOut)
{
    TDbTable_801FAA00 *pTable;
    TDbIndex_801FAA00 *pIndex;
    TDbExpr_801FAA00 *pFilter;
    unsigned int size;
    unsigned int pad;

    size = 0;
    for (pTable = pDb->mTables; pTable != 0; pTable = pTable->mNext) {
        if (pTable->mFlags & 2) {
            pOut[0] = pTable->mUnknown1C;
            pOut[1] = size;
            pOut += 2;
            size += 0x24;
            size += pTable->mColumnCount * sizeof(TDbColumn_801FAA00);
            size += pTable->mCapacity * pTable->mRowSize;
            for (pIndex = pTable->mIndexes; pIndex != 0; pIndex = pIndex->mNext) {
                if (pIndex->mDestroyed == 0) {
                    size += 8;
                    size += pIndex->mTree.mPartCount * 8;
                    pFilter = pIndex->mFilter;
                    if (pFilter != 0) {
                        size += sizeof(TDbExpr_801FAA00);
                        if (pFilter->mLeft.mType <= TDB_TYPE_BINARY) {
                            size += pFilter->mLeft.mSize;
                        }
                        if (pFilter->mRight.mType <= TDB_TYPE_BINARY) {
                            size += pFilter->mRight.mSize;
                        }
                    }
                }
            }
            if ((pTable->mFlags & 0x60) && pTable->mUnknown2C != 0) {
                pad = pTable->mUnknown2C & 7;
                size += pTable->mUnknown2C;
                if (pad) {
                    size += 8 - pad;
                }
            }
            size += 4;
        }
    }
    return size;
}

int fn_801FAAF8(TDbTable_801FAA00 *pTable, TDbIOTableHdr_801FAAF8 *pHdr, int unused, TDbIOStream_801FA8C8 *pStream)
{
    TDbColumn_801FAA00 columns[0xFE];
    TDbIndex_801FAA00 *pIndex;
    unsigned short count;
    unsigned short remaining;
    int appended;
    int err;

    count = pHdr->mRowCount - pHdr->mUnknown14;
    appended = 0;
    if ((pTable->mFlags & 0x60) || (pHdr->mFlags & 0x60)) {
        return 0x31;
    }
    if (count != 0 && (pTable->mFlags & 8) && pTable->mCapacity == 0 && pTable->mUnknown40 != 0) {
        fn_8020C5C8(pTable, pTable->mUnknown40);
    }
    if (count > (unsigned short)(TDbTableFree_801FAAF8(pTable) + pTable->mUnknown46)) {
        return 0x13;
    }
    if (pTable->mColumnCount != pHdr->mColumnCount) {
        return 0x18;
    }
    err = fn_801FA964(pStream, columns, pTable->mColumnCount * sizeof(TDbColumn_801FAA00));
    if (err == 0 && memcmp(pTable->mColumns, columns, pTable->mColumnCount * sizeof(TDbColumn_801FAA00)) != 0) {
        err = 0x18;
    }
    if ((pHdr->mFlags & 0x18) == 0x18) {
        remaining = 0;
    } else {
        remaining = pHdr->mUnknown10;
    }
    if (pHdr->mRowCount != 0) {
        if (pTable->mRowCount == 0 && pHdr->mRowCount <= pTable->mCapacity) {
            appended = 1;
            pTable->mUnknown46 = pHdr->mUnknown14;
            pTable->mRowCount = pHdr->mRowCount;
            pTable->mUnknown48 = pHdr->mUnknown16;
            err = fn_801FA964(pStream, pTable->mRows, pTable->mRowSize * pHdr->mRowCount);
            count = pHdr->mRowCount;
            remaining -= pHdr->mRowCount;
        } else if (pHdr->mUnknown14 == 0 && pHdr->mRowCount <= pTable->mCapacity - pTable->mRowCount) {
            appended = 1;
            err = fn_801FA964(pStream, pTable->mRows + pTable->mRowSize * pTable->mRowCount,
                              pTable->mRowSize * pHdr->mRowCount);
            pTable->mRowCount += pHdr->mRowCount;
            count = pHdr->mRowCount;
            remaining -= pHdr->mRowCount;
        } else {
            while (count != 0 && err == 0) {
                if (count != 0) {
                    err = fn_801FAEDC(pTable, pStream, 0);
                }
                if (err == 0x16) {
                    err = 0;
                } else if (err == 0) {
                    count--;
                }
                remaining--;
            }
        }
    }
    if (remaining != 0) {
        if (pTable->mUnknown46 == 0 && remaining <= pTable->mCapacity - pTable->mRowCount) {
            err = fn_801FA964(pStream, pTable->mRows + pTable->mRowSize * pTable->mRowCount,
                              pTable->mRowSize * remaining);
        } else {
            while (remaining != 0 && err == 0) {
                err = fn_801FAEDC(pTable, pStream, 1);
                if (err == 0x17) {
                    err = 0;
                }
                remaining--;
            }
        }
    }
    if (appended && err == 0) {
        for (pIndex = pTable->mIndexes; pIndex != 0; pIndex = pIndex->mNext) {
            for (count = pTable->mRowCount - count; count < pTable->mRowCount; count++) {
                if (!TDbRowBit_801FAAF8(pTable, count)) {
                    err = fn_8020299C(pIndex, count);
                    if (err != 0) {
                        return err;
                    }
                }
            }
            if (err != 0) {
                break;
            }
        }
    }
    if (err == 0) {
        while (pHdr->mIndexCount != 0) {
            err = fn_801FB5C0(pTable, pStream, 1);
            if (err != 0) {
                break;
            }
            pHdr->mIndexCount--;
        }
    }
    return err;
}

int fn_801FAEDC(TDbTable_801FAA00 *pTable, TDbIOStream_801FA8C8 *pStream, int skip)
{
    unsigned char buffer[0x2000];
    unsigned char *pRow;
    TDbIndex_801FAA00 *pIndex;
    unsigned short row;
    int reused;
    int err;

    err = 0;
    row = 0;
    reused = 0;
    if (!skip) {
        if (pTable->mRowCount < pTable->mCapacity) {
            row = pTable->mRowCount++;
        } else if (pTable->mUnknown46 != 0) {
            row = pTable->mUnknown48;
            reused = 1;
            pTable->mUnknown46--;
            pTable->mUnknown48 = *(unsigned short *)(pTable->mRows + pTable->mRowSize * row);
        } else {
            err = 0x13;
        }
    }
    if (err == 0) {
        if (!skip) {
            pRow = pTable->mRows + pTable->mRowSize * row;
        } else {
            pRow = buffer;
        }
        err = fn_801FA964(pStream, pRow, pTable->mRowSize);
        if (err == 0 && !skip && TDbRowBit_801FAAF8(pTable, row)) {
            err = 0x16;
        }
        if (!skip) {
            if (err == 0) {
                for (pIndex = pTable->mIndexes; pIndex != 0; pIndex = pIndex->mNext) {
                    err = fn_8020299C(pIndex, row);
                    if (err != 0) {
                        break;
                    }
                }
                if (err != 0) {
                    for (pIndex = pTable->mIndexes; pIndex != 0; pIndex = pIndex->mNext) {
                        fn_80202D34(pIndex, row);
                    }
                }
            }
            if (err != 0) {
                if (reused) {
                    memset(pRow, 0, pTable->mRowSize);
                    TDbRowSetBit_801FAEDC(pTable, row);
                    *(unsigned short *)(pTable->mRows + pTable->mRowSize * row) = pTable->mUnknown48;
                    pTable->mUnknown48 = row;
                    pTable->mUnknown46++;
                } else {
                    pTable->mRowCount--;
                }
            }
        }
    }
    return err;
}
