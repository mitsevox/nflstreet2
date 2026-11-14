#include <string.h>
#include "engine/t3db.h"

int fn_802071F8(TDbExpr_t *pExpr, unsigned int column, TDbExpr_t **ppOut);
int fn_802072E8(TDbExpr_t *pA, TDbExpr_t *pB);
extern unsigned int lbl_803EBE94;
extern TDbMemPool_t lbl_803E968C;
extern int lbl_802F9B78[];

void fn_8020651C(TDbTable_t *pTable, int row)
{
    TDbQuery_t *pQuery;
    TDbIdxNode_t *pNode;
    unsigned int found;

    for (pQuery = lbl_803EBE90; pQuery != 0; pQuery = pQuery->mNext) {
        if (pQuery->mState == 0) {
            continue;
        }
        if (pQuery->mState != 3) {
            if (pTable == pQuery->mSource.mIndex->mTable && pQuery->mCur != 0 &&
                row == (unsigned short)pQuery->mCur->mRow) {
                pNode = _TDbIdxTreeMoveLeft(&pQuery->mSource.mIndex->mTree, pQuery->mCur);
                if (pNode == 0) {
                    pNode = _TDbIdxTreeMoveRight(&pQuery->mSource.mIndex->mTree, pQuery->mCur);
                }
                pQuery->mCur = pNode;
            }
        } else {
            found = TDbStmtTableSlot_80205C44(pQuery->mSource.mQIdx->mStmt, pTable);
            if (found != 0) {
                found--;
                while (pQuery->mCur != 0 && row == ((unsigned short *)pQuery->mCur->mRow)[found]) {
                    pQuery->mCur = _TDbIdxTreeMoveLeft(&pQuery->mSource.mQIdx->mTree, pQuery->mCur);
                }
            }
        }
    }
}

void fn_80206668(TDbIndex_t *pIndex, TDbIdxNode_t *pOld, TDbIdxNode_t *pNew)
{
    TDbQuery_t *pQuery;

    for (pQuery = lbl_803EBE90; pQuery != 0; pQuery = pQuery->mNext) {
        if ((pQuery->mState == 1 || pQuery->mState == 2) && pIndex == pQuery->mSource.mIndex &&
            pOld == pQuery->mCur) {
            if (pNew == 0) {
                pNew = _TDbIdxTreeMoveLeft(&pIndex->mTree, pOld);
                if (pNew == 0) {
                    pNew = _TDbIdxTreeMoveRight(&pQuery->mSource.mIndex->mTree, pQuery->mCur);
                }
            }
            pQuery->mCur = pNew;
        }
    }
}

unsigned int fn_80206708(TDbIndex_t *pIndex, TDbStmt_80205754 *pStmt, unsigned int table, int column,
                         TDbExpr_t *pExpr)
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

unsigned int fn_802067D4(TDbIndex_t *pIndex, TDbExpr_t *pExpr, TDbIdxColumnDef_t *pCols,
                         TDbExpr_t **ppSeek)
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
                    (pIndex->mTree.mParts[i].mAscending == 0) != pCols[i].mDescending) {
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

int fn_802069BC(TDbTable_t *pTable, TDbIdxColumnDef_t *pCols, TDbExpr_t *pFilter,
                TDbIndex_t **ppIndex)
{
    TDbIdxColumnDef_t rowDef;
    unsigned char count;
    int err;
    TDbIndex_t *pIndex;

    memset(&rowDef, 0, sizeof(rowDef));
    _TDbMemNotify(3, (int)pTable->mDb->mUnknown8, pTable->mUnknown1C);
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
        err = __TDbMemPoolAlloc(&lbl_803E96A8, ppIndex);
        (*ppIndex)->mFlags = 4;
    } else {
        err = TDbExtMemAlloc(pTable->mDb->mHeap, count * sizeof(TDbIdxPart_t) + 0x3C, ppIndex);
        (*ppIndex)->mFlags = 0;
    }
    if (err == 0) {
        pIndex = *ppIndex;
        _TDbExprCopy(pFilter, &pIndex->mFilter);
        err = _TDbMemPoolInit(&pIndex->mPool, pTable->mDb->mHeap, count * 4 + 0x14,
                          (pFilter == 0 ? pTable->mCapacity : pTable->mCapacity >> 2) + 5, 100);
        if (err == 0) {
            pIndex->mLocked = 0;
            pIndex->mId = 0;
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
                pIndex->mTree.mParts[count].mAscending = pCols[count].mDescending == 0;
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
            __TDbMemPoolFree(&lbl_803E96A8, pIndex);
        } else {
            TDbExtMemFree(pTable->mDb->mHeap, pIndex, count * sizeof(TDbIdxPart_t) + 0x3C);
        }
    }
    _TDbMemNotify(4, -1, -1);
    return err;
}

void fn_80206C9C(TDbQIdx_80205880 *pQIdx, TDbIdxNode_t **ppNode)
{
    unsigned char i;
    unsigned int *pKey;
    unsigned short *pRows;
    unsigned int t;
    TDbTable_t *pTable;
    TDbColumn_t *pColumn;
    unsigned char *pRow;
    unsigned int row;

    __TDbMemPoolAlloc(&pQIdx->mPool, ppNode);
    __TDbMemPoolAlloc(&pQIdx->mKeyPool, &(*ppNode)->mRow);
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
                    _TDbDataGetBitData((unsigned int *)pRow, pColumn->mBitOffset, pColumn->mBitCount, &pKey[i],
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
    __TDbMemPoolFree(&lbl_803E968C, pQIdx->mStmt);
    pHeap = pQIdx->mKeyPool.mHeap;
    _TDbMemPoolDeinit(&pQIdx->mKeyPool);
    _TDbMemPoolDeinit(&pQIdx->mPool);
    TDbExtMemFree(pHeap, pQIdx, pQIdx->mTree.mPartCount * sizeof(TDbIdxPart_t) + 0x4C);
}

int fn_80206EB8(TDbStmt_80205754 *pStmt, TDbIdxColumnDef_t *pCols, TDbQIdx_80205880 **ppQIdx)
{
    TDbIdxColumnDef_t rowDef[2] = {{0, TDB_COLUMN_ROW, 0, 0}, {-1, -1, 3, 0}};
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
    _TDbMemNotify(3, (int)pDb->mUnknown8, -1);
    err = TDbExtMemAlloc(pDb->mHeap, count * sizeof(TDbIdxPart_t) + 0x4C, ppQIdx);
    _TDbMemNotify(4, -1, -1);
    (*ppQIdx)->mCount = 0;
    if (err == 0) {
        (*ppQIdx)->mStmt = pStmt;
        err = _TDbMemPoolInit(&(*ppQIdx)->mPool, pDb->mHeap, count * 4 + 0x14, 100, 100);
        if (err == 0) {
            err = _TDbMemPoolInit(&(*ppQIdx)->mKeyPool, pDb->mHeap,
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
                            (*ppQIdx)->mTree.mParts[count].mAscending = pCols[count].mDescending == 0;
                            (*ppQIdx)->mTree.mParts[count].mColumn =
                                pCols[count].mId != TDB_COLUMN_ROW ? _TDbTblResolveColRef(pStmt->mTables[t], pCols[count].mId)
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
                    _TDbMemPoolDeinit(&(*ppQIdx)->mKeyPool);
                }
            }
            if (err != 0) {
                _TDbMemPoolDeinit(&(*ppQIdx)->mPool);
            }
        }
        if (err != 0) {
            TDbExtMemFree(pDb->mHeap, *ppQIdx, count * sizeof(TDbIdxPart_t) + 0x4C);
        }
    }
    return err;
}

int fn_802071F8(TDbExpr_t *pExpr, unsigned int column, TDbExpr_t **ppOut)
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

int fn_802072E8(TDbExpr_t *pA, TDbExpr_t *pB)
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

unsigned char fn_80207448(TDbExpr_t *pExpr, unsigned int table, unsigned int *pOtherTable,
                          TDbExpr_t **ppSeek)
{
    TDbValue_t tmp;
    unsigned char column;

    column = 0xFF;
    if (pExpr->mOp != 0x2000A) {
        if (pExpr->mLeft.mType >= TDB_TYPE_EXPR_TRUNC && pExpr->mLeft.mType <= TDB_TYPE_EXPR_FLOAT) {
            column = fn_80207448(pExpr->mLeft.mValue.p, table, pOtherTable, ppSeek);
        }
        if (column == 0xFF) {
            if (pExpr->mRight.mType >= TDB_TYPE_EXPR_TRUNC && pExpr->mRight.mType <= TDB_TYPE_EXPR_FLOAT) {
                column = fn_80207448(pExpr->mRight.mValue.p, table, pOtherTable, ppSeek);
            }
            if (column == 0xFF && pExpr->mLeft.mType == TDB_TYPE_COLUMN && pExpr->mRight.mType == TDB_TYPE_COLUMN &&
                (pExpr->mOp & 0x10000)) {
                if (table == (pExpr->mRight.mValue.l >> 32)) {
                    tmp = pExpr->mRight;
                    pExpr->mRight = pExpr->mLeft;
                    pExpr->mLeft = tmp;
                    pExpr->mOp = lbl_802F9B78[pExpr->mOp - 0x10001];
                    *ppSeek = pExpr;
                    column = pExpr->mRight.mValue.l;
                    *pOtherTable = pExpr->mLeft.mValue.l >> 32;
                }
                if (table == (pExpr->mLeft.mValue.l >> 32)) {
                    *ppSeek = pExpr;
                    column = pExpr->mLeft.mValue.l;
                    *pOtherTable = pExpr->mRight.mValue.l >> 32;
                }
            }
        }
    }
    return column;
}

