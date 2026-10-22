#include <string.h>
#include "engine/t3db.h"

int fn_802071F8(TDbExpr_801FAA00 *pExpr, unsigned int column, TDbExpr_801FAA00 **ppOut);
int fn_802072E8(TDbExpr_801FAA00 *pA, TDbExpr_801FAA00 *pB);
extern unsigned int lbl_803EBE94;
extern TDbMemPool_80202B60 lbl_803E968C;

void fn_8020651C(TDbTable_801FAA00 *pTable, int row)
{
    TDbQuery_802032D8 *pQuery;
    TDbIdxNode_80201EC8 *pNode;
    unsigned int found;

    for (pQuery = lbl_803EBE90; pQuery != 0; pQuery = pQuery->mNext) {
        if (pQuery->mState == 0) {
            continue;
        }
        if (pQuery->mState != 3) {
            if (pTable == pQuery->mSource.mIndex->mTable && pQuery->mCur != 0 &&
                row == (unsigned short)pQuery->mCur->mRow) {
                pNode = fn_80202298(&pQuery->mSource.mIndex->mTree, pQuery->mCur);
                if (pNode == 0) {
                    pNode = fn_80202200(&pQuery->mSource.mIndex->mTree, pQuery->mCur);
                }
                pQuery->mCur = pNode;
            }
        } else {
            found = TDbStmtTableSlot_80205C44(pQuery->mSource.mQIdx->mStmt, pTable);
            if (found != 0) {
                found--;
                while (pQuery->mCur != 0 && row == ((unsigned short *)pQuery->mCur->mRow)[found]) {
                    pQuery->mCur = fn_80202298(&pQuery->mSource.mQIdx->mTree, pQuery->mCur);
                }
            }
        }
    }
}

void fn_80206668(TDbIndex_801FAA00 *pIndex, TDbIdxNode_80201EC8 *pOld, TDbIdxNode_80201EC8 *pNew)
{
    TDbQuery_802032D8 *pQuery;

    for (pQuery = lbl_803EBE90; pQuery != 0; pQuery = pQuery->mNext) {
        if ((pQuery->mState == 1 || pQuery->mState == 2) && pIndex == pQuery->mSource.mIndex &&
            pOld == pQuery->mCur) {
            if (pNew == 0) {
                pNew = fn_80202298(&pIndex->mTree, pOld);
                if (pNew == 0) {
                    pNew = fn_80202200(&pQuery->mSource.mIndex->mTree, pQuery->mCur);
                }
            }
            pQuery->mCur = pNew;
        }
    }
}

unsigned int fn_80206708(TDbIndex_801FAA00 *pIndex, TDbStmt_80205754 *pStmt, unsigned int table, int column,
                         TDbExpr_801FAA00 *pExpr)
{
    int score = -1;

    if (column != 0xFF && pIndex->mTree.mParts[0].mColumn == column) {
        if (pIndex->mFilter == 0) {
            score = 0;
            if (pExpr != pStmt->mTableExprs[table]) {
                score = pIndex->mCount;
            }
        } else if (pExpr != pStmt->mTableExprs[table] &&
                   fn_802072E8(pStmt->mTableExprs[table], pIndex->mFilter) != -1) {
            score = pIndex->mCount;
        }
    } else if (pExpr != pStmt->mTableExprs[table] && pIndex->mFilter != 0 &&
               fn_802072E8(pStmt->mTableExprs[table], pIndex->mFilter) != -1) {
        score = pIndex->mCount + 0xFFFF;
    }
    return score;
}

unsigned int fn_802067D4(TDbIndex_801FAA00 *pIndex, TDbExpr_801FAA00 *pExpr, TDbIdxColumnDef_801FFFC4 *pCols,
                         TDbExpr_801FAA00 **ppSeek)
{
    int score;
    int cmp;
    unsigned char i;

    *ppSeek = 0;
    score = -1;
    if (pExpr == 0 && pCols == 0) {
        return -1;
    }
    cmp = (pIndex->mFilter != 0 && pExpr != 0) ? fn_802072E8(pExpr, pIndex->mFilter) : 0;
    cmp = pExpr == 0 ? (pIndex->mFilter == 0 ? 1 : -1)
                     : (pIndex->mFilter == 0 ? 0 : fn_802072E8(pExpr, pIndex->mFilter));
    if (cmp == 1) {
        score = 1;
        if (pExpr == 0) {
            score = -1;
        }
        if (pCols != 0) {
            for (i = 0; pCols[i].mId != -1 && i < pIndex->mTree.mPartCount; i++) {
                if (pIndex->mTree.mParts[i].mColumn != pCols[i].mColumn ||
                    (pIndex->mTree.mParts[i].mDescending == 0) != pCols[i].mAscending) {
                    break;
                }
            }
            if (pCols[i].mId == -1) {
                score = 0;
            }
        } else {
            score = 0;
        }
    } else if (cmp == 0) {
        if (fn_802071F8(pExpr, pIndex->mTree.mParts[0].mColumn, ppSeek) != 0) {
            score = pIndex->mCount;
            if (!pIndex->mTree.mAllowDuplicates) {
                score = 2;
            }
        } else if ((unsigned int)((pIndex->mTable->mRowCount - pIndex->mTable->mUnknown46) / 2) >= pIndex->mCount) {
            score = pIndex->mCount + 0xFFFF;
        } else {
            score = -1;
        }
    }
    return score;
}

int fn_802069BC(TDbTable_801FAA00 *pTable, TDbIdxColumnDef_801FFFC4 *pCols, TDbExpr_801FAA00 *pFilter,
                TDbIndex_801FAA00 **ppIndex)
{
    TDbIdxColumnDef_801FFFC4 rowDef;
    unsigned char count;
    int err;
    TDbIndex_801FAA00 *pIndex;
    TDbMemEvent_801FC5FC event;

    memset(&rowDef, 0, sizeof(rowDef));
    TDbMemNotifyTo_801FC5FC(&event, 3, (int)pTable->mDb->mUnknown8, pTable->mUnknown1C);
    if (pCols == 0 || pCols[0].mId == -1) {
        rowDef.mColumn = TDB_COLUMN_ROW;
        pCols = &rowDef;
        count = 1;
    } else {
        count = 0;
        do {
            count++;
        } while (pCols[count].mId != -1);
    }
    if (count <= 2) {
        err = fn_8020360C(&lbl_803E96A8, ppIndex);
        (*ppIndex)->mFlags = 4;
    } else {
        err = fn_8020D1B0(pTable->mDb->mHeap, count * sizeof(TDbIdxPart_80202708) + 0x3C, ppIndex);
        (*ppIndex)->mFlags = 0;
    }
    if (err == 0) {
        pIndex = *ppIndex;
        fn_80204D14(pFilter, &pIndex->mFilter);
        err = fn_80203444(&pIndex->mPool, pTable->mDb->mHeap, count * 4 + 0x14,
                          (pFilter == 0 ? pTable->mCapacity : pTable->mCapacity >> 2) + 5, 100);
        if (err == 0) {
            pIndex->mLocked = 0;
            pIndex->mUserData = 0;
            pIndex->mTable = pTable;
            pIndex->mCount = 0;
            pIndex->mDestroyed = 1;
            pIndex->mTree.mRoot = 0;
            pIndex->mTree.mAllowDuplicates = 1;
            pIndex->mTree.mPartCount = count;
            for (count = 0; count < pIndex->mTree.mPartCount; count++) {
                pIndex->mTree.mParts[count].mColumn = pCols[count].mColumn;
                if (pCols[count].mColumn != TDB_COLUMN_ROW && pTable->mColumns[pCols[count].mColumn].mType <= 1) {
                    pIndex->mFlags |= 1;
                }
                pIndex->mTree.mParts[count].mDescending = pCols[count].mAscending == 0;
                pIndex->mTree.mParts[count].mTable = pTable;
            }
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
        } else if (pIndex->mFlags & 4) {
            fn_80203744(&lbl_803E96A8, pIndex);
        } else {
            fn_8020D2AC(pTable->mDb->mHeap, pIndex, count * sizeof(TDbIdxPart_80202708) + 0x3C);
        }
    }
    TDbMemNotifyEnd_801FC5FC(&event, 4);
    return err;
}

void fn_80206C9C(TDbQIdx_80205880 *pQIdx, TDbIdxNode_80201EC8 **ppNode)
{
    unsigned char i;
    unsigned int *pKey;
    unsigned short *pRows;
    unsigned int t;
    TDbTable_801FAA00 *pTable;
    TDbColumn_801FAA00 *pColumn;
    unsigned char *pRow;
    unsigned int row;

    fn_8020360C(&pQIdx->mPool, ppNode);
    fn_8020360C(&pQIdx->mKeyPool, &(*ppNode)->mRow);
    pRows = (unsigned short *)(*ppNode)->mRow;
    pKey = (*ppNode)->mKey;
    for (i = 0; i < pQIdx->mTree.mPartCount; i++) {
        unsigned char column = pQIdx->mTree.mParts[i].mColumn;
        unsigned char table = pQIdx->mTree.mParts[i].mUnknown4;

        if (column != TDB_COLUMN_ROW) {
            if (pQIdx->mStmt->mRows[table] != 0xFFFF) {
                row = pQIdx->mStmt->mRows[table];
                pTable = pQIdx->mStmt->mTables[table];
                pColumn = &pTable->mColumns[column];
                pRow = pTable->mRows + pTable->mRowSize * row;
                if (pColumn->mType > 1) {
                    fn_80201D94((unsigned int *)pRow, pColumn->mBitOffset, pColumn->mBitCount, &pKey[i],
                                pColumn->mType == 2);
                } else {
                    pKey[i] = (unsigned int)(pRow + (pColumn->mBitOffset >> 3));
                }
            } else {
                pColumn = &pQIdx->mStmt->mTables[table]->mColumns[column];
                if (pColumn->mType > 1) {
                    pKey[i] = 0;
                } else {
                    pKey[i] = lbl_803EBE94;
                }
            }
        } else {
            pKey[i] = pQIdx->mStmt->mRows[table];
        }
    }
    for (t = 0; t < pQIdx->mStmt->mTableCount; t++) {
        pRows[t] = pQIdx->mStmt->mRows[t];
    }
}

void fn_80206E4C(TDbQIdx_80205880 *pQIdx)
{
    void *pHeap;

    fn_80207DB4(pQIdx->mStmt);
    fn_80203744(&lbl_803E968C, pQIdx->mStmt);
    pHeap = pQIdx->mKeyPool.mHeap;
    fn_8020353C(&pQIdx->mKeyPool);
    fn_8020353C(&pQIdx->mPool);
    fn_8020D2AC(pHeap, pQIdx, pQIdx->mTree.mPartCount * sizeof(TDbIdxPart_80202708) + 0x4C);
}

int fn_80206EB8(TDbStmt_80205754 *pStmt, TDbIdxColumnDef_801FFFC4 *pCols, TDbQIdx_80205880 **ppQIdx)
{
    TDbIdxColumnDef_801FFFC4 rowDef[2] = {{0, TDB_COLUMN_ROW, 0, 0}, {-1, -1, 3, 0}};
    TDbDatabase_801FAA00 *pDb;
    unsigned int count;
    unsigned int t;
    int err;

    pDb = pStmt->mTables[0]->mDb;
    if (pCols == 0 || pCols[0].mId == -1) {
        pCols = rowDef;
        pCols[0].mColumn = TDB_COLUMN_ROW;
        count = 1;
    } else {
        count = 0;
        do {
            count++;
        } while (pCols[count].mId != -1);
    }
    TDbMemNotify_801FC9D4(3, (int)pDb->mUnknown8, -1);
    err = fn_8020D1B0(pDb->mHeap, count * sizeof(TDbIdxPart_80202708) + 0x4C, ppQIdx);
    TDbMemNotify_801FC9D4(4, -1, -1);
    (*ppQIdx)->mCount = 0;
    if (err == 0) {
        (*ppQIdx)->mStmt = pStmt;
        err = fn_80203444(&(*ppQIdx)->mPool, pDb->mHeap, count * 4 + 0x14, 100, 100);
        if (err == 0) {
            err = fn_80203444(&(*ppQIdx)->mKeyPool, pDb->mHeap,
                              (pStmt->mTableCount < 4 ? 4 : pStmt->mTableCount) * sizeof(unsigned short), 100, 100);
            if (err == 0) {
                (*ppQIdx)->mTree.mPartCount = count;
                (*ppQIdx)->mTree.mAllowDuplicates = 1;
                (*ppQIdx)->mTree.mRoot = 0;
                for (count = 0; count < (*ppQIdx)->mTree.mPartCount; count++) {
                    for (t = 0; t < pStmt->mTableCount; t++) {
                        if (pCols[count].mTableId == pStmt->mTables[t]->mUnknown1C || pCols[count].mTableId == 0) {
                            (*ppQIdx)->mTree.mParts[count].mTable = pStmt->mTables[t];
                            (*ppQIdx)->mTree.mParts[count].mUnknown4 = t;
                            (*ppQIdx)->mTree.mParts[count].mDescending = pCols[count].mAscending == 0;
                            (*ppQIdx)->mTree.mParts[count].mColumn =
                                pCols[count].mId != TDB_COLUMN_ROW ? fn_8020B97C(pStmt->mTables[t], pCols[count].mId)
                                                                   : TDB_COLUMN_ROW;
                            break;
                        }
                    }
                    if (t >= pStmt->mTableCount) {
                        err = 7;
                        break;
                    }
                    if ((*ppQIdx)->mTree.mParts[count].mColumn == 0xFF) {
                        err = 9;
                        break;
                    }
                }
                count = (*ppQIdx)->mTree.mPartCount;
                if (err != 0) {
                    fn_8020353C(&(*ppQIdx)->mKeyPool);
                }
            }
            if (err != 0) {
                fn_8020353C(&(*ppQIdx)->mPool);
            }
        }
        if (err != 0) {
            fn_8020D2AC(pDb->mHeap, *ppQIdx, count * sizeof(TDbIdxPart_80202708) + 0x4C);
        }
    }
    return err;
}

int fn_802071F8(TDbExpr_801FAA00 *pExpr, unsigned int column, TDbExpr_801FAA00 **ppOut)
{
    int found;

    if ((pExpr->mOp & 0x10000) && pExpr->mLeft.mType == TDB_TYPE_COLUMN &&
        (unsigned long long)column == pExpr->mLeft.mValue.l && (unsigned int)(pExpr->mOp - 0x10006) > 2) {
        *ppOut = pExpr;
        return 1;
    }
    if (pExpr->mOp == 0x20009) {
        if ((unsigned int)(pExpr->mLeft.mType - TDB_TYPE_EXPR_TRUNC) <= 2 &&
            fn_802071F8(pExpr->mLeft.mValue.p, column, ppOut)) {
            return 1;
        }
        if ((unsigned int)(pExpr->mRight.mType - TDB_TYPE_EXPR_TRUNC) <= 2) {
            found = fn_802071F8(pExpr->mRight.mValue.p, column, ppOut);
            return found;
        }
    }
    return 0;
}

static inline int TDbColEq_802072E8(unsigned long long a, unsigned long long b)
{
    return (a & 0xFFFFFFFF) == (b & 0xFFFFFFFF);
}

int fn_802072E8(TDbExpr_801FAA00 *pA, TDbExpr_801FAA00 *pB)
{
    int same = 0;
    int result = 0;
    int sameOp = pA->mOp == pB->mOp;

    if ((unsigned int)(pA->mOp - 0x2000A) <= 1) {
        result = -1;
    }
    if ((unsigned int)(pA->mLeft.mType - TDB_TYPE_EXPR_TRUNC) <= 2) {
        if (fn_802072E8(pA->mLeft.mValue.p, pB) != -1) {
            return result;
        }
    } else if (sameOp && pA->mLeft.mType == pB->mLeft.mType) {
        if (pA->mLeft.mType == TDB_TYPE_COLUMN) {
            same = TDbColEq_802072E8(pA->mLeft.mValue.l, pB->mLeft.mValue.l);
        } else {
            same = pA->mLeft.mValue.p == pB->mLeft.mValue.p;
        }
    }
    if ((unsigned int)(pA->mRight.mType - TDB_TYPE_EXPR_TRUNC) <= 2) {
        if (fn_802072E8(pA->mRight.mValue.p, pB) != -1) {
            return result;
        }
        return -1;
    }
    if (same && pA->mRight.mType == pB->mRight.mType && pA->mRight.mValue.l == pB->mRight.mValue.l) {
        return 1;
    }
    return -1;
}
