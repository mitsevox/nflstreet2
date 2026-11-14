/* Animated big objects: the placed level objects (crowd stands, fences,
   birds, the animated ball and the like). Sets up their object pool and
   model file, creates one object per level placement with its BigObjInst
   state, links grouped objects, copies instance positions back each frame,
   registers their save and load streams as "Animated Big Objects", and finds
   objects by index, key, group or distance. */
#include "game/BigObjDesc.h"
#include "game/fn_8022781C.h"
#include <string.h>

#include "game/bitstream.h"
#include "game/LevelData.h"
#include "game/BigObj.h"
#include "game/BigObjInst.h"
#include "game/Ball.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801D2B7C.h"
#include "game/ResOpenDevice.h"
#include "game/LevelSurface.h"
#include "engine/llquat.h"

extern "C" {
void fn_800301C4(void *pStream, float *pValues, int bits, float scale);
void fn_80030304(void *pStream, float *pValues, int bits, float scale);
void fn_80030554(void *pStream, float *pValues, int bits, float scale);
void fn_8003065C(void *pStream, float *pValues, int bits, float scale);
void fn_80030ACC(void (*pSave)(BitStream_t *pStream),
                 void (*pLoad)(BitStream_t *pStream0, BitStream_t *pStream1, BitStream_t *pStream2,
                               BitStream_t *pStream3, float t),
                 int size, const char *pName);
void BallModelSetLinkedObj(Block_80170E64 *pBlock, BigObjInst *pLinked);
void fn_8004AA34(AnimPose_t *pPose, BitStream_t *pStream, unsigned int count);
void fn_8004ABF4(BigObj_t *pObject, BigObjInst *pLinked, BitStream_t *pStream0, BitStream_t *pStream1,
                 BitStream_t *pStream2, BitStream_t *pStream3, float t);
void fn_8004AF84(BigObjPhysics_t *pExtra);
void fn_8004CBE8(void);
void fn_8004D0F4(int handle);
void fn_8004D118(int handle);
void fn_8004D144(BigObjDesc_t *pDesc, int handle, int first);
int fn_8004D3A8(void *pData, char *pName);
void fn_8004D798(void);
void fn_8004D818(void);
void fn_8004DC88(void *pData, int model, BigObj_t *pObject);
void fn_8004DF68(BigObj_t *pObject);
void fn_8004DFDC(void);
void fn_8004E018(void);
void fn_8004E0CC(BigObj_t *pObject, int a, int b);
void fn_8004E320(void);
void fn_8004E358(void);
void fn_8004F754(int model, BigObj_t *pObject, int index);
void fn_800504EC(void);
void fn_80051308(void);
void HotspotReset(void);
void fn_800B2A14(float *pPos, unsigned char *pAngles);
int FileSetMemAllocFlags(int value);
int ObjNewType_(int type, int size, int count, void (*pInit)(BigObj_t *, BigObjDesc_t *),
                void (*pRelease)(BigObj_t *));
int ObjDelType(int type);
void ObjSetListObjFunc(int handle, int type, int a, int (*pCallback)(BigObj_t *));
BigObj_t *ObjNewInList(int handle, int type, int a, BigObjDesc_t *pDesc);
void ObjRemoveFromList(int handle, BigObj_t *pObject);
void ObjSetPriority(int handle, BigObj_t *pObject, int a);
void QuatFromEuler(Quat_801EB488 *pOut, int a, int b, int c);
void QuatSlerp(Quat_801EB488 *pOut, Quat_801EB488 *pA, Quat_801EB488 *pB, float t);
int ResSetMemFlags(int value);
int fn_801F7C88(void);
int fn_80227594(float *pA, float *pB, float tolerance);
float fn_8022785C(Vector_80039F5C *pA, Vector_80039F5C *pB);
void fn_80227930(Vector_80039F5C *pOut, Vector_80039F5C *pA, Vector_80039F5C *pB, float t);
void VptTrashObject(BigObj_t *pObject);
void VptFlushObjectTrash(void);
void VptFlushObjectTrashSync(void);

int BigObjDefaultUpdate(BigObj_t *pObject);
void BigObjLinkGroup(BigObj_t *pObject, unsigned int count);
void BigObjRegisterPool(int handle, int count);
void BigObjReleasePool(void);
void BigObjItemInit(BigObj_t *pObject, BigObjDesc_t *pDesc);
void BigObjItemRelease(BigObj_t *pObject);
int BigObjItemUpdate(BigObj_t *pObject);
}

static BigObj_t **_BigObj_apObjects = 0;
static unsigned char _BigObj_bUpdate = 1;
static unsigned short _BigObj_uCount;
static unsigned short _BigObj_uMax;
static unsigned short _BigObj_uLinkedStart;
static void *_BigObj_pModelFile;

extern "C" {
#if defined(DECOMP_COMPARE)
int BigObjDefaultUpdate(BigObj_t *pObject)
{
    return 0;
}

/* Links the newest object to up to eight earlier objects that share its
   group id, and points each of them back at it. */
void BigObjLinkGroup(BigObj_t *pObject, unsigned int count)
{
    BigObjInst *pLinked = pObject->mUnknown472;
    unsigned int n = 0;
    unsigned int i;

    for (i = 0; i < count; i++) {
        if (_BigObj_apObjects[i]->mUnknown472->mUnknown144 == pLinked->mUnknown144) {
            if (n < 8) {
                pLinked->mUnknown152[n++] = _BigObj_apObjects[i];
                _BigObj_apObjects[i]->mUnknown472->mUnknown152[0] = pObject;
            } else {
                break;
            }
        }
    }
}
#endif

void BigObjSave(BitStream_t *pStream)
{
    unsigned int i;

    for (i = 0; i < _BigObj_uCount; i++) {
        BigObj_t *pObject = _BigObj_apObjects[i];

        if (pObject->mUnknown300 != 0) {
            if (BigObjGetItemSkeleton(pObject) != 0) {
                fn_8004AA34(&pObject->mUnknown172, pStream, pObject->mUnknown172.mUnknown4 - 1);
            }
            fn_80191068(pStream, pObject->mUnknown232_31, 1);
            fn_80191068(pStream, pObject->mUnknown300->mUnknown40, 8);
            fn_80030554(pStream, &pObject->mPos.mX, 17, 256.0f);
            fn_8003065C(pStream, &pObject->mRot.mX, 12, 1024.0f);
        }
    }
}

/* Load callback: reads each object back from two saved streams and blends
   position and rotation by t; the last two streams are read and skipped. */
void BigObjLoad(BitStream_t *pStream0, BitStream_t *pStream1, BitStream_t *pStream2, BitStream_t *pStream3, float t)
{
    unsigned int i;

    for (i = 0; i < _BigObj_uCount; i++) {
        BigObj_t *pObject = _BigObj_apObjects[i];

        if (pObject->mUnknown300 != 0) {
            Vector_80039F5C pos0;
            Vector_80039F5C pos1;
            Quat_801EB488 rot0;
            Quat_801EB488 rot1;
            unsigned char bit;
            unsigned char value;

            if (BigObjGetItemSkeleton(pObject) != 0) {
                fn_8004AF84(pObject->mUnknown472->mUnknown428);
                fn_8004ABF4(pObject, BigObjInstGet(i), pStream0, pStream1, pStream2, pStream3, t);
            }
            bit = ReadBitStream(pStream1, 1);
            ReadBitStream(pStream0, 1);
            if (bit) {
                pObject->mUnknown232_29 = 1;
            } else {
                pObject->mUnknown232_29 = 0;
            }
            value = ReadBitStream(pStream1, 8);
            ReadBitStream(pStream0, 8);
            fn_8004E0CC(pObject, 0, value);
            fn_800301C4(pStream1, &pos1.mX, 17, 256.0f);
            fn_800301C4(pStream0, &pos0.mX, 17, 256.0f);
            if (fn_8022785C(&pos0, &pos1) > 15.0f) {
                pObject->mPos.mX = pos0.mX;
                pObject->mPos.mY = pos0.mY;
                pObject->mPos.mZ = pos0.mZ;
            } else {
                fn_80227930(&pObject->mPos, &pos0, &pos1, t);
            }
            fn_80030304(pStream1, &rot1.mX, 12, 1024.0f);
            fn_80030304(pStream0, &rot0.mX, 12, 1024.0f);
            QuatSlerp(&pObject->mRot, &rot0, &rot1, t);
            if (pStream2 != 0) {
                ReadBitStream(pStream2, 1);
                ReadBitStream(pStream2, 8);
                fn_800301C4(pStream2, &pos1.mX, 17, 256.0f);
                fn_80030304(pStream2, &rot1.mX, 12, 1024.0f);
            }
            if (pStream3 != 0) {
                ReadBitStream(pStream3, 1);
                ReadBitStream(pStream3, 8);
                fn_800301C4(pStream3, &pos1.mX, 17, 256.0f);
                fn_80030304(pStream3, &rot1.mX, 12, 1024.0f);
            }
        }
    }
}

int BigObjGetSaveSize(void)
{
    int size = 0;
    unsigned int i;

    for (i = 0; i < _BigObj_uCount; i++) {
        BigObj_t *pObject = _BigObj_apObjects[i];

        if (pObject->mUnknown300 != 0) {
            AnimSkeleton_t *pSkeleton = BigObjGetItemSkeleton(pObject);

            if (pSkeleton != 0) {
                size += pSkeleton->mUnknown6 * 36;
                size += 64;
            }
            size += 108;
        }
    }
    return size;
}

void BigObjSetupBigObjects(int count, int handle)
{
    BigObjRegisterPool(handle, count);
    _BigObj_apObjects = (BigObj_t **)fn_801D2B7C(count * 4, 0, 0);
    memset(_BigObj_apObjects, 0, count * 4);
    fn_801F7C88();
    _BigObj_uMax = count;
    _BigObj_uCount = 0;
    _BigObj_pModelFile = ResOpenDevice("objmodel.dat", 44);
    fn_8004DFDC();
    fn_8004E320();
    fn_800504EC();
    fn_8004D0F4(handle);
}

void BigObjShutdownObjects(int handle)
{
    unsigned int i;

    if (_BigObj_apObjects != 0) {
        for (i = 0; i < _BigObj_uCount; i++) {
            BigObjInst *pLinked = _BigObj_apObjects[i]->mUnknown472;

            if (pLinked->mUnknown184 != 0) {
                pLinked->mUnknown184(pLinked, _BigObj_apObjects[i], 3);
            }
            ObjRemoveFromList(handle, _BigObj_apObjects[i]);
            VptTrashObject(_BigObj_apObjects[i]);
        }
        VptFlushObjectTrash();
        fn_801D2BD0(_BigObj_apObjects);
        _BigObj_apObjects = 0;
    }
    BigObjReleasePool();
    fn_8004E018();
    fn_8004E358();
    fn_80051308();
    fn_8004D118(handle);
    ResClose(_BigObj_pModelFile);
}

void BigObjNotifyTypes(unsigned int flags)
{
    int all = (flags >> 8) & 1;
    unsigned int i;

    if (_BigObj_apObjects != 0) {
        for (i = 0; i < _BigObj_uCount; i++) {
            BigObj_t *pObject = _BigObj_apObjects[i];

            if (all || ((1 << pObject->mUnknown472->mUnknown188) & flags)) {
                BigObjInst *pLinked = pObject->mUnknown472;

                if (pLinked->mUnknown184 != 0) {
                    pLinked->mUnknown184(pLinked, pObject, 4);
                }
            }
        }
    }
    if (all || (flags & 0xC0)) {
        HotspotReset();
    }
}

void BigObjRegisterPool(int handle, int count)
{
    ObjNewType_(28, sizeof(BigObj_t), count, BigObjItemInit, BigObjItemRelease);
    if (handle != 0) {
        ObjSetListObjFunc(handle, 28, 0, BigObjItemUpdate);
    }
}

void BigObjReleasePool(void)
{
    VptFlushObjectTrashSync();
    ObjDelType(28);
}

void BigObjItemInit(BigObj_t *pObject, BigObjDesc_t *pDesc)
{
    pObject->mUnknown328 = pDesc->mUnknown0;
    strcpy(pObject->mName, pDesc->mName);
    pObject->mUnknown20 = BigObjDefaultUpdate;
    pObject->mUnknown304 = 0;
    pObject->mUnknown336 = -100000.0f;
    pObject->mUnknown340 = -100000.0f;
    pObject->mUnknown332 = 0;
    pObject->mUnknown476 = 0;
    pObject->mUnknown480 = 0;
}

void BigObjItemRelease(BigObj_t *pObject)
{
    fn_8004DF68(pObject);
}

int BigObjItemUpdate(BigObj_t *pObject)
{
    int result = 0;

    if (_BigObj_bUpdate) {
        result = pObject->mUnknown20(pObject);
    }
    return result;
}

void BigObjCreate(BigObjDesc_t *pDesc, int handle)
{
    BigObjInst *pLinked;

    pDesc->mUnknown168 = fn_8004D3A8(pDesc->mUnknown160, pDesc->mName);
    if (pDesc->mUnknown168 == -1) {
        return;
    }
    _BigObj_apObjects[_BigObj_uCount] = ObjNewInList(handle, 28, 0, pDesc);
    ObjSetPriority(handle, _BigObj_apObjects[_BigObj_uCount], 6);
    fn_8004DC88(pDesc->mUnknown164, pDesc->mUnknown168, _BigObj_apObjects[_BigObj_uCount]);
    if (strstr(pDesc->mName, "CROWD") != 0) {
        _BigObj_apObjects[_BigObj_uCount]->mUnknown232_27 = 1;
    }
    _BigObj_apObjects[_BigObj_uCount]->mUnknown472 = BigObjInstCreate((void *)pDesc->mUnknown168, &pDesc->mUnknown132);
    _BigObj_apObjects[_BigObj_uCount]->mUnknown472->mUnknown4 = _BigObj_uCount;
    fn_8004F754(pDesc->mUnknown168, _BigObj_apObjects[_BigObj_uCount], _BigObj_uCount);
    _BigObj_apObjects[_BigObj_uCount]->mUnknown472->mUnknown144 = pDesc->mUnknown172;
    _BigObj_apObjects[_BigObj_uCount]->mUnknown472->mUnknown148 = pDesc->mUnknown180;
    memset(_BigObj_apObjects[_BigObj_uCount]->mUnknown472->mUnknown152, 0, 32);
    _BigObj_apObjects[_BigObj_uCount]->mUnknown308 = pDesc->mUnknown176;
    _BigObj_apObjects[_BigObj_uCount]->mUnknown332 = LevelFindArea(&pDesc->mUnknown132.mUnknown4);
    _BigObj_uCount++;
}

void BigObjSyncFromInst(BigObjInst *pLinked, int index)
{
    BigObj_t *pObject = _BigObj_apObjects[index];

    if (pLinked->mUnknown428 != 0 && (pLinked->mUnknown428->mUnknown32 != 0 || pLinked->mUnknown428->mUnknown33 != 0)) {
        fn_800B2A14(&pLinked->mUnknown8, &pLinked->mUnknown428->mUnknown32);
        QuatEulerAngles_t angles;
        QuatToEuler(&angles, &pLinked->mUnknown96);
        angles.mUnknown8 = pLinked->mUnknown32 + 0x400000;
        QuatFromEuler(&pObject->mRot, angles.mUnknown8, angles.mUnknown4, angles.mUnknown0);
    } else {
        pObject->mRot.mX = pLinked->mUnknown96;
        pObject->mRot.mY = pLinked->mUnknown100;
        pObject->mRot.mZ = pLinked->mUnknown104;
        pObject->mRot.mW = pLinked->mUnknown108;
    }
    pObject->mPos.mX = pLinked->mUnknown8;
    pObject->mPos.mY = pLinked->mUnknown12;
    pObject->mPos.mZ = pLinked->mUnknown16;
    if (pLinked->mUnknown428 != 0) {
        pLinked->mUnknown428->mUnknown56 = pLinked->mUnknown32;
    }
    if (fn_80227594(&pObject->mUnknown336, &pLinked->mUnknown8, 0.05f) == 0) {
        pObject->mUnknown332 = LevelFindArea(&pLinked->mUnknown8);
        pObject->mUnknown336 = pLinked->mUnknown8;
        pObject->mUnknown340 = pLinked->mUnknown12;
    }
}

void BigObjCreateAnimBall(int handle)
{
    BigObjDesc_t desc;
    unsigned short index;

    {
        int saved0 = ResSetMemFlags(4);
        int saved1 = FileSetMemAllocFlags(4);

        desc.mUnknown160 = ResOpenDevice("objdefs.dat", 44);
        ResSetMemFlags(saved0);
        FileSetMemAllocFlags(saved1);
    }
    desc.mUnknown164 = _BigObj_pModelFile;
    fn_8004D798();
    strcpy(desc.mName, "OBJDEF_ANIMBALL");
    desc.mUnknown132.mUnknown12 = 0.0f;
    desc.mUnknown132.mUnknown8 = 0.0f;
    desc.mUnknown132.mUnknown4 = 0.0f;
    desc.mUnknown132.mUnknown24 = 0.0f;
    desc.mUnknown132.mUnknown20 = 0.0f;
    desc.mUnknown132.mUnknown16 = 0.0f;
    desc.mUnknown172 = 0;
    desc.mUnknown176 = 0;
    desc.mUnknown180 = 0;
    index = _BigObj_uCount;
    BigObjCreate(&desc, handle);
    BallModelSetLinkedObj(BallGetModel(BallGetCurrent()), BigObjGet(index)->mUnknown472);
    fn_8004D818();
    ResClose(desc.mUnknown160);
}

void BigObjAddAllObjects(int handle)
{
    BigObjDesc_t desc;
    LevelData_t *pLevel;
    LevelPlacement_t *pEntry;
    unsigned int i;
    unsigned short first;

    {
        int saved0 = ResSetMemFlags(4);
        int saved1 = FileSetMemAllocFlags(4);

        desc.mUnknown160 = ResOpenDevice("objdefs.dat", 44);
        ResSetMemFlags(saved0);
        FileSetMemAllocFlags(saved1);
    }
    desc.mUnknown164 = _BigObj_pModelFile;
    fn_8004D798();
    pLevel = LevelGetData();
    for (i = 0; i < pLevel->mUnknown88; i++) {
        pEntry = &pLevel->mUnknown92[i];

        strcpy(desc.mName, &pLevel->mUnknown44[pEntry->mUnknown24 * 24]);
        desc.mUnknown132.mUnknown4 = pEntry->mUnknown0[0];
        desc.mUnknown132.mUnknown8 = pEntry->mUnknown0[1];
        desc.mUnknown132.mUnknown12 = pEntry->mUnknown0[2];
        desc.mUnknown132.mUnknown16 = pEntry->mUnknown0[3];
        desc.mUnknown132.mUnknown20 = pEntry->mUnknown0[4];
        desc.mUnknown132.mUnknown24 = pEntry->mUnknown0[5];
        desc.mUnknown172 = pEntry->mUnknown28;
        desc.mUnknown176 = pEntry->mUnknown32;
        desc.mUnknown180 = pEntry->mUnknown24;
        BigObjCreate(&desc, handle);
    }
    first = _BigObj_uCount;
    _BigObj_uLinkedStart = first;
    for (i = 0; i < pLevel->mUnknown104; i++) {
        LevelPlacement_t *pLinked = &pLevel->mUnknown108[i];
        unsigned short count;

        strcpy(desc.mName, &pLevel->mUnknown60[pLinked->mUnknown24 * 24]);
        desc.mUnknown132.mUnknown4 = pLinked->mUnknown0[0];
        desc.mUnknown132.mUnknown8 = pLinked->mUnknown0[1];
        desc.mUnknown132.mUnknown12 = pLinked->mUnknown0[2];
        desc.mUnknown132.mUnknown16 = pLinked->mUnknown0[3];
        desc.mUnknown132.mUnknown20 = pLinked->mUnknown0[4];
        desc.mUnknown132.mUnknown24 = pLinked->mUnknown0[5];
        desc.mUnknown172 = pLinked->mUnknown28;
        desc.mUnknown180 = pLinked->mUnknown24;
        desc.mUnknown176 = pLinked->mUnknown32;
        count = _BigObj_uCount;
        BigObjCreate(&desc, handle);
        if (count != _BigObj_uCount) {
            BigObjLinkGroup(_BigObj_apObjects[_BigObj_uCount - 1], first);
        }
    }
    for (i = 0; i < pLevel->mUnknown112; i++) {
        pEntry = &pLevel->mUnknown116[i];

        strcpy(desc.mName, &pLevel->mUnknown68[pEntry->mUnknown24 * 24]);
        desc.mUnknown132.mUnknown4 = pEntry->mUnknown0[0];
        desc.mUnknown132.mUnknown8 = pEntry->mUnknown0[1];
        desc.mUnknown132.mUnknown12 = pEntry->mUnknown0[2];
        desc.mUnknown132.mUnknown16 = pEntry->mUnknown0[3];
        desc.mUnknown132.mUnknown20 = pEntry->mUnknown0[4];
        desc.mUnknown132.mUnknown24 = pEntry->mUnknown0[5];
        desc.mUnknown176 = pEntry->mUnknown32;
        fn_8004D144(&desc, handle, first);
    }
    fn_8004D818();
    ResClose(desc.mUnknown160);
    fn_8004CBE8();
}

unsigned short BigObjGetCount(void)
{
    return _BigObj_uCount;
}

BigObj_t *BigObjGet(int index)
{
    return _BigObj_apObjects[index];
}

BigObj_t *BigObjFindNearest(Vector_80039F5C *pPos, float *pDist)
{
    float best = 10000.0f;
    BigObj_t *pBest = 0;
    unsigned int i;

    if (_BigObj_apObjects != 0) {
        for (i = 0; i < _BigObj_uCount; i++) {
            BigObj_t *pObject = _BigObj_apObjects[i];
            float dist = fn_8022781C(&pObject->mPos, pPos);

            if (dist < best) {
                pBest = pObject;
                best = dist;
            }
        }
    }
    if (pDist != 0) {
        *pDist = best;
    }
    return pBest;
}

BigObj_t *BigObjFindNearestOfType(Vector_80039F5C *pPos, int type, float *pDist)
{
    float best = 10000.0f;
    BigObj_t *pBest = 0;
    unsigned int i;

    if (_BigObj_apObjects != 0) {
        for (i = 0; i < _BigObj_uCount; i++) {
            BigObj_t *pObject = _BigObj_apObjects[i];

            if (pObject->mUnknown472->mUnknown188 == type) {
                float dist = fn_8022781C(&pObject->mPos, pPos);

                if (dist < best) {
                    pBest = pObject;
                    best = dist;
                }
            }
        }
    }
    if (pDist != 0) {
        *pDist = best;
    }
    return pBest;
}

int BigObjHasSkeleton(int index)
{
    if (_BigObj_apObjects[index]->mUnknown304 != 0) {
        return 1;
    }
    return 0;
}

AnimSkeleton_t *BigObjGetSkeleton(int index)
{
    BigObj_t *pObject = _BigObj_apObjects[index];

    if (pObject->mUnknown304 != 0) {
        return *pObject->mUnknown304;
    }
    return 0;
}

AnimSkeleton_t *BigObjGetItemSkeleton(BigObj_t *pObject)
{
    if (pObject->mUnknown304 != 0) {
        return *pObject->mUnknown304;
    }
    return 0;
}

void BigObjRegisterSave(void)
{
    fn_80030ACC(BigObjSave, BigObjLoad, BigObjGetSaveSize(), "Animated Big Objects");
}

BigObj_t *BigObjFindByKey(int key, unsigned int count)
{
    unsigned short i;

    for (i = 0; i < count; i++) {
        BigObj_t *pObject = _BigObj_apObjects[i];

        if (pObject->mUnknown308 == key) {
            return pObject;
        }
    }
    return 0;
}

BigObj_t *BigObjFindLinkedByGroup(int key)
{
    unsigned short i;

    for (i = _BigObj_uLinkedStart; i < _BigObj_uCount; i++) {
        BigObj_t *pObject = _BigObj_apObjects[i];

        if (pObject->mUnknown472->mUnknown144 == key) {
            return pObject;
        }
    }
    return 0;
}

void BigObjClearFlag(BigObj_t *pObject)
{
    if (pObject == 0) {
        return;
    }
    if (pObject->mUnknown476 == 0) {
        return;
    }
    pObject->mUnknown476->mUnknown2 &= ~1;
}

void BigObjSetFlag(BigObj_t *pObject)
{
    if (pObject == 0) {
        return;
    }
    if (pObject->mUnknown476 == 0) {
        return;
    }
    pObject->mUnknown476->mUnknown2 |= 1;
}
}
