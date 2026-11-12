/* Ball-carrier move state. While the ball is live the ball carrier can do a
   move: the controlling player starts it with a button, and the computer
   starts it when a defender is near. This file decides whether he may,
   starts the player state for it, picks the move animation (a wall move
   next to a wall, otherwise one of the open-field moves), and runs that
   state: its start, each frame, its end and its button input. */

#include "engine/cu_801B9F00.h"
#include "game/Command_800CEE74.h"
#include "game/LevelData.h"
#include "game/Record_800DB60C.h"
#include "game/StyleTracker.h"
#include "game/Input_800B6D34.h"
#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/AudmonEvent.h"
#include "game/Ball.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_801C1F94.h"
#include "game/fn_800B65A0.h"
#include "game/fn_802372EC.h"

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
void fn_800DB520(void *pBlock, Object_80039F5C *p, Object_80039F5C *pOther, float value);
void fn_800DB7A4(void *pBlock, Object_80039F5C *p);
void CarrierMoveStartWallAnim(Object_80039F5C *p);
void CarrierMoveStartAnim(Object_80039F5C *p);
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
void fn_800F05E4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
float fn_801250B8(Object_80039F5C *p, Object_80039F5C *a, int b);
int fn_801BE068(void *a, void *b, void *c, unsigned short d, float f, void *e);
void fn_8009BD60(Object_80039F5C *p);
void AnimSeqSetSpeed(void *p, float value);
float MathInverse(float value);
int fn_800A7EF4(int team);
int fn_800CA5CC(Object_80039F5C *p, int a, int b);
float fn_800CA9B4(int kind, Object_80039F5C *p);
float LevelGetWallHeight(LevelWall_t *pRecord);
int fn_800B83A0(Object_80039F5C *p);
int fn_800A8444(int team);
void PlayerMoveSetResult(Object_80039F5C *p, int a);

static float _CarrierMove_fBaseAnimTime = 0.25f;
static float _CarrierMove_fRatedAnimScale = 1.15f;
static float _CarrierMove_fAnimWeight = 1.0f;
int _CarrierMove_iUnused = 5;
static float _CarrierMove_fPickRange = 9.0f;
}


extern "C" void CarrierMoveStartWallAnim(Object_80039F5C *p) {
    int flag = 0;
    int kind;
    if (fn_800B83A0(p)) {
        kind = 228;
        if (fn_800A8444(p->mIdBytes[2]))
            p->mUnknown1008.mUnknown0 = 3;
        else
            p->mUnknown1008.mUnknown0 = 2;
    } else {
        p->mUnknown1008.mUnknown0 = 0;
        kind = 230;
    }
    flag = p->mUnknown776 == 1;
    Command_800CEE74 command;
    int value;
    int unused;
    fn_800CEE74(&command, p, 0, 0, 0, kind, flag);
    int index = fn_800C3BEC(p, &command, &value, &unused);
    LevelWall_t *pRecord = &LevelGetData()->mUnknown140[p->mUnknown1160.mUnknown28];
    if (kind == 228) {
        if (index == -1 || (p->mUnknown1008.mUnknown0 == 3 && LevelGetWallHeight(pRecord) < 5.0f)) {
            p->mUnknown1008.mUnknown0 = 2;
            index = fn_800C3BEC(p, &command, &value, &unused);
        }
        if (p->mUnknown1160.mUnknown24 < 2.0f) {
            p->mUnknown1008.mUnknown0 = 1;
            index = fn_800C3BEC(p, &command, &value, &unused);
        }
    }
    if (index != -1) {
        fn_800C39E0(p, kind, index, value, flag);
        if (fn_801BA568(p->mpUnknown796, p->mpUnknown800, 228)) {
            Record_800D81C8 *pRecords = p->mpUnknown800;
            int entry = fn_801BA5A8(p->mpUnknown796, pRecords, 228, 0);
            float speed;
            if (fn_800A7EF4(p->mIdBytes[2]) == 0) {
                speed = _CarrierMove_fBaseAnimTime;
            } else {
                speed = 1.0f;
                float rating = p->mRatings[4];
                if (rating < 200.0f)
                    speed = rating * 0.0004999998f + 0.8f;
                speed *= _CarrierMove_fRatedAnimScale;
            }
            if (fn_800CA5CC(p, 11, 1))
                speed *= fn_800CA9B4(12, p);
            Record_800D81C8 *pEntry = &pRecords[entry];
            AnimSeqSetSpeed(&pEntry->mUnknown4C, MathInverse(speed));
            pEntry->mUnknown2C = _CarrierMove_fAnimWeight;
            PlayerMoveSetResult(p, 0);
        }
        if (kind != 230) {
            AudmonEventPostId(51, &p->mMotion.mPos, p->mId, 0, 0, 0);
            AudmonEventPostId(56, &p->mMotion.mPos, p->mId, 0, 0, 0);
        }
        p->mFlags |= 8;
    } else {
        PlayerMoveBegin(p, 1, 36);
        CarrierMoveStartAnim(p);
        AudmonEventPostId(59, &p->mMotion.mPos, p->mId, 0, 0, 0);
    }
}

extern "C" void CarrierMoveStartAnim(Object_80039F5C *p) {
    int mode = PlayerMoveGetKind(p);
    fn_8009BD60(p);
    if (BallGetCurrentHolder() == p) {
        int kind = 1;
        if (!mode)
            kind = 12;
        p->mUnknown1008.mUnknown0 = kind;
        if (p->mUnknown776 == 1)
            p->mUnknown1008.mUnknown1 = 2;
        else
            p->mUnknown1008.mUnknown1 = 1;
    } else {
        p->mUnknown1008.mUnknown1 = 0;
        p->mUnknown1008.mUnknown0 = 1;
    }
    if (mode) {
        unsigned int roll = fn_802372EC(0, 100);
        if (roll <= 32)
            p->mUnknown1008.mUnknown2 = 1;
        else if (roll <= 66)
            p->mUnknown1008.mUnknown2 = 2;
        else
            p->mUnknown1008.mUnknown2 = 3;
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 180, 1.0f, p);
        switch (p->mUnknown1008.mUnknown2) {
        case 1:
            if (p->mUnknown1008.mUnknown1 == 2)
                PlayerMoveSetResult(p, 1);
            else
                PlayerMoveSetResult(p, 2);
            break;
        case 2:
            if (p->mUnknown1008.mUnknown1 == 2)
                PlayerMoveSetResult(p, 7);
            else
                PlayerMoveSetResult(p, 8);
            break;
        case 3:
            if (p->mUnknown1008.mUnknown1 == 2)
                PlayerMoveSetResult(p, 3);
            else
                PlayerMoveSetResult(p, 4);
            break;
        }
    } else {
        PlayerMoveSetResult(p, 0);
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 24, 1.0f, p);
    }
    if (fn_801BA568(p->mpUnknown796, p->mpUnknown800, 24) || fn_801BA568(p->mpUnknown796, p->mpUnknown800, 180)) {
        Record_800D81C8 *pRecords = p->mpUnknown800;
        int index;
        if (mode)
            index = fn_801BA5A8(p->mpUnknown796, pRecords, 180, 0);
        else
            index = fn_801BA5A8(p->mpUnknown796, pRecords, 24, 0);
        float speed;
        if (fn_800A7EF4(p->mIdBytes[2]) == 0) {
            speed = _CarrierMove_fBaseAnimTime;
        } else {
            float rating = p->mRatings[4];
            speed = 1.0f;
            if (rating < 200.0f)
                speed = rating * 0.0004999998f + 0.8f;
            speed *= _CarrierMove_fRatedAnimScale;
        }
        if (fn_800CA5CC(p, 11, 1))
            speed *= fn_800CA9B4(12, p);
        Record_800D81C8 *pRecord = &pRecords[index];
        AnimSeqSetSpeed(&pRecord->mUnknown4C, MathInverse(speed));
        pRecord->mUnknown2C = _CarrierMove_fAnimWeight;
    }
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
        CarrierMoveStartWallAnim(p);
    } else {
        CarrierMoveStartAnim(p);
    }
    AudmonEventPostId(97, &p->mMotion.mPos, p->mId, p->mpState->mId, 0, 0);
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
        StyleTrackerFinishHurdle(p);
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
    return fn_801250B8(p, a, 6) < _CarrierMove_fPickRange;
}
