#ifndef ENGINE_T3DB_H
#define ENGINE_T3DB_H

#include "engine/fn_801F8D60.h"
#include "engine/t3db_index.h"

#define TDB_COLUMN_ROW 0xFE

typedef enum TDbType_t {
    TDB_TYPE_STRING = 0,
    TDB_TYPE_BINARY = 1,
    TDB_TYPE_INT = 2,
    TDB_TYPE_UINT = 3,
    TDB_TYPE_FLOAT = 4,
    TDB_TYPE_COLUMN = 6,
    TDB_TYPE_RANGE_INT = 7,
    TDB_TYPE_RANGE_UINT = 8,
    TDB_TYPE_RANGE_FLOAT = 9,
    TDB_TYPE_EXPR_TRUNC = 10,
    TDB_TYPE_EXPR_UINT = 11,
    TDB_TYPE_EXPR_FLOAT = 12
} TDbType_t;

typedef struct TDbValue_t {
    TDbType_t mType;
    unsigned int mSize;
    union {
        int i;
        unsigned int u;
        float f;
        char *s;
        void *p;
        unsigned long long l;
    } mValue;
} TDbValue_t;

typedef struct TDbExpr_t {
    TDbValue_t mLeft;
    TDbValue_t mRight;
    int mOp;
} TDbExpr_t;

typedef struct TDbColumn_t {
    TDbType_t mType;
    unsigned int mBitOffset;
    unsigned int mUnknown8;
    unsigned int mBitCount;
} TDbColumn_t;

typedef struct TDbDatabase_801FAA00 {
    unsigned char mUnknown0[0x4];
    struct TDbTable_t *mTables;
    void *mUnknown8;
    void *mHeap;
} TDbDatabase_801FAA00;

typedef struct TDbTable_t {
    TDbDatabase_801FAA00 *mDb;
    struct TDbTable_t *mNext;
    struct TDbIndex_t *mIndexes;
    void *mUnknownC;
    void *mUnknown10;
    unsigned char *mRows;
    unsigned char *mUnknown18;
    unsigned int mUnknown1C;
    unsigned int mRowSize;
    unsigned int mDeletedBit;
    unsigned int mFlags;
    unsigned int mUnknown2C;
    void (*mCallbacks[4])(int dbId, int tableId, int op, void *pOld, void *pNew);
    unsigned short mUnknown40;
    unsigned short mCapacity;
    unsigned short mRowCount;
    unsigned short mUnknown46;
    unsigned short mUnknown48;
    unsigned char mColumnCount;
    unsigned char mUnknown4B;
    TDbColumn_t mColumns[1];
} TDbTable_t;

typedef struct TDbMemEvent_t {
    int mType;
    int mUnknown4;
    int mUnknown8;
} TDbMemEvent_t;

typedef struct TDbMemBlock_t {
    struct TDbMemBlock_t *mNext;
    unsigned char unk_0x4[4];
} TDbMemBlock_t;

typedef struct TDbMemPool_t {
    void *mFree;
    TDbMemBlock_t *mBlocks;
    unsigned char *mNext;
    void *mHeap;
    unsigned int mItemSize;
    unsigned short mRemaining;
    unsigned short mCount;
    unsigned short mGrowCount;
} TDbMemPool_t;

typedef struct TDbIdxNode_t {
    struct TDbIdxNode_t *mChild[2];
    struct TDbIdxNode_t *mParent;
    short mColor;
    unsigned int mRow;
    unsigned int mKey[1];
} TDbIdxNode_t;

typedef struct TDbIdxPart_t {
    TDbTable_t *mTable;
    unsigned char mUnknown4;
    unsigned char mColumn;
    unsigned char mAscending;
    unsigned char mUnknown7;
    unsigned int mUnknown8;
} TDbIdxPart_t;

typedef struct TDbIdxTree_t {
    TDbIdxNode_t *mRoot;
    unsigned char mAllowDuplicates;
    unsigned char mPartCount;
    unsigned char mUnknown6[2];
    TDbIdxPart_t mParts[1];
} TDbIdxTree_t;

typedef struct TDbIdxColumnDef_t {
    unsigned int mTableId;
    int mId;
    int mDescending;
    unsigned char mColumn;
} TDbIdxColumnDef_t;

typedef struct TDbIndex_t {
    TDbTable_t *mTable;
    struct TDbIndex_t *mNext;
    TDbExpr_t *mFilter;
    int mId;
    TDbMemPool_t mPool;
    unsigned int mCount;
    unsigned char mFlags;
    unsigned char mLocked;
    unsigned char mDirty;
    unsigned char mDestroyed;
    TDbIdxTree_t mTree;
} TDbIndex_t;

typedef struct TDbStmt_80205754 {
    unsigned int mTableCount;
    TDbExpr_t *mWhere;
    TDbTable_t *mTables[10];
    TDbExpr_t *mTableExprs[10];
    TDbIndex_t *mIndexes[10];
    TDbExpr_t *mSeekExprs[10];
    TDbIdxNode_t *mNodes[10];
    unsigned int mJoinTables[10];
    unsigned short mRows[10];
    unsigned int mJoinType[10];
} TDbStmt_80205754;

typedef struct TDbSQLTableRef_801FDC18 {
    unsigned int mId;
    unsigned int mJoinType;
    TDbExpr_t *mExpr;
} TDbSQLTableRef_801FDC18;

typedef struct TDbLitRef_t {
    unsigned int mUnknown0;
    unsigned int mTableId;
    int mId;
    unsigned int mColumn;
} TDbLitRef_t;

typedef struct TDbQIdx_80205880 {
    TDbStmt_80205754 *mStmt;
    unsigned int mCount;
    TDbMemPool_t mPool;
    TDbMemPool_t mKeyPool;
    unsigned char mDirty;
    TDbIdxTree_t mTree;
} TDbQIdx_80205880;

typedef struct TDbQuery_t {
    TDbDatabase_801FAA00 *mDb;
    struct TDbQuery_t *mNext;
    void (*mCallback)(int arg);
    int mCallbackArg;
    union {
        TDbTable_t *mTable;
        TDbIndex_t *mIndex;
        TDbQIdx_80205880 *mQIdx;
    } mSource;
    TDbIdxNode_t *mCur;
    unsigned int mState;
} TDbQuery_t;

typedef struct TDbResult_8020AD1C {
    unsigned short mCount;
    int mErr;
    int mUnknown08;
} TDbResult_8020AD1C;

typedef struct TDbToken_801FD2E8 {
    unsigned int mType;
    void *mValue;
    char *mSrc;
    int mUnknownC;
} TDbToken_801FD2E8;

typedef struct TDbLexer_801FCE10 {
    TDbToken_801FD2E8 mTokens[2];
    unsigned int mCount;
    char *mSrc;
    char mBuffer[0x64];
    unsigned int mBufUsed;
} TDbLexer_801FCE10;

typedef struct TDbIODevice_t {
    int (*mOpen)(void *pHandle, unsigned int size, void *pName, int mode);
    int (*mClose)(void *pHandle);
    int (*mRead)(void *pHandle, void *pData, unsigned int size, unsigned int *pDone);
    int (*mWrite)(void *pHandle, void *pData, unsigned int size, unsigned int *pDone);
    int (*mSeek)(void *pHandle, int offset);
    unsigned int (*mReserve)(unsigned int size);
    unsigned int mUnknown18;
} TDbIODevice_t;

typedef struct TDbIOStream_801FA8C8 {
    unsigned int mCrcA;
    unsigned int mCrcB;
    TDbIODevice_t *mDevice;
    unsigned char mUnknownC;
    unsigned int mSize;
    unsigned int mEnd;
    unsigned int mOffset;
    unsigned char mHandle[4];
    unsigned char mUnknown20[0x80];
} TDbIOStream_801FA8C8;

typedef struct TDbIOTableHdr_801FAAF8 {
    unsigned int mFlags;
    unsigned int mRowSize;
    unsigned int mDeletedBit;
    unsigned int mDataSize;
    unsigned short mUnknown10;
    unsigned short mRowCount;
    unsigned short mUnknown14;
    unsigned short mUnknown16;
    unsigned char mColumnCount;
    unsigned char mIndexCount;
    unsigned char mUnknown1A[6];
} TDbIOTableHdr_801FAAF8;

typedef struct TDbIOIndexHdr_801FBC2C {
    int mId;
    unsigned char mPartCount;
    unsigned char mAllowDuplicates;
    unsigned char mHasFilter;
    unsigned char mUnknown7;
} TDbIOIndexHdr_801FBC2C;

typedef struct TDbIOIndexPart_801FBC2C {
    unsigned int mColumn;
    unsigned int mAscending;
} TDbIOIndexPart_801FBC2C;

extern void (*_tDbMemAllocInfoCallback)(TDbMemEvent_t *pEvent);
extern unsigned int lbl_802F9548[256];
extern TDbMemPool_t lbl_803E9654;
extern TDbMemPool_t lbl_803E96A8;
extern int (*lbl_803EBE74)(const char *a, const char *b, int size);
extern void *lbl_803EBE8C;
extern TDbQuery_t *lbl_803EBE90;

void fn_801FA870(void);
int fn_801FA8C8(TDbIOStream_801FA8C8 *pStream, void *pData, unsigned int size);
int fn_801FA964(TDbIOStream_801FA8C8 *pStream, void *pData, unsigned int size);
unsigned int fn_801FAA00(TDbDatabase_801FAA00 *pDb, unsigned int *pOut);
int fn_801FBD2C(TDbTable_t *pTable, TDbIOStream_801FA8C8 *pStream);
unsigned int fn_801FC950(void *pData, unsigned int size, unsigned int crc);
void fn_802009B0(TDbLexer_801FCE10 *pLexer, unsigned int start);
char *fn_80201C70(TDbLexer_801FCE10 *pLexer, char *p);
void _TDbDataGetBitData(unsigned int *pData, unsigned int bitOffset, unsigned int bitCount, unsigned int *pValue,
                 int isSigned);
TDbIdxNode_t *_TDbIdxSeekClosest(TDbIdxTree_t *pTree, unsigned int *pKey);
TDbIdxNode_t *_TDbIdxSeek(TDbIdxTree_t *pTree, unsigned int *pKey, unsigned int mode);
TDbIdxNode_t *_TDbIdxTreeMoveRight(TDbIdxTree_t *pTree, TDbIdxNode_t *pNode);
TDbIdxNode_t *_TDbIdxTreeMoveLeft(TDbIdxTree_t *pTree, TDbIdxNode_t *pNode);
int _TDbIdxTreeInsert(TDbIdxTree_t *pTree, TDbIdxNode_t *pNode, TDbIdxNode_t *pStart);
TDbIdxNode_t *_TDbIdxTreeDelete(TDbIdxTree_t *pTree, TDbIdxNode_t *pNode);
int _TDbIndexRowAdd(TDbIndex_t *pIndex, unsigned int row);
int _TDbIndexRowDelete(TDbIndex_t *pIndex, int row);
int _TDbIndexDestroy(TDbIndex_t *pIndex);
int _TDbMemPoolInit(TDbMemPool_t *pPool, void *pHeap, unsigned int itemSize, unsigned short count,
                unsigned short growCount);
int _TDbMemPoolDeinit(TDbMemPool_t *pPool);
int _TDbMemPoolReset(TDbMemPool_t *pPool);
int __TDbMemPoolAlloc(TDbMemPool_t *pPool, void *ppItem);
void __TDbMemPoolFree(TDbMemPool_t *pPool, void *pItem);
void _TDbExprTest(TDbExpr_t *pExpr, TDbValue_t *pResult, TDbTable_t **ppTables,
                 unsigned short *pRows);
int _TDbExprCopy(TDbExpr_t *pSrc, TDbExpr_t **ppDst);
int _TDbExprPrepare(TDbExpr_t *pSrc, TDbExpr_t **ppDst, TDbTable_t **ppTables, int tableCount,
                int flags);
void _TDbExprFree(TDbExpr_t *pExpr);
int _TDbExprFindTableCol(TDbExpr_t *pExpr, unsigned long long column);
void fn_80205C44(TDbTable_t *pTable, int row);
void fn_8020651C(TDbTable_t *pTable, int row);
void fn_80206668(TDbIndex_t *pIndex, TDbIdxNode_t *pOld, TDbIdxNode_t *pNew);
unsigned int fn_80206708(TDbIndex_t *pIndex, TDbStmt_80205754 *pStmt, unsigned int table, int column,
                         TDbExpr_t *pExpr);
unsigned int fn_802067D4(TDbIndex_t *pIndex, TDbExpr_t *pExpr, TDbIdxColumnDef_t *pCols,
                         TDbExpr_t **ppSeek);
int fn_802069BC(TDbTable_t *pTable, TDbIdxColumnDef_t *pCols, TDbExpr_t *pFilter,
                TDbIndex_t **ppIndex);
void fn_80206C9C(TDbQIdx_80205880 *pQIdx, TDbIdxNode_t **ppNode);
void fn_80206E4C(TDbQIdx_80205880 *pQIdx);
int fn_802075F4(TDbStmt_80205754 *pStmt, unsigned int t);
int fn_80207988(TDbStmt_80205754 *pStmt, unsigned int t);
void fn_80207DB4(TDbStmt_80205754 *pStmt);
int fn_80208094(TDbStmt_80205754 *pStmt);
unsigned char _TDbTblResolveColRef(TDbTable_t *pTable, int id);
int TDbExtMemAlloc(void *pHeap, int size, void *ppMem);
void TDbExtMemFree(void *pHeap, void *pMem, int size);

static inline void _TDbMemNotify(int type, int a, int b)
{
    TDbMemEvent_t event;

    if (_tDbMemAllocInfoCallback) {
        event.mType = type;
        event.mUnknown4 = a;
        event.mUnknown8 = b;
        _tDbMemAllocInfoCallback(&event);
    }
}

static inline unsigned char TDbRowBit_801FAAF8(TDbTable_t *pTable, unsigned int row)
{
    unsigned char *pRow = pTable->mRows + pTable->mRowSize * row;
    unsigned int bit = pTable->mDeletedBit;

    if (!((pRow[bit >> 3] >> (7 - (bit & 7))) & 1)) {
        return 0;
    }
    return 1;
}

static inline unsigned int TDbStmtTableSlot_80205C44(TDbStmt_80205754 *pStmt, TDbTable_t *pTable)
{
    unsigned int i;

    for (i = 0; i < pStmt->mTableCount; i++) {
        if (pTable == pStmt->mTables[i]) {
            return i + 1;
        }
    }
    return 0;
}

#endif
