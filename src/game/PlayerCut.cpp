/* Player state 20: a player plants and cuts to a new direction with a table-driven
   animation, then hands over to the next state or keeps running on his facing. Also holds
   the lookups other code uses to read the cut table and the cut in progress. */

#include "engine/cu_801B9F00.h"
#include "game/StyleTracker.h"
#include "game/OptionRunControl.h"
#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/AnimMomentumActor.h"
#include "game/Object_8017886C.h"
#include "game/Plan_80121264.h"
#include "game/Table_80089904.h"
#include "engine/AnimStateAnimList.h"
#include "game/AudmonEvent.h"
#include "game/cu_8003108C.h"
#include "game/Ball.h"
#include "game/fn_800AD9B4.h"
#include "game/GameOptions.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80178D18.h"
#include "game/fn_801C1F94.h"
#include "game/fn_80227638.h"
#include "game/fn_802270D4.h"
#include "game/fn_8022781C.h"
#include "game/fn_802372EC.h"
#include "game/fn_801BE60C.h"
#include "game/fn_800B65A0.h"
#include "game/fn_800F06F4.h"
#include <math.h>

extern "C" {
void fn_800A5A8C(int a, void *pA, void *pB);
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
float AnimSeqGetOpcodeTime(void *p, int key);
float AnimSeqGetTimeToOpcode(AnimSeq_t *p, int key);
int MathAngleDiff(int a, int b);
float PlyrMoveGetRatedSpeed(Object_80039F5C *p, float a, float b);
void fn_80227384(Point_8017886C *pOut, Point_8017886C *pIn, int angle);
void fn_8009BD60(Object_80039F5C *p);
int fn_800B83F4(Object_80039F5C *p);
int fn_800C4D54(Object_80039F5C *p);
int fn_80112928(Object_80039F5C *p);
float fn_80260FE8(float a);
float fn_80260E24(float a);
extern float gPlyrMoveFwdSpeed;

void PlayerCutStartAnim(Object_80039F5C *p);
Info_80089904 *PlayerCutFindAnimInfo(int a, int b);
void PlayerCutInitHeadings(Object_80039F5C *p);
void PlayerCutPostChainedCut(Object_80039F5C *p, int value);
void PlayerCutPostTurn(Object_80039F5C *p, int angle);
int PlayerCutEnter(Object_80039F5C *p);
int PlayerCutUpdate(Object_80039F5C *p);
int PlayerCutExit();
void PlayerCutMirrorMessage(unsigned char *p);
int PlayerCutGetTargetHeading(Object_80039F5C *p);
int PlayerCutGetStartHeading(Object_80039F5C *p);
int PlayerCutGetRunHeading(Object_80039F5C *p);
int PlayerCutGetMessageTurn(Message_800F01CC *pMessage);
void PlayerCutGetAnimOffset(int a, unsigned char b, int angle, Point_8017886C *pOut);
int PlayerCutGetAnimLength(unsigned char a);
int PlayerCutGetTimeLeft(Object_80039F5C *p);
int PlayerCutGetAnimTime(Object_80039F5C *p);
void PlayerCutGetEndPoint(Object_80039F5C *p, Point_8017886C *pOut);
float PlayerCutGetRunSpeed(Object_80039F5C *p, float value);
}

/* Player block at +336 as used by PlayerCutInitHeadings, PlayerCutEnter, PlayerCutGetTargetHeading,
   PlayerCutGetStartHeading and PlayerCutGetEndPoint. Only the accessed fields are declared; the
   size is unknown. */
struct PlayerCutState_t {
    Point_8017886C mUnknown0;
    int mUnknown8;
    int mUnknown12;
    int mUnknown16;
    int mUnknown20;
};

/* The list fn_801BBC3C fills with the cut animations (object type 1, state 153). The game
   declaration of fn_801BBC3C takes the Table_80089904 view, and the entries' +4 words are
   Info_80089904 pointers. */
static AnimStateAnimList_t _PlayerCut_sAnimList;

extern "C" void PlayerCutStartAnim(Object_80039F5C *p)
{
    PlayerCutState_t *state = (PlayerCutState_t *)&p->mUnknown336;

    p->mUnknown512.mUnknown14 = 6;
    p->mUnknown512.mUnknown4 = state->mUnknown12;
    p->mUnknown512.mUnknown8 = state->mUnknown12;
    p->mUnknown512.mUnknown0 = 1.0f;
    fn_8009BD60(p);
    p->mUnknown1008.mUnknown0 = p->mpState->mUnknown1;
    p->mUnknown1008.mUnknown1 = p->mpState->mUnknown2;
    if (p->mpState->mUnknown3[0] == 1) {
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 198, 1.0f, p);
    } else if (p->mpState->mUnknown3[0] == 2) {
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 199, 1.0f, p);
    } else if (fn_800B83F4(p)) {
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 239, 1.0f, p);
    } else {
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 153, 1.0f, p);
    }
    p->mUnknown512.mUnknown14 = 0;
    p->mFlags &= ~1;
    p->mFlags &= ~4;
}

extern "C" Info_80089904 *PlayerCutFindAnimInfo(int a, int b)
{
    unsigned int i;

    fn_801BBC3C(1, 153, (Table_80089904 *)&_PlayerCut_sAnimList);
    for (i = 0; i < _PlayerCut_sAnimList.mCount; i++) {
        Info_80089904 *pInfo = (Info_80089904 *)_PlayerCut_sAnimList.mEntries[i].mpUnknown4;

        if (pInfo->mType == a && pInfo->mValue == b) {
            return pInfo;
        }
    }
    return (Info_80089904 *)_PlayerCut_sAnimList.mEntries[0].mpUnknown4;
}

extern "C" void PlayerCutInitHeadings(Object_80039F5C *p)
{
    PlayerCutState_t *state = (PlayerCutState_t *)&p->mUnknown336;
    Info_80089904 *pInfo = PlayerCutFindAnimInfo(p->mpState->mUnknown2, p->mpState->mUnknown1);

    state->mUnknown8 = p->mMotion.mFacing & 0xFFFFFF;
    state->mUnknown12 = state->mUnknown8 + pInfo->mUnknown12 & 0xFFFFFF;
    state->mUnknown16 = 0;
}

extern "C" void PlayerCutPostChainedCut(Object_80039F5C *p, int value)
{
    Message_800F01CC message;
    int kind;

    AudmonEventPostId(38, &p->mMotion.mPos, p->mId, 0, 0, 0);
    StyleTrackerOnCarrierActionTwo(p);
    fn_801C1F94(&message, 0, 4);
    message.mId = 20;
    kind = p->mpState->mUnknown2;
    if (kind == 4) {
        message.mUnknown1[1] = 1;
    } else {
        message.mUnknown1[1] = kind;
    }

    message.mUnknown1[0] = p->mpState->mUnknown1;
    message.mUnknown1[2] = value;
    fn_800F00D4(0, p->mpState, &message, p);
}

extern "C" void PlayerCutPostTurn(Object_80039F5C *p, int angle)
{
    Message_800F01CC message;

    fn_801C1F94(&message, 0, 4);
    if (((angle - p->mMotion.mFacing) & 0xFFFFFF) > 0x800000) {
        message.mUnknown1[0] = 1;
    } else {
        message.mUnknown1[0] = 2;
    }
    message.mUnknown1[2] = 0;
    unsigned short value = (unsigned short)fn_80260E24(fn_80260FE8((float)((float)MathAngleDiff(angle, p->mMotion.mFacing)
                                                   * 0.000021457672119140625f * (16.0 / 180.0))) * 0.5f);

    switch (value) {
    case 1: case 15: message.mUnknown1[1] = 3; break;
    case 2: case 14: message.mUnknown1[1] = 1; break;
    case 3: case 13: message.mUnknown1[1] = 4; break;
    case 4: case 12: message.mUnknown1[1] = 2; break;
    case 5: case 11: message.mUnknown1[1] = 7; break;
    case 6: case 10: message.mUnknown1[1] = 5; break;
    case 7: case 8: case 9: message.mUnknown1[1] = 11; break;
    case 0: case 16: default: return;
    }
    message.mId = 20;
    fn_800F053C(0, p->mpState, &message, p);
}

extern "C" int PlayerCutEnter(Object_80039F5C *p)
{
    PlayerCutState_t *state = (PlayerCutState_t *)&p->mUnknown336;

    state->mUnknown20 = 0;
    PlayerCutInitHeadings(p);
    PlayerCutStartAnim(p);
    PlayerCutGetAnimOffset(p->mpState->mUnknown2, p->mpState->mUnknown1, state->mUnknown8 + state->mUnknown16,
                &state->mUnknown0);
    fn_80227638(&state->mUnknown0, &state->mUnknown0, &p->mMotion.mPos);
    if (fn_801BE648(p->mpUnknown792) == 153) {
        fn_800A5A8C(10, p, p);
    }
    return 0;
}

extern "C" int PlayerCutUpdate(Object_80039F5C *p)
{
    PlayerCutState_t *state = (PlayerCutState_t *)&p->mUnknown336;
    int animation = fn_801BE648(p->mpUnknown792);
    int held = (p->mFlags >> 14) & 1;

    if (held == 1) {
        if (!p->mUnknown512.mUnknown14) {
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
            p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
            p->mUnknown512.mUnknown0 = 1.0f;
        }
        return 1;
    }
    if (p->mFlags & 1) {
        p->mFlags &= ~1;
        int value = fn_800C4D54(p);

        if (value) {
            PlayerCutPostChainedCut(p, value);
            return 1;
        }
    }
    if (p->mFlags & 4) {
        p->mFlags &= ~4;
        if (p->mpState[1].mId == 51) {
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
            p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
            p->mUnknown512.mUnknown0 = 1.0f;
        } else {
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown8 = p->mMotion.mUnknown32;
            p->mUnknown512.mUnknown4 = p->mMotion.mUnknown32;
            p->mUnknown512.mUnknown0 = 1.0f;
        }
        if (!p->mpState[1].mId) {
            Message_800F01CC message;

            fn_801C1F94(&message, 0, 4);
            message.mId = 21;
            fn_800F00D4(0, p->mpState, &message, p);
        }
        return 1;
    }
    if ((animation == 153 || animation == 239) && --state->mUnknown20 < 0) {
        state->mUnknown20 = (int)((int)((1.0f - p->mRatings[3] * (1.0f / 255.0f)) * 5.0f) + 2.0f);
        if (fn_80112928(p)) {
            return 0;
        }
    }
    return 0;
}

extern "C" int PlayerCutExit()
{
    return 1;
}

extern "C" void PlayerCutMirrorMessage(unsigned char *p)
{
    if (p[1] == 1) {
        p[1] = 2;
    } else {
        p[1] = 1;
    }
}

extern "C" int PlayerCutGetTargetHeading(Object_80039F5C *p)
{
    return ((PlayerCutState_t *)&p->mUnknown336)->mUnknown12;
}

extern "C" int PlayerCutGetStartHeading(Object_80039F5C *p)
{
    return ((PlayerCutState_t *)&p->mUnknown336)->mUnknown8;
}

extern "C" int PlayerCutGetRunHeading(Object_80039F5C *p)
{
    int angle = 0;
    State_80039F5C *pState = p->mpState;
    int other = 0;

    switch (pState->mUnknown2) {
    case 8:
    case 9: {
        int count = PlayerCutGetAnimTime(p);

        if (pState->mUnknown2 == 8) {
            if (count <= 55) {
                angle = PlayerCutGetTargetHeading(p) + 0x800000;
                angle &= 0xFFFFFF;
            } else {
                other = 1;
            }
        } else {
            if (count <= 51) {
                angle = PlayerCutGetTargetHeading(p) + 0x800000;
                angle &= 0xFFFFFF;
            } else {
                other = 1;
            }
        }
        break;
    }
    default:
        other = 1;
        break;
    }
    if (other) {
        angle = PlayerCutGetTargetHeading(p);
    }
    return angle;
}

extern "C" int PlayerCutGetMessageTurn(Message_800F01CC *pMessage)
{
    int angle = 0;
    Info_80089904 *pInfo = PlayerCutFindAnimInfo(pMessage->mUnknown1[1], pMessage->mUnknown1[0]);

    if (pInfo) {
        angle = pInfo->mUnknown12 & 0xFFFFFF;
    }
    return angle;
}

extern "C" void PlayerCutGetAnimOffset(int a, unsigned char b, int angle, Point_8017886C *pOut)
{
    Point_8017886C point;
    Info_80089904 *pInfo;

    point.mX = 0.0f;
    point.mY = 0.0f;
    pInfo = PlayerCutFindAnimInfo(a, b);

    if (pInfo) {
        point.mX = pInfo->mUnknown28;
        point.mY = pInfo->mUnknown32;
    }
    fn_80227384(pOut, &point, angle);
}

extern "C" int PlayerCutGetAnimLength(unsigned char a)
{
    int result = 0;
    Info_80089904 *pInfo = PlayerCutFindAnimInfo(a, 1);

    if (pInfo) {
        result = (int)pInfo->mUnknown24;
    }
    return result;
}

extern "C" int PlayerCutGetTimeLeft(Object_80039F5C *p)
{
    int result = 0;
    int count = PlayerCutGetAnimTime(p);
    int limit = PlayerCutGetAnimLength(p->mpState->mUnknown2);

    if (limit > count) {
        result = limit - count;
    }
    return result;
}

extern "C" int PlayerCutGetAnimTime(Object_80039F5C *p)
{
    int result = 0;

    if (fn_801BA568(p->mpUnknown796, p->mpUnknown800, 153)) {
        int index = fn_801BA5A8(p->mpUnknown796, p->mpUnknown800, 153, 0);
        float start = AnimSeqGetTimeToOpcode(&p->mpUnknown800[index].mUnknown4C, 0xC004);

        result = (int)(AnimSeqGetOpcodeTime(p->mpUnknown800[index].mUnknown4C.mpUnknown0, 0xC004) - start);
    }
    return result;
}

extern "C" void PlayerCutGetEndPoint(Object_80039F5C *p, Point_8017886C *pOut)
{
    PlayerCutState_t *state = (PlayerCutState_t *)&p->mUnknown336;

    pOut->mX = state->mUnknown0.mX;
    pOut->mY = state->mUnknown0.mY;
}

extern "C" float PlayerCutGetRunSpeed(Object_80039F5C *p, float value)
{
    State_80039F5C *state = p->mpState;
    int limit = PlayerCutGetAnimLength(state->mUnknown2);
    float fraction = 1.0f - (unsigned int)PlayerCutGetTimeLeft(p) / (float)(unsigned int)limit;
    float speed;

    switch (state->mUnknown2) {
    case 11:
        if (!(fraction < 0.64f)) {
            speed = p->mMotion.mUnknown28 / gPlyrMoveFwdSpeed;
        } else {
            speed = value;
        }
        break;
    case 5:
        if (fraction >= 0.8f) {
            speed = p->mMotion.mUnknown28 / gPlyrMoveFwdSpeed;
        } else {
            speed = value;
        }
        break;
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    default:
        speed = value;
        break;
    }
    return PlyrMoveGetRatedSpeed(p, speed, 0.72f);
}
