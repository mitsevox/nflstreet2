#ifndef GAME_COLLIDECONTACTS_H
#define GAME_COLLIDECONTACTS_H

struct Record_8003EC04;

/* One contact produced by CollideAddCapsuleContact: a point and the two sub-record indices. */
struct CollideContact {
    float mUnknown0;
    float mUnknown4;
    float mUnknown8;
    unsigned char mUnknownC;
    unsigned char mUnknownD;
    char mUnknownE[2];
};

/* Contact list at 0x8030BD74: CollideContactsBegin sets the capacity and storage, CollideAddCapsuleContact appends. */
struct CollideContactList {
    int mCount;
    int mCapacity;
    CollideContact *mpContacts;
};

/* Plane built by CollideMakeSplitPlane from two records: a point and a normal, as read by CollideCapsuleInFront. */
struct CollidePlane {
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
int CollideTestCylinders(Record_8003EC04 *pA, Record_8003EC04 *pB);
int CollideTestSpheres(float *pSphereA, float *pSphereB);
void CollideMakeSplitPlane(CollidePlane *pPlane, Record_8003EC04 *pA, Record_8003EC04 *pB);
int CollideCapsuleInFront(CollidePlane *pPlane, float *pCapsule);
void CollideContactsBegin(CollideContact *pContacts, int capacity);
CollideContactList *CollideGetContacts(void);
void CollideContactsEnd(void);
void CollideContactsStub0(void);
void CollideContactsStub1(void);
void CollideContactsStub2(void);
}

#endif
