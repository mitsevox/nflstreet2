/* Ball-carrier move state. While the ball is live the ball carrier can do a
   move: the controlling player starts it with a button, and the computer
   starts it when a defender is near. This file decides whether he may,
   starts the player state for it, and runs that state: its start, each
   frame, its end and its button input. */

#include "game/Record_800DB60C.h"
#include "game/Input_800B6D34.h"
#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/cu_80067C10.h"
#include "game/Ball.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_801C1F94.h"
#include "game/fn_800B65A0.h"

/* Partial view of the opaque player block at +336 used by the handlers
   below. */
struct CarrierMoveBlock_t {
    Record_800DB60C mRecord;
    unsigned char mUnknown24;
    unsigned char mUnknown25;
    unsigned short mUnknown26;
};

extern "C" {
void fn_800A8954(int event, int team, Object_80039F5C *p);
int fn_800C4B6C(Object_80039F5C *p);
int PlayerMoveGetKind(Object_80039F5C *p);
void PlayerMoveBegin(Object_80039F5C *p, int a, int b);
void fn_800D640C(Object_80039F5C *p);
void fn_800DB520(void *pBlock, Object_80039F5C *p, Object_80039F5C *pOther, float value);
void fn_800DB7A4(void *pBlock, Object_80039F5C *p);
void fn_800EF224(Object_80039F5C *p);
void fn_800EF538(Object_80039F5C *p);
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
void fn_800F05E4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
float fn_801250B8(Object_80039F5C *p, Object_80039F5C *a, int b);

extern float lbl_803EAE10;
}

extern "C" int CarrierMoveCanStart(Object_80039F5C *p)
{
    int result = 0;

    if (fn_800AD9B4() == 3) {
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
        case 34:
        case 35:
            result = 0;
            break;
        default:
            result = 1;
            break;
        }
        if (result && p->mUnknown1032 == 4) {
            result = 0;
        }
    }
    return result;
}

extern "C" int CarrierMoveStart(Object_80039F5C *p, int a)
{
    int result = 0;

    if (CarrierMoveCanStart(p)) {
        Message_800F01CC message;

        PlayerMoveBegin(p, a, 36);
        result = 1;
        fn_801C1F94(&message, 0, 4);
        message.mId = 36;
        fn_800F00D4(0, p->mpState, &message, p);
    }
    return result;
}

extern "C" int CarrierMoveEnter(Object_80039F5C *p)
{
    CarrierMoveBlock_t *pBlock = (CarrierMoveBlock_t *)&p->mUnknown336;
    int mode = PlayerMoveGetKind(p);

    if (p == BallGetCurrentHolder()) {
        pBlock->mUnknown24 = 1;
    } else {
        pBlock->mUnknown24 = 0;
    }
    pBlock->mUnknown25 = 0;
    pBlock->mUnknown26 = 0;
    fn_800DB520(pBlock, p, 0, 0.0f);
    if (mode == 4) {
        fn_800EF224(p);
    } else {
        fn_800EF538(p);
    }
    fn_80067E3C(97, &p->mMotion.mPos, p->mId, p->mpState->mId, 0, 0);
    fn_800A8954(3, p->mIdBytes[2], p);
    p->mUnknown512.mUnknown14 = 0;
    p->mFlags &= ~4;
    return 0;
}

extern "C" int CarrierMoveUpdate(Object_80039F5C *p)
{
    CarrierMoveBlock_t *pBlock = (CarrierMoveBlock_t *)&p->mUnknown336;

    pBlock->mUnknown26++;
    fn_800DB7A4(pBlock, p);
    if (pBlock->mUnknown24) {
        int result = (int)BallFindHeldBy(p);

        if (result == 0) {
            p->mFlags |= 0x4000000;
            pBlock->mUnknown24 = result;
        }
    }
    if (p->mFlags & 1) {
        p->mFlags &= ~1;
        if (pBlock->mUnknown25) {
            if (fn_800C4B6C(p)) {
                return 1;
            }
        } else {
            pBlock->mUnknown25 = 1;
        }
    }
    if (p->mFlags & 0x40000000) {
        p->mFlags &= ~0x40000000;
        fn_800D640C(p);
    }
    if (p->mFlags & 4) {
        p->mFlags &= ~4;
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
        p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
        p->mUnknown512.mUnknown0 = 0.72f;
        return 1;
    }
    if (p->mUnknown9[0] != 1) {
        Message_800F01CC message;

        p->mFlags &= ~0x80000;
        fn_801C1F94(&message, 0, 4);
        message.mId = 11;
        message.mUnknown1[0] = p->mUnknown9[0];
        fn_800F05E4(0, p->mpState, &message, p);
        return 1;
    }
    return 0;
}

extern "C" int CarrierMoveExit(Object_80039F5C *p)
{
    p->mUnknown512.mUnknown14 = 1;
    p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
    p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
    p->mUnknown512.mUnknown0 = 0.72f;
    p->mUnknown512.mUnknown15 = 0;
    p->mFlags &= ~8;
    return 1;
}

extern "C" int CarrierMoveInput(Object_80039F5C *p)
{
    CarrierMoveBlock_t *pBlock = (CarrierMoveBlock_t *)&p->mUnknown336;
    Input_800B6D34 input;

    fn_800B65A0(p->mIdBytes[2]);
    fn_800B6D34(p, &input);
    if (input.mUnknown95 & 64) {
        fn_800DB60C(&pBlock->mRecord, p);
    }
    return 0;
}

extern "C" int CarrierMovePickKind(Object_80039F5C *p, Object_80039F5C *a)
{
    return fn_801250B8(p, a, 6) < lbl_803EAE10;
}
