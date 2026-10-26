#include <math.h>
#include "engine/vec.h"
#include "game/Class_80297CE8.h"
#include "game/Input_800B6D34.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/fn_800B65A0.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_801BE60C.h"
#include "game/fn_802270D4.h"

/* Player block at +336 as fn_800E513C uses it. */
struct State_800E513C {
    char mUnknown0[3];
    unsigned char mUnknown3;
};

extern "C" {
int fn_800C05F4(void);
Object_80039F5C *fn_800B6544(int index);
int fn_80178320(void);
int fn_80178308(void);
int fn_801784C4(void);
Point_8017886C fn_80177FFC(int team);
int fn_800E1870(Object_80039F5C *p);
void fn_800E3AE8(Object_80039F5C *p, int a, int b);
void fn_800E4120(Object_80039F5C *p, State_800E513C *pState, int heading, float speed);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
int fn_801BE068(void *a, void *b, void *c, unsigned short d, float f, void *e);
extern float lbl_803EAD4C;
}

extern "C" int fn_800E513C(Object_80039F5C *p)
{
    State_800E513C *pState = (State_800E513C *)&p->mUnknown336;
    Input_800B6D34 input;
    Point_8017886C dir;
    float limit;
    float speed;
    int near;

    if (fn_800C05F4() != 0) {
        return 0;
    }
    if (fn_800AD9B4() == 8) {
        return 0;
    }
    if (lbl_803EABA4->fn_800C043C(p->mIdBytes[2]) && p->mIdBytes[2] == fn_80178320() &&
        p == fn_800B6544(fn_800B65A0(p->mIdBytes[2]))) {
        return 0;
    }
    fn_800B6D34(p, &input);
    dir.mX = dir.mY = 0.0f;
    if (input.mUnknown4 != 0.0f || input.mUnknown8 != 0.0f) {
        dir.mX = input.mUnknown4;
        dir.mY = input.mUnknown8;
    } else {
        if (input.mUnknown0 & 1) {
            dir.mY = 1.0f;
        }
        if (input.mUnknown0 & 2) {
            dir.mY = -1.0f;
        }
        if (input.mUnknown0 & 4) {
            dir.mX = -1.0f;
        }
        if (input.mUnknown0 & 8) {
            dir.mX = 1.0f;
        }
    }
    if (fn_800E1870(p)) {
        limit = 2.25f;
    } else {
        limit = lbl_803EAD4C;
    }
    near = 0;
    if (p->mIdBytes[2] == fn_80178320() &&
        !(fabsf(p->mMotion.mPos.mY - fn_80177FFC(p->mIdBytes[2]).mY) > limit)) {
        near = dir.mY < 0.0f;
    }
    if (near) {
        dir.mX = dir.mY = 0.0f;
    }
    speed = fn_802270A4(&dir) > 1.0f ? 1.0f : fn_802270A4(&dir);
    if (dir.mY != 0.0f || dir.mX != 0.0f) {
        p->mFlags = (p->mFlags | 0x400) & ~0x10;
        int heading = fn_801CFE40(dir.mY, dir.mX) - input.mUnknown20;
        if (fn_801784C4()) {
            heading -= 0x800000;
        }
        heading &= 0xFFFFFF;
        int turn = fn_801CFFD0(heading, p->mMotion.mFacing);
        if (turn > 0x56C16B && speed > 0.6f) {
            speed = 0.6f;
        }
        int facing = p->mIdBytes[2] == fn_80178308() ? 0x400000 : 0xC00000;
        p->mUnknown512.mUnknown14 = 3;
        p->mUnknown512.mUnknown8 = facing;
        p->mUnknown512.mUnknown0 = speed;
        p->mUnknown512.mUnknown4 = heading;
        if (turn >= 0x200000 && turn <= 0x600000) {
            if (fn_801BE648(p->mpUnknown792) == 86) {
                if (pState->mUnknown3 == 0) {
                    fn_800E4120(p, pState, heading >= 0x400000 && heading <= 0xC00000 ? 0x800000 : 0, 0.975f);
                    return 0;
                }
            } else if (pState->mUnknown3 == 0) {
                p->mFlags &= ~0x40000;
                return 0;
            }
            p->mUnknown512.mUnknown14 = 0;
        } else {
            p->mFlags &= ~0x40000;
            pState->mUnknown3 = 0;
        }
    } else if (fn_801BE648(p->mpUnknown792) == 189 && (p->mFlags & 4)) {
        p->mFlags &= ~4;
        if (fn_801CFFD0(p->mMotion.mFacing, 0xC00000) > 0xAAAAA) {
            fn_800E3AE8(p, 8, 1);
        } else if (pState->mUnknown3 != 0 || fn_800E1870(p)) {
            fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 86, 1.0f, p);
            pState->mUnknown3 = 0;
        } else {
            int close = 0;
            if (p->mMotion.mPos.mY < fn_80177FFC(p->mIdBytes[2]).mY + 2.5f) {
                close = fabsf(p->mMotion.mPos.mX) < 8.0f;
            }
            if (close) {
                fn_800E3AE8(p, 8, 1);
            } else if (!(p->mFlags & 0x40000)) {
                fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 85, 1.0f, p);
            }
        }
    }
    return 0;
}
