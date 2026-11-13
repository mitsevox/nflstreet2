/* Player states run through the state handler table. The turn-to-play
   state plays a turning animation towards the ball, the ball carrier or the
   player's huddle spot. The handoff state lets the ball carrier give the
   ball to a teammate next to him, with a paired two-player animation when
   one fits. The huddle states walk every player to his spot on a ring
   around the huddle point and hold the first player of the formation
   there. */

#include "engine/cu_801B9F00.h"
#include "game/Command_800CEE74.h"
#include "game/Block_801BE60C.h"
#include "game/Input_800B6D34.h"
#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/Query_800CE770.h"
#include "game/Record_800B15FC.h"
#include "game/AudmonEvent.h"
#include "game/Ball.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_800F06F4.h"
#include "game/fn_801C1F94.h"
#include "game/PlayBookDb.h"
#include "game/PlaySet.h"
#include "game/fn_80178D18.h"
#include "game/fn_802270D4.h"
#include "game/fn_8022781C.h"
#include "game/fn_80227638.h"
#include "game/fn_802372EC.h"
#include <math.h>
#include "game/fn_801BE60C.h"
#include "game/fn_800B65A0.h"
#include "game/fn_801BA2A8.h"
#include "game/Record_800CE608.h"

/* Player block at +336 in the turn-to-play state. */
struct TurnToPlayBlock_t {
    int mUnknown0;
    unsigned char mUnknown4;
};

/* Player block at +336 in the handoff state. */
struct HandoffBlock_t {
    int mUnknown0;
    unsigned short mUnknown4;
    unsigned char mUnknown6;
    unsigned char mUnknown7;
    unsigned int mUnknown8;
};

/* Player block at +336 in the huddle states. */
struct HuddleBlock_t {
    short mUnknown0;
    unsigned char mUnknown2;
    char mUnknown3[5];
    Point_8017886C mUnknown8;
    int mUnknown16;
    char mUnknown20[4];
    float mUnknown24;
    char mUnknown28[20];
    unsigned char mUnknown48;
    unsigned char mUnknown49;
    unsigned char mUnknown50;
    char mUnknown51[1];
    int mUnknown52;
};

extern "C" {
static unsigned char _Handoff_auHuddleSlots[8] = {0, 1, 2, 3, 4, 5, 6, 0};
static float _Handoff_fHuddleWalkSpeed = 0.3f;
extern float gPlyrMoveFwdSpeed;
void fn_80227690(void *pOut, void *pA, void *pB);
int fn_801CFE40(float y, float x);
int MathAngleDiff(int a, int b);
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
Object_80039F5C *fn_800B6544(int index);
void fn_800B67FC(Object_80039F5C *p, Object_80039F5C *pOther);
int fn_800B7FE8(Object_80039F5C *p);
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
void fn_800F05E4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
void fn_8010AEC4(Object_80039F5C *p);
void fn_80227384(void *pOut, void *pIn, int angle);
void fn_800D7A0C(Object_80039F5C *p, int a);
int fn_8011F4C8(void);
float fn_8011F4D4(void);
int fn_800CE590(Query_800CE770 *pQuery, Record_800CE608 *pA, Record_800CE608 *pB);
void fn_800CE608(Object_80039F5C *p, Record_800CE608 *pRecord);
void fn_80143E14(Object_80039F5C *p, Object_80039F5C *pOther);
void fn_80227538(Point_8017886C *pOut, int angle, float length);
void fn_8011E1BC(Object_80039F5C *p, Object_80039F5C *pOther, int a, int b);
void fn_8011E3EC(Object_80039F5C *p, int a);
int fn_8010A2DC(Object_80039F5C *p, int a, short b);
int fn_801486A0(void);
void fn_80143EBC(Object_80039F5C *p, Object_80039F5C *pOther);
int fn_80178308(void);
int fn_80178320(void);
int fn_801BE068(void *a, void *b, void *c, unsigned short d, float f, void *e);
float fn_80237260(int stream);
void fn_8009BD60(Object_80039F5C *p);
void TurnToPlayStartAnim(Object_80039F5C *p, int a, int b);
float fn_80178A68(Point_8017886C *pPos);
int fn_800A2178(void);
int fn_80178348(void);
int fn_801787A0(void);
int BallStateGet(Ball_t *pBall, int *pOut);
int fn_801BA6B0(Record_800D81C8 *entry);
void fn_801BA6BC(Record_800D81C8 *entry, int value);
extern float _Handoff_fTurnCloseRange;
extern unsigned char _Handoff_auTurnDirections[8];
void HuddleSetSpot(HuddleBlock_t *pState, Object_80039F5C *p, Point_8017886C *pPoint, int value);
void HuddleArrive(Object_80039F5C *p, HuddleBlock_t *pState);
float fn_801CFB94(int angle);
void fn_800DBC4C(Object_80039F5C *p, int angle, float value);
int PassIconsAreShown(void);
int fn_8011F2C4(void);
void fn_800A5A8C(int a, void *pA, void *pB);
void fn_800A60D8(Object_80039F5C *p, Object_80039F5C *pOther);
int fn_800E1044(Object_80039F5C *p, Vector_80039F5C *pTarget);
int fn_800FF094(Object_80039F5C *p);
int fn_800CB708(Object_80039F5C *p, int *pOut, Point_8017886C point, int angle, int a);
int fn_800CB580(Object_80039F5C *p, int *pOut, Point_8017886C point, int angle, int a);
void fn_800CBB00(Object_80039F5C *p, int value, Point_8017886C point, int angle, int a);
void HuddleGetSpot(Point_8017886C *pOut, int *pFacing, Object_80039F5C *p, int value);
int HuddleMoveUpdate(Object_80039F5C *p);
int fn_800DC080(Object_80039F5C *p);
Point_8017886C fn_8017808C(void);
float fn_80178A2C(void);
void fn_800FF598(HuddleBlock_t *pState, Object_80039F5C *p, Point_8017886C *pPoint, int value, float scale);
int fn_8011F1A4(void);
PlayBookFormation_t *PlayBookGetFormation(int team);
Point_8017886C fn_80177FE0(void);
}

#if defined(DECOMP_COMPARE)
extern "C" int TurnToPlayPickVariant(Object_80039F5C *p) {
    if (fn_80178A68((Point_8017886C *)&p->mMotion.mPos) < _Handoff_fTurnCloseRange)
        return 5;
    int mode = fn_800A2178();
    if (p->mIdBytes[2] == fn_80178348()) {
        switch (mode) {
        case 0:
        case 1:
        case 3:
        case 13:
            return 2;
        case 2:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 14:
        case 15:
        case 16:
        case 17:
            return 3;
        }
    } else {
        switch (mode) {
        case 7:
        case 8:
        case 9:
        case 10:
        case 16:
            return 4;
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 17:
            return 3;
        }
    }
    return 3;
}

extern "C" int TurnToPlayPickAnim(Object_80039F5C *p, int value) {
    return fn_801787A0() == 0 ? 208 : 209;
}

extern "C" unsigned char TurnToPlayPickDirection(Object_80039F5C *p) {
    Point_8017886C delta;
    int angle;
    Vector_80039F5C pos;
    if (fn_801787A0()) {
        HuddleGetSpot(&delta, &angle, p, 0);
        fn_80227690(&delta, &delta, &p->mMotion.mPos);
    } else if (p->mIdBytes[2] == fn_80178320() || p->mpState[1].mId == 33 || p->mpState[1].mId == 31) {
        Object_80039F5C *pCarrier = BallGetCurrentHolder();
        if (!pCarrier)
            goto ball;
        fn_80227538(&delta, pCarrier->mMotion.mUnknown32, pCarrier->mMotion.mUnknown28 * 15.0f);
        fn_80227638(&delta, &delta, &pCarrier->mMotion.mPos);
        fn_80227690(&delta, &delta, &p->mMotion.mPos);
    } else if (BallStateGet(BallGetCurrent(), 0) == 5) {
    ball:
        BallGetPosition(BallGetCurrent(), &pos);
        fn_80227690(&delta, &pos, &p->mMotion.mPos);
    } else {
        goto facing;
    }
    angle = (fn_801CFE40(delta.mY, delta.mX) - p->mMotion.mFacing) & 0xFFFFFF;
    return _Handoff_auTurnDirections[((angle + 0x100000) >> 21) & 7];
facing:
    if (!fn_801486A0())
        angle = (fn_801CFE40(p->mMotion.mPos.mY, p->mMotion.mPos.mX) + 0x800000) & 0xFFFFFF;
    else
        angle = (0x400000 - p->mMotion.mFacing) & 0xFFFFFF;
    return _Handoff_auTurnDirections[((angle + 0x100000) >> 21) & 7];
}

extern "C" void TurnToPlayStartAnim(Object_80039F5C *p, int kind, int flag) {
    int mirror = 0;
    int alternate = 0;
    fn_8009BD60(p);
    p->mUnknown512.mUnknown14 = mirror;
    if (fn_801BA568(p->mpUnknown796, p->mpUnknown800, fn_801BE648(p->mpUnknown792))) {
        if (fn_801BE648(p->mpUnknown792) == 192) {
            mirror = p->mUnknown776 == 1;
        } else {
            Record_800D81C8 *pEntries = p->mpUnknown800;
            mirror = fn_801BA6B0(&pEntries[fn_801BA5A8(p->mpUnknown796, pEntries, fn_801BE648(p->mpUnknown792), 0)]);
        }
    }
    if (kind == 3)
        p->mUnknown1008.mUnknown1 = 3;
    else
        p->mUnknown1008.mUnknown1 = 2;
    int animation = TurnToPlayPickAnim(p, kind);
    if (animation == 209) {
        p->mUnknown1008.mUnknown2 = TurnToPlayPickVariant(p);
        if (p->mUnknown1008.mUnknown2 == 5) {
            alternate = 1;
            if (!flag && BallGetCurrentHolder() == p)
                flag = 1;
        }
    }
    if (animation == 208 || alternate) {
        int direction = TurnToPlayPickDirection(p);
        if (mirror) {
            switch (direction) {
            case 7:
                direction = 2;
                break;
            case 2:
                direction = 7;
                break;
            case 6:
                direction = 3;
                break;
            case 5:
                direction = 4;
                break;
            case 4:
                direction = 5;
                break;
            case 3:
                direction = 6;
                break;
            }
        }
        if (alternate)
            p->mUnknown1011 = direction;
        else
            p->mUnknown1008.mUnknown2 = direction;
    }
    if (p == BallGetCurrentHolder() && !flag)
        p->mUnknown1008.mUnknown0 = 1;
    else
        p->mUnknown1008.mUnknown0 = 2;
    fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, animation, 1.0f, p);
    if (fn_801BA568(p->mpUnknown796, p->mpUnknown800, animation)) {
        Record_800D81C8 *pEntries = p->mpUnknown800;
        int index = fn_801BA5A8(p->mpUnknown796, pEntries, animation, 0);
        if (mirror) {
            Record_800D81C8 *pEntry = &pEntries[index];
            fn_801BA6BC(pEntry, fn_801BA6B0(pEntry) == 0);
        }
    }
    p->mUnknown9[0] = 1;
    if (flag)
        p->mFlags |= 0x1000;
}
#endif

extern "C" int TurnToPlayEnter(Object_80039F5C *p) {
    TurnToPlayBlock_t *state = (TurnToPlayBlock_t *)&p->mUnknown336;
    int flag = p->mpState->mUnknown1 == 4 || p->mpState->mUnknown1 == 5;
    if (BallGetCurrentHolder() == p)
        fn_8010AEC4(p);
    if (fn_800AD9B4() == 4) {
        state->mUnknown0 = p->mpState->mUnknown2;
        state->mUnknown4 = 1;
    } else {
        state->mUnknown0 = p->mpState->mUnknown2;
        state->mUnknown4 = 1;
    }
    if (p->mIdBytes[3] == 1)
        p->mFlags &= ~0x1000;
    TurnToPlayStartAnim(p, p->mpState->mUnknown1, flag);
    p->mUnknown772 = 1.0f;
    return 0;
}

extern "C" int TurnToPlayUpdate(Object_80039F5C *p) {
    int result = 0;
    if (p->mUnknown336 != 0) {
        p->mUnknown336--;
        return 0;
    }
    fn_8010A2DC(p, 0, 0);
    if (p->mIdBytes[3] == 1 && (p->mFlags & 0x1000)) {
        p->mFlags &= ~0x1000;
        Ball_t *pBall = BallFindHeldBy(p);
        if (pBall && fn_801486A0())
            BallReleaseStill(pBall, 5, 0);
    }
    int kind = p->mUnknown9[0];
    unsigned int flags = p->mFlags;
    if (kind == 8 || (flags & 4)) {
        p->mUnknown9[0] = 1;
        p->mUnknown512.mUnknown14 = 1;
        p->mFlags = flags & ~0x10804;
        p->mUnknown512.mUnknown8 = p->mMotion.mUnknown32;
        p->mUnknown512.mUnknown4 = p->mMotion.mUnknown32;
        p->mUnknown512.mUnknown0 = p->mMotion.mUnknown28 / gPlyrMoveFwdSpeed;
        result = 1;
    } else if (kind != 1) {
        TurnToPlayStartAnim(p, kind, 0);
    }
    return result;
}

extern "C" int TurnToPlayExit() {
    return 0;
}

extern "C" int TurnToPlayNotify() {
    return 0;
}

extern "C" int TurnToPlayInput(Object_80039F5C *p) {
    int mode = fn_800AD9B4();
    int index = fn_800B65A0(p->mIdBytes[2]);
    if (p->mIdBytes[2] == fn_80178320() || mode == 3
        || (mode == 2 && index != 255 && fn_800B6544(index) != p))
        return fn_800B7FE8(p);
    return 0;
}

extern "C" float HandoffPickSide(Object_80039F5C *p, HandoffBlock_t *state) {
    float speed = 1.0f;
    if (BallFindHeldBy(p)) {
        Object_80039F5C *pOther = fn_8009BCE8(&state->mUnknown0);
        int sideFlag = 0;
        int wideFlag = 0;
        Point_8017886C delta;
        fn_80227690(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
        int angle = fn_801CFE40(delta.mY, delta.mX);
        if (fn_8011F1A4() && p->mUnknown2914 == 0) {
            float x = fn_8011F4D4();
            sideFlag = x > p->mMotion.mPos.mX;
            wideFlag = fabsf(x - p->mMotion.mPos.mX) < fabsf(x - pOther->mMotion.mPos.mX);
            wideFlag |= p->mMotion.mPos.mY - pOther->mMotion.mPos.mY > 5.0f;
            wideFlag |= (unsigned int)fn_8011F4C8() <= 3;
        } else {
            if (p->mUnknown2914 == 0)
                angle = (angle - 0x400000) & 0xFFFFFF;
            else
                angle = (angle - p->mMotion.mFacing) & 0xFFFFFF;
            if (angle > 0x800000)
                sideFlag = 1;
            if (angle > 0x600000 && angle < 0xA00000)
                wideFlag = 1;
        }
        state->mUnknown7 = sideFlag ? 6 : 3;
        switch (state->mUnknown6) {
        case 0:
            break;
        case 1:
            if (!sideFlag)
                speed = 1.6f;
            sideFlag = 1;
            wideFlag = 1;
            break;
        case 2:
            if (sideFlag == 1)
                speed = 1.6f;
            sideFlag = 0;
            wideFlag = 1;
            break;
        }
        switch (state->mUnknown8) {
        case 2:
        case 3:
        case 8:
        case 9:
            state->mUnknown7 = 6;
            sideFlag = 1;
            break;
        case 4:
        case 5:
        case 10:
        case 11:
            state->mUnknown7 = 3;
            sideFlag = 0;
            break;
        }
        if (sideFlag)
            state->mUnknown7 = wideFlag ? 5 : 6;
        else
            state->mUnknown7 = wideFlag ? 4 : 3;
    }
    return speed;
}

extern "C" int HandoffIsMirrored(Object_80039F5C *p, HandoffBlock_t *state) {
    int result = 0;
    unsigned int kind = state->mUnknown8;
    if (kind == 1 || kind == 3 || kind == 5 || kind == 7 || kind == 9 || kind == 11) {
        if (kind >= 6 && kind <= 11)
            result = 1;
        if (!result) {
            int pending = fn_800F06F4(0, &p->mpState[1], 26, 0xFFFF) != 0xFFFF;
            if (pending)
                result = 1;
        }
        if (!result && fn_800F06F4(0, p->mpState, 18, 0xFFFF) != 0xFFFF) {
            if (p->mUnknown2913 == 1) {
                if (state->mUnknown7 == 3 || state->mUnknown7 == 4)
                    result = 1;
            } else if (state->mUnknown7 == 5 || state->mUnknown7 == 6) {
                result = 1;
            }
        }
    }
    return result;
}

extern "C" void HandoffStartAnim(Object_80039F5C *p, HandoffBlock_t *state, unsigned int mode) {
    fn_8009BD60(p);
    unsigned int kind = state->mUnknown8;
    float speed = 1.0f;
    unsigned short animation;
    switch (kind) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 15:
        speed = HandoffPickSide(p, state);
        animation = 77;
        switch (mode) {
        case 1:
            p->mUnknown1008.mUnknown1 = 1;
            break;
        case 2:
            p->mUnknown1008.mUnknown1 = 2;
            break;
        case 3:
            if (kind == 2 || kind == 4 || kind == 0 || p->mpState[1].mId != 18)
                p->mUnknown1008.mUnknown1 = 3;
            else
                p->mUnknown1008.mUnknown1 = 4;
            break;
        }
        p->mUnknown1008.mUnknown0 = state->mUnknown7;
        if (state->mUnknown4 != 1) {
            if (state->mUnknown7 == 5)
                p->mUnknown1008.mUnknown0 = 6;
            else if (state->mUnknown7 == 4)
                p->mUnknown1008.mUnknown0 = 3;
        }
        switch (p->mUnknown2913) {
        case 0:
            p->mUnknown1008.mUnknown2 = 1;
            break;
        case 1:
            p->mUnknown1008.mUnknown2 = 2;
            break;
        }
        break;
    case 14:
        animation = 34;
        if (fn_801486A0() == 3)
            p->mUnknown1008.mUnknown0 = 5;
        else if (fn_801486A0() == 2)
            p->mUnknown1008.mUnknown0 = 6;
        else
            p->mUnknown1008.mUnknown0 = 1;
        break;
    default:
        animation = 77;
        break;
    }
    if (HandoffIsMirrored(p, state)) {
        if (state->mUnknown7 == 5 || state->mUnknown7 == 6)
            fn_800D7A0C(p, 2);
        else
            fn_800D7A0C(p, 1);
    } else {
        if (state->mUnknown7 == 5 || state->mUnknown7 == 6)
            fn_800D7A0C(p, 1);
        else
            fn_800D7A0C(p, 2);
    }
    fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, animation, 1.0f, p);
    unsigned char count = fn_801BA568(p->mpUnknown796, p->mpUnknown800, animation);
    for (unsigned char i = 0; i < count; i++)
        p->mpUnknown800[fn_801BA5A8(p->mpUnknown796, p->mpUnknown800, animation, i)].mUnknown20 = (int)(speed * 16777216.0f);
}

extern "C" int HandoffTryPairAnim(Object_80039F5C *p, Object_80039F5C *pOther, HandoffBlock_t *state) {
    int angle = 0x155555;
    if (BallFindHeldBy(p) && pOther->mpState->mId == 27) {
        int id;
        float speed;
        if (state->mUnknown8 == 15) {
            Point_8017886C delta;
            fn_80227690(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
            int heading = (fn_801CFE40(delta.mY, delta.mX) - p->mMotion.mFacing) & 0xFFFFFF;
            speed = 0.9f;
            if (heading > 0x800000) {
                state->mUnknown6 = 6;
                id = 30;
            } else {
                state->mUnknown6 = 3;
                id = 31;
            }
        } else if (state->mUnknown8 == 6 || state->mUnknown8 == 8 || state->mUnknown8 == 10) {
            id = 202;
            speed = 1.5f;
            angle = 0x200000;
        } else if (state->mUnknown8 == 7 || state->mUnknown8 == 9 || state->mUnknown8 == 11) {
            id = 200;
            speed = 1.5f;
            angle = 0x200000;
        } else {
            switch (state->mUnknown7) {
            case 3:
            case 4:
                id = 30;
                break;
            case 5:
            case 6:
                id = 31;
                break;
            default:
                id = 30;
                break;
            }
            if (state->mUnknown8 == 12 || !p->mUnknown560.mFlags.mBytes[0])
                speed = 0.85f;
            else
                speed = 0.85f;
        }
        Query_800CE770 query;
        Record_800CE608 a;
        Record_800CE608 b;
        fn_800CE770(&query);
        query.mUnknown52 = id;
        query.mUnknown36 = angle;
        query.mUnknown44 = speed;
        query.mpUnknown0 = p;
        query.mpUnknown4 = pOther;
        if (fn_800CE590(&query, &a, &b)) {
            fn_80143E14(p, pOther);
            fn_80143E14(pOther, p);
            fn_800CE608(p, &a);
            fn_800CE608(pOther, &b);
            p->mUnknown512.mUnknown14 = 0;
            pOther->mUnknown512.mUnknown14 = 0;
            p->mFlags &= ~4;
            p->mFlags &= ~1;
            return 1;
        }
    }
    return 0;
}

extern "C" int HandoffSteer(Object_80039F5C *p, Object_80039F5C *pOther, HandoffBlock_t *state) {
    int result;
    Ball_t *pBall = BallFindHeldBy(p);
    if (pBall) {
        result = 2;
        float speed = 1.0f;
        float x = p->mMotion.mPos.mX;
        float otherX = pOther->mMotion.mPos.mX;
        float otherVelX = pOther->mMotion.mUnknown40;
        int adjust = 1;
        int id;
        int turn;
        Vector_80039F5C ballPos;
        Point_8017886C delta;
        BallGetPosition(pBall, &ballPos);
        fn_80227690(&delta, &pOther->mMotion.mPos, &ballPos);
        int angle = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
        float distance = fn_802270A4(&delta);
        if (fn_8011F1A4() && p->mUnknown2914 == 0) {
            id = p->mpState->mUnknown2;
            if (id == 0 || id == 2 || id == 4 || id == 6 || id == 8 || id == 10) {
                Point_8017886C point;
                point.mX = fn_8011F4D4();
                point.mY = fn_80177FE0().mY;
                fn_80227690(&point, &point, &p->mMotion.mPos);
                int pointAngle = fn_801CFE40(point.mY, point.mX) & 0xFFFFFF;
                if (state->mUnknown8 == 12) {
                    adjust = 0;
                    if (state->mUnknown7 == 6) {
                        angle -= 0x71C71;
                        if (p->mUnknown2913 == 1)
                            angle -= 0x71C71;
                    } else {
                        angle += 0x71C71;
                        if (p->mUnknown2913 == 0)
                            angle += 0x71C71;
                    }
                    angle &= 0xFFFFFF;
                }
                if (adjust) {
                    turn = MathAngleDiff(angle, pointAngle);
                    turn = (int)(turn * fn_801CFB94(turn / 2));
                    if (turn > 0x38E38) {
                        if (p->mMotion.mFacing - angle <= 0x38E37) {
                            if ((otherX <= x + 0.2f && otherVelX > 0.0f)
                                || (otherX >= x - 0.2f && otherVelX < 0.0f))
                                turn = (int)(turn * 0.33333334f);
                        }
                        if (((pointAngle - p->mMotion.mFacing) & 0xFFFFFF) <= 0x7FFFFF)
                            angle += turn;
                        else
                            angle -= turn;
                    }
                }
            }
        } else {
            speed = 0.75f;
        }
        angle &= 0xFFFFFF;
        float range;
        id = p->mpState->mUnknown2;
        if (id == 1 || id == 3 || id == 5 || state->mUnknown8 == 12)
            range = 1.5f;
        else if (state->mUnknown8 == 7)
            range = 1.25f;
        else
            range = 1.5f;
        if (distance < range) {
            turn = MathAngleDiff(pOther->mMotion.mFacing, p->mMotion.mFacing);
            if (turn > 0x400000) {
                float scale;
                switch (p->mpState->mUnknown2) {
                case 0:
                case 2:
                case 4:
                case 6:
                case 8:
                case 10:
                case 13:
                    scale = 1.0f - distance * 0.6666667f;
                    result = 3;
                    break;
                case 1:
                case 3:
                case 5:
                case 7:
                case 9:
                case 11:
                    scale = 1.0f - distance * 0.16666667f;
                    result = 3;
                    break;
                default:
                    scale = 0.0f;
                    break;
                }
                scale *= fn_801CFB94(turn - 0x400000);
                speed -= scale;
            }
            fn_80143E14(p, pOther);
            fn_80143E14(pOther, p);
        }
        if (speed < 0.0f)
            speed = 0.0f;
        unsigned int kind = state->mUnknown8;
        if (kind == 15 || kind == 12) {
            if (distance > 4.0f && kind == 12) {
                fn_800DBC4C(p, angle, speed);
            } else {
                speed = distance * 0.25f;
                p->mUnknown512.mUnknown0 = speed;
                p->mUnknown512.mUnknown8 = angle;
                p->mUnknown512.mUnknown4 = angle;
                p->mUnknown512.mUnknown14 = 1;
            }
        } else {
            p->mUnknown512.mUnknown0 = speed;
            p->mUnknown512.mUnknown4 = angle;
            p->mUnknown512.mUnknown8 = angle;
            p->mUnknown512.mUnknown14 = 4;
        }
    } else {
        result = 3;
    }
    return result;
}

extern "C" void HandoffSteerClear(Object_80039F5C *p, Object_80039F5C *pOther, HandoffBlock_t *state) {
    if (p->mMotion.mPos.mY > pOther->mMotion.mPos.mY) {
        Point_8017886C delta;
        fn_80227690(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
        fn_801CFE40(delta.mY, delta.mX);
        float distance = fn_802270A4(&delta);
        if (distance < 2.0f) {
            float speed = distance * 0.5f;
            int turn = (int)((1.0f - speed) * 0x355555);
            if (state->mUnknown6 == 6)
                turn = -turn;
            unsigned int kind = state->mUnknown8;
            if (kind == 15 || kind == 12) {
                if (distance > 4.0f && kind == 12) {
                    fn_800DBC4C(p, (p->mMotion.mFacing + turn) & 0xFFFFFF, speed);
                } else {
                    int angle = (p->mMotion.mFacing + turn) & 0xFFFFFF;
                    p->mUnknown512.mUnknown0 = speed;
                    p->mUnknown512.mUnknown14 = 1;
                    p->mUnknown512.mUnknown4 = angle;
                    p->mUnknown512.mUnknown8 = angle;
                }
            } else {
                int angle = (p->mMotion.mFacing + turn) & 0xFFFFFF;
                p->mUnknown512.mUnknown0 = speed;
                p->mUnknown512.mUnknown14 = 4;
                p->mUnknown512.mUnknown4 = angle;
                p->mUnknown512.mUnknown8 = angle;
            }
        }
    } else {
        unsigned int kind = state->mUnknown8;
        if (kind == 3 || kind == 5 || kind == 1) {
            p->mUnknown512.mUnknown0 = 1.0f;
            p->mUnknown512.mUnknown14 = 4;
            p->mUnknown512.mUnknown4 = 0xC00000;
            p->mUnknown512.mUnknown8 = 0xC00000;
        }
    }
}

extern "C" void HandoffGiveBall(Object_80039F5C *p, Object_80039F5C *pOther, Ball_t *pBall, HandoffBlock_t *state) {
    if (pBall) {
        int mode = fn_800AD9B4();
        BallGiveToPlayer(pBall, pOther);
        BallSetTransferKind(pBall, 0);
        if (mode == 3) {
            switch (state->mUnknown8) {
            case 0:
            case 2:
            case 4:
            case 6:
            case 8:
            case 10:
            case 12:
            case 13:
            case 15: {
                Record_800B15FC *pRecord = fn_800B15FC();
                fn_8009BD2C(pOther, &pRecord->mUnknown0);
                pRecord->mUnknownC = pOther->mMotion.mPos.mX;
                pRecord->mUnknown10 = pOther->mMotion.mPos.mY;
                pRecord->mUnknown14 = 8;
                fn_800B1508();
                AudmonEventPostId(30, &pOther->mMotion.mPos, pOther->mId, 1, 1, 0);
                break;
            }
            }
            fn_800B67FC(p, pOther);
        }
    }
}

extern "C" int HandoffEnter(Object_80039F5C *p) {
    HandoffBlock_t *state = (HandoffBlock_t *)&p->mUnknown336;
    state->mUnknown4 = 0;
    state->mUnknown8 = p->mpState->mUnknown2;
    state->mUnknown6 = p->mpState->mUnknown3[0];
    Object_80039F5C *pOther = PlyrGet(p->mIdBytes[2], p->mpState->mUnknown1);
    fn_8009BD2C(pOther, &state->mUnknown0);
    switch (state->mUnknown8) {
    case 12:
    case 13:
    case 15:
        BallSetCurrentTarget(pOther);
        if (p->mUnknown2914 != 0)
            state->mUnknown8 = 15;
        if (fn_800DC080(p)) {
            state->mUnknown8 = 12;
            if (p->mMotion.mPos.mY < pOther->mMotion.mPos.mY
                || fn_80177FE0().mY - p->mMotion.mPos.mY > 3.0f)
                state->mUnknown8 = 13;
        }
        break;
    case 14:
        if (p->mpState[1].mId == 31) {
            fn_8011E1BC(p, 0, 0, 1);
            fn_8011E3EC(p, 1);
        } else if (p->mpState[1].mId == 33) {
            fn_8011E1BC(p, 0, 0, 1);
            fn_8011E3EC(p, 2);
        }
        break;
    }
    p->mUnknown512.mUnknown14 = 0;
    p->mFlags &= ~4;
    p->mFlags &= ~1;
    return 0;
}

extern "C" int HandoffUpdate(Object_80039F5C *p) {
    int result = 0;
    HandoffBlock_t *state = (HandoffBlock_t *)&p->mUnknown336;
    Object_80039F5C *pOther = fn_8009BCE8(&state->mUnknown0);
    Message_800F01CC message;
    if (state->mUnknown8 == 14 && !BallFindHeldBy(p))
        return 1;
    switch (state->mUnknown8) {
    case 0:
    case 2:
    case 4:
    case 12:
    case 13:
    case 15:
        if ((p->mUnknown560.mUnknown40 || pOther->mUnknown560.mUnknown40) && state->mUnknown4 != 3) {
            fn_801C1F94(&message, 0, 4);
            message.mId = 1;
            fn_800F053C(0, p->mpState, &message, p);
            return 0;
        }
        break;
    }
    if (fn_800F06F4(0, pOther->mpState, 27, 0xFFFF) == 0xFFFF && state->mUnknown8 != 14 && state->mUnknown4 != 3) {
        fn_801C1F94(&message, 0, 4);
        message.mId = 1;
        fn_800F053C(0, p->mpState, &message, p);
        fn_801C1F94(&message, 0, 4);
        message.mId = 33;
        fn_800F053C(0, pOther->mpState, &message, p);
        return 0;
    }
    switch (state->mUnknown4) {
    case 0:
        if (BallFindHeldBy(p)) {
            if (state->mUnknown8 == 15 || state->mUnknown8 == 12) {
                state->mUnknown4 = 2;
                HandoffPickSide(p, state);
                break;
            }
            switch (state->mUnknown8) {
            case 14:
                state->mUnknown4 = 3;
                break;
            case 1:
            case 3:
            case 5: {
                int none = fn_800F06F4(0, pOther->mpState, 27, 0xFFFF);
                if (none == 0xFFFF && fn_800F06F4(0, pOther->mpState, 21, 0xFFFF) == none) {
                    if (fn_800B65A0(p->mIdBytes[2]) != 255 && !fn_8011F1A4())
                        PassIconsAreShown();
                    fn_801C1F94(&message, 0, 4);
                    message.mId = 3;
                    message.mUnknown1[0] = 20;
                    message.mUnknown1[1] = 96;
                    message.mUnknown1[2] = 255;
                    fn_800F05E4(0, p->mpState, &message, p);
                    return 0;
                }
                state->mUnknown4 = 1;
                break;
            }
            case 13:
                state->mUnknown4 = 2;
                HandoffPickSide(p, state);
                break;
            default:
                state->mUnknown4 = 1;
                break;
            }
            if (state->mUnknown4 == 1 && state->mUnknown6 == 3) {
                HandoffPickSide(p, state);
                state->mUnknown4 = 2;
            }
            HandoffStartAnim(p, state, state->mUnknown4);
            p->mFlags &= ~4;
        }
        break;
    case 1:
        if ((p->mFlags & 4) || state->mUnknown6 == 3) {
            p->mFlags &= ~4;
            state->mUnknown4 = 2;
            if (HandoffSteer(p, pOther, state) == 3)
                state->mUnknown4 = 3;
            HandoffStartAnim(p, state, state->mUnknown4);
        }
        break;
    case 2:
        if (HandoffTryPairAnim(p, pOther, state) == 1) {
            state->mUnknown4 = 3;
            BallSetCurrentTarget(0);
        } else if (HandoffSteer(p, pOther, state) == 3) {
            state->mUnknown4 = 3;
            HandoffStartAnim(p, state, 3);
        } else {
            Point_8017886C delta;
            fn_80227690(&delta, &p->mMotion.mPos, &pOther->mMotion.mPos);
            if (MathAngleDiff(fn_801CFE40(delta.mY, delta.mX), pOther->mMotion.mUnknown32) > 0x400000
                && p->mMotion.mPos.mY < pOther->mMotion.mPos.mY) {
                switch (state->mUnknown8) {
                case 12:
                case 13:
                    if (pOther->mMotion.mPos.mY - p->mMotion.mPos.mY < 2.5f
                        && p->mMotion.mPos.mY < fn_80177FE0().mY)
                        break;
                case 0:
                case 2:
                case 4:
                case 14:
                    if (fn_800F06F4(0, pOther->mpState, 18, 0xFFFF) != 0xFFFF)
                        return 1;
                    fn_801C1F94(&message, 0, 4);
                    message.mId = 1;
                    fn_800F053C(0, p->mpState, &message, p);
                    break;
                case 1:
                case 3:
                case 5:
                    p->mUnknown512.mUnknown14 = 1;
                    p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
                    p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
                    p->mUnknown512.mUnknown0 = 0.4f;
                default:
                    result = 1;
                    break;
                }
                fn_80143EBC(p, pOther);
                fn_80143EBC(pOther, p);
            }
        }
        if (state->mUnknown4 == 3) {
            unsigned int kind = state->mUnknown8;
            if (kind == 1 || kind == 3 || kind == 5 || kind == 7 || kind == 9 || kind == 11) {
                if (p->mUnknown2914 == 0 || p->mUnknown2914 == 7)
                    fn_800A5A8C(0, p, pOther);
                fn_800A60D8(p, pOther);
            } else if (fn_8011F2C4()) {
                fn_800A5A8C(8, p, pOther);
            }
        }
        break;
    case 3:
        if (p->mFlags & 1) {
            p->mFlags &= ~1;
            unsigned int kind = state->mUnknown8;
            if (kind != 1 && kind != 3 && kind != 5 && kind != 7 && kind != 9 && kind != 11) {
                HandoffGiveBall(p, pOther, BallFindHeldBy(p), state);
                if (state->mUnknown8 != 14 && p->mUnknown2914 != 0)
                    fn_800A5A8C(6, p, p);
            } else if (p->mUnknown2914 != 0 && p->mUnknown2914 != 7) {
                fn_800A5A8C(7, p, pOther);
            }
        }
        if (p->mFlags & 4) {
            fn_80143EBC(p, pOther);
            fn_80143EBC(pOther, p);
            p->mFlags &= ~4;
            switch (state->mUnknown8) {
            case 0:
            case 2:
            case 4:
            case 12:
            case 13:
            case 15:
                if (p->mpState[1].mId == 0) {
                    fn_801C1F94(&message, 0, 4);
                    message.mId = 3;
                    message.mUnknown1[0] = 16;
                    message.mUnknown1[1] = p->mMotion.mUnknown32 >> 17;
                    message.mUnknown1[2] = 128;
                    fn_800F053C(0, p->mpState, &message, p);
                    break;
                }
                result = 1;
                break;
            case 1:
            case 3:
            case 5:
                p->mUnknown512.mUnknown14 = 1;
                p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
                p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
                p->mUnknown512.mUnknown0 = 0.4f;
                if (fn_800B65A0(p->mIdBytes[2]) != 255 && !fn_8011F1A4())
                    PassIconsAreShown();
                result = 1;
                break;
            case 14:
                p->mUnknown512.mUnknown0 = 1.0f;
                p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
                p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
                p->mUnknown512.mUnknown14 = 1;
                result = 1;
                break;
            default:
                result = 1;
                break;
            }
        }
        break;
    }
    return result;
}

extern "C" int HandoffExit(Object_80039F5C *p) {
    HandoffBlock_t *state = (HandoffBlock_t *)&p->mUnknown336;
    Object_80039F5C *pOther = fn_8009BCE8(&state->mUnknown0);
    if (BallFindHeldBy(p) == BallGetCurrent())
        BallSetCurrentTarget(0);
    fn_80143EBC(p, pOther);
    if (pOther)
        fn_80143EBC(pOther, p);
    return 1;
}

extern "C" void HandoffMirrorMessage(Object_80039F5C *p) {
    if (p->mIdBytes[3] == 1)
        p->mIdBytes[3] = 2;
    else if (p->mIdBytes[3] == 2)
        p->mIdBytes[3] = 1;
    switch (p->mIdBytes[2]) {
    case 2:
        p->mIdBytes[2] = 4;
        break;
    case 4:
        p->mIdBytes[2] = 2;
        break;
    case 3:
        p->mIdBytes[2] = 5;
        break;
    case 5:
        p->mIdBytes[2] = 3;
        break;
    case 8:
        p->mIdBytes[2] = 10;
        break;
    case 10:
        p->mIdBytes[2] = 8;
        break;
    case 9:
        p->mIdBytes[2] = 11;
        break;
    case 11:
        p->mIdBytes[2] = 9;
        break;
    }
    PlayBookFormation_t *pObject = PlayBookGetFormation(fn_80178308());
    unsigned int count = fn_80178D18(fn_80178308());
    for (unsigned char i = 0; i < count; i++) {
        if (PlaySetGetEntry(pObject, i, 0)->mUnknownB == p->mIdBytes[1]) {
            p->mIdBytes[1] = i;
            break;
        }
    }
}

extern "C" int HandoffIsStarting(Object_80039F5C *p) {
    return ((HandoffBlock_t *)&p->mUnknown336)->mUnknown4 == 1;
}

extern "C" void HuddleArrive(Object_80039F5C *p, HuddleBlock_t *pState) {
    Message_800F01CC message;
    fn_801C1F94(&message, 0, 4);
    message.mId = 64;
    message.mUnknown1[0] = 18;
    message.mUnknown1[1] = 1;
    fn_800F03D8(0, p->mpState, &message, p);
    if (fn_801BE648(p->mpUnknown792) != 74 && fn_801BE648(p->mpUnknown792) != 203)
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 74, 1.0f, p);
    fn_801C1F94(&message, 0, 4);
    message.mId = 51;
    message.mUnknown1[0] = (int)(fn_80237260(0) * 32.0f);
    fn_800F03D8(0, p->mpState, &message, p);
    fn_801C1F94(&message, 0, 4);
    message.mId = 9;
    message.mUnknown1[0] = 203;
    message.mUnknown1[1] = 0;
    message.mUnknown1[2] = 255;
    fn_800F03D8(0, p->mpState, &message, p);
    int index;
    if (p->mIdBytes[2] == fn_80178308())
        index = 0;
    else
        index = 5;
    if (p->mIdBytes[1] == index) {
        fn_801C1F94(&message, 0, 4);
        message.mId = 71;
        fn_800F03D8(0, p->mpState, &message, p);
    }
}

extern "C" void HuddleSetSpot(HuddleBlock_t *pState, Object_80039F5C *p, Point_8017886C *pPoint, int value) {
    fn_800FF598(pState, p, pPoint, value, 0.0f);
    pState->mUnknown0 = fn_802372EC(0, 40) + 20;
}

extern "C" int HuddleMoveEnter(Object_80039F5C *p) {
    Point_8017886C point;
    int facing;
    HuddleGetSpot(&point, &facing, p, 0);
    HuddleBlock_t *state = (HuddleBlock_t *)&p->mUnknown336;
    HuddleSetSpot(state, p, &point, facing);
    state->mUnknown48 = 0;
    state->mUnknown49 = 0;
    state->mUnknown50 = 0;
    state->mUnknown52 = 0;
    return 0;
}

extern "C" int HuddleMoveUpdate(Object_80039F5C *p) {
    HuddleBlock_t *state = (HuddleBlock_t *)&p->mUnknown336;
    int stopped = 0;
    int facing = 0;
    int ready = 0;
    int checked = 0;
    int value;
    state->mUnknown52--;
    switch (state->mUnknown48) {
    case 0: {
        if (fn_800E1044(p, (Vector_80039F5C *)&state->mUnknown8)) {
            p->mUnknown1008Word = 26;
            if (fn_801BE648(p->mpUnknown792) != 203)
                fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 203, 1.0f, p);
            state->mUnknown48 = 3;
            break;
        }
        float distance = fn_8022781C(&state->mUnknown8, &p->mMotion.mPos);
        Point_8017886C delta;
        fn_80227690(&delta, &state->mUnknown8, &p->mMotion.mPos);
        if (state->mUnknown49 == 0 && p->mMotion.mUnknown28 < 0.006f) {
            state->mUnknown2 = 3;
            stopped = 1;
            ready = fn_800FF094(p);
            checked = 1;
            facing = p->mUnknown512.mUnknown4;
        }
        if (stopped) {
            if (fn_800CB580(p, &value, state->mUnknown8, facing, 0)) {
                fn_800CBB00(p, value, state->mUnknown8, facing, 1);
                state->mUnknown48 = state->mUnknown49 = 1;
                break;
            }
        }
        if (distance < 6.0f && p->mMotion.mUnknown28 > 0.006f) {
            if (fn_800CB708(p, &value, state->mUnknown8, state->mUnknown16, 1)) {
                fn_800CBB00(p, value, state->mUnknown8, state->mUnknown16, 1);
                state->mUnknown48 = 2;
                state->mUnknown50 = 1;
                break;
            }
        }
        state->mUnknown49 = 1;
        if (ready == 1 || (!checked && fn_800FF094(p) == 1)) {
            int done = 1;
            if (state->mUnknown50 == 0) {
                if (fn_800CB708(p, &value, state->mUnknown8, state->mUnknown16, 2)) {
                    fn_800CBB00(p, value, state->mUnknown8, state->mUnknown16, 1);
                    state->mUnknown48 = 2;
                    state->mUnknown50 = 1;
                    done = 0;
                }
            }
            if (done) {
                state->mUnknown50 = state->mUnknown49 = 0;
                HuddleArrive(p, state);
                return 1;
            }
        }
        break;
    }
    case 2:
        if (p->mFlags & 4) {
            p->mFlags &= ~4;
            p->mUnknown512.mUnknown0 = 0.0f;
            p->mUnknown512.mUnknown14 = 3;
            p->mUnknown512.mUnknown8 = p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
            state->mUnknown48 = 0;
            state->mUnknown0 = 0;
            state->mUnknown8.mX = p->mMotion.mPos.mX;
            state->mUnknown8.mY = p->mMotion.mPos.mY;
        }
        break;
    case 1:
        if (p->mFlags & 4) {
            p->mUnknown512.mUnknown14 = 3;
            p->mFlags &= ~4;
            p->mUnknown512.mUnknown8 = p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
            p->mUnknown512.mUnknown0 = _Handoff_fHuddleWalkSpeed;
            state->mUnknown24 = _Handoff_fHuddleWalkSpeed * 0.5f;
            state->mUnknown48 = 0;
            state->mUnknown0 = 0;
        }
        break;
    }
    return 0;
}

extern "C" int HuddleMoveAltEnter(Object_80039F5C *p) {
    Point_8017886C point;
    int facing;
    HuddleGetSpot(&point, &facing, p, 0);
    HuddleBlock_t *state = (HuddleBlock_t *)&p->mUnknown336;
    HuddleSetSpot(state, p, &point, facing);
    state->mUnknown48 = 0;
    state->mUnknown49 = 0;
    state->mUnknown50 = 0;
    state->mUnknown52 = 0;
    return 0;
}

extern "C" void HuddleGetSpot(Point_8017886C *pOut, int *pFacing, Object_80039F5C *p, int value) {
    unsigned int count = fn_80178D70(p->mIdBytes[2]);
    Point_8017886C origin;
    Point_8017886C offset;
    float base;
    origin = fn_8017808C();
    int id = p->mId;
    if (((id >> 16) & 0xFF) < count) {
        if (((id >> 8) & 0xFF) == fn_80178308()) {
            offset.mX = 0.0f;
            offset.mY = 0.0f;
            if (value)
                base = 2.5f;
            else
                base = 4.0f;
            fn_80227538(pOut, 0, fn_802372EC(0, 100) * 0.003f + base);
            fn_80227384(pOut, pOut, ((_Handoff_auHuddleSlots[p->mIdBytes[1]] << 24) / count + 0x400000) & 0xFFFFFF);
            fn_80227690(&offset, &offset, pOut);
            *pFacing = fn_801CFE40(offset.mY, offset.mX);
            if (origin.mY < 3.0f - fn_80178A2C())
                pOut->mY -= 7.0f;
            else
                pOut->mY -= 10.0f;
            fn_80227638(pOut, pOut, &origin);
        } else {
            offset.mX = 0.0f;
            offset.mY = 0.0f;
            if (value)
                base = 2.5f;
            else
                base = 4.0f;
            fn_80227538(pOut, 0, fn_802372EC(0, 100) * 0.003f + base);
            fn_80227384(pOut, pOut, ((_Handoff_auHuddleSlots[p->mIdBytes[1]] << 24) / count + 0x400000) & 0xFFFFFF);
            fn_80227690(&offset, &offset, pOut);
            *pFacing = fn_801CFE40(offset.mY, offset.mX);
            pOut->mY += 3.0f;
            fn_80227638(pOut, pOut, &origin);
        }
    } else {
        pOut->mX = p->mMotion.mPos.mX;
        pOut->mY = p->mMotion.mPos.mY;
        *pFacing = p->mMotion.mFacing;
    }
}

extern "C" int HuddleMoveAltUpdate(Object_80039F5C *p) {
    return HuddleMoveUpdate(p);
}

extern "C" int HuddleHoldUpdate(Object_80039F5C *p) {
    if (fn_800AD9B4() != 5) {
        if (p->mUnknown9[0] != 1) {
            Message_800F01CC message;
            fn_801C1F94(&message, 0, 4);
            message.mId = 11;
            message.mUnknown1[0] = p->mUnknown9[0];
            fn_800F00D4(0, p->mpState, &message, p);
            p->mUnknown512.mUnknown14 = 0;
        } else if (fn_801BE648(p->mpUnknown792) != 74 && fn_801BE648(p->mpUnknown792) != 203) {
            fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 74, 1.0f, p);
        }
        return 1;
    }
    return 0;
}

extern "C" int HuddleHoldExit(Object_80039F5C *p) {
    if (fn_801BE648(p->mpUnknown792) != 74)
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 74, 1.0f, p);
    return 1;
}
