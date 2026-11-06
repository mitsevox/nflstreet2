#ifndef ENGINE_OBJECT_H
#define ENGINE_OBJECT_H

/* Object type table and object lists of the 0x801DCA10-0x801DD498 object manager. */

typedef struct Obj_t {
    unsigned char mType;
    unsigned char mSubType;
    unsigned char mRefCount;
    char mUnknown3[0x10 - 0x3];
    unsigned short mPriority;
} Obj_t;

typedef void (*ObjNewFunc_t)(Obj_t *pObj, int arg);
typedef void (*ObjDelFunc_t)(Obj_t *pObj);
typedef void (*ObjFunc_t)(Obj_t *pObj, int step);
typedef int (*ObjInsertFunc_t)(Obj_t **ppA, Obj_t **ppB);
typedef int (*ObjFindFunc_t)(void *pNode, void *pContext);

typedef struct ObjType_t {
    int mSize;
    int mCount;
    ObjNewFunc_t mNew;
    ObjDelFunc_t mDel;
    void *mpPool;
} ObjType_t;

typedef struct ObjList_t {
    void *mpList;
    int mUnknown4;
    ObjInsertFunc_t mInsert;
    ObjFindFunc_t mFind;
    int mUnknown10;
    int mFuncCount;
    int mUnknown18;
    int mStep;
    int mTime;
    ObjFunc_t mFuncs[1];
} ObjList_t;

#endif
