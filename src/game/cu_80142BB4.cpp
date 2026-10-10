#include "game/cu_80142BB4.h"
#include "game/fn_802270D4.h"
#include "game/fn_80227638.h"

extern float lbl_803ECB08;

extern "C" {
int fn_801CFE40(float y, float x);
void fn_801D0370(Vector_80039F5C *pFrom, Vector_80039F5C *pTo);
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

void fn_80142BB4(Axis_80142BB4 *pAxis, float restitution)
{
    float delta;

    pAxis->mUnknown4 = -pAxis->mUnknown0 * restitution;
    delta = (pAxis->mUnknown4 - pAxis->mUnknown0) * 335.40372f;
    pAxis->mUnknown8 = pAxis->mUnknownC * delta;
}

void fn_80142BE4(Axis_80142BB4 *pA, Axis_80142BB4 *pB, float restitution)
{
    float ratio = pA->mUnknownC / pB->mUnknownC;
    float a = pA->mUnknown0;
    float b = pB->mUnknown0;
    float outA;
    float outB;
    float deltaA;
    float deltaB;

    outA = (a * (ratio - restitution) + b * (restitution + 1.0f)) / (ratio + 1.0f);
    pA->mUnknown4 = outA;
    outB = restitution * (a - b) + outA;
    pB->mUnknown4 = outB;
    deltaA = (outA - a) * 335.40372f;
    pA->mUnknown8 = pA->mUnknownC * deltaA;
    deltaB = (outB - b) * 335.40372f;
    pB->mUnknown8 = pB->mUnknownC * deltaB;
}

int fn_80142C5C(Segment_80142C5C *pA, Segment_80142C5C *pB, unsigned char *pHitA, unsigned char *pHitB)
{
    Vector_80039F5C offset;
    Vector_80039F5C move;
    Vector_80039F5C otherMove;

    fn_802276B4(&offset, &pA->mUnknown12, &pB->mUnknown12);
    fn_802276B4(&move, &pA->mUnknown0, &pA->mUnknown12);
    *pHitA = 0;
    if (move.mX != 0.0f || move.mY != 0.0f) {
        if (fn_80227704(&move, &offset) < 0.0f) {
            *pHitA = 1;
        }
    }
    fn_80227264(&offset, &offset, -1.0f);
    fn_802276B4(&otherMove, &pB->mUnknown0, &pB->mUnknown12);
    *pHitB = 0;
    if (otherMove.mX != 0.0f || otherMove.mY != 0.0f) {
        if (fn_80227704(&otherMove, &offset) < 0.0f) {
            *pHitB = 1;
        }
    }
    return *pHitA || *pHitB;
}

static inline int Heading(float *v)
{
    return fn_801CFE40(v[1], v[0]);
}

void BounceBody2D(Body_80142D98 *pBody, float *pNormal, float restitution)
{
    Axis_80142BB4 axis;
    float up[2];
    int angle;

    up[0] = 0.0f;
    up[1] = 1.0f;
    angle = Heading(pNormal);
    angle = (Heading(up) - angle) & 0xFFFFFF;
    fn_80227384(&pBody->mUnknown0, &pBody->mUnknown0, angle);
    pBody->mUnknown12.mX = pBody->mUnknown0.mX;
    pBody->mUnknown24.mX = 0.0f;
    axis.mUnknownC = pBody->mUnknown36;
    axis.mUnknown0 = pBody->mUnknown0.mY;
    fn_80142BB4(&axis, restitution);
    pBody->mUnknown12.mY = axis.mUnknown4;
    pBody->mUnknown24.mY = axis.mUnknown8;
    angle = -angle & 0xFFFFFF;
    fn_80227384(&pBody->mUnknown12, &pBody->mUnknown12, angle);
    fn_80227384(&pBody->mUnknown24, &pBody->mUnknown24, angle);
}

void fn_80142D98(Body_80142D98 *pBody, Vector_80039F5C *pNormal, float restitution)
{
    Vector_80039F5C up;
    Axis_80142BB4 axis;

    axis.mUnknown8 = 0.0f;
    up.mX = 0.0f;
    up.mY = 0.0f;
    up.mZ = 1.0f;
    fn_801D0470(3);
    fn_801D0494();
    fn_801D0370(pNormal, &up);
    fn_80227C2C(&pBody->mUnknown0, &pBody->mUnknown0);
    pBody->mUnknown12.mX = pBody->mUnknown0.mX * 0.5f;
    pBody->mUnknown12.mY = pBody->mUnknown0.mY * 0.5f;
    pBody->mUnknown24.mX = 0.0f;
    pBody->mUnknown24.mY = 0.0f;
    axis.mUnknown0 = pBody->mUnknown0.mZ;
    axis.mUnknownC = pBody->mUnknown36;
    if (axis.mUnknown0 > 0.0f) {
        axis.mUnknown4 = axis.mUnknown0;
    } else {
        fn_80142BB4(&axis, restitution);
    }
    pBody->mUnknown12.mZ = axis.mUnknown4;
    pBody->mUnknown24.mZ = axis.mUnknown8;
    fn_801D0E94();
    fn_80227C2C(&pBody->mUnknown12, &pBody->mUnknown12);
    fn_80227C2C(&pBody->mUnknown24, &pBody->mUnknown24);
}

void fn_80142EA0(Body_80142D98 *pA, Body_80142D98 *pB, float *pNormal, float restitution)
{
    Axis_80142BB4 axisA;
    Axis_80142BB4 axisB;
    float up[2];
    int angle;

    up[0] = 0.0f;
    up[1] = 1.0f;
    angle = Heading(pNormal);
    angle = (Heading(up) - angle) & 0xFFFFFF;
    fn_80227384(&pA->mUnknown0, &pA->mUnknown0, angle);
    fn_80227384(&pB->mUnknown0, &pB->mUnknown0, angle);
    pA->mUnknown12.mX = pA->mUnknown0.mX;
    pA->mUnknown24.mX = 0.0f;
    pB->mUnknown12.mX = pB->mUnknown0.mX;
    pB->mUnknown24.mX = 0.0f;
    axisA.mUnknownC = pA->mUnknown36;
    axisA.mUnknown0 = pA->mUnknown0.mY;
    axisB.mUnknownC = pB->mUnknown36;
    axisB.mUnknown0 = pB->mUnknown0.mY;
    fn_80142BE4(&axisA, &axisB, restitution);
    pA->mUnknown12.mY = axisA.mUnknown4;
    pA->mUnknown24.mY = axisA.mUnknown8;
    pB->mUnknown12.mY = axisB.mUnknown4;
    pB->mUnknown24.mY = axisB.mUnknown8;
    angle = -angle & 0xFFFFFF;
    fn_80227384(&pA->mUnknown12, &pA->mUnknown12, angle);
    fn_80227384(&pA->mUnknown24, &pA->mUnknown24, angle);
    fn_80227384(&pB->mUnknown12, &pB->mUnknown12, angle);
    fn_80227384(&pB->mUnknown24, &pB->mUnknown24, angle);
}

void fn_80142FF8(Body_80142D98 *pA, Body_80142D98 *pB, Vector_80039F5C *pNormal, float restitution)
{
    Vector_80039F5C up;
    Axis_80142BB4 axisA;
    Axis_80142BB4 axisB;

    up.mX = 0.0f;
    up.mY = 0.0f;
    up.mZ = 1.0f;
    fn_802271F0(pNormal, pNormal);
    fn_801D0470(3);
    fn_801D0494();
    fn_801D0370(pNormal, &up);
    fn_80227C2C(&pA->mUnknown0, &pA->mUnknown0);
    fn_80227C2C(&pB->mUnknown0, &pB->mUnknown0);
    pA->mUnknown12.mX = pA->mUnknown0.mX;
    pA->mUnknown24.mX = 0.0f;
    pB->mUnknown12.mX = pB->mUnknown0.mX;
    pB->mUnknown24.mX = 0.0f;
    pA->mUnknown12.mY = pA->mUnknown0.mY;
    pA->mUnknown24.mY = 0.0f;
    pB->mUnknown12.mY = pB->mUnknown0.mY;
    pB->mUnknown24.mY = 0.0f;
    axisA.mUnknownC = pA->mUnknown36;
    axisA.mUnknown0 = pA->mUnknown0.mZ;
    axisB.mUnknownC = pB->mUnknown36;
    axisB.mUnknown0 = pB->mUnknown0.mZ;
    fn_80142BE4(&axisA, &axisB, restitution);
    pA->mUnknown12.mZ = axisA.mUnknown4;
    pA->mUnknown24.mZ = axisA.mUnknown8;
    pB->mUnknown12.mZ = axisB.mUnknown4;
    pB->mUnknown24.mZ = axisB.mUnknown8;
    fn_801D0E94();
    fn_80227C2C(&pA->mUnknown12, &pA->mUnknown12);
    fn_80227C2C(&pA->mUnknown24, &pA->mUnknown24);
    fn_80227C2C(&pB->mUnknown12, &pB->mUnknown12);
    fn_80227C2C(&pB->mUnknown24, &pB->mUnknown24);
}

void fn_80143150(Vector_80039F5C *pOut, Vector_80039F5C *pNormal, float scale)
{
    Vector_80039F5C up;
    Vector_80039F5C v;

    up.mX = 0.0f;
    up.mY = 0.0f;
    up.mZ = 1.0f;
    fn_801D0470(3);
    fn_801D0494();
    fn_801D0370(pNormal, &up);
    v.mX = fn_80237260(0) - 0.5f;
    v.mY = fn_80237260(0) - 0.5f;
    v.mZ = fn_80237260(0) * 0.5f;
    fn_802272DC(&v, &v, scale);
    fn_801D0E94();
    fn_80227C2C(pOut, &v);
}

void fn_80143220(Object_80039F5C *pA, Object_80039F5C *pB)
{
    Body_80142D98 bodyA;
    Body_80142D98 bodyB;
    float normal[2];

    fn_80227690(normal, &pA->mMotion.mPos, &pB->mMotion.mPos);
    bodyA.mUnknown0.mX = pA->mMotion.mUnknown40;
    bodyA.mUnknown0.mY = pA->mMotion.mUnknown44;
    bodyB.mUnknown0.mX = pB->mMotion.mUnknown40;
    bodyB.mUnknown0.mY = pB->mMotion.mUnknown44;
    bodyA.mUnknown36 = pA->mUnknown508;
    bodyB.mUnknown36 = pB->mUnknown508;
    fn_80142EA0(&bodyA, &bodyB, normal, 0.5f);
    if (!(pA->mFlags & 8) && !fn_80143718(pA, pB)) {
        pA->mMotion.mUnknown40 = bodyA.mUnknown12.mX;
        pA->mMotion.mUnknown44 = bodyA.mUnknown12.mY;
        pA->mMotion.mUnknown28 = fn_802270A4(&bodyA.mUnknown12);
        pA->mMotion.mUnknown32 = fn_801CFE40(bodyA.mUnknown12.mY, bodyA.mUnknown12.mX);
    }
    if (!(pB->mFlags & 8) && !fn_80143718(pB, pA)) {
        pB->mMotion.mUnknown40 = bodyB.mUnknown12.mX;
        pB->mMotion.mUnknown44 = bodyB.mUnknown12.mY;
        pB->mMotion.mUnknown28 = fn_802270A4(&bodyB.mUnknown12);
        pB->mMotion.mUnknown32 = fn_801CFE40(bodyB.mUnknown12.mY, bodyB.mUnknown12.mX);
    }
    fn_80143360(pA, pB, &bodyA.mUnknown24.mX);
    fn_80143360(pB, pA, &bodyB.mUnknown24.mX);
}

void fn_80143360(Object_80039F5C *p, Object_80039F5C *pOther, float *pImpulse)
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
    force = fn_80143464(pBlock, &impulse, &zero, &zero);
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

float fn_80143464(Block_80170374 *pBlock, Vector_80039F5C *pImpulse, Vector_80039F5C *pPoint, Vector_80039F5C *pCentre)
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
    limit = lbl_803ECB08 * 100621.117f;
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
    Body_80142D98 body = { 0 };
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
    fn_80143464(&p->mUnknown560, &body.mUnknown24, &zero, &zero);
}

unsigned int fn_80143540(int part)
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

void fn_8014359C(Block_80170374 *pBlock, int part, int otherPart)
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

void fn_80143668(Contact_80089330 *pContact, Contact_80143668 *pState, int second)
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
    current = fn_80143540(pState->mBlock.mUnknown54) + fn_80143540(pState->mBlock.mUnknown55);
    score = fn_80143540(part) + fn_80143540(otherPart);
    fn_8014359C(&pState->mBlock, part, otherPart);
    if (score > current) {
        pState->mBlock.mUnknown54 = part;
        pState->mBlock.mUnknown55 = otherPart;
        pState->mUnknown56.mX = pContact->mUnknown0;
        pState->mUnknown56.mY = pContact->mUnknown4;
        pState->mUnknown56.mZ = pContact->mUnknown8;
    }
}

int fn_80143718(Object_80039F5C *p, Object_80039F5C *pOther)
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

int fn_8014377C(ContactList_8030BD74 *pContacts, unsigned int partA, unsigned int partB)
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

void fn_801437FC(Object_80039F5C *pA, Object_80039F5C *pB)
{
    unsigned char hitA;
    unsigned char hitB;

    if (fn_800B2C48(&pA->mMotion, &pB->mMotion, 0x800000, &hitA, &hitB)) {
        if (hitA && !(pA->mFlags & 8) && !fn_80143718(pA, pB)) {
            pA->mMotion.mPos = pA->mMotion.mUnknown12;
        }
        if (hitB && !(pB->mFlags & 8) && !fn_80143718(pB, pA)) {
            pB->mMotion.mPos = pB->mMotion.mUnknown12;
        }
        fn_80143220(pA, pB);
    }
}

void fn_801438EC(Object_80039F5C *pA, Record_8003EC04 *pRecordA, Object_80039F5C *pB, Record_8003EC04 *pRecordB, ContactList_8030BD74 *pContacts)
{
    Body_80142D98 bodyA;
    Body_80142D98 bodyB;
    Segment_80142C5C segA;
    Segment_80142C5C segB;
    Vector_80039F5C normal;
    unsigned char hitA;
    unsigned char hitB;
    float totalA[2];
    float totalB[2];
    float deltaA[2];
    float deltaB[2];
    Contact_80089330 *pContact;
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
        if (!fn_80142C5C(&segA, &segB, &hitA, &hitB)) {
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
        if (fn_8014377C(pContacts, pContact->mUnknownC, pContact->mUnknownD)) {
            bodyA.mUnknown36 *= 0.35f;
            bodyB.mUnknown36 *= 0.35f;
        }
        fn_80142FF8(&bodyA, &bodyB, &normal, restitution);
        fn_80227248(deltaA, &bodyA.mUnknown24, 1.0f / (pA->mUnknown508 * 335.40372f));
        fn_80227248(deltaB, &bodyB.mUnknown24, 1.0f / (pB->mUnknown508 * 335.40372f));
        if (!(pA->mFlags & 8) && !fn_80143718(pA, pB)) {
            fn_80227638(&pA->mMotion.mUnknown40, &pA->mMotion.mUnknown40, deltaA);
            pA->mMotion.mUnknown28 = fn_802270A4(&pA->mMotion.mUnknown40);
            pA->mMotion.mUnknown32 = fn_801CFE40(pA->mMotion.mUnknown44, pA->mMotion.mUnknown40);
        }
        if (!(pB->mFlags & 8) && !fn_80143718(pB, pA)) {
            fn_80227638(&pB->mMotion.mUnknown40, &pB->mMotion.mUnknown40, deltaB);
            pB->mMotion.mUnknown28 = fn_802270A4(&pB->mMotion.mUnknown40);
            pB->mMotion.mUnknown32 = fn_801CFE40(pB->mMotion.mUnknown44, pB->mMotion.mUnknown40);
        }
        fn_80227638(totalA, totalA, &bodyA.mUnknown24);
        fn_80227638(totalB, totalB, &bodyB.mUnknown24);
        fn_80143668(pContact, &pA->mContact560, 0);
        fn_80143668(pContact, &pB->mContact560, 1);
        if (pContact->mUnknownC == 0 || pContact->mUnknownD == 0) {
            if (hitA && !(pA->mFlags & 8) && !fn_80143718(pA, pB)) {
                pA->mMotion.mPos = pA->mMotion.mUnknown12;
            }
            if (hitB && !(pB->mFlags & 8) && !fn_80143718(pB, pA)) {
                pB->mMotion.mPos = pB->mMotion.mUnknown12;
            }
        }
    }
    fn_80143360(pA, pB, totalA);
    fn_80143360(pB, pA, totalB);
}

void fn_80143D3C(Block_80170374 *pBlock)
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

void fn_80143DC4(Object_80039F5C *p)
{
    int *pRefs = p->mUnknown628;
    int ref;
    unsigned int i;

    fn_8009BD2C(0, &ref);
    for (i = 0; i < 2; i++) {
        pRefs[i] = ref;
    }
}

void fn_80143E14(Object_80039F5C *p, Object_80039F5C *pOther)
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

void fn_80143EBC(Object_80039F5C *p, Object_80039F5C *pOther)
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
