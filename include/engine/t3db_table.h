#ifndef ENGINE_T3DB_TABLE_H
#define ENGINE_T3DB_TABLE_H

#include <string.h>
#include "engine/t3db.h"

typedef struct TDbHuffNode_t {
    unsigned char mChild[2][2];
} TDbHuffNode_t;

typedef void (*TDbHandlerFn_8020A660)(TDbLitRef_t *pLits, int user, unsigned char *pbEmit);

typedef struct TDbHandler_8020A660 {
    TDbHandlerFn_8020A660 mpFn;
    int mKey;
} TDbHandler_8020A660;

/* Defined in the T3DB query and index sources. */
void _TDbDataSetBitData(unsigned int *pData, unsigned int bitOffset, unsigned int bitCount, unsigned int *pValue);
int _TDbIndexZap(TDbIndex_t *pIndex);
int fn_80205754(TDbStmt_80205754 *pStmt, TDbLitRef_t *pLits, unsigned int *pMask);
int fn_80205880(TDbTable_t *pTable, unsigned char column, TDbQIdx_80205880 *pQIdx);
int fn_80205A10(TDbQIdx_80205880 *pQIdx, TDbIdxNode_t **ppCur);
int fn_80205B88(TDbStmt_80205754 *pStmt);
void fn_80205C08(TDbStmt_80205754 *pStmt);
int fn_80207E24(TDbStmt_80205754 *pStmt, TDbIdxColumnDef_t *pCols, int create);

void fn_80209F34(TDbStmt_80205754 *pStmt, TDbLitRef_t *pLits, unsigned int *pMask);
void fn_8020A540(void);
void fn_8020A5A8(void);
void _TDbTblCallInsertTriggers(TDbTable_t *pTable, int row);
void _TDbTblGetFullRow(TDbTable_t *pTable, int row, TDbLitRef_t *pValues);
void _TDbBlobGetData(TDbTable_t *pTable, TDbColumn_t *pColumn, void *pRow, unsigned char *pOut);
void _TDbDataSetPtrData(unsigned char *pRow, unsigned int bitOffset, unsigned int bitCount, void *pSrc, unsigned int len);
void _TDbDataGetPtrData(unsigned char *pRow, unsigned int bitOffset, unsigned int bitCount, unsigned char *pDst,
                 unsigned int len);
int TDbExtMemAllocTemp(void *pHeap, int size, void *ppMem);
int TDbExtMemRealloc(void *pHeap, void *pOld, int oldSize, int newSize, void *ppMem);

static inline void TDbReadColumn_8020A3A0(TDbTable_t *pTable, TDbColumn_t *pColumn, unsigned char *pRow,
                                          TDbLitRef_t *pValue)
{
    int type = pColumn->mType;

    if ((unsigned int)(type - 13) <= 2) {
        _TDbBlobGetData(pTable, pColumn, pRow, (unsigned char *)pValue->mUnknown0);
    } else if ((unsigned int)type <= 1) {
        _TDbDataGetPtrData(pRow, pColumn->mBitOffset, pColumn->mBitCount, (unsigned char *)pValue->mUnknown0,
                    pColumn->mBitCount >> 3);
    } else {
        _TDbDataGetBitData((unsigned int *)pRow, pColumn->mBitOffset, pColumn->mBitCount, &pValue->mUnknown0, type == 2);
    }
}

static inline void TDbWriteColumn_8020BFA4(TDbColumn_t *pColumn, unsigned char *pRow, TDbLitRef_t *pValue)
{
    int type = pColumn->mType;

    if ((unsigned int)(type - 13) <= 2) {
        return;
    }
    if (type == 0) {
        _TDbDataSetPtrData(pRow, pColumn->mBitOffset, pColumn->mBitCount, (unsigned char *)pValue->mUnknown0,
                    strlen((char *)pValue->mUnknown0));
    } else if (type == 1) {
        _TDbDataSetPtrData(pRow, pColumn->mBitOffset, pColumn->mBitCount, (unsigned char *)pValue->mUnknown0,
                    pColumn->mBitCount >> 3);
    } else {
        _TDbDataSetBitData((unsigned int *)pRow, pColumn->mBitOffset, pColumn->mBitCount, &pValue->mUnknown0);
    }
}

#endif
