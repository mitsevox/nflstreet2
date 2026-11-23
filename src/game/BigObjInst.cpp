/* Big-object instances: the pool of placed level objects (birds, fences, path followers,
   hotspots), their creation from placements, per-frame behaviour callbacks, physics steps and
   syncing back to their owning objects. */
#include "game/BigObjInst.h"
#include "game/BigObj.h"
#include "game/SyncStateRegister.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801BE60C.h"
#include <string.h>

struct BigObjPool_t {
    BigObjInst *mObjects;
    BigObjPhysics_t *mExtras;
    unsigned short mCount;
    unsigned short mMaxObjects;
    unsigned short mExtraCount;
    unsigned short mMaxExtras;
};

extern "C" {
int BigObjSyncFromInst(BigObjInst *pObject, int index);
int BigObjHasSkeleton(int index);
void BigObjAnimBlend(BigObjPhysics_t *pExtra, BigObj_t *pItem, int a);
void BigObjAnimBlendRoot(BigObj_t *pItem, void *a, int b, void *c);
void BigObjAnimInitObject(BigObjInst *pObject, int index);
void BigObjParseBehavior(void *pOwner, BigObjInst *pObject);
void BigObjFreeEvents(BigObjInst *pObject);
void AnimChanProcess(void *a, void *b, float c, BigObjInst *pObject);
int AnimMotCreateWeightList(void *a, void *b, void *c);
int fn_801BCA74(void *a, void *b, int c, void *d, int e, int f);
int fn_801BCCAC(void *a, void *b, int c, void *d, int e, int f);
void fn_801BE420(void *a, void *b, void *c, BigObjInst *pObject, float d);
void QuatFromEulerYZX(float *pOut, int x, int y, int z);
int Crc32Update(const void *p, int size, int seed);
void *SyncStateGetData(void *pHandle);

BigObjPool_t *_BigObjInst_pPool = 0;
unsigned int _BigObjInst_uFrame = 0;

int BigObjPoolCreate(void *p, int value)
{
    BigObjPool_t *pPool = (BigObjPool_t *)p;
    int i;

    pPool->mObjects = (BigObjInst *)fn_801D2B7C(pPool->mMaxObjects * 432, 0, 0);
    memset(pPool->mObjects, 0, pPool->mMaxObjects * 432);
    pPool->mExtras = (BigObjPhysics_t *)fn_801D2B7C(pPool->mMaxExtras * 1712, 0, 0);
    memset(pPool->mExtras, 0, pPool->mMaxExtras * 1712);
    for (i = 0; i < pPool->mMaxObjects; i++) {
    }
    return 0;
}

int BigObjPoolDestroy(void *p, int value)
{
    BigObjPool_t *pPool = (BigObjPool_t *)p;
    unsigned short i;

    for (i = 0; i < pPool->mMaxObjects; i++) {
        BigObjFreeEvents(&pPool->mObjects[i]);
    }
    fn_801D2BD0(pPool->mObjects);
    pPool->mObjects = 0;
    fn_801D2BD0(pPool->mExtras);
    pPool->mExtras = 0;
    return 0;
}

int BigObjPoolEmptyPass(void *p, int value)
{
    BigObjPool_t *pPool = (BigObjPool_t *)p;
    unsigned int i;

    for (i = 0; i < pPool->mMaxObjects; i++) {
    }
    return 0;
}

int BigObjPoolCompare(void *p, void *q)
{
    BigObjPool_t *pPool = (BigObjPool_t *)p;
    BigObjPool_t *pOther = (BigObjPool_t *)q;
    int result;
    int i;

    if (pOther != 0) {
        result = 0;
        result |= pPool->mCount != pOther->mCount;
        result |= pPool->mMaxObjects != pOther->mMaxObjects;
        for (i = 0; i < pPool->mMaxObjects; i++) {
        }
    } else {
        result = Crc32Update(pPool, 16, 0);
        for (i = 0; i < pPool->mMaxObjects; i++) {
        }
    }
    return result;
}

void BigObjInstInit(int maxObjects, int maxExtras)
{
    void *pHandle;
    BigObjPool_t *pPool;

    pHandle = SyncStateRegister(0, (void **)&_BigObjInst_pPool, 16, 2, 0x626F626A);
    SyncStateSetCallbacks(pHandle, BigObjPoolCreate, BigObjPoolDestroy, BigObjPoolEmptyPass, BigObjPoolCompare);
    pPool = (BigObjPool_t *)SyncStateGetData(pHandle);
    pPool->mCount = 0;
    pPool->mMaxObjects = maxObjects;
    pPool->mExtraCount = 0;
    pPool->mMaxExtras = maxExtras;
    _BigObjInst_uFrame = 0;
    SyncStateCommit(pHandle);
}

void BigObjInstShutdown(void)
{
    _BigObjInst_pPool = 0;
}

BigObjInst *BigObjInstCreate(void *pOwner, BigObjPlacement_t *pDesc)
{
    BigObjInst *pObject = &_BigObjInst_pPool->mObjects[_BigObjInst_pPool->mCount];

    if (BigObjGetSkeleton(_BigObjInst_pPool->mCount) != 0) {
        pObject->mUnknown428 = &_BigObjInst_pPool->mExtras[_BigObjInst_pPool->mExtraCount++];
    } else {
        pObject->mUnknown428 = 0;
    }
    pObject->mUnknown0 = pDesc->mUnknown0;
    BigObjAnimInitObject(pObject, _BigObjInst_pPool->mCount);
    pObject->mState.mUnknown0 = pDesc->mUnknown4;
    pObject->mState.mUnknown4 = pDesc->mUnknown8;
    pObject->mState.mUnknown8 = pDesc->mUnknown12;
    QuatFromEulerYZX(&pObject->mState.mUnknown88, (int)(pDesc->mUnknown20 * 46603.3789f), (int)(pDesc->mUnknown24 * 46603.3789f),
                (int)(pDesc->mUnknown16 * 46603.3789f));
    pObject->mState.mUnknown24 = (int)((pDesc->mUnknown24 - 90.0f) * 46603.3789f);
    if (pObject->mUnknown428 != 0) {
        pObject->mUnknown428->mUnknown56 = pObject->mState.mUnknown24;
    }
    pObject->mState.mUnknown104 = pObject->mState.mUnknown0;
    pObject->mState.mUnknown108 = pObject->mState.mUnknown4;
    pObject->mState.mUnknown112 = pObject->mState.mUnknown8;
    pObject->mState.mUnknown116 = pObject->mState.mUnknown88;
    pObject->mState.mUnknown120 = pObject->mState.mUnknown92;
    pObject->mState.mUnknown124 = pObject->mState.mUnknown96;
    pObject->mState.mUnknown128 = pObject->mState.mUnknown100;
    pObject->mState.mUnknown132 = pObject->mState.mUnknown24;
    BigObjParseBehavior(pOwner, pObject);
    if (pObject->mUnknown184 != 0) {
        pObject->mUnknown184(pObject, BigObjGet(_BigObjInst_pPool->mCount), 0);
    }
    _BigObjInst_pPool->mCount++;
    return pObject;
}

int BigObjInstSyncAll(void)
{
    unsigned short i;

    for (i = 0; i < _BigObjInst_pPool->mCount; i++) {
        BigObjSyncFromInst(&_BigObjInst_pPool->mObjects[i], i);
    }
    return 0;
}

int BigObjInstSimulateAll(float dt)
{
    unsigned short i;

    for (i = 0; i < _BigObjInst_pPool->mCount; i++) {
        if (BigObjHasSkeleton(i) != 0) {
            BigObjInst *pObject = &_BigObjInst_pPool->mObjects[i];
            BigObjPhysics_t *pExtra = pObject->mUnknown428;
            int a;

            if (pExtra->mUnknown1708 & 8) {
                if (pExtra->mUnknown1708 & 16) {
                    continue;
                }
                pExtra->mUnknown1708 |= 16;
            }
            fn_801BE420(pExtra->mUnknown1300, pExtra->mUnknown48, pExtra->mUnknown60, pObject, dt);
            AnimChanProcess(pExtra->mUnknown48, pExtra->mUnknown60, dt, pObject);
            a = AnimMotCreateWeightList(pExtra->mUnknown48, pExtra->mUnknown60, pExtra->mUnknown1300);
            BigObjAnimBlend(pExtra, BigObjGet(i), a);
            pExtra->mSpin.mUnknown0 = fn_801BCA74(pExtra->mUnknown48, pExtra->mUnknown60, a, &pExtra->mSpin.mUnknown4, 0xFFFF, 1);
            pExtra->mSpin.mUnknown1 = fn_801BCCAC(pExtra->mUnknown48, pExtra->mUnknown60, a, pExtra->mUnknown40,
                                             fn_801BE648(pObject->mUnknown428->mUnknown1300), 1);
            BigObjAnimBlendRoot(BigObjGet(i), pExtra->mUnknown60, pExtra->mUnknown52, pExtra->mUnknown1300);
        }
    }
    return 0;
}

int BigObjInstTickAll(void)
{
    unsigned short i;

    _BigObjInst_uFrame++;
    for (i = 0; i < _BigObjInst_pPool->mCount; i++) {
        BigObjInst *pObject = &_BigObjInst_pPool->mObjects[i];

        if (pObject->mUnknown184 != 0) {
            if (fn_800AD9B4() == 5) {
                pObject->mUnknown184(pObject, BigObjGet(i), 2);
            } else {
                pObject->mUnknown184(pObject, BigObjGet(i), 1);
            }
        }
    }
    return 0;
}

BigObjInst *BigObjInstGet(int index)
{
    BigObjInst *pObject = 0;

    if (_BigObjInst_pPool != 0) {
        pObject = &_BigObjInst_pPool->mObjects[index];
    }
    return pObject;
}

unsigned int BigObjInstGetFrame(void)
{
    return _BigObjInst_uFrame;
}
}
