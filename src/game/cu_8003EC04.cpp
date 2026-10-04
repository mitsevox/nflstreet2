#include "game/cu_8003EC04.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801D2B7C.h"
#include "game/Object_80039F5C.h"

/* Registration of one record type: active flag, sub-record count and update callback. */
struct Entry_803075E0 {
    unsigned char mUnknown0;
    unsigned char mUnknown1;
    Callback_802DCF9C mpUnknown4;
};

extern "C" {
int fn_80178320(void);
int fn_80238258(const void *pA, const void *pB, unsigned int size);
}

static Entry_803075E0 lbl_803075E0[8];
static Callback_8003EE2C lbl_80307620[8][8];

extern "C" void fn_8003EC04(Record_8003EC04 *pRecord)
{
    Sub_8003EC54 *pSubs = pRecord->mpUnknown20;

    pRecord->mpUnknown20 = pRecord->mpUnknown24;
    pRecord->mpUnknown24 = pSubs;
    lbl_803075E0[pRecord->mUnknown2E].mpUnknown4(pRecord);
}

extern "C" void fn_8003EC54(Record_8003EC04 *pRecord)
{
    unsigned int i;
    Sub_8003EC54 *pA;
    Sub_8003EC54 *pB;

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

extern "C" void fn_8003ED30(int value)
{
    unsigned int i;
    unsigned int j;

    fn_800895C4();
    for (i = 0; i < 8; i++) {
        lbl_803075E0[i].mUnknown0 = 0;
        lbl_803075E0[i].mUnknown1 = 0;
        lbl_803075E0[i].mpUnknown4 = 0;
    }
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            lbl_80307620[i][j] = 0;
        }
    }
}

extern "C" void fn_8003EDB8(void)
{
    fn_800895E0();
}

extern "C" void fn_8003EDD8(unsigned char type, unsigned char count, Callback_802DCF9C pCallback)
{
    lbl_803075E0[type].mUnknown0 = 1;
    lbl_803075E0[type].mUnknown1 = count;
    lbl_803075E0[type].mpUnknown4 = pCallback;
}

extern "C" void fn_8003EE00(unsigned char type)
{
    lbl_803075E0[type].mUnknown0 = 0;
    lbl_803075E0[type].mUnknown1 = 0;
    lbl_803075E0[type].mpUnknown4 = 0;
}

extern "C" void fn_8003EE2C(unsigned char a, unsigned char b, Callback_8003EE2C pCallback)
{
    unsigned char lo = (a < b) ? a : b;
    unsigned char hi = (a > b) ? a : b;

    lbl_80307620[lo][hi] = pCallback;
}

extern "C" Set_8003EE6C *fn_8003EE6C(int count, int subCount)
{
    Set_8003EE6C *pSet = (Set_8003EE6C *)fn_801D2B7C(sizeof(Set_8003EE6C), 0, 0);

    fn_801C1F94(pSet, 0, sizeof(Set_8003EE6C));
    pSet->mUnknown4 = count;
    pSet->mUnknown8 = 0;
    pSet->mpUnknown0 = (Record_8003EC04 *)fn_801D2B7C(count * sizeof(Record_8003EC04), 0, 0);
    fn_801C1F94(pSet->mpUnknown0, 0, pSet->mUnknown4 * sizeof(Record_8003EC04));
    pSet->mUnknownC = subCount;
    pSet->mUnknown10 = 0;
    pSet->mpUnknown14 = 0;
    pSet->mpUnknown18 = 0;
    if (subCount) {
        pSet->mpUnknown14 = (Sub_8003EC54 *)fn_801D2B7C(subCount * sizeof(Sub_8003EC54), 0, 0);
        fn_801C1F94(pSet->mpUnknown14, 0, pSet->mUnknownC * sizeof(Sub_8003EC54));
        pSet->mpUnknown18 = (Sub_8003EC54 *)fn_801D2B7C(pSet->mUnknownC * sizeof(Sub_8003EC54), 0, 0);
        fn_801C1F94(pSet->mpUnknown18, 0, pSet->mUnknownC * sizeof(Sub_8003EC54));
    }
    return pSet;
}

extern "C" void fn_8003EF5C(Set_8003EE6C *pSet)
{
    if (pSet->mpUnknown14 && pSet->mpUnknown18) {
        fn_801D2BD0(pSet->mpUnknown14);
        fn_801D2BD0(pSet->mpUnknown18);
    }
    fn_801D2BD0(pSet->mpUnknown0);
    fn_801D2BD0(pSet);
}

extern "C" Record_8003EC04 *fn_8003EFB8(Set_8003EE6C *pSet, unsigned char type, int value)
{
    Record_8003EC04 *pRecord = &pSet->mpUnknown0[pSet->mUnknown8];
    unsigned char count = lbl_803075E0[type].mUnknown1;

    pRecord->mUnknown2C = 1;
    pRecord->mUnknown2E = type;
    pRecord->mUnknown28 = value;
    pRecord->mUnknown2F = count;
    if (count) {
        pRecord->mpUnknown20 = &pSet->mpUnknown14[pSet->mUnknown10];
        pRecord->mpUnknown24 = &pSet->mpUnknown18[pSet->mUnknown10];
    } else {
        pRecord->mpUnknown20 = 0;
        pRecord->mpUnknown24 = 0;
    }
    pSet->mUnknown10 += count;
    pSet->mUnknown8++;
    return pRecord;
}

extern "C" void fn_8003F04C(Set_8003EE6C *pSet)
{
    unsigned int i;

    if (pSet) {
        for (i = 0; i < pSet->mUnknown8; i++) {
            fn_8003EC04(&pSet->mpUnknown0[i]);
        }
    }
}

extern "C" void fn_8003F0AC(Set_8003EE6C *pA, Set_8003EE6C *pB)
{
    unsigned int i;
    unsigned int j;

    if (pA && pB) {
        fn_800895E4();
        if (pA == pB) {
            for (i = 0; i < pA->mUnknown8; i++) {
                for (j = i + 1; j < pA->mUnknown8; j++) {
                    fn_8003F1B8(&pA->mpUnknown0[i], &pA->mpUnknown0[j]);
                }
            }
        } else {
            for (i = 0; i < pA->mUnknown8; i++) {
                for (j = 0; j < pB->mUnknown8; j++) {
                    fn_8003F1B8(&pA->mpUnknown0[i], &pB->mpUnknown0[j]);
                }
            }
        }
        fn_800895E8();
    }
}

extern "C" void fn_8003F1B8(Record_8003EC04 *pA, Record_8003EC04 *pB)
{
    Contact_80089330 contacts[128];
    Plane_800894B8 plane;
    unsigned char hit[16];
    ContactList_8030BD74 *pContacts = 0;
    Sub_8003EC54 *pSubsA = pA->mpUnknown20;
    Sub_8003EC54 *pSubsB = pB->mpUnknown20;
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
    if (lbl_80307620[pA->mUnknown2E][pB->mUnknown2E] == 0) {
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
            lbl_80307620[pA->mUnknown2E][pB->mUnknown2E](pA, pB, pContacts);
        }
    }
    pA->mUnknown18 = radiusA;
    pB->mUnknown18 = radiusB;
}

extern "C" int fn_8003F4E8(Record_8003EC04 *pA, Record_8003EC04 *pB, Record_8003EC04 *pBase)
{
    int result = fn_80238258(pA, pB, 32);
    int i;

    result |= pA->mUnknown2F != pB->mUnknown2F;
    result |= pA->mUnknown2C != pB->mUnknown2C;
    result |= pA->mUnknown2E != pB->mUnknown2E;
    result |= pA->mUnknown28 != pB->mUnknown28;
    for (i = 0; i < pA->mUnknown2F; i++) {
        result |= fn_80238258((char *)&pA->mpUnknown20[i] + ((char *)pA - (char *)pBase),
                              (char *)&pB->mpUnknown20[i] + ((char *)pB - (char *)pBase), sizeof(Sub_8003EC54));
        result |= fn_80238258((char *)&pA->mpUnknown24[i] + ((char *)pA - (char *)pBase),
                              (char *)&pB->mpUnknown24[i] + ((char *)pB - (char *)pBase), sizeof(Sub_8003EC54));
    }
    return result;
}

extern "C" void fn_8003F60C(Set_8003EE6C *pSet)
{
    unsigned int i;

    if (pSet) {
        for (i = 0; i < pSet->mUnknown8; i++) {
            fn_8003EC54(&pSet->mpUnknown0[i]);
        }
    }
}
