#ifndef ENGINE_T3DB_MEM_H
#define ENGINE_T3DB_MEM_H

/* T3DB fixed-size item pools (t3db_mem.c) and the t3db.c globals other T3DB files share: the four
   pools TDbInit creates and the query handler table TDbRegisterHandler fills. */

struct TDbLitRef_t;

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

typedef void (*TDbHandlerFn_8020A660)(struct TDbLitRef_t *pLits, int user, unsigned char *pbEmit);

/* One _tDbQryCallbackNames entry: the handler and the key _TDbQryUpdateWithHandler looks it up by. */
typedef struct TDbHandler_8020A660 {
    TDbHandlerFn_8020A660 mpFn;
    int mKey;
} TDbHandler_8020A660;

int _TDbMemPoolInit(TDbMemPool_t *pPool, void *pHeap, unsigned int itemSize, unsigned short count,
                unsigned short growCount);
int _TDbMemPoolDeinit(TDbMemPool_t *pPool);

/* Defined in t3db.c. */
extern TDbHandler_8020A660 _tDbQryCallbackNames[15];
extern TDbMemPool_t _tDbGlobalExprPool;
extern TDbMemPool_t _tDbQryMem;
extern TDbMemPool_t _tDbQrySearchMem;
extern TDbMemPool_t _tDbIndexPool;

#endif
