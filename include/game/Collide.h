#ifndef GAME_COLLIDE_H
#define GAME_COLLIDE_H

#include "game/CollideContacts.h"

/* Collision sub-record: centre and radius at +0..+12, capsule endpoints at
   +16..+24 and +32..+40, and capsule radius at +28. */
struct CollideShape_t {
    float mUnknown0;
    float mUnknown4;
    float mUnknown8;
    float mUnknownC;
    float mUnknown10;
    float mUnknown14;
    float mUnknown18;
    float mUnknown1C;
    float mUnknown20;
    float mUnknown24;
    float mUnknown28;
    char mUnknown2C[4];
};

/* 48-byte collision record with two sub-record arrays, which CollideUpdateObject
   swaps before running the type callback registered with CollideRegisterType. */
struct CollideObject_t {
    float mUnknown0;
    float mUnknown4;
    float mUnknown8;
    char mUnknownC[4];
    float mUnknown10;
    float mUnknown14;
    float mUnknown18;
    char mUnknown1C[4];
    CollideShape_t *mpUnknown20;
    CollideShape_t *mpUnknown24;
    int mUnknown28;
    unsigned short mUnknown2C;
    unsigned char mUnknown2E;
    unsigned char mUnknown2F;
};

/* Record pool created by CollideSetCreate: a record array and two sub-record arrays. */
struct CollideSet_t {
    CollideObject_t *mpUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknownC;
    int mUnknown10;
    CollideShape_t *mpUnknown14[2];
};

typedef void (*CollideUpdateFunc)(CollideObject_t *pRecord);
typedef void (*CollidePairFunc)(CollideObject_t *pA, CollideObject_t *pB, CollideContactList_t *pContacts);

extern "C" {
void CollideUpdateObject(CollideObject_t *pRecord);
void CollideMirrorObject(CollideObject_t *pRecord);
void CollideInit(int value);
void CollideShutdown(void);
void CollideRegisterType(unsigned char type, unsigned char count, CollideUpdateFunc pCallback);
void CollideUnregisterType(unsigned char type);
void CollideSetPairCallback(unsigned char a, unsigned char b, CollidePairFunc pCallback);
CollideSet_t *CollideSetCreate(int count, int subCount);
void CollideSetDestroy(CollideSet_t *pSet);
CollideObject_t *CollideSetAddObject(CollideSet_t *pSet, unsigned char type, int value);
void CollideSetUpdate(CollideSet_t *pSet);
void CollideSetTest(CollideSet_t *pA, CollideSet_t *pB);
void CollideTestPair(CollideObject_t *pA, CollideObject_t *pB);
int CollideCompareObjects(CollideObject_t *pA, CollideObject_t *pB, CollideObject_t *pBase);
void CollideSetMirror(CollideSet_t *pSet);
}

#endif
