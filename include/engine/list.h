#ifndef ENGINE_LIST_H
#define ENGINE_LIST_H

/* Node header word: bit 31 is set while the node is linked into its list. */
typedef struct DSListNode_t {
    unsigned int mFlags;
} DSListNode_t;

typedef struct DSList_t {
    int mType;
    int mCount;
    int mItemSize;
    int mHeap;
    int (*mCompare)(void *, void *);
    void *mpNodes;
} DSList_t;

/* Visit callback of 0x801C6D34: item, then the caller's context and argument, passed through unchanged
   by the type's traverse function (the bintree collector 0x801C82E0 takes an index pointer there). */
typedef int (*DSListVisitFn_t)(void *pItem, void *pCtx, void *pArg);
/* Search callback of 0x801C6DCC: item, key and result pointer. */
typedef int (*DSListSearchFn_t)(void *pItem, void *pKey, void *pResult);

typedef struct DSListType_t {
    void (*mInit)(DSList_t *);
    int (*mDelete)(DSList_t *);
    void (*mInitNode)(DSListNode_t *, int);
    DSListNode_t *(*mAdd)(DSList_t *, DSListNode_t *, int);
    DSListNode_t *(*mGet)(DSList_t *, DSListNode_t *, int);
    void (*mRemove)(DSList_t *, DSListNode_t *);
    int (*mTraverse)(DSList_t *, DSListNode_t *, void *, void *, DSListVisitFn_t, int);
    int (*mSearch)(DSList_t *, DSListNode_t *, void *, void *, DSListSearchFn_t);
    void (*mOptimize)(DSList_t *);
    int mHeaderSize;
    int mNodeSize;
    unsigned char mActive;
} DSListType_t;

extern DSListType_t DSList_Interface[9];

typedef struct LinkNode_t {
    unsigned int mFlags;
    int mUnused;
    struct LinkNode_t *mpPrev;
    struct LinkNode_t *mpNext;
} LinkNode_t;

typedef struct LinkList_t {
    DSList_t mBase;
    LinkNode_t *mpHead;
    LinkNode_t *mpTail;
} LinkList_t;

typedef struct SplayNode_801C7684 {
    unsigned int mFlags;
    int mUnused;
    struct SplayNode_801C7684 *mpLeft;
    struct SplayNode_801C7684 *mpRight;
} SplayNode_801C7684;

typedef struct SplayTree_801C7684 {
    DSList_t mBase;
    SplayNode_801C7684 mNil;
    SplayNode_801C7684 *mpFirst;
    SplayNode_801C7684 *mpLast;
    SplayNode_801C7684 *mpNil;
    SplayNode_801C7684 *mpRoot;
} SplayTree_801C7684;

/* Threaded binary tree node: flag bits 0x1/0x2 mark the left/right link as a thread,
   0x4/0x8 first/last in order, 0x10/0x20 left/right child of the parent. */
typedef struct BinNode_t {
    unsigned int mFlags;
    int mUnused;
    unsigned char mDepth;
    struct BinNode_t *mpLeft;
    struct BinNode_t *mpRight;
} BinNode_t;

typedef struct BinTree_t {
    DSList_t mBase;
    unsigned int mMaxDepth;
    unsigned int mTotalDepth;
    unsigned char mAutoOptimize;
    float mAvgLimit;
    float mDepthLimit;
    BinNode_t **mppScratch;
    BinNode_t *mpRoot;
} BinTree_t;

typedef struct NodePool_t {
    unsigned int mCount;
    int mNodeSize;
    int mFree;
    int mHeap;
    void *mpStack;
    char *mpNodes;
} NodePool_t;

int DSAlignSize(int size);
void DSAddListType(int type, void (*init)(DSList_t *), int (*del)(DSList_t *),
                 void (*initNode)(DSListNode_t *, int),
                 DSListNode_t *(*add)(DSList_t *, DSListNode_t *, int),
                 DSListNode_t *(*get)(DSList_t *, DSListNode_t *, int),
                 void (*remove)(DSList_t *, DSListNode_t *),
                 int (*traverse)(DSList_t *, DSListNode_t *, void *, void *, DSListVisitFn_t, int),
                 int (*search)(DSList_t *, DSListNode_t *, void *, void *, DSListSearchFn_t),
                 void (*optimize)(DSList_t *), int headerSize, int nodeSize);

void *DSNewListNode(void *pool);
void *DSGetListNode(DSList_t *pList, int mode);
void DSRemoveListNode(DSList_t *pList, void *item);
void DSDelListNode(DSList_t *pList, void *item);
void *DSNextListNode(DSList_t *pList, void *item);
int DSTraverseList(DSList_t *pList, void *pStart, void *pCtx, void *pArg, DSListVisitFn_t fn, int direction);
int DSSearchList(DSList_t *pList, void *pStart, void *pKey, void *pResult, DSListSearchFn_t fn);
int DSGetNodeHandlerMemSize(unsigned int count, int size);
unsigned int DSGetNodeHandlerStat(NodePool_t *pPool, unsigned int stat);
NodePool_t *DSNewNodeHandler(int heap, unsigned int count, int size, NodePool_t *pPool);
int DSDelNodeHandler(NodePool_t *pPool);
void *DSNewNode(NodePool_t *pPool);
void DSDelNode(NodePool_t *pPool, void *pNode);

#endif
