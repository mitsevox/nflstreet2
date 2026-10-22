#include <string.h>
#include "engine/tmlib.h"

extern void fn_8020325C(TDbQuery_8020C6C8 *pQuery);
extern void fn_802032D8(TDbQuery_8020C6C8 *pQuery);
extern TDbLock_8020BD90 *lbl_803EBE90;
int fn_8020C6C8(TDbTable_8020B564 *pTable);
int fn_8020C5C8(TDbTable_8020B564 *pTable, int count);
extern void (*lbl_803EBE80)(TDbEvent_8020C5C8 *pEvent);
extern void fn_80201E10(void *pRecord, int bitOffset, int bitSize, void *pValue);
extern int fn_8020299C(TDbQuery_8020C6C8 *pQuery, unsigned int record);
extern void fn_80202D34(TDbQuery_8020C6C8 *pQuery, unsigned int record);
extern int fn_80205880(TDbTable_8020B564 *pTable, int field, void *pList);
extern void fn_80205A10(void *pList, int *pState);
extern void fn_80201D94(void *pRecord, int bitOffset, int bitSize, void *pValue, int bSigned);

static inline void fn_8020B878_ReadField(TDbTable_8020B564 *pTable, TDbField_8020B564 *pField, unsigned char *pRecord, TDbValue_8020B710 *pValue)
{
    int type = pField->mType;

    if ((unsigned int)(type - 13) <= 2) {
        fn_8020CD9C(pTable, pField, pRecord, pValue->mpData);
    } else if ((unsigned int)type <= 1) {
        fn_8020CF34(pRecord, pField->mOffset, pField->mBits, pValue->mpData, (unsigned int)pField->mBits >> 3);
    } else {
        fn_80201D94(pRecord, pField->mOffset, pField->mBits, pValue, type == 2);
    }
}

static inline void fn_8020B564_InitField(TDbField_8020B564 *pDst, TDbField_8020B564 *pSrc)
{
    unsigned int id = pSrc->mId;
    unsigned int type = pSrc->mType;
    int bits = pSrc->mBits;

    pDst->mId = id;
    pDst->mType = type;
    pDst->mBits = bits;
    pDst->mOffset = -1;
}

void fn_8020B564(TDbTable_8020B564 *pTable, TDbField_8020B564 *pFields)
{
    unsigned int i;
    unsigned int numFields = pTable->mNumFields;
    int bitOffset = 0;
    int byteOffset = 0;
    int halfOffset = 0;
    int wordOffset = 0;

    for (i = 0; i < numFields; i++) {
        int j;

        j = i - 1;
        if (j >= 0) {
            do {
                if (pFields[i].mId >= pTable->mFields[j].mId) {
                    break;
                }
                pTable->mFields[j + 1] = pTable->mFields[j];
            } while (--j >= 0);
        }
        pTable->mFields[j + 1] = pFields[i];
        fn_8020B564_InitField(&pTable->mFields[j + 1], &pFields[i]);
        if (pFields[i].mBits == 32) {
            halfOffset += 32;
            byteOffset += 32;
            bitOffset += 32;
        } else if (pFields[i].mBits == 16) {
            byteOffset += 16;
            bitOffset += 16;
        } else if ((pFields[i].mBits & 7) == 0) {
            bitOffset += pFields[i].mBits;
        }
    }
    for (i = 0; i < pTable->mNumFields; i++) {
        if (pTable->mFields[i].mBits == 32) {
            pTable->mFields[i].mOffset = wordOffset;
            wordOffset += 32;
        } else if (pTable->mFields[i].mBits == 16) {
            pTable->mFields[i].mOffset = halfOffset;
            halfOffset += 16;
        } else if ((pTable->mFields[i].mBits & 7) == 0) {
            pTable->mFields[i].mOffset = byteOffset;
            byteOffset += pTable->mFields[i].mBits;
        } else {
            pTable->mFields[i].mOffset = bitOffset;
            bitOffset += pTable->mFields[i].mBits;
        }
    }
}


void fn_8020B710(TDbTable_8020B564 *pTable, int record)
{
    int bDecoded = 0;
    unsigned int k;

    for (k = 0; k <= 3; k++) {
        if (pTable->mCallbacks[k] != 0) {
            if (!bDecoded) {
                TDbValue_8020B710 *pValue = pTable->mpValues;
                unsigned char i = 0;

                do {
                    fn_8020B878_ReadField(pTable, &pTable->mFields[i], pTable->mpRecords + pTable->mRecordSize * record, pValue);
                    if (pTable->mFields[i].mType == 0) {
                        ((unsigned char *)pValue->mpData)[(unsigned int)pTable->mFields[i].mBits >> 3] = 0;
                    }
                    pValue->mId = pTable->mFields[i].mId;
                    pValue++;
                    i++;
                } while (i < pTable->mNumFields);
                pValue->mId = -1;
                bDecoded = 1;
            }
            pTable->mCallbacks[k](pTable->mpOwner->mId, pTable->mId, 0, 0, pTable->mpValues);
        }
    }
}

void fn_8020B878(TDbTable_8020B564 *pTable, int record, TDbValue_8020B710 *pValue)
{
    unsigned char *pRecord = pTable->mpRecords + record * pTable->mRecordSize;
    unsigned char i = 0;

    do {
        fn_8020B878_ReadField(pTable, &pTable->mFields[i], pRecord, pValue);
        if (pTable->mFields[i].mType == 0) {
            ((unsigned char *)pValue->mpData)[(unsigned int)pTable->mFields[i].mBits >> 3] = 0;
        }
        pValue->mId = pTable->mFields[i].mId;
        pValue++;
        i++;
    } while (i < pTable->mNumFields);
    pValue->mId = -1;
}

unsigned char fn_8020B97C(TDbTable_8020B564 *pTable, unsigned int id)
{
    unsigned char result;

    if (id > 0xFE) {
        int hi = pTable->mNumFields - 1;
        int lo = pTable->mFields[0].mId == 0xFFFF;

        result = 0xFF;
        while (lo <= hi) {
            int mid = ((hi - lo) >> 1) + lo;
            int diff = id - pTable->mFields[mid].mId;

            if (diff == 0) {
                result = mid;
                break;
            }
            if (diff < 0) {
                if (mid == hi) {
                    if (id == pTable->mFields[lo].mId) {
                        result = lo;
                    }
                    break;
                }
                hi = mid;
            } else {
                if (mid == lo) {
                    if (id == pTable->mFields[hi].mId) {
                        result = hi;
                    }
                    break;
                }
                lo = mid;
            }
        }
    } else {
        result = (unsigned char)id < pTable->mNumFields ? (unsigned char)id : 0xFF;
    }
    return result;
}

TDbTable_8020B564 *fn_8020BA48(TDbTable_8020B564 *pTable, int id)
{
    TDbTable_8020B564 *pNext;

    for (pNext = pTable->mpNext; pNext != 0; pNext = pNext->mpNext) {
        if (id == pNext->mId) {
            break;
        }
    }
    return pNext;
}

static inline void fn_8020C5C8_Notify(int type, int dbId, int tableId)
{
    TDbEvent_8020C5C8 event;

    if (lbl_803EBE80 != 0) {
        event.mType = type;
        event.mDbId = dbId;
        event.mTableId = tableId;
        lbl_803EBE80(&event);
    }
}

int fn_8020BA7C(TDbOwner_8020B710 *pOwner, int tableId, TDbField_8020B564 *pDefs, int capacity)
{
    TDbTable_8020B564 *pTable;
    int err = 0;
    int bHuffman = 0;
    unsigned int recBits = 0;
    unsigned char n;
    int bBlob = 0;
    unsigned int words;

    for (n = 0; pDefs[n].mId != -1; n++) {
        recBits += pDefs[n].mBits;
        if (n > 0xFD) {
            err = 0x2F;
            break;
        }
        if (pDefs[n].mId <= 0xFE) {
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
        fn_8020C5C8_Notify(2, pOwner->mId, tableId);
        err = fn_8020D1B0(pOwner->mHeap, n * sizeof(TDbField_8020B564) + 0x4C, (unsigned char **)&pTable);
        if (err == 0) {
            pTable->mRecordSize = recBits;
            pTable->mNumRecords = capacity;
            pTable->mCapacity = capacity;
            pTable->mUnknown44 = 0;
            pTable->mNumDeleted = 0;
            pTable->mFreeHead = 0xFFFF;
            pTable->mNumFields = n;
            pTable->mDeletedBit = words * 32 - 1;
            pTable->mpOwner = pOwner;
            pTable->mId = tableId;
            pTable->mFlags = 2;
            pTable->mpQueries = 0;
            pTable->mpBlob = 0;
            pTable->mBlobSize = 0;
            pTable->mpOldValues = pTable->mpValues = 0;
            if (bBlob) {
                pTable->mFlags |= 0x20;
            } else if (bHuffman) {
                pTable->mFlags |= 0x40;
            }
            if (capacity != 0) {
                err = fn_8020D1B0(pOwner->mHeap, pTable->mRecordSize * capacity, &pTable->mpRecords);
                if (err != 0) {
                    fn_8020D2AC(pOwner->mHeap, pTable, n * sizeof(TDbField_8020B564) + 0x4C);
                } else {
                    memset(pTable->mpRecords, 0, pTable->mRecordSize * capacity);
                }
            }
        }
        if (lbl_803EBE80 != 0) {
            TDbEvent_8020C5C8 event;

            event.mType = 4;
            event.mDbId = -1;
            event.mTableId = -1;
            lbl_803EBE80(&event);
        }
        if (err == 0) {
            fn_8020B564(pTable, pDefs);
            if (pOwner->mpTables == 0) {
                pOwner->mpTables = pTable;
            } else {
                pTable->mpNext = pOwner->mpTables;
                while (pTable->mpNext->mpNext != 0) {
                    pTable->mpNext = pTable->mpNext->mpNext;
                }
                pTable->mpNext->mpNext = pTable;
            }
            pTable->mpNext = 0;
            for (n = 0; n <= 3; n++) {
                pTable->mCallbacks[n] = 0;
            }
        }
    }
    return err;
}

int fn_8020BD90(TDbTable_8020B564 *pTable)
{
    TDbLock_8020BD90 *pLock;

    for (pLock = lbl_803EBE90; pLock != 0; pLock = pLock->mpNext) {
        if (pLock->mType == 3) {
            unsigned int j;

            for (j = 0; j < (*(TDbTableList_8020BD90 **)pLock->mpTarget)->mCount; j++) {
                if ((*(TDbTableList_8020BD90 **)pLock->mpTarget)->mpTables[j] == pTable) {
                    break;
                }
            }
            if (j >= (*(TDbTableList_8020BD90 **)pLock->mpTarget)->mCount) {
                continue;
            }
        } else {
            if (pLock->mpOwner != pTable->mpOwner) {
                continue;
            }
            if ((pLock->mType == 0 ? (TDbTable_8020B564 *)pLock->mpTarget : *(TDbTable_8020B564 **)pLock->mpTarget) != pTable) {
                continue;
            }
        }
        return 0x10;
    }
    while (pTable->mpQueries != 0) {
        fn_802032D8(pTable->mpQueries);
    }
    if (pTable->mpValues != 0) {
        unsigned int size = (pTable->mNumFields + 1) * sizeof(TDbValue_8020B710);
        unsigned char i = 0;

        do {
            if ((unsigned int)pTable->mFields[i].mType <= 1) {
                size += 1 + ((unsigned int)pTable->mFields[i].mBits >> 3);
            }
            i++;
        } while (i < pTable->mNumFields);
        fn_8020D2AC(pTable->mpOwner->mHeap, pTable->mpValues, ((size + 3) & ~3) * 2);
    }
    if (pTable == pTable->mpOwner->mpTables) {
        pTable->mpOwner->mpTables = pTable->mpNext;
    } else {
        TDbTable_8020B564 *pPrev = pTable->mpOwner->mpTables;

        while (pPrev->mpNext != pTable) {
            pPrev = pPrev->mpNext;
        }
        pPrev->mpNext = pTable->mpNext;
    }
    if (pTable->mNumRecords != 0) {
        fn_8020D2AC(pTable->mpOwner->mHeap, pTable->mpRecords, pTable->mRecordSize * pTable->mNumRecords);
    }
    if ((pTable->mFlags & 0x60) && pTable->mBlobSize != 0 && pTable->mpBlob != 0) {
        fn_8020D2AC(pTable->mpOwner->mHeap, pTable->mpBlob, pTable->mBlobSize);
    }
    fn_8020D2AC(pTable->mpOwner->mHeap, pTable, pTable->mNumFields * sizeof(TDbField_8020B564) + 0x4C);
    return 0;
}

static inline void fn_8020BFA4_WriteField(TDbField_8020B564 *pField, unsigned char *pRecord, TDbValue_8020B710 *pValue)
{
    int type = pField->mType;

    if ((unsigned int)(type - 13) <= 2) {
        return;
    }
    if (type == 0) {
        fn_8020CEC4(pRecord, pField->mOffset, pField->mBits, pValue->mpData, strlen(pValue->mpData));
    } else if (type == 1) {
        fn_8020CEC4(pRecord, pField->mOffset, pField->mBits, pValue->mpData, (unsigned int)pField->mBits >> 3);
    } else {
        fn_80201E10(pRecord, pField->mOffset, pField->mBits, pValue);
    }
}

int fn_8020BFA4(TDbTable_8020B564 *pTable, TDbValue_8020B710 *pValues, TDbResult_8020AD1C *pResult)
{
    int err = 0;
    unsigned int record = 0;
    int bReused = 0;
    unsigned char *pRecord;
    TDbValue_8020B710 *pValue;
    TDbQuery_8020C6C8 *pQuery;

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
    if ((pTable->mFlags & 8) && pTable->mNumRecords == 0) {
        fn_8020C5C8(pTable, pTable->mCapacity);
    }
    if (pTable->mNumDeleted != 0) {
        record = pTable->mFreeHead;
        bReused = 1;
        pTable->mNumDeleted--;
        pTable->mFreeHead = *(unsigned short *)(pTable->mpRecords + pTable->mRecordSize * record);
    } else if (pTable->mUnknown44 < pTable->mNumRecords) {
        record = pTable->mUnknown44++;
    } else {
        err = 0x13;
    }
    if (err == 0) {
        pRecord = pTable->mpRecords + pTable->mRecordSize * record;
        memset(pRecord, 0, pTable->mRecordSize);
        for (pValue = pValues; pValue->mId != -1; pValue++) {
            fn_8020BFA4_WriteField(&pTable->mFields[pValue->mUnknown0C], pRecord, pValue);
        }
        for (pQuery = pTable->mpQueries; pQuery != 0; pQuery = pQuery->mpNext) {
            err = fn_8020299C(pQuery, record);
            if (err != 0) {
                for (pQuery = pTable->mpQueries; pQuery != 0; pQuery = pQuery->mpNext) {
                    fn_80202D34(pQuery, record);
                }
                break;
            }
        }
        if (err == 0) {
            TDbLock_8020BD90 *pLock;

            for (pLock = lbl_803EBE90; pLock != 0; pLock = pLock->mpNext) {
                if (pLock->mType == 3 && fn_80205880(pTable, 0xFF, pLock->mpTarget) != 0) {
                    fn_80205A10(pLock->mpTarget, &pLock->mUnknown14);
                }
            }
            pTable->mFlags |= 4;
        } else if (bReused) {
            unsigned char *pFlags;

            memset(pRecord, 0, pTable->mRecordSize);
            pFlags = pTable->mpRecords + pTable->mRecordSize * record;
            pFlags += pTable->mDeletedBit >> 3;
            *pFlags |= 1 << (7 - (pTable->mDeletedBit & 7));
            *(unsigned short *)(pTable->mpRecords + pTable->mRecordSize * record) = pTable->mFreeHead;
            pTable->mFreeHead = record;
            pTable->mNumDeleted++;
        } else {
            pTable->mUnknown44--;
        }
        if (err == 0) {
            int bDecoded = 0;
            int k;

            for (k = 0; k <= 3; k++) {
                if (pTable->mCallbacks[k] != 0) {
                    if (!bDecoded) {
                        unsigned char i = 0;

                        pValue = pTable->mpValues;
                        do {
                            fn_8020B878_ReadField(pTable, &pTable->mFields[i], pRecord, pValue);
                            pValue->mId = pTable->mFields[i].mId;
                            pValue++;
                            i++;
                        } while (i < pTable->mNumFields);
                        pValue->mId = -1;
                        bDecoded = 1;
                    }
                    pTable->mCallbacks[k](pTable->mpOwner->mId, pTable->mId, 0, 0, pTable->mpValues);
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

void fn_8020C3E4(TDbTable_8020B564 *pTable, int record)
{
    int k;
    unsigned char *pRecord;
    unsigned char i;

    for (k = 0; k <= 3; k++) {
        if (pTable->mCallbacks[k] != 0) {
            break;
        }
    }
    pRecord = pTable->mpRecords + pTable->mRecordSize * record;
    i = 0;
    if (k <= 3) {
        TDbValue_8020B710 *pValue = pTable->mpOldValues;

        do {
            fn_8020B878_ReadField(pTable, &pTable->mFields[i], pRecord, pValue);
            pValue->mId = pTable->mFields[i].mId;
            pValue++;
            i++;
        } while (i < pTable->mNumFields);
        pValue->mId = -1;
    }
    {
        unsigned char *pFlags = pTable->mpRecords + pTable->mRecordSize * record;

        pFlags += pTable->mDeletedBit >> 3;
        *pFlags |= 1 << (7 - (pTable->mDeletedBit & 7));
    }
    *(unsigned short *)(pTable->mpRecords + pTable->mRecordSize * record) = pTable->mFreeHead;
    pTable->mFreeHead = record;
    pTable->mFlags |= 4;
    pTable->mNumDeleted++;
    for (k = 0; k <= 3; k++) {
        if (pTable->mCallbacks[k] != 0) {
            pTable->mCallbacks[k](pTable->mpOwner->mId, pTable->mId, 1, pTable->mpOldValues, 0);
        }
    }
    if ((pTable->mFlags & 8) && pTable->mUnknown44 == pTable->mNumDeleted) {
        fn_8020C6C8(pTable);
    }
}

int fn_8020C5C8(TDbTable_8020B564 *pTable, int count)
{
    int err;

    if (pTable->mFlags & 0x60) {
        return 0x31;
    }
    fn_8020C5C8_Notify(2, pTable->mpOwner->mId, pTable->mId);
    if (pTable->mNumRecords == 0) {
        err = fn_8020D1B0(pTable->mpOwner->mHeap, pTable->mRecordSize * count, &pTable->mpRecords);
    } else {
        err = fn_8020D260(pTable->mpOwner->mHeap, pTable->mpRecords, pTable->mRecordSize * pTable->mNumRecords,
                          pTable->mRecordSize * count, &pTable->mpRecords);
    }
    if (err == 0) {
        pTable->mNumRecords = count;
        pTable->mCapacity = count;
    }
    if (lbl_803EBE80 != 0) {
        TDbEvent_8020C5C8 event;

        event.mType = 4;
        event.mDbId = -1;
        event.mTableId = -1;
        lbl_803EBE80(&event);
    }
    return err;
}

int fn_8020C6C8(TDbTable_8020B564 *pTable)
{
    TDbQuery_8020C6C8 *pQuery;

    if (pTable->mFlags & 0x60) {
        return 0x31;
    }
    for (pQuery = pTable->mpQueries; pQuery != 0; pQuery = pQuery->mpNext) {
        fn_8020325C(pQuery);
    }
    if (pTable->mNumRecords != 0) {
        fn_8020D2AC(pTable->mpOwner->mHeap, pTable->mpRecords, pTable->mRecordSize * pTable->mNumRecords);
    }
    pTable->mNumRecords = 0;
    pTable->mNumDeleted = 0;
    pTable->mUnknown44 = 0;
    pTable->mFreeHead = 0xFFFF;
    return 0;
}

static inline void fn_8020C764_ReadField(TDbTable_8020B564 *pTable, TDbField_8020B564 *pField, unsigned char *pRecord, void **ppData)
{
    int type = pField->mType;

    if ((unsigned int)(type - 13) <= 2) {
        fn_8020CD9C(pTable, pField, pRecord, *ppData);
    } else if ((unsigned int)type <= 1) {
        fn_8020CF34(pRecord, pField->mOffset, pField->mBits, *ppData, (unsigned int)pField->mBits >> 3);
    } else {
        fn_80201D94(pRecord, pField->mOffset, pField->mBits, ppData, type == 2);
    }
}

static inline void fn_8020C764_WriteField(TDbField_8020B564 *pField, unsigned char *pRecord, void **ppData)
{
    int type = pField->mType;

    if ((unsigned int)(type - 13) <= 2) {
        return;
    }
    if (type == 0) {
        fn_8020CEC4(pRecord, pField->mOffset, pField->mBits, *ppData, strlen(*ppData));
    } else if (type == 1) {
        fn_8020CEC4(pRecord, pField->mOffset, pField->mBits, *ppData, (unsigned int)pField->mBits >> 3);
    } else {
        fn_80201E10(pRecord, pField->mOffset, pField->mBits, ppData);
    }
}

static inline int fn_8020C764_IsDeleted(TDbTable_8020B564 *pTable, unsigned int record)
{
    unsigned char *pRecord = pTable->mpRecords + pTable->mRecordSize * record;

    if (!((pRecord[pTable->mDeletedBit >> 3] >> (7 - (pTable->mDeletedBit & 7))) & 1)) {
        return 0;
    }
    return 1;
}

int fn_8020C764(TDbTable_8020B564 *pSrc, TDbTable_8020B564 *pDst, TDbResult_8020AD1C *pResult)
{
    int err = 0;
    unsigned int record = 0;
    unsigned int maxBits = 0;
    unsigned char map[256];
    unsigned char *pBuf;
    TDbEvent_8020C5C8 event;
    TDbEvent_8020C5C8 *pEvent;
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
    for (i = 0; i < pDst->mNumFields; i++) {
        map[i] = fn_8020B97C(pSrc, pDst->mFields[i].mId);
        if (map[i] != 0xFF) {
            unsigned int type = pSrc->mFields[map[i]].mType;

            if (type - 13 <= 2 || type <= 1) {
                if ((unsigned int)pSrc->mFields[map[i]].mBits > maxBits) {
                    maxBits = pSrc->mFields[map[i]].mBits;
                }
            }
        }
    }
    if (maxBits != 0) {
        int dbId = pSrc->mpOwner->mId;
        int tableId = pSrc->mId;

        pEvent = &event;
        if (lbl_803EBE80 != 0) {
            event.mDbId = dbId;
            event.mType = 2;
            event.mTableId = tableId;
            lbl_803EBE80(pEvent);
        }
        pResult->mErr = fn_8020D1B0(pSrc->mpOwner->mHeap, maxBits + 1, &pBuf);
        if (pResult->mErr != 0) {
            return pResult->mErr;
        }
        if (lbl_803EBE80 != 0) {
            pEvent->mType = 4;
            pEvent->mDbId = -1;
            pEvent->mTableId = -1;
            lbl_803EBE80(pEvent);
        }
    }
    fn_8020A540();
    for (rec = 0; rec < pSrc->mUnknown44; rec++) {
        int bReused;

        if (fn_8020C764_IsDeleted(pSrc, rec)) {
            continue;
        }
        if (pDst->mNumRecords == 0 && (pDst->mFlags & 8)) {
            fn_8020C5C8(pDst, pDst->mCapacity);
        }
        bReused = 0;
        if (pDst->mNumDeleted != 0) {
            record = pDst->mFreeHead;
            bReused = 1;
            pDst->mNumDeleted--;
            pDst->mFreeHead = *(unsigned short *)(pDst->mpRecords + pDst->mRecordSize * record);
        } else if (pDst->mUnknown44 < pDst->mNumRecords) {
            record = pDst->mUnknown44++;
        } else {
            err = 0x13;
        }
        if (err != 0) {
            continue;
        }
        memset(pDst->mpRecords + pDst->mRecordSize * record, 0, pDst->mRecordSize);
        for (i = 0; i < pDst->mNumFields; i++) {
            if (map[i] == 0xFF) {
                continue;
            }
            pData = pBuf;
            fn_8020C764_ReadField(pSrc, &pSrc->mFields[map[i]], pSrc->mpRecords + pSrc->mRecordSize * rec, &pData);
            fn_8020C764_WriteField(&pDst->mFields[i], pDst->mpRecords + pDst->mRecordSize * record, &pData);
        }
        {
            TDbQuery_8020C6C8 *pQuery;

            for (pQuery = pDst->mpQueries; pQuery != 0; pQuery = pQuery->mpNext) {
                err = fn_8020299C(pQuery, record);
                if (err != 0) {
                    for (pQuery = pDst->mpQueries; pQuery != 0; pQuery = pQuery->mpNext) {
                        fn_80202D34(pQuery, record);
                    }
                    break;
                }
            }
        }
        if (err == 0) {
            unsigned char *pFlags = pDst->mpRecords + pDst->mRecordSize * record;

            pFlags += pDst->mDeletedBit >> 3;
            *pFlags &= ~(1 << (7 - (pDst->mDeletedBit & 7)));
            pDst->mFlags |= 4;
            pResult->mCount++;
            fn_8020B710(pDst, record);
        } else if (bReused) {
            unsigned char *pFlags = pDst->mpRecords + pDst->mRecordSize * record;

            pFlags += pDst->mDeletedBit >> 3;
            *pFlags |= 1 << (7 - (pDst->mDeletedBit & 7));
            *(unsigned short *)(pDst->mpRecords + pDst->mRecordSize * record) = pDst->mFreeHead;
            pDst->mFreeHead = record;
            pDst->mNumDeleted++;
        } else {
            pDst->mUnknown44--;
        }
    }
    if (maxBits != 0) {
        fn_8020D2AC(pSrc->mpOwner->mHeap, pBuf, maxBits + 1);
    }
    pDst->mFlags &= ~1;
    if (pResult->mCount != 0) {
        fn_8020A5A8();
    }
    pResult->mErr = err;
    return err;
}
