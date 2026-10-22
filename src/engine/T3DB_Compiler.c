#include <string.h>
#include <stdarg.h>
#include "engine/t3db.h"

typedef struct TDbSQLPool_801FC9D4 {
    unsigned int mItemSize;
    unsigned int mCount;
    unsigned int mUsed;
    void *mItems;
} TDbSQLPool_801FC9D4;

typedef struct TDbSQLResult_801FCE10 {
    unsigned short mUnknown0;
    short mUnknown2;
    int mErr;
    int mUnknown8;
    unsigned char mUnknownC[4];
} TDbSQLResult_801FCE10;

typedef struct TDbSQLCursor_801FCFA0 {
    void *mTable;
    unsigned short mUnknown4;
    int mUnknown8;
    struct TDbParseInfo_801FC9D4 *mInfo;
} TDbSQLCursor_801FCFA0;

typedef struct TDbSQLColRef_801FC9D4 {
    unsigned int mValue;
    unsigned int mTableId;
    int mColumn;
    unsigned int mUnknownC;
} TDbSQLColRef_801FC9D4;

typedef struct TDbSQLVar_801FD47C {
    unsigned int mValue;
    unsigned int mType;
    unsigned int mBits;
} TDbSQLVar_801FD47C;

typedef struct TDbSQLAggregate_8020071C {
    unsigned int mCount;
    unsigned int mMin;
    unsigned int mMax;
    unsigned int mSum;
} TDbSQLAggregate_8020071C;

typedef struct TDbParseInfo_801FC9D4 {
    va_list mArgs;
    unsigned int mUnknownC;
    unsigned int mState;
    void *mUnknown14;
    int mUnknown18;
    unsigned int mUnknown1C;
    unsigned int mColRefCount;
    TDbSQLColRef_801FC9D4 *mColRefs;
    TDbSQLVar_801FD47C *mVars;
    unsigned int mTableRefCount;
    TDbSQLTableRef_801FDC18 *mTableRefs;
    TDbExpr_801FAA00 *mWhere;
    unsigned int mExprCount;
    TDbExpr_801FAA00 *mExprs;
    TDbLexer_801FCE10 mLexer;
} TDbParseInfo_801FC9D4;

/* va_arg with signed register counts, where the first stack argument also closes the register area (gpr = 8);
   the va_arg of include/libc/stdarg.h has neither. */
#define TDB_VA_ARG(AP, TYPE) \
    (*({ \
        TYPE *__ptr; \
        if (__builtin_classify_type(*(TYPE *)0) == 8) { \
            signed char __fpr = (AP)->fpr; \
            if (__fpr < 8) { \
                __ptr = (TYPE *)((AP)->reg_save_area + 32 + __fpr * 8); \
                (AP)->fpr++; \
            } else { \
                __ptr = (TYPE *)(AP)->overflow_arg_area; \
                (AP)->overflow_arg_area = (char *)(__ptr + 1); \
            } \
        } else { \
            signed char __gpr = (AP)->gpr; \
            if (__gpr + sizeof(TYPE) / 4 <= 8) { \
                __ptr = (TYPE *)((AP)->reg_save_area + __gpr * 4); \
                (AP)->gpr++; \
            } else if (__gpr < 8) { \
                __ptr = (TYPE *)(AP)->overflow_arg_area; \
                (AP)->gpr = 8; \
                (AP)->overflow_arg_area = (char *)(__ptr + 1); \
            } else { \
                __ptr = (TYPE *)(AP)->overflow_arg_area; \
                (AP)->overflow_arg_area = (char *)(__ptr + 1); \
            } \
        } \
        __ptr; \
    }))

extern TDbSQLPool_801FC9D4 lbl_8039B43C[5];

extern int fn_801F9718(void *pDb, unsigned int tableId, TDbSQLColRef_801FC9D4 *pColRefs, TDbSQLResult_801FCE10 *pResult,
                       int a);
extern int fn_801F97D0(void *pDb, unsigned int tableId, void *pSrcDb, int srcTable, TDbSQLResult_801FCE10 *pResult,
                       int a);
extern int fn_801F9858(void *pDb, TDbSQLTableRef_801FDC18 *pTableRefs, TDbExpr_801FAA00 *pWhere,
                       TDbSQLColRef_801FC9D4 *pColRefs, void *pSrcDb, int srcTable, TDbSQLResult_801FCE10 *pResult,
                       int a);
extern int fn_801F9908(void *pDb, TDbSQLTableRef_801FDC18 *pTableRefs, TDbExpr_801FAA00 *pWhere,
                       TDbSQLResult_801FCE10 *pResult, int a);
extern int fn_801F9AB8(void *pDb, unsigned int tableId, TDbColumn_801FAA00 *pColumns, unsigned int *pCount);
extern int fn_801F9D70(void *pDb, unsigned int tableId, TDbExpr_801FAA00 *pWhere, TDbSQLResult_801FCE10 *pResult);
extern int fn_801F9E84(void *pDb, unsigned int tableId, unsigned int index, TDbIdxColumnDef_801FFFC4 *pOrder,
                       TDbExpr_801FAA00 *pWhere, unsigned char unique);
extern int fn_801FA0BC(void *pDb, TDbSQLTableRef_801FDC18 *pTableRefs, TDbExpr_801FAA00 *pWhere, void *pOrder,
                       void **ppTable, TDbSQLResult_801FCE10 *pResult);
extern int fn_801FA148(void *pTable);
extern int fn_801FA228(void *pTable, int a, unsigned short row, TDbSQLColRef_801FC9D4 *pColRefs);
extern int fn_801FA290(void *pDb, TDbSQLTableRef_801FDC18 *pTableRefs, TDbExpr_801FAA00 *pWhere,
                       TDbSQLColRef_801FC9D4 *pColRefs);
extern int fn_801FA3A0(void *pDb, TDbSQLTableRef_801FDC18 *pTableRefs, TDbExpr_801FAA00 *pWhere,
                       TDbSQLColRef_801FC9D4 *pColRefs, TDbSQLResult_801FCE10 *pResult, int a);
extern int fn_801FA5EC(void *a, int b, void *pTable, unsigned char *pData, TDbSQLResult_801FCE10 *pResult);
extern int fn_801FA844(void *pDb, TDbSQLTableRef_801FDC18 *pTableRefs, TDbExpr_801FAA00 *pWhere,
                       unsigned long long column, TDbSQLAggregate_8020071C *pAgg, TDbSQLResult_801FCE10 *pResult);
extern int fn_801FE5E0(TDbParseInfo_801FC9D4 *pInfo, TDbLexer_801FCE10 *pLexer, int result, TDbExpr_801FAA00 **ppExpr);
extern void fn_8020CCBC(TDbSQLColRef_801FC9D4 *pRefs, unsigned char *pData);

void fn_801FD0A4(TDbParseInfo_801FC9D4 *pInfo);
void fn_801FFEE4(TDbParseInfo_801FC9D4 *pInfo);
void fn_801FFFC4(TDbParseInfo_801FC9D4 *pInfo, TDbLexer_801FCE10 *pLexer, int result, TDbSQLResult_801FCE10 *pResult);
int fn_802004CC(TDbParseInfo_801FC9D4 *pInfo, TDbLexer_801FCE10 *pLexer, int result, TDbIdxColumnDef_801FFFC4 *pOrder,
                int count);
void fn_8020071C(void *pDb, TDbParseInfo_801FC9D4 *pInfo, TDbSQLResult_801FCE10 *pResult);

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

int fn_801FC9D4(unsigned int parseCount, unsigned int colRefCount, unsigned int countC, unsigned int tableRefCount,
                unsigned int countE)
{
    int err;

    err = TDbSQLPoolInit_801FC9D4(&lbl_8039B43C[2], 0xC, countC);
    if (err == 0) {
        err = TDbSQLPoolInit_801FC9D4(&lbl_8039B43C[1], sizeof(TDbSQLColRef_801FC9D4), colRefCount);
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

int fn_801FCE10(TDbSQLResult_801FCE10 *pResult, const char *pQuery, ...)
{
    TDbSQLResult_801FCE10 local;
    TDbParseInfo_801FC9D4 *pInfo;
    TDbLexer_801FCE10 *pLexer;

    pInfo = TDbSQLPoolGet_801FCE10(&lbl_8039B43C[0]);
    pLexer = &pInfo->mLexer;
    fn_801FD0A4(pInfo);
    if (pResult == 0) {
        pResult = &local;
    }
    pResult->mErr = 0;
    pResult->mUnknown8 = 0;
    pResult->mUnknown0 = 0;
    pResult->mUnknown2 = 0;
    pLexer->mSrc = (char *)pQuery;
    pLexer->mBufUsed = 0;
    fn_802009B0(pLexer, 0);
    va_start(pInfo->mArgs, pQuery);
    fn_801FFFC4(pInfo, pLexer, -1, pResult);
    if (pInfo->mState != 2) {
        TDbParseInfoRelease_801FCE10(pInfo);
    }
    return pResult->mErr;
}

int fn_801FCFA0(TDbSQLCursor_801FCFA0 *pCursor)
{
    TDbParseInfo_801FC9D4 *pInfo;
    unsigned int n;
    unsigned int i;

    if (pCursor->mInfo != 0) {
        pCursor->mInfo->mState = 10;
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
    pCursor->mInfo = 0;
    return fn_801FA148(pCursor->mTable);
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

void fn_801FD0E0(void *pDb, TDbParseInfo_801FC9D4 *pInfo, unsigned char *pData, int size)
{
    TDbColumn_801FAA00 columns[0xFE];
    unsigned int count;
    TDbColumn_801FAA00 *pColumn;
    TDbSQLColRef_801FC9D4 *pRef;

    count = 0xFE;
    memset(pData, 0, size);
    if (pInfo->mTableRefCount == 2) {
        fn_801F9AB8(pDb, pInfo->mTableRefs->mId, columns, &count);
        columns[count].mUnknown8 = -1;
        pInfo->mColRefs = TDbSQLPoolCur_801FD0E0(&lbl_8039B43C[1]);
        pRef = pInfo->mColRefs;
        for (pColumn = columns; pColumn->mUnknown8 != -1; pColumn++, pRef++) {
            pRef->mColumn = pColumn->mUnknown8;
            pRef->mTableId = pInfo->mTableRefs->mId;
            if (pColumn->mType <= TDB_TYPE_BINARY) {
                unsigned int bytes = pColumn->mBitCount >> 3;
                pRef->mValue = (unsigned int)pData;
                pData += bytes;
            }
            pInfo->mColRefCount++;
            TDbSQLPoolAdd_801FD0E0(&lbl_8039B43C[1], 1);
        }
        pRef->mColumn = -1;
        pRef->mTableId = -1;
    }
}

void fn_801FD200(void *pDb, TDbParseInfo_801FC9D4 *pInfo, void *pOrder, TDbSQLResult_801FCE10 *pResult)
{
    unsigned char row[0x7F0];
    unsigned char literals[0x800];
    void *pTable;

    pResult->mErr = fn_801FA0BC(pDb, pInfo->mTableRefs, pInfo->mWhere, pOrder, &pTable, pResult);
    if (pResult->mErr == 0 || pResult->mErr == 0x17 || pResult->mErr == 0x15 || pResult->mErr == 0x14) {
        if (pInfo->mColRefCount == 0) {
            fn_801FD0E0(pDb, pInfo, literals, sizeof(literals));
            fn_8020CCBC(pInfo->mColRefs, row);
        } else {
            fn_8020CCBC(pInfo->mColRefs, row);
        }
        pResult->mErr = fn_801FA5EC(pInfo->mUnknown14, pInfo->mUnknown18, pTable, row, pResult);
    }
    if (pResult->mErr == 0) {
        pResult->mErr = fn_801FA148(pTable);
    } else {
        fn_801FA148(pTable);
    }
}

unsigned int fn_801FD2E8(TDbParseInfo_801FC9D4 *pInfo, TDbToken_801FD2E8 *pToken)
{
    unsigned int value;

    value = -1;
    switch (pToken->mType) {
    case 0xC:
        value = TDB_VA_ARG(pInfo->mArgs, unsigned int);
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
        pVar->mValue = TDB_VA_ARG(pInfo->mArgs, unsigned int);
        pVar->mType = 2;
        pVar->mBits = 8;
        break;
    case 1:
        pVar->mValue = TDB_VA_ARG(pInfo->mArgs, unsigned int);
        pVar->mType = 2;
        pVar->mBits = 0x10;
        break;
    case 2:
        pVar->mValue = TDB_VA_ARG(pInfo->mArgs, unsigned int);
        pVar->mType = 2;
        pVar->mBits = 0x20;
        break;
    case 3:
        pVar->mValue = TDB_VA_ARG(pInfo->mArgs, unsigned int);
        pVar->mType = 3;
        pVar->mBits = 8;
        break;
    case 4:
        pVar->mValue = TDB_VA_ARG(pInfo->mArgs, unsigned int);
        pVar->mType = 3;
        pVar->mBits = 0x10;
        break;
    case 5:
        pVar->mValue = TDB_VA_ARG(pInfo->mArgs, unsigned int);
        pVar->mType = 3;
        pVar->mBits = 0x20;
        break;
    case 6:
        pVar->mValue = TDB_VA_ARG(pInfo->mArgs, unsigned int);
        pVar->mType = 4;
        pVar->mBits = 0x20;
        break;
    case 7:
        pVar->mValue = TDB_VA_ARG(pInfo->mArgs, unsigned int);
        pVar->mType = 4;
        pVar->mBits = 0x40;
        break;
    case 9:
        pVar->mValue = TDB_VA_ARG(pInfo->mArgs, unsigned int);
        pVar->mType = 1;
        break;
    case 8:
        pVar->mValue = TDB_VA_ARG(pInfo->mArgs, unsigned int);
        pVar->mType = 0;
        break;
    }
    return result;
}

int fn_801FD97C(TDbParseInfo_801FC9D4 *pInfo, TDbLexer_801FCE10 *pLexer, int result, TDbSQLColRef_801FC9D4 *pRef,
                TDbSQLVar_801FD47C *pVar, int mode)
{
    unsigned int table;
    unsigned int column;
    unsigned int none;

    none = 0;
    TDbLexNext_801FD3C0(pLexer);
    result = fn_801FD3C0(pInfo, pLexer, result, &pLexer->mTokens[0], &table, &column);
    pRef->mTableId = table;
    pRef->mColumn = column;
    pRef->mValue = none;
    if (pLexer->mTokens[1].mType == 0x17 && (mode == 0 || mode == 2)) {
        result = fn_801FD47C(pInfo, pLexer, result, pVar);
        if (pVar->mType == 0) {
            pRef->mValue = pVar->mValue;
        } else if (pVar->mType == 1) {
            pRef->mValue = pVar->mValue;
        }
    } else {
        pVar->mValue = none;
        pVar->mType = none;
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
    pInfo->mColRefs[n].mColumn = -1;
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
        *pOp = TDB_VA_ARG(pInfo->mArgs, unsigned int);
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
        pValue->mValue.i = TDB_VA_ARG(pInfo->mArgs, int);
        pValue->mType = TDB_TYPE_INT;
        break;
    case 1:
        pValue->mValue.i = TDB_VA_ARG(pInfo->mArgs, int);
        pValue->mType = TDB_TYPE_INT;
        break;
    case 2:
        pValue->mValue.i = TDB_VA_ARG(pInfo->mArgs, int);
        pValue->mType = TDB_TYPE_INT;
        break;
    case 3:
        pValue->mValue.u = TDB_VA_ARG(pInfo->mArgs, unsigned int);
        pValue->mType = TDB_TYPE_UINT;
        break;
    case 4:
        pValue->mValue.u = TDB_VA_ARG(pInfo->mArgs, unsigned int);
        pValue->mType = TDB_TYPE_UINT;
        break;
    case 5:
        pValue->mValue.u = TDB_VA_ARG(pInfo->mArgs, unsigned int);
        pValue->mType = TDB_TYPE_UINT;
        break;
    case 6:
    case 7:
        pValue->mValue.f = TDB_VA_ARG(pInfo->mArgs, double);
        pValue->mType = TDB_TYPE_FLOAT;
        break;
    case 9:
        pValue->mValue.p = TDB_VA_ARG(pInfo->mArgs, void *);
        pValue->mType = TDB_TYPE_BINARY;
        break;
    case 8:
        pValue->mValue.s = TDB_VA_ARG(pInfo->mArgs, char *);
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

static inline void TDbValueSetUInt_801FE534(TDbValue_801FDF28 *pValue, unsigned int value)
{
    pValue->mType = TDB_TYPE_UINT;
    pValue->mValue.u = value;
}

int fn_801FE534(TDbParseInfo_801FC9D4 *pInfo, TDbLexer_801FCE10 *pLexer, int result, TDbExpr_801FAA00 *pExpr)
{
    result = fn_801FDF28(pInfo, pLexer, result, &pExpr->mLeft);
    result = fn_801FDDC8(pInfo, pLexer, result, (unsigned int *)&pExpr->mOp);
    result = fn_801FDF28(pInfo, pLexer, result, &pExpr->mRight);
    if ((pExpr->mLeft.mType == TDB_TYPE_COLUMN && (int)pExpr->mLeft.mValue.l == -1) ||
        (pExpr->mRight.mType == TDB_TYPE_COLUMN && (int)pExpr->mRight.mValue.l == -1)) {
        pExpr->mOp = 0;
        TDbValueSetUInt_801FE534(&pExpr->mLeft, 1);
        TDbValueSetUInt_801FE534(&pExpr->mRight, 1);
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
        *ppExpr = pExpr = TDB_VA_ARG(pInfo->mArgs, TDbExpr_801FAA00 *);
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

int fn_801FEA04(TDbParseInfo_801FC9D4 *pInfo, TDbLexer_801FCE10 *pLexer, int result, TDbSQLColRef_801FC9D4 *pRef,
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
        value = TDB_VA_ARG(pInfo->mArgs, unsigned int);
        pVar->mType = TDB_TYPE_INT;
        pVar->mBits = 1;
        break;
    case 1:
        value = TDB_VA_ARG(pInfo->mArgs, unsigned int);
        pVar->mType = TDB_TYPE_INT;
        pVar->mBits = 2;
        break;
    case 2:
        value = TDB_VA_ARG(pInfo->mArgs, unsigned int);
        pVar->mType = TDB_TYPE_INT;
        pVar->mBits = 4;
        break;
    case 3:
        value = TDB_VA_ARG(pInfo->mArgs, unsigned int);
        pVar->mType = TDB_TYPE_UINT;
        pVar->mBits = 1;
        break;
    case 4:
        value = TDB_VA_ARG(pInfo->mArgs, unsigned int);
        pVar->mType = TDB_TYPE_UINT;
        pVar->mBits = 2;
        break;
    case 5:
        value = TDB_VA_ARG(pInfo->mArgs, unsigned int);
        pVar->mType = TDB_TYPE_UINT;
        pVar->mBits = 4;
        break;
    case 6:
        f = TDB_VA_ARG(pInfo->mArgs, double);
        pVar->mType = TDB_TYPE_FLOAT;
        value = *(unsigned int *)&f;
        pVar->mBits = 4;
        break;
    case 7:
        f = TDB_VA_ARG(pInfo->mArgs, double);
        pVar->mType = TDB_TYPE_FLOAT;
        value = *(unsigned int *)&f;
        pVar->mBits = 4;
        break;
    case 9:
        value = TDB_VA_ARG(pInfo->mArgs, unsigned int);
        pVar->mType = TDB_TYPE_BINARY;
        break;
    case 8:
        value = TDB_VA_ARG(pInfo->mArgs, unsigned int);
        pVar->mType = TDB_TYPE_STRING;
        break;
    case 0x30:
        value = (unsigned int)pLexer->mTokens[0].mValue;
        pVar->mType = TDB_TYPE_INT;
        pVar->mBits = 4;
        break;
    case 0x31:
        value = (unsigned int)pLexer->mTokens[0].mValue;
        pVar->mType = TDB_TYPE_FLOAT;
        pVar->mBits = 4;
        break;
    case 0x32:
        value = (unsigned int)pLexer->mTokens[0].mValue;
        pVar->mType = TDB_TYPE_STRING;
        pVar->mBits = 4;
        break;
    }
    pRef->mValue = value;
    pRef->mTableId = table;
    pRef->mColumn = column;
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
    pInfo->mColRefs[n].mColumn = -1;
    return result;
}

int fn_801FF0D4(TDbParseInfo_801FC9D4 *pInfo, TDbLexer_801FCE10 *pLexer, int result)
{
    TDbLexNext_801FD3C0(pLexer);
    return fn_801FEF44(pInfo, pLexer, result);
}

int fn_801FF13C(TDbParseInfo_801FC9D4 *pInfo, TDbLexer_801FCE10 *pLexer, int result)
{
    TDbSQLColRef_801FC9D4 *pRef;
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
        pRef->mValue = 0;
        if (pLexer->mTokens[0].mType == 0x41) {
            pRef->mTableId = 0;
            pRef->mColumn = 1;
            pRef->mValue = 0;
        } else {
            result = fn_801FD3C0(pInfo, pLexer, result, &pLexer->mTokens[0], &pRef->mTableId,
                                 (unsigned int *)&pRef->mColumn);
            pRef->mValue = 1;
        }
        pRef->mUnknownC = op;
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
    pInfo->mColRefs[n].mColumn = -1;
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
            pInfo->mUnknown14 = (void *)id;
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
    TDbSQLCursor_801FCFA0 *pCursor;
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
        pInfo->mUnknown1C = TDB_VA_ARG(pInfo->mArgs, unsigned int);
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
        pCursor = TDB_VA_ARG(pInfo->mArgs, TDbSQLCursor_801FCFA0 *);
        pInfo->mUnknown1C = (unsigned int)pCursor;
        if (pLexer->mTokens[0].mType == 0x28) {
            pInfo->mState = 2;
            pCursor->mInfo = pInfo;
        } else {
            pInfo->mState = 1;
            pCursor->mInfo = 0;
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
    TDbSQLCursor_801FCFA0 *pCursor;
    TDbParseInfo_801FC9D4 *pOther;

    TDbLexNext_801FD3C0(pLexer);
    TDbLexNext_801FD3C0(pLexer);
    pInfo->mState = 9;
    pCursor = TDB_VA_ARG(pInfo->mArgs, TDbSQLCursor_801FCFA0 *);
    pInfo->mUnknown1C = (unsigned int)pCursor;
    pOther = pCursor->mInfo;
    if (pOther != 0) {
        pInfo->mColRefs = pOther->mColRefs;
        pInfo->mVars = pOther->mVars;
    } else {
        result = fn_801FDA78(pInfo, pLexer, result, 2);
        pInfo->mTableRefs = TDbSQLPoolCur_801FD0E0(&lbl_8039B43C[3]);
        pInfo->mTableRefCount++;
        TDbSQLPoolAdd_801FD0E0(&lbl_8039B43C[3], 1);
        pInfo->mTableRefs->mId = ((TDbSQLCursor_801FCFA0 *)pInfo->mUnknown1C)->mUnknown8;
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
        pInfo->mUnknown14 = (void *)id;
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
    TDbSQLColRef_801FC9D4 *pRef = pInfo->mColRefs;
    TDbSQLVar_801FD47C *pVar = pInfo->mVars;
    void *pDst;

    while (pRef->mColumn != -1) {
        pDst = (void *)pVar->mValue;
        if (pDst != 0) {
            switch (pVar->mType) {
            case TDB_TYPE_STRING:
            case TDB_TYPE_BINARY:
                break;
            case TDB_TYPE_INT:
                if (pVar->mBits <= 8) {
                    *(unsigned char *)pDst = pRef->mValue;
                } else if (pVar->mBits <= 16) {
                    *(unsigned short *)pDst = pRef->mValue;
                } else if (pVar->mBits <= 32) {
                    *(unsigned int *)pDst = pRef->mValue;
                }
                break;
            case TDB_TYPE_UINT:
                if (pVar->mBits <= 8) {
                    *(unsigned char *)pDst = pRef->mValue;
                } else if (pVar->mBits <= 16) {
                    *(unsigned short *)pDst = pRef->mValue;
                } else if (pVar->mBits <= 32) {
                    *(unsigned int *)pDst = pRef->mValue;
                }
                break;
            case TDB_TYPE_FLOAT:
                if (pVar->mBits <= 32) {
                    *(float *)pDst = *(float *)&pRef->mValue;
                } else if (pVar->mBits <= 64) {
                    *(double *)pDst = *(float *)&pRef->mValue;
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
    TDbSQLColRef_801FC9D4 *pRef;

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

void fn_801FFFC4(TDbParseInfo_801FC9D4 *pInfo, TDbLexer_801FCE10 *pLexer, int result, TDbSQLResult_801FCE10 *pResult)
{
    TDbIdxColumnDef_801FFFC4 order[8];
    unsigned char unique;
    TDbSQLCursor_801FCFA0 *pCursor;
    void *pDb = 0;

    if (pLexer->mTokens[0].mType == 0x1F) {
        TDbLexNext_801FD3C0(pLexer);
        pDb = (void *)fn_801FD2E8(pInfo, &pLexer->mTokens[0]);
        pInfo->mUnknown14 = pDb;
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
            pResult->mErr = fn_801F9E84(pDb, pInfo->mTableRefs->mId, pInfo->mUnknown1C, order, pInfo->mWhere, unique);
            break;
        case 5:
            ((TDbSQLCursor_801FCFA0 *)pInfo->mUnknown1C)->mUnknown4 = 0;
            fn_801FD200(pDb, pInfo, order, pResult);
            if (pResult->mErr == 0 || pResult->mErr == 0x17 || pResult->mErr == 0x15 || pResult->mErr == 0x14) {
                pInfo->mTableRefs[0].mId = pInfo->mUnknown18;
                pInfo->mTableRefs[0].mJoinType = 2;
                pInfo->mTableRefs[0].mExpr = 0;
                pInfo->mTableRefs[1].mId = -1;
                pInfo->mTableRefs[1].mJoinType = 2;
                pInfo->mTableRefs[1].mExpr = 0;
                ((TDbSQLCursor_801FCFA0 *)pInfo->mUnknown1C)->mUnknown8 = pInfo->mUnknown18;
                pResult->mErr = fn_801FA0BC(pInfo->mUnknown14, pInfo->mTableRefs, 0, order,
                                            (void **)pInfo->mUnknown1C, pResult);
            }
            break;
        case 1:
        case 2:
            ((TDbSQLCursor_801FCFA0 *)pInfo->mUnknown1C)->mUnknown4 = 0;
            ((TDbSQLCursor_801FCFA0 *)pInfo->mUnknown1C)->mUnknown8 = pInfo->mTableRefs->mId;
            pResult->mErr = fn_801FA0BC(pDb, pInfo->mTableRefs, pInfo->mWhere, order, (void **)pInfo->mUnknown1C,
                                        pResult);
            if (pResult->mErr != 0 && pResult->mErr != 0x17 && pResult->mErr != 0x15 && pResult->mErr != 0x14 &&
                pInfo->mState == 2) {
                ((TDbSQLCursor_801FCFA0 *)pInfo->mUnknown1C)->mInfo = 0;
                pInfo->mState = 1;
            }
            break;
        }
        break;
    case 0x11:
        result = fn_801FF390(pInfo, pLexer, result);
        fn_801FFEE4(pInfo);
        if (pInfo->mState == 8) {
            fn_8020071C(pDb, pInfo, pResult);
        } else if (pInfo->mUnknown18 != -1) {
            fn_802004CC(pInfo, pLexer, result, order, 8);
            fn_801FD200(pDb, pInfo, order, pResult);
        } else {
            pResult->mErr = fn_801FA290(pDb, pInfo->mTableRefs, pInfo->mWhere, pInfo->mColRefs);
            if (pResult->mErr == 0) {
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
        pResult->mErr = fn_801FA3A0(pDb, pInfo->mTableRefs, pInfo->mWhere, pInfo->mColRefs, pResult, 0);
        break;
    case 0x12:
        fn_801FFB68(pInfo, pLexer, result);
        fn_801FFEE4(pInfo);
        if (pInfo->mState == 7) {
            pResult->mErr = fn_801F9858(pDb, pInfo->mTableRefs, pInfo->mWhere, pInfo->mColRefs, pInfo->mUnknown14,
                                        pInfo->mUnknown18, pResult, 0);
        } else if (pInfo->mState == 6) {
            if (pInfo->mWhere != 0 || pInfo->mTableRefCount > 2) {
                unsigned char data[0x800];

                fn_801FD0E0(pDb, pInfo, data, sizeof(data));
                pResult->mErr = fn_801F9858(pDb, pInfo->mTableRefs, pInfo->mWhere, pInfo->mColRefs,
                                            pInfo->mUnknown14, pInfo->mUnknown18, pResult, 0);
            } else {
                pResult->mErr = fn_801F97D0(pDb, pInfo->mTableRefs->mId, pInfo->mUnknown14, pInfo->mUnknown18,
                                            pResult, 0);
            }
        } else {
            pResult->mErr = fn_801F9718(pDb, pInfo->mTableRefs->mId, pInfo->mColRefs, pResult, 0);
        }
        break;
    case 0x15:
        fn_801FF8BC(pInfo, pLexer, result);
        fn_801FFEE4(pInfo);
        pResult->mErr = fn_801F9908(pDb, pInfo->mTableRefs, pInfo->mWhere, pResult, 0);
        break;
    case 0x13:
        fn_801FF8FC(pInfo, pLexer, result);
        pCursor = (TDbSQLCursor_801FCFA0 *)pInfo->mUnknown1C;
        pResult->mErr = fn_801FA228(pCursor->mTable, 1, pCursor->mUnknown4++, pInfo->mColRefs);
        if (pResult->mErr == 0) {
            fn_801FFDA8(pInfo);
            pResult->mUnknown0 = 1;
        } else {
            pResult->mUnknown0 = 0;
        }
        break;
    default:
        pResult->mErr = 3;
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
                pOrder->mAscending = 0;
                TDbLexNext_801FD3C0(pLexer);
                break;
            case 0x23:
                pOrder->mAscending = 1;
                TDbLexNext_801FD3C0(pLexer);
                break;
            case 0xE:
                pOrder->mAscending = TDB_VA_ARG(pInfo->mArgs, int);
                TDbLexNext_801FD3C0(pLexer);
                break;
            default:
                pOrder->mAscending = 0;
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


void fn_8020071C(void *pDb, TDbParseInfo_801FC9D4 *pInfo, TDbSQLResult_801FCE10 *pResult)
{
    TDbSQLAggregate_8020071C agg;
    int map[4];
    TDbSQLColRef_801FC9D4 *pRef = pInfo->mColRefs;
    TDbSQLColRef_801FC9D4 *pNextRef;
    TDbSQLColRef_801FC9D4 *pCur;
    unsigned char i = 0;
    unsigned char j;
    int done = 1;
    int count;
    unsigned int op;

    while (pRef->mColumn != -1) {
        op = pRef->mUnknownC;
        pNextRef = pRef + 1;
        if (op != -1) {
            memset(map, -1, sizeof(map));
            op -= 0x2B;
            map[op] = i;
            pCur = pNextRef;
            j = i + 1;
            count = 1;
            for (; pCur->mColumn != -1; pCur++, j++) {
                if (pCur->mUnknownC != -1 && ((pCur->mTableId == pRef->mTableId && pCur->mColumn == pRef->mColumn) ||
                                              (pCur->mUnknownC == 0x2B && map[0] == -1))) {
                    op = pCur->mUnknownC - 0x2B;
                    map[op] = j;
                    count++;
                    done++;
                    pCur->mUnknownC = -1;
                }
            }
            if (count == 1 && map[0] != -1 && pInfo->mTableRefCount <= 2) {
                pResult->mErr = fn_801F9D70(pDb, pInfo->mTableRefs->mId, pInfo->mWhere, pResult);
                pInfo->mColRefs->mValue = pResult->mUnknown0;
            } else {
                pResult->mErr = fn_801FA844(pDb, pInfo->mTableRefs, pInfo->mWhere,
                                            (unsigned long long)pRef->mTableId << 32 | (unsigned int)pRef->mColumn,
                                            &agg, pResult);
                pResult->mUnknown0 = agg.mCount;
                if (map[0] != -1) {
                    pInfo->mColRefs[map[0]].mValue = agg.mCount;
                }
                if (map[1] != -1) {
                    pInfo->mColRefs[map[1]].mValue = agg.mMax;
                }
                if (map[2] != -1) {
                    pInfo->mColRefs[map[2]].mValue = agg.mMin;
                }
                if (map[3] != -1) {
                    pInfo->mColRefs[map[3]].mValue = agg.mSum;
                }
            }
            if (pResult->mErr != 0 && pResult->mErr != 0x17 && pResult->mErr != 0x15 && pResult->mErr != 0x14) {
                pResult->mUnknown0 = 0;
                break;
            }
            pRef->mUnknownC = -1;
            done++;
            if (done == pInfo->mColRefCount) {
                break;
            }
        }
        pRef = pNextRef;
        i++;
    }
    if (pResult->mErr == 0 || pResult->mErr == 0x17 || pResult->mErr == 0x15 || pResult->mErr == 0x14) {
        fn_801FFDA8(pInfo);
    }
}
