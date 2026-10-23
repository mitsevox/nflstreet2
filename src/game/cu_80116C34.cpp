#include "game/Object_80039F5C.h"
#include "game/Message_800F01CC.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800B65A0.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80178D18.h"
#include "game/fn_801C1F94.h"
#include "game/fn_802372EC.h"
#include <math.h>

struct State_80116C34 {
    unsigned short mUnknown0;
    short mUnknown2;
    int mUnknown4;
    int mUnknown8;
    float mUnknown12;
    unsigned char mUnknown16;
    char mUnknown17;
    short mUnknown18;
    unsigned char mUnknown20;
    unsigned char mUnknown21;
    char mUnknown22[2];
    unsigned char mUnknown24;
};

/* View of the block at player +336 used by fn_80116B98. */
struct Block_80116B98 {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    int mUnknown4;
    int mUnknown8;
    float mUnknown12;
    unsigned char mUnknown16;
    char mUnknown17[1];
    short mUnknown18;
    unsigned char mUnknown20;
};

extern "C" {
int fn_8011F1A4(void);
int fn_8010A2DC(Object_80039F5C *p, int a, int b);
int fn_800AC2C0(int team);
signed char fn_8009AF00(int team, signed char value);
int fn_801163B4(Object_80039F5C *p);
void fn_8011569C(Object_80039F5C *p);
int fn_801CFFD0(int a, int b);
int fn_800A5C04(Object_80039F5C *p, int a, int b);
int fn_8009E180(Object_80039F5C *p);
float fn_8016B938(void);
float fn_8016B974(void);
int fn_8009F258(Object_80039F5C *p);
int fn_80178308(void);
int fn_80178320(void);
int fn_801783AC(int value);
int fn_80168E00(int team, int index, unsigned char *pOut);
int fn_8011E9D8(State_80039F5C *p);
int fn_800DC21C(Object_80039F5C *p);
int fn_800DC080(Object_80039F5C *p);
int fn_8009EFDC(int index);
float fn_80178A2C(void);
extern unsigned char *lbl_803EC9F0;
extern float lbl_803EAFE8;
extern float lbl_803EAFEC;
extern float lbl_803EAFF0;
extern float lbl_803EAFF4;
extern float lbl_803EAFF8;
extern float lbl_803EAFFC;
extern float lbl_803EB000;

int fn_80116B98(Object_80039F5C *p)
{
    Block_80116B98 *pBlock = (Block_80116B98 *)&p->mUnknown336;

    pBlock->mUnknown2 = 0;
    pBlock->mUnknown0 = 0;
    pBlock->mUnknown20 = 0;
    pBlock->mUnknown8 = 0;
    pBlock->mUnknown4 = 0xC00000;
    pBlock->mUnknown12 = 0.0f;
    if (fn_8011F1A4()) {
        pBlock->mUnknown16 = 1;
        pBlock->mUnknown18 = p->mRatings[5] <= 255 ? 255 - p->mRatings[5] : 0;
    } else {
        pBlock->mUnknown16 = 0;
        pBlock->mUnknown18 = 0;
    }
    return 0;
}

static inline int IsBallAway(const Vector_80039F5C &ball)
{
    int away = 0;
    if (ball.mY > fn_80177FE0().mY + 3.0f) {
        away = 1;
    } else if (!(fabsf(ball.mX - fn_80177FE0().mX) <= 3.0f)) {
        away = 1;
    }
    return away;
}

int fn_80116C34(Object_80039F5C *p)
{
    fn_8010A2DC(p, 0, -1);
    State_80116C34 *state = (State_80116C34 *)&p->mUnknown336;
    int update = 0;
    state->mUnknown0++;
    state->mUnknown2 = (signed char)(state->mUnknown2 - 1);
    if (state->mUnknown2 < 0) {
        int limit = 255 - p->mRatings[8];
        if (limit < 0) limit = 0;
        update = 1;
        int base = fn_800AC2C0(p->mIdBytes[2]);
        state->mUnknown2 = (signed char)(state->mUnknown2 + base + fn_802372EC(0, (unsigned int)limit >> 5));
        state->mUnknown2 = fn_8009AF00(p->mIdBytes[2], (signed char)state->mUnknown2);
    }
    if (state->mUnknown16 && state->mUnknown0 >= state->mUnknown18) update = 1;
    if (!(p->mFlags & 0x4000) && update) {
        if (fn_801163B4(p)) return 1;
        if (!state->mUnknown16 || state->mUnknown0 < state->mUnknown18) {
            state->mUnknown21 = 0;
            fn_8011569C(p);
            if (state->mUnknown12 == 1.0f) {
                state->mUnknown4 = state->mUnknown8;
                if (fn_801CFFD0(p->mMotion.mFacing, state->mUnknown8) <= 0xE38E2 &&
                    fn_801CFFD0(p->mMotion.mUnknown32, state->mUnknown8) <= 0xE38E2) {
                    state->mUnknown21 = 1;
                }
            } else {
                state->mUnknown4 = 0xC00000;
            }
            if (state->mUnknown16) state->mUnknown12 *= 0.5f;
        } else {
            state->mUnknown4 = state->mUnknown8;
            state->mUnknown12 = 0.0f;
            state->mUnknown8 = p->mMotion.mFacing;
        }
    }
    if (!fn_800A5C04(p, state->mUnknown8, state->mUnknown4) && !(p->mFlags & 0x4000)) {
        if (update) {
            int kind = fn_8009E180(p);
            if (state->mUnknown20) kind = 5;
            if (kind > 2) {
                Message_800F01CC message;
                Vector_80039F5C target;
                if (kind != 4) {
                    unsigned short odds = p->mRatings[8] >> 1;
                    if (fn_800B65A0(p->mIdBytes[2]) == 255) {
                        odds += (int)(odds * fn_8016B938());
                    }
                    Vector_80039F5C ball;
                    fn_80137D58(fn_801374BC(), &ball);
                    if (fn_802372EC(0, 255) < odds || IsBallAway(ball)) {
                        fn_801C1F94(&message, 0, 4);
                        message.mId = 2;
                        fn_800F053C(0, p->mpState, &message, p);
                        return 1;
                    }
                } else {
                    fn_80138064(fn_801374BC(), &target);
                    if (fn_8009F258(p)) {
                        fn_801C1F94(&message, 0, 4);
                        message.mId = 24;
                        if (!fn_80137B88(fn_801374BC())) {
                            message.mUnknown1[0] = 0;
                        } else if (fabsf(target.mX - p->mMotion.mPos.mX) < 10.0f || fn_802372EC(0, 100) <= 49) {
                            message.mUnknown1[0] = 2;
                        } else {
                            message.mUnknown1[0] = 1;
                        }
                        fn_800F053C(0, p->mpState, &message, p);
                        return 0;
                    }
                }
            }
        }
        if (state->mUnknown12 != 0.0f) {
            p->mUnknown512.mUnknown14 = 3;
            p->mUnknown512.mUnknown4 = state->mUnknown8;
            p->mUnknown512.mUnknown8 = state->mUnknown4;
            p->mUnknown512.mUnknown0 = state->mUnknown12;
        } else if (fn_801CFFD0(p->mMotion.mFacing, state->mUnknown4) > 0x71C71) {
            p->mUnknown512.mUnknown14 = 3;
            p->mUnknown512.mUnknown4 = (state->mUnknown4 + 0x800000) & 0xFFFFFF;
            p->mUnknown512.mUnknown8 = state->mUnknown4;
            p->mUnknown512.mUnknown0 = 0.5f;
        }
        p->mUnknown512.mUnknown15 = state->mUnknown21;
    }
    return 0;
}

int fn_801170E8(Object_80039F5C *p)
{
    unsigned char side = p->mpState->mUnknown1 + 14;
    int found = 0;
    int result = 0;
    int beyond = 0;
    int blocked;
    unsigned int count = fn_80178D70(fn_80178320());
    for (unsigned char i = 0; i < count && !found; i++) {
        if (fn_80039F5C(fn_80178320(), i)->mpState->mId == 85) found = 1;
    }
    Point_8017886C origin;
    origin = fn_80177FE0();
    for (unsigned char i = 0; i <= 2; i++) {
        int index = fn_80168E00(fn_80178308(), i, 0);
        if (index == 255) continue;
        Object_80039F5C *other = fn_80039F5C(fn_80178308(), (unsigned short)index);
        if (!other) continue;
        switch (side) {
        case 15: case 17: case 20:
            if (!(other->mMotion.mPos.mX >= origin.mX)) {
                fn_8011E9D8(other->mpState);
                if (other->mMotion.mPos.mY < origin.mY + 4.0f && (other->mFlags & 0x800)) blocked = 1;
            }
            break;
        case 16: case 19: case 23:
            if (!(other->mMotion.mPos.mX <= origin.mX)) {
                fn_8011E9D8(other->mpState);
                if (other->mMotion.mPos.mY < origin.mY + 4.0f && (other->mFlags & 0x800)) blocked = 1;
            }
            break;
        }
    }
    Object_80039F5C *carrier = fn_80137B40();
    if (carrier) {
        switch (side) {
        case 15: case 17: case 20:
            if (!(carrier->mMotion.mPos.mX >= origin.mX)) beyond = 1;
            break;
        case 16: case 19: case 23:
            if (!(carrier->mMotion.mPos.mX <= origin.mX)) beyond = 1;
            break;
        }
    }
    if (carrier) {
        float ratio = carrier->mMotion.mUnknown28 / carrier->mMotion.mUnknown36;
        float speed = ratio < 0.0 ? 0.0f : (float)(ratio <= 1.0 ? ratio : 1.0);
        float proximity = 1.0f - fabsf(carrier->mMotion.mPos.mY - origin.mY) * 0.16666667f;
        float position = proximity < 0.0 ? 0.0f : (float)(proximity <= 1.0 ? proximity : 1.0);
        float score = speed * 0.6f + position * 0.4f;
        if (!(score <= 0.7f) && beyond) {
            blocked = 0;
            result = 1;
        } else blocked = 1;
    } else {
        blocked = 0;
        result = 1;
    }
    if (fn_801783AC(0) || fn_8009E180(p) == 5) result = 1;
    else if (found || blocked) result = 0;
    if (result) {
        Message_800F01CC message;
        fn_801C1F94(&message, 0, 4);
        message.mId = 2;
        fn_800F053C(0, p->mpState, &message, p);
        *lbl_803EC9F0 = 1;
    }
    return result;
}

int fn_80117494(Object_80039F5C *p, Point_8017886C *out)
{
    State_80116C34 *state = (State_80116C34 *)&p->mUnknown336;
    int result = 0;
    unsigned char side = p->mpState->mUnknown1 + 14;
    float centerX = fn_80177FE0().mX;
    float centerY = fn_80177FE0().mY;
    out->mX = p->mMotion.mPos.mX;
    out->mY = p->mMotion.mPos.mY;
    Object_80039F5C *carrier = fn_80137B40();
    if (carrier && (carrier->mFlags & 0x8000) &&
        ((!(carrier->mMotion.mPos.mX >= centerX) && p->mMotion.mPos.mX < centerX) ||
         (!(carrier->mMotion.mPos.mX <= centerX) && !(p->mMotion.mPos.mX <= centerX)))) {
        float distance = centerY - carrier->mMotion.mPos.mY;
        if (!(distance >= lbl_803EAFE8) &&
            (carrier->mMotion.mUnknown32 & 0xFFFFFF) <= 0x7FFFFF) {
            int first = fn_800DC21C(carrier);
            int second = fn_800DC080(carrier);
            if (first || second || fn_801783AC(0)) {
                if (fn_801783AC(7) == 1 || fn_801783AC(8) == 1) state->mUnknown24 = 1;
                if (!(distance >= lbl_803EAFEC)) {
                    float half = lbl_803EAFF0 * 0.5f;
                    out->mY = half * (distance / lbl_803EAFEC) + centerY;
                    float threshold = fn_8016B974() * lbl_803EAFF8 + lbl_803EAFF4;
                    if (!(distance >= threshold) && carrier->mUnknown8 != 255) state->mUnknown24 = 1;
                    result = 1;
                }
                if (!(fabsf(carrier->mMotion.mPos.mX) <= fabsf(p->mMotion.mPos.mX))) {
                    state->mUnknown12 = 0.8f;
                    distance = fabsf(carrier->mMotion.mPos.mX - p->mMotion.mPos.mX);
                    if (!(distance <= lbl_803EAFFC)) {
                        if (fn_8009EFDC(side) == -1) {
                            out->mX = carrier->mMotion.mPos.mX - 1.5f;
                            if (first && fn_801CFFD0(carrier->mMotion.mUnknown32, 0x638E39) <= 0x1C71C6) state->mUnknown12 = 0.8f;
                        } else {
                            out->mX = carrier->mMotion.mPos.mX + 1.5f;
                            if (first && fn_801CFFD0(carrier->mMotion.mUnknown32, 0x1C71C7) <= 0x1C71C6) state->mUnknown12 = 0.8f;
                        }
                        result = 1;
                    }
                }
                if (!(fabsf(p->mMotion.mPos.mX - centerX) <= 5.0f) &&
                    !(p->mMotion.mPos.mY <= fn_80178A2C()) &&
                    !(distance >= lbl_803EB000)) state->mUnknown24 = 1;
            }
        }
    }
    if (state->mUnknown24) result = 1;
    if (*lbl_803EC9F0) result = 0;
    return result;
}
}
