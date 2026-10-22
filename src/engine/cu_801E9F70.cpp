#include "game/fn_801C1F94.h"
#define NONE_801E9F70 0xFFFF

void *operator new[](unsigned int size, int unknown);

/* Corner vector, read by axis index. */
struct Vec_801E9F70 {
    float operator[](int i) const { return (&x)[i]; }

    float x;
    float y;
    float z;
};

/* Axis-aligned box of an object (defined in another file): min and max corners. */
struct Box_801E9F70 {
    Vec_801E9F70 mCorner[2];
};

/* Tracked object. */
struct Object_801E9F70 {
    int mUser;
    Box_801E9F70 *mpBox;
    unsigned int mMask;
    unsigned short mNext;
    unsigned short mPrev;
};

/* Interval endpoint on one axis. */
struct Endpoint_801E9F70 {
    unsigned short mObject;
    unsigned short mIsMax;
    unsigned short mNext;
    unsigned short mPrev;
};

/* Overlapping pair. */
struct Pair_801E9F70 {
    unsigned short mObjectA;
    unsigned short mObjectB;
    Pair_801E9F70 *mpNext;
    Pair_801E9F70 *mpPrev;
};

/* Overlap state of two objects: one bit per axis and the pair index. */
struct Overlap_801E9F70 {
    unsigned short mAxes;
    unsigned short mPair;
};

/* Sweep-and-prune broad phase over three axes. */
class Class_801E9F70 {
public:
    Class_801E9F70(unsigned int maxObjects, unsigned int maxPairs);
    virtual ~Class_801E9F70();
    void fn_801EA1D8(Box_801E9F70 *pBox, unsigned int mask, int user);
    void fn_801EA284(Box_801E9F70 *pBox);
    Pair_801E9F70 *fn_801EA428();
    int fn_801EA470(unsigned short object);
    void fn_801EA480(int axis);
    void fn_801EA5C0(unsigned short a, unsigned short b, int axis);
    unsigned int fn_801EA668(unsigned short a, unsigned short b);
    float fn_801EA6C0(int axis, unsigned short endpoint, unsigned char *pIsMin);
    void fn_801EA708(unsigned short a, unsigned short b, unsigned short axis);
    void fn_801EA818(unsigned short a, unsigned short b, Overlap_801E9F70 *pOverlap);
    void fn_801EA8A0(unsigned short pair);
    void fn_801EA908(int axis, unsigned short object);
    void fn_801EAA5C(int axis, unsigned short object);
    void fn_801EAB60(int axis, unsigned short endpoint);
    Pair_801E9F70 *fn_801EAC98();
    void fn_801EACF0(Pair_801E9F70 *pPair);
    unsigned short fn_801EAD00();
    void fn_801EAD50(unsigned short endpoint);
    unsigned short fn_801EAD6C();
    void fn_801EADBC(unsigned short object);

    unsigned int mMaxObjects;
    unsigned int mMaxPairs;
    Object_801E9F70 *mpObjects;
    unsigned short mFirstObject;
    unsigned short mFreeObject;
    unsigned short mAxisHead[3];
    unsigned short mFreeEndpoint;
    Endpoint_801E9F70 *mpEndpoints;
    Pair_801E9F70 *mpPairs;
    Pair_801E9F70 *mpFreePair;
    Pair_801E9F70 *mpFirstPair;
    Overlap_801E9F70 *mpOverlaps;
};

Class_801E9F70::Class_801E9F70(unsigned int maxObjects, unsigned int maxPairs)
{
    unsigned int i;
    unsigned int count;
    unsigned int axis;

    mMaxObjects = maxObjects;
    mMaxPairs = maxPairs;
    count = maxObjects * (maxObjects - 1) / 2;
    mpOverlaps = new (0) Overlap_801E9F70[count];
    for (i = 0; i < count; i++) {
        mpOverlaps[i].mPair = NONE_801E9F70;
        mpOverlaps[i].mAxes = 0;
    }
    mpPairs = new (0) Pair_801E9F70[maxPairs];
    mpFirstPair = 0;
    mpFreePair = 0;
    for (i = 0; i < maxPairs; i++) {
        fn_801EACF0(&mpPairs[i]);
    }
    for (axis = 0; axis < 3; axis++) {
        mAxisHead[axis] = NONE_801E9F70;
    }
    mFreeEndpoint = NONE_801E9F70;
    mpEndpoints = new (0) Endpoint_801E9F70[maxObjects * 6];
    for (i = 0; i < maxObjects * 6; i++) {
        fn_801EAD50(i);
    }
    mFirstObject = NONE_801E9F70;
    mFreeObject = NONE_801E9F70;
    mpObjects = new (0) Object_801E9F70[maxObjects];
    for (i = 0; i < maxObjects; i++) {
        fn_801EADBC(i);
    }
}

Class_801E9F70::~Class_801E9F70()
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
    mFirstObject = NONE_801E9F70;
    mFreeObject = NONE_801E9F70;
    mpFirstPair = 0;
    mFreeEndpoint = NONE_801E9F70;
    for (axis = 0; axis < 3; axis++) {
        mAxisHead[axis] = NONE_801E9F70;
    }
    mMaxObjects = 0;
}

void Class_801E9F70::fn_801EA1D8(Box_801E9F70 *pBox, unsigned int mask, int user)
{
    unsigned short object = fn_801EAD6C();
    Object_801E9F70 *pObject = &mpObjects[object];
    unsigned short axis;

    pObject->mUser = user;
    pObject->mpBox = pBox;
    pObject->mMask = mask;
    if (mFirstObject != NONE_801E9F70) {
        mpObjects[mFirstObject].mPrev = object;
    }
    pObject->mPrev = NONE_801E9F70;
    pObject->mNext = mFirstObject;
    mFirstObject = object;
    for (axis = 0; axis <= 2; axis++) {
        fn_801EA908(axis, object);
    }
}

void Class_801E9F70::fn_801EA284(Box_801E9F70 *pBox)
{
    unsigned short object = NONE_801E9F70;
    unsigned short i;
    unsigned short other;
    unsigned short axis;
    Overlap_801E9F70 *pOverlap;

    for (i = 0; i < mMaxObjects; i++) {
        if (mpObjects[i].mpBox == pBox) {
            object = i;
            break;
        }
    }
    if (mpObjects[object].mNext != NONE_801E9F70) {
        mpObjects[mpObjects[object].mNext].mPrev = mpObjects[object].mPrev;
    }
    if (mpObjects[object].mPrev != NONE_801E9F70) {
        mpObjects[mpObjects[object].mPrev].mNext = mpObjects[object].mNext;
    }
    if (mFirstObject == object) {
        mFirstObject = mpObjects[object].mNext;
    }
    mpObjects[object].mNext = NONE_801E9F70;
    mpObjects[object].mPrev = NONE_801E9F70;
    for (axis = 0; axis <= 2; axis++) {
        fn_801EAA5C(axis, object);
    }
    for (other = 0; other < mMaxObjects; other++) {
        if (other != object) {
            pOverlap = &mpOverlaps[fn_801EA668(object, other)];
            if (pOverlap->mPair != NONE_801E9F70) {
                fn_801EA8A0(pOverlap->mPair);
            }
            pOverlap->mAxes = 0;
            pOverlap->mPair = NONE_801E9F70;
        }
    }
}

Pair_801E9F70 *Class_801E9F70::fn_801EA428()
{
    unsigned int axis;

    for (axis = 0; axis <= 2; axis++) {
        fn_801EA480(axis);
    }
    return mpFirstPair;
}

int Class_801E9F70::fn_801EA470(unsigned short object)
{
    return mpObjects[object].mUser;
}

void Class_801E9F70::fn_801EA480(int axis)
{
    unsigned short endpoint = mAxisHead[axis];
    unsigned short next;
    unsigned short prev;
    unsigned char isMin;
    unsigned char isMinNext;
    float value;
    float nextValue;

    if (endpoint == NONE_801E9F70) {
        return;
    }
    value = fn_801EA6C0(axis, endpoint, &isMin);
    next = mpEndpoints[endpoint].mNext;
    while (next != NONE_801E9F70) {
        nextValue = fn_801EA6C0(axis, next, &isMinNext);
        if (value > nextValue || (value == nextValue && !isMin && isMinNext)) {
            prev = mpEndpoints[endpoint].mPrev;
            fn_801EA5C0(endpoint, next, axis);
            if (prev == NONE_801E9F70) {
                prev = mAxisHead[axis];
            }
            endpoint = prev;
            next = mpEndpoints[endpoint].mNext;
            value = fn_801EA6C0(axis, endpoint, &isMin);
        } else {
            endpoint = next;
            next = mpEndpoints[endpoint].mNext;
            value = nextValue;
            isMin = isMinNext;
        }
    }
}

void Class_801E9F70::fn_801EA5C0(unsigned short a, unsigned short b, int axis)
{
    unsigned short objectA = mpEndpoints[a].mObject;
    unsigned short objectB = mpEndpoints[b].mObject;
    unsigned short isMaxA = mpEndpoints[a].mIsMax;
    unsigned short isMaxB = mpEndpoints[b].mIsMax;

    if ((mpObjects[objectA].mMask & mpObjects[objectB].mMask) == 0) {
        fn_801EA708(objectA, objectB, axis);
    }
    mpEndpoints[a].mObject = objectB;
    mpEndpoints[a].mIsMax = isMaxB;
    mpEndpoints[b].mObject = objectA;
    mpEndpoints[b].mIsMax = isMaxA;
}

unsigned int Class_801E9F70::fn_801EA668(unsigned short a, unsigned short b)
{
    if (a > b) {
        return b * mMaxObjects - ((unsigned int)((b + 1) * b) / 2 + 1) + a - b;
    }
    return a * mMaxObjects - ((unsigned int)((a + 1) * a) / 2 + 1) + b - a;
}

float Class_801E9F70::fn_801EA6C0(int axis, unsigned short endpoint, unsigned char *pIsMin)
{
    Endpoint_801E9F70 *pEndpoint = &mpEndpoints[endpoint];

    *pIsMin = pEndpoint->mIsMax == 0;
    return mpObjects[pEndpoint->mObject].mpBox->mCorner[pEndpoint->mIsMax][axis];
}

void Class_801E9F70::fn_801EA708(unsigned short a, unsigned short b, unsigned short axis)
{
    unsigned short bit = 1 << axis;
    Box_801E9F70 *pBoxA;
    Box_801E9F70 *pBoxB;
    Overlap_801E9F70 *pOverlap;
    float minA;
    float maxA;
    float minB;
    float maxB;
    unsigned int index = fn_801EA668(a, b);

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
        if (pOverlap->mPair == NONE_801E9F70) {
            fn_801EA818(a, b, pOverlap);
        }
    } else if (pOverlap->mPair != NONE_801E9F70) {
        fn_801EA8A0(pOverlap->mPair);
        pOverlap->mPair = NONE_801E9F70;
    }
}

void Class_801E9F70::fn_801EA818(unsigned short a, unsigned short b, Overlap_801E9F70 *pOverlap)
{
    Pair_801E9F70 *pPair = fn_801EAC98();

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

void Class_801E9F70::fn_801EA8A0(unsigned short pair)
{
    Pair_801E9F70 *pPair = &mpPairs[pair];

    if (pPair->mpNext) {
        pPair->mpNext->mpPrev = pPair->mpPrev;
    }
    if (pPair->mpPrev) {
        pPair->mpPrev->mpNext = pPair->mpNext;
    }
    if (mpFirstPair == pPair) {
        mpFirstPair = pPair->mpNext;
    }
    fn_801EACF0(pPair);
}

void Class_801E9F70::fn_801EA908(int axis, unsigned short object)
{
    unsigned short endpoint = mAxisHead[axis];
    unsigned short minEndpoint;
    unsigned short maxEndpoint;
    Endpoint_801E9F70 *pEndpoint;

    while (endpoint != NONE_801E9F70) {
        pEndpoint = &mpEndpoints[endpoint];
        if ((mpObjects[object].mMask & mpObjects[pEndpoint->mObject].mMask) == 0 &&
            pEndpoint->mIsMax == 0) {
            fn_801EA708(object, pEndpoint->mObject, axis);
        }
        endpoint = pEndpoint->mNext;
    }
    minEndpoint = fn_801EAD00();
    maxEndpoint = fn_801EAD00();
    mpEndpoints[minEndpoint].mObject = object;
    mpEndpoints[minEndpoint].mIsMax = 0;
    mpEndpoints[minEndpoint].mNext = NONE_801E9F70;
    mpEndpoints[minEndpoint].mPrev = NONE_801E9F70;
    mpEndpoints[maxEndpoint].mObject = object;
    mpEndpoints[maxEndpoint].mIsMax = 1;
    mpEndpoints[maxEndpoint].mNext = NONE_801E9F70;
    mpEndpoints[maxEndpoint].mPrev = NONE_801E9F70;
    fn_801EAB60(axis, minEndpoint);
    fn_801EAB60(axis, maxEndpoint);
}

void Class_801E9F70::fn_801EAA5C(int axis, unsigned short object)
{
    unsigned short endpoint = mAxisHead[axis];
    unsigned short next;

    while (endpoint != NONE_801E9F70) {
        next = mpEndpoints[endpoint].mNext;
        if (mpEndpoints[endpoint].mObject == object) {
            if (next != NONE_801E9F70) {
                mpEndpoints[next].mPrev = mpEndpoints[endpoint].mPrev;
            }
            if (mpEndpoints[endpoint].mPrev != NONE_801E9F70) {
                mpEndpoints[mpEndpoints[endpoint].mPrev].mNext = mpEndpoints[endpoint].mNext;
            }
            if (mAxisHead[axis] == endpoint) {
                mAxisHead[axis] = mpEndpoints[endpoint].mNext;
            }
            mpEndpoints[endpoint].mNext = NONE_801E9F70;
            mpEndpoints[endpoint].mPrev = NONE_801E9F70;
            fn_801EAD50(endpoint);
        }
        endpoint = next;
    }
}

void Class_801E9F70::fn_801EAB60(int axis, unsigned short endpoint)
{
    Endpoint_801E9F70 *pEndpoint = &mpEndpoints[endpoint];
    Endpoint_801E9F70 *pCurrent;
    unsigned char isMin = pEndpoint->mIsMax == 0;
    float value = mpObjects[pEndpoint->mObject].mpBox->mCorner[pEndpoint->mIsMax][axis];
    unsigned short current = mAxisHead[axis];
    unsigned short next;
    float currentValue;

    if (current == NONE_801E9F70) {
        mAxisHead[axis] = endpoint;
        pEndpoint->mPrev = current;
        pEndpoint->mNext = current;
        return;
    }
    for (;;) {
        pCurrent = &mpEndpoints[current];
        next = pCurrent->mNext;
        currentValue = mpObjects[pCurrent->mObject].mpBox->mCorner[pCurrent->mIsMax][axis];
        if ((isMin && value == currentValue) || value < currentValue) {
            if (pCurrent->mPrev != NONE_801E9F70) {
                mpEndpoints[pCurrent->mPrev].mNext = endpoint;
            } else {
                mAxisHead[axis] = endpoint;
            }
            pEndpoint->mNext = current;
            pEndpoint->mPrev = pCurrent->mPrev;
            pCurrent->mPrev = endpoint;
            return;
        }
        if (next == NONE_801E9F70) {
            pEndpoint->mNext = next;
            pEndpoint->mPrev = current;
            mpEndpoints[current].mNext = endpoint;
            return;
        }
        current = next;
    }
}

Pair_801E9F70 *Class_801E9F70::fn_801EAC98()
{
    Pair_801E9F70 *pPair = mpFreePair;

    if (pPair == 0) {
        return 0;
    }
    mpFreePair = pPair->mpNext;
    fn_801C1F94(pPair, 0, sizeof(Pair_801E9F70));
    return pPair;
}

void Class_801E9F70::fn_801EACF0(Pair_801E9F70 *pPair)
{
    pPair->mpNext = mpFreePair;
    mpFreePair = pPair;
}

unsigned short Class_801E9F70::fn_801EAD00()
{
    unsigned short endpoint = mFreeEndpoint;

    mFreeEndpoint = mpEndpoints[endpoint].mNext;
    fn_801C1F94(&mpEndpoints[endpoint], 0, sizeof(Endpoint_801E9F70));
    return endpoint;
}

void Class_801E9F70::fn_801EAD50(unsigned short endpoint)
{
    mpEndpoints[endpoint].mNext = mFreeEndpoint;
    mFreeEndpoint = endpoint;
}

unsigned short Class_801E9F70::fn_801EAD6C()
{
    unsigned short object = mFreeObject;

    mFreeObject = mpObjects[object].mNext;
    fn_801C1F94(&mpObjects[object], 0, sizeof(Object_801E9F70));
    return object;
}

void Class_801E9F70::fn_801EADBC(unsigned short object)
{
    mpObjects[object].mNext = mFreeObject;
    mFreeObject = object;
}
