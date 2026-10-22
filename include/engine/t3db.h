#ifndef ENGINE_T3DB_H
#define ENGINE_T3DB_H

#define TDB_COLUMN_ROW 0xFE

typedef enum TDbType_801FDF28 {
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
} TDbType_801FDF28;

typedef struct TDbValue_801FDF28 {
    TDbType_801FDF28 mType;
    unsigned int mSize;
    union {
        int i;
        unsigned int u;
        float f;
        char *s;
        void *p;
        unsigned long long l;
    } mValue;
} TDbValue_801FDF28;

typedef struct TDbExpr_801FAA00 {
    TDbValue_801FDF28 mLeft;
    TDbValue_801FDF28 mRight;
    int mOp;
} TDbExpr_801FAA00;

typedef struct TDbColumn_801FAA00 {
    TDbType_801FDF28 mType;
    unsigned int mBitOffset;
    unsigned int mUnknown8;
    unsigned int mBitCount;
} TDbColumn_801FAA00;

typedef struct TDbDatabase_801FAA00 {
    unsigned char mUnknown0[0x4];
    struct TDbTable_801FAA00 *mTables;
    void *mUnknown8;
    void *mHeap;
} TDbDatabase_801FAA00;

typedef struct TDbTable_801FAA00 {
    TDbDatabase_801FAA00 *mDb;
    struct TDbTable_801FAA00 *mNext;
    struct TDbIndex_801FAA00 *mIndexes;
    void *mUnknownC;
    void *mUnknown10;
    unsigned char *mRows;
    unsigned char *mUnknown18;
    unsigned int mUnknown1C;
    unsigned int mRowSize;
    unsigned int mDeletedBit;
    unsigned int mFlags;
    unsigned int mUnknown2C;
    unsigned int mUnknown30[4];
    unsigned short mUnknown40;
    unsigned short mCapacity;
    unsigned short mRowCount;
    unsigned short mUnknown46;
    unsigned short mUnknown48;
    unsigned char mColumnCount;
    unsigned char mUnknown4B;
    TDbColumn_801FAA00 mColumns[1];
} TDbTable_801FAA00;

typedef struct TDbMemEvent_801FC5FC {
    int mType;
    int mUnknown4;
    int mUnknown8;
} TDbMemEvent_801FC5FC;

typedef struct TDbMemBlock_80203444 {
    struct TDbMemBlock_80203444 *mNext;
    int mUnknown4;
} TDbMemBlock_80203444;

typedef struct TDbMemPool_80202B60 {
    void *mFree;
    TDbMemBlock_80203444 *mBlocks;
    unsigned char *mNext;
    void *mHeap;
    unsigned int mItemSize;
    unsigned short mRemaining;
    unsigned short mCount;
    unsigned short mGrowCount;
} TDbMemPool_80202B60;

typedef struct TDbIdxNode_80201EC8 {
    struct TDbIdxNode_80201EC8 *mChild[2];
    struct TDbIdxNode_80201EC8 *mParent;
    short mColor;
    unsigned int mRow;
    unsigned int mKey[1];
} TDbIdxNode_80201EC8;

typedef struct TDbIdxPart_80202708 {
    TDbTable_801FAA00 *mTable;
    unsigned char mUnknown4;
    unsigned char mColumn;
    unsigned char mDescending;
    unsigned char mUnknown7;
    unsigned int mUnknown8;
} TDbIdxPart_80202708;

typedef struct TDbIdxTree_80201EC8 {
    TDbIdxNode_80201EC8 *mRoot;
    unsigned char mAllowDuplicates;
    unsigned char mPartCount;
    unsigned char mUnknown6[2];
    TDbIdxPart_80202708 mParts[1];
} TDbIdxTree_80201EC8;

typedef struct TDbIdxColumnDef_801FFFC4 {
    unsigned int mTableId;
    int mId;
    int mAscending;
    unsigned char mColumn;
} TDbIdxColumnDef_801FFFC4;

typedef struct TDbIndex_801FAA00 {
    TDbTable_801FAA00 *mTable;
    struct TDbIndex_801FAA00 *mNext;
    TDbExpr_801FAA00 *mFilter;
    void *mUserData;
    TDbMemPool_80202B60 mPool;
    unsigned int mCount;
    unsigned char mFlags;
    unsigned char mLocked;
    unsigned char mDirty;
    unsigned char mDestroyed;
    TDbIdxTree_80201EC8 mTree;
} TDbIndex_801FAA00;

typedef struct TDbStmt_80205754 {
    unsigned int mTableCount;
    TDbExpr_801FAA00 *mWhere;
    TDbTable_801FAA00 *mTables[10];
    TDbExpr_801FAA00 *mTableExprs[10];
    TDbIndex_801FAA00 *mIndexes[10];
    TDbExpr_801FAA00 *mSeekExprs[10];
    TDbIdxNode_80201EC8 *mNodes[10];
    unsigned int mJoinTables[10];
    unsigned short mRows[10];
    unsigned int mJoinType[10];
} TDbStmt_80205754;

typedef struct TDbSQLTableRef_801FDC18 {
    unsigned int mId;
    unsigned int mJoinType;
    TDbExpr_801FAA00 *mExpr;
} TDbSQLTableRef_801FDC18;

typedef struct TDbLitRef_80205754 {
    unsigned int mUnknown0;
    unsigned int mTableId;
    int mId;
    unsigned char mUnknownC[3];
    unsigned char mColumn;
} TDbLitRef_80205754;

typedef struct TDbQIdx_80205880 {
    TDbStmt_80205754 *mStmt;
    unsigned int mCount;
    TDbMemPool_80202B60 mPool;
    TDbMemPool_80202B60 mKeyPool;
    unsigned char mDirty;
    TDbIdxTree_80201EC8 mTree;
} TDbQIdx_80205880;

typedef struct TDbQuery_802032D8 {
    unsigned char mUnknown0[0x4];
    struct TDbQuery_802032D8 *mNext;
    unsigned char mUnknown8[0x8];
    union {
        TDbIndex_801FAA00 *mIndex;
        TDbQIdx_80205880 *mQIdx;
    } mSource;
    TDbIdxNode_80201EC8 *mCur;
    int mState;
} TDbQuery_802032D8;

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

typedef struct TDbIODevice_801FC5FC {
    int (*mOpen)(void *pHandle, unsigned int size, void *pName, int mode);
    int (*mClose)(void *pHandle);
    int (*mRead)(void *pHandle, void *pData, unsigned int size, unsigned int *pDone);
    int (*mWrite)(void *pHandle, void *pData, unsigned int size, unsigned int *pDone);
    void *mUnknown10;
    unsigned int (*mReserve)(unsigned int size);
} TDbIODevice_801FC5FC;

typedef struct TDbIOStream_801FA8C8 {
    unsigned int mCrcA;
    unsigned int mCrcB;
    TDbIODevice_801FC5FC *mDevice;
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
    void *mUserData;
    unsigned char mPartCount;
    unsigned char mAllowDuplicates;
    unsigned char mHasFilter;
    unsigned char mUnknown7;
} TDbIOIndexHdr_801FBC2C;

typedef struct TDbIOIndexPart_801FBC2C {
    unsigned int mColumn;
    unsigned int mDescending;
} TDbIOIndexPart_801FBC2C;

extern void (*lbl_803EBE80)(TDbMemEvent_801FC5FC *pEvent);
extern unsigned int lbl_802F9548[256];
extern TDbMemPool_80202B60 lbl_803E9654;
extern TDbMemPool_80202B60 lbl_803E96A8;
extern int (*lbl_803EBE74)(const char *a, const char *b, int size);
extern void *lbl_803EBE8C;
extern TDbQuery_802032D8 *lbl_803EBE90;

void fn_801FA870(void);
int fn_801FA8C8(TDbIOStream_801FA8C8 *pStream, void *pData, unsigned int size);
int fn_801FA964(TDbIOStream_801FA8C8 *pStream, void *pData, unsigned int size);
unsigned int fn_801FAA00(TDbDatabase_801FAA00 *pDb, unsigned int *pOut);
int fn_801FBD2C(TDbTable_801FAA00 *pTable, TDbIOStream_801FA8C8 *pStream);
unsigned int fn_801FC950(void *pData, unsigned int size, unsigned int crc);
void fn_802009B0(TDbLexer_801FCE10 *pLexer, unsigned int start);
char *fn_80201C70(TDbLexer_801FCE10 *pLexer, char *p);
void fn_80201D94(unsigned int *pData, unsigned int bitOffset, unsigned int bitCount, unsigned int *pValue,
                 int isSigned);
TDbIdxNode_80201EC8 *fn_80201EC8(TDbIdxTree_80201EC8 *pTree, unsigned int *pKey);
TDbIdxNode_80201EC8 *fn_80201F9C(TDbIdxTree_80201EC8 *pTree, unsigned int *pKey, unsigned int mode);
TDbIdxNode_80201EC8 *fn_80202200(TDbIdxTree_80201EC8 *pTree, TDbIdxNode_80201EC8 *pNode);
TDbIdxNode_80201EC8 *fn_80202298(TDbIdxTree_80201EC8 *pTree, TDbIdxNode_80201EC8 *pNode);
int fn_802024B0(TDbIdxTree_80201EC8 *pTree, TDbIdxNode_80201EC8 *pNode, TDbIdxNode_80201EC8 *pStart);
TDbIdxNode_80201EC8 *fn_802025C4(TDbIdxTree_80201EC8 *pTree, TDbIdxNode_80201EC8 *pNode);
int fn_8020299C(TDbIndex_801FAA00 *pIndex, unsigned short row);
int fn_80202D34(TDbIndex_801FAA00 *pIndex, int row);
int fn_802032D8(TDbIndex_801FAA00 *pIndex);
int fn_80203444(TDbMemPool_80202B60 *pPool, void *pHeap, unsigned int itemSize, unsigned short count,
                unsigned short growCount);
int fn_8020353C(TDbMemPool_80202B60 *pPool);
int fn_802035C8(TDbMemPool_80202B60 *pPool);
int fn_8020360C(TDbMemPool_80202B60 *pPool, void *ppItem);
void fn_80203744(TDbMemPool_80202B60 *pPool, void *pItem);
void fn_802047EC(TDbExpr_801FAA00 *pExpr, TDbValue_801FDF28 *pResult, TDbTable_801FAA00 **ppTables,
                 unsigned short *pRows);
int fn_80204D14(TDbExpr_801FAA00 *pSrc, TDbExpr_801FAA00 **ppDst);
int fn_80204EF8(TDbExpr_801FAA00 *pSrc, TDbExpr_801FAA00 **ppDst, TDbTable_801FAA00 **ppTables, int tableCount,
                int flags);
void fn_802055CC(TDbExpr_801FAA00 *pExpr);
int fn_8020567C(TDbExpr_801FAA00 *pExpr, unsigned long long column);
void fn_80205C44(TDbTable_801FAA00 *pTable, int row);
void fn_8020651C(TDbTable_801FAA00 *pTable, int row);
void fn_80206668(TDbIndex_801FAA00 *pIndex, TDbIdxNode_80201EC8 *pOld, TDbIdxNode_80201EC8 *pNew);
unsigned int fn_80206708(TDbIndex_801FAA00 *pIndex, TDbStmt_80205754 *pStmt, unsigned int table, int column,
                         TDbExpr_801FAA00 *pExpr);
unsigned int fn_802067D4(TDbIndex_801FAA00 *pIndex, TDbExpr_801FAA00 *pExpr, TDbIdxColumnDef_801FFFC4 *pCols,
                         TDbExpr_801FAA00 **ppSeek);
int fn_802069BC(TDbTable_801FAA00 *pTable, TDbIdxColumnDef_801FFFC4 *pCols, TDbExpr_801FAA00 *pFilter,
                TDbIndex_801FAA00 **ppIndex);
void fn_80206C9C(TDbQIdx_80205880 *pQIdx, TDbIdxNode_80201EC8 **ppNode);
void fn_80206E4C(TDbQIdx_80205880 *pQIdx);
int fn_802075F4(TDbStmt_80205754 *pStmt, unsigned int t);
int fn_80207988(TDbStmt_80205754 *pStmt, unsigned int t);
void fn_80207DB4(TDbStmt_80205754 *pStmt);
int fn_80208094(TDbStmt_80205754 *pStmt);
unsigned char fn_8020B97C(TDbTable_801FAA00 *pTable, int id);
int fn_8020D1B0(void *pHeap, int size, void *ppMem);
void fn_8020D2AC(void *pHeap, void *pMem, int size);

static inline void TDbMemNotify_801FC9D4(int type, int a, int b)
{
    TDbMemEvent_801FC5FC event;

    if (lbl_803EBE80) {
        event.mType = type;
        event.mUnknown4 = a;
        event.mUnknown8 = b;
        lbl_803EBE80(&event);
    }
}

static inline unsigned char TDbRowBit_801FAAF8(TDbTable_801FAA00 *pTable, unsigned int row)
{
    unsigned char *pRow = pTable->mRows + pTable->mRowSize * row;
    unsigned int bit = pTable->mDeletedBit;

    if (!((pRow[bit >> 3] >> (7 - (bit & 7))) & 1)) {
        return 0;
    }
    return 1;
}

static inline void TDbMemNotifyTo_801FC5FC(TDbMemEvent_801FC5FC *pEvent, int type, int a, int b)
{
    if (lbl_803EBE80) {
        pEvent->mType = type;
        pEvent->mUnknown4 = a;
        pEvent->mUnknown8 = b;
        lbl_803EBE80(pEvent);
    }
}

static inline void TDbMemNotifyEnd_801FC5FC(TDbMemEvent_801FC5FC *pEvent, int type)
{
    if (lbl_803EBE80) {
        pEvent->mType = type;
        pEvent->mUnknown4 = -1;
        pEvent->mUnknown8 = -1;
        lbl_803EBE80(pEvent);
    }
}

static inline unsigned int TDbStmtTableSlot_80205C44(TDbStmt_80205754 *pStmt, TDbTable_801FAA00 *pTable)
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
