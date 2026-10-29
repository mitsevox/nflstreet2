#include <string.h>
#include "engine/t3db.h"

enum {
    TDB_OP_LT = 0x10001,
    TDB_OP_LE = 0x10002,
    TDB_OP_EQ = 0x10003,
    TDB_OP_GT = 0x10004,
    TDB_OP_GE = 0x10005
};


int fn_80202708(TDbIdxTree_80201EC8 *pTree, unsigned int *pKeyA, unsigned int *pKeyB, unsigned int count);

TDbIdxNode_80201EC8 *fn_80201EC8(TDbIdxTree_80201EC8 *pTree, unsigned int *pKey)
{
    TDbIdxNode_80201EC8 *pNode;
    TDbIdxNode_80201EC8 *pNext;
    int cmp;
    unsigned int dir;

    if (pTree->mRoot == 0) {
        return 0;
    }
    pNode = pTree->mRoot;
    cmp = fn_80202708(pTree, pKey, pNode->mKey, 1);
    dir = (unsigned int)cmp >> 31;
    while (cmp != 0 && pNode->mChild[dir] != 0) {
        pNode = pNode->mChild[dir];
        cmp = fn_80202708(pTree, pKey, pNode->mKey, 1);
        dir = (unsigned int)cmp >> 31;
    }
    if (cmp == 0) {
        pNext = fn_80202298(pTree, pNode);
        while (pNext != 0 && fn_80202708(pTree, pKey, pNext->mKey, 1) == 0) {
            pNode = pNext;
            pNext = fn_80202298(pTree, pNode);
        }
    }
    return pNode;
}

TDbIdxNode_80201EC8 *fn_80201F9C(TDbIdxTree_80201EC8 *pTree, unsigned int *pKey, unsigned int mode)
{
    TDbIdxNode_80201EC8 *pNode;
    TDbIdxNode_80201EC8 *pNext;
    int cmp;
    unsigned int dir;

    if (pTree->mRoot == 0) {
        return 0;
    }
    if ((pTree->mParts[0].mAscending && mode == TDB_OP_LT) ||
        (!pTree->mParts[0].mAscending && mode == TDB_OP_GT)) {
        pNode = fn_80202200(pTree, 0);
        if (fn_80202708(pTree, pKey, pNode->mKey, 1) != 1) {
            pNode = 0;
        }
    } else if ((pTree->mParts[0].mAscending && mode == TDB_OP_LE) ||
               (!pTree->mParts[0].mAscending && mode == TDB_OP_GE)) {
        pNode = fn_80202200(pTree, 0);
        if (fn_80202708(pTree, pKey, pNode->mKey, 1) == -1) {
            pNode = 0;
        }
    } else {
        pNode = pTree->mRoot;
        cmp = fn_80202708(pTree, pKey, pNode->mKey, 1);
        dir = (unsigned int)cmp >> 31;
        while (cmp != 0 && pNode->mChild[dir] != 0) {
            pNode = pNode->mChild[dir];
            cmp = fn_80202708(pTree, pKey, pNode->mKey, 1);
            dir = (unsigned int)cmp >> 31;
        }
        switch (mode) {
        case TDB_OP_LE:
        case TDB_OP_GE:
            if (cmp != 0) {
                while (pNode != 0 && fn_80202708(pTree, pKey, pNode->mKey, 1) > 0) {
                    pNode = fn_80202200(pTree, pNode);
                }
                break;
            }
        case TDB_OP_EQ:
            if (cmp != 0) {
                pNode = 0;
                break;
            }
            pNext = fn_80202298(pTree, pNode);
            while (pNext != 0 && fn_80202708(pTree, pKey, pNext->mKey, 1) == 0) {
                pNode = pNext;
                pNext = fn_80202298(pTree, pNode);
            }
            break;
        case TDB_OP_LT:
        case TDB_OP_GT:
            while (pNode != 0 && fn_80202708(pTree, pKey, pNode->mKey, 1) >= 0) {
                pNode = fn_80202200(pTree, pNode);
            }
            break;
        }
    }
    return pNode;
}

TDbIdxNode_80201EC8 *fn_80202200(TDbIdxTree_80201EC8 *pTree, TDbIdxNode_80201EC8 *pNode)
{
    TDbIdxNode_80201EC8 *pParent;
    int state;

    if (pNode == 0) {
        pNode = pTree->mRoot;
        state = 1;
        if (pNode == 0) {
            return 0;
        }
    } else {
        state = 0;
    }
    for (;;) {
        if (state == 2) {
            pParent = pNode->mParent;
            if (pParent == 0) {
                return 0;
            }
            if (pParent->mChild[0] != pNode) {
                return pParent;
            }
            pNode = pParent;
        }
        if (state == 0) {
            if (pNode->mChild[0] == 0) {
                state = 2;
            } else {
                pNode = pNode->mChild[0];
                state = 1;
            }
        }
        while (state == 1) {
            if (pNode->mChild[1] == 0) {
                return pNode;
            }
            pNode = pNode->mChild[1];
        }
    }
}

TDbIdxNode_80201EC8 *fn_80202298(TDbIdxTree_80201EC8 *pTree, TDbIdxNode_80201EC8 *pNode)
{
    TDbIdxNode_80201EC8 *pParent;
    int state;

    if (pNode == 0) {
        pNode = pTree->mRoot;
        state = 0;
    } else {
        state = 1;
    }
    for (;;) {
        if (state == 2) {
            pParent = pNode->mParent;
            if (pParent == 0) {
                return 0;
            }
            if (pParent->mChild[1] != pNode) {
                return pParent;
            }
            pNode = pParent;
        }
        if (state == 1) {
            if (pNode->mChild[1] == 0) {
                state = 2;
            } else {
                pNode = pNode->mChild[1];
                state = 0;
            }
        }
        while (state == 0) {
            if (pNode->mChild[0] == 0) {
                return pNode;
            }
            pNode = pNode->mChild[0];
        }
    }
}

static void fn_8020232C(TDbIdxTree_80201EC8 *pTree, TDbIdxNode_80201EC8 *pNode, int dir)
{
    int other = !dir;
    TDbIdxNode_80201EC8 *pPivot = pNode->mChild[other];

    pNode->mChild[other] = pPivot->mChild[dir];
    if (pPivot->mChild[dir] != 0) {
        pPivot->mChild[dir]->mParent = pNode;
    }
    if (pPivot != 0) {
        pPivot->mParent = pNode->mParent;
    }
    if (pNode->mParent != 0) {
        if (pNode == pNode->mParent->mChild[dir]) {
            pNode->mParent->mChild[dir] = pPivot;
        } else {
            pNode->mParent->mChild[other] = pPivot;
        }
    } else {
        pTree->mRoot = pPivot;
    }
    pPivot->mChild[dir] = pNode;
    if (pNode != 0) {
        pNode->mParent = pPivot;
    }
}

static void fn_802023AC(TDbIdxTree_80201EC8 *pTree, TDbIdxNode_80201EC8 *pNode)
{
    TDbIdxNode_80201EC8 *pParent;
    TDbIdxNode_80201EC8 *pGrand;
    TDbIdxNode_80201EC8 *pUncle;
    int dir;
    int side;

    while (pNode != pTree->mRoot && pNode->mParent->mColor == 1) {
        pParent = pNode->mParent;
        pGrand = pParent->mParent;
        dir = pParent == pGrand->mChild[1];
        side = !dir;
        pUncle = pGrand->mChild[side];
        if (pUncle != 0 && pUncle->mColor == 1) {
            pParent->mColor = 0;
            pUncle->mColor = 0;
            pGrand->mColor = 1;
            pNode = pGrand;
        } else {
            if (pNode == pParent->mChild[side]) {
                pNode = pParent;
                fn_8020232C(pTree, pNode, dir);
            }
            pParent = pNode->mParent;
            pGrand = pParent->mParent;
            pParent->mColor = 0;
            pGrand->mColor = 1;
            fn_8020232C(pTree, pGrand, side);
        }
    }
    pTree->mRoot->mColor = 0;
}

int fn_802024B0(TDbIdxTree_80201EC8 *pTree, TDbIdxNode_80201EC8 *pNode, TDbIdxNode_80201EC8 *pStart)
{
    TDbIdxNode_80201EC8 *pParent;
    int cmp;
    int dir;

    if (pStart == 0) {
        if (pTree->mRoot == 0) {
            pNode->mParent = 0;
            pTree->mRoot = pNode;
            pNode->mColor = 0;
            return 0;
        }
        pParent = pTree->mRoot;
    } else {
        pParent = pStart;
    }
    cmp = fn_80202708(pTree, pNode->mKey, pParent->mKey, pTree->mPartCount);
    dir = cmp < 0;
    while (pParent->mChild[dir] != 0) {
        pParent = pParent->mChild[dir];
        cmp = fn_80202708(pTree, pNode->mKey, pParent->mKey, pTree->mPartCount);
        if (!pTree->mAllowDuplicates && cmp == 0) {
            return 0x12;
        }
        dir = cmp == 0 ? pStart == 0 : cmp < 0;
    }
    pParent->mChild[dir] = pNode;
    pNode->mParent = pParent;
    fn_802023AC(pTree, pNode);
    return 0;
}

TDbIdxNode_80201EC8 *fn_802025C4(TDbIdxTree_80201EC8 *pTree, TDbIdxNode_80201EC8 *pNode)
{
    TDbIdxNode_80201EC8 **ppLink;
    TDbIdxNode_80201EC8 *pPrev;
    TDbIdxNode_80201EC8 *pLast;

    if (pNode->mParent != 0) {
        int dir = pNode->mParent->mChild[1] == pNode;
        ppLink = &pNode->mParent->mChild[dir];
    } else {
        ppLink = &pTree->mRoot;
    }
    if (pNode->mChild[0] == 0) {
        if ((*ppLink = pNode->mChild[1]) != 0) {
            (*ppLink)->mColor = pNode->mColor;
            (*ppLink)->mParent = pNode->mParent;
        }
    } else if (pNode->mChild[0]->mChild[1] == 0) {
        *ppLink = pNode->mChild[0];
        (*ppLink)->mColor = pNode->mColor;
        (*ppLink)->mParent = pNode->mParent;
        if (((*ppLink)->mChild[1] = pNode->mChild[1]) != 0) {
            (*ppLink)->mChild[1]->mParent = *ppLink;
        }
    } else {
        for (pLast = pNode->mChild[0]; pLast->mChild[1]->mChild[1] != 0; pLast = pLast->mChild[1]) {
        }
        pPrev = pLast->mChild[1];
        if ((pLast->mChild[1] = pPrev->mChild[0]) != 0) {
            pLast->mChild[1]->mColor = pPrev->mColor;
            pLast->mChild[1]->mParent = pLast;
        }
        *ppLink = pPrev;
        (*ppLink)->mColor = pNode->mColor;
        (*ppLink)->mParent = pNode->mParent;
        if (((*ppLink)->mChild[1] = pNode->mChild[1]) != 0) {
            pNode->mChild[1]->mParent = *ppLink;
        }
        if (((*ppLink)->mChild[0] = pNode->mChild[0]) != 0) {
            pNode->mChild[0]->mParent = *ppLink;
        }
    }
    return pNode;
}

int fn_80202708(TDbIdxTree_80201EC8 *pTree, unsigned int *pKeyA, unsigned int *pKeyB, unsigned int count)
{
    short sign = 0;
    short result = 0;
    unsigned char i;

    TDbIdxPart_80202708 *pParts = pTree->mParts;

    for (i = 0; i < count; i++) {
        TDbColumn_801FAA00 *pColumn;

        sign = pParts[i].mAscending ? 1 : -1;
        if (pParts[i].mColumn != TDB_COLUMN_ROW) {
            pColumn = &pParts[i].mTable->mColumns[pParts[i].mColumn];
            switch (pColumn->mType) {
            case TDB_TYPE_STRING:
                result = lbl_803EBE74((char *)pKeyA[i], (char *)pKeyB[i], pColumn->mBitCount >> 3);
                break;
            case TDB_TYPE_INT:
                result = (int)pKeyA[i] > (int)pKeyB[i] ? 1 : (int)pKeyA[i] < (int)pKeyB[i] ? -1 : 0;
                break;
            case TDB_TYPE_UINT:
                result = pKeyA[i] > pKeyB[i] ? 1 : pKeyA[i] < pKeyB[i] ? -1 : 0;
                break;
            case TDB_TYPE_FLOAT:
                result = ((float *)pKeyA)[i] > ((float *)pKeyB)[i]   ? 1
                         : ((float *)pKeyA)[i] < ((float *)pKeyB)[i] ? -1
                                                                     : 0;
                break;
            case TDB_TYPE_BINARY:
                result = memcmp((void *)pKeyA[i], (void *)pKeyB[i], pColumn->mBitOffset >> 3);
                break;
            default:
                result = 0;
                break;
            }
        } else {
            result = pKeyA[i] > pKeyB[i] ? 1 : pKeyA[i] < pKeyB[i] ? -1 : 0;
        }
        if (result != 0) {
            break;
        }
    }
    return result * sign;
}

void fn_802028C0(TDbIdxTree_80201EC8 *pTree, int row, TDbIdxNode_80201EC8 *pNode)
{
    unsigned int *pKey = pNode->mKey;
    unsigned char i;

    for (i = 0; i < pTree->mPartCount; i++) {
        if (pTree->mParts[i].mColumn != TDB_COLUMN_ROW) {
            TDbTable_801FAA00 *pTable = pTree->mParts[i].mTable;
            TDbColumn_801FAA00 *pColumn = &pTable->mColumns[pTree->mParts[i].mColumn];
            unsigned char *pRow = pTable->mRows + pTable->mRowSize * row;

            if (pColumn->mType > TDB_TYPE_BINARY) {
                fn_80201D94((unsigned int *)pRow, pColumn->mBitOffset, pColumn->mBitCount, &pKey[i],
                            pColumn->mType == TDB_TYPE_INT);
            } else {
                pKey[i] = (unsigned int)(pRow + (pColumn->mBitOffset >> 3));
            }
        } else {
            pKey[i] = row;
        }
    }
}

int fn_8020299C(TDbIndex_801FAA00 *pIndex, unsigned int rowArg)
{
    unsigned short row = rowArg;
    TDbValue_801FDF28 result;
    TDbIdxNode_80201EC8 *pNode;
    int err;

    if (pIndex->mFilter != 0) {
        fn_802047EC(pIndex->mFilter, &result, &pIndex->mTable, &row);
        if (result.mValue.i == 0) {
            return 0;
        }
    }
    err = fn_8020360C(&pIndex->mPool, &pNode);
    if (err == 0) {
        fn_802028C0(&pIndex->mTree, row, pNode);
        pNode->mRow = row;
        pNode->mChild[0] = pNode->mChild[1] = 0;
        pNode->mColor = 1;
        err = fn_802024B0(&pIndex->mTree, pNode, 0);
        if (err != 0) {
            fn_80203744(&pIndex->mPool, pNode);
        } else {
            pIndex->mDirty = 1;
            pIndex->mCount++;
        }
    }
    return err;
}

TDbIdxNode_80201EC8 *fn_80202A84(TDbIndex_801FAA00 *pIndex, int row)
{
    TDbIdxNode_80201EC8 *pKey;
    TDbIdxNode_80201EC8 *pNode = 0;

    if (fn_8020360C(&pIndex->mPool, &pKey) == 0) {
        fn_802028C0(&pIndex->mTree, row, pKey);
        pNode = fn_80201F9C(&pIndex->mTree, pKey->mKey, TDB_OP_EQ);
        while (pNode != 0 && row != pNode->mRow) {
            pNode = fn_80202200(&pIndex->mTree, pNode);
            if (pNode != 0 && fn_80202708(&pIndex->mTree, pNode->mKey, pKey->mKey, 1) != 0) {
                pNode = 0;
            }
        }
        fn_80203744(&pIndex->mPool, pKey);
    }
    return pNode;
}

int fn_80202B60(TDbIndex_801FAA00 *pIndex, TDbIdxNode_80201EC8 *pNode, unsigned short row)
{
    TDbValue_801FDF28 result;
    TDbIdxNode_80201EC8 *pNew;
    TDbMemPool_80202B60 *pPool;
    int err;

    if (pNode == 0) {
        return fn_8020299C(pIndex, row);
    }
    if (pIndex->mFilter != 0) {
        fn_802047EC(pIndex->mFilter, &result, &pIndex->mTable, &row);
        if (result.mValue.i == 0) {
            fn_80206668(pIndex, pNode, 0);
            fn_802025C4(&pIndex->mTree, pNode);
            fn_80203744(&pIndex->mPool, pNode);
            pIndex->mDirty = 1;
            pIndex->mCount--;
            return 0;
        }
    }
    pPool = &pIndex->mPool;
    err = fn_8020360C(pPool, &pNew);
    if (err == 0) {
        if (pIndex->mFlags & 1) {
            pIndex->mDirty = 1;
            fn_802025C4(&pIndex->mTree, pNode);
            pNode->mChild[0] = pNode->mChild[1] = pNode->mParent = 0;
            pNew->mColor = 1;
            err = fn_802024B0(&pIndex->mTree, pNode, 0);
            if (err != 0) {
                fn_80203744(pPool, pNew);
            }
        } else {
            fn_802028C0(&pIndex->mTree, row, pNew);
            if (fn_80202708(&pIndex->mTree, pNode->mKey, pNew->mKey, pIndex->mTree.mPartCount) != 0) {
                pIndex->mDirty = 1;
                fn_80206668(pIndex, pNode, pNew);
                fn_802025C4(&pIndex->mTree, pNode);
                fn_80203744(pPool, pNode);
                pNew->mRow = row;
                pNew->mChild[0] = pNew->mChild[1] = 0;
                pNew->mColor = 1;
                err = fn_802024B0(&pIndex->mTree, pNew, 0);
                if (err != 0) {
                    fn_80203744(pPool, pNew);
                }
            } else {
                fn_80203744(pPool, pNew);
            }
        }
    }
    return err;
}

int fn_80202D34(TDbIndex_801FAA00 *pIndex, int row)
{
    TDbIdxNode_80201EC8 *pKey;
    TDbIdxNode_80201EC8 *pNode;
    int err;

    err = fn_8020360C(&pIndex->mPool, &pKey);
    if (err == 0) {
        fn_802028C0(&pIndex->mTree, row, pKey);
        pNode = fn_80201F9C(&pIndex->mTree, pKey->mKey, TDB_OP_EQ);
        while (pNode != 0) {
            if (row == pNode->mRow) {
                fn_802025C4(&pIndex->mTree, pNode);
                fn_80203744(&pIndex->mPool, pNode);
                pIndex->mDirty = 1;
                pIndex->mCount--;
                pNode = fn_80201F9C(&pIndex->mTree, pKey->mKey, TDB_OP_EQ);
            } else {
                pNode = fn_80202200(&pIndex->mTree, pNode);
                if (pNode != 0 && fn_80202708(&pIndex->mTree, pNode->mKey, pKey->mKey, 1) != 0) {
                    pNode = 0;
                }
            }
        }
        fn_80203744(&pIndex->mPool, pKey);
    }
    return err;
}

/* Build an index from rows whose deletion bit is clear. */
int CreateDatabaseIndex(TDbTable_801FAA00 *pTable, int id, TDbIdxColumnDef_801FFFC4 *pDefs,
                        TDbExpr_801FAA00 *pFilter, int unique)
{
    int err = 0;
    TDbIndex_801FAA00 *pIndex = 0;
    unsigned char i = 0;
    unsigned short row;

    while (pDefs[i].mId != -1) {
        i++;
    }
    TDbMemNotify_801FC9D4(2, (int)pTable->mDb->mUnknown8, pTable->mUnknown1C);
    if (i <= 2) {
        err = fn_8020360C(&lbl_803E96A8, &pIndex);
        pIndex->mFlags = 4;
    } else {
        err =
            fn_8020D1B0(pTable->mDb->mHeap, sizeof(TDbIndex_801FAA00) + (i - 1) * sizeof(TDbIdxPart_80202708), &pIndex);
        pIndex->mFlags = 0;
    }
    if (lbl_803EBE80) {
        TDbMemEvent_801FC5FC event;
        event.mType = 4;
        event.mUnknown4 = -1;
        event.mUnknown8 = -1;
        lbl_803EBE80(&event);
    }
    if (err == 0) {
        if (pFilter != 0) {
            err = fn_80204EF8(pFilter, &pIndex->mFilter, &pTable, 1, 0);
        } else {
            pIndex->mFilter = 0;
        }
        if (err == 0) {
            err = fn_80203444(&pIndex->mPool, pTable->mDb->mHeap,
                              sizeof(TDbIdxNode_80201EC8) + (i - 1) * sizeof(unsigned int),
                              (pFilter == 0 ? pTable->mCapacity : pTable->mCapacity >> 2) + 5, 100);
            if (err == 0) {
                pIndex->mLocked = 0;
                pIndex->mId = id;
                pIndex->mTable = pTable;
                pIndex->mCount = 0;
                pIndex->mDestroyed = 0;
                pIndex->mTree.mPartCount = i;
                pIndex->mTree.mAllowDuplicates = unique == 0;
                pIndex->mTree.mRoot = 0;
                for (i = 0; i < pIndex->mTree.mPartCount; i++) {
                    pIndex->mTree.mParts[i].mColumn = pDefs[i].mColumn;
                    if (pTable->mColumns[pDefs[i].mColumn].mType <= TDB_TYPE_BINARY) {
                        pIndex->mFlags |= 1;
                    }
                    pIndex->mTree.mParts[i].mAscending = pDefs[i].mDescending == 0;
                    pIndex->mTree.mParts[i].mTable = pTable;
                }
                if (err == 0) {
                    for (row = 0; row < pTable->mRowCount; row++) {
                        if (!TDbRowBit_801FAAF8(pTable, row)) {
                            err = fn_8020299C(pIndex, row);
                            if (err != 0) {
                                break;
                            }
                        }
                    }
                }
                if (err != 0) {
                    fn_8020353C(&pIndex->mPool);
                }
            }
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
    } else if (pIndex != 0) {
        if (pIndex->mFlags & 4) {
            fn_80203744(&lbl_803E96A8, pIndex);
        } else {
            fn_8020D2AC(pTable->mDb->mHeap, pIndex, sizeof(TDbIndex_801FAA00) + (i - 1) * sizeof(TDbIdxPart_80202708));
        }
    }
    return err;
}

int fn_8020325C(TDbIndex_801FAA00 *pIndex)
{
    int err;

    err = fn_8020353C(&pIndex->mPool);
    if (err == 0) {
        err = fn_80203444(&pIndex->mPool, pIndex->mTable->mDb->mHeap,
                          sizeof(TDbIdxNode_80201EC8) + (pIndex->mTree.mPartCount - 1) * sizeof(unsigned int),
                          pIndex->mTable->mCapacity + 5, 100);
        if (err == 0) {
            pIndex->mTree.mRoot = 0;
            pIndex->mCount = 0;
        }
    }
    return err;
}

int fn_802032D8(TDbIndex_801FAA00 *pIndex)
{
    TDbTable_801FAA00 *pTable = pIndex->mTable;
    TDbIndex_801FAA00 *pCur = pTable->mIndexes;
    TDbQuery_802032D8 *pQuery;
    int found = 0;
    int err;

    if (pIndex->mLocked) {
        pIndex->mId = 0;
        pIndex->mDestroyed = 1;
        for (pQuery = lbl_803EBE90; pQuery != 0; pQuery = pQuery->mNext) {
            if (pQuery->mState == 1 && pQuery->mSource.mIndex == pIndex) {
                pQuery->mState = 2;
            }
        }
        return 0;
    }
    if (pCur == pIndex) {
        pTable->mIndexes = pIndex->mNext;
        found = 1;
    } else {
        for (; pCur != 0; pCur = pCur->mNext) {
            if (pCur->mNext == pIndex) {
                pCur->mNext = pIndex->mNext;
                pIndex->mNext = 0;
                found = 1;
                break;
            }
        }
    }
    if (found) {
        err = fn_8020353C(&pIndex->mPool);
        if (err == 0) {
            if (pIndex->mFilter != 0) {
                fn_802055CC(pIndex->mFilter);
            }
            if (pIndex->mFlags & 4) {
                fn_80203744(&lbl_803E96A8, pIndex);
            } else {
                fn_8020D2AC(pTable->mDb->mHeap, pIndex,
                            sizeof(TDbIndex_801FAA00) + (pIndex->mTree.mPartCount - 1) * sizeof(TDbIdxPart_80202708));
            }
        }
    } else {
        err = 3;
    }
    return err;
}
