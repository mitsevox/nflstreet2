#include "engine/t3db.h"

typedef struct TDbDeleteResult_80208204 {
    unsigned short mCount;
    int mErr;
} TDbDeleteResult_80208204;

extern int fn_801F88F0(void *pDb, int id, int *pOut, TDbTable_801FAA00 **ppTable);
extern int fn_80205DB8(TDbStmt_80205754 *pStmt, TDbExpr_801FAA00 *pWhere, int a, int b);
extern unsigned char fn_80207448(TDbExpr_801FAA00 *pExpr, unsigned int table, unsigned int *pOtherTable,
                                 TDbExpr_801FAA00 **ppOut);
extern void fn_8020C3E4(TDbTable_801FAA00 *pTable, int row);
extern void fn_8020A5A8(void);

int fn_802075F4(TDbStmt_80205754 *pStmt, unsigned int t)
{
    int err = 0;
    unsigned int key;
    TDbValue_801FDF28 value;
    TDbValue_801FDF28 result;
    TDbExpr_801FAA00 *pSeek;
    unsigned int *pKey;

    if (pStmt->mIndexes[t] == 0) {
        pStmt->mRows[t] = 0;
    } else {
        if (pStmt->mSeekExprs[t] == 0) {
            pStmt->mNodes[t] = fn_80202200(&pStmt->mIndexes[t]->mTree, 0);
        } else {
            pSeek = pStmt->mSeekExprs[t];
            pKey = &key;
            if (pSeek->mRight.mType == TDB_TYPE_COLUMN) {
                unsigned int table = pSeek->mRight.mValue.l >> 32;
                unsigned char column = pSeek->mRight.mValue.l;
                unsigned short row = pStmt->mRows[table];
                TDbTable_801FAA00 *pTable = pStmt->mTables[table];

                if (row == 0xFFFF) {
                    *pKey = 0;
                } else {
                    unsigned char *pRow = pTable->mRows + pTable->mRowSize * row;

                    if (pTable->mColumns[column].mType > 1) {
                        fn_80201D94((unsigned int *)pRow, pTable->mColumns[column].mBitOffset,
                                    pTable->mColumns[column].mBitCount, pKey, pTable->mColumns[column].mType == 2);
                    } else {
                        *pKey = (unsigned int)(pRow + (pTable->mColumns[column].mBitOffset >> 3));
                    }
                }
            } else if ((unsigned int)(pSeek->mRight.mType - TDB_TYPE_EXPR_TRUNC) <= 2) {
                fn_802047EC(pSeek->mRight.mValue.p, &result, pStmt->mTables, pStmt->mRows);
                *pKey = result.mValue.u;
            } else {
                *pKey = pSeek->mRight.mValue.u;
            }
            pStmt->mNodes[t] = fn_80201F9C(&pStmt->mIndexes[t]->mTree, pKey, pStmt->mSeekExprs[t]->mOp);
        }
        if (err == 0) {
            if (pStmt->mNodes[t] != 0) {
                pStmt->mRows[t] = pStmt->mNodes[t]->mRow;
                pStmt->mNodes[t] = fn_80202200(&pStmt->mIndexes[t]->mTree, pStmt->mNodes[t]);
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
                if (TDbRowBit_801FAAF8(pStmt->mTables[t], pStmt->mRows[t])) {
                    pStmt->mRows[t]++;
                    continue;
                }
            }
            fn_802047EC(pStmt->mTableExprs[t], &value, pStmt->mTables, pStmt->mRows);
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
                    pStmt->mNodes[t] = fn_80202200(&pStmt->mIndexes[t]->mTree, pStmt->mNodes[t]);
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
    TDbValue_801FDF28 value;

    if (pStmt->mRows[t] != 0xFFFF) {
        do {
            if (pStmt->mIndexes[t] == 0) {
                for (;;) {
                    pStmt->mRows[t]++;
                    if (pStmt->mRows[t] >= pStmt->mTables[t]->mRowCount ||
                        !TDbRowBit_801FAAF8(pStmt->mTables[t], pStmt->mRows[t])) {
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
                pStmt->mNodes[t] = fn_80202200(&pStmt->mIndexes[t]->mTree, pStmt->mNodes[t]);
            }
            if (pStmt->mSeekExprs[t] != 0) {
                fn_802047EC(pStmt->mSeekExprs[t], &value, pStmt->mTables, pStmt->mRows);
                if (value.mValue.i == 0) {
                    err = 0x17;
                    break;
                }
                if (pStmt->mSeekExprs[t] != pStmt->mTableExprs[t]) {
                    fn_802047EC(pStmt->mTableExprs[t], &value, pStmt->mTables, pStmt->mRows);
                }
            } else {
                fn_802047EC(pStmt->mTableExprs[t], &value, pStmt->mTables, pStmt->mRows);
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

int fn_80207B8C(void *pDb, TDbSQLTableRef_801FDC18 *pRefs, TDbExpr_801FAA00 *pWhere, TDbStmt_80205754 *pStmt)
{
    int err = 0;
    unsigned int count;
    int info;
    TDbExpr_801FAA00 *pAnd;

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
        err = fn_80204EF8(pRefs[count].mExpr, &pStmt->mTableExprs[count], pStmt->mTables, count + 1, 0);
        if (err != 0) {
            pStmt->mTableCount = count;
            break;
        }
    }
    pStmt->mTableCount = count;
    if (err == 0) {
        if (count == 1) {
            err = fn_80204EF8(pWhere, &pStmt->mWhere, pStmt->mTables, 1, 0);
            if (err == 0) {
                if (pStmt->mTableExprs[0] == 0) {
                    pStmt->mTableExprs[0] = pStmt->mWhere;
                    pStmt->mWhere = 0;
                } else if (pStmt->mWhere != 0) {
                    err = fn_8020360C(&lbl_803E9654, &pAnd);
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
            fn_802055CC(pStmt->mWhere);
        }
        while (pStmt->mTableCount > 1) {
            pStmt->mTableCount--;
            fn_802055CC(pStmt->mTableExprs[pStmt->mTableCount]);
        }
    }
    return err;
}

void fn_80207DB4(TDbStmt_80205754 *pStmt)
{
    unsigned int i;

    if (pStmt->mWhere != 0) {
        fn_802055CC(pStmt->mWhere);
    }
    for (i = 0; i < pStmt->mTableCount; i++) {
        if (pStmt->mTableExprs[i] != 0) {
            fn_802055CC(pStmt->mTableExprs[i]);
        }
    }
}

int fn_80207E24(TDbStmt_80205754 *pStmt, TDbIdxColumnDef_801FFFC4 *pCols, int create)
{
    int err = 0;
    int exact = 0;
    TDbIndex_801FAA00 *pBest = 0;
    unsigned int best = -1;
    TDbExpr_801FAA00 *pBestSeek = 0;
    unsigned int score;
    TDbIndex_801FAA00 *pIndex;
    TDbExpr_801FAA00 *pSeek;
    TDbIdxColumnDef_801FFFC4 *pCol;
    unsigned short row;

    pStmt->mJoinTables[0] = 0;
    pStmt->mSeekExprs[0] = 0;
    pStmt->mNodes[0] = 0;
    pStmt->mIndexes[0] = 0;
    if (pCols != 0) {
        for (pCol = pCols; pCol->mId != -1; pCol++) {
            pCol->mColumn = fn_8020B97C(pStmt->mTables[0], pCol->mId);
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
                        if (!TDbRowBit_801FAAF8(pStmt->mTables[0], row)) {
                            err = fn_8020299C(pIndex, row);
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
                        err = fn_8020299C(pIndex, pStmt->mRows[0]);
                        if (err != 0) {
                            break;
                        }
                    }
                    if (err == 0x17) {
                        err = 0;
                    }
                }
                if (err != 0) {
                    fn_802032D8(pIndex);
                    pStmt->mIndexes[0] = 0;
                    pStmt->mRows[0] = 0;
                    pStmt->mNodes[0] = 0;
                } else {
                    pStmt->mRows[0] = 0;
                    pStmt->mIndexes[0] = pIndex;
                    pStmt->mNodes[0] = fn_80202200(&pIndex->mTree, 0);
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
    TDbExpr_801FAA00 *pSeek;
    TDbIndex_801FAA00 *pIndex;

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

int fn_80208204(void *pUnused, TDbStmt_80205754 *pStmt, TDbDeleteResult_80208204 *pResult)
{
    int err = 0;
    TDbValue_801FDF28 value;
    TDbIndex_801FAA00 *pIndex;

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
                    fn_802047EC(pStmt->mWhere, &value, pStmt->mTables, pStmt->mRows);
                    if (value.mValue.i != 0) {
                        fn_8020651C(pStmt->mTables[0], pStmt->mRows[0]);
                        for (pIndex = pStmt->mTables[0]->mIndexes; pIndex != 0; pIndex = pIndex->mNext) {
                            err = fn_80202D34(pIndex, pStmt->mRows[0]);
                            if (err != 0) {
                                break;
                            }
                        }
                        fn_80205C44(pStmt->mTables[0], pStmt->mRows[0]);
                        if (err != 0) {
                            break;
                        }
                        fn_8020C3E4(pStmt->mTables[0], pStmt->mRows[0]);
                        pResult->mCount++;
                    }
                    if (pStmt->mRows[0] < pStmt->mTables[0]->mRowCount &&
                        TDbRowBit_801FAAF8(pStmt->mTables[0], pStmt->mRows[0])) {
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
        if (pStmt->mTables[0]->mUnknown46 == pStmt->mTables[0]->mRowCount) {
            pStmt->mTables[0]->mUnknown46 = 0;
            pStmt->mTables[0]->mRowCount = 0;
            pStmt->mTables[0]->mUnknown48 = 0xFFFF;
        }
    }
    pResult->mErr = err;
    return err;
}
