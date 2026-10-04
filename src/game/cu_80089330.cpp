#include "game/cu_80089330.h"
#include "game/cu_8003EC04.h"
#include "game/fn_802270D4.h"

extern "C" {
float fn_80088FFC(float *pA0, float *pA1, float *pB0, float *pB1, float *pOut);
void fn_802271F0(float *pOut, float *pIn);
void fn_80227930(float *pOut, float *pA, float *pB, float t);
}

static ContactList_8030BD74 lbl_8030BD74;

void fn_80089330(float *pCapsuleA, float *pCapsuleB, unsigned int index)
{
    float point[3];
    float radius = pCapsuleA[3] + pCapsuleB[3];
    int n;

    radius = radius * radius;
    if (fn_80088FFC(pCapsuleA, pCapsuleA + 4, pCapsuleB, pCapsuleB + 4, point) < radius) {
        n = lbl_8030BD74.mCount;
        lbl_8030BD74.mpContacts[n].mUnknown0 = point[0];
        lbl_8030BD74.mpContacts[n].mUnknown4 = point[1];
        lbl_8030BD74.mpContacts[n].mUnknown8 = point[2];
        lbl_8030BD74.mpContacts[n].mUnknownC = index;
        lbl_8030BD74.mpContacts[n].mUnknownD = index >> 8;
        lbl_8030BD74.mCount = n + 1;
    }
}

int fn_800893F0(Record_8003EC04 *pA, Record_8003EC04 *pB)
{
    float t;
    float d;
    float r;

    t = pA->mUnknown0 - pB->mUnknown0;
    d = t * t;
    t = pA->mUnknown4 - pB->mUnknown4;
    d += t * t;
    r = pA->mUnknown18 + pB->mUnknown18;
    if (d <= r * r) {
        if (pA->mUnknown14 < pB->mUnknown10 || pA->mUnknown10 > pB->mUnknown14) {
            return 0;
        }
        return 1;
    }
    return 0;
}

int fn_80089464(float *pSphereA, float *pSphereB)
{
    float t;
    float d;
    float r;

    t = pSphereA[0] - pSphereB[0];
    d = t * t;
    t = pSphereA[1] - pSphereB[1];
    d += t * t;
    t = pSphereA[2] - pSphereB[2];
    d += t * t;
    r = pSphereA[3] + pSphereB[3];
    return d <= r * r;
}

void fn_800894B8(Plane_800894B8 *pPlane, Record_8003EC04 *pA, Record_8003EC04 *pB)
{
    float delta[3];

    fn_802276B4(delta, pA, pB);
    fn_802271F0(&pPlane->mUnknown10, delta);
    fn_80227930(&pPlane->mUnknown0, &pA->mUnknown0, &pB->mUnknown0, 0.5f);
}

int fn_80089514(Plane_800894B8 *pPlane, float *pCapsule)
{
    float d0 = (pCapsule[0] - pPlane->mUnknown0) * pPlane->mUnknown10 + (pCapsule[1] - pPlane->mUnknown4) * pPlane->mUnknown14 + (pCapsule[2] - pPlane->mUnknown8) * pPlane->mUnknown18;
    float d1 = (pCapsule[4] - pPlane->mUnknown0) * pPlane->mUnknown10 + (pCapsule[5] - pPlane->mUnknown4) * pPlane->mUnknown14 + (pCapsule[6] - pPlane->mUnknown8) * pPlane->mUnknown18;
    int result = 0;

    if (d0 < pCapsule[3] || d1 < pCapsule[3]) {
        result = 1;
    }
    return result;
}

void fn_8008959C(Contact_80089330 *pContacts, int capacity)
{
    lbl_8030BD74.mCount = 0;
    lbl_8030BD74.mCapacity = capacity;
    lbl_8030BD74.mpContacts = pContacts;
}

ContactList_8030BD74 *fn_800895B8(void)
{
    return &lbl_8030BD74;
}

void fn_800895C4(void)
{
    lbl_8030BD74.mCount = 0;
    lbl_8030BD74.mCapacity = 0;
    lbl_8030BD74.mpContacts = 0;
}

void fn_800895E0(void)
{
}

void fn_800895E4(void)
{
}

void fn_800895E8(void)
{
}
