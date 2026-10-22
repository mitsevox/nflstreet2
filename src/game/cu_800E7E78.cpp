#include "game/State_800D7A4C.h"
#include "game/Object_80039F5C.h"
#include "game/cu_80136B1C.h"
#include "game/fn_80177FE0.h"

extern "C" {
float fn_8022781C(void *pA, void *pB);
void fn_80227690(void *pOut, void *pA, void *pB);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
int fn_800ACD04(Object_80039F5C *p);
int fn_801783AC(int bit);
int fn_80178320(void);
extern unsigned int lbl_803EAD78;
extern float lbl_803EAD7C;
extern unsigned char lbl_803EAD58[8];

void fn_800E7E78(Object_80039F5C *p, State_800D7A4C *state)
{
    if (state->mUnknown5 != 3) return;
    Vector_80039F5C point;
    Object_80039F5C *carrier = fn_80137B40();
    if (carrier) {
        point.mX = carrier->mMotion.mPos.mX;
        point.mY = carrier->mMotion.mPos.mY;
        float distance = fn_8022781C(&carrier->mMotion.mPos, &p->mMotion.mPos);
        if (!(distance <= 10.0f)) distance = 10.0f;
        float scale = distance * ((float)lbl_803EAD78 * 0.1f);
        point.mX += carrier->mMotion.mUnknown40 * scale;
        point.mY += carrier->mMotion.mUnknown44 * scale;
    } else fn_80137D58(fn_801374BC(), &point);
    Vector_80039F5C delta;
    fn_80227690(&delta, &point, &p->mMotion.mPos);
    int heading = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
    int limit = fn_800ACD04(p);
    Point_8017886C origin = fn_80177FE0();
    if (!(point.mY >= origin.mY) && !fn_801783AC(0)) limit *= (int)lbl_803EAD7C;
    int step;
    if (fn_801CFFD0(heading, p->mMotion.mFacing) <= limit)
        step = fn_801CFFD0(heading, p->mMotion.mFacing);
    else step = limit;
    int facing;
    if (((heading - p->mMotion.mFacing) & 0xFFFFFF) > 0x800000)
        facing = p->mMotion.mFacing - step;
    else facing = p->mMotion.mFacing + step;
    facing &= 0xFFFFFF;
    int remaining = (heading - facing) & 0xFFFFFF;
    p->mUnknown512.mUnknown4 = facing;
    p->mUnknown512.mUnknown0 = 1.0f;
    p->mUnknown512.mUnknown14 = 6;
    p->mUnknown512.mUnknown8 = facing;
    state->mUnknown9 = lbl_803EAD58[((remaining + 0x100000) >> 21) & 7];
    if (p->mIdBytes[2] == fn_80178320()) {
        if (state->mUnknown9 == 2) state->mUnknown9 = 3;
        else if (state->mUnknown9 == 7) state->mUnknown9 = 6;
    }
}
}
