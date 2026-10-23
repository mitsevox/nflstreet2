#include "game/Object_80039F5C.h"
#include "game/Item_80097440.h"
#include "game/Object_8017886C.h"
#include "game/fn_800F06F4.h"
#include "game/fn_801BE60C.h"
#include "game/cu_80136B1C.h"
#include "game/fn_80177FE0.h"

extern "C" {
float fn_80237260(int stream);
int fn_800A84C0(int team);
float fn_800C4A70(Object_80039F5C *p, int index);
Item_80097440 *fn_8009A63C(int ref);
int fn_800A7F30(int team);
int fn_800A851C(int team, Object_80039F5C *p);
int fn_800C53D8(Object_80039F5C *p);
int fn_800D0B90(Object_80039F5C *p);
Object_80039F5C *fn_80114E7C(Object_80039F5C *p);
int fn_801486A0(void);
float fn_80178A08(void);
int fn_801CFFD0(int a, int b);

extern float lbl_803EABFC;
extern float lbl_803EAC00;
extern float lbl_803EAC04;
extern float lbl_803EAC08;
}

extern "C" int fn_800C4D54(Object_80039F5C *p)
{
    int result = 0;
    float chance = fn_80237260(0) * (1.0f / 255.0f);
    float value = chance * p->mRatings[0];

    if (fn_800A84C0(p->mIdBytes[2]) != 0) {
        if (value < fn_800C4A70(p, 0)) {
            result = 1;
        } else if (value < fn_800C4A70(p, 1)) {
            result = 2;
        }
    }
    return result;
}


extern "C" int fn_800C4EE8(Object_80039F5C *p, Object_80039F5C *pOther, int roll, int chance)
{
    int result = 1;
    Point_8017886C point;
    int high;
    int low;
    float ratio;

    if (fn_801486A0() == 0 && (p == 0 || fn_800F06F4(0, p->mpState, 51, 0xFFFF) != 0xFFFF)) {
        result = 0;
    }
    point = fn_80177FE0();
    high = chance < roll ? roll : chance;
    low = chance > roll ? roll : chance;
    if (high != 0) {
        ratio = (float)low / (float)high;
    } else {
        ratio = 0.0f;
    }
    if (!(ratio > 0.65f)) {
        result = 0;
    }
    if (fn_800C53D8(pOther) || (!fn_800A7F30(pOther->mIdBytes[2]) && fn_800A851C(p->mIdBytes[2], p))) {
        result = 0;
    }
    if (fn_800D0B90(pOther)) {
        result = 0;
    }
    if (fn_80137B40() != pOther) {
        result = 0;
    }
    if (fn_801CFFD0(pOther->mMotion.mFacing, 0x400000) > (int)(lbl_803EABFC * 46603.37890625f)) {
        result = 0;
    }
    if (fn_801CFFD0(pOther->mMotion.mFacing, 0x400000) > (int)(lbl_803EAC00 * 46603.37890625f) &&
        fn_801CFFD0(pOther->mMotion.mFacing, 0x400000) < (int)(lbl_803EAC04 * 46603.37890625f) &&
        fabsf(pOther->mMotion.mPos.mX) > fn_80178A08() - lbl_803EAC08) {
        result = 0;
    }
    if (fn_80114E7C(pOther)) {
        result = 0;
    }
    if (pOther->mpState->mId == 15 || pOther->mpState->mId == 18) {
        result = 0;
    }
    if ((pOther->mpState[1].mId == 15 || pOther->mpState[1].mId == 18) && pOther->mMotion.mPos.mY < point.mY) {
        result = 0;
    }
    if (p->mUnknown1160.mUnknown52) {
        result = 0;
    }
    if (fn_801CFFD0(pOther->mMotion.mFacing, p->mMotion.mFacing) > 0x400000) {
        if (fn_801BE648(pOther->mpUnknown792) == 225) {
            result = 0;
        }
        if (fn_801BE648(pOther->mpUnknown792) == 67 && fn_8009A63C(pOther->mpState->mUnknown2)->mUnknown4 == 4) {
            result = 0;
        }
    }
    return result;
}
