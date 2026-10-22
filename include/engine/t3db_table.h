#ifndef ENGINE_T3DB_TABLE_H
#define ENGINE_T3DB_TABLE_H

#include "engine/t3db.h"

typedef struct HuffNode_8020CD2C {
    unsigned char mChild[2][2];
} HuffNode_8020CD2C;

typedef void (*TDbTableCallback_8020B710)(int dbId, int tableId, int op, TDbLitRef_80205754 *pOld,
                                          TDbLitRef_80205754 *pNew);

/* Members that t3db.h keeps as raw storage: the owning database, change callback and
   callback argument of a TDbQuery_802032D8, its table source (state 0), the 32-bit
   column index word at +0xC of a TDbLitRef_80205754, and the four row-change callbacks
   of a TDbTable_801FAA00 at +0x30. */
#define TDB_QUERY_DB(q) (*(TDbDatabase_801FAA00 **)(q)->mUnknown0)
#define TDB_QUERY_CALLBACK(q) (*(void (**)(int))(q)->mUnknown8)
#define TDB_QUERY_CALLBACK_ARG(q) (*(int *)((q)->mUnknown8 + 4))
#define TDB_QUERY_TABLE(q) ((TDbTable_801FAA00 *)(q)->mSource.mIndex)
#define TDB_LITREF_INDEX(l) (*(unsigned int *)(l)->mUnknownC)
#define TDB_TABLE_CALLBACK(t, k) ((TDbTableCallback_8020B710)(t)->mUnknown30[k])

/* fn_8020299C called with a full-width row: the callers below pass the row
   register without the halfword truncation that t3db.h's unsigned short
   parameter would add. */
#define TDB_INDEX_INSERT(i, row) (((int (*)(TDbIndex_801FAA00 *, unsigned int))fn_8020299C)((i), (row)))

typedef struct TDbResult_8020AD1C {
    unsigned short mCount;
    int mErr;
    int mUnknown08;
} TDbResult_8020AD1C;

typedef void (*TDbHandlerFn_8020A660)(TDbLitRef_80205754 *pLits, int user, unsigned char *pbEmit);

typedef struct TDbHandler_8020A660 {
    TDbHandlerFn_8020A660 mpFn;
    int mKey;
} TDbHandler_8020A660;

/* Defined in the E5 T3DB sources; not declared in t3db.h. */
void fn_80201E10(unsigned int *pData, unsigned int bitOffset, unsigned int bitCount, unsigned int *pValue);
int fn_8020325C(TDbIndex_801FAA00 *pIndex);
int fn_80205754(TDbStmt_80205754 *pStmt, TDbLitRef_80205754 *pLits, unsigned int *pMask);
int fn_80205880(TDbTable_801FAA00 *pTable, unsigned int column, TDbQIdx_80205880 *pQIdx);
int fn_80205A10(TDbQIdx_80205880 *pQIdx, TDbIdxNode_80201EC8 **ppCur);
int fn_80205B88(TDbStmt_80205754 *pStmt);
void fn_80205C08(TDbStmt_80205754 *pStmt);
int fn_80207E24(TDbStmt_80205754 *pStmt, TDbIdxColumnDef_801FFFC4 *pCols, int create);

void fn_80209F34(TDbStmt_80205754 *pStmt, TDbLitRef_80205754 *pLits, unsigned int *pMask);
void fn_8020A540(void);
void fn_8020A5A8(void);
void fn_8020B710(TDbTable_801FAA00 *pTable, int row);
void fn_8020B878(TDbTable_801FAA00 *pTable, int row, TDbLitRef_80205754 *pValues);
void fn_8020CD2C(HuffNode_8020CD2C *pTree, unsigned char *pBits, int count, unsigned char *pOut);
void fn_8020CD9C(TDbTable_801FAA00 *pTable, TDbColumn_801FAA00 *pColumn, void *pRow, unsigned char *pOut);
void fn_8020CEC4(unsigned char *pRow, unsigned int bitOffset, unsigned int bitCount, void *pSrc, unsigned int len);
void fn_8020CF34(unsigned char *pRow, unsigned int bitOffset, unsigned int bitCount, unsigned char *pDst,
                 unsigned int len);
int fn_8020D204(void *pHeap, int size, void *ppMem);
int fn_8020D260(void *pHeap, void *pOld, int oldSize, int newSize, void *ppMem);

#endif
