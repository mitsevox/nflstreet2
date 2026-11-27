/* Rigid-body physics: the sweep-and-prune broad phase that finds which bodies may touch. Each
   body's world box puts a min and a max endpoint on a sorted list per axis; keeping the lists
   sorted as boxes move flags the object pairs whose intervals overlap on every axis, and the
   collision system runs its shape tests only on those pairs. */

#include <string.h>
#include "engine/physbroadphase.h"

void *operator new[](unsigned int size, int unknown);

BroadPhase::BroadPhase(unsigned int maxObjects, unsigned int maxPairs)
{
    unsigned int i;
    unsigned int count;
    unsigned int axis;

    mMaxObjects = maxObjects;
    mMaxPairs = maxPairs;
    count = maxObjects * (maxObjects - 1) / 2;
    mpOverlaps = new (0) BroadPhaseOverlap[count];
    for (i = 0; i < count; i++) {
        mpOverlaps[i].mPair = BROADPHASE_NONE;
        mpOverlaps[i].mAxes = 0;
    }
    mpPairs = new (0) BroadPhasePair[maxPairs];
    mpFirstPair = 0;
    mpFreePair = 0;
    for (i = 0; i < maxPairs; i++) {
        FreePair(&mpPairs[i]);
    }
    for (axis = 0; axis < 3; axis++) {
        mAxisHead[axis] = BROADPHASE_NONE;
    }
    mFreeEndpoint = BROADPHASE_NONE;
    mpEndpoints = new (0) BroadPhaseEndpoint[maxObjects * 6];
    for (i = 0; i < maxObjects * 6; i++) {
        FreeEndpoint(i);
    }
    mFirstObject = BROADPHASE_NONE;
    mFreeObject = BROADPHASE_NONE;
    mpObjects = new (0) BroadPhaseObject[maxObjects];
    for (i = 0; i < maxObjects; i++) {
        FreeObject(i);
    }
}

BroadPhase::~BroadPhase()
{
    unsigned int axis;

    if (mpObjects) {
        delete[] mpObjects;
    }
    if (mpEndpoints) {
        delete[] mpEndpoints;
    }
    if (mpPairs) {
        delete[] mpPairs;
    }
    if (mpOverlaps) {
        delete[] mpOverlaps;
    }
    mpObjects = 0;
    mpEndpoints = 0;
    mpPairs = 0;
    mpOverlaps = 0;
    mpFreePair = 0;
    mFirstObject = BROADPHASE_NONE;
    mFreeObject = BROADPHASE_NONE;
    mpFirstPair = 0;
    mFreeEndpoint = BROADPHASE_NONE;
    for (axis = 0; axis < 3; axis++) {
        mAxisHead[axis] = BROADPHASE_NONE;
    }
    mMaxObjects = 0;
}

void BroadPhase::AddObject(BroadPhaseBox *pBox, unsigned int mask, void *user)
{
    unsigned short object = AllocObject();
    BroadPhaseObject *pObject = &mpObjects[object];
    unsigned short axis;

    pObject->mUser = user;
    pObject->mpBox = pBox;
    pObject->mMask = mask;
    if (mFirstObject != BROADPHASE_NONE) {
        mpObjects[mFirstObject].mPrev = object;
    }
    pObject->mPrev = BROADPHASE_NONE;
    pObject->mNext = mFirstObject;
    mFirstObject = object;
    for (axis = 0; axis <= 2; axis++) {
        InsertObjectOnAxis(axis, object);
    }
}

void BroadPhase::RemoveObject(BroadPhaseBox *pBox)
{
    unsigned short object = BROADPHASE_NONE;
    unsigned short i;
    unsigned short other;
    unsigned short axis;
    BroadPhaseOverlap *pOverlap;

    for (i = 0; i < mMaxObjects; i++) {
        if (mpObjects[i].mpBox == pBox) {
            object = i;
            break;
        }
    }
    if (mpObjects[object].mNext != BROADPHASE_NONE) {
        mpObjects[mpObjects[object].mNext].mPrev = mpObjects[object].mPrev;
    }
    if (mpObjects[object].mPrev != BROADPHASE_NONE) {
        mpObjects[mpObjects[object].mPrev].mNext = mpObjects[object].mNext;
    }
    if (mFirstObject == object) {
        mFirstObject = mpObjects[object].mNext;
    }
    mpObjects[object].mNext = BROADPHASE_NONE;
    mpObjects[object].mPrev = BROADPHASE_NONE;
    for (axis = 0; axis <= 2; axis++) {
        RemoveObjectFromAxis(axis, object);
    }
    for (other = 0; other < mMaxObjects; other++) {
        if (other != object) {
            pOverlap = &mpOverlaps[GetOverlapIndex(object, other)];
            if (pOverlap->mPair != BROADPHASE_NONE) {
                RemovePair(pOverlap->mPair);
            }
            pOverlap->mAxes = 0;
            pOverlap->mPair = BROADPHASE_NONE;
        }
    }
}

BroadPhasePair *BroadPhase::UpdatePairs()
{
    unsigned int axis;

    for (axis = 0; axis <= 2; axis++) {
        SortAxis(axis);
    }
    return mpFirstPair;
}

void *BroadPhase::GetObjectUser(unsigned short object)
{
    return mpObjects[object].mUser;
}

void BroadPhase::SortAxis(int axis)
{
    unsigned short endpoint = mAxisHead[axis];
    unsigned short next;
    unsigned short prev;
    unsigned char isMin;
    unsigned char isMinNext;
    float value;
    float nextValue;

    if (endpoint == BROADPHASE_NONE) {
        return;
    }
    value = GetEndpointValue(axis, endpoint, &isMin);
    next = mpEndpoints[endpoint].mNext;
    while (next != BROADPHASE_NONE) {
        nextValue = GetEndpointValue(axis, next, &isMinNext);
        if (value > nextValue || (value == nextValue && !isMin && isMinNext)) {
            prev = mpEndpoints[endpoint].mPrev;
            SwapEndpoints(endpoint, next, axis);
            if (prev == BROADPHASE_NONE) {
                prev = mAxisHead[axis];
            }
            endpoint = prev;
            next = mpEndpoints[endpoint].mNext;
            value = GetEndpointValue(axis, endpoint, &isMin);
        } else {
            endpoint = next;
            next = mpEndpoints[endpoint].mNext;
            value = nextValue;
            isMin = isMinNext;
        }
    }
}

void BroadPhase::SwapEndpoints(unsigned short a, unsigned short b, int axis)
{
    unsigned short objectA = mpEndpoints[a].mObject;
    unsigned short objectB = mpEndpoints[b].mObject;
    unsigned short isMaxA = mpEndpoints[a].mIsMax;
    unsigned short isMaxB = mpEndpoints[b].mIsMax;

    if ((mpObjects[objectA].mMask & mpObjects[objectB].mMask) == 0) {
        TestAxisOverlap(objectA, objectB, axis);
    }
    mpEndpoints[a].mObject = objectB;
    mpEndpoints[a].mIsMax = isMaxB;
    mpEndpoints[b].mObject = objectA;
    mpEndpoints[b].mIsMax = isMaxA;
}

unsigned int BroadPhase::GetOverlapIndex(unsigned short a, unsigned short b)
{
    if (a > b) {
        int index = b * mMaxObjects - (b + 1) * b / 2u - 1;
        return index + a - b;
    }
    int index = a * mMaxObjects - (a + 1) * a / 2u - 1;
    return index + b - a;
}

float BroadPhase::GetEndpointValue(int axis, unsigned short endpoint, unsigned char *pIsMin)
{
    BroadPhaseEndpoint *pEndpoint = &mpEndpoints[endpoint];

    *pIsMin = pEndpoint->mIsMax == 0;
    return mpObjects[pEndpoint->mObject].mpBox->mCorner[pEndpoint->mIsMax][axis];
}

void BroadPhase::TestAxisOverlap(unsigned short a, unsigned short b, unsigned short axis)
{
    unsigned short bit = 1 << axis;
    BroadPhaseBox *pBoxA;
    BroadPhaseBox *pBoxB;
    BroadPhaseOverlap *pOverlap;
    float minA;
    float maxA;
    float minB;
    float maxB;
    unsigned int index = GetOverlapIndex(a, b);

    pBoxB = mpObjects[b].mpBox;
    pBoxA = mpObjects[a].mpBox;
    minA = pBoxA->mCorner[0][axis];
    maxA = pBoxA->mCorner[1][axis];
    minB = pBoxB->mCorner[0][axis];
    maxB = pBoxB->mCorner[1][axis];
    pOverlap = &mpOverlaps[index];
    if (minA > maxB || maxA < minB) {
        mpOverlaps[index].mAxes &= ~bit;
    } else {
        mpOverlaps[index].mAxes |= bit;
    }
    if ((pOverlap->mAxes & 7) == 7) {
        if (pOverlap->mPair == BROADPHASE_NONE) {
            AddPair(a, b, pOverlap);
        }
    } else if (pOverlap->mPair != BROADPHASE_NONE) {
        RemovePair(pOverlap->mPair);
        pOverlap->mPair = BROADPHASE_NONE;
    }
}

void BroadPhase::AddPair(unsigned short a, unsigned short b, BroadPhaseOverlap *pOverlap)
{
    BroadPhasePair *pPair = AllocPair();

    if (pPair) {
        pPair->mObjectA = a;
        pPair->mObjectB = b;
        pPair->mpPrev = 0;
        pPair->mpNext = mpFirstPair;
        if (mpFirstPair) {
            mpFirstPair->mpPrev = pPair;
        }
        mpFirstPair = pPair;
        pOverlap->mPair = pPair - mpPairs;
    }
}

void BroadPhase::RemovePair(unsigned short pair)
{
    BroadPhasePair *pPair = &mpPairs[pair];

    if (pPair->mpNext) {
        pPair->mpNext->mpPrev = pPair->mpPrev;
    }
    if (pPair->mpPrev) {
        pPair->mpPrev->mpNext = pPair->mpNext;
    }
    if (mpFirstPair == pPair) {
        mpFirstPair = pPair->mpNext;
    }
    FreePair(pPair);
}

void BroadPhase::InsertObjectOnAxis(int axis, unsigned short object)
{
    unsigned short endpoint = mAxisHead[axis];
    unsigned short minEndpoint;
    unsigned short maxEndpoint;
    BroadPhaseEndpoint *pEndpoint;

    while (endpoint != BROADPHASE_NONE) {
        pEndpoint = &mpEndpoints[endpoint];
        if ((mpObjects[object].mMask & mpObjects[pEndpoint->mObject].mMask) == 0 &&
            pEndpoint->mIsMax == 0) {
            TestAxisOverlap(object, pEndpoint->mObject, axis);
        }
        endpoint = pEndpoint->mNext;
    }
    minEndpoint = AllocEndpoint();
    maxEndpoint = AllocEndpoint();
    mpEndpoints[minEndpoint].mObject = object;
    mpEndpoints[minEndpoint].mIsMax = 0;
    mpEndpoints[minEndpoint].mNext = BROADPHASE_NONE;
    mpEndpoints[minEndpoint].mPrev = BROADPHASE_NONE;
    mpEndpoints[maxEndpoint].mObject = object;
    mpEndpoints[maxEndpoint].mIsMax = 1;
    mpEndpoints[maxEndpoint].mNext = BROADPHASE_NONE;
    mpEndpoints[maxEndpoint].mPrev = BROADPHASE_NONE;
    InsertEndpoint(axis, minEndpoint);
    InsertEndpoint(axis, maxEndpoint);
}

void BroadPhase::RemoveObjectFromAxis(int axis, unsigned short object)
{
    unsigned short endpoint = mAxisHead[axis];
    unsigned short next;

    while (endpoint != BROADPHASE_NONE) {
        next = mpEndpoints[endpoint].mNext;
        if (mpEndpoints[endpoint].mObject == object) {
            if (next != BROADPHASE_NONE) {
                mpEndpoints[next].mPrev = mpEndpoints[endpoint].mPrev;
            }
            if (mpEndpoints[endpoint].mPrev != BROADPHASE_NONE) {
                mpEndpoints[mpEndpoints[endpoint].mPrev].mNext = mpEndpoints[endpoint].mNext;
            }
            if (mAxisHead[axis] == endpoint) {
                mAxisHead[axis] = mpEndpoints[endpoint].mNext;
            }
            mpEndpoints[endpoint].mNext = BROADPHASE_NONE;
            mpEndpoints[endpoint].mPrev = BROADPHASE_NONE;
            FreeEndpoint(endpoint);
        }
        endpoint = next;
    }
}

void BroadPhase::InsertEndpoint(int axis, unsigned short endpoint)
{
    BroadPhaseEndpoint *pEndpoint = &mpEndpoints[endpoint];
    BroadPhaseEndpoint *pCurrent;
    unsigned char isMin = pEndpoint->mIsMax == 0;
    float value = mpObjects[pEndpoint->mObject].mpBox->mCorner[pEndpoint->mIsMax][axis];
    unsigned short current = mAxisHead[axis];
    unsigned short next;
    float currentValue;

    if (current == BROADPHASE_NONE) {
        mAxisHead[axis] = endpoint;
        pEndpoint->mPrev = current;
        pEndpoint->mNext = current;
    } else {
        for (;;) {
            pCurrent = &mpEndpoints[current];
            next = pCurrent->mNext;
            currentValue = mpObjects[pCurrent->mObject].mpBox->mCorner[pCurrent->mIsMax][axis];
            if ((isMin && value == currentValue) || value < currentValue) {
                if (pCurrent->mPrev != BROADPHASE_NONE) {
                    mpEndpoints[pCurrent->mPrev].mNext = endpoint;
                } else {
                    mAxisHead[axis] = endpoint;
                }
                pEndpoint->mNext = current;
                pEndpoint->mPrev = pCurrent->mPrev;
                pCurrent->mPrev = endpoint;
                return;
            }
            if (next == BROADPHASE_NONE) {
                pEndpoint->mNext = next;
                pEndpoint->mPrev = current;
                mpEndpoints[current].mNext = endpoint;
                return;
            }
            current = next;
        }
    }
}

BroadPhasePair *BroadPhase::AllocPair()
{
    BroadPhasePair *pPair = mpFreePair;

    if (pPair == 0) {
        return 0;
    }
    mpFreePair = pPair->mpNext;
    memset(pPair, 0, sizeof(BroadPhasePair));
    return pPair;
}

void BroadPhase::FreePair(BroadPhasePair *pPair)
{
    pPair->mpNext = mpFreePair;
    mpFreePair = pPair;
}

unsigned short BroadPhase::AllocEndpoint()
{
    unsigned short endpoint = mFreeEndpoint;

    mFreeEndpoint = mpEndpoints[endpoint].mNext;
    memset(&mpEndpoints[endpoint], 0, sizeof(BroadPhaseEndpoint));
    return endpoint;
}

void BroadPhase::FreeEndpoint(unsigned short endpoint)
{
    mpEndpoints[endpoint].mNext = mFreeEndpoint;
    mFreeEndpoint = endpoint;
}

unsigned short BroadPhase::AllocObject()
{
    unsigned short object = mFreeObject;

    mFreeObject = mpObjects[object].mNext;
    memset(&mpObjects[object], 0, sizeof(BroadPhaseObject));
    return object;
}

void BroadPhase::FreeObject(unsigned short object)
{
    mpObjects[object].mNext = mFreeObject;
    mFreeObject = object;
}
