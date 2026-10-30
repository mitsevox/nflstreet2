#include <string.h>
#include "engine/t3db.h"
#include "engine/t3db_table.h"

extern TDbMemPool_80202B60 lbl_803E9670;
extern TDbHandler_8020A660 lbl_803E95DC[15];

int fn_802087D4(TDbQuery_802032D8 *pQuery)
{
    if (lbl_803EBE90 == pQuery) {
        lbl_803EBE90 = pQuery->mNext;
    } else {
        TDbQuery_802032D8 *pPrev = lbl_803EBE90;

        while (pPrev->mNext != pQuery) {
            pPrev = pPrev->mNext;
        }
        pPrev->mNext = pQuery->mNext;
    }
    if (pQuery->mState == 2) {
        if (--pQuery->mSource.mIndex->mLocked == 0) {
            fn_802032D8(pQuery->mSource.mIndex);
        }
    } else if (pQuery->mState == 1) {
        pQuery->mSource.mIndex->mLocked--;
    } else if (pQuery->mState == 3) {
        fn_80206E4C(pQuery->mSource.mQIdx);
    }
    fn_80203744(&lbl_803E9670, pQuery);
    return 0;
}

int fn_802088A8(TDbQuery_802032D8 *pQuery, unsigned short *pCount)
{
    switch (pQuery->mState) {
    case 0:
        *pCount = pQuery->mSource.mTable->mRowCount - pQuery->mSource.mTable->mUnknown46;
        break;
    case 1:
    case 2:
        *pCount = pQuery->mSource.mIndex->mCount;
        break;
    case 3:
        *pCount = pQuery->mSource.mQIdx->mCount;
        break;
    }
    return 0;
}

int fn_80209E40(TDbStmt_80205754 *pStmt, TDbLitRef_80205754 *pLit)
{
    for (; pLit->mId != -1; pLit++) {
        unsigned int j;

        if (pStmt->mTableCount == 1 || pLit->mTableId == 0) {
            j = 0;
        } else {
            int bFound = 0;

            for (j = 0; j < pStmt->mTableCount; j++) {
                if (pLit->mTableId == pStmt->mTables[j]->mUnknown1C) {
                    bFound = 1;
                    break;
                }
            }
            if (bFound != 1) {
                return 7;
            }
        }
        pLit->mColumn = fn_8020B97C(pStmt->mTables[j], pLit->mId);
        if (pLit->mColumn == 0xFF) {
            return 9;
        }
    }
    return 0;
}

void fn_8020A3A0(TDbStmt_80205754 *pStmt, TDbLitRef_80205754 *pLit)
{
    for (; pLit->mId != -1; pLit++) {
        unsigned int j;
        int row;

        if (pStmt->mTableCount == 1 || pLit->mTableId == 0) {
            j = 0;
        } else {
            for (j = 0; j <= pStmt->mTableCount; j++) {
                if (pLit->mTableId == pStmt->mTables[j]->mUnknown1C) {
                    break;
                }
            }
        }
        row = pStmt->mRows[j];
        if (row != 0xFFFF) {
            TDbTable_801FAA00 *pTable = pStmt->mTables[j];

            TDbReadColumn_8020A3A0(pTable, &pTable->mColumns[pLit->mColumn], pTable->mRows + row * pTable->mRowSize, pLit);
            if (pStmt->mTables[j]->mColumns[pLit->mColumn].mType == 0) {
                ((unsigned char *)pLit->mUnknown0)[pStmt->mTables[j]->mColumns[pLit->mColumn].mBitCount >> 3] = 0;
            }
        } else {
            pLit->mUnknown0 = 0;
        }
    }
}

void fn_8020A540(void)
{
    TDbQuery_802032D8 *pQuery;

    for (pQuery = lbl_803EBE90; pQuery != 0; pQuery = pQuery->mNext) {
        switch (pQuery->mState) {
        case 0:
            pQuery->mSource.mTable->mFlags &= ~4;
            break;
        case 1:
        case 2:
            pQuery->mSource.mIndex->mDirty = 0;
            break;
        case 3:
            pQuery->mSource.mQIdx->mDirty = 0;
            break;
        }
    }
}

void fn_8020A5A8(void)
{
    TDbQuery_802032D8 *pQuery;

    for (pQuery = lbl_803EBE90; pQuery != 0; pQuery = pQuery->mNext) {
        if (pQuery->mCallback == 0) {
            continue;
        }
        switch (pQuery->mState) {
        case 0:
            if (pQuery->mSource.mTable->mFlags & 4) {
                pQuery->mSource.mTable->mFlags &= ~4;
                pQuery->mCallback(pQuery->mCallbackArg);
            }
            break;
        case 1:
        case 2:
            if (pQuery->mSource.mIndex->mDirty) {
                pQuery->mSource.mIndex->mDirty = 0;
                pQuery->mCallback(pQuery->mCallbackArg);
            }
            break;
        case 3:
            pQuery->mSource.mQIdx->mDirty = 0;
            break;
        }
    }
}

int fn_8020A660(int unused, TDbStmt_80205754 *pStmt, int key, TDbLitRef_80205754 *pLits, int user, TDbResult_8020AD1C *pResult)
{
    unsigned char saved[0x100];
    TDbValue_801FDF28 value;
    unsigned int mask[8];
    unsigned char bEmit;
    TDbHandlerFn_8020A660 pFn;
    unsigned int i;
    int bSaved;
    int err;

    memset(mask, 0, sizeof(mask));
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
    if (pStmt->mTableCount == 1) {
        err = fn_80207E24(pStmt, 0, 0);
    } else {
        err = fn_80208094(pStmt);
    }
    if (err == 0) {
        bEmit = err;
        bSaved = 0;
        pFn(0, user, &bEmit);
        err = fn_80209E40(pStmt, pLits);
        if (err == 0) {
            err = fn_80205B88(pStmt);
            if (bEmit) {
                bSaved = 1;
                for (i = 0; pLits[i].mId != -1; i++) {
                    saved[i] = pLits[i].mColumn;
                }
            }
        }
        pResult->mCount = 0;
        if (err == 0) {
            for (err = fn_802075F4(pStmt, 0); err == 0; err = fn_80207988(pStmt, pStmt->mTableCount - 1)) {
                _TDbExprTest(pStmt->mWhere, &value, pStmt->mTables, pStmt->mRows);
                if (value.mValue.i != 0) {
                    pResult->mCount++;
                    fn_8020A3A0(pStmt, pLits);
                    pFn(pLits, user, &bEmit);
                    if (bSaved) {
                        for (i = 0; pLits[i].mId != -1; i++) {
                            pLits[i].mColumn = saved[i];
                        }
                    }
                    if (bEmit) {
                        fn_80209F34(pStmt, pLits, mask);
                        bEmit = 0;
                    }
                }
            }
            fn_80205754(pStmt, pLits, mask);
            fn_8020A5A8();
            fn_80205C08(pStmt);
        }
        if (pResult->mCount != 0 && err == 0x17) {
            err = 0;
        }
        pFn(0, user, 0);
    }
    pResult->mErr = err;
    return err;
}

int fn_8020AD1C(int unused, TDbStmt_80205754 *pStmt, TDbLitRef_80205754 *pLits, int bFirstOnly, TDbResult_8020AD1C *pResult)
{
    unsigned int mask[8];
    TDbValue_801FDF28 value;
    int err = 0;

    memset(mask, 0, sizeof(mask));
    fn_8020A540();
    pResult->mCount = err;
    if (pStmt->mTableCount == 1) {
        err = fn_80207E24(pStmt, 0, 0);
    } else {
        err = fn_80208094(pStmt);
    }
    if (err == 0) {
        err = fn_80205B88(pStmt);
        if (err == 0) {
            err = fn_80209E40(pStmt, pLits);
            if (err == 0) {
                for (err = fn_802075F4(pStmt, 0); err == 0; err = fn_80207988(pStmt, pStmt->mTableCount - 1)) {
                    _TDbExprTest(pStmt->mWhere, &value, pStmt->mTables, pStmt->mRows);
                    if (value.mValue.i != 0) {
                        pResult->mCount++;
                        fn_80209F34(pStmt, pLits, mask);
                        if (bFirstOnly) {
                            err = 0x17;
                            break;
                        }
                    }
                }
                fn_80205754(pStmt, pLits, mask);
                fn_80205C08(pStmt);
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
