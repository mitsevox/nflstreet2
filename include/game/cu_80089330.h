#ifndef GAME_CU_80089330_H
#define GAME_CU_80089330_H

struct Record_8003EC04;

/* One contact produced by fn_80089330: a point and the two sub-record indices. */
struct Contact_80089330 {
    float mUnknown0;
    float mUnknown4;
    float mUnknown8;
    unsigned char mUnknownC;
    unsigned char mUnknownD;
    char mUnknownE[2];
};

/* Contact list at 0x8030BD74: fn_8008959C sets the capacity and storage, fn_80089330 appends. */
struct ContactList_8030BD74 {
    int mCount;
    int mCapacity;
    Contact_80089330 *mpContacts;
};

/* Plane built by fn_800894B8 from two records: a point and a normal, as read by fn_80089514. */
struct Plane_800894B8 {
    float mUnknown0;
    float mUnknown4;
    float mUnknown8;
    char mUnknownC[4];
    float mUnknown10;
    float mUnknown14;
    float mUnknown18;
};

extern "C" {
void fn_80089330(float *pCapsuleA, float *pCapsuleB, int index);
int fn_800893F0(Record_8003EC04 *pA, Record_8003EC04 *pB);
int fn_80089464(float *pSphereA, float *pSphereB);
void fn_800894B8(Plane_800894B8 *pPlane, Record_8003EC04 *pA, Record_8003EC04 *pB);
int fn_80089514(Plane_800894B8 *pPlane, float *pCapsule);
void fn_8008959C(Contact_80089330 *pContacts, int capacity);
ContactList_8030BD74 *fn_800895B8(void);
void fn_800895C4(void);
void fn_800895E0(void);
void fn_800895E4(void);
void fn_800895E8(void);
}

#endif
