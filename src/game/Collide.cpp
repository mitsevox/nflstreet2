/* Collision objects for players and the field: typed collision sets with sub-shapes, per-type
   update callbacks, pairwise tests that build contact lists and per-pair contact callbacks, and
   mirroring for a flipped field. */
#include "game/Collide.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801D2B7C.h"
#include "game/Object_80039F5C.h"

/* Registration of one record type: active flag, sub-record count and update callback. */
struct CollideTypeReg_t {
    unsigned char mUnknown0;
    unsigned char mUnknown1;
    CollideUpdateFunc mpUnknown4;
};

extern "C" {
int fn_80178320(void);
int fn_80238258(const void *pA, const void *pB, unsigned int size);
}

static CollideTypeReg_t _Collide_aTypes[8];
static CollidePairFunc _Collide_aPairCallbacks[8][8];

extern "C" void CollideUpdateObject(CollideObject_t *pRecord)
{
    CollideShape_t *pSubs = pRecord->mpUnknown20;

    pRecord->mpUnknown20 = pRecord->mpUnknown24;
    pRecord->mpUnknown24 = pSubs;
    _Collide_aTypes[pRecord->mUnknown2E].mpUnknown4(pRecord);
}

extern "C" void CollideMirrorObject(CollideObject_t *pRecord)
{
    unsigned int i;
    CollideShape_t *pA;
    CollideShape_t *pB;

    pRecord->mUnknown0 = -pRecord->mUnknown0;
    pRecord->mUnknown4 = -pRecord->mUnknown4;
    pA = pRecord->mpUnknown20;
    pB = pRecord->mpUnknown24;
    for (i = 0; i < pRecord->mUnknown2F; i++) {
        pA->mUnknown0 = -pA->mUnknown0;
        pA->mUnknown4 = -pA->mUnknown4;
        pA->mUnknown10 = -pA->mUnknown10;
        pA->mUnknown14 = -pA->mUnknown14;
        pA->mUnknown20 = -pA->mUnknown20;
        pA->mUnknown24 = -pA->mUnknown24;
        pA++;
        pB->mUnknown0 = -pB->mUnknown0;
        pB->mUnknown4 = -pB->mUnknown4;
        pB->mUnknown10 = -pB->mUnknown10;
        pB->mUnknown14 = -pB->mUnknown14;
        pB->mUnknown20 = -pB->mUnknown20;
        pB->mUnknown24 = -pB->mUnknown24;
        pB++;
    }
}

extern "C" void CollideInit(int value)
{
    unsigned int i;
    unsigned int j;

    fn_800895C4();
    for (i = 0; i < 8; i++) {
        _Collide_aTypes[i].mUnknown0 = 0;
        _Collide_aTypes[i].mUnknown1 = 0;
        _Collide_aTypes[i].mpUnknown4 = 0;
    }
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            _Collide_aPairCallbacks[i][j] = 0;
        }
    }
}

extern "C" void CollideShutdown(void)
{
    fn_800895E0();
}

extern "C" void CollideRegisterType(unsigned char type, unsigned char count, CollideUpdateFunc pCallback)
{
    _Collide_aTypes[type].mUnknown0 = 1;
    _Collide_aTypes[type].mUnknown1 = count;
    _Collide_aTypes[type].mpUnknown4 = pCallback;
}

extern "C" void CollideUnregisterType(unsigned char type)
{
    _Collide_aTypes[type].mUnknown0 = 0;
    _Collide_aTypes[type].mUnknown1 = 0;
    _Collide_aTypes[type].mpUnknown4 = 0;
}

extern "C" void CollideSetPairCallback(unsigned char a, unsigned char b, CollidePairFunc pCallback)
{
    unsigned char lo = (a < b) ? a : b;
    unsigned char hi = (a > b) ? a : b;

    _Collide_aPairCallbacks[lo][hi] = pCallback;
}

extern "C" CollideSet_t *CollideSetCreate(int count, int subCount)
{
    CollideSet_t *pSet = (CollideSet_t *)fn_801D2B7C(sizeof(CollideSet_t), 0, 0);

    fn_801C1F94(pSet, 0, sizeof(CollideSet_t));
    pSet->mUnknown4 = count;
    pSet->mUnknown8 = 0;
    pSet->mpUnknown0 = (CollideObject_t *)fn_801D2B7C(count * sizeof(CollideObject_t), 0, 0);
    fn_801C1F94(pSet->mpUnknown0, 0, pSet->mUnknown4 * sizeof(CollideObject_t));
    pSet->mUnknownC = subCount;
    pSet->mUnknown10 = 0;
    pSet->mpUnknown14[0] = 0;
    pSet->mpUnknown14[1] = 0;
    if (subCount) {
        pSet->mpUnknown14[0] = (CollideShape_t *)fn_801D2B7C(subCount * sizeof(CollideShape_t), 0, 0);
        fn_801C1F94(pSet->mpUnknown14[0], 0, pSet->mUnknownC * sizeof(CollideShape_t));
        pSet->mpUnknown14[1] = (CollideShape_t *)fn_801D2B7C(pSet->mUnknownC * sizeof(CollideShape_t), 0, 0);
        fn_801C1F94(pSet->mpUnknown14[1], 0, pSet->mUnknownC * sizeof(CollideShape_t));
    }
    return pSet;
}

extern "C" void CollideSetDestroy(CollideSet_t *pSet)
{
    if (pSet->mpUnknown14[0] && pSet->mpUnknown14[1]) {
        fn_801D2BD0(pSet->mpUnknown14[0]);
        fn_801D2BD0(pSet->mpUnknown14[1]);
    }
    fn_801D2BD0(pSet->mpUnknown0);
    fn_801D2BD0(pSet);
}

extern "C" CollideObject_t *CollideSetAddObject(CollideSet_t *pSet, unsigned char type, int value)
{
    CollideObject_t *pRecord = &pSet->mpUnknown0[pSet->mUnknown8];
    unsigned char count = _Collide_aTypes[type].mUnknown1;

    pRecord->mUnknown2C = 1;
    pRecord->mUnknown2E = type;
    pRecord->mUnknown28 = value;
    pRecord->mUnknown2F = count;
    if (count) {
        pRecord->mpUnknown20 = &pSet->mpUnknown14[0][pSet->mUnknown10];
        pRecord->mpUnknown24 = &pSet->mpUnknown14[1][pSet->mUnknown10];
    } else {
        pRecord->mpUnknown20 = 0;
        pRecord->mpUnknown24 = 0;
    }
    pSet->mUnknown10 += count;
    pSet->mUnknown8++;
    return pRecord;
}

extern "C" void CollideSetUpdate(CollideSet_t *pSet)
{
    unsigned int i;

    if (pSet) {
        for (i = 0; i < pSet->mUnknown8; i++) {
            CollideUpdateObject(&pSet->mpUnknown0[i]);
        }
    }
}

extern "C" void CollideSetTest(CollideSet_t *pA, CollideSet_t *pB)
{
    unsigned int i;
    unsigned int j;

    if (pA && pB) {
        fn_800895E4();
        if (pA == pB) {
            for (i = 0; i < pA->mUnknown8; i++) {
                for (j = i + 1; j < pA->mUnknown8; j++) {
                    CollideTestPair(&pA->mpUnknown0[i], &pA->mpUnknown0[j]);
                }
            }
        } else {
            for (i = 0; i < pA->mUnknown8; i++) {
                for (j = 0; j < pB->mUnknown8; j++) {
                    CollideTestPair(&pA->mpUnknown0[i], &pB->mpUnknown0[j]);
                }
            }
        }
        fn_800895E8();
    }
}

extern "C" void CollideTestPair(CollideObject_t *pA, CollideObject_t *pB)
{
    Contact_80089330 contacts[128];
    Plane_800894B8 plane;
    unsigned char hit[16];
    ContactList_8030BD74 *pContacts = 0;
    CollideShape_t *pSubsA = pA->mpUnknown20;
    CollideShape_t *pSubsB = pB->mpUnknown20;
    int detail = 1;
    float radiusA;
    float radiusB;
    unsigned int countA;
    unsigned int countB;
    unsigned int i;
    unsigned int j;

    if (!(pA->mUnknown2C & 1) || !(pB->mUnknown2C & 1)) {
        return;
    }
    if (_Collide_aPairCallbacks[pA->mUnknown2E][pB->mUnknown2E] == 0) {
        return;
    }
    radiusA = pA->mUnknown18;
    radiusB = pB->mUnknown18;
    if (fn_800AD9B4() == 2 && pA->mUnknown2E == 0 && pB->mUnknown2E == 0) {
        Object_80039F5C *pObjectA = fn_8009BCE8(&pA->mUnknown28);
        Object_80039F5C *pObjectB = fn_8009BCE8(&pB->mUnknown28);

        if ((pObjectA->mId >> 8 & 0xFF) == fn_80178320() && (pObjectB->mId >> 8 & 0xFF) == fn_80178320()) {
            pA->mUnknown18 += 0.4f;
            pB->mUnknown18 += 0.4f;
            detail = 0;
        }
    }
    if (fn_800893F0(pA, pB)) {
        if (pSubsA && pSubsB && detail) {
            fn_8008959C(contacts, 128);
            countA = pA->mUnknown2F;
            countB = pB->mUnknown2F;
            fn_800894B8(&plane, pA, pB);
            for (i = 0; i < countA; i++) {
                hit[i] = 0;
                if (fn_80089514(&plane, &pSubsA[i].mUnknown10)) {
                    hit[i] = 1;
                    for (j = 0; j < countB; j++) {
                        if (fn_80089464(&pSubsA[i].mUnknown0, &pSubsB[j].mUnknown0)) {
                            fn_80089330(&pSubsA[i].mUnknown10, &pSubsB[j].mUnknown10, (j << 8) | i);
                        }
                    }
                }
            }
            plane.mUnknown10 = -plane.mUnknown10;
            plane.mUnknown14 = -plane.mUnknown14;
            plane.mUnknown18 = -plane.mUnknown18;
            for (j = 0; j < countB; j++) {
                if (fn_80089514(&plane, &pSubsB[j].mUnknown10)) {
                    for (i = 0; i < countA; i++) {
                        if (hit[i] == 0 && fn_80089464(&pSubsA[i].mUnknown0, &pSubsB[j].mUnknown0)) {
                            fn_80089330(&pSubsA[i].mUnknown10, &pSubsB[j].mUnknown10, (j << 8) | i);
                        }
                    }
                }
            }
            pContacts = fn_800895B8();
        }
        if (pContacts == 0 || pContacts->mCount > 0) {
            _Collide_aPairCallbacks[pA->mUnknown2E][pB->mUnknown2E](pA, pB, pContacts);
        }
    }
    pA->mUnknown18 = radiusA;
    pB->mUnknown18 = radiusB;
}

extern "C" int CollideCompareObjects(CollideObject_t *pA, CollideObject_t *pB, CollideObject_t *pBase)
{
    int result = fn_80238258(pA, pB, 32);
    int i;

    result |= pA->mUnknown2F != pB->mUnknown2F;
    result |= pA->mUnknown2C != pB->mUnknown2C;
    result |= pA->mUnknown2E != pB->mUnknown2E;
    result |= pA->mUnknown28 != pB->mUnknown28;
    for (i = 0; i < pA->mUnknown2F; i++) {
        result |= fn_80238258((char *)&pA->mpUnknown20[i] + ((char *)pA - (char *)pBase),
                              (char *)&pB->mpUnknown20[i] + ((char *)pB - (char *)pBase), sizeof(CollideShape_t));
        result |= fn_80238258((char *)&pA->mpUnknown24[i] + ((char *)pA - (char *)pBase),
                              (char *)&pB->mpUnknown24[i] + ((char *)pB - (char *)pBase), sizeof(CollideShape_t));
    }
    return result;
}

extern "C" void CollideSetMirror(CollideSet_t *pSet)
{
    unsigned int i;

    if (pSet) {
        for (i = 0; i < pSet->mUnknown8; i++) {
            CollideMirrorObject(&pSet->mpUnknown0[i]);
        }
    }
}
