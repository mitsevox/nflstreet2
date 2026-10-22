#include <string.h>
#include "engine/t3db.h"
#include "engine/t3db_table.h"

int fn_8020C6C8(TDbTable_801FAA00 *pTable);
int fn_8020C5C8(TDbTable_801FAA00 *pTable, int count);

static void fn_8020B564(TDbTable_801FAA00 *pTable, TDbColumn_801FAA00 *pFields)
{
    unsigned int i;
    unsigned int numFields = pTable->mColumnCount;
    int bitOffset = 0;
    int byteOffset = 0;
    int halfOffset = 0;
    int wordOffset = 0;

    for (i = 0; i < numFields; i++) {
        int j;

        j = i - 1;
        if (j >= 0) {
            do {
                if (pFields[i].mUnknown8 >= pTable->mColumns[j].mUnknown8) {
                    break;
                }
                pTable->mColumns[j + 1] = pTable->mColumns[j];
            } while (--j >= 0);
        }
        pTable->mColumns[j + 1] = pFields[i];
        {
            TDbColumn_801FAA00 *pDst = &pTable->mColumns[j + 1];
            TDbColumn_801FAA00 *pSrc = &pFields[i];

            pDst->mUnknown8 = pSrc->mUnknown8;
            pDst->mType = pSrc->mType;
            pDst->mBitCount = pSrc->mBitCount;
            pDst->mBitOffset = -1;
        }
        if (pFields[i].mBitCount == 32) {
            halfOffset += 32;
            byteOffset += 32;
            bitOffset += 32;
        } else if (pFields[i].mBitCount == 16) {
            byteOffset += 16;
            bitOffset += 16;
        } else if ((pFields[i].mBitCount & 7) == 0) {
            bitOffset += pFields[i].mBitCount;
        }
    }
    for (i = 0; i < pTable->mColumnCount; i++) {
        if (pTable->mColumns[i].mBitCount == 32) {
            pTable->mColumns[i].mBitOffset = wordOffset;
            wordOffset += 32;
        } else if (pTable->mColumns[i].mBitCount == 16) {
            pTable->mColumns[i].mBitOffset = halfOffset;
            halfOffset += 16;
        } else if ((pTable->mColumns[i].mBitCount & 7) == 0) {
            pTable->mColumns[i].mBitOffset = byteOffset;
            byteOffset += pTable->mColumns[i].mBitCount;
        } else {
            pTable->mColumns[i].mBitOffset = bitOffset;
            bitOffset += pTable->mColumns[i].mBitCount;
        }
    }
}

void fn_8020B710(TDbTable_801FAA00 *pTable, int record)
{
    int bDecoded = 0;
    unsigned int k;

    for (k = 0; k <= 3; k++) {
        if (pTable->mCallbacks[k] != 0) {
            if (!bDecoded) {
                TDbLitRef_80205754 *pValue = pTable->mUnknown10;
                unsigned char i = 0;

                do {
                    TDbReadColumn_8020A3A0(pTable, &pTable->mColumns[i], pTable->mRows + pTable->mRowSize * record, pValue);
                    if (pTable->mColumns[i].mType == 0) {
                        ((unsigned char *)pValue->mUnknown0)[pTable->mColumns[i].mBitCount >> 3] = 0;
                    }
                    pValue->mId = pTable->mColumns[i].mUnknown8;
                    pValue++;
                    i++;
                } while (i < pTable->mColumnCount);
                pValue->mId = -1;
                bDecoded = 1;
            }
            pTable->mCallbacks[k]((int)pTable->mDb->mUnknown8, pTable->mUnknown1C, 0, 0, pTable->mUnknown10);
        }
    }
}

void fn_8020B878(TDbTable_801FAA00 *pTable, int record, TDbLitRef_80205754 *pValue)
{
    unsigned char *pRecord = pTable->mRows + record * pTable->mRowSize;
    unsigned char i = 0;

    do {
        TDbReadColumn_8020A3A0(pTable, &pTable->mColumns[i], pRecord, pValue);
        if (pTable->mColumns[i].mType == 0) {
            ((unsigned char *)pValue->mUnknown0)[pTable->mColumns[i].mBitCount >> 3] = 0;
        }
        pValue->mId = pTable->mColumns[i].mUnknown8;
        pValue++;
        i++;
    } while (i < pTable->mColumnCount);
    pValue->mId = -1;
}

unsigned char fn_8020B97C(TDbTable_801FAA00 *pTable, int id)
{
    unsigned char result;

    if ((unsigned int)id > 0xFE) {
        int hi = pTable->mColumnCount - 1;
        int lo = pTable->mColumns[0].mUnknown8 == 0xFFFF;

        result = 0xFF;
        while (lo <= hi) {
            int mid = ((hi - lo) >> 1) + lo;
            int diff = id - pTable->mColumns[mid].mUnknown8;

            if (diff == 0) {
                result = mid;
                break;
            }
            if (diff < 0) {
                if (mid == hi) {
                    if (id == pTable->mColumns[lo].mUnknown8) {
                        result = lo;
                    }
                    break;
                }
                hi = mid;
            } else {
                if (mid == lo) {
                    if (id == pTable->mColumns[hi].mUnknown8) {
                        result = hi;
                    }
                    break;
                }
                lo = mid;
            }
        }
    } else {
        result = (unsigned char)id < pTable->mColumnCount ? (unsigned char)id : 0xFF;
    }
    return result;
}

TDbTable_801FAA00 *fn_8020BA48(TDbDatabase_801FAA00 *pDb, int id)
{
    TDbTable_801FAA00 *pTable;

    for (pTable = pDb->mTables; pTable != 0; pTable = pTable->mNext) {
        if (id == pTable->mUnknown1C) {
            break;
        }
    }
    return pTable;
}

int fn_8020BA7C(TDbDatabase_801FAA00 *pOwner, int tableId, TDbColumn_801FAA00 *pDefs, int capacity)
{
    TDbTable_801FAA00 *pTable;
    int err = 0;
    int bHuffman = 0;
    unsigned int recBits = 0;
    unsigned char n;
    int bBlob = 0;
    unsigned int words;

    for (n = 0; pDefs[n].mUnknown8 != -1; n++) {
        recBits += pDefs[n].mBitCount;
        if (n > 0xFD) {
            err = 0x2F;
            break;
        }
        if (pDefs[n].mUnknown8 <= 0xFE) {
            err = 3;
            break;
        }
    }
    if (bBlob && bHuffman) {
        err = 3;
    }
    if (err == 0) {
        if (recBits < 16) {
            recBits = 16;
        }
        words = (recBits + 32) >> 5;
        recBits = words * 4;
        TDbMemNotify_801FC9D4(2, (int)pOwner->mUnknown8, tableId);
        err = fn_8020D1B0(pOwner->mHeap, n * sizeof(TDbColumn_801FAA00) + 0x4C, &pTable);
        if (err == 0) {
            pTable->mRowSize = recBits;
            pTable->mCapacity = capacity;
            pTable->mUnknown40 = capacity;
            pTable->mRowCount = 0;
            pTable->mUnknown46 = 0;
            pTable->mUnknown48 = 0xFFFF;
            pTable->mColumnCount = n;
            pTable->mDeletedBit = words * 32 - 1;
            pTable->mDb = pOwner;
            pTable->mUnknown1C = tableId;
            pTable->mFlags = 2;
            pTable->mIndexes = 0;
            pTable->mUnknown18 = 0;
            pTable->mUnknown2C = 0;
            pTable->mUnknownC = pTable->mUnknown10 = 0;
            if (bBlob) {
                pTable->mFlags |= 0x20;
            } else if (bHuffman) {
                pTable->mFlags |= 0x40;
            }
            if (capacity != 0) {
                err = fn_8020D1B0(pOwner->mHeap, pTable->mRowSize * capacity, &pTable->mRows);
                if (err != 0) {
                    fn_8020D2AC(pOwner->mHeap, pTable, n * sizeof(TDbColumn_801FAA00) + 0x4C);
                } else {
                    memset(pTable->mRows, 0, pTable->mRowSize * capacity);
                }
            }
        }
        if (lbl_803EBE80 != 0) {
            TDbMemEvent_801FC5FC event;

            event.mType = 4;
            event.mUnknown4 = -1;
            event.mUnknown8 = -1;
            lbl_803EBE80(&event);
        }
        if (err == 0) {
            fn_8020B564(pTable, pDefs);
            if (pOwner->mTables == 0) {
                pOwner->mTables = pTable;
            } else {
                pTable->mNext = pOwner->mTables;
                while (pTable->mNext->mNext != 0) {
                    pTable->mNext = pTable->mNext->mNext;
                }
                pTable->mNext->mNext = pTable;
            }
            pTable->mNext = 0;
            for (n = 0; n <= 3; n++) {
                pTable->mCallbacks[n] = 0;
            }
        }
    }
    return err;
}

int fn_8020BD90(TDbTable_801FAA00 *pTable)
{
    TDbQuery_802032D8 *pQuery;

    for (pQuery = lbl_803EBE90; pQuery != 0; pQuery = pQuery->mNext) {
        if (pQuery->mState == 3) {
            unsigned int j;

            for (j = 0; j < pQuery->mSource.mQIdx->mStmt->mTableCount; j++) {
                if (pQuery->mSource.mQIdx->mStmt->mTables[j] == pTable) {
                    break;
                }
            }
            if (j >= pQuery->mSource.mQIdx->mStmt->mTableCount) {
                continue;
            }
        } else {
            if (pQuery->mDb != pTable->mDb) {
                continue;
            }
            if ((pQuery->mState == 0 ? pQuery->mSource.mTable : pQuery->mSource.mIndex->mTable) != pTable) {
                continue;
            }
        }
        return 0x10;
    }
    while (pTable->mIndexes != 0) {
        fn_802032D8(pTable->mIndexes);
    }
    if (pTable->mUnknown10 != 0) {
        unsigned int size = (pTable->mColumnCount + 1) * sizeof(TDbLitRef_80205754);
        unsigned char i = 0;

        do {
            if ((unsigned int)pTable->mColumns[i].mType <= 1) {
                size += 1 + (pTable->mColumns[i].mBitCount >> 3);
            }
            i++;
        } while (i < pTable->mColumnCount);
        fn_8020D2AC(pTable->mDb->mHeap, pTable->mUnknown10, ((size + 3) & ~3) * 2);
    }
    if (pTable == pTable->mDb->mTables) {
        pTable->mDb->mTables = pTable->mNext;
    } else {
        TDbTable_801FAA00 *pPrev = pTable->mDb->mTables;

        while (pPrev->mNext != pTable) {
            pPrev = pPrev->mNext;
        }
        pPrev->mNext = pTable->mNext;
    }
    if (pTable->mCapacity != 0) {
        fn_8020D2AC(pTable->mDb->mHeap, pTable->mRows, pTable->mRowSize * pTable->mCapacity);
    }
    if ((pTable->mFlags & 0x60) && pTable->mUnknown2C != 0 && pTable->mUnknown18 != 0) {
        fn_8020D2AC(pTable->mDb->mHeap, pTable->mUnknown18, pTable->mUnknown2C);
    }
    fn_8020D2AC(pTable->mDb->mHeap, pTable, pTable->mColumnCount * sizeof(TDbColumn_801FAA00) + 0x4C);
    return 0;
}

int fn_8020BFA4(TDbTable_801FAA00 *pTable, TDbLitRef_80205754 *pValues, TDbResult_8020AD1C *pResult)
{
    int err = 0;
    unsigned int record = 0;
    int bReused = 0;
    unsigned char *pRecord;
    TDbLitRef_80205754 *pValue;
    TDbIndex_801FAA00 *pIndex;

    if (pTable->mFlags & 0x60) {
        return 0x31;
    }
    pResult->mCount = err;
    fn_8020A540();
    if (pTable->mFlags & 1) {
        pResult->mErr = 0x1E;
        return 0x1E;
    }
    pTable->mFlags |= 1;
    if ((pTable->mFlags & 8) && pTable->mCapacity == 0) {
        fn_8020C5C8(pTable, pTable->mUnknown40);
    }
    if (pTable->mUnknown46 != 0) {
        record = pTable->mUnknown48;
        bReused = 1;
        pTable->mUnknown46--;
        pTable->mUnknown48 = *(unsigned short *)(pTable->mRows + pTable->mRowSize * record);
    } else if (pTable->mRowCount < pTable->mCapacity) {
        record = pTable->mRowCount++;
    } else {
        err = 0x13;
    }
    if (err == 0) {
        pRecord = pTable->mRows + pTable->mRowSize * record;
        memset(pRecord, 0, pTable->mRowSize);
        for (pValue = pValues; pValue->mId != -1; pValue++) {
            TDbWriteColumn_8020BFA4(&pTable->mColumns[pValue->mColumn], pRecord, pValue);
        }
        for (pIndex = pTable->mIndexes; pIndex != 0; pIndex = pIndex->mNext) {
            err = fn_8020299C(pIndex, record);
            if (err != 0) {
                for (pIndex = pTable->mIndexes; pIndex != 0; pIndex = pIndex->mNext) {
                    fn_80202D34(pIndex, record);
                }
                break;
            }
        }
        if (err == 0) {
            TDbQuery_802032D8 *pQuery;

            for (pQuery = lbl_803EBE90; pQuery != 0; pQuery = pQuery->mNext) {
                if (pQuery->mState == 3 && fn_80205880(pTable, 0xFF, pQuery->mSource.mQIdx) != 0) {
                    fn_80205A10(pQuery->mSource.mQIdx, &pQuery->mCur);
                }
            }
            pTable->mFlags |= 4;
        } else if (bReused) {
            unsigned char *pFlags;

            memset(pRecord, 0, pTable->mRowSize);
            pFlags = pTable->mRows + pTable->mRowSize * record;
            pFlags += pTable->mDeletedBit >> 3;
            *pFlags |= 1 << (7 - (pTable->mDeletedBit & 7));
            *(unsigned short *)(pTable->mRows + pTable->mRowSize * record) = pTable->mUnknown48;
            pTable->mUnknown48 = record;
            pTable->mUnknown46++;
        } else {
            pTable->mRowCount--;
        }
        if (err == 0) {
            int bDecoded = 0;
            int k;

            for (k = 0; k <= 3; k++) {
                if (pTable->mCallbacks[k] != 0) {
                    if (!bDecoded) {
                        unsigned char i = 0;

                        pValue = pTable->mUnknown10;
                        do {
                            TDbReadColumn_8020A3A0(pTable, &pTable->mColumns[i], pRecord, pValue);
                            pValue->mId = pTable->mColumns[i].mUnknown8;
                            pValue++;
                            i++;
                        } while (i < pTable->mColumnCount);
                        pValue->mId = -1;
                        bDecoded = 1;
                    }
                    pTable->mCallbacks[k]((int)pTable->mDb->mUnknown8, pTable->mUnknown1C, 0, 0, pTable->mUnknown10);
                }
            }
        }
    }
    pTable->mFlags &= ~1;
    if (err == 0) {
        fn_8020A5A8();
    }
    pResult->mCount = err == 0;
    pResult->mUnknown08 = 0;
    pResult->mErr = err;
    return err;
}

void fn_8020C3E4(TDbTable_801FAA00 *pTable, int record)
{
    int k;
    unsigned char *pRecord;
    unsigned char i;

    for (k = 0; k <= 3; k++) {
        if (pTable->mCallbacks[k] != 0) {
            break;
        }
    }
    pRecord = pTable->mRows + pTable->mRowSize * record;
    i = 0;
    if (k <= 3) {
        TDbLitRef_80205754 *pValue = pTable->mUnknownC;

        do {
            TDbReadColumn_8020A3A0(pTable, &pTable->mColumns[i], pRecord, pValue);
            pValue->mId = pTable->mColumns[i].mUnknown8;
            pValue++;
            i++;
        } while (i < pTable->mColumnCount);
        pValue->mId = -1;
    }
    {
        unsigned char *pFlags = pTable->mRows + pTable->mRowSize * record;

        pFlags += pTable->mDeletedBit >> 3;
        *pFlags |= 1 << (7 - (pTable->mDeletedBit & 7));
    }
    *(unsigned short *)(pTable->mRows + pTable->mRowSize * record) = pTable->mUnknown48;
    pTable->mUnknown48 = record;
    pTable->mFlags |= 4;
    pTable->mUnknown46++;
    for (k = 0; k <= 3; k++) {
        if (pTable->mCallbacks[k] != 0) {
            pTable->mCallbacks[k]((int)pTable->mDb->mUnknown8, pTable->mUnknown1C, 1, pTable->mUnknownC, 0);
        }
    }
    if ((pTable->mFlags & 8) && pTable->mRowCount == pTable->mUnknown46) {
        fn_8020C6C8(pTable);
    }
}

int fn_8020C5C8(TDbTable_801FAA00 *pTable, int count)
{
    int err;

    if (pTable->mFlags & 0x60) {
        return 0x31;
    }
    TDbMemNotify_801FC9D4(2, (int)pTable->mDb->mUnknown8, pTable->mUnknown1C);
    if (pTable->mCapacity == 0) {
        err = fn_8020D1B0(pTable->mDb->mHeap, pTable->mRowSize * count, &pTable->mRows);
    } else {
        err = fn_8020D260(pTable->mDb->mHeap, pTable->mRows, pTable->mRowSize * pTable->mCapacity,
                          pTable->mRowSize * count, &pTable->mRows);
    }
    if (err == 0) {
        pTable->mCapacity = count;
        pTable->mUnknown40 = count;
    }
    if (lbl_803EBE80 != 0) {
        TDbMemEvent_801FC5FC event;

        event.mType = 4;
        event.mUnknown4 = -1;
        event.mUnknown8 = -1;
        lbl_803EBE80(&event);
    }
    return err;
}

int fn_8020C6C8(TDbTable_801FAA00 *pTable)
{
    TDbIndex_801FAA00 *pIndex;

    if (pTable->mFlags & 0x60) {
        return 0x31;
    }
    for (pIndex = pTable->mIndexes; pIndex != 0; pIndex = pIndex->mNext) {
        fn_8020325C(pIndex);
    }
    if (pTable->mCapacity != 0) {
        fn_8020D2AC(pTable->mDb->mHeap, pTable->mRows, pTable->mRowSize * pTable->mCapacity);
    }
    pTable->mCapacity = 0;
    pTable->mUnknown46 = 0;
    pTable->mRowCount = 0;
    pTable->mUnknown48 = 0xFFFF;
    return 0;
}

int fn_8020C764(TDbTable_801FAA00 *pSrc, TDbTable_801FAA00 *pDst, TDbResult_8020AD1C *pResult)
{
    int err = 0;
    unsigned int record = 0;
    unsigned int maxBits = 0;
    unsigned char map[256];
    unsigned char *pBuf;
    TDbMemEvent_801FC5FC event;
    TDbMemEvent_801FC5FC *pEvent;
    void *pData;
    unsigned char i;
    unsigned short rec;

    pResult->mCount = err;
    pBuf = 0;
    if (pDst->mFlags & 1) {
        pResult->mErr = 0x1E;
        return 0x1E;
    }
    if (pDst->mFlags & 0x60) {
        pResult->mErr = 0x31;
        return 0x31;
    }
    pDst->mFlags |= 1;
    for (i = 0; i < pDst->mColumnCount; i++) {
        map[i] = fn_8020B97C(pSrc, pDst->mColumns[i].mUnknown8);
        if (map[i] != 0xFF) {
            unsigned int type = pSrc->mColumns[map[i]].mType;

            if (type - 13 <= 2 || type <= 1) {
                if (pSrc->mColumns[map[i]].mBitCount > maxBits) {
                    maxBits = pSrc->mColumns[map[i]].mBitCount;
                }
            }
        }
    }
    if (maxBits != 0) {
        int dbId = (int)pSrc->mDb->mUnknown8;
        int tableId = pSrc->mUnknown1C;

        pEvent = &event;
        if (lbl_803EBE80 != 0) {
            event.mUnknown4 = dbId;
            event.mType = 2;
            event.mUnknown8 = tableId;
            lbl_803EBE80(pEvent);
        }
        pResult->mErr = fn_8020D1B0(pSrc->mDb->mHeap, maxBits + 1, &pBuf);
        if (pResult->mErr != 0) {
            return pResult->mErr;
        }
        if (lbl_803EBE80 != 0) {
            pEvent->mType = 4;
            pEvent->mUnknown4 = -1;
            pEvent->mUnknown8 = -1;
            lbl_803EBE80(pEvent);
        }
    }
    fn_8020A540();
    for (rec = 0; rec < pSrc->mRowCount; rec++) {
        int bReused;

        if (TDbRowBit_801FAAF8(pSrc, rec)) {
            continue;
        }
        if (pDst->mCapacity == 0 && (pDst->mFlags & 8)) {
            fn_8020C5C8(pDst, pDst->mUnknown40);
        }
        bReused = 0;
        if (pDst->mUnknown46 != 0) {
            record = pDst->mUnknown48;
            bReused = 1;
            pDst->mUnknown46--;
            pDst->mUnknown48 = *(unsigned short *)(pDst->mRows + pDst->mRowSize * record);
        } else if (pDst->mRowCount < pDst->mCapacity) {
            record = pDst->mRowCount++;
        } else {
            err = 0x13;
        }
        if (err != 0) {
            continue;
        }
        memset(pDst->mRows + pDst->mRowSize * record, 0, pDst->mRowSize);
        for (i = 0; i < pDst->mColumnCount; i++) {
            if (map[i] == 0xFF) {
                continue;
            }
            pData = pBuf;
            TDbReadColumn_8020A3A0(pSrc, &pSrc->mColumns[map[i]], pSrc->mRows + pSrc->mRowSize * rec, (TDbLitRef_80205754 *)&pData);
            TDbWriteColumn_8020BFA4(&pDst->mColumns[i], pDst->mRows + pDst->mRowSize * record, (TDbLitRef_80205754 *)&pData);
        }
        {
            TDbIndex_801FAA00 *pIndex;

            for (pIndex = pDst->mIndexes; pIndex != 0; pIndex = pIndex->mNext) {
                err = fn_8020299C(pIndex, record);
                if (err != 0) {
                    for (pIndex = pDst->mIndexes; pIndex != 0; pIndex = pIndex->mNext) {
                        fn_80202D34(pIndex, record);
                    }
                    break;
                }
            }
        }
        if (err == 0) {
            unsigned char *pFlags = pDst->mRows + pDst->mRowSize * record;

            pFlags += pDst->mDeletedBit >> 3;
            *pFlags &= ~(1 << (7 - (pDst->mDeletedBit & 7)));
            pDst->mFlags |= 4;
            pResult->mCount++;
            fn_8020B710(pDst, record);
        } else if (bReused) {
            unsigned char *pFlags = pDst->mRows + pDst->mRowSize * record;

            pFlags += pDst->mDeletedBit >> 3;
            *pFlags |= 1 << (7 - (pDst->mDeletedBit & 7));
            *(unsigned short *)(pDst->mRows + pDst->mRowSize * record) = pDst->mUnknown48;
            pDst->mUnknown48 = record;
            pDst->mUnknown46++;
        } else {
            pDst->mRowCount--;
        }
    }
    if (maxBits != 0) {
        fn_8020D2AC(pSrc->mDb->mHeap, pBuf, maxBits + 1);
    }
    pDst->mFlags &= ~1;
    if (pResult->mCount != 0) {
        fn_8020A5A8();
    }
    pResult->mErr = err;
    return err;
}
