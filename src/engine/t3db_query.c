#include <string.h>
#include "engine/t3db.h"

int fn_80205880(TDbTable_801FAA00 *pTable, unsigned char column, TDbQIdx_80205880 *pQIdx);
int fn_80205A10(TDbQIdx_80205880 *pQIdx, TDbIdxNode_80201EC8 **ppCur);

int fn_80205754(TDbStmt_80205754 *pStmt, TDbLitRef_80205754 *pLits, unsigned int *pMask)
{
    TDbQuery_802032D8 *pQuery;
    unsigned int i;
    unsigned int lit;

    for (pQuery = lbl_803EBE90; pQuery != 0; pQuery = pQuery->mNext) {
        if (pQuery->mState != 3) {
            continue;
        }
        for (i = 0; i < pStmt->mTableCount; i++) {
            for (lit = 0; pLits[lit].mId != -1; lit++) {
                if (pStmt->mTableCount == 1 || pLits[lit].mTableId == pStmt->mTables[i]->mUnknown1C ||
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

int fn_80205880(TDbTable_801FAA00 *pTable, unsigned char column, TDbQIdx_80205880 *pQIdx)
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
                    used = fn_8020567C(pQIdx->mStmt->mWhere, (unsigned long long)table << 32 | column);
                }
                if (!used) {
                    for (i = table; i < pQIdx->mStmt->mTableCount; i++) {
                        if (pQIdx->mStmt->mTableExprs[i] != 0) {
                            used = fn_8020567C(pQIdx->mStmt->mTableExprs[i],
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

int fn_80205A10(TDbQIdx_80205880 *pQIdx, TDbIdxNode_80201EC8 **ppCur)
{
    unsigned int key[10];
    TDbValue_801FDF28 result;
    TDbIdxNode_80201EC8 *pNode;
    TDbIdxTree_80201EC8 *pTree;
    int err;

    if (*ppCur != 0) {
        memcpy(key, (*ppCur)->mKey, pQIdx->mTree.mPartCount * 4);
    } else {
        memset(key, 0, sizeof(key));
    }
    err = fn_802035C8(&pQIdx->mPool);
    if (err == 0) {
        fn_802035C8(&pQIdx->mKeyPool);
        pQIdx->mCount = 0;
        pQIdx->mTree.mRoot = 0;
        err = fn_80208094(pQIdx->mStmt);
        if (err == 0) {
            pTree = &pQIdx->mTree;
            err = fn_802075F4(pQIdx->mStmt, 0);
            while (err == 0) {
                TDbEvaluateExpression_802047EC(pQIdx->mStmt->mWhere, &result, pQIdx->mStmt->mTables, pQIdx->mStmt->mRows);
                if (result.mValue.i != 0) {
                    fn_80206C9C(pQIdx, &pNode);
                    pNode->mColor = 1;
                    pNode->mParent = pNode->mChild[0] = pNode->mChild[1] = 0;
                    fn_802024B0(pTree, pNode, 0);
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
            *ppCur = fn_80201EC8(pTree, key);
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

void fn_80205C44(TDbTable_801FAA00 *pTable, int row)
{
    TDbQuery_802032D8 *pQuery;
    TDbIdxNode_80201EC8 *pNode;
    TDbIdxNode_80201EC8 *pNext;
    unsigned int found;

    for (pQuery = lbl_803EBE90; pQuery != 0; pQuery = pQuery->mNext) {
        found = 0;
        if (pQuery->mState == 3) {
            found = TDbStmtTableSlot_80205C44(pQuery->mSource.mQIdx->mStmt, pTable);
        }
        if (found != 0) {
            pQuery->mSource.mQIdx->mDirty = 1;
            found--;
            pNode = fn_80202200(&pQuery->mSource.mQIdx->mTree, 0);
            while (pNode != 0) {
                pNext = fn_80202200(&pQuery->mSource.mQIdx->mTree, pNode);
                if (row == ((unsigned short *)pNode->mRow)[found]) {
                    if (pNode == pQuery->mCur) {
                        pQuery->mCur = fn_80202298(&pQuery->mSource.mQIdx->mTree, pNode);
                        if (pQuery->mCur == 0) {
                            pQuery->mCur = fn_80202200(&pQuery->mSource.mQIdx->mTree, pNode);
                        }
                    }
                    fn_802025C4(&pQuery->mSource.mQIdx->mTree, pNode);
                    fn_80203744(&pQuery->mSource.mQIdx->mPool, pNode);
                    pQuery->mSource.mQIdx->mDirty = 1;
                    pQuery->mSource.mQIdx->mCount--;
                }
                pNode = pNext;
            }
        }
    }
}
