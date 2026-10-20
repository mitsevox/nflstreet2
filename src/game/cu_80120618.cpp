#include "game/Lookup_8012078C.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/fn_80177FE0.h"
#include "game/fn_802270D4.h"

extern "C" {

extern Lookup_8012078C *lbl_803EB09C;
extern float lbl_803ECB08;

int fn_801208C8(Vector_80039F5C *pA, Vector_80039F5C *pB, float speed, Vector_80039F5C *pDir);
int fn_801486A0(void);
float fn_80178A2C(void);
float fn_801CFB18(int angle);
int fn_801CFDD0(float value);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
void fn_80227350(Vector_80039F5C *pOut, Vector_80039F5C *pV, float scale);
void fn_80227690(void *pOut, void *pA, void *pB);
float fn_80237260(int stream);

void fn_80120618(void)
{
    Point_8017886C ball;
    unsigned char i;

    for (i = 0; i < lbl_803EB09C->mUnknown16; i++) {
        lbl_803EB09C->mpUnknown12[i] = 0;
        lbl_803EB09C->mpUnknown0[i] = lbl_803EB09C->mpUnknown4[i] = i;
        lbl_803EB09C->mpUnknown8[i].mUnknown4 = i;
        lbl_803EB09C->mpUnknown8[i].mUnknown0 = 0.0f;
    }
    if (fn_801486A0() == 0) {
        lbl_803EB09C->mUnknown18 = 3;
    } else {
        lbl_803EB09C->mUnknown18 = 0;
    }
    ball = fn_80177FE0();
    if (ball.mX > 0.0f) {
        lbl_803EB09C->mUnknown19 = 0;
    } else {
        lbl_803EB09C->mUnknown19 = 1;
    }
    lbl_803EB09C->mUnknown20 = 0;
}

int fn_80120794(Vector_80039F5C *pA, Vector_80039F5C *pB, Vector_80039F5C *pDir, float speed, float dist,
                float range)
{
    Point_8017886C delta;
    int angle;
    int result;

    fn_80227690(&delta, pB, pA);
    angle = fn_801CFE40(delta.mY, delta.mX);
    if (range > 10.0f && pA->mY < pB->mY) {
        return 0x400000;
    }
    if (dist < lbl_803ECB08 * 0.1f) {
        return angle;
    }
    if (speed == 0.0f) {
        return angle;
    }
    result = fn_801208C8(pA, pB, speed, pDir);
    if (result <= 0x7FFFFF && pA->mY > pB->mY && pA->mY > fn_80178A2C()) {
        fn_80237260(0);
        result = result > 0x400000 ? 0x800000 : 0;
    }
    return result;
}

int fn_801208C8(Vector_80039F5C *pA, Vector_80039F5C *pB, float speed, Vector_80039F5C *pDir)
{
    int dirAngle = fn_801CFE40(pDir->mY, pDir->mX);
    float dirLength = fn_802270A4(pDir);
    Point_8017886C delta;
    int toAngle;
    int backAngle;
    int diff;
    int opposite;
    int wide;
    float ratio;
    int turn;

    fn_80227690(&delta, pA, pB);
    toAngle = fn_801CFE40(delta.mY, delta.mX);
    backAngle = (toAngle + 0x800000) & 0xFFFFFF;
    diff = fn_801CFFD0(dirAngle, toAngle);
    opposite = fn_801CFFD0(0x800000, diff);
    wide = diff > 0x400000;
    if (speed < 1e-7f) {
        speed = 1e-7f;
    }
    if (wide) {
        ratio = fn_801CFB18(opposite);
    } else {
        ratio = fn_801CFB18(diff);
    }
    ratio = ratio * dirLength / speed;
    if (ratio > 1.0f) {
        Vector_80039F5C target;
        Point_8017886C toTarget;

        target.mX = pB->mX;
        target.mY = pB->mY;
        target.mZ = pB->mZ;
        fn_80227350(&target, pDir, 120.0f);
        fn_80227690(&toTarget, &target, pA);
        return fn_801CFE40(toTarget.mY, toTarget.mX) & 0xFFFFFF;
    }
    turn = fn_801CFDD0(ratio);
    return (((toAngle - dirAngle) & 0xFFFFFF) <= 0x7FFFFF ? backAngle + turn : backAngle - turn) & 0xFFFFFF;
}

int fn_80120A50(Point_8017886C *p, Point_8017886C *pA, Point_8017886C *pB, Point_8017886C *pC)
{
    float d0 = p->mX * (pC->mY - pB->mY) + pC->mX * (pB->mY - p->mY) + pB->mX * (p->mY - pC->mY);
    float d1 = pB->mX * (p->mY - pA->mY) + p->mX * (pA->mY - pB->mY) + pA->mX * (pB->mY - p->mY);
    float d2 = pA->mX * (pB->mY - pC->mY) + pB->mX * (pC->mY - pA->mY) + pC->mX * (pA->mY - pB->mY);
    float d3 = p->mX * (pC->mY - pA->mY) + pC->mX * (pA->mY - p->mY) + pA->mX * (p->mY - pC->mY);

    if (d0 >= 0.0f && d1 >= 0.0f && d2 >= 0.0f && d3 >= 0.0f) {
        return 1;
    }
    if (d0 <= 0.0f && d1 <= 0.0f && d2 <= 0.0f && d3 <= 0.0f) {
        return 1;
    }
    return 0;
}

}
