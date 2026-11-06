#ifndef GAME_COLLIDECONTACTS_H
#define GAME_COLLIDECONTACTS_H

struct CollideObject_t;

/* One contact produced by CollideAddCapsuleContact: a point and the two sub-record indices. */
struct CollideContact_t {
    float mUnknown0;
    float mUnknown4;
    float mUnknown8;
    unsigned char mUnknownC;
    unsigned char mUnknownD;
    char mUnknownE[2];
};

/* The contact list of a player collision test: CollideContactsBegin sets the capacity and
   storage, CollideAddCapsuleContact appends. */
struct CollideContactList_t {
    int mCount;
    int mCapacity;
    CollideContact_t *mpContacts;
};

/* Plane built by CollideMakeSplitPlane from two records: a point and a normal, as read by CollideCapsuleReachesPlane. */
struct CollidePlane_t {
    float mUnknown0;
    float mUnknown4;
    float mUnknown8;
    char mUnknownC[4];
    float mUnknown10;
    float mUnknown14;
    float mUnknown18;
};

extern "C" {
void CollideAddCapsuleContact(float *pCapsuleA, float *pCapsuleB, unsigned int index);
int CollideTestCylinders(CollideObject_t *pA, CollideObject_t *pB);
int CollideTestSpheres(float *pSphereA, float *pSphereB);
void CollideMakeSplitPlane(CollidePlane_t *pPlane, CollideObject_t *pA, CollideObject_t *pB);
int CollideCapsuleReachesPlane(CollidePlane_t *pPlane, float *pCapsule);
void CollideContactsBegin(CollideContact_t *pContacts, int capacity);
CollideContactList_t *CollideGetContacts(void);
void CollideContactsEnd(void);
void CollideContactsStub0(void);
void CollideContactsStub1(void);
void CollideContactsStub2(void);
}

#endif
