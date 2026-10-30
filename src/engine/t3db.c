#include "engine/t3db_index.h"
#include "engine/fn_801F8D60.h"
#include "engine/fn_801F9134.h"
typedef struct TDbDefault_803E944C {
    int mDb;
    int mTbl;
} TDbDefault_803E944C;

typedef struct TDbIdx_801F9E84 {
    int mUnk0;
    struct TDbIdx_801F9E84 *pNext;
    int mUnk8;
    int mId;
} TDbIdx_801F9E84;

typedef struct TDbIdxCol_801F9E84 {
    int mUnk0;
    int mCol;
    int mUnk8;
    unsigned char mIdx;
} TDbIdxCol_801F9E84;

typedef struct TDbColDef_801F9AB8 {
    int mType;
    int mUnk4;
    int mCol;
    int mSize;
} TDbColDef_801F9AB8;

typedef struct TDbTbl_801F88F0 {
    int mUnk0;
    struct TDbTbl_801F88F0 *pNext;
    struct TDbIdx_801F9E84 *pIdx;
    char mUnkC[0x10];
    int mId;
    char mUnk20[8];
    unsigned int mFlags;
    char mUnk2C[0x14];
    unsigned short mUnk40;
    unsigned short mUnk42;
    unsigned short mUnk44;
    unsigned short mUnk46;
    unsigned char mUnk48[2];
    unsigned char mNumCols;
    TDbColDef_801F9AB8 mCols[1];
} TDbTbl_801F88F0;

typedef struct TDbDb_801F88F0 {
    struct TDbDb_801F88F0 *pNext;
    TDbTbl_801F88F0 *pTables;
    int mId;
    int mHeap;
    unsigned char mState;
} TDbDb_801F88F0;

typedef struct TDbQry_801F89B8 {
    TDbDb_801F88F0 *pDb;
    struct TDbQry_801F89B8 *pNext;
    int mUnk8;
    int mRef;
} TDbQry_801F89B8;

typedef struct TDbStrFuncs_801F8A54 {
    unsigned int (*pStrlen)(const char *s);
    int (*pStrncmp)(const char *a, const char *b, unsigned int n);
    char *(*pStrcpy)(char *dst, const char *src);
    char *(*pStrncpy)(char *dst, const char *src, unsigned int n);
} TDbStrFuncs_801F8A54;

typedef struct TDbInitParms_801F8A0C {
    int mHeapSize;
    int mPool0Max;
    int mPool0Grow;
    int mPool1Max;
    int mPool1Grow;
    int mPool2Max;
    int mPool2Grow;
    int mIdxMax;
    int mIdxGrow;
    TDbStrFuncs_801F8A54 *pStrFuncs;
} TDbInitParms_801F8A0C;

typedef struct TDbFile_801F9064 {
    int mFile;
    int mUnk4;
} TDbFile_801F9064;

typedef struct TDbAsync_801F9228 {
    int mDb;
    int mUnk4;
    int *pResult;
    int mUnkC;
    int mUnk10;
    void (*pDone)(void);
    int mIsLoad;
} TDbAsync_801F9228;

typedef struct TDbJob_801F9228 {
    int mUnk0;
    int mUnk4;
    TDbAsync_801F9228 *pReq;
    int mUnkC;
    void (*pRun)(TDbAsync_801F9228 *pReq);
    int mUnk14;
} TDbJob_801F9228;

typedef struct TDbResult_801F9718 {
    unsigned short mRows;
    int mErr;
    int mUnk8;
    int mUnkC;
} TDbResult_801F9718;

#include "engine/t3db_cols.h"

typedef struct TDbTerm_801FA4B0 {
    char mUnk0[0x28];
} TDbTerm_801FA4B0;

typedef struct TDbQrySel_801F9858 {
    TDbTbl_801F88F0 *pTbl;
    char mUnk4[0x24];
    int mUnk28;
    char mUnk2C[0x24];
    int mUnk50;
    char mUnk54[0x24];
    int mUnk78;
    char mUnk7C[0x24];
    int mUnkA0;
    char mUnkA4[0x24];
    int mUnkC8;
    char mUnkCC[0x24];
} TDbQrySel_801F9858;

typedef struct TDbQryRow_801F9858 {
    unsigned short mUnk0;
    char mUnk2[0x12];
    int mUnk14;
    char mUnk18[0x28];
} TDbQryRow_801F9858;

typedef struct TDbQryBuf_801F9858 {
    int mUnk0;
    int mUnk4;
    TDbQrySel_801F9858 mSel;
    TDbQryRow_801F9858 mRow;
} TDbQryBuf_801F9858;

typedef struct TDbRowInfo_801FA290 {
    int mUnk0;
    int mUnk4;
    int mUnk8;
    int mUnkC;
} TDbRowInfo_801FA290;

typedef struct TDbSelCol_801FA4B0 {
    int mUnk0;
    int mCol;
} TDbSelCol_801FA4B0;


typedef struct TDbEvent_801F8A54 {
    int mType;
    int mUnk4;
    int mUnk8;
} TDbEvent_801F8A54;

typedef struct TDbPool_803E9654 {
    char mUnk0[0x1C];
} TDbPool_803E9654;

extern TDbDefault_803E944C lbl_803E944C[];
extern TDbDefault_803E944C lbl_803E95DC[15];
extern TDbPool_803E9654 lbl_803E9654;
extern TDbPool_803E9654 lbl_803E9670;
extern TDbPool_803E9654 lbl_803E968C;
extern TDbPool_803E9654 lbl_803E96A8;
extern unsigned int (*lbl_803EBE70)(const char *s);
extern int (*lbl_803EBE74)(const char *a, const char *b, unsigned int n);
extern char *(*lbl_803EBE78)(char *dst, const char *src);
extern char *(*lbl_803EBE7C)(char *dst, const char *src, unsigned int n);
extern void (*lbl_803EBE80)(TDbEvent_801F8A54 *pEvent);
extern int lbl_803EBE8C;

extern unsigned int strlen(const char *s);
extern int strncmp(const char *a, const char *b, unsigned int n);
extern char *strcpy(char *dst, const char *src);
extern char *strncpy(char *dst, const char *src, unsigned int n);
extern int fn_80203444(TDbPool_803E9654 *pPool, int heap, int size, unsigned short max, unsigned short grow);
extern void fn_8020353C(TDbPool_803E9654 *pPool);
extern int fn_8020D194(int a, int size, int *pHeap);
extern void fn_8020D1A8(int heap);
extern int fn_8020D1B0(int heap, int size, void *ppOut);
extern int fn_801F9014(int db);
extern int fn_801F95C8(void);
extern int fn_801FC5FC(TDbDb_801F88F0 *pDb, int a, int b);
extern TDbTbl_801F88F0 *fn_8020BA48(TDbDb_801F88F0 *pDb, int tbl);
void fn_801F93AC(TDbAsync_801F9228 *pReq);
extern int _TDbExprPrepare(TDbTerm_801FA4B0 *pTerm, int *pOut, TDbTbl_801F88F0 **ppTbl, int b, int c);
extern void _TDbExprTest(int a, TDbRowInfo_801FA290 *pInfo, TDbQrySel_801F9858 *pSel, TDbQryRow_801F9858 *pRow);
extern int fn_80208094(TDbQryBuf_801F9858 *pQry);
extern int fn_80209E40(TDbQryBuf_801F9858 *pQry, int out);
extern void fn_8020A3A0(TDbQryBuf_801F9858 *pQry, int out);
extern int fn_8020AD1C(int a, TDbQryBuf_801F9858 *pQry, int d, int mode, TDbResult_801F9718 *pRes);
extern int fn_8020AE88(int a, TDbQryBuf_801F9858 *pQry, TDbSelCol_801FA4B0 *pCols, int *pHandles, TDbResult_801F9718 *pRes);
extern void fn_802055CC(int a);
extern int fn_802075F4(TDbQryBuf_801F9858 *pQry, int a);
extern int fn_80207988(TDbQryBuf_801F9858 *pQry, int a);
extern int fn_80207E24(TDbQryBuf_801F9858 *pQry, int a, int b);
extern int fn_802032D8(TDbIdx_801F9E84 *pIdx);
extern int fn_8020840C(int a, int b, int c, int d, int ref, TDbResult_801F9718 *pRes);
extern int fn_802088A8(TDbQry_801F89B8 *pQry);
extern int fn_802088FC(TDbQry_801F89B8 *pQry);
extern int fn_8020925C(TDbDb_801F88F0 *pDb, int tbl, TDbQry_801F89B8 *pQry, int a, int b);
extern int fn_8020A660(int a, TDbQryBuf_801F9858 *pQry, int d, int e, int f, TDbResult_801F9718 *pRes);
extern int fn_8020B094(int a, int b, int c, int d, int e, int f, int g, TDbResult_801F9718 *pRes);
extern int fn_8020B97C(TDbTbl_801F88F0 *pTbl, int col);
extern int fn_8020BFA4(TDbTbl_801F88F0 *pTbl, TDbCol_801F9718 *pCols, TDbResult_801F9718 *pRes);
extern int fn_8020C764(TDbTbl_801F88F0 *pSrc, TDbTbl_801F88F0 *pDst, TDbResult_801F9718 *pRes);
extern int fn_80207B8C(int a, int b, int c, TDbQryBuf_801F9858 *pQry);
extern void fn_80207DB4(TDbQryBuf_801F9858 *pQry);
extern int fn_80208204(int a, TDbQryBuf_801F9858 *pQry, TDbResult_801F9718 *pRes);
extern int fn_8020A908(int a, TDbQryBuf_801F9858 *pQry, int d, TDbTbl_801F88F0 *pTbl, TDbResult_801F9718 *pRes);
extern int fn_801FBFEC(TDbDb_801F88F0 *pDb, void *pFile, int a, int b, int c);
extern int fn_802087D4(TDbQry_801F89B8 *pQry);
extern int fn_8020BD90(TDbTbl_801F88F0 *pTbl);
extern void fn_8020D2AC(int heap, void *p, int size);
extern int lbl_803EBE84;
extern TDbDb_801F88F0 *lbl_803EBE88;
extern TDbQry_801F89B8 *lbl_803EBE90;

static inline void Notify_801F8A54(int type, int a, int b)
{
    TDbEvent_801F8A54 event;

    if (lbl_803EBE80 != 0) {
        event.mType = type;
        event.mUnk4 = a;
        event.mUnk8 = b;
        lbl_803EBE80(&event);
    }
}

static inline TDbDb_801F88F0 *FindDb_801F88F0(int db)
{
    TDbDb_801F88F0 *pDb;

    for (pDb = lbl_803EBE88; pDb != 0; pDb = pDb->pNext) {
        if (db == pDb->mId) {
            break;
        }
    }
    if (pDb != 0 && pDb->mState == 0x1F) {
        pDb = 0;
    }
    return pDb;
}

static int fn_801F8878(int tbl)
{
    int i;
    int db;
    int fallback;

    i = lbl_803EBE84;
    db = 0;
    fallback = 0;
    while (i != 0) {
        i--;
        if (tbl == lbl_803E944C[i].mTbl) {
            db = lbl_803E944C[i].mDb;
            break;
        }
        if (fallback == 0 && lbl_803E944C[i].mTbl == 0) {
            fallback = lbl_803E944C[i].mDb;
        }
    }
    if (db == 0) {
        db = fallback;
    }
    return db;
}

int fn_801F88F0(int db, int tbl, TDbDb_801F88F0 **ppDb, TDbTbl_801F88F0 **ppTbl)
{
    TDbDb_801F88F0 *pDb;
    int err;

    err = 0;
    if (db == 0) {
        db = fn_801F8878(tbl);
    }
    for (pDb = lbl_803EBE88; pDb != 0; pDb = pDb->pNext) {
        if (db == pDb->mId) {
            break;
        }
    }
    if (pDb != 0 && pDb->mState == 0x1F) {
        pDb = 0;
    }
    *ppDb = pDb;
    if (pDb != 0) {
        for (*ppTbl = pDb->pTables; *ppTbl != 0; *ppTbl = (*ppTbl)->pNext) {
            if (tbl == (*ppTbl)->mId) {
                break;
            }
        }
        if (*ppTbl == 0) {
            err = 7;
        }
    } else {
        err = 5;
    }
    return err;
}

static int fn_801F89B8(void)
{
    TDbQry_801F89B8 *pHead;
    TDbQry_801F89B8 *pQry;
    int ref;

    ref = 1;
    pHead = lbl_803EBE90;
    pQry = pHead;
    while (pQry != 0) {
        if (ref == pQry->mRef) {
            if (ref == 255) {
                ref = 0;
                break;
            }
            ref++;
            pQry = pHead;
        } else {
            pQry = pQry->pNext;
        }
    }
    return ref;
}

void fn_801F8A0C(TDbInitParms_801F8A0C *pParms)
{
    if (pParms != 0) {
        pParms->mHeapSize = 0;
        pParms->mPool0Max = 100;
        pParms->mPool0Grow = 20;
        pParms->mPool1Max = 10;
        pParms->mPool1Grow = 10;
        pParms->mPool2Max = 5;
        pParms->mPool2Grow = 5;
        pParms->mIdxMax = 100;
        pParms->mIdxGrow = 20;
        pParms->pStrFuncs = 0;
    }
}

int fn_801F8A54(TDbInitParms_801F8A0C *pParms)
{
    TDbStrFuncs_801F8A54 *pFuncs;
    int err;
    int i;

    for (i = 0; i < 15; i++) {
        lbl_803E95DC[i].mDb = 0;
        lbl_803E95DC[i].mTbl = 0;
    }
    lbl_803EBE84 = 0;
    lbl_803EBE88 = 0;
    err = fn_8020D194(-1, pParms->mHeapSize, &lbl_803EBE8C);
    if (err == 0) {
        Notify_801F8A54(err, -1, -1);
        err = fn_80203444(&lbl_803E9654, lbl_803EBE8C, 0x28, pParms->mPool0Max, pParms->mPool0Grow);
        if (err == 0) {
            if (fn_80203444(&lbl_803E9670, lbl_803EBE8C, 0x1C, pParms->mPool1Max, pParms->mPool1Grow) == 0) {
                if (fn_80203444(&lbl_803E968C, lbl_803EBE8C, 0x134, pParms->mPool2Max, pParms->mPool2Grow) == 0) {
                    goto pools_done;
                }
                fn_8020353C(&lbl_803E9670);
            }
            fn_8020353C(&lbl_803E9654);
        pools_done:
            err = fn_80203444(&lbl_803E96A8, lbl_803EBE8C, 0x54, pParms->mIdxMax, pParms->mIdxGrow);
        }
        if (err != 0) {
            fn_8020D1A8(lbl_803EBE8C);
        }
        Notify_801F8A54(4, -1, -1);
        pFuncs = pParms->pStrFuncs;
        if (pFuncs != 0) {
            lbl_803EBE70 = (pFuncs->pStrlen != 0) ? pFuncs->pStrlen : strlen;
            lbl_803EBE74 = (pFuncs->pStrncmp != 0) ? pFuncs->pStrncmp : strncmp;
            lbl_803EBE78 = (pFuncs->pStrcpy != 0) ? pFuncs->pStrcpy : strcpy;
            lbl_803EBE7C = (pFuncs->pStrncpy != 0) ? pFuncs->pStrncpy : strncpy;
        } else {
            lbl_803EBE70 = strlen;
            lbl_803EBE74 = strncmp;
            lbl_803EBE78 = strcpy;
            lbl_803EBE7C = strncpy;
        }
    }
    return err;
}

void fn_801F8C64(void)
{
    if (lbl_803EBE84 != -1) {
        while (lbl_803EBE88 != 0) {
            fn_801F8EEC(lbl_803EBE88->mId);
        }
        fn_8020353C(&lbl_803E9670);
        fn_8020353C(&lbl_803E9654);
        fn_8020353C(&lbl_803E96A8);
        fn_8020353C(&lbl_803E968C);
        fn_8020D1A8(lbl_803EBE8C);
        lbl_803EBE84 = -1;
    }
}

int fn_801F8CE8(int *pDb)
{
    unsigned char i;

    if (pDb == 0) {
        return 3;
    }
    for (i = 0; i < 127; i++) {
        *pDb = i | 0xFFFFFF00;
        if (fn_801F9014(*pDb) == 5) {
            return 0;
        }
    }
    *pDb = -1;
    return 5;
}

int fn_801F8D60(int db, int size)
{
    TDbDb_801F88F0 *pFind;
    TDbDb_801F88F0 *pDb;
    int heap;
    int err;

    for (pFind = lbl_803EBE88; pFind != 0; pFind = pFind->pNext) {
        if (db == pFind->mId) {
            break;
        }
    }
    pDb = pFind;
    if (pDb == 0) {
        err = fn_8020D194(db, size, &heap);
        if (err == 0) {
            Notify_801F8A54(1, db, -1);
            err = fn_8020D1B0(heap, 0x14, &pDb);
            Notify_801F8A54(4, -1, -1);
            if (err != 0) {
                fn_8020D1A8(heap);
            }
        }
    } else {
        err = 4;
    }
    if (err == 0) {
        pDb->pTables = 0;
        pDb->mId = db;
        pDb->mHeap = heap;
        pDb->mState = 0;
        if (lbl_803EBE88 == 0) {
            lbl_803EBE88 = pDb;
        } else {
            pDb->pNext = lbl_803EBE88;
            while (pDb->pNext->pNext != 0) {
                pDb->pNext = pDb->pNext->pNext;
            }
            pDb->pNext->pNext = pDb;
        }
        pDb->pNext = 0;
    }
    return err;
}

int fn_801F8EEC(int db)
{
    TDbDb_801F88F0 *pDb;
    TDbDb_801F88F0 *pPrev;
    TDbQry_801F89B8 *pQry;
    TDbQry_801F89B8 *pNextQry;
    TDbTbl_801F88F0 *pTbl;
    TDbTbl_801F88F0 *pNextTbl;
    int heap;
    int err;

    err = 0;
    pDb = FindDb_801F88F0(db);
    if (pDb != 0) {
        for (pQry = lbl_803EBE90; pQry != 0; pQry = pNextQry) {
            pNextQry = pQry->pNext;
            if (pDb == pQry->pDb) {
                err = fn_802087D4(pQry);
                if (err != 0) {
                    break;
                }
            }
        }
        while ((pTbl = pDb->pTables) != 0) {
            pNextTbl = pTbl->pNext;
            err = fn_8020BD90(pTbl);
            if (err != 0) {
                break;
            }
            pDb->pTables = pNextTbl;
        }
        if (err == 0) {
            if (pDb == lbl_803EBE88) {
                lbl_803EBE88 = pDb->pNext;
            } else {
                for (pPrev = lbl_803EBE88; pPrev->pNext != pDb; pPrev = pPrev->pNext) {
                }
                pPrev->pNext = pDb->pNext;
            }
            heap = pDb->mHeap;
            fn_8020D2AC(heap, pDb, 0x14);
            fn_8020D1A8(heap);
        }
    } else {
        err = 5;
    }
    return err;
}

int fn_801F9014(int db)
{
    int err;

    err = 0;
    if (FindDb_801F88F0(db) == 0) {
        err = 5;
    }
    return err;
}

int fn_801F9064(int db, int file, int a, int b, int c)
{
    TDbDb_801F88F0 *pDb;
    TDbFile_801F9064 desc;
    int err;

    if (db == 0) {
        pDb = FindDb_801F88F0(fn_801F95C8());
    } else {
        pDb = FindDb_801F88F0(db);
    }
    if (pDb == 0) {
        err = 5;
    } else {
        desc.mFile = file;
        desc.mUnk4 = -1;
        err = fn_801FBFEC(pDb, &desc, a, b, c);
    }
    return err;
}

int fn_801F9134(int db, int a, int b, int c)
{
    TDbDb_801F88F0 *pDb;
    int err;

    for (pDb = lbl_803EBE88; pDb != 0; pDb = pDb->pNext) {
        if (db == pDb->mId) {
            break;
        }
    }
    if (pDb != 0) {
        err = fn_801FBFEC(pDb, 0, a, b, c);
        pDb->mState = 0;
    } else {
        err = 5;
    }
    return err;
}

int fn_801F91AC(int db, int a, int b)
{
    TDbDb_801F88F0 *pDb;
    int err;

    pDb = FindDb_801F88F0(db);
    if (pDb != 0) {
        err = fn_801FC5FC(pDb, a, b);
        pDb->mState = 0;
    } else {
        err = 5;
    }
    return err;
}

void fn_801F9228(TDbAsync_801F9228 *pReq, void (*pStart)(TDbJob_801F9228 *pJob), int a, int b)
{
    TDbJob_801F9228 job;
    TDbDb_801F88F0 *pDb;
    int db;

    job.mUnk0 = 0;
    job.mUnk4 = b;
    job.pReq = pReq;
    job.mUnkC = 0;
    job.pRun = fn_801F93AC;
    job.mUnk14 = a;
    *pReq->pResult = 0x2E;
    pReq->mIsLoad = 1;
    db = pReq->mDb;
    for (pDb = lbl_803EBE88; pDb != 0; pDb = pDb->pNext) {
        if (db == pDb->mId) {
            break;
        }
    }
    if (pDb == 0) {
        *pReq->pResult = 5;
    } else if (pDb->mState == 1) {
        *pReq->pResult = 0x19;
    } else {
        pDb->mState = 1;
        pStart(&job);
    }
}

void fn_801F92EC(TDbAsync_801F9228 *pReq, void (*pStart)(TDbJob_801F9228 *pJob), int a, int b)
{
    TDbJob_801F9228 job;
    TDbDb_801F88F0 *pDb;
    int db;

    job.mUnk0 = 0;
    job.mUnk4 = b;
    job.pReq = pReq;
    job.mUnkC = 0;
    job.pRun = fn_801F93AC;
    job.mUnk14 = a;
    *pReq->pResult = 0x2E;
    pReq->mIsLoad = 0;
    db = pReq->mDb;
    for (pDb = lbl_803EBE88; pDb != 0; pDb = pDb->pNext) {
        if (db == pDb->mId) {
            break;
        }
    }
    if (pDb == 0) {
        *pReq->pResult = 5;
    } else if (pDb->mState == 1) {
        *pReq->pResult = 0x19;
    } else {
        pDb->mState = 1;
        pStart(&job);
    }
}

void fn_801F93AC(TDbAsync_801F9228 *pReq)
{
    int err;

    *pReq->pResult = 0x2D;
    if (pReq->mIsLoad != 0) {
        err = fn_801F9134(pReq->mDb, pReq->mUnkC, pReq->mUnk4, pReq->mUnk10);
    } else {
        err = fn_801F91AC(pReq->mDb, pReq->mUnkC, pReq->mUnk10);
    }
    *pReq->pResult = err;
    if (pReq->pDone != 0) {
        pReq->pDone();
    }
}

int fn_801F9430(int db, int *pTbls, int *pDbs)
{
    unsigned int i;
    int err;

    i = 0;
    err = 0;
    if (FindDb_801F88F0(db) == 0) {
        err = 5;
    } else {
        if ((unsigned int)lbl_803EBE84 < 50) {
            lbl_803E944C[lbl_803EBE84].mDb = db;
            lbl_803E944C[lbl_803EBE84].mTbl = 0;
            lbl_803EBE84++;
            if (pTbls != 0 && pDbs != 0) {
                for (; pDbs[i] != -1 && pTbls[i] != -1; i++) {
                    if ((unsigned int)(lbl_803EBE84 + i + 1) >= 50) {
                        err = 2;
                        break;
                    }
                    lbl_803E944C[lbl_803EBE84 + i].mDb = pDbs[i];
                    lbl_803E944C[lbl_803EBE84 + i].mTbl = pTbls[i];
                }
            }
        } else {
            err = 2;
        }
        if (err == 0) {
            lbl_803EBE84 += i;
        }
    }
    return err;
}

int fn_801F9574(void)
{
    unsigned int i;
    unsigned int n;
    int err;

    err = 5;
    i = lbl_803EBE84;
    if (i != 0) {
        n = i;
        do {
            i--;
            if (lbl_803E944C[i].mTbl == 0) {
                n = i;
                err = 0;
                break;
            }
        } while (i != 0);
        lbl_803EBE84 = n;
    }
    return err;
}

int fn_801F95C8(void)
{
    int i;
    int db;

    db = 0;
    i = lbl_803EBE84;
    while (i != 0) {
        i--;
        if (lbl_803E944C[i].mTbl == 0) {
            db = lbl_803E944C[i].mDb;
            break;
        }
    }
    return db;
}

int fn_801F9608(int db, int tbl, unsigned char *pFlag, unsigned short *pValue)
{
    TDbDb_801F88F0 *pDb;
    TDbTbl_801F88F0 *pTbl;
    unsigned short value;
    int err;

    err = fn_801F88F0(db, tbl, &pDb, &pTbl);
    if (err == 0) {
        if (pTbl->mFlags & 8) {
            *pFlag = 1;
            value = pTbl->mUnk40;
        } else {
            *pFlag = 0;
            value = 0;
        }
        if (pValue != 0) {
            *pValue = value;
        }
    }
    return err;
}

int fn_801F967C(int db, int tbl)
{
    TDbDb_801F88F0 *pDb;
    TDbTbl_801F88F0 *pTbl;
    int err;

    if (db == 0) {
        db = fn_801F95C8();
    }
    pDb = FindDb_801F88F0(db);
    if (pDb != 0) {
        pTbl = fn_8020BA48(pDb, tbl);
        if (pTbl != 0) {
            err = fn_8020BD90(pTbl);
        } else {
            err = 7;
        }
    } else {
        err = 5;
    }
    return err;
}

int fn_801F9718(int db, int tbl, TDbCol_801F9718 *pCols, TDbResult_801F9718 *pRes, int cb)
{
    TDbResult_801F9718 res;
    TDbDb_801F88F0 *pDb;
    TDbTbl_801F88F0 *pTbl;
    TDbCol_801F9718 *pCol;
    int err;

    if (pRes == 0) {
        if (cb != 0) {
            return 3;
        }
        pRes = &res;
    }
    err = fn_801F88F0(db, tbl, &pDb, &pTbl);
    if (err == 0) {
        for (pCol = pCols; pCol->mCol != -1; pCol++) {
            pCol->mIdx = fn_8020B97C(pTbl, pCol->mCol);
            if (pCol->mIdx == 0xFF) {
                return 9;
            }
        }
        err = fn_8020BFA4(pTbl, pCols, pRes);
    } else {
        pRes->mErr = err;
        pRes->mRows = 0;
    }
    return err;
}

int fn_801F97D0(int db, int tbl, int dstDb, int dstTbl, TDbResult_801F9718 *pRes, int cb)
{
    TDbResult_801F9718 res;
    TDbDb_801F88F0 *pDb;
    TDbTbl_801F88F0 *pTbl;
    TDbDb_801F88F0 *pDstDb;
    TDbTbl_801F88F0 *pDstTbl;
    int err;

    if (pRes == 0 && cb == 0) {
        pRes = &res;
    }
    err = fn_801F88F0(db, tbl, &pDb, &pTbl);
    pRes->mErr = err;
    if (err == 0) {
        err = fn_801F88F0(dstDb, dstTbl, &pDstDb, &pDstTbl);
        pRes->mErr = err;
        if (err == 0) {
            err = fn_8020C764(pTbl, pDstTbl, pRes);
        }
    }
    return err;
}

int fn_801F9858(int a, int b, int c, int d, int db, int tbl, TDbResult_801F9718 *pRes, int cb)
{
    TDbResult_801F9718 res;
    TDbQryBuf_801F9858 qry;
    TDbDb_801F88F0 *pDb;
    TDbTbl_801F88F0 *pTbl;
    int err;

    if (pRes == 0 && cb == 0) {
        pRes = &res;
    }
    pRes->mErr = fn_801F88F0(db, tbl, &pDb, &pTbl);
    if (pRes->mErr != 0) {
        return pRes->mErr;
    }
    err = fn_80207B8C(a, b, c, &qry);
    if (err == 0) {
        err = fn_8020A908(a, &qry, d, pTbl, pRes);
        fn_80207DB4(&qry);
    }
    return err;
}

int fn_801F9908(int a, int b, int c, TDbResult_801F9718 *pRes)
{
    TDbResult_801F9718 res;
    TDbQryBuf_801F9858 qry;
    int err;

    if (pRes == 0) {
        pRes = &res;
    }
    err = fn_80207B8C(a, b, c, &qry);
    if (err == 0) {
        err = fn_80208204(a, &qry, pRes);
        if (err == 0x17) {
            err = 0;
        }
        fn_80207DB4(&qry);
    }
    return err;
}

int fn_801F9980(int db, unsigned int *pTbl)
{
    TDbDb_801F88F0 *pDb;
    TDbTbl_801F88F0 *p;

    if (pTbl == 0) {
        return 3;
    }
    if (db == 0) {
        pDb = FindDb_801F88F0(fn_801F95C8());
    } else {
        pDb = FindDb_801F88F0(db);
    }
    if (pDb == 0) {
        return 5;
    }
    *pTbl = 0x100;
    p = pDb->pTables;
    while (p != 0) {
        if (p->mId == *pTbl) {
            if (*pTbl + 1 > 0xFFFFFFFE) {
                *pTbl = -1;
                return 7;
            }
            (*pTbl)++;
            p = pDb->pTables;
        } else {
            p = p->pNext;
        }
    }
    return 0;
}

int fn_801F9A90(int db, int tbl)
{
    TDbDb_801F88F0 *pDb;
    TDbTbl_801F88F0 *pTbl;

    return fn_801F88F0(db, tbl, &pDb, &pTbl);
}

int fn_801F9AB8(int db, int tbl, TDbColInfo_801F9AB8 *pCols, unsigned int *pCount)
{
    TDbDb_801F88F0 *pDb;
    TDbTbl_801F88F0 *pTbl;
    TDbColDef_801F9AB8 *pDefs;
    unsigned char i;
    unsigned char n;
    int err;

    i = 0;
    n = 0;
    err = fn_801F88F0(db, tbl, &pDb, &pTbl);
    if (err == 0) {
        if (pCount != 0) {
            if (pCols == 0) {
                *pCount = 0;
            }
            pDefs = pTbl->mCols;
            for (; i < pTbl->mNumCols; i++, n++) {
                if (*pCount != 0) {
                    pCols[n].mCol = pDefs[i].mCol;
                    pCols[n].mType = pDefs[i].mType;
                    if ((unsigned int)(pDefs[i].mType - 13) <= 2) {
                        pCols[n].mType = 0;
                    }
                    pCols[n].mSize = pDefs[i].mSize;
                    pCols[n].mUnk4 = -1;
                    (*pCount)--;
                }
            }
            *pCount = n;
        } else {
            err = 3;
        }
    }
    return err;
}

int fn_801F9BB4(int db, int tbl, int col, TDbColInfo_801F9AB8 *pInfo)
{
    TDbDb_801F88F0 *pDb;
    TDbTbl_801F88F0 *pTbl;
    int idx;
    int type;
    int err;

    err = fn_801F88F0(db, tbl, &pDb, &pTbl);
    if (err == 0) {
        if (pInfo != 0) {
            idx = fn_8020B97C(pTbl, col);
            if (idx == 0xFF) {
                err = 9;
            } else {
                pInfo->mCol = pTbl->mCols[idx].mCol;
                pInfo->mUnk4 = -1;
                pInfo->mSize = pTbl->mCols[idx].mSize;
                type = pTbl->mCols[idx].mType;
                pInfo->mType = type;
                if ((unsigned int)(type - 13) <= 2) {
                    pInfo->mType = err;
                }
            }
        } else {
            err = 3;
        }
    }
    return err;
}

int fn_801F9C68(int db, int tbl, int col)
{
    TDbDb_801F88F0 *pDb;
    TDbTbl_801F88F0 *pTbl;
    int err;

    err = fn_801F88F0(db, tbl, &pDb, &pTbl);
    if (err == 0) {
        if (fn_8020B97C(pTbl, col) == 0xFF) {
            err = 9;
        }
    }
    return err;
}

int fn_801F9CC0(int db, int tbl, unsigned short *pOut)
{
    TDbDb_801F88F0 *pDb;
    TDbTbl_801F88F0 *pTbl;
    int err;

    err = fn_801F88F0(db, tbl, &pDb, &pTbl);
    if (err == 0) {
        *pOut = pTbl->mUnk42;
        return 0;
    }
    return err;
}

int fn_801F9D0C(int db, int tbl, int on)
{
    TDbDb_801F88F0 *pDb;
    TDbTbl_801F88F0 *pTbl;
    int err;

    err = fn_801F88F0(db, tbl, &pDb, &pTbl);
    if (err == 0) {
        if (on == 1) {
            pTbl->mFlags |= 2;
        } else {
            pTbl->mFlags &= ~2;
        }
    }
    return err;
}

int fn_801F9D70(int db, int tbl, TDbTerm_801FA4B0 *pFilter, unsigned short *pCount)
{
    TDbQryBuf_801F9858 qry;
    TDbDb_801F88F0 *pDb;
    TDbTbl_801F88F0 *pTbl;
    unsigned short n;
    int err;

    n = 0;
    err = fn_801F88F0(db, tbl, &pDb, &pTbl);
    if (err == 0) {
        if (pFilter == 0) {
            n = pTbl->mUnk44 - pTbl->mUnk46;
        } else {
            qry.mUnk4 = 0;
            qry.mSel.mUnkC8 = 0;
            qry.mSel.mUnkA0 = 0;
            qry.mSel.mUnk50 = 0;
            qry.mSel.mUnk78 = 0;
            qry.mRow.mUnk0 = 0;
            qry.mSel.pTbl = pTbl;
            qry.mRow.mUnk14 = 2;
            qry.mUnk0 = 1;
            _TDbExprPrepare(pFilter, &qry.mSel.mUnk28, &pTbl, 1, 0);
            err = fn_80207E24(&qry, 0, 0);
            if (err == 0) {
                for (err = fn_802075F4(&qry, 0); err == 0; err = fn_80207988(&qry, 0)) {
                    n++;
                }
                if (err == 0x17) {
                    err = 0;
                }
                fn_802055CC(qry.mSel.mUnk28);
            }
        }
        *pCount = n;
    }
    return err;
}

static inline TDbIdx_801F9E84 *FindIdx_801F9E84(TDbIdx_801F9E84 *p, int idx)
{
    for (; p != 0; p = p->pNext) {
        if (idx == p->mId) {
            return p;
        }
    }
    return 0;
}

int fn_801F9E84(int db, int tbl, int idx, TDbIdxCol_801F9E84 *pCols, struct TDbExpr_801FAA00 *a, int b)
{
    TDbDb_801F88F0 *pDb;
    TDbTbl_801F88F0 *pTbl;
    unsigned char i;
    int err;

    pTbl = 0;
    err = fn_801F88F0(db, tbl, &pDb, &pTbl);
    if (idx == 0 || pCols == 0) {
        return 3;
    }
    if (err == 0) {
        if (FindIdx_801F9E84(pTbl->pIdx, idx) != 0) {
            err = 0xC;
        }
        if (err == 0) {
            for (i = 0; pCols[i].mCol != -1; i++) {
                pCols[i].mIdx = fn_8020B97C(pTbl, pCols[i].mCol);
                if (pCols[i].mIdx == 0xFF) {
                    return 9;
                }
            }
            err = CreateDatabaseIndex((struct TDbTable_801FAA00 *)pTbl, idx,
                                      (struct TDbIdxColumnDef_801FFFC4 *)pCols, a, b);
        }
    }
    return err;
}

int fn_801F9FA4(int db, int tbl, int idx)
{
    TDbDb_801F88F0 *pDb;
    TDbTbl_801F88F0 *pTbl;
    TDbIdx_801F9E84 *p;
    int err;

    err = fn_801F88F0(db, tbl, &pDb, &pTbl);
    if (err == 0) {
        if (idx == 0) {
            return 3;
        }
        p = FindIdx_801F9E84(pTbl->pIdx, idx);
        if (p == 0) {
            return 0xD;
        }
        err = fn_802032D8(p);
    }
    return err;
}

int fn_801FA038(int db, int tbl, int idx)
{
    TDbDb_801F88F0 *pDb;
    TDbTbl_801F88F0 *pTbl;
    int err;

    err = fn_801F88F0(db, tbl, &pDb, &pTbl);
    if (err != 0) {
        return err;
    }
    if (FindIdx_801F9E84(pTbl->pIdx, idx) == 0) {
        return 0xD;
    }
    return 0;
}

int fn_801FA0BC(int a, int b, int c, int d, int *pRef, TDbResult_801F9718 *pRes)
{
    TDbResult_801F9718 res;
    int err;

    if (pRes == 0) {
        pRes = &res;
    }
    *pRef = fn_801F89B8();
    if (*pRef == 0) {
        return 0x11;
    }
    err = fn_8020840C(a, b, c, d, *pRef, pRes);
    if (err != 0 && err != 0x17) {
        *pRef = 0;
    }
    return err;
}

static inline TDbQry_801F89B8 *FindQry_801FA148(int ref)
{
    TDbQry_801F89B8 *pQry;

    for (pQry = lbl_803EBE90; pQry != 0; pQry = pQry->pNext) {
        if (ref == pQry->mRef) {
            break;
        }
    }
    return pQry;
}

int fn_801FA148(int ref)
{
    TDbQry_801F89B8 *pQry;

    if (ref == 0) {
        return 0;
    }
    pQry = FindQry_801FA148(ref);
    if (pQry == 0) {
        return 0x11;
    }
    if (pQry->pDb->mState == 1) {
        return 0x1F;
    }
    return fn_802087D4(pQry);
}

int fn_801FA1C0(int ref)
{
    TDbQry_801F89B8 *pQry;
    int err;

    pQry = FindQry_801FA148(ref);
    if (pQry != 0) {
        err = 0x1F;
        if (pQry->pDb->mState != 1) {
            err = fn_802088A8(pQry);
        }
    } else {
        err = 0x11;
    }
    return err;
}

int fn_801FA228(int ref)
{
    TDbQry_801F89B8 *pQry;
    int err;

    pQry = FindQry_801FA148(ref);
    if (pQry != 0) {
        err = 0x1F;
        if (pQry->pDb->mState != 1) {
            err = fn_802088FC(pQry);
        }
    } else {
        err = 0x11;
    }
    return err;
}

int fn_801FA290(int a, int b, int c, int out)
{
    TDbRowInfo_801FA290 info;
    TDbQryBuf_801F9858 qry;
    int err;

    err = fn_80207B8C(a, b, c, &qry);
    if (err == 0) {
        if (qry.mUnk0 == 1) {
            err = fn_80207E24(&qry, 0, 0);
        } else {
            err = fn_80208094(&qry);
        }
        if (err == 0) {
            err = fn_802075F4(&qry, 0);
            if (err == 0) {
                for (_TDbExprTest(qry.mUnk4, &info, &qry.mSel, &qry.mRow); info.mUnk8 == 0;
                     _TDbExprTest(qry.mUnk4, &info, &qry.mSel, &qry.mRow)) {
                    err = fn_80207988(&qry, qry.mUnk0 - 1);
                    if (err != 0) {
                        break;
                    }
                }
                if (err == 0) {
                    err = fn_80209E40(&qry, out);
                    if (err == 0) {
                        fn_8020A3A0(&qry, out);
                    }
                }
            }
        }
        fn_80207DB4(&qry);
    }
    return err;
}

int fn_801FA3A0(int a, int b, int c, int d, TDbResult_801F9718 *pRes, int cb)
{
    TDbResult_801F9718 res;
    TDbQryBuf_801F9858 qry;
    int err;

    if (pRes == 0) {
        if (cb != 0) {
            return 3;
        }
        pRes = &res;
    }
    err = fn_80207B8C(a, b, c, &qry);
    if (err == 0) {
        err = fn_8020AD1C(a, &qry, d, 0, pRes);
        fn_80207DB4(&qry);
    }
    return err;
}

int fn_801FA428(int a, int b, int c, int d, TDbResult_801F9718 *pRes, int cb)
{
    TDbResult_801F9718 res;
    TDbQryBuf_801F9858 qry;
    int err;

    if (pRes == 0) {
        if (cb != 0) {
            return 3;
        }
        pRes = &res;
    }
    err = fn_80207B8C(a, b, c, &qry);
    if (err == 0) {
        err = fn_8020AD1C(a, &qry, d, 1, pRes);
        fn_80207DB4(&qry);
    }
    return err;
}

int fn_801FA4B0(int a, int b, int c, TDbSelCol_801FA4B0 *pCols, TDbTerm_801FA4B0 *pTerms, TDbResult_801F9718 *pRes, int cb)
{
    TDbResult_801F9718 res;
    TDbQryBuf_801F9858 qry;
    int handles[32];
    int i;
    int err;

    if (pRes == 0) {
        if (cb != 0) {
            return 3;
        }
        pRes = &res;
    }
    err = fn_80207B8C(a, b, c, &qry);
    if (err == 0) {
        for (i = 0; pCols[i].mCol != -1; i++) {
            err = _TDbExprPrepare(&pTerms[i], &handles[i], &qry.mSel.pTbl, qry.mUnk0, 0);
            if (err != 0) {
                while (i != 0) {
                    i--;
                    fn_802055CC(handles[i]);
                }
                break;
            }
        }
        if (err == 0) {
            err = fn_8020AE88(a, &qry, pCols, handles, pRes);
        }
        for (i = 0; pCols[i].mCol != -1; i++) {
            fn_802055CC(handles[i]);
        }
        fn_80207DB4(&qry);
    }
    return err;
}

int fn_801FA5EC(int db, int tbl, int ref, int a, int b)
{
    TDbQry_801F89B8 *pQry;
    TDbDb_801F88F0 *pDb;
    TDbTbl_801F88F0 *pTbl;
    int err;

    pQry = FindQry_801FA148(ref);
    if (pQry == 0) {
        return 0x11;
    }
    err = fn_801F88F0(db, tbl, &pDb, &pTbl);
    if (err == 7) {
        return fn_8020925C(pDb, tbl, pQry, a, b);
    }
    if (err == 0) {
        err = 6;
    }
    return err;
}

int fn_801FA68C(int db, int tbl)
{
    unsigned int i;
    int err;

    err = 0;
    for (i = 0; i < 15; i++) {
        if (tbl == lbl_803E95DC[i].mTbl) {
            err = 0xA;
            break;
        }
    }
    if (err != 0) {
        return err;
    }
    for (i = 0; i < 15; i++) {
        if (lbl_803E95DC[i].mTbl == 0) {
            lbl_803E95DC[i].mDb = db;
            lbl_803E95DC[i].mTbl = tbl;
            break;
        }
    }
    if (i > 14) {
        err = 2;
    }
    return err;
}

int fn_801FA740(int tbl)
{
    unsigned int i;

    for (i = 0; i < 15; i++) {
        if (tbl == lbl_803E95DC[i].mTbl) {
            lbl_803E95DC[i].mDb = 0;
            lbl_803E95DC[i].mTbl = 0;
            break;
        }
    }
    if (i > 14) {
        return 0xB;
    }
    return 0;
}

int fn_801FA7B0(int a, int b, int c, int d, int e, int f, TDbResult_801F9718 *pRes, int cb)
{
    TDbResult_801F9718 res;
    TDbQryBuf_801F9858 qry;
    int err;

    if (pRes == 0) {
        if (cb != 0) {
            return 3;
        }
        pRes = &res;
    }
    err = fn_80207B8C(a, b, c, &qry);
    if (err == 0) {
        err = fn_8020A660(a, &qry, d, e, f, pRes);
        fn_80207DB4(&qry);
    }
    return err;
}

int fn_801FA844(int a, int b, int c, int d, int e, int f, int g, TDbResult_801F9718 *pRes)
{
    TDbResult_801F9718 res;

    if (pRes == 0) {
        pRes = &res;
    }
    return fn_8020B094(a, b, c, d, e, f, g, pRes);
}
