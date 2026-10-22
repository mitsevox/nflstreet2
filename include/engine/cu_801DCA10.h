#ifndef ENGINE_CU_801DCA10_H
#define ENGINE_CU_801DCA10_H

/* Object type table and object lists of the 0x801DCA10-0x801DD498 object manager. */

typedef struct Obj_801DCA10 {
    unsigned char mType;
    unsigned char mSubType;
    unsigned char mRefCount;
    char mUnknown3[0x10 - 0x3];
    unsigned short mPriority;
} Obj_801DCA10;

typedef void (*ObjNewFunc_801DCA10)(Obj_801DCA10 *pObj, int arg);
typedef void (*ObjDelFunc_801DCA10)(Obj_801DCA10 *pObj);
typedef void (*ObjFunc_801DCA10)(Obj_801DCA10 *pObj, int step);
typedef int (*ObjInsertFunc_801DCA10)(Obj_801DCA10 **ppA, Obj_801DCA10 **ppB);
typedef int (*ObjFindFunc_801DCA10)(void *pNode, void *pContext);

typedef struct ObjType_801DCA10 {
    int mSize;
    int mCount;
    ObjNewFunc_801DCA10 mNew;
    ObjDelFunc_801DCA10 mDel;
    void *mpPool;
} ObjType_801DCA10;

typedef struct ObjList_801DCA10 {
    void *mpList;
    int mUnknown4;
    ObjInsertFunc_801DCA10 mInsert;
    ObjFindFunc_801DCA10 mFind;
    int mUnknown10;
    int mFuncCount;
    int mUnknown18;
    int mStep;
    int mTime;
    ObjFunc_801DCA10 mFuncs[1];
} ObjList_801DCA10;

#endif
