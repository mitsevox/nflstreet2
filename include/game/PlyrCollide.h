#ifndef GAME_PLYRCOLLIDE_H
#define GAME_PLYRCOLLIDE_H

#include "game/CollideBounce.h"
#include "game/CollideContacts.h"

extern "C" {
void PlyrCollideResolve2D(Object_80039F5C *pA, Object_80039F5C *pB);
void PlyrCollideRecordImpulse(Object_80039F5C *p, Object_80039F5C *pOther, float *pImpulse);
float PlyrCollideAddImpulse(Block_80170374 *pBlock, Vector_80039F5C *pImpulse, Vector_80039F5C *pPoint, Vector_80039F5C *pCentre);
unsigned int PlyrCollidePartWeight(int part);
void PlyrCollideSetPartFlags(Block_80170374 *pBlock, int part, int otherPart);
void PlyrCollideRecordContact(CollideContact_t *pContact, PlyrCollideState_t *pState, int second);
int PlyrCollideIsExempt(Object_80039F5C *p, Object_80039F5C *pOther);
int PlyrCollideIsLightContact(CollideContactList_t *pContacts, unsigned int partA, unsigned int partB);
void PlyrCollideMotion(Object_80039F5C *pA, Object_80039F5C *pB);
void PlyrCollideContacts(Object_80039F5C *pA, CollideObject_t *pRecordA, Object_80039F5C *pB, CollideObject_t *pRecordB, CollideContactList_t *pContacts);
void PlyrCollideResetBlock(Block_80170374 *pBlock);
void PlyrCollideClearExempt(Object_80039F5C *p);
void PlyrCollideAddExempt(Object_80039F5C *p, Object_80039F5C *pOther);
void PlyrCollideRemoveExempt(Object_80039F5C *p, Object_80039F5C *pOther);
}

#endif
