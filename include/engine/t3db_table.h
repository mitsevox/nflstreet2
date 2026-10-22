#ifndef ENGINE_T3DB_TABLE_H
#define ENGINE_T3DB_TABLE_H

#include <string.h>
#include "engine/t3db.h"

typedef struct HuffNode_8020CD2C {
    unsigned char mChild[2][2];
} HuffNode_8020CD2C;

typedef void (*TDbHandlerFn_8020A660)(TDbLitRef_80205754 *pLits, int user, unsigned char *pbEmit);

typedef struct TDbHandler_8020A660 {
    TDbHandlerFn_8020A660 mpFn;
    int mKey;
} TDbHandler_8020A660;

/* Defined in the T3DB query and index sources. */
void fn_80201E10(unsigned int *pData, unsigned int bitOffset, unsigned int bitCount, unsigned int *pValue);
int fn_8020325C(TDbIndex_801FAA00 *pIndex);
int fn_80205754(TDbStmt_80205754 *pStmt, TDbLitRef_80205754 *pLits, unsigned int *pMask);
int fn_80205880(TDbTable_801FAA00 *pTable, unsigned char column, TDbQIdx_80205880 *pQIdx);
int fn_80205A10(TDbQIdx_80205880 *pQIdx, TDbIdxNode_80201EC8 **ppCur);
int fn_80205B88(TDbStmt_80205754 *pStmt);
void fn_80205C08(TDbStmt_80205754 *pStmt);
int fn_80207E24(TDbStmt_80205754 *pStmt, TDbIdxColumnDef_801FFFC4 *pCols, int create);

void fn_80209F34(TDbStmt_80205754 *pStmt, TDbLitRef_80205754 *pLits, unsigned int *pMask);
void fn_8020A540(void);
void fn_8020A5A8(void);
void fn_8020B710(TDbTable_801FAA00 *pTable, int row);
void fn_8020B878(TDbTable_801FAA00 *pTable, int row, TDbLitRef_80205754 *pValues);
void fn_8020CD9C(TDbTable_801FAA00 *pTable, TDbColumn_801FAA00 *pColumn, void *pRow, unsigned char *pOut);
void fn_8020CEC4(unsigned char *pRow, unsigned int bitOffset, unsigned int bitCount, void *pSrc, unsigned int len);
void fn_8020CF34(unsigned char *pRow, unsigned int bitOffset, unsigned int bitCount, unsigned char *pDst,
                 unsigned int len);
int fn_8020D204(void *pHeap, int size, void *ppMem);
int fn_8020D260(void *pHeap, void *pOld, int oldSize, int newSize, void *ppMem);

static inline void TDbReadColumn_8020A3A0(TDbTable_801FAA00 *pTable, TDbColumn_801FAA00 *pColumn, unsigned char *pRow,
                                          TDbLitRef_80205754 *pValue)
{
    int type = pColumn->mType;

    if ((unsigned int)(type - 13) <= 2) {
        fn_8020CD9C(pTable, pColumn, pRow, (unsigned char *)pValue->mUnknown0);
    } else if ((unsigned int)type <= 1) {
        fn_8020CF34(pRow, pColumn->mBitOffset, pColumn->mBitCount, (unsigned char *)pValue->mUnknown0,
                    pColumn->mBitCount >> 3);
    } else {
        fn_80201D94((unsigned int *)pRow, pColumn->mBitOffset, pColumn->mBitCount, &pValue->mUnknown0, type == 2);
    }
}

static inline void TDbWriteColumn_8020BFA4(TDbColumn_801FAA00 *pColumn, unsigned char *pRow, TDbLitRef_80205754 *pValue)
{
    int type = pColumn->mType;

    if ((unsigned int)(type - 13) <= 2) {
        return;
    }
    if (type == 0) {
        fn_8020CEC4(pRow, pColumn->mBitOffset, pColumn->mBitCount, (unsigned char *)pValue->mUnknown0,
                    strlen((char *)pValue->mUnknown0));
    } else if (type == 1) {
        fn_8020CEC4(pRow, pColumn->mBitOffset, pColumn->mBitCount, (unsigned char *)pValue->mUnknown0,
                    pColumn->mBitCount >> 3);
    } else {
        fn_80201E10((unsigned int *)pRow, pColumn->mBitOffset, pColumn->mBitCount, &pValue->mUnknown0);
    }
}

#endif
