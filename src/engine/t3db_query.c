#include <string.h>
#include "engine/t3db.h"
#include "engine/t3db_table.h"

int fn_80205880(TDbTable_t *pTable, unsigned char column, TDbQIdx_80205880 *pQIdx);
int fn_80205A10(TDbQIdx_80205880 *pQIdx, TDbIdxNode_t **ppCur);

int fn_80205754(TDbStmt_80205754 *pStmt, TDbLitRef_t *pLits, unsigned int *pMask)
{
    TDbQuery_t *pQuery;
    unsigned int i;
    unsigned int lit;

    for (pQuery = lbl_803EBE90; pQuery != 0; pQuery = pQuery->mNext) {
        if (pQuery->mState != 3) {
            continue;
        }
        for (i = 0; i < pStmt->mTableCount; i++) {
            for (lit = 0; pLits[lit].mId != -1; lit++) {
                if (pStmt->mTableCount == 1 || pLits[lit].mTableId == pStmt->mTables[i]->mId ||
                    (pLits[lit].mTableId == 0 && i == 0)) {
                    if (pMask[lit >> 5] & (1 << (lit & 31))) {
                        if (fn_80205880(pStmt->mTables[i], pLits[lit].mColumn, pQuery->mSource.mQIdx)) {
                            fn_80205A10(pQuery->mSource.mQIdx, &pQuery->mCur);
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int fn_80205880(TDbTable_t *pTable, unsigned char column, TDbQIdx_80205880 *pQIdx)
{
    unsigned int table;
    unsigned int i;
    int used = 0;

    for (table = 0; table < pQIdx->mStmt->mTableCount; table++) {
        if (pTable == pQIdx->mStmt->mTables[table]) {
            break;
        }
    }
    if (table < pQIdx->mStmt->mTableCount) {
        if (column > 0xFE) {
            used = 1;
        } else {
            for (i = 0; i < pQIdx->mTree.mPartCount; i++) {
                if (pQIdx->mTree.mParts[i].mUnknown4 == table && pQIdx->mTree.mParts[i].mColumn == column) {
                    used = 1;
                    break;
                }
            }
            if (!used) {
                if (pQIdx->mStmt->mWhere != 0) {
                    used = _TDbExprFindTableCol(pQIdx->mStmt->mWhere, (unsigned long long)table << 32 | column);
                }
                if (!used) {
                    for (i = table; i < pQIdx->mStmt->mTableCount; i++) {
                        if (pQIdx->mStmt->mTableExprs[i] != 0) {
                            used = _TDbExprFindTableCol(pQIdx->mStmt->mTableExprs[i],
                                               (unsigned long long)table << 32 | column);
                            if (used) {
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    return used;
}

int fn_80205A10(TDbQIdx_80205880 *pQIdx, TDbIdxNode_t **ppCur)
{
    unsigned int key[10];
    TDbValue_t result;
    TDbIdxNode_t *pNode;
    TDbIdxTree_t *pTree;
    int err;

    if (*ppCur != 0) {
        memcpy(key, (*ppCur)->mKey, pQIdx->mTree.mPartCount * 4);
    } else {
        memset(key, 0, sizeof(key));
    }
    err = _TDbMemPoolReset(&pQIdx->mPool);
    if (err == 0) {
        _TDbMemPoolReset(&pQIdx->mKeyPool);
        pQIdx->mCount = 0;
        pQIdx->mTree.mRoot = 0;
        err = fn_80208094(pQIdx->mStmt);
        if (err == 0) {
            pTree = &pQIdx->mTree;
            err = fn_802075F4(pQIdx->mStmt, 0);
            while (err == 0) {
                _TDbExprTest(pQIdx->mStmt->mWhere, &result, pQIdx->mStmt->mTables, pQIdx->mStmt->mRows);
                if (result.mValue.i != 0) {
                    fn_80206C9C(pQIdx, &pNode);
                    pNode->mColor = 1;
                    pNode->mParent = pNode->mChild[0] = pNode->mChild[1] = 0;
                    _TDbIdxTreeInsert(pTree, pNode, 0);
                    pQIdx->mCount++;
                }
                err = fn_80207988(pQIdx->mStmt, pQIdx->mStmt->mTableCount - 1);
            }
            if (err != 0x17 && err != 0x15 && err != 0x14) {
                fn_80206E4C(pQIdx);
            } else {
                err = 0;
            }
            pQIdx->mDirty = 1;
            *ppCur = _TDbIdxSeekClosest(pTree, key);
        }
    }
    return err;
}

int fn_80205B88(TDbStmt_80205754 *pStmt)
{
    unsigned int i;

    for (i = 0; i < pStmt->mTableCount; i++) {
        if (!(pStmt->mTables[i]->mFlags & 1)) {
            pStmt->mTables[i]->mFlags |= 1;
        } else {
            while (i != 0) {
                i--;
                pStmt->mTables[i]->mFlags &= ~1;
            }
            return 0x1E;
        }
    }
    return 0;
}

void fn_80205C08(TDbStmt_80205754 *pStmt)
{
    unsigned int i;

    for (i = 0; i < pStmt->mTableCount; i++) {
        pStmt->mTables[i]->mFlags &= ~1;
    }
}

void fn_80205C44(TDbTable_t *pTable, int row)
{
    TDbQuery_t *pQuery;
    TDbIdxNode_t *pNode;
    TDbIdxNode_t *pNext;
    unsigned int found;

    for (pQuery = lbl_803EBE90; pQuery != 0; pQuery = pQuery->mNext) {
        found = 0;
        if (pQuery->mState == 3) {
            found = TDbStmtTableSlot_80205C44(pQuery->mSource.mQIdx->mStmt, pTable);
        }
        if (found != 0) {
            pQuery->mSource.mQIdx->mDirty = 1;
            found--;
            pNode = _TDbIdxTreeMoveRight(&pQuery->mSource.mQIdx->mTree, 0);
            while (pNode != 0) {
                pNext = _TDbIdxTreeMoveRight(&pQuery->mSource.mQIdx->mTree, pNode);
                if (row == ((unsigned short *)pNode->mRow)[found]) {
                    if (pNode == pQuery->mCur) {
                        pQuery->mCur = _TDbIdxTreeMoveLeft(&pQuery->mSource.mQIdx->mTree, pNode);
                        if (pQuery->mCur == 0) {
                            pQuery->mCur = _TDbIdxTreeMoveRight(&pQuery->mSource.mQIdx->mTree, pNode);
                        }
                    }
                    _TDbIdxTreeDelete(&pQuery->mSource.mQIdx->mTree, pNode);
                    __TDbMemPoolFree(&pQuery->mSource.mQIdx->mPool, pNode);
                    pQuery->mSource.mQIdx->mDirty = 1;
                    pQuery->mSource.mQIdx->mCount--;
                }
                pNode = pNext;
            }
        }
    }
}


#if defined(DECOMP_COMPARE)

int fn_802071F8(TDbExpr_t *pExpr, unsigned int column, TDbExpr_t **ppOut);
int fn_802072E8(TDbExpr_t *pA, TDbExpr_t *pB);
extern unsigned int lbl_803EBE94;
extern TDbMemPool_t lbl_803E968C;
extern int lbl_802F9B78[];

int fn_80205DB8(TDbStmt_80205754 *pStmt, TDbExpr_t *pSrc, TDbExpr_t **ppDst, int top)
{
    int err;
    int leftTrue;
    int rightTrue;
    int sub;
    unsigned int i;
    unsigned char column;
    unsigned long long value;
    TDbExpr_t *pNew;

    if (ppDst == 0) {
        top = 1;
        ppDst = &pStmt->mWhere;
    }
    if (pSrc == 0) {
        *ppDst = 0;
        return 0;
    }
    if (top && pSrc->mOp == 0 && pSrc->mLeft.mType <= TDB_TYPE_FLOAT) {
        *ppDst = 0;
        return 0;
    }
    sub = 0;
    if (top) {
        sub = pSrc->mOp == 0x20009;
    }
    rightTrue = 0;
    err = __TDbMemPoolAlloc(&lbl_803E9654, ppDst);
    leftTrue = 0;
    if (err) {
        return 2;
    }

    switch (pSrc->mLeft.mType) {
    case TDB_TYPE_STRING:
    case TDB_TYPE_BINARY:
        if (pSrc->mLeft.mType == TDB_TYPE_STRING) {
            (*ppDst)->mLeft.mSize = strlen(pSrc->mLeft.mValue.s) + 1;
        } else {
            (*ppDst)->mLeft.mSize = pSrc->mLeft.mSize;
        }
        err = TDbExtMemAlloc(_tDbGlobalMemoryHeapID, (*ppDst)->mLeft.mSize, &(*ppDst)->mLeft.mValue.p);
        memcpy((*ppDst)->mLeft.mValue.p, pSrc->mLeft.mValue.p, (*ppDst)->mLeft.mSize);
        (*ppDst)->mLeft.mType = pSrc->mLeft.mType;
        break;
    case TDB_TYPE_COLUMN:
        for (i = 0; i < pStmt->mTableCount; i++) {
            if ((int)(pSrc->mLeft.mValue.l >> 32) == pStmt->mTables[i]->mId) {
                column = _TDbTblResolveColRef(pStmt->mTables[i], (int)pSrc->mLeft.mValue.l);
                if (column == 0xFF) {
                    return 9;
                }
                (*ppDst)->mLeft.mValue.l = ((unsigned long long)i << 32) | column;
                (*ppDst)->mLeft.mType = TDB_TYPE_COLUMN;
                break;
            }
        }
        if (i >= pStmt->mTableCount) {
            err = 7;
        }
        break;
    case TDB_TYPE_EXPR_TRUNC:
    case TDB_TYPE_EXPR_UINT:
    case TDB_TYPE_EXPR_FLOAT:
        (*ppDst)->mLeft.mType = pSrc->mLeft.mType;
        err = fn_80205DB8(pStmt, pSrc->mLeft.mValue.p, (TDbExpr_t **)&(*ppDst)->mLeft.mValue.p, sub);
        if ((*ppDst)->mLeft.mValue.p == 0) {
            leftTrue = 1;
        }
        break;
    default:
        err = 0;
        (*ppDst)->mLeft.mType = pSrc->mLeft.mType;
        (*ppDst)->mLeft.mValue.u = pSrc->mLeft.mValue.u;
        leftTrue = pSrc->mRight.mValue.u == 1;
        break;
    }

    switch (pSrc->mRight.mType) {
    case TDB_TYPE_STRING:
    case TDB_TYPE_BINARY:
        if (pSrc->mRight.mType == TDB_TYPE_STRING) {
            (*ppDst)->mRight.mSize = strlen(pSrc->mRight.mValue.s) + 1;
        } else {
            (*ppDst)->mRight.mSize = pSrc->mRight.mSize;
        }
        err = TDbExtMemAlloc(_tDbGlobalMemoryHeapID, (*ppDst)->mRight.mSize, &(*ppDst)->mRight.mValue.p);
        memcpy((*ppDst)->mRight.mValue.p, pSrc->mRight.mValue.p, (*ppDst)->mRight.mSize);
        (*ppDst)->mRight.mType = pSrc->mRight.mType;
        break;
    case TDB_TYPE_COLUMN:
        for (i = 0; i < pStmt->mTableCount; i++) {
            if ((int)(pSrc->mRight.mValue.l >> 32) == pStmt->mTables[i]->mId) {
                column = _TDbTblResolveColRef(pStmt->mTables[i], (int)pSrc->mRight.mValue.l);
                if (column == 0xFF) {
                    return 9;
                }
                value = ((unsigned long long)i << 32) | column;
                (*ppDst)->mRight.mValue.l = value;
                (*ppDst)->mRight.mType = TDB_TYPE_COLUMN;
                if ((*ppDst)->mLeft.mType <= TDB_TYPE_FLOAT && ((*ppDst)->mOp & 0x30000)) {
                    (*ppDst)->mRight.mValue.l = (*ppDst)->mLeft.mValue.l;
                    (*ppDst)->mRight.mType = (*ppDst)->mLeft.mType;
                    (*ppDst)->mRight.mSize = (*ppDst)->mLeft.mSize;
                    (*ppDst)->mLeft.mValue.l = value;
                    (*ppDst)->mLeft.mType = TDB_TYPE_COLUMN;
                    (*ppDst)->mOp = pSrc->mOp == 0x10005 ? 0x10002
                                  : pSrc->mOp == 0x10004 ? 0x10001
                                  : pSrc->mOp == 0x10002 ? 0x10005
                                  : pSrc->mOp == 0x10001 ? 0x10004
                                  : (*ppDst)->mOp;
                }
                break;
            }
        }
        if (i >= pStmt->mTableCount) {
            err = 7;
        }
        break;
    case TDB_TYPE_EXPR_TRUNC:
    case TDB_TYPE_EXPR_UINT:
    case TDB_TYPE_EXPR_FLOAT:
        (*ppDst)->mRight.mType = pSrc->mRight.mType;
        err = fn_80205DB8(pStmt, pSrc->mRight.mValue.p, (TDbExpr_t **)&(*ppDst)->mRight.mValue.p, sub);
        if ((*ppDst)->mRight.mValue.p == 0) {
            rightTrue = 1;
        }
        break;
    default:
        (*ppDst)->mRight.mType = pSrc->mRight.mType;
        (*ppDst)->mRight.mValue.l = pSrc->mRight.mValue.l;
        if (pSrc->mRight.mType <= TDB_TYPE_FLOAT) {
            rightTrue = pSrc->mRight.mValue.u == 1;
        }
        err = 0;
        break;
    }

    (*ppDst)->mOp = pSrc->mOp;
    if ((leftTrue || rightTrue) && ((*ppDst)->mOp & 0x20000)) {
        if ((*ppDst)->mOp == 0x20009) {
            if (!rightTrue) {
                pNew = (*ppDst)->mRight.mValue.p;
                __TDbMemPoolFree(&lbl_803E9654, *ppDst);
                *ppDst = pNew;
            } else if (!leftTrue) {
                pNew = (*ppDst)->mLeft.mValue.p;
                __TDbMemPoolFree(&lbl_803E9654, *ppDst);
                *ppDst = pNew;
            } else {
                __TDbMemPoolFree(&lbl_803E9654, *ppDst);
                *ppDst = 0;
                return err;
            }
        } else if ((*ppDst)->mOp == 0x2000A) {
            if (!leftTrue) {
                _TDbExprFree((*ppDst)->mLeft.mValue.p);
            } else if (!rightTrue) {
                _TDbExprFree((*ppDst)->mRight.mValue.p);
            }
            __TDbMemPoolFree(&lbl_803E9654, *ppDst);
            *ppDst = 0;
            return err;
        } else {
            if (leftTrue) {
                (*ppDst)->mLeft.mType = TDB_TYPE_UINT;
                (*ppDst)->mLeft.mValue.u = 1;
            }
            if (rightTrue) {
                (*ppDst)->mRight.mType = TDB_TYPE_UINT;
                (*ppDst)->mRight.mValue.u = 1;
            }
        }
        return err;
    }

    if ((*ppDst)->mLeft.mType == TDB_TYPE_COLUMN) {
        if ((*ppDst)->mRight.mType <= TDB_TYPE_FLOAT) {
            column = (*ppDst)->mLeft.mValue.l;
            if (pStmt->mTables[(int)((*ppDst)->mLeft.mValue.l >> 32)]->mColumns[column].mType == TDB_TYPE_UINT) {
                if ((*ppDst)->mRight.mType == TDB_TYPE_INT) {
                    (*ppDst)->mRight.mType = TDB_TYPE_UINT;
                }
                if ((*ppDst)->mRight.mValue.u == 0 && (*ppDst)->mOp == 0x10005) {
                    __TDbMemPoolFree(&lbl_803E9654, *ppDst);
                    *ppDst = 0;
                    return err;
                }
            }
        }
        if (((*ppDst)->mRight.mType <= TDB_TYPE_FLOAT || (*ppDst)->mRight.mType - 0x10007 <= 1) && top &&
            (pSrc->mOp & 0x10000)) {
            i = (int)((*ppDst)->mLeft.mValue.l >> 32);
            if (pStmt->mTableExprs[i] != 0) {
                err = __TDbMemPoolAlloc(&lbl_803E9654, &pNew);
                pNew->mLeft.mType = pNew->mRight.mType = TDB_TYPE_EXPR_UINT;
                pNew->mOp = 0x20009;
                pNew->mLeft.mValue.p = pStmt->mTableExprs[i];
                pNew->mRight.mValue.p = *ppDst;
                pStmt->mTableExprs[i] = pNew;
            } else {
                pStmt->mTableExprs[i] = *ppDst;
            }
            *ppDst = 0;
            return err;
        }
    }
    return err;
}

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
        } else if ((unsigned int)((pIndex->mTable->mRowCount - pIndex->mTable->mDeletedCount) / 2) >= pIndex->mCount) {
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
    _TDbMemNotify(3, (int)pTable->mDb->mId, pTable->mId);
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
        err = __TDbMemPoolAlloc(&_tDbIndexPool, ppIndex);
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
            __TDbMemPoolFree(&_tDbIndexPool, pIndex);
        } else {
            TDbExtMemFree(pTable->mDb->mHeap, pIndex, count * sizeof(TDbIdxPart_t) + 0x3C);
        }
    }
    _TDbMemNotifyEnd();
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
    TDbDatabase_t *pDb;
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
    _TDbMemNotify(3, (int)pDb->mId, -1);
    err = TDbExtMemAlloc(pDb->mHeap, count * sizeof(TDbIdxPart_t) + 0x4C, ppQIdx);
    _TDbMemNotifyEnd();
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
                        if (pCols[count].mTableId == pStmt->mTables[t]->mId || pCols[count].mTableId == 0) {
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



extern int fn_801F88F0(void *pDb, int id, int *pOut, TDbTable_t **ppTable);
extern unsigned char fn_80207448(TDbExpr_t *pExpr, unsigned int table, unsigned int *pOtherTable,
                                 TDbExpr_t **ppOut);
extern void _TDbTblDeleteSingleRow(TDbTable_t *pTable, int row);
extern void fn_8020A5A8(void);

int fn_802075F4(TDbStmt_80205754 *pStmt, unsigned int t)
{
    int err = 0;
    unsigned int key;
    TDbValue_t value;
    TDbValue_t result;
    TDbExpr_t *pSeek;
    unsigned int *pKey;

    if (pStmt->mIndexes[t] == 0) {
        pStmt->mRows[t] = 0;
    } else {
        if (pStmt->mSeekExprs[t] == 0) {
            pStmt->mNodes[t] = _TDbIdxTreeMoveRight(&pStmt->mIndexes[t]->mTree, 0);
        } else {
            pSeek = pStmt->mSeekExprs[t];
            pKey = &key;
            if (pSeek->mRight.mType == TDB_TYPE_COLUMN) {
                unsigned int table = pSeek->mRight.mValue.l >> 32;
                unsigned char column = pSeek->mRight.mValue.l;
                unsigned short row = pStmt->mRows[table];
                TDbTable_t *pTable = pStmt->mTables[table];

                if (row == 0xFFFF) {
                    *pKey = 0;
                } else {
                    unsigned char *pRow = pTable->mRows + pTable->mRowSize * row;

                    if (pTable->mColumns[column].mType > 1) {
                        _TDbDataGetBitData((unsigned int *)pRow, pTable->mColumns[column].mBitOffset,
                                    pTable->mColumns[column].mBitCount, pKey, pTable->mColumns[column].mType == 2);
                    } else {
                        *pKey = (unsigned int)(pRow + (pTable->mColumns[column].mBitOffset >> 3));
                    }
                }
            } else if ((unsigned int)(pSeek->mRight.mType - TDB_TYPE_EXPR_TRUNC) <= 2) {
                _TDbExprTest(pSeek->mRight.mValue.p, &result, pStmt->mTables, pStmt->mRows);
                *pKey = result.mValue.u;
            } else {
                *pKey = pSeek->mRight.mValue.u;
            }
            pStmt->mNodes[t] = _TDbIdxSeek(&pStmt->mIndexes[t]->mTree, pKey, pStmt->mSeekExprs[t]->mOp);
        }
        if (err == 0) {
            if (pStmt->mNodes[t] != 0) {
                pStmt->mRows[t] = pStmt->mNodes[t]->mRow;
                pStmt->mNodes[t] = _TDbIdxTreeMoveRight(&pStmt->mIndexes[t]->mTree, pStmt->mNodes[t]);
            } else {
                pStmt->mRows[t] = 0xFFFF;
                err = 0x17;
            }
        }
    }
    if (err == 0) {
        err = 0x17;
        do {
            if (pStmt->mIndexes[t] == 0) {
                if (pStmt->mRows[t] >= pStmt->mTables[t]->mRowCount) {
                    break;
                }
                if (_TDbRowIsDeleted(pStmt->mTables[t], pStmt->mRows[t])) {
                    pStmt->mRows[t]++;
                    continue;
                }
            }
            _TDbExprTest(pStmt->mTableExprs[t], &value, pStmt->mTables, pStmt->mRows);
            if (value.mValue.i != 0) {
                if (t + 1 < pStmt->mTableCount) {
                    err = fn_802075F4(pStmt, t + 1);
                } else {
                    err = 0;
                }
            } else {
                err = 0x17;
            }
            if (err != 0) {
                if (pStmt->mIndexes[t] == 0) {
                    pStmt->mRows[t]++;
                } else if (pStmt->mNodes[t] == 0) {
                    pStmt->mRows[t] = 0xFFFF;
                    break;
                } else {
                    pStmt->mRows[t] = pStmt->mNodes[t]->mRow;
                    pStmt->mNodes[t] = _TDbIdxTreeMoveRight(&pStmt->mIndexes[t]->mTree, pStmt->mNodes[t]);
                }
            }
        } while (err == 0x17);
    }
    if (err == 0x17 && t != 0 && pStmt->mJoinType[t] == 1) {
        pStmt->mRows[t] = 0xFFFF;
        if (t + 1 < pStmt->mTableCount) {
            err = fn_802075F4(pStmt, t + 1);
        } else {
            err = 0;
        }
    }
    return err;
}

int fn_80207988(TDbStmt_80205754 *pStmt, unsigned int t)
{
    int err = 0x17;
    TDbValue_t value;

    if (pStmt->mRows[t] != 0xFFFF) {
        do {
            if (pStmt->mIndexes[t] == 0) {
                for (;;) {
                    pStmt->mRows[t]++;
                    if (pStmt->mRows[t] >= pStmt->mTables[t]->mRowCount ||
                        !_TDbRowIsDeleted(pStmt->mTables[t], pStmt->mRows[t])) {
                        break;
                    }
                }
                if (pStmt->mRows[t] >= pStmt->mTables[t]->mRowCount) {
                    break;
                }
            } else {
                if (pStmt->mNodes[t] == 0) {
                    pStmt->mRows[t] = 0xFFFF;
                    break;
                }
                pStmt->mRows[t] = pStmt->mNodes[t]->mRow;
                pStmt->mNodes[t] = _TDbIdxTreeMoveRight(&pStmt->mIndexes[t]->mTree, pStmt->mNodes[t]);
            }
            if (pStmt->mSeekExprs[t] != 0) {
                _TDbExprTest(pStmt->mSeekExprs[t], &value, pStmt->mTables, pStmt->mRows);
                if (value.mValue.i == 0) {
                    err = 0x17;
                    break;
                }
                if (pStmt->mSeekExprs[t] != pStmt->mTableExprs[t]) {
                    _TDbExprTest(pStmt->mTableExprs[t], &value, pStmt->mTables, pStmt->mRows);
                }
            } else {
                _TDbExprTest(pStmt->mTableExprs[t], &value, pStmt->mTables, pStmt->mRows);
            }
            if (value.mValue.i != 0) {
                if (t + 1 < pStmt->mTableCount) {
                    err = fn_802075F4(pStmt, t + 1);
                } else {
                    err = 0;
                }
            }
        } while (err == 0x17);
    }
    if (err != 0 && t != 0) {
        err = fn_80207988(pStmt, t - 1);
    }
    return err;
}

int fn_80207B8C(void *pDb, TDbSQLTableRef_801FDC18 *pRefs, TDbExpr_t *pWhere, TDbStmt_80205754 *pStmt)
{
    int err = 0;
    unsigned int count;
    int info;
    TDbExpr_t *pAnd;

    pStmt->mTableCount = 0;
    pStmt->mWhere = 0;
    for (count = 0; pRefs[count].mId != -1; count++) {
        if (count > 9) {
            return 1;
        }
        err = fn_801F88F0(pDb, pRefs[count].mId, &info, &pStmt->mTables[count]);
        if (err != 0) {
            return err;
        }
        pStmt->mSeekExprs[count] = 0;
        if (count != 0) {
            pStmt->mJoinType[count] = pRefs[count].mJoinType;
        } else {
            pStmt->mJoinType[count] = 2;
        }
        err = _TDbExprPrepare(pRefs[count].mExpr, &pStmt->mTableExprs[count], pStmt->mTables, count + 1, 0);
        if (err != 0) {
            pStmt->mTableCount = count;
            break;
        }
    }
    pStmt->mTableCount = count;
    if (err == 0) {
        if (count == 1) {
            err = _TDbExprPrepare(pWhere, &pStmt->mWhere, pStmt->mTables, 1, 0);
            if (err == 0) {
                if (pStmt->mTableExprs[0] == 0) {
                    pStmt->mTableExprs[0] = pStmt->mWhere;
                    pStmt->mWhere = 0;
                } else if (pStmt->mWhere != 0) {
                    err = __TDbMemPoolAlloc(&lbl_803E9654, &pAnd);
                    if (err == 0) {
                        pAnd->mOp = 0x20009;
                        pAnd->mLeft.mType = 3;
                        pAnd->mLeft.mValue.p = pStmt->mTableExprs[0];
                        pAnd->mRight.mType = 3;
                        pAnd->mRight.mValue.p = pStmt->mWhere;
                        pStmt->mWhere = 0;
                        pStmt->mTableExprs[0] = pAnd;
                    }
                }
            }
        } else {
            err = fn_80205DB8(pStmt, pWhere, 0, 0);
        }
    }
    if (err != 0) {
        if (pStmt->mWhere != 0) {
            _TDbExprFree(pStmt->mWhere);
        }
        while (pStmt->mTableCount > 1) {
            pStmt->mTableCount--;
            _TDbExprFree(pStmt->mTableExprs[pStmt->mTableCount]);
        }
    }
    return err;
}

void fn_80207DB4(TDbStmt_80205754 *pStmt)
{
    unsigned int i;

    if (pStmt->mWhere != 0) {
        _TDbExprFree(pStmt->mWhere);
    }
    for (i = 0; i < pStmt->mTableCount; i++) {
        if (pStmt->mTableExprs[i] != 0) {
            _TDbExprFree(pStmt->mTableExprs[i]);
        }
    }
}

int fn_80207E24(TDbStmt_80205754 *pStmt, TDbIdxColumnDef_t *pCols, int create)
{
    int err = 0;
    int exact = 0;
    TDbIndex_t *pBest = 0;
    unsigned int best = -1;
    TDbExpr_t *pBestSeek = 0;
    unsigned int score;
    TDbIndex_t *pIndex;
    TDbExpr_t *pSeek;
    TDbIdxColumnDef_t *pCol;
    unsigned short row;

    pStmt->mJoinTables[0] = 0;
    pStmt->mSeekExprs[0] = 0;
    pStmt->mNodes[0] = 0;
    pStmt->mIndexes[0] = 0;
    if (pCols != 0) {
        for (pCol = pCols; pCol->mId != -1; pCol++) {
            pCol->mColumn = _TDbTblResolveColRef(pStmt->mTables[0], pCol->mId);
            if (pCol->mColumn == 0xFF) {
                return 9;
            }
        }
    }
    if (pStmt->mTableExprs[0] == 0 && pCols == 0) {
        pStmt->mRows[0] = 0;
    } else {
        for (pIndex = pStmt->mTables[0]->mIndexes; pIndex != 0; pIndex = pIndex->mNext) {
            score = fn_802067D4(pIndex, pStmt->mTableExprs[0], pCols, &pSeek);
            if (score < best) {
                pBest = pIndex;
                best = score;
                pBestSeek = pSeek;
                if (best == 0) {
                    exact = 1;
                    break;
                }
            }
        }
        if (exact || !create) {
            pStmt->mIndexes[0] = pBest;
            pStmt->mSeekExprs[0] = pBestSeek;
            pStmt->mRows[0] = 0;
        } else {
            pIndex = 0;
            err = fn_802069BC(pStmt->mTables[0], pCols, pStmt->mTableExprs[0], &pIndex);
            if (err == 0) {
                if (pBest == 0) {
                    for (row = 0; row < pStmt->mTables[0]->mRowCount; row++) {
                        if (!_TDbRowIsDeleted(pStmt->mTables[0], row)) {
                            err = _TDbIndexRowAdd(pIndex, row);
                            if (err != 0) {
                                break;
                            }
                        }
                    }
                } else {
                    pStmt->mRows[0] = 0;
                    pStmt->mIndexes[0] = pBest;
                    pStmt->mSeekExprs[0] = pBestSeek;
                    for (err = fn_802075F4(pStmt, 0); err == 0; err = fn_80207988(pStmt, 0)) {
                        err = _TDbIndexRowAdd(pIndex, pStmt->mRows[0]);
                        if (err != 0) {
                            break;
                        }
                    }
                    if (err == 0x17) {
                        err = 0;
                    }
                }
                if (err != 0) {
                    _TDbIndexDestroy(pIndex);
                    pStmt->mIndexes[0] = 0;
                    pStmt->mRows[0] = 0;
                    pStmt->mNodes[0] = 0;
                } else {
                    pStmt->mRows[0] = 0;
                    pStmt->mIndexes[0] = pIndex;
                    pStmt->mNodes[0] = _TDbIdxTreeMoveRight(&pIndex->mTree, 0);
                }
            }
        }
    }
    return err;
}

int fn_80208094(TDbStmt_80205754 *pStmt)
{
    unsigned int t;
    unsigned int best;
    unsigned int score;
    unsigned char column;
    unsigned int otherTable;
    TDbExpr_t *pSeek;
    TDbIndex_t *pIndex;

    for (t = 0; t < pStmt->mTableCount; t++) {
        best = -1;
        if (t != 0) {
            column = fn_80207448(pStmt->mTableExprs[t], t, &otherTable, &pSeek);
            pStmt->mJoinTables[t] = otherTable;
        } else {
            column = 0xFF;
        }
        pStmt->mIndexes[t] = 0;
        pStmt->mNodes[t] = 0;
        pStmt->mSeekExprs[t] = 0;
        pStmt->mRows[t] = 0;
        for (pIndex = pStmt->mTables[t]->mIndexes; pIndex != 0; pIndex = pIndex->mNext) {
            if (t == 0) {
                score = fn_802067D4(pIndex, pStmt->mTableExprs[0], 0, &pSeek);
                if (score < best) {
                    best = score;
                    pStmt->mIndexes[t] = pIndex;
                    pStmt->mSeekExprs[t] = pSeek;
                    if (best == 0) {
                        break;
                    }
                }
            } else {
                score = fn_80206708(pIndex, pStmt, t, column, pSeek);
                if (score < best) {
                    best = score;
                    pStmt->mIndexes[t] = pIndex;
                    if (best <= 0xFFFE) {
                        pStmt->mSeekExprs[t] = pSeek;
                    }
                    if (best == 0) {
                        break;
                    }
                }
            }
        }
    }
    return 0;
}

int fn_80208204(int dbId, TDbStmt_80205754 *pStmt, TDbResult_8020AD1C *pResult)
{
    int err = 0;
    TDbValue_t value;
    TDbIndex_t *pIndex;

    pResult->mCount = 0;
    if (pStmt->mTableCount == 1) {
        err = fn_80207E24(pStmt, 0, 0);
    } else {
        err = fn_80208094(pStmt);
    }
    if (err == 0) {
        if (pStmt->mTables[0]->mFlags & 1) {
            err = 0x1E;
        } else {
            pStmt->mTables[0]->mFlags |= 1;
        }
        if (err == 0) {
            err = fn_802075F4(pStmt, 0);
            if (err == 0) {
                do {
                    _TDbExprTest(pStmt->mWhere, &value, pStmt->mTables, pStmt->mRows);
                    if (value.mValue.i != 0) {
                        fn_8020651C(pStmt->mTables[0], pStmt->mRows[0]);
                        for (pIndex = pStmt->mTables[0]->mIndexes; pIndex != 0; pIndex = pIndex->mNext) {
                            err = _TDbIndexRowDelete(pIndex, pStmt->mRows[0]);
                            if (err != 0) {
                                break;
                            }
                        }
                        fn_80205C44(pStmt->mTables[0], pStmt->mRows[0]);
                        if (err != 0) {
                            break;
                        }
                        _TDbTblDeleteSingleRow(pStmt->mTables[0], pStmt->mRows[0]);
                        pResult->mCount++;
                    }
                    if (pStmt->mRows[0] < pStmt->mTables[0]->mRowCount &&
                        _TDbRowIsDeleted(pStmt->mTables[0], pStmt->mRows[0])) {
                        err = fn_80207988(pStmt, 0);
                    } else {
                        err = fn_80207988(pStmt, pStmt->mTableCount - 1);
                    }
                } while (err == 0);
            }
            pStmt->mTables[0]->mFlags &= ~1;
        }
        fn_8020A5A8();
    }
    if (pResult->mCount != 0) {
        if (err == 0x17) {
            err = 0;
        }
        if (pStmt->mTables[0]->mDeletedCount == pStmt->mTables[0]->mRowCount) {
            pStmt->mTables[0]->mDeletedCount = 0;
            pStmt->mTables[0]->mRowCount = 0;
            pStmt->mTables[0]->mFirstDeletedRow = 0xFFFF;
        }
    }
    pResult->mErr = err;
    return err;
}


extern TDbMemPool_t lbl_803E9670;
extern TDbHandler_8020A660 lbl_803E95DC[15];

int fn_8020840C(void *pDb, TDbSQLTableRef_801FDC18 *pRefs, TDbExpr_t *pWhere, TDbIdxColumnDef_t *pCols,
                int arg, TDbResult_8020AD1C *pResult)
{
    TDbValue_t value;
    TDbQuery_t *pQuery;
    TDbStmt_80205754 *pStmt;
    TDbIdxNode_t *pNode;
    int err;

    pResult->mCount = 0;
    err = __TDbMemPoolAlloc(&lbl_803E9670, &pQuery);
    if (err == 0) {
        err = __TDbMemPoolAlloc(&lbl_803E968C, &pStmt);
        if (err != 0) {
            __TDbMemPoolFree(&lbl_803E9670, pQuery);
        } else {
            err = fn_80207B8C(pDb, pRefs, pWhere, pStmt);
            if (err == 0) {
                pQuery->mCallback = 0;
                if (pStmt->mTableCount == 1) {
                    err = fn_80207E24(pStmt, pCols, 1);
                    if (err == 0) {
                        if (pCols != 0) {
                            TDbIdxColumnDef_t *pCol;

                            for (pCol = pCols; pCol->mId != -1; pCol++) {
                                pCol->mColumn = _TDbTblResolveColRef(pStmt->mTables[0], pCol->mId);
                                if (pCol->mColumn == 0xFF) {
                                    break;
                                }
                            }
                        }
                        pQuery->mDb = pStmt->mTables[0]->mDb;
                        if (pStmt->mIndexes[0] == 0) {
                            pQuery->mState = 0;
                            pQuery->mSource.mTable = pStmt->mTables[0];
                            *(unsigned short *)&pQuery->mCur = 0;
                            pResult->mCount = pQuery->mSource.mTable->mRowCount - pQuery->mSource.mTable->mDeletedCount;
                        } else {
                            pQuery->mSource.mIndex = pStmt->mIndexes[0];
                            pQuery->mState = pQuery->mSource.mIndex->mDestroyed ? 2 : 1;
                            pQuery->mSource.mIndex->mLocked++;
                            pQuery->mCur = _TDbIdxTreeMoveRight(&pQuery->mSource.mIndex->mTree, 0);
                            pResult->mCount = pQuery->mSource.mIndex->mCount;
                        }
                    }
                    fn_80207DB4(pStmt);
                    __TDbMemPoolFree(&lbl_803E968C, pStmt);
                } else {
                    err = fn_80208094(pStmt);
                    if (err == 0) {
                        pQuery->mDb = pStmt->mTables[0]->mDb;
                        err = fn_80206EB8(pStmt, pCols, &pQuery->mSource.mQIdx);
                        if (err == 0) {
                            pQuery->mSource.mQIdx->mCount = 0;
                            for (err = fn_802075F4(pStmt, 0); err == 0;
                                 err = fn_80207988(pStmt, pStmt->mTableCount - 1)) {
                                _TDbExprTest(pStmt->mWhere, &value, pStmt->mTables, pStmt->mRows);
                                if (value.mValue.i != 0) {
                                    pResult->mCount++;
                                    fn_80206C9C(pQuery->mSource.mQIdx, &pNode);
                                    if (err == 0) {
                                        pNode->mColor = 1;
                                        pNode->mParent = pNode->mChild[0] = pNode->mChild[1] = 0;
                                        _TDbIdxTreeInsert(&pQuery->mSource.mQIdx->mTree, pNode, 0);
                                        pQuery->mSource.mQIdx->mCount++;
                                    }
                                }
                            }
                            if (err == 0x17) {
                                err = 0;
                            } else if (err != 0) {
                                fn_80206E4C(pQuery->mSource.mQIdx);
                                pStmt = 0;
                            }
                        }
                        if (err != 0) {
                            fn_80207DB4(pStmt);
                        }
                        if (err == 0) {
                            pQuery->mState = 3;
                            pQuery->mCur = _TDbIdxTreeMoveRight(&pQuery->mSource.mQIdx->mTree, 0);
                        }
                    }
                }
            }
            if (err != 0) {
                __TDbMemPoolFree(&lbl_803E9670, pQuery);
            }
            if (err == 0) {
                pQuery->mCallbackArg = arg;
                pQuery->mNext = lbl_803EBE90;
                lbl_803EBE90 = pQuery;
            }
        }
    }
    if (pResult->mCount == 0) {
        err = 0x17;
    }
    pResult->mErr = err;
    return err;
}

int fn_802087D4(TDbQuery_t *pQuery)
{
    if (lbl_803EBE90 == pQuery) {
        lbl_803EBE90 = pQuery->mNext;
    } else {
        TDbQuery_t *pPrev = lbl_803EBE90;

        while (pPrev->mNext != pQuery) {
            pPrev = pPrev->mNext;
        }
        pPrev->mNext = pQuery->mNext;
    }
    if (pQuery->mState == 2) {
        if (--pQuery->mSource.mIndex->mLocked == 0) {
            _TDbIndexDestroy(pQuery->mSource.mIndex);
        }
    } else if (pQuery->mState == 1) {
        pQuery->mSource.mIndex->mLocked--;
    } else if (pQuery->mState == 3) {
        fn_80206E4C(pQuery->mSource.mQIdx);
    }
    __TDbMemPoolFree(&lbl_803E9670, pQuery);
    return 0;
}

int fn_802088A8(TDbQuery_t *pQuery, unsigned short *pCount)
{
    switch (pQuery->mState) {
    case 0:
        *pCount = pQuery->mSource.mTable->mRowCount - pQuery->mSource.mTable->mDeletedCount;
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

static inline int TDbRowNext_802088FC(TDbTable_t *pTable, unsigned short *pRow)
{
    unsigned short n = pTable->mRowCount;

    while (++*pRow < n) {
        if (!_TDbRowIsDeleted(pTable, *pRow)) {
            return 0;
        }
    }
    *pRow = 0xFFFF;
    return 0x15;
}

static inline int TDbRowPrev_802088FC(TDbTable_t *pTable, unsigned short *pRow)
{
    if (*pRow > pTable->mRowCount) {
        *pRow = pTable->mRowCount;
    }
    while (*pRow != 0) {
        --*pRow;
        if (!_TDbRowIsDeleted(pTable, *pRow)) {
            return 0;
        }
    }
    return 0x14;
}

int fn_802088FC(TDbQuery_t *pQuery, unsigned int mode, int count, TDbLitRef_t *pLits)
{
    TDbTable_t *pTable;
    TDbIndex_t *pIndex;
    TDbIdxNode_t *pNode;
    TDbQIdx_80205880 *pQIdx;
    TDbLitRef_t *pLit;
    unsigned short row;
    unsigned int column;
    unsigned int i;
    int err = 0;

    pNode = 0;
    pQIdx = 0;
    row = 0;
    if (pQuery == 0) {
        err = 0x11;
    } else {
        switch (pQuery->mState) {
        case 0:
            pTable = pQuery->mSource.mTable;
            if (pTable->mRowCount - pTable->mDeletedCount <= 0) {
                err = 0x15;
                break;
            }
            switch (mode) {
            case 0:
                row = *(unsigned short *)&pQuery->mCur;
                break;
            case 1:
                row = 0;
                if (_TDbRowIsDeleted(pTable, row)) {
                    err = TDbRowNext_802088FC(pTable, &row);
                }
                break;
            case 2:
                row = pTable->mRowCount - 1;
                if (_TDbRowIsDeleted(pTable, row)) {
                    err = TDbRowPrev_802088FC(pTable, &row);
                }
                break;
            }
            if (count > 0) {
                while (count-- > 0U && err == 0) { // FAKEMATCH: unsigned 0U bound (count > 0 here, so the same test) gives the target loop compare
                    err = TDbRowNext_802088FC(pTable, &row);
                }
            } else if (count < 0) {
                while (count++ < 0 && err == 0) {
                    err = TDbRowPrev_802088FC(pTable, &row);
                }
            } else if (pTable->mRowCount == 0) {
                row = 0xFFFF;
                err = 0x15;
            }
            *(unsigned short *)&pQuery->mCur = row;
            break;
        case 1:
        case 2:
            pIndex = pQuery->mSource.mIndex;
            if (pIndex->mCount == 0) {
                err = 0x15;
                break;
            }
            if (pQuery->mCur == 0 && (pQuery->mCur = _TDbIdxTreeMoveRight(&pIndex->mTree, 0)) == 0) {
                err = 0x15;
                pNode = 0;
            } else {
                switch (mode) {
                case 0:
                    pNode = pQuery->mCur;
                    break;
                case 1:
                    if (count < 0) {
                        err = 0x14;
                        break;
                    }
                    if (count <= pIndex->mCount / 2) {
                        pNode = _TDbIdxTreeMoveRight(&pIndex->mTree, 0);
                        break;
                    }
                    count -= pIndex->mCount - 1;
                case 2:
                    pNode = _TDbIdxTreeMoveLeft(&pIndex->mTree, 0);
                    if (count > 0) {
                        err = 0x15;
                        pNode = 0;
                    }
                    break;
                }
            }
            if (err != 0) {
                break;
            }
            if (count < 0) {
                while (count < 0 && pNode != 0) {
                    pNode = _TDbIdxTreeMoveLeft(&pQuery->mSource.mIndex->mTree, pNode);
                    count++;
                }
                if (pNode == 0) {
                    pQuery->mCur = _TDbIdxTreeMoveRight(&pIndex->mTree, 0);
                    err = 0x14;
                    break;
                }
            } else if (count > 0) {
                while (count > 0 && pNode != 0) {
                    pNode = _TDbIdxTreeMoveRight(&pQuery->mSource.mIndex->mTree, pNode);
                    count--;
                }
                if (pNode == 0) {
                    pQuery->mCur = 0;
                    err = 0x15;
                    break;
                }
            }
            pQuery->mCur = pNode;
            break;
        case 3:
            pQIdx = pQuery->mSource.mQIdx;
            if (pQIdx->mCount == 0) {
                err = 0x15;
                break;
            }
            if (pQuery->mCur == 0 && (pQuery->mCur = _TDbIdxTreeMoveRight(&pQIdx->mTree, 0)) == 0) {
                err = 0x15;
                pNode = 0;
            } else {
                switch (mode) {
                case 0:
                    pNode = pQuery->mCur;
                    break;
                case 1:
                    if (count < 0) {
                        err = 0x14;
                        break;
                    }
                    if (count <= pQIdx->mCount / 2) {
                        pNode = _TDbIdxTreeMoveRight(&pQIdx->mTree, 0);
                        break;
                    }
                    count -= pQIdx->mCount - 1;
                case 2:
                    pNode = _TDbIdxTreeMoveLeft(&pQIdx->mTree, 0);
                    if (count > 0) {
                        err = 0x15;
                        pNode = 0;
                    }
                    break;
                }
            }
            if (err != 0) {
                break;
            }
            if (count < 0) {
                while (count < 0 && pNode != 0) {
                    pNode = _TDbIdxTreeMoveLeft(&pQuery->mSource.mQIdx->mTree, pNode);
                    count++;
                }
                if (pNode == 0) {
                    pQuery->mCur = _TDbIdxTreeMoveRight(&pQIdx->mTree, 0);
                    err = 0x14;
                    break;
                }
            } else if (count > 0) {
                while (count > 0 && pNode != 0) {
                    pNode = _TDbIdxTreeMoveRight(&pQuery->mSource.mQIdx->mTree, pNode);
                    count--;
                }
                if (pNode == 0) {
                    pQuery->mCur = 0;
                    err = 0x15;
                    break;
                }
            }
            pQuery->mCur = pNode;
            break;
        }
    }
    if (err == 0 && pLits != 0) {
        if (pQuery->mState == 3) {
            for (pLit = pLits; pLit->mId != -1; pLit++) {
                for (i = 0; i < pQIdx->mStmt->mTableCount; i++) {
                    pTable = pQIdx->mStmt->mTables[i];
                    if (pLit->mTableId == 0 || pLit->mTableId == pTable->mId) {
                        pLit->mColumn = _TDbTblResolveColRef(pTable, pLit->mId);
                        if (pLit->mColumn != 0xFF) {
                            row = ((unsigned short *)pQuery->mCur->mRow)[i];
                            if (row == 0xFFFF) {
                                if (pTable->mColumns[pLit->mColumn].mType > 1) {
                                    pLit->mUnknown0 = 0;
                                } else {
                                    *(unsigned char *)pLit->mUnknown0 = 0;
                                }
                            } else {
                                TDbReadColumn_8020A3A0(pTable, &pTable->mColumns[pLit->mColumn],
                                                       pTable->mRows + row * pTable->mRowSize, pLit);
                                if (pTable->mColumns[pLit->mColumn].mType == 0) {
                                    ((unsigned char *)pLit->mUnknown0)[pTable->mColumns[pLit->mColumn].mBitCount >> 3] = 0;
                                }
                            }
                        } else {
                            err = 9;
                        }
                        break;
                    }
                }
                if (i >= pQIdx->mStmt->mTableCount) {
                    err = 7;
                }
                if (err != 0) {
                    break;
                }
            }
        } else {
            if (pQuery->mState == 0) {
                row = *(unsigned short *)&pQuery->mCur;
                pTable = pQuery->mSource.mTable;
            } else {
                row = pQuery->mCur->mRow;
                pTable = pQuery->mSource.mIndex->mTable;
            }
            for (pLit = pLits; pLit->mId != -1; pLit++) {
                column = _TDbTblResolveColRef(pTable, pLit->mId);
                if (column == 0xFF) {
                    err = 9;
                    break;
                }
                TDbReadColumn_8020A3A0(pTable, &pTable->mColumns[column], pTable->mRows + row * pTable->mRowSize, pLit);
                if (pTable->mColumns[column].mType == 0) {
                    ((unsigned char *)pLit->mUnknown0)[pTable->mColumns[column].mBitCount >> 3] = 0;
                }
            }
        }
    }
    return err;
}

int fn_802088A8(TDbQuery_t *pQuery, unsigned short *pCount);
TDbTable_t *_TDbTblFindTable(TDbDatabase_t *pDb, int id);
int _TDbTblCreate(TDbDatabase_t *pOwner, int tableId, TDbColumn_t *pDefs, int capacity, int flags);

static inline void TDbGetField_8020925C(TDbTable_t *pTable, TDbColumn_t *pColumn, unsigned char *pRow,
                                        unsigned int *pValue)
{
    int type = pColumn->mType;

    if ((unsigned int)(type - 13) <= 2) {
        _TDbBlobGetData(pTable, pColumn, pRow, (unsigned char *)*pValue);
    } else if ((unsigned int)type <= 1) {
        _TDbDataGetPtrData(pRow, pColumn->mBitOffset, pColumn->mBitCount, (unsigned char *)*pValue, pColumn->mBitCount >> 3);
    } else {
        _TDbDataGetBitData((unsigned int *)pRow, pColumn->mBitOffset, pColumn->mBitCount, pValue, type == 2);
    }
}

static inline void TDbSetField_8020925C(TDbColumn_t *pColumn, unsigned char *pRow, unsigned int *pValue)
{
    int type = pColumn->mType;

    if ((unsigned int)(type - 13) <= 2) {
        return;
    }
    if (type == 0) {
        _TDbDataSetPtrData(pRow, pColumn->mBitOffset, pColumn->mBitCount, (unsigned char *)*pValue, strlen((char *)*pValue));
    } else if (type == 1) {
        _TDbDataSetPtrData(pRow, pColumn->mBitOffset, pColumn->mBitCount, (unsigned char *)*pValue, pColumn->mBitCount >> 3);
    } else {
        _TDbDataSetBitData((unsigned int *)pRow, pColumn->mBitOffset, pColumn->mBitCount, pValue);
    }
}

int _TDbQryCreateTbl(TDbDatabase_t *pDb, int tableId, TDbQuery_t *pQuery, unsigned long long *pSpec,
                TDbResult_8020AD1C *pResult)
{
    TDbResult_8020AD1C result;
    unsigned short count;
    TDbColumn_t *pCols;
    unsigned int value;
    TDbTable_t *pTable = 0;
    TDbTable_t *pNew;
    TDbColumn_t *pDef;
    TDbColumn_t *pMap;
    unsigned long long *p;
    unsigned long long *q;
    TDbQIdx_80205880 *pQIdx;
    TDbIdxTree_t *pTree;
    TDbIdxNode_t *pNode;
    unsigned char *pSrcRow;
    unsigned char *pDstRow;
    unsigned char n;
    unsigned char i;
    unsigned int k;
    int tbl;
    int col;
    int bUnique;
    unsigned short srcRow;
    unsigned short row;

    if (pResult == 0) {
        pResult = &result;
    }
    memset(pResult, 0, sizeof(TDbResult_8020AD1C));
    for (n = 0; pSpec[n] != (unsigned long long)-1; n++) {
    }
    if (n == 0) {
        return 3;
    }
    _TDbMemNotify(3, (int)pDb->mId, tableId);
    pResult->mErr = TDbExtMemAlloc(pDb->mHeap, (n + 1) * sizeof(TDbColumn_t), &pCols);
    _TDbMemNotifyEnd();
    if (pResult->mErr == 0) {
        pDef = pCols;
        for (p = pSpec; *p != (unsigned long long)-1; p++) {
            tbl = *p >> 32;
            col = *p;
            pTable = 0;
            i = 0;
            bUnique = 1;
            for (q = pSpec; q != p; q++) {
                if ((int)*q == col) {
                    bUnique = 0;
                    break;
                }
                if ((int)(*q >> 32) == tbl) {
                    pTable = (TDbTable_t *)pCols[i].mBitOffset;
                }
                i++;
            }
            if (bUnique == 1) {
                if (pTable == 0) {
                    if (pQuery->mState == 3) {
                        pQIdx = pQuery->mSource.mQIdx;
                        pResult->mErr = 7;
                        for (k = 0; k < pQIdx->mStmt->mTableCount; k++) {
                            pTable = pQIdx->mStmt->mTables[k];
                            if (tbl == 0 || tbl == pTable->mId) {
                                pResult->mErr = 0;
                                break;
                            }
                        }
                        if (pResult->mErr == 7) {
                            /* FAKEMATCH: dead store (flow deletes it); it keeps jump.c from inverting
                               the test over the break, so the target's bne/b pair at 0x80209494 stays. */
                            bUnique = 0;
                            break;
                        }
                    } else {
                        if (pQuery->mState == 0) {
                            pTable = pQuery->mSource.mTable;
                        } else if (pQuery->mState == 1 || pQuery->mState == 2) {
                            pTable = pQuery->mSource.mIndex->mTable;
                        }
                        if (pTable == 0) {
                            pResult->mErr = 7;
                            break;
                        }
                    }
                }
                i = _TDbTblResolveColRef(pTable, col);
                if (i == 0xFF) {
                    pResult->mErr = 9;
                    break;
                }
                pMap = &pTable->mColumns[i];
                pDef->mType = pMap->mType;
                pDef->mBitCount = pMap->mBitCount;
                pDef->mUnknown8 = col;
                pDef->mBitOffset = (unsigned int)pTable;
                pDef++;
            }
        }
        pDef->mUnknown8 = -1;
        if (pResult->mErr == 0) {
            pResult->mErr = fn_802088A8(pQuery, &count);
            if (pResult->mErr == 0) {
                if (count == 0) {
                    pResult->mErr = _TDbTblCreate(pDb, tableId, pCols, 0, 0);
                    if (pResult->mErr == 0) {
                        pNew = _TDbTblFindTable(pDb, tableId);
                        pNew->mFlags &= ~2;
                        pResult->mErr = 0x17;
                    }
                } else {
                    pResult->mErr = _TDbTblCreate(pDb, tableId, pCols, count, 0);
                    if (pResult->mErr == 0) {
                        pNew = _TDbTblFindTable(pDb, tableId);
                        pNew->mFlags |= 1;
                        pNew->mFlags &= ~2;
                        memset(pNew->mRows, 0, pNew->mRowSize * count);
                        pResult->mCount = pNew->mRowCount = count;
                        switch (pQuery->mState) {
                        case 0:
                            row = 0;
                            srcRow = 0;
                            pDef = pNew->mColumns;
                            pTable = pQuery->mSource.mTable;
                            for (pMap = pCols, i = 0; i < pNew->mColumnCount; i++, pMap++, pDef++) {
                                pMap->mUnknown8 = _TDbTblResolveColRef(pTable, pDef->mUnknown8);
                            }
                            for (; srcRow < pTable->mRowCount; srcRow++) {
                                if (!_TDbRowIsDeleted(pTable, srcRow)) {
                                    pSrcRow = pTable->mRows + pTable->mRowSize * srcRow;
                                    pDstRow = pNew->mRows + pNew->mRowSize * row;
                                    for (i = 0, pDef = pNew->mColumns, pMap = pCols; i < pNew->mColumnCount;
                                         i++, pMap++, pDef++) {
                                        if (pDef->mType > 1) {
                                            value = 0;
                                            TDbGetField_8020925C(pTable, &pTable->mColumns[(unsigned char)pMap->mUnknown8], pSrcRow, &value);
                                            TDbSetField_8020925C(&pNew->mColumns[i], pDstRow, &value);
                                        } else {
                                            memcpy(pDstRow + (pDef->mBitOffset >> 3),
                                                   pSrcRow + (pTable->mColumns[(unsigned char)pMap->mUnknown8].mBitOffset >> 3),
                                                   pDef->mBitCount >> 3);
                                        }
                                    }
                                    row++;
                                }
                            }
                            break;
                        case 1:
                        case 2:
                            pTree = &pQuery->mSource.mIndex->mTree;
                            pTable = pQuery->mSource.mIndex->mTable;
                            pDef = pNew->mColumns;
                            for (pMap = pCols, i = 0; i < pNew->mColumnCount; i++, pMap++, pDef++) {
                                pMap->mUnknown8 = _TDbTblResolveColRef(pTable, pDef->mUnknown8);
                            }
                            row = 0;
                            for (pNode = _TDbIdxTreeMoveRight(pTree, 0); pNode != 0; pNode = _TDbIdxTreeMoveRight(pTree, pNode)) {
                                srcRow = pNode->mRow;
                                pSrcRow = pTable->mRows + pTable->mRowSize * srcRow;
                                pDstRow = pNew->mRows + pNew->mRowSize * row;
                                for (i = 0, pDef = pNew->mColumns, pMap = pCols; i < pNew->mColumnCount;
                                     i++, pMap++, pDef++) {
                                    if (pDef->mType > 1) {
                                        value = 0;
                                        TDbGetField_8020925C(pTable, &pTable->mColumns[(unsigned char)pMap->mUnknown8], pSrcRow, &value);
                                        TDbSetField_8020925C(&pNew->mColumns[i], pDstRow, &value);
                                    } else {
                                        memcpy(pDstRow + (pDef->mBitOffset >> 3),
                                               pSrcRow + (pTable->mColumns[(unsigned char)pMap->mUnknown8].mBitOffset >> 3),
                                               pDef->mBitCount >> 3);
                                    }
                                }
                                row++;
                            }
                            break;
                        case 3:
                            pQIdx = pQuery->mSource.mQIdx;
                            pTree = &pQIdx->mTree;
                            pDef = pNew->mColumns;
                            k = 0;
                            pNode = _TDbIdxTreeMoveRight(pTree, 0);
                            for (pMap = pCols, i = 0; i < pNew->mColumnCount; i++, pMap++, pDef++) {
                                p = pSpec;
                                do {
                                    if (pDef->mUnknown8 == (int)*p) {
                                        for (k = 0; k < pQIdx->mStmt->mTableCount; k++) {
                                            pTable = pQIdx->mStmt->mTables[k];
                                            if ((int)(*p >> 32) == pTable->mId) {
                                                break;
                                            }
                                        }
                                        break;
                                    }
                                    p++;
                                } while (*p != (unsigned long long)-1);
                                pMap->mUnknown8 = _TDbTblResolveColRef(pTable, pDef->mUnknown8);
                                pMap->mBitOffset = (unsigned int)pTable;
                                pMap->mBitCount = k;
                            }
                            for (row = 0; pNode != 0; pNode = _TDbIdxTreeMoveRight(pTree, pNode)) {
                                pDstRow = pNew->mRows + pNew->mRowSize * row;
                                for (i = 0, pDef = pNew->mColumns, pMap = pCols; i < pNew->mColumnCount;
                                     i++, pMap++, pDef++) {
                                    pTable = (TDbTable_t *)pMap->mBitOffset;
                                    k = (unsigned short)pMap->mBitCount;
                                    srcRow = ((unsigned short *)pNode->mRow)[k];
                                    if (srcRow == 0xFFFF) {
                                        value = 0;
                                        TDbSetField_8020925C(&pNew->mColumns[i], pDstRow, &value);
                                    } else {
                                        pSrcRow = pTable->mRows + pTable->mRowSize * srcRow;
                                        if (pDef->mType > 1) {
                                            value = 0;
                                            TDbGetField_8020925C(pTable, &pTable->mColumns[(unsigned char)pMap->mUnknown8], pSrcRow, &value);
                                            TDbSetField_8020925C(&pNew->mColumns[i], pDstRow, &value);
                                        } else {
                                            memcpy(pDstRow + (pDef->mBitOffset >> 3),
                                                   pSrcRow + (pTable->mColumns[(unsigned char)pMap->mUnknown8].mBitOffset >> 3),
                                                   pDef->mBitCount >> 3);
                                        }
                                    }
                                }
                                row++;
                            }
                            break;
                        }
                        pNew->mFlags &= ~1;
                    }
                }
            }
        }
        TDbExtMemFree(pDb->mHeap, pCols, (n + 1) * sizeof(TDbColumn_t));
    }
    return pResult->mErr;
}

int fn_80209E40(TDbStmt_80205754 *pStmt, TDbLitRef_t *pLit)
{
    for (; pLit->mId != -1; pLit++) {
        unsigned int j;

        if (pStmt->mTableCount == 1 || pLit->mTableId == 0) {
            j = 0;
        } else {
            int bFound = 0;

            for (j = 0; j < pStmt->mTableCount; j++) {
                if (pLit->mTableId == pStmt->mTables[j]->mId) {
                    bFound = 1;
                    break;
                }
            }
            if (bFound != 1) {
                return 7;
            }
        }
        pLit->mColumn = _TDbTblResolveColRef(pStmt->mTables[j], pLit->mId);
        if (pLit->mColumn == 0xFF) {
            return 9;
        }
    }
    return 0;
}

TDbIdxNode_t *_TDbIndexRowFindNode(TDbIndex_t *pIndex, int row);
int _TDbIndexRowUpdated(TDbIndex_t *pIndex, TDbIdxNode_t *pNode, unsigned short row);

int fn_80209F34(TDbStmt_80205754 *pStmt, TDbLitRef_t *pLits, unsigned int *pMask)
{
    TDbIdxNode_t *nodes[30];
    unsigned char state[10];
    unsigned int value;
    unsigned int n;
    TDbIndex_t *pIndex;
    TDbLitRef_t *pLit;
    unsigned int changed;
    unsigned int t;
    unsigned int k;
    unsigned int i;
    int bTouched;

    for (t = 0; t < pStmt->mTableCount; t++) {
        state[t] = 0;
        for (k = 0; k <= 3; k++) {
            if (pStmt->mTables[t]->mCallbacks[k] != 0) {
                _TDbTblGetFullRow(pStmt->mTables[t], pStmt->mRows[t], pStmt->mTables[t]->mUnknownC);
                state[t] = 1;
                break;
            }
        }
    }
    changed = 0;
    for (t = 0; t < pStmt->mTableCount; t++) {
        bTouched = 0;
        for (pLit = pLits, i = 0; pLit->mId != -1; pLit++, i++) {
            if (pStmt->mTableCount == 1 || pLit->mTableId == pStmt->mTables[t]->mId ||
                (pLit->mTableId == 0 && t == 0)) {
                if (pStmt->mRows[t] != 0xFFFF) {
                    TDbTable_t *pTable = pStmt->mTables[t];
                    unsigned char *pRow = pTable->mRows + pStmt->mRows[t] * pTable->mRowSize;

                    if (pTable->mColumns[pLit->mColumn].mType > 1) {
                        TDbReadColumn_8020A3A0(pTable, &pTable->mColumns[pLit->mColumn], pRow,
                                               (TDbLitRef_t *)&value);
                        if (value == pLit->mUnknown0) {
                            continue;
                        }
                    }
                    if (!bTouched) {
                        if (state[t] == 1) {
                            state[t] = 2;
                        }
                        bTouched = 1;
                        for (pIndex = pStmt->mTables[t]->mIndexes, n = 0; pIndex != 0; pIndex = pIndex->mNext, n++) {
                            nodes[n] = _TDbIndexRowFindNode(pIndex, pStmt->mRows[t]);
                        }
                    }
                    TDbWriteColumn_8020BFA4(&pStmt->mTables[t]->mColumns[pLit->mColumn], pRow, pLit);
                    pMask[i >> 5] |= 1 << (i & 31);
                    changed++;
                }
            }
        }
        if (bTouched) {
            for (pIndex = pStmt->mTables[t]->mIndexes, n = 0; pIndex != 0; pIndex = pIndex->mNext, n++) {
                _TDbIndexRowUpdated(pIndex, nodes[n], pStmt->mRows[t]);
            }
        }
    }
    if (changed != 0) {
        for (t = 0; t < pStmt->mTableCount; t++) {
            if (state[t] == 2) {
                _TDbTblGetFullRow(pStmt->mTables[t], pStmt->mRows[t], pStmt->mTables[t]->mUnknown10);
                for (k = 0; k <= 3; k++) {
                    if (pStmt->mTables[t]->mCallbacks[k] != 0) {
                        pStmt->mTables[t]->mCallbacks[k]((int)pStmt->mTables[t]->mDb->mId,
                                                         pStmt->mTables[t]->mId, 2,
                                                         pStmt->mTables[t]->mUnknownC,
                                                         pStmt->mTables[t]->mUnknown10);
                    }
                }
            }
        }
    }
    return changed != 0;
}

void fn_8020A3A0(TDbStmt_80205754 *pStmt, TDbLitRef_t *pLit)
{
    for (; pLit->mId != -1; pLit++) {
        unsigned int j;
        int row;

        if (pStmt->mTableCount == 1 || pLit->mTableId == 0) {
            j = 0;
        } else {
            for (j = 0; j <= pStmt->mTableCount; j++) {
                if (pLit->mTableId == pStmt->mTables[j]->mId) {
                    break;
                }
            }
        }
        row = pStmt->mRows[j];
        if (row != 0xFFFF) {
            TDbTable_t *pTable = pStmt->mTables[j];

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
    TDbQuery_t *pQuery;

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
    TDbQuery_t *pQuery;

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

int fn_8020A660(int unused, TDbStmt_80205754 *pStmt, int key, TDbLitRef_t *pLits, int user, TDbResult_8020AD1C *pResult)
{
    unsigned char saved[0x100];
    TDbValue_t value;
    unsigned int mask[8];
    unsigned char bEmit;
    TDbHandlerFn_8020A660 pFn = 0; // FAKEMATCH: dead initializer (pFn is always set before use) that gives the target register allocation
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

int _TDbTblRowGrow(TDbTable_t *pTable, int count);

int fn_8020A908(int unused, TDbStmt_80205754 *pStmt, TDbLitRef_t *pLits, TDbTable_t *pTable,
                TDbResult_8020AD1C *pResult)
{
    unsigned char map[0x100];
    TDbValue_t value;
    unsigned int i;
    int record;
    int bReused;
    int err = 0;
    TDbIndex_t *pIndex;

    pResult->mCount = err;
    if (pTable->mFlags & 1) {
        pResult->mErr = 0x1E;
        return 0x1E;
    }
    if (pTable->mFlags & 0x60) {
        pResult->mErr = 0x31;
        return 0x31;
    }
    fn_8020A540();
    for (i = 0; pLits[i].mId != -1; i++) {
        map[i] = _TDbTblResolveColRef(pTable, pLits[i].mId);
    }
    if (pStmt->mTableCount == 1) {
        err = fn_80207E24(pStmt, 0, 0);
    } else {
        err = fn_80208094(pStmt);
    }
    if (err == 0) {
        err = fn_80209E40(pStmt, pLits);
        pResult->mCount = 0;
        if (err == 0) {
            for (err = fn_802075F4(pStmt, 0); err == 0; err = fn_80207988(pStmt, pStmt->mTableCount - 1)) {
                _TDbExprTest(pStmt->mWhere, &value, pStmt->mTables, pStmt->mRows);
                if (value.mValue.i != 0) {
                    fn_8020A3A0(pStmt, pLits);
                    if (pTable->mCapacity == 0 && (pTable->mFlags & 8)) {
                        _TDbTblRowGrow(pTable, pTable->mNominalCapacity);
                    }
                    bReused = 0;
                    if (pTable->mDeletedCount != 0) {
                        record = pTable->mFirstDeletedRow;
                        bReused = 1;
                        pTable->mDeletedCount--;
                        pTable->mFirstDeletedRow = *(unsigned short *)(pTable->mRows + pTable->mRowSize * record);
                    } else if (pTable->mRowCount < pTable->mCapacity) {
                        record = pTable->mRowCount++;
                    } else {
                        err = 0x13;
                        break;
                    }
                    if (err == 0) {
                        memset(pTable->mRows + pTable->mRowSize * record, 0, pTable->mRowSize);
                        for (i = 0; pLits[i].mId != -1; i++) {
                            if (map[i] != 0xFF) {
                                TDbWriteColumn_8020BFA4(&pTable->mColumns[map[i]],
                                                        pTable->mRows + pTable->mRowSize * record, &pLits[i]);
                            }
                        }
                        for (pIndex = pTable->mIndexes; pIndex != 0; pIndex = pIndex->mNext) {
                            err = _TDbIndexRowAdd(pIndex, record);
                            if (err != 0) {
                                for (pIndex = pTable->mIndexes; pIndex != 0; pIndex = pIndex->mNext) {
                                    _TDbIndexRowDelete(pIndex, record);
                                }
                                break;
                            }
                        }
                        if (err == 0) {
                            unsigned char *pFlags = pTable->mRows + pTable->mRowSize * record;

                            pFlags += pTable->mDeletedBit >> 3;
                            *pFlags &= ~(1 << (7 - (pTable->mDeletedBit & 7)));
                            pTable->mFlags |= 4;
                            pResult->mCount++;
                            _TDbTblCallInsertTriggers(pTable, record);
                        } else if (bReused) {
                            unsigned char *pFlags = pTable->mRows + pTable->mRowSize * record;

                            pFlags += pTable->mDeletedBit >> 3;
                            *pFlags |= 1 << (7 - (pTable->mDeletedBit & 7));
                            *(unsigned short *)(pTable->mRows + pTable->mRowSize * record) = pTable->mFirstDeletedRow;
                            pTable->mFirstDeletedRow = record;
                            pTable->mDeletedCount++;
                        } else {
                            pTable->mRowCount--;
                        }
                    }
                }
            }
        }
        if (pResult->mCount != 0) {
            if (err == 0x17) {
                err = 0;
            }
            fn_8020A5A8();
        }
    }
    pResult->mErr = err;
    return err;
}

int fn_8020AD1C(int unused, TDbStmt_80205754 *pStmt, TDbLitRef_t *pLits, int bFirstOnly, TDbResult_8020AD1C *pResult)
{
    unsigned int mask[8];
    TDbValue_t value;
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

int fn_8020AE88(int unused, TDbStmt_80205754 *pStmt, unsigned long long *pKeys, TDbExpr_t **ppExprs,
                TDbResult_8020AD1C *pResult)
{
    TDbValue_t value;
    TDbLitRef_t lits[33];
    unsigned int mask[8];
    unsigned int count;
    unsigned int i;
    int err = 0;

    memset(mask, 0, sizeof(mask));
    pResult->mCount = err;
    for (count = 0; (int)pKeys[count] != -1; count++) {
        lits[count].mId = (int)pKeys[count];
        lits[count].mTableId = pKeys[count] >> 32;
    }
    lits[count].mId = -1;
    fn_8020A540();
    if (pStmt->mTableCount == 1) {
        err = fn_80207E24(pStmt, 0, 0);
    } else {
        err = fn_80208094(pStmt);
    }
    if (err == 0) {
        pResult->mCount = err;
        err = fn_80209E40(pStmt, lits);
        if (err == 0) {
            err = fn_80205B88(pStmt);
            if (err == 0) {
                for (err = fn_802075F4(pStmt, 0); err == 0; err = fn_80207988(pStmt, pStmt->mTableCount - 1)) {
                    _TDbExprTest(pStmt->mWhere, &value, pStmt->mTables, pStmt->mRows);
                    if (value.mValue.i != 0) {
                        pResult->mCount++;
                        for (i = 0; i < count; i++) {
                            _TDbExprTest(ppExprs[i], &value, pStmt->mTables, pStmt->mRows);
                            lits[i].mUnknown0 = value.mValue.i;
                        }
                        fn_80209F34(pStmt, lits, mask);
                    }
                }
                fn_80205754(pStmt, lits, mask);
                fn_80205C08(pStmt);
            }
        }
        if (pResult->mCount != 0 && err == 0x17) {
            err = 0;
        }
        fn_8020A5A8();
    }
    pResult->mErr = err;
    return err;
}

typedef union TDbStatValue_8020B094 {
    int i;
    unsigned int u;
    float f;
    char *s;
} TDbStatValue_8020B094;

typedef struct TDbColStats_8020B094 {
    unsigned int mCount;
    TDbStatValue_8020B094 mMax;
    TDbStatValue_8020B094 mMin;
    TDbStatValue_8020B094 mSum;
} TDbColStats_8020B094;


int fn_8020B094(void *pDb, TDbSQLTableRef_801FDC18 *pRefs, TDbExpr_t *pWhere, int unused,
                unsigned long long column, TDbColStats_8020B094 *pStats, TDbResult_8020AD1C *pResult)
{
    TDbValue_t result;
    TDbStmt_80205754 stmt;
    TDbStatValue_8020B094 value;
    TDbColumn_t *pColumn = 0;
    unsigned int t = 0;
    unsigned char col;
    int bHave;
    int err = 0;

    pResult->mCount = err;
    pStats->mCount = err;
    err = fn_80207B8C(pDb, pRefs, pWhere, &stmt);
    if (err == 0) {
        if (pRefs[1].mId == -1) {
            err = fn_80207E24(&stmt, 0, 0);
        } else {
            err = fn_80208094(&stmt);
        }
        if (err == 0) {
            if ((column >> 32) != 0 && stmt.mTableCount != 1) {
                for (; t < stmt.mTableCount; t++) {
                    if ((unsigned int)(column >> 32) == stmt.mTables[t]->mId) {
                        break;
                    }
                }
                if (t >= stmt.mTableCount) {
                    err = 7;
                }
            }
            if (err == 0) {
                col = _TDbTblResolveColRef(stmt.mTables[t], column);
                if (col == 0xFF) {
                    err = 9;
                } else {
                    pColumn = &stmt.mTables[t]->mColumns[col];
                }
                if (err == 0) {
                    pStats->mSum.i = 0;
                    pStats->mMin.i = 0;
                    pStats->mMax.i = 0;
                    bHave = 0;
                    for (err = fn_802075F4(&stmt, 0); err == 0; err = fn_80207988(&stmt, stmt.mTableCount - 1)) {
                        _TDbExprTest(stmt.mWhere, &result, stmt.mTables, stmt.mRows);
                        if (result.mValue.i == 0) {
                            continue;
                        }
                        if (stmt.mRows[t] != 0xFFFF) {
                            unsigned char *pRow = stmt.mTables[t]->mRows + stmt.mTables[t]->mRowSize * stmt.mRows[t];

                            if ((unsigned int)pColumn->mType <= 1) {
                                value.s = (char *)pRow + (pColumn->mBitOffset >> 3);
                            } else if (pColumn->mType == TDB_TYPE_INT) {
                                _TDbDataGetBitData((unsigned int *)pRow, pColumn->mBitOffset, pColumn->mBitCount, &value.u, 1);
                            } else {
                                _TDbDataGetBitData((unsigned int *)pRow, pColumn->mBitOffset, pColumn->mBitCount, &value.u, 0);
                            }
                        } else {
                            value.s = 0;
                        }
                        switch (pColumn->mType) {
                        case TDB_TYPE_STRING:
                            if (value.s != 0) {
                                if (!bHave || lbl_803EBE74(value.s, pStats->mMin.s, pColumn->mBitCount >> 3) < 0) {
                                    strncpy(pStats->mMin.s, value.s, pColumn->mBitCount >> 3);
                                    pStats->mMin.s[pColumn->mBitCount >> 3] = 0;
                                }
                                if (!bHave || lbl_803EBE74(value.s, pStats->mMax.s, pColumn->mBitCount >> 3) > 0) {
                                    bHave = 1;
                                    strncpy(pStats->mMax.s, value.s, pColumn->mBitCount >> 3);
                                    pStats->mMin.s[pColumn->mBitCount >> 3] = 0;
                                }
                            }
                            break;
                        case TDB_TYPE_BINARY:
                            if (value.s != 0) {
                                if (!bHave || memcmp(value.s, pStats->mMin.s, pColumn->mBitCount >> 3) < 0) {
                                    memcpy(pStats->mMin.s, value.s, pColumn->mBitCount >> 3);
                                }
                                if (!bHave || memcmp(value.s, pStats->mMax.s, pColumn->mBitCount >> 3) > 0) {
                                    bHave = 1;
                                    memcpy(pStats->mMax.s, value.s, pColumn->mBitCount >> 3);
                                }
                            }
                            break;
                        case TDB_TYPE_UINT:
                            if (!bHave || value.u < pStats->mMin.u) {
                                pStats->mMin.u = value.u;
                            }
                            if (!bHave || value.u > pStats->mMax.u) {
                                bHave = 1;
                                pStats->mMax.u = value.u;
                            }
                            pStats->mSum.u += value.u;
                            break;
                        case TDB_TYPE_INT:
                            if (!bHave || value.i < pStats->mMin.i) {
                                pStats->mMin.i = value.i;
                            }
                            if (!bHave || value.i > pStats->mMax.i) {
                                bHave = 1;
                                pStats->mMax.i = value.i;
                            }
                            pStats->mSum.i += value.i;
                            break;
                        case TDB_TYPE_FLOAT:
                            if (!bHave || value.f < pStats->mMin.f) {
                                pStats->mMin.f = value.f;
                            }
                            if (!bHave || value.f > pStats->mMax.f) {
                                bHave = 1;
                                pStats->mMax.f = value.f;
                            }
                            pStats->mSum.f += value.f;
                            break;
                        }
                        pResult->mCount++;
                        pStats->mCount++;
                    }
                }
            }
        }
        fn_80207DB4(&stmt);
    }
    if (pResult->mCount != 0 && err == 0x17) {
        err = 0;
    }
    pResult->mErr = err;
    return err;
}

#endif
