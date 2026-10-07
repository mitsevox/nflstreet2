#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_800F06F4.h"
#include "game/fn_80178D18.h"
#include "game/fn_801C1F94.h"
#include "game/fn_802372EC.h"

extern "C" {
void fn_8003AB28(Object_80039F5C *p, Message_800F01CC *pMessage, int value);
int fn_800B65A0(int unknown);
void fn_800B6714(Object_80039F5C *p, int port);
void fn_800D0BF4(Object_80039F5C *p, int a, int b);
void fn_800E9528(Object_80039F5C *p);
int fn_800E96EC(Object_80039F5C *p, Object_80039F5C *pOther);
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
void fn_8010D508(Object_80039F5C *p);
int fn_801101DC(Object_80039F5C *p);
int fn_801102A4(Object_80039F5C *p);
void fn_8011E240(Object_80039F5C *p);
void fn_8011E3EC(Object_80039F5C *p, int a);
Object_80039F5C *fn_801244F0(Object_80039F5C *p, int team, int a, unsigned char count, float *pOut, int b);
float fn_801250B8(Object_80039F5C *p, int a, int b);
int fn_80178308(void);
int fn_80178320(void);
int fn_801BE648(void *p);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
void fn_80227690(void *pOut, void *pA, void *pB);

extern char lbl_802DABBC[];
extern float lbl_803EAF58;
}

extern "C" int fn_800F08F8() {
    return 0;
}

extern "C" int fn_800F0900() {
    return 1;
}

extern "C" int fn_800F0908() {
    return 0;
}

extern "C" int fn_800F2C14() {
    return 0;
}

extern "C" int fn_800F8D24() {
    return 0;
}

extern "C" int fn_800F9CAC() {
    return 1;
}

extern "C" int fn_800FF860() {
    return 1;
}

extern "C" void fn_8010BE54(Object_80039F5C *p)
{
    Message_800F01CC message;

    fn_801C1F94(&message, 0, 4);
    message.mId = 93;
    fn_8003AB28(p, &message, 0);
}

extern "C" void fn_8010BEA4(void)
{
    fn_801C1F94(lbl_802DABBC, 0, 100);
}

extern "C" int fn_8010C864(Object_80039F5C *p)
{
    int found = 0;
    unsigned char i;
    unsigned int count = fn_80178D18(fn_80178308());

    for (i = 0; i < count; i++) {
        Object_80039F5C *pOther = fn_80039F5C(fn_80178308(), i);

        if (pOther != p && fn_800F06F4(0, pOther->mpState, 26, 0xFFFF) != 0xFFFF) {
            found = 1;
            break;
        }
    }
    return found;
}

extern "C" void fn_8010CFD4(Object_80039F5C *p)
{
    if (((p->mMotion.mUnknown32 - 0x400000) & 0xFFFFFF) > 0x800000) {
        p->mUnknown512.mUnknown15 = 15;
    } else {
        p->mUnknown512.mUnknown15 = 16;
    }
}

extern "C" int fn_8010D6D4(Object_80039F5C *p)
{
    int port;

    fn_8010D508(p);
    port = fn_800B65A0(p->mIdBytes[2]);
    if (port != 255 && p->mUnknown8 == 255) {
        fn_800B6714(p, port);
    }
    p->mUnknown512.mUnknown14 = 0;
    return 0;
}

extern "C" Object_80039F5C *fn_8010DA38(Object_80039F5C *p, Object_80039F5C *pExclude)
{
    unsigned char i;
    unsigned int count = fn_80178D18(p->mIdBytes[2]);

    for (i = 0; i < count; i++) {
        Object_80039F5C *pOther = fn_80039F5C(p->mIdBytes[2], i);

        if (pOther != pExclude && pOther->mpState->mId == 90) {
            return pOther;
        }
    }
    return 0;
}

extern "C" void fn_8010EF40(Object_80039F5C *p)
{
    int found = 0;
    Block_80170374 *pBlock = &p->mUnknown560;
    Object_80039F5C *pCarrier;
    Object_80039F5C *pOther;
    Point_8017886C delta;

    if (pBlock->mFlags.mBytes[0] == 1) {
        pCarrier = fn_80137B40();
        if (pCarrier != 0 && (pCarrier->mFlags & 0x10000)) {
            switch (pBlock->mUnknown54) {
            case 0:
            case 5:
            case 7:
                pOther = fn_8009BCE8(&pBlock->mUnknown44);
                if (pOther == pCarrier) {
                    found = 1;
                } else {
                    pOther = fn_8009BCE8(&pBlock->mUnknown40);
                    if (pOther != 0 && (pOther->mpState->mId == 17 || pOther == pCarrier)) {
                        found = 1;
                    }
                }
                if (found && fn_802372EC(0, 100) <= 74) {
                    fn_80227690(&delta, &p->mMotion.mPos, &pOther->mMotion.mPos);
                    if (fn_801CFFD0(fn_801CFE40(delta.mY, delta.mX), pOther->mMotion.mUnknown32) <= 0x3FFFFF) {
                        fn_800E96EC(p, pOther);
                    }
                }
                break;
            }
        }
    }
}

extern "C" int fn_8010FB10(Object_80039F5C *p)
{
    fn_8011E3EC(p, 0);
    fn_8011E240(p);
    return 1;
}

extern "C" int fn_8010FD8C() {
    return 1;
}

extern "C" int fn_801100A0(Object_80039F5C *p)
{
    State_80039F5C *pState = p->mpState;

    if (pState->mUnknown2) {
        p->mFlags |= 1 << pState->mUnknown1;
    } else {
        p->mFlags &= ~(1 << pState->mUnknown1);
    }
    return 1;
}

extern "C" int fn_801105B0(Object_80039F5C *p)
{
    int angle;

    if (p->mUnknown776 == 1) {
        angle = (0x800000 - p->mMotion.mFacing) & 0xFFFFFF;
    } else {
        angle = p->mMotion.mFacing;
    }
    if (p->mUnknown1008.mUnknown1 == 6) {
        angle = (angle + 0xB1C71D) & 0xFFFFFF;
    } else {
        angle = (0x131C71D - angle) & 0xFFFFFF;
    }
    if (angle <= 0x5FFFFF) {
        if (angle <= 0x3FFFFF) {
            angle = 0x1000000;
        } else {
            angle = 0x600000;
        }
    }
    return angle;
}

extern "C" int fn_80110630(Key_80110630 *pA, Key_80110630 *pB)
{
    int result = pA->mUnknown0 == pB->mUnknown0;

    if (pA->mUnknown1 != pB->mUnknown1) {
        result = 0;
    }
    if (pA->mUnknown2 != pB->mUnknown2 && pA->mUnknown2 != 0) {
        result = 0;
    }
    return result;
}

extern "C" int fn_80110824(Object_80039F5C *p, int a, int b, int c)
{
    int result = 0;
    Message_800F01CC message;

    if (fn_801101DC(p)) {
        if (b == 0) {
            b = fn_801102A4(p);
        }
        if (a == 1) {
            a = 2;
        }
        result = 1;
        fn_800D0BF4(p, c, 35);
        fn_801C1F94(&message, 0, 4);
        message.mId = 35;
        message.mUnknown1[0] = a;
        message.mUnknown1[1] = b;
        fn_800F00D4(0, p->mpState, &message, p);
    }
    return result;
}

extern "C" int fn_80110EB0(Object_80039F5C *p, int a)
{
    return fn_801250B8(p, a, 6) < lbl_803EAF58;
}

extern "C" int fn_80110EE4(Object_80039F5C *p)
{
    int result;
    int team;
    int angle;
    Object_80039F5C *pTarget;
    float distance;
    Point_8017886C delta;

    switch (p->mpState->mUnknown1) {
    case 1:
        result = 6;
        break;
    case 2:
        result = 8;
        break;
    case 0:
    default:
        team = fn_80178320();
        result = 6;
        pTarget = fn_801244F0(p, team, 0, fn_80178D70(fn_80178320()), &distance, 1);
        if (pTarget != 0) {
            fn_80227690(&delta, &pTarget->mMotion.mPos, &p->mMotion.mPos);
            angle = fn_801CFE40(delta.mY, delta.mX);
            fn_801CFFD0(angle, p->mMotion.mFacing);
            if (((angle - p->mMotion.mFacing) & 0xFFFFFF) > 0x800000) {
                p->mpState->mUnknown1 = 1;
            } else {
                p->mpState->mUnknown1 = 2;
                result = 8;
            }
        } else if (p->mUnknown776 == 2) {
            result = 8;
        }
        break;
    }
    return result;
}

extern "C" int fn_80110FE4(Object_80039F5C *p)
{
    int result = 0;

    if (fn_800AD9B4() == 3) {
        switch (p->mpState->mId) {
        case 5:
        case 10:
        case 11:
        case 12:
        case 15:
        case 16:
        case 17:
        case 25:
        case 26:
        case 27:
        case 34:
        case 35:
            result = 0;
            break;
        default:
            result = 1;
            break;
        }
        if (p != fn_80137B40()) {
            result = 0;
        }
    }
    return result;
}

extern "C" int fn_80111090(Object_80039F5C *p, int a)
{
    int result = 0;
    Message_800F01CC message;

    if (fn_80110FE4(p)) {
        result = 1;
        fn_801C1F94(&message, 0, 4);
        message.mId = 43;
        message.mUnknown1[0] = a;
        fn_800F00D4(0, p->mpState, &message, p);
    }
    return result;
}

extern "C" void fn_80111354(Object_80039F5C *p)
{
    switch (p->mpState->mId) {
    case 5:
    case 10:
    case 11:
    case 15:
    case 16:
    case 17:
    case 25:
    case 26:
    case 27:
    case 32:
    case 36:
    case 58:
        break;
    default:
        fn_800E9528(p);
        break;
    }
}

extern "C" int fn_80111580(Object_80039F5C *p)
{
    switch (fn_801BE648(p->mpUnknown792)) {
    case 196:
    case 210:
        return 0;
    }
    return 1;
}

extern "C" int fn_80111964(Object_80039F5C *p)
{
    p->mUnknown512.mUnknown15 = 0;
    return 1;
}

extern "C" int fn_80113C18() {
    return 0;
}

extern "C" int fn_80125508() {
    return 0;
}
