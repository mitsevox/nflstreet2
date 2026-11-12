/* Player state 21: a player without the ball looks for open space. He scores a grid of
   nearby defenders and team-mates around him, picks the least crowded cell between the line
   of the ball and the far end of the field, cuts toward it or runs there, and turns back to
   wave for the ball when the carrier is behind him. */

#include "engine/cu_801B9F00.h"
#include "game/StyleTracker.h"
#include "game/OptionRunControl.h"
#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/AnimMomentumActor.h"
#include "game/Object_8017886C.h"
#include "game/Plan_80121264.h"
#include "game/Table_80089904.h"
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

#define CLAMP(v, lo, hi) ((v) < (lo) ? (lo) : ((v) > (hi) ? (hi) : (v)))

extern "C" {
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
void fn_800FD68C(Message_800F01CC *, void *, void *);
int fn_8010A2DC(Object_80039F5C *p, int a, short b);
int fn_80178320(void);
int fn_801CFE40(float y, float x);
int MathAngleDiff(int a, int b);
void fn_80227690(void *pOut, void *pA, void *pB);
int fn_80177F70(void);
float fn_80178298(void);
float fn_80178A08(void);
float fn_80178A2C(void);
float fn_80178A44(void);
float PlyrMoveGetRatedSpeed(Object_80039F5C *p, float a, float b);
void fn_80227538(Point_8017886C *pOut, int angle, float length);
void fn_8009BD60(Object_80039F5C *p);
int fn_80112928(Object_80039F5C *p);
int fn_80178308(void);
int fn_801783AC(int a);
extern float gPlyrMoveFwdSpeed;
void fn_8009A8D4(void *p);
int fn_80103D6C(Object_80039F5C *p);
int fn_800C13A0(Object_80039F5C *p, unsigned char *pA, unsigned char *pB);
int PlayBookGetReceiver(int team, int a, unsigned char *pOut);
void PlayerCutPostTurn(Object_80039F5C *p, int angle);

int GetOpenShouldRunOn(Object_80039F5C *p);
int GetOpenIsOpenToCarrier(Object_80039F5C *p, float a, float b);
int GetOpenFindOpenSpot(Point_8017886C *out, Object_80039F5C *p, float lower, float upper);
void GetOpenRunOn(Object_80039F5C *p, float distance);
void GetOpenGetRunOnPoint(Object_80039F5C *p, Point_8017886C *pOut);
int GetOpenEnter(Object_80039F5C *p);
int GetOpenUpdate(Object_80039F5C *p);
void GetOpenGetDepthRange(float *pA, float *pB);
}

/* Player block at +336 as the state-21 handlers use it. Only the accessed fields
   are declared; the size is unknown. */
struct GetOpenState_t {
    char mUnknown0[20];
    float mUnknown20;
    int mUnknown24;
    int mUnknown28;
    int mUnknown32;
    unsigned short mUnknown36;
    unsigned char mUnknown38;
    unsigned char mUnknown39;
    unsigned char mUnknown40;
};

extern "C" int GetOpenShouldRunOn(Object_80039F5C *p)
{
    float a, b;
    int facing = p->mMotion.mFacing;
    int result = 0;

    GetOpenGetDepthRange(&a, &b);
    if ((MathAngleDiff(facing, 0x400000) <= 0x438E38 && p->mMotion.mPos.mY < b)
        || (!(p->mMotion.mPos.mY <= b) && !(p->mMotion.mPos.mY >= a))) {
        result = 1;
    }
    if (result) {
        if ((!(fn_80178A08() - p->mMotion.mPos.mX >= 4.0f)
             && MathAngleDiff(facing, 0) <= 0x1FFFFF)
            || (!(-fn_80178A08() - p->mMotion.mPos.mX <= -4.0f)
                && MathAngleDiff(facing, 0x800000) <= 0x1FFFFF)) {
            result = 0;
        }
    }
    if (p->mFlags & 0x4000) {
        result = 0;
    }
    if (!(p->mMotion.mUnknown28 >= PlyrMoveGetRatedSpeed(p, 0.14f, 1.0f))) {
        Object_80039F5C *pOther = BallGetCurrentHolder();

        if (pOther && pOther->mpState->mId == 15) {
            result = 0;
        }
    }
    return result;
}

extern "C" int GetOpenIsOpenToCarrier(Object_80039F5C *p, float a, float b)
{
    unsigned char count = 0;
    int tracking = 0;
    int result = 1;
    int angle = 0;
    Point_8017886C delta;
    GetOpenState_t *state = (GetOpenState_t *)&p->mUnknown336;
    Object_80039F5C *carrier;
    unsigned char i;
    Point_8017886C offset;

    delta.mX = delta.mY = 0.0f;
    carrier = BallGetCurrentHolder();
    if (carrier) {
        fn_80227690(&delta, &carrier->mMotion.mPos, &p->mMotion.mPos);
    }
    if (carrier && p->mMotion.mPos.mY > a && p->mMotion.mPos.mY < b
        && (float)(int)state->mUnknown36 < state->mUnknown20
        && fabsf(delta.mX) < fn_80178A08()
        && fabsf(p->mMotion.mPos.mX) < fn_80178A08() - 1.0f) {
        unsigned int total = fn_80178D18(fn_80178320());
        for (i = 0; i < total; ++i) {
            Object_80039F5C *other = fn_80039F5C(fn_80178320(), i);
            fn_80227690(&offset, &other->mMotion.mPos, &p->mMotion.mPos);
            int otherAngle = fn_801CFE40(offset.mY, offset.mX);
            angle = fn_801CFE40(delta.mY, delta.mX);
            if (MathAngleDiff(otherAngle, angle) <= 0x555554 && fn_802270A4(&offset) < 5.0f) {
                count = 1;
                break;
            }
            if (other->mpState->mId == 22 && fn_8009BCE8((int *)&other->mUnknown336) == p) {
                tracking = 1;
                break;
            }
        }
        if (count || tracking) {
            result = 0;
        } else {
            unsigned int others = fn_80178D18(fn_80178308());
            for (i = 0; i < others; ++i) {
                Object_80039F5C *other = fn_80039F5C(fn_80178308(), i);
                if (other != p) {
                    Point_8017886C toOther;
                    fn_80227690(&toOther, &other->mMotion.mPos, &p->mMotion.mPos);
                    int otherAngle = fn_801CFE40(toOther.mY, toOther.mX);
                    if (MathAngleDiff(otherAngle, angle) <= 0x555554 && fn_802270A4(&toOther) < 5.0f) {
                        ++count;
                        break;
                    }
                }
            }
            if (count) {
                result = 0;
            }
        }
    } else {
        result = 0;
    }
    return result;
}

extern "C" int GetOpenFindOpenSpot(Point_8017886C *out, Object_80039F5C *p, float lower, float upper)
{
    int grid[9][12];
    Object_80039F5C *other;
    Point_8017886C point;
    int x, y;

    fn_801C1F94(grid, 0, sizeof(grid));
    out->mY = out->mX = 0.0f;
    float left = p->mMotion.mPos.mX - 27.0f;
    float right = p->mMotion.mPos.mX + 27.0f;
    float top = p->mMotion.mPos.mY + 42.0f;
    float bottom = p->mMotion.mPos.mY - 42.0f;
    if (!(top >= upper)) {
        upper = top;
        lower = top - 10.5f;
    }
    int team = fn_80178320();
    unsigned int total = fn_80178D70(team);
    for (unsigned char i = 0; i < total; ++i) {
        other = fn_80039F5C(team, i);
        switch (other->mpState->mId) {
        case 40:
        case 85:
        case 92:
            point.mX = other->mMotion.mPos.mX;
            point.mY = other->mMotion.mPos.mY;
            break;
        case 22:
            if (fn_8009BCE8((int *)&other->mUnknown336)) {
                if (other->mpState->mId == 19) {
                    point.mX = ((Point_8017886C *)&other->mUnknown336)->mX;
                    point.mY = ((Point_8017886C *)&other->mUnknown336)->mY;
                } else {
                    point.mX = other->mMotion.mPos.mX;
                    point.mY = other->mMotion.mPos.mY;
                }
            } else {
                point.mX = other->mMotion.mPos.mX;
                point.mY = other->mMotion.mPos.mY;
            }
            break;
        default:
            point.mX = other->mMotion.mPos.mX;
            point.mY = other->mMotion.mPos.mY;
            break;
        }
        if (!(point.mX <= left) && !(point.mX >= right) && !(point.mY <= bottom) && !(point.mY >= top)) {
            x = (int)((point.mX - p->mMotion.mPos.mX) * (1.0f / 6.0f)) + 4;
            y = (int)((point.mY - p->mMotion.mPos.mY) * (1.0f / 7.0f)) + 6;
            x = CLAMP(x, 0, 8);
            y = CLAMP(y, 0, 11);
            grid[x][y] += 4;
        }
    }
    team = fn_80178308();
    for (unsigned char i = 0; i <= 2; ++i) {
        unsigned char valid;
        int index = PlayBookGetReceiver(team, i, &valid);
        if (valid) {
            other = fn_80039F5C(team, index);
            if (other != p) {
                if (other->mpState->mId == 19) {
                    point.mX = ((Point_8017886C *)&other->mUnknown336)->mX;
                    point.mY = ((Point_8017886C *)&other->mUnknown336)->mY;
                } else {
                    point.mX = other->mMotion.mPos.mX;
                    point.mY = other->mMotion.mPos.mY;
                }
                x = (int)((point.mX - p->mMotion.mPos.mX) * (1.0f / 6.0f)) + 4;
                y = (int)((point.mY - p->mMotion.mPos.mY) * (1.0f / 7.0f)) + 6;
                x = CLAMP(x, 0, 8);
                y = CLAMP(y, 0, 11);
                grid[x][y] += 8;
            }
        }
    }
    Object_80039F5C *carrier = BallGetCurrentHolder();
    if (carrier) {
        float width = fn_80178A08();
        width += width;
        float cx = carrier->mMotion.mPos.mX;
        float minimum, maximum;
        if (!(cx >= 0.0f)) {
            if (!(-fn_80178A08() >= cx - width * (1.0f / 3.0f))) minimum = cx - width * (1.0f / 3.0f);
            else minimum = -fn_80178A08();
            maximum = width * (1.0f / 3.0f) + cx;
            if (!(maximum <= 0.0f)) maximum = 0.0f;
        } else {
            if (!(fn_80178A08() <= width * (1.0f / 3.0f) + cx)) maximum = width * (1.0f / 3.0f) + cx;
            else maximum = fn_80178A08();
            minimum = cx - width * (1.0f / 3.0f);
            if (!(minimum >= 0.0f)) minimum = 0.0f;
        }
        for (unsigned char i = 0; i <= 8; ++i) {
            float column = (float)(int)i * 6.0f - 27.0f;
            if (!(column >= maximum) && !(column <= minimum)) {
                for (unsigned char j = 0; j <= 11; ++j) {
                    grid[i][j] -= 4;
                }
            }
        }
    }
    int best = 200;
    int bestX = 255, bestY = 255;
    Point_8017886C cell;
    for (unsigned char i = 0; i <= 8; ++i) {
        cell.mX = (float)(int)i * 6.0f - 27.0f + p->mMotion.mPos.mX;
        if (!(cell.mX <= 4.0f - fn_80178A08()) && !(cell.mX >= fn_80178A08() - 4.0f)) {
            for (unsigned char j = 0; j <= 11; ++j) {
                cell.mY = (float)(int)j * 7.0f - 42.0f + p->mMotion.mPos.mY;
                if (!(cell.mY <= lower) && !(cell.mY >= upper)) {
                    if (grid[i][j] < best) {
                        best = grid[i][j];
                        bestX = i;
                        bestY = j;
                    } else if (grid[i][j] == best && fn_802372EC(0, 100) <= 19) {
                        bestX = i;
                        bestY = j;
                    }
                }
            }
        }
    }
    if (bestX != 255) {
        out->mX = (float)bestX * 6.0f - 27.0f + p->mMotion.mPos.mX;
        out->mY = (float)bestY * 7.0f - 42.0f + p->mMotion.mPos.mY;
        GetOpenGetDepthRange(&upper, &lower);
        out->mX = !(out->mX >= 4.0f - fn_80178A08()) ? 4.0f - fn_80178A08()
                  : (out->mX <= fn_80178A08() - 4.0f ? out->mX : fn_80178A08() - 4.0f);
        out->mY = out->mY < lower ? lower : (out->mY <= upper ? out->mY : upper);
        return 1;
    }
    return 0;
}

extern "C" void GetOpenRunOn(Object_80039F5C *p, float distance)
{
    Message_800F01CC message;
    Point_8017886C point;

    GetOpenGetRunOnPoint(p, &point);
    fn_801C1F94(&message, 0, 4);
    message.mId = 19;
    fn_800FD68C(&message, &p->mMotion, &point);
    message.mUnknown1[2] = 255;
    fn_800F00D4(0, p->mpState, &message, p);
}

extern "C" void GetOpenGetRunOnPoint(Object_80039F5C *p, Point_8017886C *pOut)
{
    float a, b;

    GetOpenGetDepthRange(&a, &b);
    fn_80227538(pOut, p->mMotion.mUnknown32, 5.0f);
    pOut->mX += p->mMotion.mPos.mX;
    pOut->mY += p->mMotion.mPos.mY;
    fn_80177FE0();
    pOut->mX = pOut->mX > fn_80178A08() - 4.0f ? fn_80178A08() - 4.0f : pOut->mX;
    pOut->mX = pOut->mX < 4.0f - fn_80178A08() ? 4.0f - fn_80178A08() : pOut->mX;
    pOut->mY = pOut->mY < b ? b : (pOut->mY <= a ? pOut->mY : a);
}

extern "C" int GetOpenEnter(Object_80039F5C *p)
{
    GetOpenState_t *state = (GetOpenState_t *)&p->mUnknown336;
    state->mUnknown38 = 0;
    state->mUnknown24 = 0;
    state->mUnknown28 = (int)((float)(int)((1.0f - (float)p->mRatings[3] * (1.0f / 255.0f)) * 5.0f) + 2.0f);
    state->mUnknown36 = 0;
    state->mUnknown39 = 0;
    state->mUnknown40 = 0;

    state->mUnknown20 = 250.0f;
    state->mUnknown32 = 700;
    fn_8009A8D4(state);
    if (p->mIdBytes[3] == 1) {
        float fraction = (float)p->mRatings[3] * (1.0f / 255.0f);
        state->mUnknown20 += fraction * 150.0f;
        state->mUnknown32 -= (int)(fraction * 400.0f);
    }
    if (GetOpenShouldRunOn(p)) {
        int near = 0;
        int ahead = 0;
        if (!(p->mMotion.mPos.mY >= fn_80177FE0().mY + 5.0f)) {
            ahead = MathAngleDiff(p->mMotion.mUnknown32, 0x400000) <= 0x3FFFFF;
        }
        if (ahead) {
            near = 1;
        }
        if (!near) {
            if (!fn_80103D6C(p)) {
                unsigned char a, b;
                if (fn_800C13A0(p, &a, &b) > 1 && BallGetCurrentHolder()) {
                    if (!(fabsf(fn_80178A08() - p->mMotion.mPos.mX) >= 9.0f)) {
                        state->mUnknown28 = 0;
                    }
                    return 0;
                }
            }
        }
        GetOpenRunOn(p, 5.0f);
    } else if (!(fabsf(fn_80178A08() - p->mMotion.mPos.mX) >= 9.0f)) {
        state->mUnknown28 = 0;
    }
    return 0;


}

extern "C" int GetOpenUpdate(Object_80039F5C *p)
{
    GetOpenState_t *state = (GetOpenState_t *)&p->mUnknown336;
    p->mFlags |= 0x80000000;
    BallGetCurrent();
    fn_8010A2DC(p, 0, -1);
    if (!(p->mFlags & 0x4000)) {
        if (--state->mUnknown28 < 0) {
            state->mUnknown28 = (int)((float)(int)((1.0f - (float)p->mRatings[3] * (1.0f / 255.0f)) * 5.0f) + 2.0f);
            if (fn_80112928(p)) {
                return 1;
            }
        }
        Message_800F01CC message;
        if (BallGetCurrentHolder() && fn_801783AC(0)) {
            fn_801C1F94(&message, 0, 4);
            message.mId = 33;
            fn_800F053C(0, p->mpState, &message, p);
            return 1;
        }
        float a, b;
        state->mUnknown24 -= 2;
        if (state->mUnknown24 < 0 || !(fabsf(p->mMotion.mPos.mX) <= fn_80178A08() - 4.0f)) {
            int available = 0;
            if (BallGetCurrentHolder() && fn_80103D6C(p)) {
                unsigned char first, second;
                available = fn_800C13A0(p, &first, &second) <= 1;
            }
            if (!state->mUnknown39 && available && GetOpenShouldRunOn(p)) {
                GetOpenRunOn(p, 5.0f);
                goto fallback;
            }
            GetOpenGetDepthRange(&a, &b);
            if (state->mUnknown39) {
                if (p->mFlags & 4) {
                    p->mFlags &= ~4;
                    state->mUnknown39 = 0;
                    state->mUnknown40 = 1;
                }
            } else if (GetOpenIsOpenToCarrier(p, b, a)) {
                if (MathAngleDiff(p->mMotion.mFacing, 0xC00000) > 0x71C70) {
                    p->mUnknown512.mUnknown14 = 6;
                    p->mUnknown512.mUnknown4 = 0xC00000;
                    p->mUnknown512.mUnknown8 = 0xC00000;
                    p->mUnknown512.mUnknown0 = 4.0f;
                } else {
                    p->mUnknown512.mUnknown14 = 1;
                    p->mUnknown512.mUnknown8 = 0xC00000;
                    p->mUnknown512.mUnknown4 = 0xC00000;
                    p->mUnknown512.mUnknown0 = 0.0f;

                }
                ++state->mUnknown36;
                if (!fn_80103D6C(p) && MathAngleDiff(p->mMotion.mFacing, 0xC00000) <= 0x71C70
                    && !state->mUnknown40 && fn_802372EC(0, state->mUnknown32) < state->mUnknown36) {
                    p->mUnknown512.mUnknown14 = 0;
                    fn_8009BD60(p);
                    fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 152, 1.0f, p);
                    state->mUnknown39 = 1;
                }
            } else {
                state->mUnknown36 = 0;
            }
            if (state->mUnknown36) {
                return 0;
            }
            Point_8017886C point, delta;
            if (GetOpenFindOpenSpot(&point, p, b, a)) {
                fn_80227690(&delta, &point, &p->mMotion.mPos);
                PlayerCutPostTurn(p, fn_801CFE40(delta.mY, delta.mX));
                fn_801C1F94(&message, 0, 4);
                message.mId = 19;
                fn_800FD68C(&message, &p->mMotion, &point);
                message.mUnknown1[2] = 255;
                if (fn_800F06F4(0, p->mpState, 20, 65535) == 65535) {
                    fn_800F053C(0, p->mpState, &message, p);
                } else {
                    fn_800F03D8(0, p->mpState, &message, p);
                }
                fn_801C1F94(&message, 0, 4);
                message.mId = 21;
                fn_800F03D8(0, p->mpState, &message, p);
                return 0;
            }
        }
    fallback:
        if (!state->mUnknown36) {
            if (state->mUnknown38) {
                p->mUnknown512.mUnknown14 = 10;
                p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
                p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
                p->mUnknown512.mUnknown0 = 0.5f;
            } else {
                float speed = p->mMotion.mUnknown28 / gPlyrMoveFwdSpeed;
                if (!(speed >= 0.14f)) speed = 0.14f;
                p->mUnknown512.mUnknown14 = 1;
                p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
                p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
                p->mUnknown512.mUnknown0 = speed;
            }
        }
    } else if (fn_80112928(p)) {
        return 1;
    }
    return 0;
}

extern "C" void GetOpenGetDepthRange(float *pA, float *pB)
{
    switch (fn_80177F70()) {
    case 6:
        *pB = fn_80178A2C();
        break;
    case 3:
    case 4:
    case 5:
        *pB = fn_80178298() + 1.0f;
        break;
    default:
        if (!(fn_80177FE0().mY <= fn_80178A2C() - 12.0f)) {
            *pB = fn_80178A2C() + 1.0f;
        } else {
            *pB = fn_80177FE0().mY + 3.0f;
        }
        break;
    }
    Object_80039F5C *pOther = BallGetCurrentHolder();

    if (pOther) {
        *pA = pOther->mMotion.mPos.mY + 30.0f;
    } else {
        *pA = fn_80177FE0().mY + 30.0f;
    }
    if (!(*pA >= *pB + 10.5f)) {
        *pA = *pB + 10.5f;
    }
    if (!(*pA <= fn_80178A44() - 2.0f)) {
        *pA = fn_80178A44() - 2.0f;
    }
}
