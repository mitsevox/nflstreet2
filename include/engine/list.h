#ifndef ENGINE_LIST_H
#define ENGINE_LIST_H

/* Node header word: bit 31 is set while the node is linked into its list. */
typedef struct Node_801C6A20 {
    unsigned int mFlags;
} Node_801C6A20;

typedef struct List_801C68FC {
    int mType;
    int mCount;
    int mItemSize;
    int mHeap;
    int (*mCompare)(void *, void *);
    void *mpNodes;
} List_801C68FC;

/* Visit callback of 0x801C6D34: item, then the caller's context and argument, passed through unchanged
   by the type's traverse function (the bintree collector 0x801C82E0 takes an index pointer there). */
typedef int (*ListVisitFn_801C6D34)(void *pItem, void *pCtx, void *pArg);
/* Search callback of 0x801C6DCC: item, key and result pointer. */
typedef int (*ListSearchFn_801C6DCC)(void *pItem, void *pKey, void *pResult);

typedef struct ListType_803D4FB8 {
    void (*mInit)(List_801C68FC *);
    int (*mDelete)(List_801C68FC *);
    void (*mInitNode)(Node_801C6A20 *, int);
    Node_801C6A20 *(*mAdd)(List_801C68FC *, Node_801C6A20 *, int);
    Node_801C6A20 *(*mGet)(List_801C68FC *, Node_801C6A20 *, int);
    void (*mRemove)(List_801C68FC *, Node_801C6A20 *);
    int (*mTraverse)(List_801C68FC *, Node_801C6A20 *, void *, void *, ListVisitFn_801C6D34, int);
    int (*mSearch)(List_801C68FC *, Node_801C6A20 *, void *, void *, ListSearchFn_801C6DCC);
    void (*mOptimize)(List_801C68FC *);
    int mHeaderSize;
    int mNodeSize;
    unsigned char mActive;
} ListType_803D4FB8;

extern ListType_803D4FB8 lbl_803D4FB8[9];

typedef struct LinkNode_t {
    unsigned int mFlags;
    int mUnused;
    struct LinkNode_t *mpPrev;
    struct LinkNode_t *mpNext;
} LinkNode_t;

typedef struct LinkList_t {
    List_801C68FC mBase;
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
    List_801C68FC mBase;
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
    List_801C68FC mBase;
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
void fn_801C67AC(int type, void (*init)(List_801C68FC *), int (*del)(List_801C68FC *),
                 void (*initNode)(Node_801C6A20 *, int),
                 Node_801C6A20 *(*add)(List_801C68FC *, Node_801C6A20 *, int),
                 Node_801C6A20 *(*get)(List_801C68FC *, Node_801C6A20 *, int),
                 void (*remove)(List_801C68FC *, Node_801C6A20 *),
                 int (*traverse)(List_801C68FC *, Node_801C6A20 *, void *, void *, ListVisitFn_801C6D34, int),
                 int (*search)(List_801C68FC *, Node_801C6A20 *, void *, void *, ListSearchFn_801C6DCC),
                 void (*optimize)(List_801C68FC *), int headerSize, int nodeSize);

void *fn_801C6A20(void *pool);
void *fn_801C6B4C(List_801C68FC *pList, int mode);
void fn_801C6BC0(List_801C68FC *pList, void *item);
void fn_801C6C0C(List_801C68FC *pList, void *item);
void *fn_801C6C84(List_801C68FC *pList, void *item);
int fn_801C6D34(List_801C68FC *pList, void *pStart, void *pCtx, void *pArg, ListVisitFn_801C6D34 fn, int direction);
int fn_801C6DCC(List_801C68FC *pList, void *pStart, void *pKey, void *pResult, ListSearchFn_801C6DCC fn);
int DSGetNodeHandlerMemSize(unsigned int count, int size);
unsigned int DSGetNodeHandlerStat(NodePool_t *pPool, unsigned int stat);
NodePool_t *DSNewNodeHandler(int heap, unsigned int count, int size, NodePool_t *pPool);
int DSDelNodeHandler(NodePool_t *pPool);
void *DSNewNode(NodePool_t *pPool);
void DSDelNode(NodePool_t *pPool, void *pNode);

#endif
