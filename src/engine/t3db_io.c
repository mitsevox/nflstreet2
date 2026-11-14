/* Reads and writes the table databases used by the game. */
#include <string.h>
#include "engine/t3db.h"
#include "engine/t3db_table.h"

typedef struct TDbIOFileHdr_t {
    union {
        unsigned int mWord;
        unsigned char mBytes[4];
    } mIdentity;
    unsigned char mUnknown4;
    unsigned int mEnd;
    unsigned int mBase;
} TDbIOFileHdr_t;

extern TDbTable_t *fn_8020BA48(TDbDatabase_t *pDb, int id);
extern int fn_8020BD90(TDbTable_t *pTable);
extern int fn_80208204(int dbId, TDbStmt_80205754 *pStmt, TDbResult_8020AD1C *pResult);
int _TDbIOReadExprNode(TDbExpr_t *pExpr, TDbIOStream_t *pStream, int release);

unsigned int crc32_table[256] = { 0 };

extern int fn_8020C5C8(TDbTable_t *pTable, int count);
int _TDbIOReadTableRow(TDbTable_t *pTable, TDbIOStream_t *pStream, int skip);
int _TDbIOReadIndex(TDbTable_t *pTable, TDbIOStream_t *pStream, int mode);

static inline unsigned short _TDbTableAvailableRows(TDbTable_t *pTable)
{
    return pTable->mCapacity - pTable->mRowCount;
}

static inline void _TDbRowSetDeleted(TDbTable_t *pTable, unsigned int row)
{
    unsigned char *pRow = pTable->mRows + pTable->mRowSize * row;
    unsigned int bit = pTable->mDeletedBit;

    pRow += bit >> 3;
    *pRow |= 1 << (7 - (bit & 7));
}

/* Builds the lookup table for the database file checksum. */
void _TDbIOInitCRCTable(void)
{
    unsigned short i;
    unsigned short j;
    int crc;

    for (i = 0; i <= 0xFF; i++) {
        crc = i << 24;
        for (j = 8; j != 0; j--) {
            crc = crc < 0 ? (crc << 1) ^ 0x04C11DB7 : crc << 1;
        }
        crc32_table[i] = crc;
    }
}

/* Accounts for a complete write in both active checksum streams. */
int _TDbIOWriteBuffer(TDbIOStream_t *pStream, void *pData, unsigned int size)
{
    unsigned int done;
    int err;

    err = pStream->mDevice->mWrite(pStream->mHandle, pData, size, &done);
    if (err == 0) {
        if (size != done) {
            err = 0x24;
        } else {
            pStream->mOffset += size;
            pStream->mCrcA = _TDbIOCRC32(pData, size, pStream->mCrcA);
            pStream->mCrcB = _TDbIOCRC32(pData, size, pStream->mCrcB);
        }
    }
    return err;
}

/* Accounts for a complete read in both active checksum streams. */
int _TDbIOReadBuffer(TDbIOStream_t *pStream, void *pData, unsigned int size)
{
    unsigned int done;
    int err;

    err = pStream->mDevice->mRead(pStream->mHandle, pData, size, &done);
    if (err == 0) {
        if (size != done) {
            err = 0x24;
        } else {
            pStream->mOffset += size;
            pStream->mCrcA = _TDbIOCRC32(pData, size, pStream->mCrcA);
            pStream->mCrcB = _TDbIOCRC32(pData, size, pStream->mCrcB);
        }
    }
    return err;
}

/* Builds the saved-table directory and calculates its payload size. */
unsigned int _TDbIODatabaseSaveSize(TDbDatabase_t *pDb, unsigned int *pOut)
{
    TDbTable_t *pTable;
    TDbIndex_t *pIndex;
    TDbExpr_t *pFilter;
    unsigned int size;
    unsigned int pad;

    size = 0;
    for (pTable = pDb->mTables; pTable != 0; pTable = pTable->mNext) {
        if (pTable->mFlags & 2) {
            pOut[0] = pTable->mId;
            pOut[1] = size;
            pOut += 2;
            size += 0x24;
            size += pTable->mColumnCount * sizeof(TDbColumn_t);
            size += pTable->mCapacity * pTable->mRowSize;
            for (pIndex = pTable->mIndexes; pIndex != 0; pIndex = pIndex->mNext) {
                if (pIndex->mDestroyed == 0) {
                    size += 8;
                    size += pIndex->mTree.mPartCount * 8;
                    pFilter = pIndex->mFilter;
                    if (pFilter != 0) {
                        size += sizeof(TDbExpr_t);
                        if (pFilter->mLeft.mType <= TDB_TYPE_BINARY) {
                            size += pFilter->mLeft.mSize;
                        }
                        if (pFilter->mRight.mType <= TDB_TYPE_BINARY) {
                            size += pFilter->mRight.mSize;
                        }
                    }
                }
            }
            if ((pTable->mFlags & 0x60) && pTable->mExtraSize != 0) {
                pad = pTable->mExtraSize & 7;
                size += pTable->mExtraSize;
                if (pad) {
                    size += 8 - pad;
                }
            }
            size += 4;
        }
    }
    return size;
}

/* Merges serialized rows into an existing table and rebuilds its indexes. */
int _TDbIOReadTableAppend(TDbTable_t *pTable, TDbIOTableHdr_t *pHdr, int unused, TDbIOStream_t *pStream)
{
    TDbColumn_t columns[0xFE];
    TDbIndex_t *pIndex;
    unsigned short count;
    unsigned short remaining;
    int appended;
    int err;

    count = pHdr->mRowCount - pHdr->mDeletedCount;
    appended = 0;
    if ((pTable->mFlags & 0x60) || (pHdr->mFlags & 0x60)) {
        return 0x31;
    }
    if (count != 0 && (pTable->mFlags & 8) && pTable->mCapacity == 0 && pTable->mNominalCapacity != 0) {
        fn_8020C5C8(pTable, pTable->mNominalCapacity);
    }
    if (count > (unsigned short)(_TDbTableAvailableRows(pTable) + pTable->mDeletedCount)) {
        return 0x13;
    }
    if (pTable->mColumnCount != pHdr->mColumnCount) {
        return 0x18;
    }
    err = _TDbIOReadBuffer(pStream, columns, pTable->mColumnCount * sizeof(TDbColumn_t));
    if (err == 0 && memcmp(pTable->mColumns, columns, pTable->mColumnCount * sizeof(TDbColumn_t)) != 0) {
        err = 0x18;
    }
    if ((pHdr->mFlags & 0x18) == 0x18) {
        remaining = 0;
    } else {
        remaining = pHdr->mCapacity;
    }
    if (pHdr->mRowCount != 0) {
        if (pTable->mRowCount == 0 && pHdr->mRowCount <= pTable->mCapacity) {
            appended = 1;
            pTable->mDeletedCount = pHdr->mDeletedCount;
            pTable->mRowCount = pHdr->mRowCount;
            pTable->mFirstDeletedRow = pHdr->mFirstDeletedRow;
            err = _TDbIOReadBuffer(pStream, pTable->mRows, pTable->mRowSize * pHdr->mRowCount);
            count = pHdr->mRowCount;
            remaining -= pHdr->mRowCount;
        } else if (pHdr->mDeletedCount == 0 && pHdr->mRowCount <= pTable->mCapacity - pTable->mRowCount) {
            appended = 1;
            err = _TDbIOReadBuffer(pStream, pTable->mRows + pTable->mRowSize * pTable->mRowCount,
                              pTable->mRowSize * pHdr->mRowCount);
            pTable->mRowCount += pHdr->mRowCount;
            count = pHdr->mRowCount;
            remaining -= pHdr->mRowCount;
        } else {
            while (count != 0 && err == 0) {
                if (count != 0) {
                    err = _TDbIOReadTableRow(pTable, pStream, 0);
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
        if (pTable->mDeletedCount == 0 && remaining <= pTable->mCapacity - pTable->mRowCount) {
            err = _TDbIOReadBuffer(pStream, pTable->mRows + pTable->mRowSize * pTable->mRowCount,
                              pTable->mRowSize * remaining);
        } else {
            while (remaining != 0 && err == 0) {
                err = _TDbIOReadTableRow(pTable, pStream, 1);
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
                if (!_TDbRowIsDeleted(pTable, count)) {
                    err = _TDbIndexRowAdd(pIndex, count);
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
            err = _TDbIOReadIndex(pTable, pStream, 1);
            if (err != 0) {
                break;
            }
            pHdr->mIndexCount--;
        }
    }
    return err;
}

/* Loads a row into a free slot, or consumes it without retaining it. */
int _TDbIOReadTableRow(TDbTable_t *pTable, TDbIOStream_t *pStream, int skip)
{
    unsigned char buffer[0x2000];
    unsigned char *pRow;
    TDbIndex_t *pIndex;
    unsigned short row;
    int reused;
    int err;

    err = 0;
    row = 0;
    reused = 0;
    if (!skip) {
        if (pTable->mRowCount < pTable->mCapacity) {
            row = pTable->mRowCount++;
        } else if (pTable->mDeletedCount != 0) {
            row = pTable->mFirstDeletedRow;
            reused = 1;
            pTable->mDeletedCount--;
            pTable->mFirstDeletedRow = *(unsigned short *)(pTable->mRows + pTable->mRowSize * row);
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
        err = _TDbIOReadBuffer(pStream, pRow, pTable->mRowSize);
        if (err == 0 && !skip && _TDbRowIsDeleted(pTable, row)) {
            err = 0x16;
        }
        if (!skip) {
            if (err == 0) {
                for (pIndex = pTable->mIndexes; pIndex != 0; pIndex = pIndex->mNext) {
                    err = _TDbIndexRowAdd(pIndex, row);
                    if (err != 0) {
                        break;
                    }
                }
                if (err != 0) {
                    for (pIndex = pTable->mIndexes; pIndex != 0; pIndex = pIndex->mNext) {
                        _TDbIndexRowDelete(pIndex, row);
                    }
                }
            }
            if (err != 0) {
                if (reused) {
                    memset(pRow, 0, pTable->mRowSize);
                    _TDbRowSetDeleted(pTable, row);
                    *(unsigned short *)(pTable->mRows + pTable->mRowSize * row) = pTable->mFirstDeletedRow;
                    pTable->mFirstDeletedRow = row;
                    pTable->mDeletedCount++;
                } else {
                    pTable->mRowCount--;
                }
            }
        }
    }
    return err;
}

#if defined(DECOMP_COMPARE)

/* Creates a table from its serialized schema, rows and indexes. */
int _TDbIOReadTableNew(TDbDatabase_t *pDb, TDbIOTableHdr_t *pHdr, int id,
                TDbIOStream_t *pStream)
{
    TDbTable_t *pTable;
    unsigned char pad[8];
    int i;
    int err;

    _TDbMemNotify(2, (int)pDb->mId, id);
    err = TDbExtMemAlloc(pDb->mHeap, pHdr->mColumnCount * sizeof(TDbColumn_t) + 0x4C, &pTable);
    if (err == 0) {
        pTable->mRowSize = pHdr->mRowSize;
        pTable->mCapacity = pHdr->mCapacity;
        pTable->mNominalCapacity = pHdr->mCapacity;
        pTable->mRowCount = pHdr->mRowCount;
        pTable->mColumnCount = pHdr->mColumnCount;
        pTable->mDeletedBit = pHdr->mDeletedBit;
        pTable->mDb = pDb;
        pTable->mId = id;
        pTable->mFlags = pHdr->mFlags;
        pTable->mFlags &= ~1;
        pTable->mRowCount = pHdr->mRowCount;
        pTable->mDeletedCount = pHdr->mDeletedCount;
        pTable->mFirstDeletedRow = pHdr->mFirstDeletedRow;
        pTable->mExtraSize = pHdr->mDataSize;
        pTable->mUnknownC = pTable->mUnknown10 = 0;
        pTable->mIndexes = 0;
        pTable->mRows = 0;
        if ((pTable->mFlags & 0x18) == 0x18) {
            pTable->mCapacity = 0;
        }
        err = _TDbIOReadBuffer(pStream, pTable->mColumns, pTable->mColumnCount * sizeof(TDbColumn_t));
        if (err == 0) {
            if (pTable->mCapacity != 0) {
                err = TDbExtMemAlloc(pDb->mHeap, pTable->mRowSize * pTable->mCapacity, &pTable->mRows);
                if (err == 0) {
                    err = _TDbIOReadBuffer(pStream, pTable->mRows, pTable->mRowSize * pTable->mCapacity);
                    if (err != 0) {
                        TDbExtMemFree(pDb->mHeap, pTable->mRows, pTable->mRowSize * pTable->mCapacity);
                    }
                }
            }
            if (err == 0) {
                if ((pTable->mFlags & 0x60) && err == 0 && pTable->mExtraSize != 0) {
                    err = TDbExtMemAlloc(pDb->mHeap, pTable->mExtraSize, &pTable->mExtraData);
                    if (err == 0) {
                        err = _TDbIOReadBuffer(pStream, pTable->mExtraData, pTable->mExtraSize);
                        if (err == 0) {
                            if (pTable->mExtraSize & 7) {
                                err = pStream->mDevice->mSeek(pStream->mHandle, 8 - (pTable->mExtraSize & 7));
                                memset(pad, 0, sizeof(pad));
                                pStream->mOffset += 8 - (pTable->mExtraSize & 7);
                                pStream->mCrcA = _TDbIOCRC32(pad, 8 - (pTable->mExtraSize & 7), pStream->mCrcA);
                                pStream->mCrcB = _TDbIOCRC32(pad, 8 - (pTable->mExtraSize & 7), pStream->mCrcB);
                            }
                        }
                        if (err != 0) {
                            TDbExtMemFree(pDb->mHeap, pTable->mExtraData, pTable->mExtraSize);
                        }
                    }
                }
            }
        }
        if (err != 0) {
            TDbExtMemFree(pDb->mHeap, pTable, pHdr->mColumnCount * sizeof(TDbColumn_t) + 0x4C);
        }
        if (err == 0) {
            while (pHdr->mIndexCount != 0) {
                err = _TDbIOReadIndex(pTable, pStream, 0);
                if (err != 0) {
                    break;
                }
                pHdr->mIndexCount--;
            }
            if (err != 0) {
                while (pTable->mIndexes != 0) {
                    _TDbIndexDestroy(pTable->mIndexes);
                }
                if ((pTable->mFlags & 0x60) && pTable->mExtraSize != 0) {
                    TDbExtMemFree(pDb->mHeap, pTable->mExtraData, pTable->mExtraSize);
                }
                TDbExtMemFree(pDb->mHeap, pTable->mRows, pTable->mRowSize * pTable->mCapacity);
                TDbExtMemFree(pDb->mHeap, pTable, pHdr->mColumnCount * sizeof(TDbColumn_t) + 0x4C);
            }
            if (err == 0) {
                if (pDb->mTables == 0) {
                    pDb->mTables = pTable;
                } else {
                    pTable->mNext = pDb->mTables;
                    while (pTable->mNext->mNext != 0) {
                        pTable->mNext = pTable->mNext->mNext;
                    }
                    pTable->mNext->mNext = pTable;
                }
                pTable->mNext = 0;
                for (i = 0; i <= 3; i++) {
                    pTable->mCallbacks[i] = 0;
                }
            }
        }
    }
    if (_tDbMemAllocInfoCallback) {
        TDbMemEvent_t event;

        event.mType = 4;
        event.mUnknown4 = -1;
        event.mUnknown8 = -1;
        _tDbMemAllocInfoCallback(&event);
    }
    return err;
}

/* Recreates a saved index, or consumes its records during an append. */
int _TDbIOReadIndex(TDbTable_t *pTable, TDbIOStream_t *pStream, int skip)
{
    TDbExpr_t expr;
    TDbIOIndexHdr_t hdr;
    TDbIndex_t *pIndex = 0;
    TDbIOIndexPart_t part;
    unsigned char i;
    unsigned short row;
    int err;

    err = _TDbIOReadBuffer(pStream, &hdr, sizeof(hdr));
    if (err == 0) {
        if (!skip) {
            if (hdr.mPartCount <= 2) {
                err = __TDbMemPoolAlloc(&_tDbIndexPool, &pIndex);
                pIndex->mFlags = 4;
            } else {
                err = TDbExtMemAlloc(pTable->mDb->mHeap,
                    sizeof(TDbIndex_t) + (hdr.mPartCount - 1) * sizeof(TDbIdxPart_t), &pIndex);
                pIndex->mFlags = 0;
            }
        }
        if (err == 0) {
            if (!skip) {
                pIndex->mLocked = 0;
                pIndex->mCount = 0;
                pIndex->mDestroyed = 0;
                pIndex->mFilter = 0;
                pIndex->mNext = 0;
                pIndex->mTable = pTable;
                pIndex->mId = hdr.mId;
                pIndex->mTree.mPartCount = hdr.mPartCount;
                pIndex->mTree.mAllowDuplicates = hdr.mAllowDuplicates;
                pIndex->mTree.mRoot = 0;
            }
            for (i = 0; i < hdr.mPartCount; i++) {
                err = _TDbIOReadBuffer(pStream, &part, sizeof(part));
                if (err == 0) {
                    if (!skip) {
                        pIndex->mTree.mParts[i].mAscending = part.mAscending;
                        pIndex->mTree.mParts[i].mColumn = part.mColumn;
                        if (pTable->mColumns[part.mColumn].mType <= TDB_TYPE_BINARY) {
                            pIndex->mFlags |= 1;
                        }
                        pIndex->mTree.mParts[i].mTable = pTable;
                    }
                } else {
                    break;
                }
            }
            if (hdr.mHasFilter == 1 && err == 0) {
                err = _TDbIOReadExprNode(&expr, pStream, skip);
                if (err == 0 && !skip) {
                    err = _TDbExprPrepare(&expr, &pIndex->mFilter, &pTable, 1, 1);
                }
            }
            if (!skip) {
                if (err == 0) {
                    err = _TDbMemPoolInit(&pIndex->mPool, pTable->mDb->mHeap,
                        sizeof(TDbIdxNode_t) + (hdr.mPartCount - 1) * sizeof(unsigned int),
                        pTable->mCapacity + 5, 100);
                }
                if (err != 0) {
                    if (pIndex->mFlags & 4) {
                        __TDbMemPoolFree(&_tDbIndexPool, pIndex);
                    } else {
                        TDbExtMemFree(pTable->mDb->mHeap, pIndex,
                            sizeof(TDbIndex_t) + (hdr.mPartCount - 1) * sizeof(TDbIdxPart_t));
                    }
                    pIndex = 0;
                }
            }
        }
    }
    if (!skip && err == 0) {
        for (row = 0; row < pTable->mRowCount; row++) {
            if (!_TDbRowIsDeleted(pTable, row)) {
                err = _TDbIndexRowAdd(pIndex, row);
                if (err != 0) {
                    break;
                }
            }
        }
        if (err != 0) {
            _TDbMemPoolDeinit(&pIndex->mPool);
            if (pIndex->mFlags & 4) {
                __TDbMemPoolFree(&_tDbIndexPool, pIndex);
            } else {
                TDbExtMemFree(pTable->mDb->mHeap, pIndex,
                    sizeof(TDbIndex_t) + (hdr.mPartCount - 1) * sizeof(TDbIdxPart_t));
            }
        }
        if (err == 0) {
            if (pTable->mIndexes == 0) {
                pTable->mIndexes = pIndex;
            } else {
                pIndex->mNext = pTable->mIndexes;
                while (pIndex->mNext->mNext != 0) {
                    pIndex->mNext = pIndex->mNext->mNext;
                }
                pIndex->mNext->mNext = pIndex;
            }
            pIndex->mNext = 0;
        }
    }
    return err;
}

/* Reads an index filter and its separately stored operand payloads. */
int _TDbIOReadExprNode(TDbExpr_t *pExpr, TDbIOStream_t *pStream, int release)
{
    int err;

    err = _TDbIOReadBuffer(pStream, pExpr, sizeof(TDbExpr_t));
    if (err == 0) {
        if (pExpr->mLeft.mType <= TDB_TYPE_BINARY) {
            err = TDbExtMemAlloc(_tDbGlobalMemoryHeapID, pExpr->mLeft.mSize, &pExpr->mLeft.mValue.p);
            if (err == 0) {
                err = _TDbIOReadBuffer(pStream, pExpr->mLeft.mValue.p, pExpr->mLeft.mSize);
            }
            if (release) {
                TDbExtMemFree(_tDbGlobalMemoryHeapID, pExpr->mLeft.mValue.p, pExpr->mRight.mSize);
            }
        }
        if (pExpr->mRight.mType <= TDB_TYPE_BINARY && err == 0) {
            err = TDbExtMemAlloc(_tDbGlobalMemoryHeapID, pExpr->mRight.mSize, &pExpr->mRight.mValue.p);
            if (err == 0) {
                err = _TDbIOReadBuffer(pStream, pExpr->mRight.mValue.p, pExpr->mRight.mSize);
            }
            if (release) {
                TDbExtMemFree(_tDbGlobalMemoryHeapID, pExpr->mRight.mValue.p, pExpr->mRight.mSize);
            }
        }
    }
    return err;
}

/* Serializes a filter using database column identities. */
int _TDbIOWriteExprNode(TDbTable_t *pTable, TDbExpr_t *pExpr, TDbIOStream_t *pStream)
{
    TDbExpr_t expr;
    int err;

    expr = *pExpr;
    if (expr.mLeft.mType == TDB_TYPE_COLUMN) {
        expr.mLeft.mValue.l = (unsigned long long)pTable->mId << 32 |
                              pTable->mColumns[(unsigned char)expr.mLeft.mValue.l].mUnknown8;
    }
    if (expr.mRight.mType == TDB_TYPE_COLUMN) {
        expr.mRight.mValue.l = (unsigned long long)pTable->mId << 32 |
                               pTable->mColumns[(unsigned char)expr.mRight.mValue.l].mUnknown8;
    }
    err = _TDbIOWriteBuffer(pStream, &expr, sizeof(expr));
    if (pExpr->mLeft.mType <= TDB_TYPE_BINARY && err == 0) {
        err = _TDbIOWriteBuffer(pStream, pExpr->mLeft.mValue.p, pExpr->mLeft.mSize);
    }
    if (pExpr->mRight.mType <= TDB_TYPE_BINARY && err == 0) {
        err = _TDbIOWriteBuffer(pStream, pExpr->mRight.mValue.p, pExpr->mRight.mSize);
    }
    return err;
}

/* Writes index columns and an optional filter. */
int _TDbIOWriteIndex(TDbIndex_t *pIndex, TDbIOStream_t *pStream)
{
    TDbIOIndexHdr_t hdr;
    TDbIOIndexPart_t part;
    unsigned char count;
    unsigned char i;
    int err;

    memset(&hdr, 0, sizeof(hdr));
    hdr.mId = pIndex->mId;
    count = pIndex->mTree.mPartCount;
    hdr.mAllowDuplicates = pIndex->mTree.mAllowDuplicates;
    hdr.mPartCount = count;
    hdr.mHasFilter = pIndex->mFilter != 0;
    err = _TDbIOWriteBuffer(pStream, &hdr, sizeof(hdr));
    if (err == 0) {
        for (i = 0; i < count; i++) {
            part.mColumn = pIndex->mTree.mParts[i].mColumn;
            part.mAscending = pIndex->mTree.mParts[i].mAscending;
            err = _TDbIOWriteBuffer(pStream, &part, sizeof(part));
            if (err != 0) {
                break;
            }
        }
    }
    if (hdr.mHasFilter && err == 0) {
        err = _TDbIOWriteExprNode(pIndex->mTable, pIndex->mFilter, pStream);
    }
    return err;
}

/* Writes the table header and payload with separate checksums. */
int _TDbIOWriteTable(TDbTable_t *pTable, TDbIOStream_t *pStream)
{
    TDbIOTableHdr_t hdr;
    unsigned int done;
    unsigned char pad[8];
    TDbIndex_t *pIndex;
    int rows;
    int err;

    memset(&hdr, 0, sizeof(hdr));
    hdr.mFlags = pTable->mFlags;
    hdr.mRowSize = pTable->mRowSize;
    hdr.mDeletedBit = pTable->mDeletedBit;
    hdr.mDataSize = pTable->mExtraSize;
    if ((hdr.mFlags & 8) && pTable->mCapacity == 0) {
        hdr.mFlags |= 0x10;
        hdr.mCapacity = pTable->mNominalCapacity;
        rows = 0;
    } else {
        hdr.mFlags &= ~0x10;
        hdr.mCapacity = pTable->mCapacity;
        rows = 1;
    }
    hdr.mRowCount = pTable->mRowCount;
    hdr.mDeletedCount = pTable->mDeletedCount;
    hdr.mFirstDeletedRow = pTable->mFirstDeletedRow;
    hdr.mColumnCount = pTable->mColumnCount;
    hdr.mIndexCount = 0;
    for (pIndex = pTable->mIndexes; pIndex != 0; pIndex = pIndex->mNext) {
        if (pIndex->mDestroyed == 0) {
            hdr.mIndexCount++;
        }
    }
    pStream->mCrcB = -1;
    err = _TDbIOWriteBuffer(pStream, &hdr, sizeof(hdr));
    if (err == 0) {
        err = pStream->mDevice->mWrite(pStream->mHandle, &pStream->mCrcB, 4, &done);
        if (err == 0) {
            if (done != 4) {
                err = 0x24;
            } else {
                pStream->mOffset += 4;
            }
        }
    }
    pStream->mCrcB = -1;
    if (err == 0) {
        err = _TDbIOWriteBuffer(pStream, pTable->mColumns, pTable->mColumnCount * sizeof(TDbColumn_t));
    }
    if (rows == 1 && err == 0 && pTable->mCapacity != 0) {
        err = _TDbIOWriteBuffer(pStream, pTable->mRows, pTable->mRowSize * pTable->mCapacity);
    }
    if (err == 0) {
        if ((pTable->mFlags & 0x60) && pTable->mExtraSize != 0) {
            err = _TDbIOWriteBuffer(pStream, pTable->mExtraData, pTable->mExtraSize);
            if (err == 0 && (pTable->mExtraSize & 7)) {
                memset(pad, 0, sizeof(pad));
                err = _TDbIOWriteBuffer(pStream, pad, 8 - (pTable->mExtraSize & 7));
            }
        }
        if (err == 0) {
            for (pIndex = pTable->mIndexes; pIndex != 0; pIndex = pIndex->mNext) {
                if (pIndex->mDestroyed == 0) {
                    err = _TDbIOWriteIndex(pIndex, pStream);
                    if (err != 0) {
                        break;
                    }
                }
            }
            if (err == 0) {
                err = pStream->mDevice->mWrite(pStream->mHandle, &pStream->mCrcB, 4, &done);
                if (err == 0) {
                    if (done != 4) {
                        err = 0x24;
                    } else {
                        pStream->mOffset += 4;
                    }
                }
            }
        }
    }
    return err;
}

/* Loads selected tables with replace, reject, append or clear-and-append behavior. */
int _TDbIOLoadDatabase(TDbDatabase_t *pDb, int *pTableIds, void *pName,
                unsigned int mode, TDbIODevice_t *pDevice)
{
    TDbIOFileHdr_t hdr;
    TDbIOTableHdr_t tableHdr;
    TDbIOStream_t stream;
    TDbTable_t *pTable;
    int err = 0;
    unsigned int *pOffsets = 0;
    unsigned char *pSelected = 0;
    unsigned int count;
    unsigned int tableCount;
    unsigned int headerCrc;
    unsigned int directoryCrc;
    unsigned int tableCrc;
    unsigned int done;
    unsigned int base;
    unsigned int i;
    int id;

    _TDbMemNotify(1, (int)pDb->mId, -1);
    if (mode == 0 && pTableIds == 0) {
        while (pDb->mTables != 0) {
            fn_8020BD90(pDb->mTables);
        }
    }
    stream.mDevice = pDevice;
    stream.mUnknownC = 1;
    stream.mOffset = 0;
    stream.mCrcA = -1;
    err = pDevice->mOpen(stream.mHandle, 0, pName, 1);
    if (err == 0) {
        err = _TDbIOReadBuffer(&stream, &hdr, sizeof(hdr));
        if (err == 0) {
            if ((hdr.mIdentity.mWord & 0xFFFF0000) != 0x44420000) {
                err = 0x2C;
            } else if ((hdr.mIdentity.mWord & 0xFFFF) != 8 || hdr.mUnknown4 != 1) {
                err = 0x25;
            }
            stream.mEnd = hdr.mEnd;
            stream.mSize = hdr.mEnd - hdr.mBase;
        }
        count = 0;
        if (err == 0) {
            err = _TDbIOReadBuffer(&stream, &tableCount, sizeof(tableCount));
            count = tableCount;
            if (err == 0) {
                err = pDevice->mRead(stream.mHandle, &headerCrc, 4, &done);
                if (done != 4) {
                    err = 0x24;
                } else {
                    stream.mOffset += 4;
                    if (headerCrc != stream.mCrcA) {
                        err = 0x2B;
                    }
                    stream.mCrcA = -1;
                }
                if (err == 0) {
                    err = TDbExtMemAllocTemp(_tDbGlobalMemoryHeapID, count * 8 + ((count + 7) >> 3), &pOffsets);
                    if (err == 0) {
                        err = _TDbIOReadBuffer(&stream, pOffsets, count * 8);
                        if (err == 0) {
                            err = pDevice->mRead(stream.mHandle, &directoryCrc, 4, &done);
                            if (done != 4) {
                                err = 0x24;
                            } else {
                                stream.mOffset += 4;
                                if (directoryCrc != stream.mCrcA) {
                                    err = 0x2B;
                                }
                                stream.mCrcA = -1;
                            }
                            if (err == 0) {
                                pSelected = (unsigned char *)(pOffsets + count * 2);
                                if (pTableIds == 0) {
                                    memset(pSelected, 0xFF, (count + 7) >> 3);
                                } else {
                                    memset(pSelected, 0, (count + 7) >> 3);
                                    while (*pTableIds != -1) {
                                        err = 7;
                                        for (i = 0; i < count; i++) {
                                            if (pOffsets[i * 2] == *pTableIds) {
                                                pSelected[i >> 3] |= 1 << (i & 7);
                                                err = 0;
                                                break;
                                            }
                                        }
                                        if (err != 0) {
                                            break;
                                        }
                                        pTableIds++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        base = stream.mOffset;
        for (i = 0; err == 0 && i < count; i++) {
            if ((pSelected[i >> 3] >> (i & 7)) & 1) {
                if (pOffsets[i * 2 + 1] > stream.mOffset - base) {
                    pDevice->mSeek(stream.mHandle, pOffsets[i * 2 + 1] - (stream.mOffset - base));
                    stream.mOffset = pOffsets[i * 2 + 1] + base;
                }
                id = pOffsets[i * 2];
                stream.mCrcB = -1;
                err = _TDbIOReadBuffer(&stream, &tableHdr, sizeof(tableHdr));
                if (err == 0) {
                    err = pDevice->mRead(stream.mHandle, &tableCrc, 4, &done);
                    if (done != 4) {
                        err = 0x24;
                    } else {
                        stream.mOffset += 4;
                        if (tableCrc != stream.mCrcB) {
                            err = 0x2B;
                        }
                        stream.mCrcB = -1;
                    }
                    if (err == 0) {
                        pTable = fn_8020BA48(pDb, id);
                        switch (mode) {
                        case 0:
                            if (pTable != 0) {
                                fn_8020BD90(pTable);
                                pTable = 0;
                            }
                        case 3:
                            if (pTable != 0) {
                                TDbResult_8020AD1C result;
                                TDbStmt_80205754 stmt;

                                stmt.mTableCount = 1;
                                stmt.mWhere = 0;
                                stmt.mTables[0] = pTable;
                                stmt.mTableExprs[0] = 0;
                                fn_80208204(pTable->mDb->mId, &stmt, &result);
                            }
                            if (pTable != 0) {
                                err = _TDbIOReadTableAppend(pTable, &tableHdr, id, &stream);
                            } else {
                                err = _TDbIOReadTableNew(pDb, &tableHdr, id, &stream);
                            }
                            break;
                        case 1:
                            if (pTable != 0) {
                                err = 6;
                            } else {
                                err = _TDbIOReadTableNew(pDb, &tableHdr, id, &stream);
                            }
                            break;
                        case 2:
                            if (pTable != 0) {
                                err = _TDbIOReadTableAppend(pTable, &tableHdr, id, &stream);
                            } else {
                                err = _TDbIOReadTableNew(pDb, &tableHdr, id, &stream);
                            }
                            break;
                        default:
                            err = 3;
                            break;
                        }
                        if (err == 0) {
                            err = pDevice->mRead(stream.mHandle, &tableCrc, 4, &done);
                            if (done != 4) {
                                err = 0x24;
                            } else {
                                stream.mOffset += 4;
                                if (tableCrc != stream.mCrcB) {
                                    err = 0x2B;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (pOffsets != 0) {
            TDbExtMemFree(_tDbGlobalMemoryHeapID, pOffsets, count * 8 + ((count + 7) >> 3));
        }
        if (err == 0) {
            err = pDevice->mClose(stream.mHandle);
        } else {
            pDevice->mClose(stream.mHandle);
        }
    }
    if (_tDbMemAllocInfoCallback) {
        TDbMemEvent_t event;

        event.mType = 4;
        event.mUnknown8 = -1;
        event.mUnknown4 = -1;
        _tDbMemAllocInfoCallback(&event);
    }
    return err;
}

/* Writes the database directory and all tables marked for saving. */
int _TDbIOSaveDatabase(TDbDatabase_t *pDb, void *pName, TDbIODevice_t *pDevice)
{
    TDbIOFileHdr_t hdr;
    TDbIOStream_t stream;
    TDbTable_t *pTable;
    unsigned int *pOffsets;
    unsigned int count;
    unsigned int n;
    unsigned int done;
    unsigned int base;
    int err;

    _TDbMemNotify(1, (int)pDb->mId, -1);
    memset(&hdr, 0, sizeof(hdr));
    count = 0;
    for (pTable = pDb->mTables; pTable != 0; pTable = pTable->mNext) {
        if (pTable->mFlags & 2) {
            count++;
        }
    }
    pOffsets = 0;
    err = TDbExtMemAlloc(_tDbGlobalMemoryHeapID, count * 8, &pOffsets);
    if (err != 0) {
        pOffsets = 0;
    }
    stream.mSize = _TDbIODatabaseSaveSize(pDb, pOffsets) + (0x1C + count * 8);
    base = pDevice->mReserve(stream.mSize);
    hdr.mBase = base;
    stream.mEnd = hdr.mEnd = stream.mSize + base;
    stream.mUnknownC = 0;
    stream.mCrcB = -1;
    stream.mDevice = pDevice;
    stream.mCrcA = -1;
    stream.mOffset = 0;
    if (err == 0) {
        err = pDevice->mOpen(stream.mHandle, stream.mSize, pName, 0);
    }
    if (err == 0) {
        hdr.mIdentity.mBytes[0] = 'D';
        hdr.mIdentity.mBytes[1] = 'B';
        hdr.mIdentity.mBytes[2] = 0;
        hdr.mIdentity.mBytes[3] = 8;
        hdr.mUnknown4 = 1;
        n = count;
        err = _TDbIOWriteBuffer(&stream, &hdr, sizeof(hdr));
        if (err == 0) {
            err = _TDbIOWriteBuffer(&stream, &n, 4);
            if (err == 0) {
                err = pDevice->mWrite(stream.mHandle, &stream.mCrcA, 4, &done);
                if (err == 0) {
                    if (done == 4) {
                        stream.mOffset += 4;
                    } else {
                        err = 0x24;
                    }
                }
            }
        }
        stream.mCrcA = -1;
        if (err == 0) {
            err = _TDbIOWriteBuffer(&stream, pOffsets, count * 8);
            TDbExtMemFree(_tDbGlobalMemoryHeapID, pOffsets, count * 8);
            pOffsets = 0;
            if (err == 0) {
                err = pDevice->mWrite(stream.mHandle, &stream.mCrcA, 4, &done);
                if (err == 0) {
                    if (done == 4) {
                        stream.mOffset += 4;
                    } else {
                        err = 0x24;
                    }
                }
                if (err == 0) {
                    for (pTable = pDb->mTables; pTable != 0; pTable = pTable->mNext) {
                        if ((pTable->mFlags & 2) && (err = _TDbIOWriteTable(pTable, &stream)) != 0) {
                            break;
                        }
                    }
                }
            }
        }
        if (pOffsets) {
            TDbExtMemFree(_tDbGlobalMemoryHeapID, pOffsets, count * 8);
            pOffsets = 0;
        }
        if (err == 0) {
            err = pDevice->mClose(stream.mHandle);
        } else {
            pDevice->mClose(stream.mHandle);
        }
    } else if (pOffsets) {
        TDbExtMemFree(_tDbGlobalMemoryHeapID, pOffsets, count * 8);
    }
    if (_tDbMemAllocInfoCallback) {
        TDbMemEvent_t event;

        event.mType = 4;
        event.mUnknown8 = -1;
        event.mUnknown4 = -1;
        _tDbMemAllocInfoCallback(&event);
    }
    return err;
}

/* Updates the nonreflected CRC, initializing its table on first use. */
unsigned int _TDbIOCRC32(void *pData, unsigned int size, unsigned int crc)
{
    unsigned char *p;

    if (crc32_table[1] == 0) {
        _TDbIOInitCRCTable();
        crc = -1;
    }
    for (p = pData; size != 0; size--) {
        crc = (crc << 8) ^ crc32_table[(crc >> 24) ^ *p++];
    }
    return crc;
}

#endif
