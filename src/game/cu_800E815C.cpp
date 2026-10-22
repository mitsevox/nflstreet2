#include "game/Object_80039F5C.h"
#include "game/cu_80136B1C.h"
#include "game/fn_80178D18.h"
#include "game/fn_801C1F94.h"
#include "game/fn_802372EC.h"

extern "C" {
int fn_800E7C84(Object_80039F5C *p);
int fn_800E7D80(Object_80039F5C *p);
float fn_80178298(void);
float fn_80178A2C(void);
int fn_80178320(void);
Object_80039F5C *fn_801245DC(Object_80039F5C *p, int team, int a, unsigned char count, int angle, float *pOut, int b);
void fn_80227690(void *pOut, void *pA, void *pB);
float fn_802270A4(void *p);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
int fn_8013BA58(Object_80137ABC *pBall, int *pOut);
void fn_800D0BF4(Object_80039F5C *p, int a, int b);
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *message, Object_80039F5C *p);
extern unsigned char lbl_803EAD68[5];

int fn_800E815C(Object_80039F5C *p, int unused, int mode)
{
    if (!fn_800E7C84(p) || !fn_800E7D80(p)) return 0;
    Message_800F01CC message;
    fn_801C1F94(&message, 0, 4);
    message.mId = 12;
    Object_80039F5C *carrier = fn_80137B40();
    unsigned char choice;
    unsigned char kind;
    if (p == carrier) {
        float distance = fn_80178298() - p->mMotion.mPos.mY;
        choice = 2;
        kind = 1;
        if (distance <= 0.0f || !(distance < 4.0f)) fn_80178A2C();
        int team = fn_80178320();
        unsigned char count = fn_80178D18(fn_80178320());
        float range;
        Object_80039F5C *other = fn_801245DC(p, team, 0, count, 0x18E38E, &range, 0);
        if (other && !(range >= 3.0f) && (other->mFlags & 0x800)) kind = 2;
    } else if (carrier && p->mIdBytes[2] == fn_80178320()) {
        Vector_80039F5C delta;
        fn_80227690(&delta, &carrier->mMotion.mPos, &p->mMotion.mPos);
        kind = 3;
        choice = 1;
        int heading = fn_801CFE40(delta.mY, delta.mX);
        if (fn_801CFFD0(heading, p->mMotion.mFacing) <= 0x3FFFFF) fn_802270A4(&delta);
    } else {
        Vector_80039F5C point;
        fn_80138064(fn_801374BC(), &point);
        Vector_80039F5C delta;
        fn_80227690(&delta, &point, &p->mMotion.mPos);
        if (!(fn_802270A4(&delta) >= 8.0f)) fn_8013BA58(fn_801374BC(), 0);
        choice = 2;
        kind = 4;
    }
    if (choice == 0) choice = fn_802372EC(0, 3) + 1;
    fn_800D0BF4(p, mode, 12);
    message.mUnknown1[0] = kind;
    message.mUnknown1[1] = choice;
    message.mUnknown1[2] = mode == 0 ? 0 : lbl_803EAD68[fn_802372EC(0, 5)];
    fn_800F00D4(0, p->mpState, &message, p);
    return 1;
}
}
