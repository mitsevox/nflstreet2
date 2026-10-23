#include "game/Object_80039F5C.h"
#include "game/Message_800F01CC.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800B65A0.h"
#include "game/fn_80177FE0.h"
#include "game/fn_801C1F94.h"
#include "game/fn_802372EC.h"

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

extern "C" {
int fn_8010A2DC(Object_80039F5C *p, int a, int b);
int fn_800AC2C0(int team);
signed char fn_8009AF00(int team, signed char value);
int fn_801CFFD0(int a, int b);
int fn_800A5C04(Object_80039F5C *p, int a, int b);
int fn_8009E180(Object_80039F5C *p);
float fn_8016B938(void);
float fn_8016B974(void);
int fn_8009F258(Object_80039F5C *p);
int fn_801783AC(int value);
void fn_801180FC(Object_80039F5C *p);
int fn_801170E8(Object_80039F5C *p);
int fn_801CFE40(float y, float x);
void fn_80227690(void *pOut, void *pA, void *pB);
extern signed char lbl_803EB008;
extern float lbl_803EB00C;
extern float lbl_803EB004;
}

extern "C" int fn_801182C8(Object_80039F5C *p)
{
    Message_800F01CC message;
    Vector_80039F5C ball;
    int update = 0;
    Object_80039F5C *pCarrier = fn_80137B40();
    State_80116C34 *state = (State_80116C34 *)&p->mUnknown336;
    fn_8010A2DC(p, 0, -1);
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
    if (!(p->mFlags & 0x4000) && update) {
        if (!state->mUnknown16 || state->mUnknown0 < state->mUnknown18) {
            fn_801180FC(p);
            if (state->mUnknown12 == 1.0f) {
                state->mUnknown4 = state->mUnknown8;
            } else {
                state->mUnknown4 = 0xC00000;
            }
        } else {
            state->mUnknown12 = 0.1f;
            fn_80137D58(fn_801374BC(), &ball);
            fn_80227690(&ball, &ball, &p->mMotion.mPos);
            state->mUnknown4 = fn_801CFE40(ball.mY, ball.mX);
            if (((fn_801CFE40(ball.mY, ball.mX) - p->mMotion.mFacing) & 0xFFFFFF) > 0x800000) {
                state->mUnknown8 = state->mUnknown4 - 0x400000;
            } else {
                state->mUnknown8 = state->mUnknown4 + 0x400000;
            }
        }
    }
    if (fn_800A5C04(p, state->mUnknown8, state->mUnknown4) || (p->mFlags & 0x4000)) return 0;
    if (update) {
        int kind = fn_8009E180(p);
        if (state->mUnknown24) kind = 5;
        if (kind > 1) {
            if (kind != 4) {
                unsigned short odds = p->mRatings[8];
                if (fn_800B65A0(p->mIdBytes[2]) == 255) {
                    odds += (int)(odds * fn_8016B938());
                }
                if ((kind == 5 || kind == 2) && pCarrier) {
                    if (fn_801783AC(7) == 1 || fn_801783AC(8) == 1) {
                        odds += pCarrier->mRatings[4] / lbl_803EB008;
                    }
                    odds += (int)(fn_8016B974() * lbl_803EB00C);
                    if (fn_80177FE0().mY - pCarrier->mMotion.mPos.mY < lbl_803EB004) odds = 255;
                }
                if (kind == 6 || kind == 2 || fn_802372EC(0, 255) <= odds) {
                    if (fn_801170E8(p)) return 0;
                }
            } else if (fn_8009F258(p) == 1) {
                fn_801C1F94(&message, 0, 4);
                message.mId = 24;
                message.mUnknown1[0] = 2;
                fn_800F053C(0, p->mpState, &message, p);
                return 0;
            }
        }
    }
    if (state->mUnknown12 != 0.0f) {
        if (state->mUnknown12 == 1.0f &&
            fn_801CFFD0(p->mMotion.mFacing, state->mUnknown8) <= 0xE38E2 &&
            fn_801CFFD0(p->mMotion.mUnknown32, state->mUnknown8) <= 0xE38E2) {
            p->mUnknown512.mUnknown15 = 1;
        }
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
    return 0;
}
