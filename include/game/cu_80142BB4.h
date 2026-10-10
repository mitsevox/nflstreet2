#ifndef GAME_CU_80142BB4_H
#define GAME_CU_80142BB4_H

#include "game/Object_80039F5C.h"
#include "game/cu_80089330.h"

/* One axis of a collision: an input value, two results written by
   fn_80142BB4/fn_80142BE4, and the weight read as +0xC.
   fn_80142BB4 works on one axis, fn_80142BE4 on a pair. */
struct Axis_80142BB4 {
    float mUnknown0;
    float mUnknown4;
    float mUnknown8;
    float mUnknownC;
};

/* The three-dimensional form of Axis_80142BB4, filled by fn_80142D98,
   fn_80142EA0 and fn_80142FF8. */
struct Body_80142D98 {
    Vector_80039F5C mUnknown0;
    Vector_80039F5C mUnknown12;
    Vector_80039F5C mUnknown24;
    float mUnknown36;
};

/* Two positions compared by fn_80142C5C; fn_801438EC fills them from the
   motion block's +0 and +12 vectors. */
struct Segment_80142C5C {
    Vector_80039F5C mUnknown0;
    Vector_80039F5C mUnknown12;
};

extern "C" {
void fn_80142BB4(Axis_80142BB4 *pAxis, float restitution);
void fn_80142BE4(Axis_80142BB4 *pA, Axis_80142BB4 *pB, float restitution);
int fn_80142C5C(Segment_80142C5C *pA, Segment_80142C5C *pB, unsigned char *pHitA, unsigned char *pHitB);
void fn_80142D98(Body_80142D98 *pBody, Vector_80039F5C *pNormal, float restitution);
void fn_80142EA0(Body_80142D98 *pA, Body_80142D98 *pB, float *pNormal, float restitution);
void fn_80142FF8(Body_80142D98 *pA, Body_80142D98 *pB, Vector_80039F5C *pNormal, float restitution);
void fn_80143150(Vector_80039F5C *pOut, Vector_80039F5C *pNormal, float scale);
void fn_80143220(Object_80039F5C *pA, Object_80039F5C *pB);
void fn_80143360(Object_80039F5C *p, Object_80039F5C *pOther, float *pImpulse);
float fn_80143464(Block_80170374 *pBlock, Vector_80039F5C *pImpulse, Vector_80039F5C *pPoint, Vector_80039F5C *pCentre);
unsigned int fn_80143540(int part);
void fn_8014359C(Block_80170374 *pBlock, int part, int otherPart);
void fn_80143668(Contact_80089330 *pContact, Contact_80143668 *pState, int second);
int fn_80143718(Object_80039F5C *p, Object_80039F5C *pOther);
int fn_8014377C(ContactList_8030BD74 *pContacts, unsigned int partA, unsigned int partB);
void fn_801437FC(Object_80039F5C *pA, Object_80039F5C *pB);
void fn_801438EC(Object_80039F5C *pA, Record_8003EC04 *pRecordA, Object_80039F5C *pB, Record_8003EC04 *pRecordB, ContactList_8030BD74 *pContacts);
void fn_80143D3C(Block_80170374 *pBlock);
void fn_80143DC4(Object_80039F5C *p);
void fn_80143E14(Object_80039F5C *p, Object_80039F5C *pOther);
void fn_80143EBC(Object_80039F5C *p, Object_80039F5C *pOther);
}

#endif
