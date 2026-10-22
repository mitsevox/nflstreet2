#ifndef ENGINE_CU_801C665C_H
#define ENGINE_CU_801C665C_H

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

/* Visit callback of 0x801C6D34: item and the caller's context. */
typedef int (*ListVisitFn_801C6D34)(void *pItem, void *pCtx);
/* Search callback of 0x801C6DCC: item, key and result pointer. */
typedef int (*ListSearchFn_801C6DCC)(void *pItem, void *pKey, void *pResult);

typedef struct ListType_803D4FB8 {
    void (*mInit)(List_801C68FC *);
    int (*mDelete)(List_801C68FC *);
    void (*mInitNode)(Node_801C6A20 *, int);
    Node_801C6A20 *(*mAdd)(List_801C68FC *, Node_801C6A20 *, int);
    Node_801C6A20 *(*mGet)(List_801C68FC *, Node_801C6A20 *, int);
    void (*mRemove)(List_801C68FC *, Node_801C6A20 *);
    int (*mTraverse)(List_801C68FC *, Node_801C6A20 *, void *, int, ListVisitFn_801C6D34, int);
    int (*mSearch)(List_801C68FC *, Node_801C6A20 *, void *, void *, ListSearchFn_801C6DCC);
    void (*mOptimize)(List_801C68FC *);
    int mHeaderSize;
    int mNodeSize;
    unsigned char mActive;
} ListType_803D4FB8;

extern ListType_803D4FB8 lbl_803D4FB8[9];

typedef struct LinkNode_801C6E5C {
    unsigned int mFlags;
    int mUnused;
    struct LinkNode_801C6E5C *mpPrev;
    struct LinkNode_801C6E5C *mpNext;
} LinkNode_801C6E5C;

typedef struct LinkList_801C6E5C {
    List_801C68FC mBase;
    LinkNode_801C6E5C *mpHead;
    LinkNode_801C6E5C *mpTail;
} LinkList_801C6E5C;

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
typedef struct BinNode_801C7F70 {
    unsigned int mFlags;
    int mUnused;
    unsigned char mDepth;
    struct BinNode_801C7F70 *mpLeft;
    struct BinNode_801C7F70 *mpRight;
} BinNode_801C7F70;

typedef struct BinTree_801C7F70 {
    List_801C68FC mBase;
    unsigned int mMaxDepth;
    unsigned int mTotalDepth;
    unsigned char mAutoOptimize;
    float mAvgLimit;
    float mDepthLimit;
    BinNode_801C7F70 **mppScratch;
    BinNode_801C7F70 *mpRoot;
} BinTree_801C7F70;

typedef struct NodePool_801C750C {
    unsigned int mCount;
    int mNodeSize;
    int mFree;
    int mHeap;
    void *mpStack;
    char *mpNodes;
} NodePool_801C750C;

int fn_801C6644(int size);
void fn_801C67AC(int type, void (*init)(List_801C68FC *), int (*del)(List_801C68FC *),
                 void (*initNode)(Node_801C6A20 *, int),
                 Node_801C6A20 *(*add)(List_801C68FC *, Node_801C6A20 *, int),
                 Node_801C6A20 *(*get)(List_801C68FC *, Node_801C6A20 *, int),
                 void (*remove)(List_801C68FC *, Node_801C6A20 *),
                 int (*traverse)(List_801C68FC *, Node_801C6A20 *, void *, int, ListVisitFn_801C6D34, int),
                 int (*search)(List_801C68FC *, Node_801C6A20 *, void *, void *, ListSearchFn_801C6DCC),
                 void (*optimize)(List_801C68FC *), int headerSize, int nodeSize);

void *fn_801C6A20(void *pool);
void *fn_801C6B4C(List_801C68FC *pList, int mode);
void fn_801C6BC0(List_801C68FC *pList, void *item);
void fn_801C6C0C(List_801C68FC *pList, void *item);
void *fn_801C6C84(List_801C68FC *pList, void *item);
int fn_801C6D34(List_801C68FC *pList, void *pStart, void *pCtx, int arg, ListVisitFn_801C6D34 fn, int direction);
int fn_801C6DCC(List_801C68FC *pList, void *pStart, void *pKey, void *pResult, ListSearchFn_801C6DCC fn);
int fn_801C74A0(unsigned int count, int size);
unsigned int fn_801C74C8(NodePool_801C750C *pPool, unsigned int stat);
NodePool_801C750C *fn_801C750C(int heap, unsigned int count, int size, NodePool_801C750C *pPool);
int fn_801C75B8(NodePool_801C750C *pPool);
void *fn_801C75F0(NodePool_801C750C *pPool);
void fn_801C7650(NodePool_801C750C *pPool, void *pNode);

#endif
