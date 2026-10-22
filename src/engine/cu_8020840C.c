#include "engine/tmlib.h"

extern TDbLock_8020BD90 *lbl_803EBE90;
extern char lbl_803E9670[];
extern void fn_802032D8(TDbQuery_8020C6C8 *pQuery);
extern void fn_80206E4C(void *pList);
extern void fn_80203744(void *pPool, void *p);
extern int fn_80207E24(TDbQueryCtx_80209E40 *pCtx, int a, int b);
extern int fn_80208094(TDbQueryCtx_80209E40 *pCtx);
extern int fn_80205B88(TDbQueryCtx_80209E40 *pCtx);
extern int fn_802075F4(TDbQueryCtx_80209E40 *pCtx, int level);
extern int fn_80207988(TDbQueryCtx_80209E40 *pCtx, int level);
extern void fn_802047EC(int handle, TDbIter_8020AD1C *pIter, TDbTable_8020B564 **ppTables, unsigned short *pRecIdx);
extern void fn_80209F34(TDbQueryCtx_80209E40 *pCtx, TDbCond_80209E40 *pCond, void *pBuf);
extern void fn_80205754(TDbQueryCtx_80209E40 *pCtx, TDbCond_80209E40 *pCond, void *pBuf);
extern void fn_80205C08(TDbQueryCtx_80209E40 *pCtx);
extern TDbHandler_8020A660 lbl_803E95DC[15];
extern void fn_80201D94(void *pRecord, int bitOffset, int bitSize, void *pValue, int bSigned);

static inline void fn_8020A3A0_ReadField(TDbTable_8020B564 *pTable, TDbField_8020B564 *pField, unsigned char *pRecord, TDbCond_80209E40 *pCond)
{
    int type = pField->mType;

    if ((unsigned int)(type - 13) <= 2) {
        fn_8020CD9C(pTable, pField, pRecord, pCond->mpData);
    } else if ((unsigned int)type <= 1) {
        fn_8020CF34(pRecord, pField->mOffset, pField->mBits, pCond->mpData, (unsigned int)pField->mBits >> 3);
    } else {
        fn_80201D94(pRecord, pField->mOffset, pField->mBits, pCond, type == 2);
    }
}

int fn_802087D4(TDbLock_8020BD90 *pLock)
{
    if (lbl_803EBE90 == pLock) {
        lbl_803EBE90 = pLock->mpNext;
    } else {
        TDbLock_8020BD90 *pPrev = lbl_803EBE90;

        while (pPrev->mpNext != pLock) {
            pPrev = pPrev->mpNext;
        }
        pPrev->mpNext = pLock->mpNext;
    }
    if (pLock->mType == 2) {
        if (--((TDbQuery_8020C6C8 *)pLock->mpTarget)->mRefCount == 0) {
            fn_802032D8(pLock->mpTarget);
        }
    } else if (pLock->mType == 1) {
        ((TDbQuery_8020C6C8 *)pLock->mpTarget)->mRefCount--;
    } else if (pLock->mType == 3) {
        fn_80206E4C(pLock->mpTarget);
    }
    fn_80203744(lbl_803E9670, pLock);
    return 0;
}

int fn_802088A8(TDbLock_8020BD90 *pLock, unsigned short *pCount)
{
    switch (pLock->mType) {
    case 0:
        *pCount = ((TDbTable_8020B564 *)pLock->mpTarget)->mUnknown44 - ((TDbTable_8020B564 *)pLock->mpTarget)->mNumDeleted;
        break;
    case 1:
    case 2:
        *pCount = ((TDbQuery_8020C6C8 *)pLock->mpTarget)->mCount;
        break;
    case 3:
        *pCount = ((TDbList_802088A8 *)pLock->mpTarget)->mCount;
        break;
    }
    return 0;
}

int fn_80209E40(TDbQueryCtx_80209E40 *pCtx, TDbCond_80209E40 *pCond)
{
    for (; pCond->mFieldId != -1; pCond++) {
        unsigned int j;

        if (pCtx->mNumTables == 1 || pCond->mTableId == 0) {
            j = 0;
        } else {
            int bFound = 0;

            for (j = 0; j < pCtx->mNumTables; j++) {
                if (pCond->mTableId == pCtx->mpTables[j]->mId) {
                    bFound = 1;
                    break;
                }
            }
            if (bFound != 1) {
                return 7;
            }
        }
        pCond->mFieldIndex = fn_8020B97C(pCtx->mpTables[j], pCond->mFieldId);
        if (pCond->mFieldIndex == 0xFF) {
            return 9;
        }
    }
    return 0;
}

void fn_8020A3A0(TDbQueryCtx_80209E40 *pCtx, TDbCond_80209E40 *pCond)
{
    for (; pCond->mFieldId != -1; pCond++) {
        unsigned int j;
        int rec;

        if (pCtx->mNumTables == 1 || pCond->mTableId == 0) {
            j = 0;
        } else {
            for (j = 0; j <= pCtx->mNumTables; j++) {
                if (pCond->mTableId == pCtx->mpTables[j]->mId) {
                    break;
                }
            }
        }
        rec = pCtx->mRecIdx[j];
        if (rec != 0xFFFF) {
            TDbTable_8020B564 *pTable = pCtx->mpTables[j];

            fn_8020A3A0_ReadField(pTable, &pTable->mFields[pCond->mFieldIndex], pTable->mpRecords + rec * pTable->mRecordSize, pCond);
            if (pCtx->mpTables[j]->mFields[pCond->mFieldIndex].mType == 0) {
                ((unsigned char *)pCond->mpData)[(unsigned int)pCtx->mpTables[j]->mFields[pCond->mFieldIndex].mBits >> 3] = 0;
            }
        } else {
            pCond->mpData = 0;
        }
    }
}

void fn_8020A540(void)
{
    TDbLock_8020BD90 *pLock;

    for (pLock = lbl_803EBE90; pLock != 0; pLock = pLock->mpNext) {
        switch (pLock->mType) {
        case 0:
            ((TDbTable_8020B564 *)pLock->mpTarget)->mFlags &= ~4;
            break;
        case 1:
        case 2:
            ((TDbQuery_8020C6C8 *)pLock->mpTarget)->mbChanged = 0;
            break;
        case 3:
            ((TDbList_802088A8 *)pLock->mpTarget)->mbChanged = 0;
            break;
        }
    }
}

void fn_8020A5A8(void)
{
    TDbLock_8020BD90 *pLock;

    for (pLock = lbl_803EBE90; pLock != 0; pLock = pLock->mpNext) {
        if (pLock->mpCallback == 0) {
            continue;
        }
        switch (pLock->mType) {
        case 0:
            if (((TDbTable_8020B564 *)pLock->mpTarget)->mFlags & 4) {
                ((TDbTable_8020B564 *)pLock->mpTarget)->mFlags &= ~4;
                pLock->mpCallback(pLock->mCallbackArg);
            }
            break;
        case 1:
        case 2:
            if (((TDbQuery_8020C6C8 *)pLock->mpTarget)->mbChanged) {
                ((TDbQuery_8020C6C8 *)pLock->mpTarget)->mbChanged = 0;
                pLock->mpCallback(pLock->mCallbackArg);
            }
            break;
        case 3:
            ((TDbList_802088A8 *)pLock->mpTarget)->mbChanged = 0;
            break;
        }
    }
}

int fn_8020A660(int unused, TDbQueryCtx_80209E40 *pCtx, int key, TDbCond_80209E40 *pConds, int user, TDbResult_8020AD1C *pResult)
{
    unsigned char saved[0x100];
    TDbIter_8020AD1C iter;
    unsigned char buf[0x20];
    unsigned char bEmit;
    TDbHandlerFn_8020A660 pFn;
    unsigned int i;
    int bSaved;
    int err;

    memset(buf, 0, sizeof(buf));
    for (i = 0; i < 15; i++) {
        if (key == lbl_803E95DC[i].mKey) {
            pFn = lbl_803E95DC[i].mpFn;
            break;
        }
    }
    if (i >= 15) {
        return 0xB;
    }
    fn_8020A540();
    if (pCtx->mNumTables == 1) {
        err = fn_80207E24(pCtx, 0, 0);
    } else {
        err = fn_80208094(pCtx);
    }
    if (err == 0) {
        bEmit = err;
        bSaved = 0;
        pFn(0, user, &bEmit);
        err = fn_80209E40(pCtx, pConds);
        if (err == 0) {
            err = fn_80205B88(pCtx);
            if (bEmit) {
                bSaved = 1;
                for (i = 0; pConds[i].mFieldId != -1; i++) {
                    saved[i] = pConds[i].mFieldIndex;
                }
            }
        }
        pResult->mCount = 0;
        if (err == 0) {
            for (err = fn_802075F4(pCtx, 0); err == 0; err = fn_80207988(pCtx, pCtx->mNumTables - 1)) {
                fn_802047EC(pCtx->mUnknown04, &iter, pCtx->mpTables, pCtx->mRecIdx);
                if (iter.mbValid != 0) {
                    pResult->mCount++;
                    fn_8020A3A0(pCtx, pConds);
                    pFn(pConds, user, &bEmit);
                    if (bSaved) {
                        for (i = 0; pConds[i].mFieldId != -1; i++) {
                            pConds[i].mFieldIndex = saved[i];
                        }
                    }
                    if (bEmit) {
                        fn_80209F34(pCtx, pConds, buf);
                        bEmit = 0;
                    }
                }
            }
            fn_80205754(pCtx, pConds, buf);
            fn_8020A5A8();
            fn_80205C08(pCtx);
        }
        if (pResult->mCount != 0 && err == 0x17) {
            err = 0;
        }
        pFn(0, user, 0);
    }
    pResult->mErr = err;
    return err;
}

int fn_8020AD1C(int unused, TDbQueryCtx_80209E40 *pCtx, TDbCond_80209E40 *pCond, int bFirstOnly, TDbResult_8020AD1C *pResult)
{
    unsigned char buf[0x20];
    TDbIter_8020AD1C iter;
    int err = 0;

    memset(buf, 0, sizeof(buf));
    fn_8020A540();
    pResult->mCount = err;
    if (pCtx->mNumTables == 1) {
        err = fn_80207E24(pCtx, 0, 0);
    } else {
        err = fn_80208094(pCtx);
    }
    if (err == 0) {
        err = fn_80205B88(pCtx);
        if (err == 0) {
            err = fn_80209E40(pCtx, pCond);
            if (err == 0) {
                for (err = fn_802075F4(pCtx, 0); err == 0; err = fn_80207988(pCtx, pCtx->mNumTables - 1)) {
                    fn_802047EC(pCtx->mUnknown04, &iter, pCtx->mpTables, pCtx->mRecIdx);
                    if (iter.mbValid != 0) {
                        pResult->mCount++;
                        fn_80209F34(pCtx, pCond, buf);
                        if (bFirstOnly) {
                            err = 0x17;
                            break;
                        }
                    }
                }
                fn_80205754(pCtx, pCond, buf);
                fn_80205C08(pCtx);
            }
        }
        fn_8020A5A8();
    }
    if (pResult->mCount != 0 && err == 0x17) {
        err = 0;
    }
    pResult->mErr = err;
    return err;
}
