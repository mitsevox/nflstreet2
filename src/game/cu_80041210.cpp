#include "game/cu_80041210.h"
#include "game/Object_80040818.h"
#include "game/fn_80238174.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801BE60C.h"
#include <string.h>

struct Pool_803EA488 {
    Object_80041904 *mObjects;
    Extra_8004149C *mExtras;
    unsigned short mCount;
    unsigned short mMaxObjects;
    unsigned short mExtraCount;
    unsigned short mMaxExtras;
};

extern "C" {
int fn_80040A70(Object_80041904 *pObject, int index);
Object_80040818 *fn_80040F18(int index);
int fn_80041094(int index);
int fn_800410B8(int index);
void fn_8004A8C4(Extra_8004149C *pExtra, int entry, int a);
void fn_8004A8E8(int entry, void *a, int b, void *c);
void fn_8004A908(Object_80041904 *pObject, int index);
void fn_8004C684(void *pOwner, Object_80041904 *pObject);
void fn_8004C7B8(Object_80041904 *pObject);
void fn_801BA03C(void *a, void *b, Object_80041904 *pObject, float c);
int fn_801BC7C0(void *a, void *b, void *c);
int fn_801BCA74(void *a, void *b, int c, void *d, int e, int f);
int fn_801BCCAC(void *a, void *b, int c, void *d, int e, int f);
void fn_801BE420(void *a, void *b, void *c, Object_80041904 *pObject, float d);
void fn_801EBFA0(float *pOut, int x, int y, int z);
int fn_80238278(const void *p, int size, int seed);
void *fn_8023816C(void *pHandle);

Pool_803EA488 *lbl_803EA488 = 0;
unsigned int lbl_803EA48C = 0;

int fn_80041210(void *p, int value)
{
    Pool_803EA488 *pPool = (Pool_803EA488 *)p;
    int i;

    pPool->mObjects = (Object_80041904 *)fn_801D2B7C(pPool->mMaxObjects * 432, 0, 0);
    memset(pPool->mObjects, 0, pPool->mMaxObjects * 432);
    pPool->mExtras = (Extra_8004149C *)fn_801D2B7C(pPool->mMaxExtras * 1712, 0, 0);
    memset(pPool->mExtras, 0, pPool->mMaxExtras * 1712);
    for (i = 0; i < pPool->mMaxObjects; i++) {
    }
    return 0;
}

int fn_800412A8(void *p, int value)
{
    Pool_803EA488 *pPool = (Pool_803EA488 *)p;
    unsigned short i;

    for (i = 0; i < pPool->mMaxObjects; i++) {
        fn_8004C7B8(&pPool->mObjects[i]);
    }
    fn_801D2BD0(pPool->mObjects);
    pPool->mObjects = 0;
    fn_801D2BD0(pPool->mExtras);
    pPool->mExtras = 0;
    return 0;
}

int fn_80041324(void *p, int value)
{
    Pool_803EA488 *pPool = (Pool_803EA488 *)p;
    unsigned int i;

    for (i = 0; i < pPool->mMaxObjects; i++) {
    }
    return 0;
}

int fn_80041348(void *p, void *q)
{
    Pool_803EA488 *pPool = (Pool_803EA488 *)p;
    Pool_803EA488 *pOther = (Pool_803EA488 *)q;
    int result;
    int i;

    if (pOther != 0) {
        result = 0;
        result |= pPool->mCount != pOther->mCount;
        result |= pPool->mMaxObjects != pOther->mMaxObjects;
        for (i = 0; i < pPool->mMaxObjects; i++) {
        }
    } else {
        result = fn_80238278(pPool, 16, 0);
        for (i = 0; i < pPool->mMaxObjects; i++) {
        }
    }
    return result;
}

void fn_800413F0(int maxObjects, int maxExtras)
{
    void *pHandle;
    Pool_803EA488 *pPool;

    pHandle = fn_80238174(0, (void **)&lbl_803EA488, 16, 2, 0x626F626A);
    fn_80238234(pHandle, fn_80041210, fn_800412A8, fn_80041324, fn_80041348);
    pPool = (Pool_803EA488 *)fn_8023816C(pHandle);
    pPool->mCount = 0;
    pPool->mMaxObjects = maxObjects;
    pPool->mExtraCount = 0;
    pPool->mMaxExtras = maxExtras;
    lbl_803EA48C = 0;
    fn_802381E0(pHandle);
}

void fn_80041490(void)
{
    lbl_803EA488 = 0;
}

Object_80041904 *fn_8004149C(void *pOwner, Desc_8004149C *pDesc)
{
    Object_80041904 *pObject = &lbl_803EA488->mObjects[lbl_803EA488->mCount];

    if (fn_800410B8(lbl_803EA488->mCount) != 0) {
        pObject->mUnknown428 = &lbl_803EA488->mExtras[lbl_803EA488->mExtraCount++];
    } else {
        pObject->mUnknown428 = 0;
    }
    pObject->mUnknown0 = pDesc->mUnknown0;
    fn_8004A908(pObject, lbl_803EA488->mCount);
    pObject->mUnknown8 = pDesc->mUnknown4;
    pObject->mUnknown12 = pDesc->mUnknown8;
    pObject->mUnknown16 = pDesc->mUnknown12;
    fn_801EBFA0(&pObject->mUnknown96, (int)(pDesc->mUnknown20 * 46603.3789f), (int)(pDesc->mUnknown24 * 46603.3789f),
                (int)(pDesc->mUnknown16 * 46603.3789f));
    pObject->mUnknown32 = (int)((pDesc->mUnknown24 - 90.0f) * 46603.3789f);
    if (pObject->mUnknown428 != 0) {
        pObject->mUnknown428->mUnknown56 = pObject->mUnknown32;
    }
    pObject->mUnknown112 = pObject->mUnknown8;
    pObject->mUnknown116 = pObject->mUnknown12;
    pObject->mUnknown120 = pObject->mUnknown16;
    pObject->mUnknown124 = pObject->mUnknown96;
    pObject->mUnknown128 = pObject->mUnknown100;
    pObject->mUnknown132 = pObject->mUnknown104;
    pObject->mUnknown136 = pObject->mUnknown108;
    pObject->mUnknown140 = pObject->mUnknown32;
    fn_8004C684(pOwner, pObject);
    if (pObject->mUnknown184 != 0) {
        pObject->mUnknown184(pObject, (int)fn_80040F18(lbl_803EA488->mCount), 0);
    }
    lbl_803EA488->mCount++;
    return pObject;
}

int fn_80041664(void)
{
    unsigned short i;

    for (i = 0; i < lbl_803EA488->mCount; i++) {
        fn_80040A70(&lbl_803EA488->mObjects[i], i);
    }
    return 0;
}

int fn_800416CC(float dt)
{
    unsigned short i;

    for (i = 0; i < lbl_803EA488->mCount; i++) {
        if (fn_80041094(i) != 0) {
            Object_80041904 *pObject = &lbl_803EA488->mObjects[i];
            Extra_8004149C *pExtra = pObject->mUnknown428;
            int a;

            if (pExtra->mUnknown1708 & 8) {
                if (pExtra->mUnknown1708 & 16) {
                    continue;
                }
                pExtra->mUnknown1708 |= 16;
            }
            fn_801BE420(pExtra->mUnknown1300, pExtra->mUnknown48, pExtra->mUnknown60, pObject, dt);
            fn_801BA03C(pExtra->mUnknown48, pExtra->mUnknown60, pObject, dt);
            a = fn_801BC7C0(pExtra->mUnknown48, pExtra->mUnknown60, pExtra->mUnknown1300);
            fn_8004A8C4(pExtra, (int)fn_80040F18(i), a);
            pExtra->mUnknown32 = fn_801BCA74(pExtra->mUnknown48, pExtra->mUnknown60, a, pExtra->mUnknown36, 0xFFFF, 1);
            pExtra->mUnknown33 = fn_801BCCAC(pExtra->mUnknown48, pExtra->mUnknown60, a, pExtra->mUnknown40,
                                             fn_801BE648(pObject->mUnknown428->mUnknown1300), 1);
            fn_8004A8E8((int)fn_80040F18(i), pExtra->mUnknown60, pExtra->mUnknown52, pExtra->mUnknown1300);
        }
    }
    return 0;
}

int fn_8004183C(void)
{
    unsigned short i;

    lbl_803EA48C++;
    for (i = 0; i < lbl_803EA488->mCount; i++) {
        Object_80041904 *pObject = &lbl_803EA488->mObjects[i];

        if (pObject->mUnknown184 != 0) {
            if (fn_800AD9B4() == 5) {
                pObject->mUnknown184(pObject, (int)fn_80040F18(i), 2);
            } else {
                pObject->mUnknown184(pObject, (int)fn_80040F18(i), 1);
            }
        }
    }
    return 0;
}

Object_80041904 *fn_80041904(int index)
{
    Object_80041904 *pObject = 0;

    if (lbl_803EA488 != 0) {
        pObject = &lbl_803EA488->mObjects[index];
    }
    return pObject;
}

unsigned int fn_80041928(void)
{
    return lbl_803EA48C;
}
}
