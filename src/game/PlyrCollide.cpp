/* Player against player collisions: bounces two colliding players off each
   other (from their motion blocks or from a contact list), records the
   impulses and contact parts in each player's collision block, and keeps the
   two-entry list of players a player does not collide with. */
#include "game/PlyrCollide.h"
#include "game/fn_802270D4.h"
#include "game/fn_80227638.h"

extern float gPlyrMoveFwdSpeed;

extern "C" {
int fn_801CFE40(float y, float x);
void MatRotVecToVec(Vector_80039F5C *pFrom, Vector_80039F5C *pTo);
void fn_801D0470(int mode);
void fn_801D0494(void);
void fn_801D0E94(void);
void fn_802271F0(void *pOut, void *pIn);
void fn_80227248(void *pOut, void *pIn, float scale);
void fn_80227264(void *pOut, void *pIn, float scale);
void fn_802272DC(void *pOut, void *pIn, float length);
void fn_80227384(void *pOut, void *pIn, int angle);
void fn_8022765C(void *pOut, void *pA, void *pB);
void fn_80227690(void *pOut, void *pA, void *pB);
float fn_80227704(void *pA, void *pB);
void fn_802277DC(void *pOut, void *pA, void *pB);
void fn_80227C2C(void *pOut, void *pIn);
float fn_80237260(int stream);
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
int fn_800B2C48(Object_800B26B0 *pA, Object_800B26B0 *pB, int angle, unsigned char *pHitA, unsigned char *pHitB);
}

extern "C" {

void PlyrCollideResolve2D(Object_80039F5C *pA, Object_80039F5C *pB)
{
    BounceBody_t bodyA;
    BounceBody_t bodyB;
    float normal[2];

    fn_80227690(normal, &pA->mMotion.mPos, &pB->mMotion.mPos);
    bodyA.mUnknown0.mX = pA->mMotion.mUnknown40;
    bodyA.mUnknown0.mY = pA->mMotion.mUnknown44;
    bodyB.mUnknown0.mX = pB->mMotion.mUnknown40;
    bodyB.mUnknown0.mY = pB->mMotion.mUnknown44;
    bodyA.mUnknown36 = pA->mUnknown508;
    bodyB.mUnknown36 = pB->mUnknown508;
    BounceBodyPair2D(&bodyA, &bodyB, normal, 0.5f);
    if (!(pA->mFlags & 8) && !PlyrCollideIsExempt(pA, pB)) {
        pA->mMotion.mUnknown40 = bodyA.mUnknown12.mX;
        pA->mMotion.mUnknown44 = bodyA.mUnknown12.mY;
        pA->mMotion.mUnknown28 = fn_802270A4(&bodyA.mUnknown12);
        pA->mMotion.mUnknown32 = fn_801CFE40(bodyA.mUnknown12.mY, bodyA.mUnknown12.mX);
    }
    if (!(pB->mFlags & 8) && !PlyrCollideIsExempt(pB, pA)) {
        pB->mMotion.mUnknown40 = bodyB.mUnknown12.mX;
        pB->mMotion.mUnknown44 = bodyB.mUnknown12.mY;
        pB->mMotion.mUnknown28 = fn_802270A4(&bodyB.mUnknown12);
        pB->mMotion.mUnknown32 = fn_801CFE40(bodyB.mUnknown12.mY, bodyB.mUnknown12.mX);
    }
    PlyrCollideRecordImpulse(pA, pB, &bodyA.mUnknown24.mX);
    PlyrCollideRecordImpulse(pB, pA, &bodyB.mUnknown24.mX);
}

void PlyrCollideRecordImpulse(Object_80039F5C *p, Object_80039F5C *pOther, float *pImpulse)
{
    Vector_80039F5C impulse;
    Vector_80039F5C zero;
    Block_80170374 *pBlock;
    int sameTeam;
    float force;

    sameTeam = p->mIdBytes[2] == pOther->mIdBytes[2];
    pBlock = &p->mUnknown560;
    impulse.mX = pImpulse[0];
    impulse.mY = pImpulse[1];
    impulse.mZ = 0.0f;
    zero.mX = 0.0f;
    zero.mY = 0.0f;
    zero.mZ = 0.0f;
    force = PlyrCollideAddImpulse(pBlock, &impulse, &zero, &zero);
    if (p->mIdBytes[3] == 1 && pOther->mIdBytes[3] == 1) {
        if (sameTeam) {
            fn_8009BD2C(pOther, &pBlock->mUnknown44);
            pBlock->mUnknown52++;
        } else {
            if (force == pBlock->mUnknown28 || !fn_8009BCE8(&pBlock->mUnknown40)) {
                fn_8009BD2C(pOther, &pBlock->mUnknown40);
                fn_8009BD2C(pOther, &pBlock->mUnknown48);
            }
            pBlock->mUnknown53++;
        }
    }
}

float PlyrCollideAddImpulse(Block_80170374 *pBlock, Vector_80039F5C *pImpulse, Vector_80039F5C *pPoint, Vector_80039F5C *pCentre)
{
    Vector_80039F5C arm;
    Vector_80039F5C torque;
    float force;
    float limit;

    pBlock->mFlags.mBytes[0] = 1;
    fn_8022765C(&pBlock->mUnknown4, &pBlock->mUnknown4, pImpulse);
    fn_802276B4(&arm, pPoint, pCentre);
    fn_802277DC(&torque, &arm, pImpulse);
    fn_8022765C(&pBlock->mUnknown16, &pBlock->mUnknown16, &torque);
    force = fn_802270D4(pImpulse);
    limit = gPlyrMoveFwdSpeed * 100621.117f;
    if (force > limit) {
        force = limit;
    }
    if (force > pBlock->mUnknown28) {
        pBlock->mUnknown28 = force;
    }
    pBlock->mUnknown32 += force;
    pBlock->mUnknown36 += force;
    return force;
}

void CollideWithPoint(Object_80039F5C *p, float *pPoint)
{
    BounceBody_t body = { 0 };
    float normal[2];
    Vector_80039F5C zero;

    fn_80227690(normal, &p->mMotion.mPos, pPoint);
    body.mUnknown0.mX = p->mMotion.mUnknown40;
    body.mUnknown0.mY = p->mMotion.mUnknown44;
    body.mUnknown36 = p->mUnknown508;
    BounceBody2D(&body, normal, 0.5f);
    p->mMotion.mUnknown40 = body.mUnknown12.mX;
    p->mMotion.mUnknown44 = body.mUnknown12.mY;
    p->mMotion.mUnknown28 = fn_802270A4(&body.mUnknown12);
    p->mMotion.mUnknown32 = fn_801CFE40(body.mUnknown12.mY, body.mUnknown12.mX);
    zero.mX = 0.0f;
    zero.mY = 0.0f;
    zero.mZ = 0.0f;
    PlyrCollideAddImpulse(&p->mUnknown560, &body.mUnknown24, &zero, &zero);
}

unsigned int PlyrCollidePartWeight(int part)
{
    switch (part) {
    case 0:
        return 4;
    case 5:
    case 6:
    case 7:
    case 8:
        return 3;
    case 1:
    case 2:
    case 3:
    case 4:
    case 9:
    case 10:
        return 1;
    case 11:
        return 0;
    }
    return 0;
}

void PlyrCollideSetPartFlags(Block_80170374 *pBlock, int part, int otherPart)
{
    switch (otherPart) {
    case 2:
    case 4:
    case 9:
    case 10:
        switch (part) {
        case 1:
            pBlock->mFlags.mBytes[1] |= 0x10;
            break;
        case 3:
            pBlock->mFlags.mBytes[1] |= 0x20;
            break;
        case 2:
            pBlock->mFlags.mBytes[1] |= 1;
            break;
        case 4:
            pBlock->mFlags.mBytes[1] |= 2;
            break;
        case 10:
            pBlock->mFlags.mBytes[1] |= 4;
            break;
        case 9:
            pBlock->mFlags.mBytes[1] |= 8;
            break;
        }
        break;
    }
}

void PlyrCollideRecordContact(CollideContact_t *pContact, PlyrCollideState_t *pState, int second)
{
    unsigned char part;
    unsigned char otherPart;
    unsigned int current;
    unsigned int score;

    if (second) {
        otherPart = pContact->mUnknownC;
        part = pContact->mUnknownD;
    } else {
        part = pContact->mUnknownC;
        otherPart = pContact->mUnknownD;
    }
    current = PlyrCollidePartWeight(pState->mBlock.mUnknown54) + PlyrCollidePartWeight(pState->mBlock.mUnknown55);
    score = PlyrCollidePartWeight(part) + PlyrCollidePartWeight(otherPart);
    PlyrCollideSetPartFlags(&pState->mBlock, part, otherPart);
    if (score > current) {
        pState->mBlock.mUnknown54 = part;
        pState->mBlock.mUnknown55 = otherPart;
        pState->mUnknown56.mX = pContact->mUnknown0;
        pState->mUnknown56.mY = pContact->mUnknown4;
        pState->mUnknown56.mZ = pContact->mUnknown8;
    }
}

int PlyrCollideIsExempt(Object_80039F5C *p, Object_80039F5C *pOther)
{
    int *pRefs = p->mUnknown628;
    int ref;
    unsigned int i;

    fn_8009BD2C(pOther, &ref);
    for (i = 0; i < 2; i++) {
        if (pRefs[i] == ref) {
            return 1;
        }
    }
    return 0;
}

int PlyrCollideIsLightContact(CollideContactList_t *pContacts, unsigned int partA, unsigned int partB)
{
    int result = 0;

    if (pContacts->mCount == 1) {
        switch (partA) {
        case 2:
        case 4:
        case 6:
        case 8:
        case 9:
        case 10:
            switch (partB) {
            case 2:
            case 4:
            case 6:
            case 8:
            case 9:
            case 10:
                result = 1;
                break;
            }
            break;
        }
    }
    return result;
}

void PlyrCollideMotion(Object_80039F5C *pA, Object_80039F5C *pB)
{
    unsigned char hitA;
    unsigned char hitB;

    if (fn_800B2C48(&pA->mMotion, &pB->mMotion, 0x800000, &hitA, &hitB)) {
        if (hitA && !(pA->mFlags & 8) && !PlyrCollideIsExempt(pA, pB)) {
            pA->mMotion.mPos = pA->mMotion.mUnknown12;
        }
        if (hitB && !(pB->mFlags & 8) && !PlyrCollideIsExempt(pB, pA)) {
            pB->mMotion.mPos = pB->mMotion.mUnknown12;
        }
        PlyrCollideResolve2D(pA, pB);
    }
}

void PlyrCollideContacts(Object_80039F5C *pA, CollideObject_t *pRecordA, Object_80039F5C *pB, CollideObject_t *pRecordB, CollideContactList_t *pContacts)
{
    BounceBody_t bodyA;
    BounceBody_t bodyB;
    BounceSegment_t segA;
    BounceSegment_t segB;
    Vector_80039F5C normal;
    unsigned char hitA;
    unsigned char hitB;
    float totalA[2];
    float totalB[2];
    float deltaA[2];
    float deltaB[2];
    CollideContact_t *pContact;
    float restitution;
    int i;

    totalA[0] = totalA[1] = 0.0f;
    totalB[0] = totalB[1] = 0.0f;
    restitution = 0.5f;
    pContact = pContacts->mpContacts;
    for (i = pContacts->mCount; i != 0; i--, pContact++) {
        segA.mUnknown0.mX = pA->mMotion.mPos.mX;
        segA.mUnknown0.mY = pA->mMotion.mPos.mY;
        segA.mUnknown0.mZ = pA->mMotion.mPos.mZ;
        segA.mUnknown12.mX = pA->mMotion.mUnknown12.mX;
        segA.mUnknown12.mY = pA->mMotion.mUnknown12.mY;
        segA.mUnknown12.mZ = pA->mMotion.mUnknown12.mZ;
        segB.mUnknown0.mX = pB->mMotion.mPos.mX;
        segB.mUnknown0.mY = pB->mMotion.mPos.mY;
        segB.mUnknown0.mZ = pB->mMotion.mPos.mZ;
        segB.mUnknown12.mX = pB->mMotion.mUnknown12.mX;
        segB.mUnknown12.mY = pB->mMotion.mUnknown12.mY;
        segB.mUnknown12.mZ = pB->mMotion.mUnknown12.mZ;
        if (!BounceCheckApproach(&segA, &segB, &hitA, &hitB)) {
            continue;
        }
        fn_802276B4(&bodyA.mUnknown0, &segA.mUnknown0, &segA.mUnknown12);
        fn_8022765C(&bodyA.mUnknown0, &bodyA.mUnknown0, &pA->mMotion.mUnknown40);
        fn_8022765C(&bodyA.mUnknown0, &bodyA.mUnknown0, &segA.mUnknown12);
        fn_802276B4(&bodyA.mUnknown0, &bodyA.mUnknown0, &segA.mUnknown0);
        fn_802276B4(&bodyB.mUnknown0, &segB.mUnknown0, &segB.mUnknown12);
        fn_8022765C(&bodyB.mUnknown0, &bodyB.mUnknown0, &pB->mMotion.mUnknown40);
        fn_8022765C(&bodyB.mUnknown0, &bodyB.mUnknown0, &segB.mUnknown12);
        fn_802276B4(&bodyB.mUnknown0, &bodyB.mUnknown0, &segB.mUnknown0);
        fn_802276B4(&normal, &segA.mUnknown12, &segB.mUnknown12);
        bodyA.mUnknown36 = pA->mUnknown508 / pContacts->mCount;
        bodyB.mUnknown36 = pB->mUnknown508 / pContacts->mCount;
        if (PlyrCollideIsLightContact(pContacts, pContact->mUnknownC, pContact->mUnknownD)) {
            bodyA.mUnknown36 *= 0.35f;
            bodyB.mUnknown36 *= 0.35f;
        }
        BounceBodyPair3D(&bodyA, &bodyB, &normal, restitution);
        fn_80227248(deltaA, &bodyA.mUnknown24, 1.0f / (pA->mUnknown508 * 335.40372f));
        fn_80227248(deltaB, &bodyB.mUnknown24, 1.0f / (pB->mUnknown508 * 335.40372f));
        if (!(pA->mFlags & 8) && !PlyrCollideIsExempt(pA, pB)) {
            fn_80227638(&pA->mMotion.mUnknown40, &pA->mMotion.mUnknown40, deltaA);
            pA->mMotion.mUnknown28 = fn_802270A4(&pA->mMotion.mUnknown40);
            pA->mMotion.mUnknown32 = fn_801CFE40(pA->mMotion.mUnknown44, pA->mMotion.mUnknown40);
        }
        if (!(pB->mFlags & 8) && !PlyrCollideIsExempt(pB, pA)) {
            fn_80227638(&pB->mMotion.mUnknown40, &pB->mMotion.mUnknown40, deltaB);
            pB->mMotion.mUnknown28 = fn_802270A4(&pB->mMotion.mUnknown40);
            pB->mMotion.mUnknown32 = fn_801CFE40(pB->mMotion.mUnknown44, pB->mMotion.mUnknown40);
        }
        fn_80227638(totalA, totalA, &bodyA.mUnknown24);
        fn_80227638(totalB, totalB, &bodyB.mUnknown24);
        PlyrCollideRecordContact(pContact, &pA->mContact560, 0);
        PlyrCollideRecordContact(pContact, &pB->mContact560, 1);
        if (pContact->mUnknownC == 0 || pContact->mUnknownD == 0) {
            if (hitA && !(pA->mFlags & 8) && !PlyrCollideIsExempt(pA, pB)) {
                pA->mMotion.mPos = pA->mMotion.mUnknown12;
            }
            if (hitB && !(pB->mFlags & 8) && !PlyrCollideIsExempt(pB, pA)) {
                pB->mMotion.mPos = pB->mMotion.mUnknown12;
            }
        }
    }
    PlyrCollideRecordImpulse(pA, pB, totalA);
    PlyrCollideRecordImpulse(pB, pA, totalB);
}

void PlyrCollideResetBlock(Block_80170374 *pBlock)
{
    pBlock->mFlags.mBytes[0] = 0;
    pBlock->mUnknown4.mX = 0.0f;
    pBlock->mUnknown4.mY = 0.0f;
    pBlock->mUnknown4.mZ = 0.0f;
    pBlock->mUnknown16.mX = 0.0f;
    pBlock->mUnknown16.mY = 0.0f;
    pBlock->mUnknown16.mZ = 0.0f;
    pBlock->mUnknown28 = 0.0f;
    pBlock->mUnknown32 = 0.0f;
    fn_8009BD2C(0, &pBlock->mUnknown40);
    fn_8009BD2C(0, &pBlock->mUnknown44);
    pBlock->mUnknown52 = 0;
    pBlock->mUnknown53 = 0;
    pBlock->mUnknown54 = 11;
    pBlock->mFlags.mBytes[1] = 0;
    pBlock->mUnknown55 = 11;
}

void PlyrCollideClearExempt(Object_80039F5C *p)
{
    int *pRefs = p->mUnknown628;
    int ref;
    unsigned int i;

    fn_8009BD2C(0, &ref);
    for (i = 0; i < 2; i++) {
        pRefs[i] = ref;
    }
}

void PlyrCollideAddExempt(Object_80039F5C *p, Object_80039F5C *pOther)
{
    int *pRefs = p->mUnknown628;
    int ref;
    int none;
    unsigned int i;

    fn_8009BD2C(pOther, &ref);
    fn_8009BD2C(0, &none);
    for (i = 0; i < 2; i++) {
        if (pRefs[i] == none) {
            break;
        }
        if (pRefs[i] == ref) {
            i = 2;
            break;
        }
    }
    if (i < 2) {
        pRefs[i] = ref;
    }
}

void PlyrCollideRemoveExempt(Object_80039F5C *p, Object_80039F5C *pOther)
{
    int *pRefs = p->mUnknown628;
    int ref;
    unsigned int i;

    fn_8009BD2C(pOther, &ref);
    for (i = 0; i < 2; i++) {
        if (pRefs[i] == ref) {
            break;
        }
    }
    if (i < 2) {
        fn_8009BD2C(0, &pRefs[i]);
    }
}

}
