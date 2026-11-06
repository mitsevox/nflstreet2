/* Object manager: pools of typed game objects and ordered object lists, with per-type
   functions run over each list every frame in fixed time steps. */

#include "game/fn_801C68FC.h"
#include "game/fn_801D2B7C.h"
#include "engine/object.h"
#include "engine/fn_801F7BD4.h"

extern void *fn_801C6A20(void *pool);
extern void *fn_801C6B4C(void *pool, void *item);
extern void fn_801C6C0C(void *pool, void *item);
extern void *fn_801C6C84(void *pool, void *item);
extern int fn_801C6D34(void *pool, int b, void *ctx, int d, int (*fn)(void *, void *), int f);
extern int fn_801C6DCC(void *pool, int a, void *pKey, void *pResult, int (*match)(void *, void *));
extern unsigned int fn_801C6880(void *pool, int c);
extern void *DSNewNodeHandler(int a, int count, int size, void *pMemory);
extern int DSDelNodeHandler(void *pPool);
extern void *DSNewNode(void *pPool);
extern void DSDelNode(void *pPool, void *pElement);
extern void *memset(void *pDst, int value, unsigned int size);

extern unsigned char lbl_803EBD50;
extern int lbl_803ED640;
extern ObjType_t *lbl_803ED644;

void ObjDel(Obj_t *pObj);
int ObjDelType(int type);

int _ObjDefaultInsertFunc(Obj_t **ppA, Obj_t **ppB)
{
    unsigned int a = (*ppA)->mPriority;
    unsigned int b = (*ppB)->mPriority;

    if (a == b) {
        return 0;
    }
    if (a < b) {
        return -1;
    }
    return 1;
}

void _ObjProcessListSingleFunc(ObjList_t *pList, int time, int step, int func)
{
    Obj_t **pNode;

    for (; time >= step; time -= step) {
        for (pNode = fn_801C6B4C(pList->mpList, 0); pNode != 0; pNode = fn_801C6C84(pList->mpList, pNode)) {
            ObjFunc_t fn = pList->mFuncs[(*pNode)->mType * pList->mFuncCount + func];
            if (fn != 0) {
                fn(*pNode, step);
            }
        }
    }
    pList->mTime = time;
}

void _ObjProcessListObjsFirst(ObjList_t *pList, int time, int step)
{
    Obj_t **pNode;
    int first;
    int i;

    for (; time >= step; time -= step) {
        for (pNode = fn_801C6B4C(pList->mpList, 0); pNode != 0; pNode = fn_801C6C84(pList->mpList, pNode)) {
            first = (*pNode)->mType * pList->mFuncCount;
            for (i = 0; i < pList->mFuncCount; i++) {
                ObjFunc_t fn = pList->mFuncs[first + i];
                if (fn != 0) {
                    fn(*pNode, step);
                }
            }
        }
    }
    pList->mTime = time;
}

void _ObjProcessListFuncsFirst(ObjList_t *pList, int time, int step)
{
    Obj_t **pNode;
    int rest;
    int i;

    while (time >= step) {
        rest = time - step;
        for (i = 0; i < pList->mFuncCount; i++) {
            for (pNode = fn_801C6B4C(pList->mpList, 0); pNode != 0; pNode = fn_801C6C84(pList->mpList, pNode)) {
                ObjFunc_t fn = pList->mFuncs[(*pNode)->mType * pList->mFuncCount + i];
                if (fn != 0) {
                    fn(*pNode, step);
                }
            }
        }
        time = rest;
    }
    pList->mTime = time;
}

void _ObjProcessList(ObjList_t *pList, int time, unsigned int mode, int func)
{
    int step = pList->mStep;

    if (step != -1) {
        time += pList->mTime;
    } else {
        step = time;
    }
    if (fn_801C6880(pList->mpList, 3) != 0) {
        switch (mode) {
        case 0:
            _ObjProcessListObjsFirst(pList, time, step);
            break;
        case 1:
            _ObjProcessListFuncsFirst(pList, time, step);
            break;
        case 2:
            _ObjProcessListSingleFunc(pList, time, step, func);
            break;
        }
    }
}

int _ObjNewTypeList(int count)
{
    ObjType_t *pTypes;
    int result = 0;
    int i;

    pTypes = fn_801D2BB0(1, count * sizeof(ObjType_t), 0, 0);
    if (pTypes != 0) {
        for (i = 0; i < count; i++) {
            pTypes[i].mSize = 0;
        }
        lbl_803ED640 = count;
        result = 1;
        lbl_803ED644 = pTypes;
    }
    return result;
}

void _ObjDelTypeList(void)
{
    unsigned char i;

    for (i = 0; i < lbl_803ED640; i++) {
        ObjDelType(i);
    }
    fn_801D2BD0(lbl_803ED644);
}

int _ObjDelListTraverseFunc(void *pNode, void *pContext)
{
    Obj_t *pObj = *(Obj_t **)pNode;

    if (--pObj->mRefCount == 0) {
        ObjDel(pObj);
    }
    return 1;
}

int _ObjListTraverseFunc(void *pNode, void *pContext)
{
    if (*(Obj_t **)pNode != *(Obj_t **)pContext) {
        return 1;
    }
    *(void **)pContext = pNode;
    return 0;
}

int ObjInit(int count)
{
    if (lbl_803EBD50 == 0) {
        if (_ObjNewTypeList(count) != 0) {
            lbl_803EBD50 = 1;
            return 0;
        }
        return fn_801F7C88();
    }
    return 0x90001;
}

int ObjShutdown(void)
{
    if (lbl_803EBD50 == 0) {
        return 0x90002;
    }
    _ObjDelTypeList();
    lbl_803EBD50 = 0;
    return 0;
}

int ObjNewType_(int type, int size, int count, ObjNewFunc_t pNew, ObjDelFunc_t pDel)
{
    ObjType_t *pType = &lbl_803ED644[type];
    int err = 0;

    pType->mSize = size;
    pType->mNew = pNew;
    pType->mDel = pDel;
    pType->mCount = count;
    pType->mpPool = DSNewNodeHandler(1, count, size, 0);
    if (pType->mpPool == 0) {
        err = fn_801F7C88();
    }
    fn_801F7BD4(err);
    return err;
}

int ObjDelType(int type)
{
    ObjType_t *pType = &lbl_803ED644[type];
    int err = 0;

    if (pType->mSize != 0) {
        pType->mSize = 0;
        if (pType->mpPool != 0) {
            err = DSDelNodeHandler(pType->mpPool);
        }
    }
    fn_801F7BD4(err);
    return err;
}

ObjList_t *ObjNewList(int a, int b, int c, ObjInsertFunc_t pInsert, ObjFindFunc_t pFind,
                              int funcCount, int unknown10, int step)
{
    ObjList_t *pList;
    int size = funcCount * lbl_803ED640 * sizeof(ObjFunc_t);

    pList = fn_801D2BB0(a, size + sizeof(ObjList_t), 0, 0);
    if (pList != 0) {
        if (pInsert == 0) {
            pInsert = (ObjInsertFunc_t)_ObjDefaultInsertFunc;
        }
        pList->mpList = fn_801C68FC(a, c, b, 4, (int (*)(void *, void *))pInsert, 0);
        pList->mUnknown4 = c;
        pList->mInsert = pInsert;
        pList->mFind = pFind;
        pList->mUnknown10 = unknown10;
        pList->mFuncCount = funcCount;
        pList->mUnknown18 = a;
        pList->mStep = step;
        pList->mTime = 0;
        if (size != 0) {
            memset(pList->mFuncs, 0, size);
        }
    }
    return pList;
}

void ObjSetListObjFunc(ObjList_t *pList, int type, int func, ObjFunc_t fn)
{
    ObjFunc_t *pFuncs = pList->mFuncs + type * pList->mFuncCount;
    pFuncs += func;
    *pFuncs = fn;
}

void ObjDelList(ObjList_t *pList)
{
    fn_801C6D34(pList->mpList, 0, 0, 0, _ObjDelListTraverseFunc, 1);
    fn_801C69E4(pList->mpList);
    fn_801D2BD0(pList);
}

void ObjProcessListFunc(ObjList_t *pList, int time, int func)
{
    _ObjProcessList(pList, time, 2, func);
}

Obj_t *ObjNew(int type, int subType, int arg)
{
    Obj_t *pObj;

    pObj = DSNewNode(lbl_803ED644[type].mpPool);
    if (pObj != 0) {
        memset(pObj, 0, lbl_803ED644[type].mSize);
        pObj->mType = type;
        pObj->mSubType = subType;
        pObj->mPriority = 2;
        if (lbl_803ED644[type].mNew != 0) {
            lbl_803ED644[type].mNew(pObj, arg);
        }
    }
    return pObj;
}

int ObjAddToList(ObjList_t *pList, Obj_t *pObj)
{
    Obj_t **pNode;

    pNode = fn_801C6A20(pList->mpList);
    if (pNode != 0) {
        *pNode = pObj;
        fn_801C6AA4(pList->mpList, pNode, 0);
        pObj->mRefCount++;
        return 0;
    }
    return fn_801F7C88();
}

Obj_t *ObjNewInList(ObjList_t *pList, int type, int subType, int arg)
{
    Obj_t *pObj;

    pObj = ObjNew(type, subType, arg);
    if (pObj != 0) {
        ObjAddToList(pList, pObj);
    }
    return pObj;
}

void ObjDel(Obj_t *pObj)
{
    if (lbl_803ED644[pObj->mType].mDel != 0) {
        lbl_803ED644[pObj->mType].mDel(pObj);
    }
    DSDelNode(lbl_803ED644[pObj->mType].mpPool, pObj);
}

void ObjRemoveFromList(ObjList_t *pList, Obj_t *pObj)
{
    void *pNode = pObj;

    if (pList->mFind != 0) {
        fn_801C6DCC(pList->mpList, 0, &pNode, 0, pList->mFind);
    } else {
        fn_801C6D34(pList->mpList, 0, &pNode, 0, _ObjListTraverseFunc, 1);
    }
    fn_801C6C0C(pList->mpList, pNode);
    pObj->mRefCount--;
}

void ObjSetPriority(ObjList_t *pList, Obj_t *pObj, int priority)
{
    ObjRemoveFromList(pList, pObj);
    pObj->mPriority = priority;
    ObjAddToList(pList, pObj);
}

void ObjClearList(ObjList_t *pList)
{
    Obj_t **pNode;
    Obj_t **pNext;

    for (pNode = fn_801C6B4C(pList->mpList, 0); pNode != 0; pNode = pNext) {
        (*pNode)->mRefCount--;
        if ((*pNode)->mRefCount == 0) {
            ObjDel(*pNode);
        }
        pNext = fn_801C6C84(pList->mpList, pNode);
        fn_801C6C0C(pList->mpList, pNode);
    }
}

unsigned int ObjGetListInfo(ObjList_t *pList, int c)
{
    return fn_801C6880(pList->mpList, c);
}
