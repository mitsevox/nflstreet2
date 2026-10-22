#include <string.h>
#include <stdarg.h>
#include "engine/t3db.h"
#include "game/fn_801FCE10.h"

typedef struct TDbSQLPool_801FC9D4 {
    unsigned int mItemSize;
    unsigned int mCount;
    unsigned int mUsed;
    void *mItems;
} TDbSQLPool_801FC9D4;

typedef struct TDbSQLVar_801FD47C {
    unsigned int mValue;
    unsigned int mType;
    unsigned int mSize;
} TDbSQLVar_801FD47C;

typedef struct TDbSQLAggregate_8020071C {
    unsigned int mCount;
    unsigned int mMax;
    unsigned int mMin;
    unsigned int mSum;
} TDbSQLAggregate_8020071C;

typedef struct TDbParseInfo_801FC9D4 {
    va_list mArgs;
    unsigned int mUnknownC;
    unsigned int mState;
    int mUnknown14;
    int mUnknown18;
    unsigned int mUnknown1C;
    unsigned int mColRefCount;
    TDbLitRef_80205754 *mColRefs;
    TDbSQLVar_801FD47C *mVars;
    unsigned int mTableRefCount;
    TDbSQLTableRef_801FDC18 *mTableRefs;
    TDbExpr_801FAA00 *mWhere;
    unsigned int mExprCount;
    TDbExpr_801FAA00 *mExprs;
    TDbLexer_801FCE10 mLexer;
} TDbParseInfo_801FC9D4;

extern TDbSQLPool_801FC9D4 lbl_8039B43C[5];

extern int fn_801F9718(int db, unsigned int tableId, TDbLitRef_80205754 *pColRefs, struct QueryResult *pResult,
                       int a);
extern int fn_801F97D0(int db, unsigned int tableId, int srcDb, int srcTable, struct QueryResult *pResult,
                       int a);
extern int fn_801F9858(int db, TDbSQLTableRef_801FDC18 *pTableRefs, TDbExpr_801FAA00 *pWhere,
                       TDbLitRef_80205754 *pColRefs, int srcDb, int srcTable, struct QueryResult *pResult,
                       int a);
extern int fn_801F9908(int db, TDbSQLTableRef_801FDC18 *pTableRefs, TDbExpr_801FAA00 *pWhere,
                       struct QueryResult *pResult, int a);
extern int fn_801F9AB8(int db, unsigned int tableId, TDbColumn_801FAA00 *pColumns, unsigned int *pCount);
extern int fn_801F9D70(int handle, int table, TDbExpr_801FAA00 *pFilter, unsigned short *pCount);
extern int fn_801F9E84(int db, unsigned int tableId, unsigned int index, TDbIdxColumnDef_801FFFC4 *pOrder,
                       TDbExpr_801FAA00 *pWhere, unsigned char unique);
extern int fn_801FA0BC(int db, TDbSQLTableRef_801FDC18 *pTableRefs, TDbExpr_801FAA00 *pWhere, void *pOrder,
                       int *pCursor, struct QueryResult *pResult);
extern int fn_801FA148(int cursor);
extern int fn_801FA228(int handle, int a, int b, void *pRecord);
extern int fn_801FA290(int db, TDbSQLTableRef_801FDC18 *pTableRefs, TDbExpr_801FAA00 *pWhere,
                       TDbLitRef_80205754 *pColRefs);
extern int fn_801FA3A0(int db, TDbSQLTableRef_801FDC18 *pTableRefs, TDbExpr_801FAA00 *pWhere,
                       TDbLitRef_80205754 *pColRefs, struct QueryResult *pResult, int a);
extern int fn_801FA5EC(int db, int b, int cursor, void *pRow, struct QueryResult *pResult);
extern int fn_801FA844(int db, TDbSQLTableRef_801FDC18 *pTableRefs, TDbExpr_801FAA00 *pWhere,
                       unsigned long long column, TDbSQLAggregate_8020071C *pAgg, struct QueryResult *pResult);
extern void fn_8020CCBC(TDbLitRef_80205754 *pLits, unsigned long long *pOut);

void fn_801FD0A4(TDbParseInfo_801FC9D4 *pInfo);
int fn_801FE5E0(TDbParseInfo_801FC9D4 *pInfo, TDbLexer_801FCE10 *pLexer, int result, TDbExpr_801FAA00 **ppExpr);
void fn_801FFEE4(TDbParseInfo_801FC9D4 *pInfo);
void fn_801FFFC4(TDbParseInfo_801FC9D4 *pInfo, TDbLexer_801FCE10 *pLexer, int result, struct QueryResult *pResult);
int fn_802004CC(TDbParseInfo_801FC9D4 *pInfo, TDbLexer_801FCE10 *pLexer, int result, TDbIdxColumnDef_801FFFC4 *pOrder,
                int count);
void fn_8020071C(int db, TDbParseInfo_801FC9D4 *pInfo, struct QueryResult *pResult);

static inline int TDbSQLPoolInit_801FC9D4(TDbSQLPool_801FC9D4 *pPool, unsigned int itemSize, unsigned int count)
{
    int err;

    pPool->mItemSize = itemSize;
    pPool->mUsed = 0;
    pPool->mCount = count;
    if (count != 0) {
        TDbMemNotify_801FC9D4(0, -1, -1);
        err = fn_8020D1B0(lbl_803EBE8C, count * itemSize, &pPool->mItems);
        TDbMemNotify_801FC9D4(4, -1, -1);
        return err;
    }
    return 3;
}

static inline void TDbSQLPoolFree_801FCD04(TDbSQLPool_801FC9D4 *pPool)
{
    if (pPool->mCount != 0 && pPool->mItemSize != 0) {
        fn_8020D2AC(lbl_803EBE8C, pPool->mItems, pPool->mItemSize * pPool->mCount);
    }
}

static inline void *TDbSQLPoolCur_801FD0E0(TDbSQLPool_801FC9D4 *pPool)
{
    return (unsigned char *)pPool->mItems + pPool->mUsed * pPool->mItemSize;
}

static inline void *TDbSQLPoolGet_801FCE10(TDbSQLPool_801FC9D4 *pPool)
{
    return (unsigned char *)pPool->mItems + pPool->mUsed++ * pPool->mItemSize;
}

static inline void TDbSQLPoolAdd_801FD0E0(TDbSQLPool_801FC9D4 *pPool, unsigned int count)
{
    pPool->mUsed += count;
}

static inline void TDbSQLPoolPut_801FCE10(TDbSQLPool_801FC9D4 *pPool, unsigned int count)
{
    pPool->mUsed -= count;
}

static inline void TDbParseInfoRelease_801FCE10(TDbParseInfo_801FC9D4 *pInfo)
{
    pInfo->mState = 0;
    TDbSQLPoolPut_801FCE10(&lbl_8039B43C[1], pInfo->mColRefCount);
    if (pInfo->mVars != 0) {
        TDbSQLPoolPut_801FCE10(&lbl_8039B43C[2], pInfo->mColRefCount);
    }
    TDbSQLPoolPut_801FCE10(&lbl_8039B43C[3], pInfo->mTableRefCount);
    TDbSQLPoolPut_801FCE10(&lbl_8039B43C[4], pInfo->mExprCount);
    TDbSQLPoolPut_801FCE10(&lbl_8039B43C[0], 1);
}

static inline void TDbLexNext_801FD3C0(TDbLexer_801FCE10 *pLexer)
{
    TDbToken_801FD2E8 *pNext = &pLexer->mTokens[1];

    pLexer->mTokens[0].mType = pNext->mType;
    pLexer->mTokens[0].mSrc = pNext->mSrc;
    pLexer->mTokens[0].mValue = pNext->mValue;
    fn_802009B0(pLexer, 1);
}

int fn_801FC9D4(int parseCount, int colRefCount, int countC, int tableRefCount, int countE)
{
    int err;

    err = TDbSQLPoolInit_801FC9D4(&lbl_8039B43C[2], 0xC, countC);
    if (err == 0) {
        err = TDbSQLPoolInit_801FC9D4(&lbl_8039B43C[1], sizeof(TDbLitRef_80205754), colRefCount);
        if (err == 0) {
            err = TDbSQLPoolInit_801FC9D4(&lbl_8039B43C[4], 0x28, countE);
            if (err == 0) {
                err = TDbSQLPoolInit_801FC9D4(&lbl_8039B43C[3], 0xC, tableRefCount);
                if (err == 0) {
                    err = TDbSQLPoolInit_801FC9D4(&lbl_8039B43C[0], sizeof(TDbParseInfo_801FC9D4), parseCount);
                }
            }
        }
    }
    return err;
}

void fn_801FCD04(void)
{
    TDbSQLPoolFree_801FCD04(&lbl_8039B43C[2]);
    TDbSQLPoolFree_801FCD04(&lbl_8039B43C[1]);
    TDbSQLPoolFree_801FCD04(&lbl_8039B43C[4]);
    TDbSQLPoolFree_801FCD04(&lbl_8039B43C[3]);
    TDbSQLPoolFree_801FCD04(&lbl_8039B43C[0]);
}

int fn_801FCE10(void *pResult, const char *pQuery, ...)
{
    struct QueryResult local;
    TDbParseInfo_801FC9D4 *pInfo;
    TDbLexer_801FCE10 *pLexer;

    pInfo = TDbSQLPoolGet_801FCE10(&lbl_8039B43C[0]);
    pLexer = &pInfo->mLexer;
    fn_801FD0A4(pInfo);
    if (pResult == 0) {
        pResult = &local;
    }
    ((struct QueryResult *)pResult)->mUnknown4 = 0;
    ((struct QueryResult *)pResult)->mUnknown8 = 0;
    ((struct QueryResult *)pResult)->mUnknown0 = 0;
    ((struct QueryResult *)pResult)->mUnknown2 = 0;
    pLexer->mSrc = (char *)pQuery;
    pLexer->mBufUsed = 0;
    fn_802009B0(pLexer, 0);
    va_start(pInfo->mArgs, pQuery);
    fn_801FFFC4(pInfo, pLexer, -1, pResult);
    if (pInfo->mState != 2) {
        TDbParseInfoRelease_801FCE10(pInfo);
    }
    return ((struct QueryResult *)pResult)->mUnknown4;
}

int fn_801FCFA0(struct QueryCursor *pCursor)
{
    TDbParseInfo_801FC9D4 *pInfo;
    unsigned int n;
    unsigned int i;

    if (pCursor->mUnknown12 != 0) {
        ((TDbParseInfo_801FC9D4 *)pCursor->mUnknown12)->mState = 10;
        n = lbl_8039B43C[0].mUsed;
        pInfo = (TDbParseInfo_801FC9D4 *)((unsigned char *)lbl_8039B43C[0].mItems + n * lbl_8039B43C[0].mItemSize);
        i = n - 1;
        if (n != 0) {
            do {
                pInfo--;
                if (pInfo->mState != 10) {
                    break;
                }
                TDbParseInfoRelease_801FCE10(pInfo);
            } while (i-- != 0);
        }
    }
    pCursor->mUnknown12 = 0;
    return fn_801FA148(pCursor->mUnknown0);
}

void fn_801FD0A4(TDbParseInfo_801FC9D4 *pInfo)
{
    pInfo->mColRefCount = 0;
    pInfo->mUnknown18 = -1;
    pInfo->mTableRefCount = 0;
    pInfo->mExprCount = 0;
    pInfo->mWhere = 0;
    pInfo->mState = 0;
    pInfo->mUnknown1C = 0;
    pInfo->mUnknown14 = 0;
    pInfo->mExprs = 0;
    pInfo->mColRefs = 0;
    pInfo->mTableRefs = 0;
    pInfo->mVars = 0;
}

void fn_801FD0E0(int db, TDbParseInfo_801FC9D4 *pInfo, unsigned char *pData, int size)
{
    TDbColumn_801FAA00 columns[0xFE];
    unsigned int count;
    TDbColumn_801FAA00 *pColumn;
    TDbLitRef_80205754 *pRef;

    count = 0xFE;
    memset(pData, 0, size);
    if (pInfo->mTableRefCount == 2) {
        fn_801F9AB8(db, pInfo->mTableRefs->mId, columns, &count);
        columns[count].mUnknown8 = -1;
        pInfo->mColRefs = TDbSQLPoolCur_801FD0E0(&lbl_8039B43C[1]);
        pRef = pInfo->mColRefs;
        for (pColumn = columns; pColumn->mUnknown8 != -1; pColumn++, pRef++) {
            pRef->mId = pColumn->mUnknown8;
            pRef->mTableId = pInfo->mTableRefs->mId;
            if (pColumn->mType <= TDB_TYPE_BINARY) {
                unsigned int bytes = pColumn->mBitCount >> 3;
                pRef->mUnknown0 = (unsigned int)pData;
                pData += bytes;
            }
            pInfo->mColRefCount++;
            TDbSQLPoolAdd_801FD0E0(&lbl_8039B43C[1], 1);
        }
        pRef->mId = -1;
        pRef->mTableId = -1;
    }
}

void fn_801FD200(int db, TDbParseInfo_801FC9D4 *pInfo, void *pOrder, struct QueryResult *pResult)
{
    unsigned long long row[0xFE];
    unsigned char literals[0x800];
    int cursor;

    pResult->mUnknown4 = fn_801FA0BC(db, pInfo->mTableRefs, pInfo->mWhere, pOrder, &cursor, pResult);
    if (pResult->mUnknown4 == 0 || pResult->mUnknown4 == 0x17 || pResult->mUnknown4 == 0x15 || pResult->mUnknown4 == 0x14) {
        if (pInfo->mColRefCount == 0) {
            fn_801FD0E0(db, pInfo, literals, sizeof(literals));
            fn_8020CCBC(pInfo->mColRefs, row);
        } else {
            fn_8020CCBC(pInfo->mColRefs, row);
        }
        pResult->mUnknown4 = fn_801FA5EC(pInfo->mUnknown14, pInfo->mUnknown18, cursor, row, pResult);
    }
    if (pResult->mUnknown4 == 0) {
        pResult->mUnknown4 = fn_801FA148(cursor);
    } else {
        fn_801FA148(cursor);
    }
}

unsigned int fn_801FD2E8(TDbParseInfo_801FC9D4 *pInfo, TDbToken_801FD2E8 *pToken)
{
    unsigned int value;

    value = -1;
    switch (pToken->mType) {
    case 0xC:
        value = va_arg(pInfo->mArgs, unsigned int);
        break;
    case 0x33:
        value = (pToken->mSrc[0] << 24) | (pToken->mSrc[1] << 16) | (pToken->mSrc[2] << 8) | pToken->mSrc[3];
        break;
    case 0xD:
    case 0x2F:
        break;
    }
    return value;
}

int fn_801FD3C0(TDbParseInfo_801FC9D4 *pInfo, TDbLexer_801FCE10 *pLexer, int result, TDbToken_801FD2E8 *pToken,
                unsigned int *pTable, unsigned int *pColumn)
{
    TDbToken_801FD2E8 *pNext = &pLexer->mTokens[1];

    *pTable = fn_801FD2E8(pInfo, pToken);
    if (pNext->mType == 0x3E) {
        TDbLexNext_801FD3C0(pLexer);
        TDbLexNext_801FD3C0(pLexer);
        *pColumn = fn_801FD2E8(pInfo, &pLexer->mTokens[0]);
    } else {
        *pColumn = *pTable;
        *pTable = -1;
    }
    return result;
}

int fn_801FD47C(TDbParseInfo_801FC9D4 *pInfo, TDbLexer_801FCE10 *pLexer, int result, TDbSQLVar_801FD47C *pVar)
{
    TDbLexNext_801FD3C0(pLexer);
    TDbLexNext_801FD3C0(pLexer);
    switch (pLexer->mTokens[0].mType) {
    case 0:
        pVar->mValue = va_arg(pInfo->mArgs, unsigned int);
        pVar->mType = 2;
        pVar->mSize = 8;
        break;
    case 1:
        pVar->mValue = va_arg(pInfo->mArgs, unsigned int);
        pVar->mType = 2;
        pVar->mSize = 0x10;
        break;
    case 2:
        pVar->mValue = va_arg(pInfo->mArgs, unsigned int);
        pVar->mType = 2;
        pVar->mSize = 0x20;
        break;
    case 3:
        pVar->mValue = va_arg(pInfo->mArgs, unsigned int);
        pVar->mType = 3;
        pVar->mSize = 8;
        break;
    case 4:
        pVar->mValue = va_arg(pInfo->mArgs, unsigned int);
        pVar->mType = 3;
        pVar->mSize = 0x10;
        break;
    case 5:
        pVar->mValue = va_arg(pInfo->mArgs, unsigned int);
        pVar->mType = 3;
        pVar->mSize = 0x20;
        break;
    case 6:
        pVar->mValue = va_arg(pInfo->mArgs, unsigned int);
        pVar->mType = 4;
        pVar->mSize = 0x20;
        break;
    case 7:
        pVar->mValue = va_arg(pInfo->mArgs, unsigned int);
        pVar->mType = 4;
        pVar->mSize = 0x40;
        break;
    case 9:
        pVar->mValue = va_arg(pInfo->mArgs, unsigned int);
        pVar->mType = 1;
        break;
    case 8:
        pVar->mValue = va_arg(pInfo->mArgs, unsigned int);
        pVar->mType = 0;
        break;
    }
    return result;
}

int fn_801FD97C(TDbParseInfo_801FC9D4 *pInfo, TDbLexer_801FCE10 *pLexer, int result, TDbLitRef_80205754 *pRef,
                TDbSQLVar_801FD47C *pVar, int mode)
{
    unsigned int table;
    unsigned int column;

    TDbLexNext_801FD3C0(pLexer);
    result = fn_801FD3C0(pInfo, pLexer, result, &pLexer->mTokens[0], &table, &column);
    pRef->mTableId = table;
    pRef->mId = column;
    pRef->mUnknown0 = 0;
    if (pLexer->mTokens[1].mType == 0x17 && (mode == 0 || mode == 2)) {
        result = fn_801FD47C(pInfo, pLexer, result, pVar);
        if (pVar->mType == 0) {
            pRef->mUnknown0 = pVar->mValue;
        } else if (pVar->mType == 1) {
            pRef->mUnknown0 = pVar->mValue;
        }
    } else {
        pVar->mValue = 0;
        pVar->mType = 0;
    }
    return result;
}

int fn_801FDA78(TDbParseInfo_801FC9D4 *pInfo, TDbLexer_801FCE10 *pLexer, int result, int mode)
{
    unsigned int n;

    pInfo->mColRefs = TDbSQLPoolCur_801FD0E0(&lbl_8039B43C[1]);
    pInfo->mVars = TDbSQLPoolCur_801FD0E0(&lbl_8039B43C[2]);
    n = pInfo->mColRefCount++;
    TDbSQLPoolAdd_801FD0E0(&lbl_8039B43C[1], 1);
    TDbSQLPoolAdd_801FD0E0(&lbl_8039B43C[2], 1);
    result = fn_801FD97C(pInfo, pLexer, result, &pInfo->mColRefs[n], &pInfo->mVars[n], mode);
    while (pLexer->mTokens[1].mType == 0x38) {
        TDbLexNext_801FD3C0(pLexer);
        n = pInfo->mColRefCount++;
        TDbSQLPoolAdd_801FD0E0(&lbl_8039B43C[1], 1);
        TDbSQLPoolAdd_801FD0E0(&lbl_8039B43C[2], 1);
        result = fn_801FD97C(pInfo, pLexer, result, &pInfo->mColRefs[n], &pInfo->mVars[n], mode);
    }
    n = pInfo->mColRefCount++;
    TDbSQLPoolAdd_801FD0E0(&lbl_8039B43C[1], 1);
    TDbSQLPoolAdd_801FD0E0(&lbl_8039B43C[2], 1);
    pInfo->mColRefs[n].mTableId = -1;
    pInfo->mColRefs[n].mId = -1;
    return result;
}

int fn_801FDC18(TDbParseInfo_801FC9D4 *pInfo, TDbLexer_801FCE10 *pLexer, int result)
{
    TDbSQLTableRef_801FDC18 *pRef;
    TDbExpr_801FAA00 *pExpr;
    unsigned int n;

    while (pLexer->mTokens[1].mType == 0x1A || pLexer->mTokens[1].mType == 0x18) {
        n = pInfo->mTableRefCount++;
        TDbSQLPoolAdd_801FD0E0(&lbl_8039B43C[3], 1);
        pRef = &pInfo->mTableRefs[n];
        TDbLexNext_801FD3C0(pLexer);
        if (pLexer->mTokens[0].mType == 0x18) {
            pRef->mJoinType = 0;
        } else if (pLexer->mTokens[0].mType == 0x1A) {
            TDbLexNext_801FD3C0(pLexer);
            pRef->mJoinType = 1;
        }
        TDbLexNext_801FD3C0(pLexer);
        TDbLexNext_801FD3C0(pLexer);
        pRef->mId = fn_801FD2E8(pInfo, &pLexer->mTokens[0]);
        TDbLexNext_801FD3C0(pLexer);
        pInfo->mExprs = TDbSQLPoolCur_801FD0E0(&lbl_8039B43C[4]);
        result = fn_801FE5E0(pInfo, pLexer, result, &pExpr);
        pRef->mExpr = pExpr;
    }
    return result;
}

int fn_801FDDC8(TDbParseInfo_801FC9D4 *pInfo, TDbLexer_801FCE10 *pLexer, int result, unsigned int *pOp)
{
    TDbLexNext_801FD3C0(pLexer);
    switch (pLexer->mTokens[0].mType) {
    case 0x34:
        *pOp = 0x10002;
        break;
    case 0x35:
        *pOp = 0x10005;
        break;
    case 0x36:
        *pOp = 0x10003;
        break;
    case 0x3A:
        *pOp = 0x10001;
        break;
    case 0x3B:
        *pOp = 0x10004;
        break;
    case 0x37:
        *pOp = 0x10006;
        break;
    case 0x10:
        *pOp = va_arg(pInfo->mArgs, unsigned int);
        break;
    }
    return result;
}

int fn_801FDF28(TDbParseInfo_801FC9D4 *pInfo, TDbLexer_801FCE10 *pLexer, int result, TDbValue_801FDF28 *pValue)
{
    unsigned int table;
    unsigned int column;
    int paren;

    TDbLexNext_801FD3C0(pLexer);
    if (pLexer->mTokens[0].mType == 0x3C) {
        TDbLexNext_801FD3C0(pLexer);
        paren = 1;
    } else {
        paren = 0;
    }
    switch (pLexer->mTokens[0].mType) {
    case 0x30:
        pValue->mType = TDB_TYPE_INT;
        pValue->mValue.i = (int)pLexer->mTokens[0].mValue;
        break;
    case 0x31:
        pValue->mType = TDB_TYPE_FLOAT;
        pValue->mValue.f = *(float *)&pLexer->mTokens[0].mValue;
        break;
    case 0x32:
        pValue->mType = TDB_TYPE_STRING;
        pValue->mValue.s = pLexer->mTokens[0].mValue;
        break;
    case 0:
        pValue->mValue.i = va_arg(pInfo->mArgs, int);
        pValue->mType = TDB_TYPE_INT;
        break;
    case 1:
        pValue->mValue.i = va_arg(pInfo->mArgs, int);
        pValue->mType = TDB_TYPE_INT;
        break;
    case 2:
        pValue->mValue.i = va_arg(pInfo->mArgs, int);
        pValue->mType = TDB_TYPE_INT;
        break;
    case 3:
        pValue->mValue.u = va_arg(pInfo->mArgs, unsigned int);
        pValue->mType = TDB_TYPE_UINT;
        break;
    case 4:
        pValue->mValue.u = va_arg(pInfo->mArgs, unsigned int);
        pValue->mType = TDB_TYPE_UINT;
        break;
    case 5:
        pValue->mValue.u = va_arg(pInfo->mArgs, unsigned int);
        pValue->mType = TDB_TYPE_UINT;
        break;
    case 6:
    case 7:
        pValue->mValue.f = va_arg(pInfo->mArgs, double);
        pValue->mType = TDB_TYPE_FLOAT;
        break;
    case 9:
        pValue->mValue.p = va_arg(pInfo->mArgs, void *);
        pValue->mType = TDB_TYPE_BINARY;
        break;
    case 8:
        pValue->mValue.s = va_arg(pInfo->mArgs, char *);
        pValue->mType = TDB_TYPE_STRING;
        break;
    case 0x2F:
    case 0xC:
    case 0x33:
        result = fn_801FD3C0(pInfo, pLexer, result, &pLexer->mTokens[0], &table, &column);
        pValue->mType = TDB_TYPE_COLUMN;
        pValue->mValue.l = (unsigned long long)table << 32 | column;
        break;
    }
    if (paren == 1) {
        TDbLexNext_801FD3C0(pLexer);
    }
    return result;
}

int fn_801FE484(TDbParseInfo_801FC9D4 *pInfo, TDbLexer_801FCE10 *pLexer, int result, int *pOp)
{
    TDbToken_801FD2E8 *pNext = &pLexer->mTokens[1];

    switch (pNext->mType) {
    case 0x38:
        TDbLexNext_801FD3C0(pLexer);
        *pOp = 0x20009;
        break;
    case 0x39:
        TDbLexNext_801FD3C0(pLexer);
        *pOp = 0x2000A;
        break;
    default:
        *pOp = -1;
        break;
    }
    return result;
}

int fn_801FE534(TDbParseInfo_801FC9D4 *pInfo, TDbLexer_801FCE10 *pLexer, int result, TDbExpr_801FAA00 *pExpr)
{
    result = fn_801FDF28(pInfo, pLexer, result, &pExpr->mLeft);
    result = fn_801FDDC8(pInfo, pLexer, result, (unsigned int *)&pExpr->mOp);
    result = fn_801FDF28(pInfo, pLexer, result, &pExpr->mRight);
    if ((pExpr->mLeft.mType == TDB_TYPE_COLUMN && (int)pExpr->mLeft.mValue.l == -1) ||
        (pExpr->mRight.mType == TDB_TYPE_COLUMN && (int)pExpr->mRight.mValue.l == -1)) {
        pExpr->mOp = 0;
        pExpr->mLeft.mType = TDB_TYPE_UINT;
        pExpr->mLeft.mValue.u = 1;
        pExpr->mRight.mType = TDB_TYPE_UINT;
        pExpr->mRight.mValue.u = 1;
    }
    return result;
}

int fn_801FE5E0(TDbParseInfo_801FC9D4 *pInfo, TDbLexer_801FCE10 *pLexer, int result, TDbExpr_801FAA00 **ppExpr)
{
    TDbToken_801FD2E8 *pNext = &pLexer->mTokens[1];
    TDbExpr_801FAA00 *pExpr;
    TDbExpr_801FAA00 *pRight;
    TDbExpr_801FAA00 *pAnd;
    int op;
    unsigned int n;

    pExpr = 0;
    if (pNext->mType == 0x3C) {
        TDbLexNext_801FD3C0(pLexer);
        result = fn_801FE5E0(pInfo, pLexer, result, &pExpr);
        TDbLexNext_801FD3C0(pLexer);
    } else if (pNext->mType == 0xF) {
        TDbLexNext_801FD3C0(pLexer);
        *ppExpr = pExpr = va_arg(pInfo->mArgs, TDbExpr_801FAA00 *);
    } else {
        n = pInfo->mExprCount++;
        TDbSQLPoolAdd_801FD0E0(&lbl_8039B43C[4], 1);
        *ppExpr = pExpr = &pInfo->mExprs[n];
        result = fn_801FE534(pInfo, pLexer, result, pExpr);
    }
    *ppExpr = pExpr;
    result = fn_801FE484(pInfo, pLexer, result, &op);
    if (op != -1) {
        n = pInfo->mExprCount++;
        TDbSQLPoolAdd_801FD0E0(&lbl_8039B43C[4], 1);
        pAnd = &pInfo->mExprs[n];
        pAnd->mLeft.mType = TDB_TYPE_EXPR_UINT;
        pAnd->mLeft.mValue.p = pExpr;
        pAnd->mOp = op;
        result = fn_801FE5E0(pInfo, pLexer, result, &pRight);
        pAnd->mRight.mType = TDB_TYPE_EXPR_UINT;
        pAnd->mRight.mValue.p = pRight;
        *ppExpr = pAnd;
        if (op == 0x2000A) {
            if (pExpr->mOp == 0) {
                pExpr->mLeft.mValue.u = 0;
            }
            if (pRight->mOp == 0) {
                pRight->mLeft.mValue.u = 0;
            }
        }
    }
    return result;
}

int fn_801FE840(TDbParseInfo_801FC9D4 *pInfo, TDbLexer_801FCE10 *pLexer, int result)
{
    TDbToken_801FD2E8 *pNext = &pLexer->mTokens[1];

    if (pNext->mType == 0x14) {
        TDbLexNext_801FD3C0(pLexer);
        pInfo->mExprs = TDbSQLPoolCur_801FD0E0(&lbl_8039B43C[4]);
        result = fn_801FE5E0(pInfo, pLexer, result, &pInfo->mWhere);
    }
    return result;
}

int fn_801FE8DC(TDbParseInfo_801FC9D4 *pInfo, TDbLexer_801FCE10 *pLexer, int result)
{
    TDbSQLTableRef_801FDC18 *pRef;
    unsigned int joinType;
    unsigned int n;

    joinType = 2;
    TDbLexNext_801FD3C0(pLexer);
    TDbLexNext_801FD3C0(pLexer);
    pInfo->mTableRefs = TDbSQLPoolCur_801FD0E0(&lbl_8039B43C[3]);
    n = pInfo->mTableRefCount++;
    TDbSQLPoolAdd_801FD0E0(&lbl_8039B43C[3], 1);
    pRef = &pInfo->mTableRefs[n];
    pRef->mId = fn_801FD2E8(pInfo, &pLexer->mTokens[0]);
    pRef->mJoinType = joinType;
    pRef->mExpr = 0;
    result = fn_801FDC18(pInfo, pLexer, result);
    n = pInfo->mTableRefCount++;
    TDbSQLPoolAdd_801FD0E0(&lbl_8039B43C[3], 1);
    pRef = &pInfo->mTableRefs[n];
    pRef->mId = -1;
    pRef->mJoinType = joinType;
    return result;
}

int fn_801FEA04(TDbParseInfo_801FC9D4 *pInfo, TDbLexer_801FCE10 *pLexer, int result, TDbLitRef_80205754 *pRef,
                TDbSQLVar_801FD47C *pVar)
{
    unsigned int table;
    unsigned int column;
    unsigned int value;
    float f;

    TDbLexNext_801FD3C0(pLexer);
    result = fn_801FD3C0(pInfo, pLexer, result, &pLexer->mTokens[0], &table, &column);
    TDbLexNext_801FD3C0(pLexer);
    TDbLexNext_801FD3C0(pLexer);
    switch (pLexer->mTokens[0].mType) {
    case 0:
        value = va_arg(pInfo->mArgs, unsigned int);
        pVar->mType = TDB_TYPE_INT;
        pVar->mSize = 1;
        break;
    case 1:
        value = va_arg(pInfo->mArgs, unsigned int);
        pVar->mType = TDB_TYPE_INT;
        pVar->mSize = 2;
        break;
    case 2:
        value = va_arg(pInfo->mArgs, unsigned int);
        pVar->mType = TDB_TYPE_INT;
        pVar->mSize = 4;
        break;
    case 3:
        value = va_arg(pInfo->mArgs, unsigned int);
        pVar->mType = TDB_TYPE_UINT;
        pVar->mSize = 1;
        break;
    case 4:
        value = va_arg(pInfo->mArgs, unsigned int);
        pVar->mType = TDB_TYPE_UINT;
        pVar->mSize = 2;
        break;
    case 5:
        value = va_arg(pInfo->mArgs, unsigned int);
        pVar->mType = TDB_TYPE_UINT;
        pVar->mSize = 4;
        break;
    case 6:
        f = va_arg(pInfo->mArgs, double);
        pVar->mType = TDB_TYPE_FLOAT;
        value = *(unsigned int *)&f;
        pVar->mSize = 4;
        break;
    case 7:
        f = va_arg(pInfo->mArgs, double);
        pVar->mType = TDB_TYPE_FLOAT;
        value = *(unsigned int *)&f;
        pVar->mSize = 4;
        break;
    case 9:
        value = va_arg(pInfo->mArgs, unsigned int);
        pVar->mType = TDB_TYPE_BINARY;
        break;
    case 8:
        value = va_arg(pInfo->mArgs, unsigned int);
        pVar->mType = TDB_TYPE_STRING;
        break;
    case 0x30:
        value = (unsigned int)pLexer->mTokens[0].mValue;
        pVar->mType = TDB_TYPE_INT;
        pVar->mSize = 4;
        break;
    case 0x31:
        value = (unsigned int)pLexer->mTokens[0].mValue;
        pVar->mType = TDB_TYPE_FLOAT;
        pVar->mSize = 4;
        break;
    case 0x32:
        value = (unsigned int)pLexer->mTokens[0].mValue;
        pVar->mType = TDB_TYPE_STRING;
        pVar->mSize = 4;
        break;
    }
    pRef->mUnknown0 = value;
    pRef->mTableId = table;
    pRef->mId = column;
    return result;
}

int fn_801FEF44(TDbParseInfo_801FC9D4 *pInfo, TDbLexer_801FCE10 *pLexer, int result)
{
    unsigned int n;

    pInfo->mColRefs = TDbSQLPoolCur_801FD0E0(&lbl_8039B43C[1]);
    pInfo->mVars = TDbSQLPoolCur_801FD0E0(&lbl_8039B43C[2]);
    n = pInfo->mColRefCount++;
    TDbSQLPoolAdd_801FD0E0(&lbl_8039B43C[1], 1);
    TDbSQLPoolAdd_801FD0E0(&lbl_8039B43C[2], 1);
    result = fn_801FEA04(pInfo, pLexer, result, &pInfo->mColRefs[n], &pInfo->mVars[n]);
    while (pLexer->mTokens[1].mType == 0x38) {
        TDbLexNext_801FD3C0(pLexer);
        n = pInfo->mColRefCount++;
        TDbSQLPoolAdd_801FD0E0(&lbl_8039B43C[1], 1);
        TDbSQLPoolAdd_801FD0E0(&lbl_8039B43C[2], 1);
        result = fn_801FEA04(pInfo, pLexer, result, &pInfo->mColRefs[n], &pInfo->mVars[n]);
    }
    n = pInfo->mColRefCount++;
    TDbSQLPoolAdd_801FD0E0(&lbl_8039B43C[1], 1);
    TDbSQLPoolAdd_801FD0E0(&lbl_8039B43C[2], 1);
    pInfo->mColRefs[n].mTableId = -1;
    pInfo->mColRefs[n].mId = -1;
    return result;
}

int fn_801FF0D4(TDbParseInfo_801FC9D4 *pInfo, TDbLexer_801FCE10 *pLexer, int result)
{
    TDbLexNext_801FD3C0(pLexer);
    return fn_801FEF44(pInfo, pLexer, result);
}

int fn_801FF13C(TDbParseInfo_801FC9D4 *pInfo, TDbLexer_801FCE10 *pLexer, int result)
{
    TDbLitRef_80205754 *pRef;
    unsigned int n;
    unsigned int op;

    TDbLexNext_801FD3C0(pLexer);
    pInfo->mState = 8;
    pInfo->mColRefs = TDbSQLPoolCur_801FD0E0(&lbl_8039B43C[1]);
    pInfo->mVars = TDbSQLPoolCur_801FD0E0(&lbl_8039B43C[2]);
    while (1) {
        op = pLexer->mTokens[0].mType;
        n = pInfo->mColRefCount++;
        TDbSQLPoolAdd_801FD0E0(&lbl_8039B43C[1], 1);
        TDbSQLPoolAdd_801FD0E0(&lbl_8039B43C[2], 1);
        pRef = &pInfo->mColRefs[n];
        TDbLexNext_801FD3C0(pLexer);
        TDbLexNext_801FD3C0(pLexer);
        pRef->mUnknown0 = 0;
        if (pLexer->mTokens[0].mType == 0x41) {
            pRef->mTableId = 0;
            pRef->mId = 1;
            pRef->mUnknown0 = 0;
        } else {
            result = fn_801FD3C0(pInfo, pLexer, result, &pLexer->mTokens[0], &pRef->mTableId,
                                 (unsigned int *)&pRef->mId);
            pRef->mUnknown0 = 1;
        }
        pRef->mColumn = op;
        TDbLexNext_801FD3C0(pLexer);
        result = fn_801FD47C(pInfo, pLexer, result, &pInfo->mVars[n]);
        if (pLexer->mTokens[1].mType != 0x38) {
            break;
        }
        TDbLexNext_801FD3C0(pLexer);
        TDbLexNext_801FD3C0(pLexer);
    }
    n = pInfo->mColRefCount++;
    TDbSQLPoolAdd_801FD0E0(&lbl_8039B43C[1], 1);
    TDbSQLPoolAdd_801FD0E0(&lbl_8039B43C[2], 1);
    pInfo->mColRefs[n].mId = -1;
    return result;
}

int fn_801FF390(TDbParseInfo_801FC9D4 *pInfo, TDbLexer_801FCE10 *pLexer, int result)
{
    unsigned int id;
    unsigned int type = pLexer->mTokens[1].mType;

    if (type - 0x2B <= 3) {
        result = fn_801FF13C(pInfo, pLexer, result);
    } else if (type == 0x17) {
        if (pInfo->mState == 1) {
            pInfo->mState = 5;
        } else {
            pInfo->mState = 4;
        }
        TDbLexNext_801FD3C0(pLexer);
        TDbLexNext_801FD3C0(pLexer);
        id = fn_801FD2E8(pInfo, &pLexer->mTokens[0]);
        if (pLexer->mTokens[1].mType == 0x3E) {
            TDbLexNext_801FD3C0(pLexer);
            pInfo->mUnknown14 = id;
            TDbLexNext_801FD3C0(pLexer);
            id = fn_801FD2E8(pInfo, &pLexer->mTokens[0]);
        }
        pInfo->mUnknown18 = id;
        if (pLexer->mTokens[1].mType == 0x41) {
            TDbLexNext_801FD3C0(pLexer);
            pInfo->mColRefCount = 0;
        } else {
            result = fn_801FDA78(pInfo, pLexer, result, 1);
        }
    } else {
        result = fn_801FDA78(pInfo, pLexer, result, 0);
    }
    result = fn_801FE8DC(pInfo, pLexer, result);
    return fn_801FE840(pInfo, pLexer, result);
}

int fn_801FF544(TDbParseInfo_801FC9D4 *pInfo, TDbLexer_801FCE10 *pLexer, int result, unsigned char *pFlag)
{
    TDbSQLTableRef_801FDC18 *pRef;
    struct QueryCursor *pCursor;
    unsigned int n;

    TDbLexNext_801FD3C0(pLexer);
    switch (pLexer->mTokens[0].mType) {
    case 0xB:
        TDbLexNext_801FD3C0(pLexer);
        if (pLexer->mTokens[0].mType == 0x2A) {
            *pFlag = 1;
            TDbLexNext_801FD3C0(pLexer);
        } else {
            *pFlag = 0;
        }
        pInfo->mState = 3;
        pInfo->mUnknown1C = va_arg(pInfo->mArgs, unsigned int);
        TDbLexNext_801FD3C0(pLexer);
        TDbLexNext_801FD3C0(pLexer);
        pInfo->mTableRefs = TDbSQLPoolCur_801FD0E0(&lbl_8039B43C[3]);
        n = pInfo->mTableRefCount++;
        TDbSQLPoolAdd_801FD0E0(&lbl_8039B43C[3], 1);
        pRef = &pInfo->mTableRefs[n];
        pRef->mId = fn_801FD2E8(pInfo, &pLexer->mTokens[0]);
        pRef->mJoinType = 2;
        pRef->mExpr = 0;
        result = fn_801FE840(pInfo, pLexer, result);
        break;
    case 0xA:
        TDbLexNext_801FD3C0(pLexer);
        pCursor = va_arg(pInfo->mArgs, struct QueryCursor *);
        pInfo->mUnknown1C = (unsigned int)pCursor;
        if (pLexer->mTokens[0].mType == 0x28) {
            pInfo->mState = 2;
            pCursor->mUnknown12 = pInfo;
        } else {
            pInfo->mState = 1;
            pCursor->mUnknown12 = 0;
        }
        *pFlag = 0;
        TDbLexNext_801FD3C0(pLexer);
        TDbLexNext_801FD3C0(pLexer);
        if (pLexer->mTokens[1].mType == 0x41) {
            TDbLexNext_801FD3C0(pLexer);
            result = fn_801FE8DC(pInfo, pLexer, result);
            result = fn_801FE840(pInfo, pLexer, result);
        } else {
            result = fn_801FF390(pInfo, pLexer, result);
        }
        break;
    }
    return result;
}

int fn_801FF8BC(TDbParseInfo_801FC9D4 *pInfo, TDbLexer_801FCE10 *pLexer, int result)
{
    result = fn_801FE8DC(pInfo, pLexer, result);
    return fn_801FE840(pInfo, pLexer, result);
}

int fn_801FF8FC(TDbParseInfo_801FC9D4 *pInfo, TDbLexer_801FCE10 *pLexer, int result)
{
    struct QueryCursor *pCursor;
    TDbParseInfo_801FC9D4 *pOther;

    TDbLexNext_801FD3C0(pLexer);
    TDbLexNext_801FD3C0(pLexer);
    pInfo->mState = 9;
    pCursor = va_arg(pInfo->mArgs, struct QueryCursor *);
    pInfo->mUnknown1C = (unsigned int)pCursor;
    pOther = pCursor->mUnknown12;
    if (pOther != 0) {
        pInfo->mColRefs = pOther->mColRefs;
        pInfo->mVars = pOther->mVars;
    } else {
        result = fn_801FDA78(pInfo, pLexer, result, 2);
        pInfo->mTableRefs = TDbSQLPoolCur_801FD0E0(&lbl_8039B43C[3]);
        pInfo->mTableRefCount++;
        TDbSQLPoolAdd_801FD0E0(&lbl_8039B43C[3], 1);
        pInfo->mTableRefs->mId = ((struct QueryCursor *)pInfo->mUnknown1C)->mUnknown8;
        fn_801FFEE4(pInfo);
    }
    return result;
}

int fn_801FFA6C(TDbParseInfo_801FC9D4 *pInfo, TDbLexer_801FCE10 *pLexer, int result)
{
    TDbSQLTableRef_801FDC18 *pRef;

    TDbLexNext_801FD3C0(pLexer);
    pInfo->mTableRefs = TDbSQLPoolCur_801FD0E0(&lbl_8039B43C[3]);
    pInfo->mTableRefCount++;
    TDbSQLPoolAdd_801FD0E0(&lbl_8039B43C[3], 1);
    pRef = pInfo->mTableRefs;
    pRef->mId = fn_801FD2E8(pInfo, &pLexer->mTokens[0]);
    pRef->mJoinType = 2;
    pRef->mExpr = 0;
    pInfo->mTableRefCount++;
    TDbSQLPoolAdd_801FD0E0(&lbl_8039B43C[3], 1);
    pRef = &pInfo->mTableRefs[1];
    pRef->mJoinType = 2;
    pRef->mId = -1;
    result = fn_801FF0D4(pInfo, pLexer, result);
    return fn_801FE840(pInfo, pLexer, result);
}

int fn_801FFB68(TDbParseInfo_801FC9D4 *pInfo, TDbLexer_801FCE10 *pLexer, int result)
{
    TDbSQLTableRef_801FDC18 *pRef;
    unsigned int id;

    TDbLexNext_801FD3C0(pLexer);
    TDbLexNext_801FD3C0(pLexer);
    id = fn_801FD2E8(pInfo, &pLexer->mTokens[0]);
    if (pLexer->mTokens[1].mType == 0x3E) {
        TDbLexNext_801FD3C0(pLexer);
        pInfo->mUnknown14 = id;
        TDbLexNext_801FD3C0(pLexer);
        id = fn_801FD2E8(pInfo, &pLexer->mTokens[0]);
    }
    if (pLexer->mTokens[1].mType == 0x1E) {
        pInfo->mTableRefs = TDbSQLPoolCur_801FD0E0(&lbl_8039B43C[3]);
        pInfo->mTableRefCount++;
        TDbSQLPoolAdd_801FD0E0(&lbl_8039B43C[3], 1);
        pRef = pInfo->mTableRefs;
        pRef->mId = id;
        pRef->mJoinType = 2;
        pRef->mExpr = 0;
        result = fn_801FF0D4(pInfo, pLexer, result);
    } else {
        pInfo->mUnknown18 = id;
        if (pLexer->mTokens[1].mType == 0x41) {
            pInfo->mState = 6;
            TDbLexNext_801FD3C0(pLexer);
            pInfo->mColRefCount = 0;
        } else {
            pInfo->mState = 7;
            result = fn_801FDA78(pInfo, pLexer, result, 1);
        }
        TDbLexNext_801FD3C0(pLexer);
        TDbLexNext_801FD3C0(pLexer);
        result = fn_801FE8DC(pInfo, pLexer, result);
        result = fn_801FE840(pInfo, pLexer, result);
    }
    return result;
}

void fn_801FFDA8(TDbParseInfo_801FC9D4 *pInfo)
{
    TDbLitRef_80205754 *pRef = pInfo->mColRefs;
    TDbSQLVar_801FD47C *pVar = pInfo->mVars;
    void *pDst;

    while (pRef->mId != -1) {
        pDst = (void *)pVar->mValue;
        if (pDst != 0) {
            switch (pVar->mType) {
            case TDB_TYPE_STRING:
            case TDB_TYPE_BINARY:
                break;
            case TDB_TYPE_INT:
                if (pVar->mSize <= 8) {
                    *(unsigned char *)pDst = pRef->mUnknown0;
                } else if (pVar->mSize <= 16) {
                    *(unsigned short *)pDst = pRef->mUnknown0;
                } else if (pVar->mSize <= 32) {
                    *(unsigned int *)pDst = pRef->mUnknown0;
                }
                break;
            case TDB_TYPE_UINT:
                if (pVar->mSize <= 8) {
                    *(unsigned char *)pDst = pRef->mUnknown0;
                } else if (pVar->mSize <= 16) {
                    *(unsigned short *)pDst = pRef->mUnknown0;
                } else if (pVar->mSize <= 32) {
                    *(unsigned int *)pDst = pRef->mUnknown0;
                }
                break;
            case TDB_TYPE_FLOAT:
                if (pVar->mSize <= 32) {
                    *(float *)pDst = *(float *)&pRef->mUnknown0;
                } else if (pVar->mSize <= 64) {
                    *(double *)pDst = *(float *)&pRef->mUnknown0;
                }
                break;
            }
        }
        pRef++;
        pVar++;
    }
}

void fn_801FFE88(TDbParseInfo_801FC9D4 *pInfo)
{
    unsigned int id = pInfo->mTableRefs->mId;
    unsigned int i = pInfo->mColRefCount;
    TDbLitRef_80205754 *pRef;

    if (i != 0) {
        i--;
        while (i-- > 0) {
            pRef = &pInfo->mColRefs[i];
            if (pRef->mTableId == -1) {
                pRef->mTableId = id;
            }
        }
    }
}

static inline unsigned long long TDbColumnValue_801FFEE4(unsigned int table, unsigned int column)
{
    return ((unsigned long long)table << 32) | column;
}

void fn_801FFEE4(TDbParseInfo_801FC9D4 *pInfo)
{
    unsigned int id = pInfo->mTableRefs->mId;
    TDbExpr_801FAA00 *pExpr = pInfo->mExprs;
    unsigned int i;

    for (i = 0; i < pInfo->mExprCount; i++, pExpr++) {
        if (pExpr->mLeft.mType == TDB_TYPE_COLUMN && (unsigned int)(pExpr->mLeft.mValue.l >> 32) == -1) {
            pExpr->mLeft.mValue.l = TDbColumnValue_801FFEE4(id, (unsigned int)pExpr->mLeft.mValue.l);
        }
        if (pExpr->mRight.mType == TDB_TYPE_COLUMN && (unsigned int)(pExpr->mRight.mValue.l >> 32) == -1) {
            pExpr->mRight.mValue.l = TDbColumnValue_801FFEE4(id, (unsigned int)pExpr->mRight.mValue.l);
        }
    }
    fn_801FFE88(pInfo);
}

void fn_801FFFC4(TDbParseInfo_801FC9D4 *pInfo, TDbLexer_801FCE10 *pLexer, int result, struct QueryResult *pResult)
{
    TDbIdxColumnDef_801FFFC4 order[8];
    unsigned char unique;
    struct QueryCursor *pCursor;
    int db = 0;

    if (pLexer->mTokens[0].mType == 0x1F) {
        TDbLexNext_801FD3C0(pLexer);
        db = fn_801FD2E8(pInfo, &pLexer->mTokens[0]);
        pInfo->mUnknown14 = db;
        TDbLexNext_801FD3C0(pLexer);
    }
    switch (pLexer->mTokens[0].mType) {
    case 0x24:
    case 0x25:
        result = fn_801FF544(pInfo, pLexer, result, &unique);
        fn_802004CC(pInfo, pLexer, result, order, 8);
        fn_801FFEE4(pInfo);
        switch (pInfo->mState) {
        case 3:
            pResult->mUnknown4 = fn_801F9E84(db, pInfo->mTableRefs->mId, pInfo->mUnknown1C, order, pInfo->mWhere, unique);
            break;
        case 5:
            ((struct QueryCursor *)pInfo->mUnknown1C)->mUnknown4 = 0;
            fn_801FD200(db, pInfo, order, pResult);
            if (pResult->mUnknown4 == 0 || pResult->mUnknown4 == 0x17 || pResult->mUnknown4 == 0x15 || pResult->mUnknown4 == 0x14) {
                pInfo->mTableRefs[0].mId = pInfo->mUnknown18;
                pInfo->mTableRefs[0].mJoinType = 2;
                pInfo->mTableRefs[0].mExpr = 0;
                pInfo->mTableRefs[1].mId = -1;
                pInfo->mTableRefs[1].mJoinType = 2;
                pInfo->mTableRefs[1].mExpr = 0;
                ((struct QueryCursor *)pInfo->mUnknown1C)->mUnknown8 = pInfo->mUnknown18;
                pResult->mUnknown4 = fn_801FA0BC(pInfo->mUnknown14, pInfo->mTableRefs, 0, order,
                                            (int *)pInfo->mUnknown1C, pResult);
            }
            break;
        case 1:
        case 2:
            ((struct QueryCursor *)pInfo->mUnknown1C)->mUnknown4 = 0;
            ((struct QueryCursor *)pInfo->mUnknown1C)->mUnknown8 = pInfo->mTableRefs->mId;
            pResult->mUnknown4 = fn_801FA0BC(db, pInfo->mTableRefs, pInfo->mWhere, order, (int *)pInfo->mUnknown1C,
                                        pResult);
            if (pResult->mUnknown4 != 0 && pResult->mUnknown4 != 0x17 && pResult->mUnknown4 != 0x15 && pResult->mUnknown4 != 0x14 &&
                pInfo->mState == 2) {
                ((struct QueryCursor *)pInfo->mUnknown1C)->mUnknown12 = 0;
                pInfo->mState = 1;
            }
            break;
        }
        break;
    case 0x11:
        result = fn_801FF390(pInfo, pLexer, result);
        fn_801FFEE4(pInfo);
        if (pInfo->mState == 8) {
            fn_8020071C(db, pInfo, pResult);
        } else if (pInfo->mUnknown18 != -1) {
            fn_802004CC(pInfo, pLexer, result, order, 8);
            fn_801FD200(db, pInfo, order, pResult);
        } else {
            pResult->mUnknown4 = fn_801FA290(db, pInfo->mTableRefs, pInfo->mWhere, pInfo->mColRefs);
            if (pResult->mUnknown4 == 0) {
                fn_801FFDA8(pInfo);
                pResult->mUnknown0 = 1;
            } else {
                pResult->mUnknown0 = 0;
            }
        }
        break;
    case 0x1C:
        fn_801FFA6C(pInfo, pLexer, result);
        fn_801FFEE4(pInfo);
        pResult->mUnknown4 = fn_801FA3A0(db, pInfo->mTableRefs, pInfo->mWhere, pInfo->mColRefs, pResult, 0);
        break;
    case 0x12:
        fn_801FFB68(pInfo, pLexer, result);
        fn_801FFEE4(pInfo);
        if (pInfo->mState == 7) {
            pResult->mUnknown4 = fn_801F9858(db, pInfo->mTableRefs, pInfo->mWhere, pInfo->mColRefs, pInfo->mUnknown14,
                                        pInfo->mUnknown18, pResult, 0);
        } else if (pInfo->mState == 6) {
            if (pInfo->mWhere != 0 || pInfo->mTableRefCount > 2) {
                unsigned char data[0x800];

                fn_801FD0E0(db, pInfo, data, sizeof(data));
                pResult->mUnknown4 = fn_801F9858(db, pInfo->mTableRefs, pInfo->mWhere, pInfo->mColRefs,
                                            pInfo->mUnknown14, pInfo->mUnknown18, pResult, 0);
            } else {
                pResult->mUnknown4 = fn_801F97D0(db, pInfo->mTableRefs->mId, pInfo->mUnknown14, pInfo->mUnknown18,
                                            pResult, 0);
            }
        } else {
            pResult->mUnknown4 = fn_801F9718(db, pInfo->mTableRefs->mId, pInfo->mColRefs, pResult, 0);
        }
        break;
    case 0x15:
        fn_801FF8BC(pInfo, pLexer, result);
        fn_801FFEE4(pInfo);
        pResult->mUnknown4 = fn_801F9908(db, pInfo->mTableRefs, pInfo->mWhere, pResult, 0);
        break;
    case 0x13:
        fn_801FF8FC(pInfo, pLexer, result);
        pCursor = (struct QueryCursor *)pInfo->mUnknown1C;
        pResult->mUnknown4 = fn_801FA228(pCursor->mUnknown0, 1, pCursor->mUnknown4++, pInfo->mColRefs);
        if (pResult->mUnknown4 == 0) {
            fn_801FFDA8(pInfo);
            pResult->mUnknown0 = 1;
        } else {
            pResult->mUnknown0 = 0;
        }
        break;
    default:
        pResult->mUnknown4 = 3;
        break;
    }
}

int fn_802004CC(TDbParseInfo_801FC9D4 *pInfo, TDbLexer_801FCE10 *pLexer, int result, TDbIdxColumnDef_801FFFC4 *pOrder,
                int count)
{
    TDbToken_801FD2E8 *pNext = &pLexer->mTokens[1];
    int more;

    if (pNext->mType == 0x20) {
        TDbLexNext_801FD3C0(pLexer);
        TDbLexNext_801FD3C0(pLexer);
        do {
            more = 0;
            TDbLexNext_801FD3C0(pLexer);
            result = fn_801FD3C0(pInfo, pLexer, result, &pLexer->mTokens[0], &pOrder->mTableId,
                                 (unsigned int *)&pOrder->mId);
            if (pOrder->mTableId == -1) {
                pOrder->mTableId = pInfo->mTableRefs->mId;
            }
            switch (pLexer->mTokens[1].mType) {
            case 0x22:
                pOrder->mDescending = 0;
                TDbLexNext_801FD3C0(pLexer);
                break;
            case 0x23:
                pOrder->mDescending = 1;
                TDbLexNext_801FD3C0(pLexer);
                break;
            case 0xE:
                pOrder->mDescending = va_arg(pInfo->mArgs, int);
                TDbLexNext_801FD3C0(pLexer);
                break;
            default:
                pOrder->mDescending = 0;
                break;
            }
            if (pLexer->mTokens[1].mType == 0x38) {
                TDbLexNext_801FD3C0(pLexer);
                more = 1;
            }
            if (pOrder->mId != -1) {
                pOrder++;
            }
        } while (more);
    }
    pOrder->mTableId = -1;
    pOrder->mId = -1;
    return result;
}


void fn_8020071C(int db, TDbParseInfo_801FC9D4 *pInfo, struct QueryResult *pResult)
{
    TDbSQLAggregate_8020071C agg;
    int map[4];
    TDbLitRef_80205754 *pRef = pInfo->mColRefs;
    TDbLitRef_80205754 *pNextRef;
    TDbLitRef_80205754 *pCur;
    unsigned char i = 0;
    unsigned char j;
    int done = 1;
    int count;
    unsigned int op;

    while (pRef->mId != -1) {
        op = pRef->mColumn;
        pNextRef = pRef + 1;
        if (op != -1) {
            memset(map, -1, sizeof(map));
            op -= 0x2B;
            map[op] = i;
            pCur = pNextRef;
            j = i + 1;
            count = 1;
            for (; pCur->mId != -1; pCur++, j++) {
                if (pCur->mColumn != -1 && ((pCur->mTableId == pRef->mTableId && pCur->mId == pRef->mId) ||
                                              (pCur->mColumn == 0x2B && map[0] == -1))) {
                    op = pCur->mColumn - 0x2B;
                    map[op] = j;
                    count++;
                    done++;
                    pCur->mColumn = -1;
                }
            }
            if (count == 1 && map[0] != -1 && pInfo->mTableRefCount <= 2) {
                pResult->mUnknown4 = fn_801F9D70(db, pInfo->mTableRefs->mId, pInfo->mWhere, &pResult->mUnknown0);
                pInfo->mColRefs->mUnknown0 = pResult->mUnknown0;
            } else {
                pResult->mUnknown4 = fn_801FA844(db, pInfo->mTableRefs, pInfo->mWhere,
                                            (unsigned long long)pRef->mTableId << 32 | (unsigned int)pRef->mId,
                                            &agg, pResult);
                pResult->mUnknown0 = agg.mCount;
                if (map[0] != -1) {
                    pInfo->mColRefs[map[0]].mUnknown0 = agg.mCount;
                }
                if (map[1] != -1) {
                    pInfo->mColRefs[map[1]].mUnknown0 = agg.mMin;
                }
                if (map[2] != -1) {
                    pInfo->mColRefs[map[2]].mUnknown0 = agg.mMax;
                }
                if (map[3] != -1) {
                    pInfo->mColRefs[map[3]].mUnknown0 = agg.mSum;
                }
            }
            if (pResult->mUnknown4 != 0 && pResult->mUnknown4 != 0x17 && pResult->mUnknown4 != 0x15 && pResult->mUnknown4 != 0x14) {
                pResult->mUnknown0 = 0;
                break;
            }
            pRef->mColumn = -1;
            done++;
            if (done == pInfo->mColRefCount) {
                break;
            }
        }
        pRef = pNextRef;
        i++;
    }
    if (pResult->mUnknown4 == 0 || pResult->mUnknown4 == 0x17 || pResult->mUnknown4 == 0x15 || pResult->mUnknown4 == 0x14) {
        fn_801FFDA8(pInfo);
    }
}
