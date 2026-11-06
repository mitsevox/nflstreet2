/* Player collision tests: cylinder, sphere and capsule overlap checks, the plane between
   two players, and the list of contact points the detailed test fills. */

#include "game/CollideContacts.h"
#include "game/Collide.h"
#include "game/fn_802270D4.h"

extern "C" {
float fn_80088FFC(float *pA0, float *pA1, float *pB0, float *pB1, float *pOut);
void fn_802271F0(float *pOut, float *pIn);
void fn_80227930(float *pOut, float *pA, float *pB, float t);
}

static CollideContactList_t _Collide_ContactList;

void CollideAddCapsuleContact(float *pCapsuleA, float *pCapsuleB, unsigned int index)
{
    float point[3];
    float radius = pCapsuleA[3] + pCapsuleB[3];
    int n;

    radius = radius * radius;
    if (fn_80088FFC(pCapsuleA, pCapsuleA + 4, pCapsuleB, pCapsuleB + 4, point) < radius) {
        n = _Collide_ContactList.mCount;
        _Collide_ContactList.mpContacts[n].mUnknown0 = point[0];
        _Collide_ContactList.mpContacts[n].mUnknown4 = point[1];
        _Collide_ContactList.mpContacts[n].mUnknown8 = point[2];
        _Collide_ContactList.mpContacts[n].mUnknownC = index;
        _Collide_ContactList.mpContacts[n].mUnknownD = index >> 8;
        _Collide_ContactList.mCount = n + 1;
    }
}

int CollideTestCylinders(CollideObject_t *pA, CollideObject_t *pB)
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

int CollideTestSpheres(float *pSphereA, float *pSphereB)
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

void CollideMakeSplitPlane(CollidePlane_t *pPlane, CollideObject_t *pA, CollideObject_t *pB)
{
    float delta[3];

    fn_802276B4(delta, pA, pB);
    fn_802271F0(&pPlane->mUnknown10, delta);
    fn_80227930(&pPlane->mUnknown0, &pA->mUnknown0, &pB->mUnknown0, 0.5f);
}

int CollideCapsuleReachesPlane(CollidePlane_t *pPlane, float *pCapsule)
{
    float d0 = (pCapsule[0] - pPlane->mUnknown0) * pPlane->mUnknown10 + (pCapsule[1] - pPlane->mUnknown4) * pPlane->mUnknown14 + (pCapsule[2] - pPlane->mUnknown8) * pPlane->mUnknown18;
    float d1 = (pCapsule[4] - pPlane->mUnknown0) * pPlane->mUnknown10 + (pCapsule[5] - pPlane->mUnknown4) * pPlane->mUnknown14 + (pCapsule[6] - pPlane->mUnknown8) * pPlane->mUnknown18;
    int result = 0;

    if (d0 < pCapsule[3] || d1 < pCapsule[3]) {
        result = 1;
    }
    return result;
}

void CollideContactsBegin(CollideContact_t *pContacts, int capacity)
{
    _Collide_ContactList.mCount = 0;
    _Collide_ContactList.mCapacity = capacity;
    _Collide_ContactList.mpContacts = pContacts;
}

CollideContactList_t *CollideGetContacts(void)
{
    return &_Collide_ContactList;
}

void CollideContactsEnd(void)
{
    _Collide_ContactList.mCount = 0;
    _Collide_ContactList.mCapacity = 0;
    _Collide_ContactList.mpContacts = 0;
}

void CollideContactsStub0(void)
{
}

void CollideContactsStub1(void)
{
}

void CollideContactsStub2(void)
{
}
