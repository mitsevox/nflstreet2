#include "game/fn_801C68FC.h"
#include "game/fn_801D2B7C.h"
#include "engine/cu_801DCA10.h"
#include "engine/fn_801F7BD4.h"

extern void *fn_801C6A20(void *pool);
extern void *fn_801C6B4C(void *pool, void *item);
extern void fn_801C6C0C(void *pool, void *item);
extern void *fn_801C6C84(void *pool, void *item);
extern int fn_801C6D34(void *pool, int b, void *ctx, int d, int (*fn)(void *, void *), int f);
extern int fn_801C6DCC(void *pool, int a, void *pKey, void *pResult, int (*match)(void *, void *));
extern unsigned int fn_801C6880(void *pool, int c);
extern void *fn_801C750C(int a, int count, int size, void *pMemory);
extern int fn_801C75B8(void *pPool);
extern void *fn_801C75F0(void *pPool);
extern void fn_801C7650(void *pPool, void *pElement);
extern void *memset(void *pDst, int value, unsigned int size);

extern unsigned char lbl_803EBD50;
extern int lbl_803ED640;
extern ObjType_801DCA10 *lbl_803ED644;

void fn_801DD2B8(Obj_801DCA10 *pObj);
int fn_801DCF8C(int type);

int fn_801DCA10(Obj_801DCA10 **ppA, Obj_801DCA10 **ppB)
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

void fn_801DCA44(ObjList_801DCA10 *pList, int time, int step, int func)
{
    Obj_801DCA10 **pNode;

    for (; time >= step; time -= step) {
        for (pNode = fn_801C6B4C(pList->mpList, 0); pNode != 0; pNode = fn_801C6C84(pList->mpList, pNode)) {
            ObjFunc_801DCA10 fn = pList->mFuncs[(*pNode)->mType * pList->mFuncCount + func];
            if (fn != 0) {
                fn(*pNode, step);
            }
        }
    }
    pList->mTime = time;
}

void fn_801DCAF0(ObjList_801DCA10 *pList, int time, int step)
{
    Obj_801DCA10 **pNode;
    int first;
    int i;

    for (; time >= step; time -= step) {
        for (pNode = fn_801C6B4C(pList->mpList, 0); pNode != 0; pNode = fn_801C6C84(pList->mpList, pNode)) {
            first = (*pNode)->mType * pList->mFuncCount;
            for (i = 0; i < pList->mFuncCount; i++) {
                ObjFunc_801DCA10 fn = pList->mFuncs[first + i];
                if (fn != 0) {
                    fn(*pNode, step);
                }
            }
        }
    }
    pList->mTime = time;
}

void fn_801DCBBC(ObjList_801DCA10 *pList, int time, int step)
{
    Obj_801DCA10 **pNode;
    int rest;
    int i;

    while (time >= step) {
        rest = time - step;
        for (i = 0; i < pList->mFuncCount; i++) {
            for (pNode = fn_801C6B4C(pList->mpList, 0); pNode != 0; pNode = fn_801C6C84(pList->mpList, pNode)) {
                ObjFunc_801DCA10 fn = pList->mFuncs[(*pNode)->mType * pList->mFuncCount + i];
                if (fn != 0) {
                    fn(*pNode, step);
                }
            }
        }
        time = rest;
    }
    pList->mTime = time;
}

void fn_801DCC84(ObjList_801DCA10 *pList, int time, unsigned int mode, int func)
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
            fn_801DCAF0(pList, time, step);
            break;
        case 1:
            fn_801DCBBC(pList, time, step);
            break;
        case 2:
            fn_801DCA44(pList, time, step, func);
            break;
        }
    }
}

int fn_801DCD40(int count)
{
    ObjType_801DCA10 *pTypes;
    int result = 0;
    int i;

    pTypes = fn_801D2BB0(1, count * sizeof(ObjType_801DCA10), 0, 0);
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

void fn_801DCDB8(void)
{
    unsigned char i;

    for (i = 0; i < lbl_803ED640; i++) {
        fn_801DCF8C(i);
    }
    fn_801D2BD0(lbl_803ED644);
}

int fn_801DCE10(void *pNode, void *pContext)
{
    Obj_801DCA10 *pObj = *(Obj_801DCA10 **)pNode;

    if (--pObj->mRefCount == 0) {
        fn_801DD2B8(pObj);
    }
    return 1;
}

int fn_801DCE50(void *pNode, void *pContext)
{
    if (*(Obj_801DCA10 **)pNode != *(Obj_801DCA10 **)pContext) {
        return 1;
    }
    *(void **)pContext = pNode;
    return 0;
}

int fn_801DCE74(int count)
{
    if (lbl_803EBD50 == 0) {
        if (fn_801DCD40(count) != 0) {
            lbl_803EBD50 = 1;
            return 0;
        }
        return fn_801F7C88();
    }
    return 0x90001;
}

int fn_801DCEC8(void)
{
    if (lbl_803EBD50 == 0) {
        return 0x90002;
    }
    fn_801DCDB8();
    lbl_803EBD50 = 0;
    return 0;
}

int fn_801DCF0C(int type, int size, int count, ObjNewFunc_801DCA10 pNew, ObjDelFunc_801DCA10 pDel)
{
    ObjType_801DCA10 *pType = &lbl_803ED644[type];
    int err = 0;

    pType->mSize = size;
    pType->mNew = pNew;
    pType->mDel = pDel;
    pType->mCount = count;
    pType->mpPool = fn_801C750C(1, count, size, 0);
    if (pType->mpPool == 0) {
        err = fn_801F7C88();
    }
    fn_801F7BD4(err);
    return err;
}

int fn_801DCF8C(int type)
{
    ObjType_801DCA10 *pType = &lbl_803ED644[type];
    int err = 0;

    if (pType->mSize != 0) {
        pType->mSize = 0;
        if (pType->mpPool != 0) {
            err = fn_801C75B8(pType->mpPool);
        }
    }
    fn_801F7BD4(err);
    return err;
}

ObjList_801DCA10 *fn_801DCFF0(int a, int b, int c, ObjInsertFunc_801DCA10 pInsert, ObjFindFunc_801DCA10 pFind,
                              int funcCount, int unknown10, int step)
{
    ObjList_801DCA10 *pList;
    int size = funcCount * lbl_803ED640 * sizeof(ObjFunc_801DCA10);

    pList = fn_801D2BB0(a, size + sizeof(ObjList_801DCA10), 0, 0);
    if (pList != 0) {
        if (pInsert == 0) {
            pInsert = (ObjInsertFunc_801DCA10)fn_801DCA10;
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

void fn_801DD0C8(ObjList_801DCA10 *pList, int type, int func, ObjFunc_801DCA10 fn)
{
    ObjFunc_801DCA10 *pFuncs = pList->mFuncs + type * pList->mFuncCount;
    pFuncs += func;
    *pFuncs = fn;
}

void fn_801DD0E8(ObjList_801DCA10 *pList)
{
    fn_801C6D34(pList->mpList, 0, 0, 0, fn_801DCE10, 1);
    fn_801C69E4(pList->mpList);
    fn_801D2BD0(pList);
}

void fn_801DD140(ObjList_801DCA10 *pList, int time, int func)
{
    fn_801DCC84(pList, time, 2, func);
}

Obj_801DCA10 *fn_801DD168(int type, int subType, int arg)
{
    Obj_801DCA10 *pObj;

    pObj = fn_801C75F0(lbl_803ED644[type].mpPool);
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

int fn_801DD200(ObjList_801DCA10 *pList, Obj_801DCA10 *pObj)
{
    Obj_801DCA10 **pNode;

    pNode = fn_801C6A20(pList->mpList);
    if (pNode != 0) {
        *pNode = pObj;
        fn_801C6AA4(pList->mpList, pNode, 0);
        pObj->mRefCount++;
        return 0;
    }
    return fn_801F7C88();
}

Obj_801DCA10 *fn_801DD268(ObjList_801DCA10 *pList, int type, int subType, int arg)
{
    Obj_801DCA10 *pObj;

    pObj = fn_801DD168(type, subType, arg);
    if (pObj != 0) {
        fn_801DD200(pList, pObj);
    }
    return pObj;
}

void fn_801DD2B8(Obj_801DCA10 *pObj)
{
    if (lbl_803ED644[pObj->mType].mDel != 0) {
        lbl_803ED644[pObj->mType].mDel(pObj);
    }
    fn_801C7650(lbl_803ED644[pObj->mType].mpPool, pObj);
}

void fn_801DD320(ObjList_801DCA10 *pList, Obj_801DCA10 *pObj)
{
    void *pNode = pObj;

    if (pList->mFind != 0) {
        fn_801C6DCC(pList->mpList, 0, &pNode, 0, pList->mFind);
    } else {
        fn_801C6D34(pList->mpList, 0, &pNode, 0, fn_801DCE50, 1);
    }
    fn_801C6C0C(pList->mpList, pNode);
    pObj->mRefCount--;
}

void fn_801DD3AC(ObjList_801DCA10 *pList, Obj_801DCA10 *pObj, int priority)
{
    fn_801DD320(pList, pObj);
    pObj->mPriority = priority;
    fn_801DD200(pList, pObj);
}

void fn_801DD3F0(ObjList_801DCA10 *pList)
{
    Obj_801DCA10 **pNode;
    Obj_801DCA10 **pNext;

    for (pNode = fn_801C6B4C(pList->mpList, 0); pNode != 0; pNode = pNext) {
        (*pNode)->mRefCount--;
        if ((*pNode)->mRefCount == 0) {
            fn_801DD2B8(*pNode);
        }
        pNext = fn_801C6C84(pList->mpList, pNode);
        fn_801C6C0C(pList->mpList, pNode);
    }
}

unsigned int fn_801DD474(ObjList_801DCA10 *pList, int c)
{
    return fn_801C6880(pList->mpList, c);
}
