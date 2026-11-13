/* The loose-ball player state, run through the state handler table. When
   the ball has no carrier every player is told to go after it; each one
   steers to where the ball will be, picks a recovery animation from the
   loose-ball animation table that reaches the ball from where he stands,
   may engage a nearby player on the way, and once someone holds the ball
   sends the message that moves him to the right next state. */

#include "game/StyleTracker.h"
#include "engine/cu_801B9F00.h"
#include "game/Block_801BE60C.h"
#include "game/Input_800B6D34.h"
#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/Ball.h"
#include "game/fn_800F06F4.h"
#include "game/fn_801C1F94.h"
#include "game/fn_80178D18.h"
#include "game/fn_802270D4.h"
#include "game/fn_8022781C.h"
#include "game/fn_80227638.h"
#include "game/fn_802372EC.h"
#include <math.h>
#include "game/fn_801BE60C.h"
#include "game/fn_800B65A0.h"
#include "game/fn_801BA2A8.h"
#include "game/Table_80089904.h"
#include "engine/AnimStateAnimList.h"

#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define CLAMP(v, lo, hi) ((v) < (lo) ? (lo) : ((v) > (hi) ? (hi) : (v)))

/* Player block at +336 in the loose-ball state. */
struct LooseBallBlock_t {
    Vector_80039F5C mUnknown0;
    Vector_80039F5C mUnknown12;
    float mUnknown24;
    int mUnknown28;
    float mUnknown32;
    int mUnknown36;
    unsigned short mUnknown40;
    unsigned char mUnknown42;
    unsigned char mUnknown43;
    signed char mUnknown44;
    signed char mUnknown45;
    char mUnknown46[2];
    char mUnknown48[12];
};

extern "C" {
static int _LooseBall_aiTrimKeys[4] = {74, 160, 159, 157};
static float _LooseBall_fEngageAngle = 90.0f;
static float _LooseBall_fEngageRange = 3.0f;
static float _LooseBall_fEngageMinDist = 1.0f;
static int _LooseBall_iPriorityBase = 150;
static int _LooseBall_iPriorityFacing = 15;
static float _LooseBall_fPriorityPerDist = 10.0f;
static float _LooseBall_fPriorityPerRating = 0.16f;
static int _LooseBall_iPriorityRandom = 10;
static float _LooseBall_fLeadScale = 4.0f;
static float _LooseBall_fThreatRange = 2.0f;
static float _LooseBall_fThreatAngle = 15.0f;
static AnimStateAnimList_t _LooseBall_AnimTable;
extern float gPlyrMoveFwdSpeed;
int fn_8009A77C(Object_80039F5C *p);
float fn_8022785C(Vector_80039F5C *pA, Vector_80039F5C *pB);
int fn_80099734(Object_80039F5C *p, Ball_t *pBall, int a, int mode, void *pBlock, int b, int c, int d, int e,
                float f);
int fn_80099F04(Object_80039F5C *p, int a, unsigned char index);
Object_80039F5C *fn_801244F0(Object_80039F5C *p, int team, unsigned char a, unsigned char count, float *pOut, int b);
void fn_8013AA00(Ball_t *pBall, float height, float *pTime, Vector_80039F5C *pLanding);
int CharSkelGetJointByName(void *p, const char *pName);
int BallStateCheckPlayerHit(Ball_t *pBall, void *pData, int value);
void fn_80227690(void *pOut, void *pA, void *pB);
void fn_80227264(Vector_80039F5C *pOut, Vector_80039F5C *pV, float scale);
void fn_8022765C(Vector_80039F5C *pOut, Vector_80039F5C *pA, Vector_80039F5C *pB);
int fn_801CFE40(float y, float x);
int MathAngleDiff(int a, int b);
void fn_8009A8D4(void *p);
int fn_800B78DC(Object_80039F5C *p);
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
void fn_80227384(void *pOut, void *pIn, int angle);
void fn_80227350(void *pOut, void *pV, float scale);
int fn_8009F0B8(Object_80039F5C *p, int angle);
void PlyrFindNearest(void *pPos, float *pExtra, int team);
void PlyrSetPendingMsg(Object_80039F5C *p, Message_800F01CC *pMessage, int value);
int fn_80178360(void);
void fn_8011E240(Object_80039F5C *p);
void fn_8011E3EC(Object_80039F5C *p, int a);
int fn_8010A2DC(Object_80039F5C *p, int a, short b);
int BallStateGet(Ball_t *pBall, int *pOut);
int fn_801486A0(void);
int fn_80178308(void);
int fn_801787A0(void);
int fn_801BE068(void *a, void *b, void *c, unsigned short d, float f, void *e);
float fn_80178A08(void);
float fn_80178A44(void);
float fn_80178A68(Point_8017886C *pPos);
Object_80039F5C *fn_801245DC(Object_80039F5C *p, int team, unsigned char a, unsigned char count, int angle, float *pOut, int b);
int fn_8011EAC0(Object_80039F5C *p, Object_80039F5C *pOther);
int fn_8011E8A4(Object_80039F5C *p);
void fn_8011E8D8(Object_80039F5C *p);
int LooseBallStartAnim(Object_80039F5C *p, int a, int b, int c);
int LooseBallGetEdge(Ball_t *pBall);
int LooseBallFindAnim(Object_80039F5C *p, LooseBallBlock_t *pState, Ball_t *pBall, int a, int b);
}

extern "C" int LooseBallTryEngage(Object_80039F5C *p, Ball_t *pBall) {
    int result = 0;
    Vector_80039F5C pos;
    Point_8017886C delta;
    float distance;
    BallGetPosition(pBall, &pos);
    fn_80227690(&delta, &pos, &p->mMotion.mPos);
    if (fn_802270A4(&delta) > _LooseBall_fEngageMinDist) {
        Object_80039F5C *pOther = fn_801245DC(p, p->mIdBytes[2] ^ 1, 0, fn_80178D18(p->mIdBytes[2] ^ 1),
                                              (int)(_LooseBall_fEngageAngle * 46603.37890625f), &distance, 1);
        if (pOther && distance < _LooseBall_fEngageRange)
            result = fn_8011EAC0(p, pOther);
        if (!fn_801486A0() && !result) {
            pOther = fn_801245DC(p, p->mIdBytes[2], 0, fn_80178D18(p->mIdBytes[2]),
                                 (int)(_LooseBall_fEngageAngle * 46603.37890625f), &distance, 1);
            if (pOther && distance < _LooseBall_fEngageRange)
                result = fn_8011EAC0(p, pOther);
        }
    }
    return result;
}

extern "C" int LooseBallCanQueueMessage(Object_80039F5C *p) {
    if (p->mpState->mId != 28)
        return 1;
    return 0;
}

extern "C" void LooseBallPredictPos(Vector_80039F5C *pOut, Ball_t *pBall, float scale) {
    Vector_80039F5C step;
    Vector_80039F5C velocity;
    BallGetPosition(pBall, pOut);
    BallGetVelocity(pBall, &velocity);
    fn_80227264(&step, &velocity, scale);
    fn_8022765C(pOut, pOut, &step);
}

extern "C" int LooseBallStartAnim(Object_80039F5C *p, int a, int b, int c) {
    int result = 0xFFFF;
    if (fn_8011E8A4(p)) {
        fn_8011E8D8(p);
        p->mUnknown1008.mUnknown0 = a;
        p->mUnknown1008.mUnknown1 = b;
        p->mUnknown1008.mUnknown2 = c;
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 48, 1.0f, p);
        result = fn_801BA5A8(p->mpUnknown796, p->mpUnknown800, 48, 0);
        p->mFlags &= ~4;
        p->mUnknown512.mUnknown14 = 0;
        if (((LooseBallBlock_t *)&p->mUnknown336)->mUnknown45 == 5)
            p->mFlags |= 8;
        p->mUnknown9[0] = 1;
    }
    return result;
}

extern "C" int LooseBallCanReach(Object_80039F5C *p, Ball_t *pBall) {
    return 1;
}

extern "C" int LooseBallGetEdge(Ball_t *pBall) {
    int result = 5;
    Vector_80039F5C pos;
    BallGetPosition(pBall, &pos);
    if (pos.mX > fn_80178A08() - 3.0f)
        result = 0;
    else if (pos.mX < 3.0f - fn_80178A08())
        result = 1;
    else if (pos.mY > fn_80178A44() - 3.0f)
        result = 2;
    else if (pos.mY < 3.0f - fn_80178A44())
        result = 3;
    return result;
}

extern "C" int LooseBallGetEdgeFacing(Ball_t *pBall, Object_80039F5C *p) {
    switch (LooseBallGetEdge(pBall)) {
    case 0:
        if (MathAngleDiff(p->mMotion.mFacing, 0xC00000) <= 0xFFFFF)
            return 7;
        if (MathAngleDiff(p->mMotion.mFacing, 0xA00000) <= 0xFFFFF)
            return 1;
        if (MathAngleDiff(p->mMotion.mFacing, 0x800000) <= 0xFFFFF)
            return 1;
        if (MathAngleDiff(p->mMotion.mFacing, 0x600000) <= 0xFFFFF)
            return 1;
        if (MathAngleDiff(p->mMotion.mFacing, 0x400000) <= 0xFFFFF)
            return 2;
        if (MathAngleDiff(p->mMotion.mFacing, 0x200000) <= 0xFFFFF)
            return 3;
        if (MathAngleDiff(p->mMotion.mFacing, 0) <= 0xFFFFF)
            return 4;
        return 6;
    case 1:
        if (MathAngleDiff(p->mMotion.mFacing, 0xC00000) <= 0xFFFFF)
            return 2;
        if (MathAngleDiff(p->mMotion.mFacing, 0xA00000) <= 0xFFFFF)
            return 3;
        if (MathAngleDiff(p->mMotion.mFacing, 0x800000) <= 0xFFFFF)
            return 5;
        if (MathAngleDiff(p->mMotion.mFacing, 0x600000) <= 0xFFFFF)
            return 6;
        if (MathAngleDiff(p->mMotion.mFacing, 0x400000) <= 0xFFFFF)
            return 7;
        if (MathAngleDiff(p->mMotion.mFacing, 0x200000) <= 0xFFFFF)
            return 1;
        if (MathAngleDiff(p->mMotion.mFacing, 0) <= 0xFFFFF)
            return 1;
        return 1;
    case 3:
        if (MathAngleDiff(p->mMotion.mFacing, 0xC00000) <= 0xFFFFF)
            return 4;
        if (MathAngleDiff(p->mMotion.mFacing, 0xA00000) <= 0xFFFFF)
            return 6;
        if (MathAngleDiff(p->mMotion.mFacing, 0x800000) <= 0xFFFFF)
            return 7;
        if (MathAngleDiff(p->mMotion.mFacing, 0x600000) <= 0xFFFFF)
            return 1;
        if (MathAngleDiff(p->mMotion.mFacing, 0x400000) <= 0xFFFFF)
            return 1;
        if (MathAngleDiff(p->mMotion.mFacing, 0x200000) <= 0xFFFFF)
            return 1;
        if (MathAngleDiff(p->mMotion.mFacing, 0) <= 0xFFFFF)
            return 2;
        return 3;
    case 2:
        if (MathAngleDiff(p->mMotion.mFacing, 0xC00000) <= 0xFFFFF)
            return 1;
        if (MathAngleDiff(p->mMotion.mFacing, 0xA00000) <= 0xFFFFF)
            return 1;
        if (MathAngleDiff(p->mMotion.mFacing, 0x800000) <= 0xFFFFF)
            return 2;
        if (MathAngleDiff(p->mMotion.mFacing, 0x600000) <= 0xFFFFF)
            return 3;
        if (MathAngleDiff(p->mMotion.mFacing, 0x400000) <= 0xFFFFF)
            return 4;
        if (MathAngleDiff(p->mMotion.mFacing, 0x200000) <= 0xFFFFF)
            return 6;
        if (MathAngleDiff(p->mMotion.mFacing, 0) <= 0xFFFFF)
            return 7;
        break;
    }
    return 1;
}

extern "C" int LooseBallFindAnim(Object_80039F5C *p, LooseBallBlock_t *state, Ball_t *pBall, int type, int force) {
    Vector_80039F5C target;
    Vector_80039F5C offset;
    Vector_80039F5C ballPos;
    Vector_80039F5C velocity;
    Ball_t *pCurrent = BallGet(state->mUnknown43);
    BallGetPosition(pCurrent, &ballPos);
    float dist = 0.0f;
    float best = 1000.0f;
    state->mUnknown44 = -1;
    if (!fn_801787A0() && (force || ballPos.mZ < 0.5f)) {
        BallGetVelocity(pCurrent, &velocity);
        if (!force && (fn_802270D4(&velocity) >= 100.0f || !LooseBallCanReach(p, pCurrent)))
            goto done;
        fn_801BBC3C(1, 48, (Table_80089904 *)&_LooseBall_AnimTable);
        for (signed char i = 0; i < _LooseBall_AnimTable.mCount; i++) {
            Info_80089904 *pInfo = (Info_80089904 *)_LooseBall_AnimTable.mEntries[i].mpUnknown4;
            if (type != pInfo->mType)
                continue;
            float time = pInfo->mUnknown32;
            state->mUnknown24 = time;
            LooseBallPredictPos(&target, pCurrent, time);
            if (type == 5) {
                if (LooseBallGetEdgeFacing(pCurrent, p) != pInfo->mUnknown6)
                    continue;
                float lane = fn_80178A68((Point_8017886C *)&target);
                float own = fn_80178A68((Point_8017886C *)&p->mMotion.mPos);
                int level = fabsf(lane - own) < 0.5f;
                switch (pInfo->mValue) {
                case 0:
                    if (!level)
                        continue;
                    break;
                case 1:
                    if (lane > own)
                        continue;
                    break;
                case 2:
                    if (lane < own)
                        continue;
                    break;
                default:
                    continue;
                }
            }
            if (fn_8022781C(&target, &p->mMotion.mPos) < 0.75f || fn_8022781C(&ballPos, &p->mMotion.mPos) < 0.75f)
                force = 1;
            offset.mX = pInfo->mUnknown8Float;
            offset.mY = pInfo->mUnknown12Float;
            offset.mZ = pInfo->mUnknown16Float;
            fn_80227384(&offset, &offset, p->mMotion.mFacing);
            fn_8022765C(&offset, &offset, &p->mMotion.mPos);
            fn_802276B4(&offset, &target, &offset);
            dist = fn_802270A4(&offset);
            float reach = fn_802270A4(&pInfo->mUnknown8Float);
            reach = MIN(reach, 0.75f);
            if (type != 2 && type != 5)
                reach = MIN(reach * 2.0f, 0.75f);
            if (!force && dist >= reach)
                continue;
            float ratio = dist / reach;
            if (ratio >= best)
                continue;
            best = ratio;
            fn_80227264(&state->mUnknown0, &offset, 0.75f / (state->mUnknown24 * dist));
            state->mUnknown12.mX = target.mX;
            state->mUnknown12.mY = target.mY;
            state->mUnknown12.mZ = target.mZ;
            fn_80227350(&state->mUnknown12, &offset, 0.75f / dist - 1.0f);
            state->mUnknown0.mZ = 0.0f;
            state->mUnknown44 = i;
            state->mUnknown45 = type;
        }
    }
done:
    return state->mUnknown44 != -1;
}

extern "C" void LooseBallUserRecover(Object_80039F5C *p) {
    LooseBallBlock_t *state = (LooseBallBlock_t *)&p->mUnknown336;
    if (LooseBallFindAnim(p, state, BallGet(state->mUnknown43), 1, 1))
        state->mUnknown40 = LooseBallStartAnim(p, 0, 0, 0);
}

extern "C" int LooseBallCanChase(Object_80039F5C *p, LooseBallBlock_t *state) {
    int result = 1;
    int value;
    BallStateGet(BallGet(state->mUnknown43), &value);
    if (p->mIdBytes[2] != fn_80178308() && !LooseBallCanReach(p, BallGet(state->mUnknown43)))
        result = 0;
    return result;
}

extern "C" void LooseBallSteer(Object_80039F5C *p, LooseBallBlock_t *state, Vector_80039F5C *pTarget) {
    Vector_80039F5C delta;
    delta.mX = CLAMP(pTarget->mX, -fn_80178A08(), fn_80178A08());
    delta.mY = CLAMP(pTarget->mY, -fn_80178A44(), fn_80178A44());
    delta.mZ = pTarget->mZ;
    fn_802276B4(&delta, &delta, &p->mMotion.mPos);
    float dist = fn_802270D4(&delta);
    state->mUnknown36 = fn_801CFE40(delta.mY, delta.mX);
    if (LooseBallCanChase(p, state)) {
        state->mUnknown32 = 0.72f;
        if (dist < 3.0f) {
            if (dist < 0.75f) {
                state->mUnknown32 = 0.0f;
                p->mMotion.mUnknown28 = 0.0f;
            } else {
                state->mUnknown32 = state->mUnknown32 * (dist / 3.0f);
                state->mUnknown32 = state->mUnknown32 < 0.4f ? 0.4f : state->mUnknown32;
            }
        }
    } else {
        state->mUnknown32 = 0.4f;
        if (dist < 15.0f) {
            if (dist < 10.0f)
                state->mUnknown36 = (state->mUnknown36 + 0x800000) & 0xFFFFFF;
            else
                state->mUnknown32 = 0.0f;
        }
    }
}

extern "C" void LooseBallBroadcast(int id) {
    Message_800F01CC message;
    Vector_80039F5C pos;
    Vector_80039F5C delta;
    int owner;
    Object_80039F5C *pOther;
    if (fn_801787A0())
        return;
    Ball_t *pBall = BallGet(id);
    BallStateGet(pBall, &owner);
    if (BallGetLandingPoint(pBall, &pos))
        PlyrFindNearest(&pos, 0, fn_80178360());
    StyleTrackerRefreshUserPlayers();
    for (unsigned char team = 0; team <= 1; team++) {
        int count = fn_80178D70(team);
        for (int i = 0; i < count; i++) {
            pOther = PlyrGet(team, (unsigned char)i);
            fn_802276B4(&delta, &pos, &pOther->mMotion.mPos);
            fn_801C1F94(&message, 0, 4);
            message.mId = 57;
            message.mUnknown1[0] = id;
            int value = fn_8009F0B8(pOther, 0x3C71C7) ? _LooseBall_iPriorityFacing : _LooseBall_iPriorityBase;
            value += (unsigned int)(fn_802270A4(&delta) * _LooseBall_fPriorityPerDist);
            value += (int)((255 - pOther->mRatings[0]) * _LooseBall_fPriorityPerRating);
            value += fn_802372EC(0, _LooseBall_iPriorityRandom);
            if ((pOther->mFlags & 0x400) || !fn_801486A0())
                value = 0;
            switch (pOther->mpState->mId) {
            case 0:
            case 11:
            case 23:
            case 24:
            case 28:
            case 68:
            case 90:
                value = 0;
                break;
            }
            if (pOther->mQueue[0].mId != message.mId && (unsigned char)pOther->mUnknown3044[0] != message.mId) {
                if (LooseBallCanQueueMessage(pOther))
                    PlyrSetPendingMsg(pOther, &message, value);
                else
                    fn_800F01CC(0, pOther->mpState, &message, (Object_80039F5C *)&pOther);
            }
        }
    }
}

extern "C" int LooseBallEnter(Object_80039F5C *p) {
    LooseBallBlock_t *state = (LooseBallBlock_t *)&p->mUnknown336;
    state->mUnknown40 = 0xFFFF;
    state->mUnknown45 = -1;
    state->mUnknown42 = state->mUnknown28 = 0;
    state->mUnknown43 = p->mpState->mUnknown1;
    if (p->mIdBytes[3] == 1) {
        fn_8011E3EC(p, 0);
        if (p->mIdBytes[2] == fn_80178308()) {
            fn_8011E240(p);
        } else {
            Object_80039F5C *pOther = fn_8009BCE8(&p->mUnknown1036);
            if (pOther)
                fn_8011E240(pOther);
        }
    }
    state->mUnknown44 = -1;
    fn_8009A8D4(state->mUnknown48);
    return 0;
}

extern "C" int LooseBallExit(Object_80039F5C *p) {
    LooseBallBlock_t *state = (LooseBallBlock_t *)&p->mUnknown336;
    if (state->mUnknown40 != 0xFFFF) {
        state->mUnknown42 = 1;
        return 0;
    }
    p->mFlags &= ~8;
    return 1;
}

extern "C" int LooseBallUpdate(Object_80039F5C *p) {
    LooseBallBlock_t *state = (LooseBallBlock_t *)&p->mUnknown336;
    Vector_80039F5C target;
    Vector_80039F5C predicted;
    Vector_80039F5C ballPos;
    Vector_80039F5C delta;
    Message_800F01CC message;
    Vector_80039F5C velocity;
    Vector_80039F5C left;
    Vector_80039F5C right;
    int owner;
    float distance;
    int result = 0;
    int found = 0;
    fn_8010A2DC(p, 0, -1);
    Ball_t *pBall = BallGet(state->mUnknown43);
    int kind = BallStateGet(pBall, &owner);
    BallGetPosition(pBall, &ballPos);
    BallGetVelocity(pBall, &velocity);
    if (ballPos.mZ > 3.15f) {
        fn_8013AA00(pBall, 2.65f, 0, &target);
        target.mZ = 2.65f;
    } else {
        fn_8013AA00(pBall, 0.0f, 0, &ballPos);
        ballPos.mZ = 0.0f;
        distance = fn_8022785C(&ballPos, &p->mMotion.mPos);
        LooseBallPredictPos(&target, pBall, distance * _LooseBall_fLeadScale);
    }
    if (state->mUnknown40 != 0xFFFF) {
        if (fn_801BE648(p->mpUnknown792) != 48) {
            result = 1;
            goto done;
        }
        if (kind == 5) {
            if ((state->mUnknown24 -= 1.0f) > 0.0f) {
                LooseBallPredictPos(&predicted, pBall, state->mUnknown24);
                fn_802276B4(&delta, &predicted, &state->mUnknown12);
                distance = fn_802270A4(&delta);
                if (distance > 0.05f) {
                    fn_80227350(&state->mUnknown0, &delta, 0.05f / (state->mUnknown24 * distance));
                    fn_80227350(&state->mUnknown12, &delta, 0.05f / distance);
                } else {
                    fn_80227350(&state->mUnknown0, &delta, 1.0f / state->mUnknown24);
                    state->mUnknown12.mX = predicted.mX;
                    state->mUnknown12.mY = predicted.mY;
                    state->mUnknown12.mZ = predicted.mZ;
                }
                state->mUnknown0.mZ = 0.0f;
                fn_8022765C(&p->mMotion.mPos, &p->mMotion.mPos, &state->mUnknown0);
            } else if (!fn_801787A0()) {
                fn_8009BF5C(p, CharSkelGetJointByName(p->mpUnknown4->mpUnknown100, "LFOOTBALL"), &left, 0);
                fn_8009BF5C(p, CharSkelGetJointByName(p->mpUnknown4->mpUnknown100, "RFOOTBALL"), &right, 0);
                float reach = (p->mFlags & 0x400) ? 0.4f : 0.15f;
                if (fn_8022785C(&target, &right) < reach || fn_8022785C(&target, &left) < reach)
                    BallStateCheckPlayerHit(pBall, p, 4);
            }
        }
        switch (p->mUnknown9[0]) {
        default:
            state->mUnknown40 = 0xFFFF;
            if (kind == 5 && LooseBallFindAnim(p, state, pBall, 3, 0))
                state->mUnknown40 = LooseBallStartAnim(p, 0, 0, 0);
            if (state->mUnknown40 == 0xFFFF) {
                fn_801C1F94(&message, 0, 4);
                message.mId = 11;
                message.mUnknown1[0] = p->mUnknown9[0];
                fn_800F00D4(0, p->mpState, &message, p);
            }
            break;
        case 1:
            if (p->mFlags & 4) {
                p->mFlags &= ~4;
                state->mUnknown40 = 0xFFFF;
                state->mUnknown28 = 0;
            }
            break;
        case 8:
            break;
        }
        if (fn_801787A0() && p->mIdBytes[3] == 1 && (p->mFlags & 0x1000)) {
            p->mFlags &= ~0x1000;
            Ball_t *pHeld = BallFindHeldBy(p);
            if (pHeld)
                BallReleaseStill(pHeld, 5, 0);
        }
        goto done;
    }
    if (p->mFlags & 0x800) {
        if (p->mUnknown9[0] != 1 && p->mUnknown9[0] != 8) {
            fn_801C1F94(&message, 0, 4);
            message.mId = 11;
            message.mUnknown1[0] = p->mUnknown9[0];
            fn_800F00D4(0, p->mpState, &message, p);
        }
        result = 0;
        goto done;
    }
    if (state->mUnknown42 == 0) {
        if (kind == 4 || kind == 5) {
            if (!fn_801787A0() && velocity.mZ < 0.0f) {
                int handle = fn_80099734(p, pBall, 0, 3, state->mUnknown48, 1, 0, 0, fn_8009A77C(p), 120.0f);
                if (handle != 0x1FFFFFFF && fn_80099F04(p, handle, BallGetIndex(pBall)) == 1) {
                    result = 0;
                    goto done;
                }
            }
            if (--state->mUnknown28 <= 0 || (p->mFlags & 0x400)) {
                state->mUnknown28 = (255 - p->mRatings[0]) / 12;
                int type = 2;
                if (LooseBallGetEdge(pBall) != 5)
                    type = 5;
                int team = p->mIdBytes[2] ^ 1;
                Object_80039F5C *pOther = fn_801244F0(p, team, 0, fn_80178D18(team), &distance, 0);
                if (pOther) {
                    Point_8017886C offset;
                    fn_80227690(&offset, &ballPos, &pOther->mMotion.mPos);
                    int angle = fn_801CFE40(offset.mY, offset.mX);
                    if (pOther->mMotion.mUnknown28 != 0.0f && distance < _LooseBall_fThreatRange &&
                        MathAngleDiff(angle, pOther->mMotion.mUnknown32) < (int)(_LooseBall_fThreatAngle * 46603.37890625f) &&
                        !(p->mFlags & 0x4000))
                        type = 1;
                }
                LooseBallSteer(p, state, &target);
                if (LooseBallFindAnim(p, state, pBall, type, 0))
                    state->mUnknown40 = LooseBallStartAnim(p, 0, 0, 0);
                else if ((fn_801486A0() || !(p->mFlags & 0x400)) && LooseBallTryEngage(p, pBall)) {
                    result = 0;
                    goto done;
                }
            } else if ((fn_801486A0() || !(p->mFlags & 0x400)) && LooseBallTryEngage(p, pBall)) {
                result = 0;
                goto done;
            }
            int *pAnimation = _LooseBall_aiTrimKeys;
            for (unsigned int i = 0; i <= 3; pAnimation++, i++) {
                if (fn_801BE648(p->mpUnknown792) == *pAnimation) {
                    found = 1;
                    break;
                }
            }
            if (state->mUnknown40 == 0xFFFF && (!(p->mFlags & 0x4000) || (((p->mFlags >> 14) & 1) && !found)) &&
                (fn_801486A0() || p->mUnknown8 == 0xFF)) {
                p->mUnknown512.mUnknown14 = 1;
                p->mUnknown512.mUnknown8 = state->mUnknown36;
                p->mUnknown512.mUnknown4 = state->mUnknown36;
                p->mUnknown512.mUnknown0 = state->mUnknown32;
            }
            goto done;
        }
        if (pBall == BallGetCurrent()) {
            Object_80039F5C *pHolder = BallGetHolder(pBall);
            if (pHolder) {
                if (pHolder != p) {
                    if (fn_801486A0()) {
                    if (pHolder->mIdBytes[2] == p->mIdBytes[2]) {
                        fn_801C1F94(&message, 0, 4);
                        message.mId = 33;
                        fn_800F053C(0, p->mpState, &message, p);
                    } else {
                        fn_801C1F94(&message, 0, 4);
                        message.mId = 2;
                        fn_800F053C(0, p->mpState, &message, p);
                    }
                    } else {
                        fn_801C1F94(&message, 0, 4);
                        message.mId = 97;
                        fn_800F053C(0, p->mpState, &message, p);
                    }
                } else {
                    fn_801C1F94(&message, 0, 4);
                    message.mId = 1;
                    fn_800F053C(0, p->mpState, &message, p);
                }
            } else if (fn_801486A0()) {
                fn_801C1F94(&message, 0, 4);
                message.mId = 2;
                fn_800F053C(0, p->mpState, &message, p);
            } else {
                fn_801C1F94(&message, 0, 4);
                message.mId = 97;
                fn_800F053C(0, p->mpState, &message, p);
            }
        }
    }
    p->mUnknown512.mUnknown14 = 1;
    p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = p->mMotion.mUnknown32;
    p->mUnknown512.mUnknown0 = p->mMotion.mUnknown28 / gPlyrMoveFwdSpeed;
    result = 1;
done:
    return result;
}

extern "C" int LooseBallIsIdleOrKind2(Object_80039F5C *p) {
    LooseBallBlock_t *state = (LooseBallBlock_t *)&p->mUnknown336;
    int result = 1;
    if (state->mUnknown40 != 0xFFFF)
        result = state->mUnknown45 == 2;
    return result;
}

extern "C" int LooseBallAnimEvent(Table_80089904 *table, unsigned short key, void *record, void *entries,
                            Object_80039F5C *p, int phase) {
    if (phase == 0) {
        LooseBallBlock_t *state = (LooseBallBlock_t *)&p->mUnknown336;
        fn_801BA2A8(record, entries, table->mEntries[state->mUnknown44].mUnknown0,
                    table->mEntries[state->mUnknown44].mUnknown2, key, p, 1.0f);
    }
    return 0;
}

extern "C" int LooseBallInput(Object_80039F5C *p) {
    if (((LooseBallBlock_t *)&p->mUnknown336)->mUnknown40 != 0xFFFF)
        return 0;
    Input_800B6D34 input;
    fn_800B6D34(p, &input);
    if (input.mBytes92[0] & 1) {
        LooseBallUserRecover(p);
        return 0;
    }
    int value;
    BallStateGet(BallGetCurrent(), &value);
    return fn_800B78DC(p);
}

extern "C" int LooseBallIsIdle(Object_80039F5C *p) {
    return ((LooseBallBlock_t *)&p->mUnknown336)->mUnknown40 == 0xFFFF;
}
