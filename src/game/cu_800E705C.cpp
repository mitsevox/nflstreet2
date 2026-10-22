#include "game/Object_80039F5C.h"
#include "game/cu_80136B1C.h"
#include "game/fn_80178D18.h"
#include "game/fn_801C1F94.h"

extern "C" {
int fn_8013BA58(Object_80137ABC *pBall, int *pOut);
int fn_801787A0(void);
int fn_801783AC(int bit);
int fn_801486A0(void);
unsigned int fn_8011E188(void);
void fn_80227690(void *pOut, void *pA, void *pB);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
extern float lbl_803EAD50;

int fn_800E705C(Object_80039F5C *p)
{
    Object_80039F5C *carrier = fn_80137B40();
    if (p->mIdBytes[3] == 1 && p->mUnknown1032 == 4) return 1;
    Object_80137ABC *ball = fn_801374BC();
    if (fn_8013BA58(ball, 0) == 4 && p == fn_80137B88(ball)) {
        Message_800F01CC message;
        fn_801C1F94(&message, 0, 4);
        message.mId = 23;
        message.mUnknown1[0] = fn_801374E0(ball);
        fn_800F053C(0, p->mpState, &message, p);
        return 1;
    }
    if (!fn_801787A0() && fn_80137B40() && fn_801783AC(0) &&
        fn_801486A0() != 0 && fn_801486A0() != 1 && fn_801486A0() != 2) {
        Message_800F01CC message;
        fn_801C1F94(&message, 0, 4);
        message.mId = 33;
        fn_800F053C(0, p->mpState, &message, p);
        return 1;
    }
    if ((p->mFlags & 0x4000) && fn_801486A0()) return 1;
    p->mUnknown336--;
    if (carrier && !((float)fn_8011E188() <= lbl_803EAD50) && !fn_801787A0() &&
        !(p->mMotion.mUnknown28 >= 0.1f)) {
        int heading;
        if (fn_801486A0() != 1) {
            Vector_80039F5C delta;
            fn_80227690(&delta, &carrier->mMotion.mPos, &p->mMotion.mPos);
            heading = fn_801CFE40(delta.mY, delta.mX);
        } else {
            heading = p->mUnknown2913 ? 0x800000 : 0;
        }
        if (fn_801CFFD0(p->mMotion.mFacing, heading) > 0x38E38) {
            if (((p->mMotion.mFacing - heading) & 0xFFFFFF) > 0x800000)
                p->mMotion.mFacing += 0x38E38;
            else p->mMotion.mFacing -= 0x38E38;
        } else p->mMotion.mFacing = heading;
    }
    if (p->mUnknown336 < 0) return 1;
    if (fn_801486A0() == 0) {
        p->mUnknown512.mUnknown0 = 0.0f;
        p->mUnknown512.mUnknown14 = 3;
        p->mUnknown512.mUnknown4 = p->mMotion.mUnknown32;
        p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
        unsigned short count = fn_80178D70(0);
        for (unsigned short i = 0; i < count; i++) {
            if (fn_80039F5C(0, i)->mpState->mId == 97) return 1;
        }
    }
    return 0;
}
}
