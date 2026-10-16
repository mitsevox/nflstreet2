#include "game/fn_801248D4.h"
#include "game/Queue_800EFE0C.h"
#include "game/State_800FDA58.h"
#include <math.h>
#include <string.h>
#include "game/fn_800B65A0.h"
#include "game/Class_80297CE8.h"
#include "game/Command_800CEE74.h"
#include "game/Input_800B6D34.h"
#include "game/Lookup_8012078C.h"
#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/Plan_80121264.h"
#include "game/Record_800B15FC.h"
#include "game/Record_8011F518.h"
#include "game/Team_80167A8C.h"
#include "game/State_803EB098.h"
#include "game/cu_80067C10.h"
#include "game/Query_800CE770.h"
#include "game/Table_80089904.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800670B4.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_800F06F4.h"
#include "game/fn_80163E94.h"
#include "game/fn_8016871C.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80178D18.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_802270D4.h"
#include "game/fn_80227638.h"
#include "game/fn_8022781C.h"
#include "game/fn_802372EC.h"
#include "game/fn_80238174.h"
#include "game/Record_800DB60C.h"
#include "game/fn_801BE60C.h"

extern "C" {
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
void fn_80227690(void *pOut, void *pA, void *pB);
extern float lbl_803ECB08;
void fn_80227538(Point_8017886C *pOut, int angle, float length);
float fn_80178A08(void);
extern float lbl_803EA2C4;
float fn_80178A08(void);
void fn_8022732C(void *pPoint, void *pVelocity, float scale);
void fn_80227538(Point_8017886C *pOut, int angle, float length);
float fn_801CFB94(int angle);
void fn_80103F80(Object_80137ABC *pBall, Vector_80039F5C pos, Vector_80039F5C offset, int angle, Vector_80039F5C *pOut,
                 Object_80039F5C *pTarget, float length, float speed);
float fn_80103DD8(Object_80039F5C *p, Object_80039F5C *pOther, short *pCount, float scale);
float fn_8016D9F4(Object_80039F5C *p, float a, float b);
}

extern "C" void fn_80101AE0(Object_80039F5C *p, float *pOut);

extern "C" unsigned int fn_8011E188(void);

extern float lbl_803EAE8C;

extern float lbl_803EAE90;

extern float lbl_803EAE94;

extern float lbl_803EAE98;

extern float lbl_803EAE9C;

extern float lbl_803EAEB8;

extern "C" float fn_8016D9F4(Object_80039F5C *p, float a, float b);

extern "C" float fn_800C49EC(float limit);

extern "C" float fn_800CAAFC(Object_80039F5C *p);

extern "C" float fn_801CFB18(int angle);

extern "C" int fn_801CFDD0(float);

extern "C" int fn_8012CAA4(Object_80039F5C *p);

extern "C" int fn_8012CAAC(Object_80039F5C *p);

extern "C" int fn_8012CB50(Message_800F01CC *pMessage);

extern "C" void fn_8012CB98(int a, int b, int angle, Point_8017886C *pOut);

extern "C" int fn_8012CC04(int a);

extern "C" int fn_8012CC50(Object_80039F5C *p);

extern "C" void fn_8012CD4C(Object_80039F5C *p, Point_8017886C *pOut);

struct State_80104328 {
    Point_8017886C mTarget;
};
extern "C" {
float fn_801CFB94(int angle);
}

extern "C" float fn_80103DD8(Object_80039F5C *p, Object_80039F5C *pOther, short *pCount, float scale)
{
    Vector_80039F5C delta;
    float factor = 0.0f;
    float distance;
    float spread;
    float base;
    float result;

    fn_8011F4F8(fn_801374E0(fn_801374BC()));
    fn_802276B4(&delta, &p->mMotion.mPos, &pOther->mMotion.mPos);
    distance = fn_802270A4(&delta);
    fn_801CFE40(delta.mY, delta.mX);
    *pCount = *pCount < 5 ? 5 : (*pCount > 20 ? 20 : *pCount);
    spread = (*pCount - 5.0f) * scale * (1.0f / 15.0f);
    fn_80101AE0(p, &factor);
    base = (lbl_803EAEB8 - distance) * (lbl_803EAEB8 - distance) / (lbl_803EAEB8 * lbl_803EAEB8)
        * (lbl_803EAE94 - lbl_803EAE98) + lbl_803EAE98;
    result = spread * (factor * (lbl_803EAE8C - base)) + base;
    result *= 1.1f;
    result *= lbl_803EA2C4;
    if ((p->mFlags & 0x4000) && fn_8011E188() < lbl_803EAE9C && result > lbl_803EAE90) {
        result = lbl_803EAE90;
    }
    return result;
}

extern "C" void fn_80103F80(Object_80137ABC *pBall, Vector_80039F5C pos, Vector_80039F5C velocity, int angle,
                            Vector_80039F5C *pOut, Object_80039F5C *p, float speed, float ballSpeed)
{
    Vector_80039F5C ball;
    Point_8017886C delta;
    int behind;
    int running;
    float runSpeed;
    float distance;
    float closing;
    float time;
    float reach;
    float slack;
    float burst;
    int turn;

    pOut->mX = pOut->mY = pOut->mZ = 0.0f;
    behind = pos.mY < fn_80177FE0().mY + 13.0f && fn_801CFFD0(angle, 0xC00000) <= 0x271C70;
    if (behind) {
        pOut->mX = pos.mX;
        pOut->mY = pos.mY;
        pOut->mZ = 1.3f;
        return;
    }
    running = speed > fn_8016D9F4(p, 0.14f, 1.0f) && angle <= 0x7FFFFF;
    if (speed > fn_800C49EC(lbl_803ECB08)) {
        speed = fn_800C49EC(lbl_803ECB08);
    }
    fn_80137D58(pBall, &ball);
    runSpeed = speed;
    fn_802276B4(&ball, &ball, &pos);
    distance = fn_802270A4(&ball);
    if (running) {
        runSpeed += (fn_8016D9F4(p, 1.0f, 1.0f) - runSpeed) * fn_801CFB18(angle);
    }
    runSpeed /= lbl_803EA2C4;
    if (runSpeed >= ballSpeed) {
        pOut->mX = pos.mX;
        pOut->mY = pos.mY;
        pOut->mZ = 1.3f;
        return;
    }
    turn = fn_801CFFD0(angle, fn_801CFE40(ball.mY, ball.mX));
    if (turn > 0x400000) {
        turn = fn_801CFFD0(0x800000, turn);
        closing = ballSpeed * fn_801CFB94(fn_801CFDD0(runSpeed * fn_801CFB18(turn) / ballSpeed)) - runSpeed * fn_801CFB94(turn);
    } else {
        closing = ballSpeed * fn_801CFB94(fn_801CFDD0(runSpeed * fn_801CFB18(turn) / ballSpeed)) + runSpeed * fn_801CFB94(turn);
    }
    time = distance / closing / lbl_803EA2C4;
    pOut->mX = pos.mX;
    pOut->mY = pos.mY;
    fn_8022732C(pOut, &velocity, time);
    pOut->mZ = 1.3f;
    fn_80227690(&delta, pOut, &p->mMotion.mPos);
    distance = fn_802270A4(&delta);
    burst = fn_800CAAFC(p);
    slack = runSpeed - fn_8016D9F4(p, 0.72f, 1.0f);
    if (slack < 0.0f) {
        slack = 0.0f;
    }
    reach = (slack * burst + fn_8016D9F4(p, 0.72f, 1.0f) * time) * 0.75f;
    if (reach < distance) {
        float short_ = distance - reach;

        pOut->mX -= short_ * fn_801CFB94(angle);
        pOut->mY -= short_ * fn_801CFB18(angle);
    }
    pOut->mX = pOut->mX < 1.0f - fn_80178A08()
                   ? 1.0f - fn_80178A08()
                   : (pOut->mX > fn_80178A08() - 1.0f ? fn_80178A08() - 1.0f : pOut->mX);
}

extern "C" void fn_80104328(Object_80039F5C *p, unsigned int count, int *pTime, Vector_80039F5C *pPos, int *pAngle)
{
    State_80039F5C *pQueue = p->mpState;
    float speed = fn_8016D9F4(p, 1.0f, 1.0f);
    State_80039F5C *pEntry;
    Point_8017886C offset;
    unsigned char i;

    pPos->mX = pPos->mY = pPos->mZ = 0.0f;
    pEntry = pQueue;
    switch (pEntry->mId) {
    case 19: {
        State_80104328 *pState = (State_80104328 *)&p->mUnknown336;

        offset.mX = pState->mTarget.mX;
        offset.mY = pState->mTarget.mY;
        *pTime = (int)(fn_8022781C(&offset, &p->mMotion.mPos) / speed);
        pPos->mX = pState->mTarget.mX;
        pPos->mY = pState->mTarget.mY;
        *pAngle = pEntry->mUnknown2 << 17 & 0xFE0000;
        break;
    }
    case 20:
        fn_8012CD4C(p, &offset);
        pPos->mX = offset.mX;
        pPos->mY = offset.mY;
        if ((unsigned int)(pEntry->mUnknown2 - 8) <= 1) {
            *pAngle = fn_8012CAAC(p);
        } else {
            *pAngle = fn_8012CAA4(p);
        }
        *pTime = fn_8012CC50(p);
        break;
    default:
        *pTime = 0;
        break;
    }
    for (i = 1; i <= count; i++) {
        pEntry = &pQueue[i];
        if (pEntry->mId == 20) {
            State_80039F5C *pPrev = &pQueue[i - 1];
            int kind = pEntry->mUnknown2;
            unsigned char type = pEntry->mUnknown1;

            if (pPrev->mId == 19) {
                fn_8012CB98(kind, type, pPrev->mUnknown2 << 17 & 0xFE0000, &offset);
                *pTime += fn_8012CC04(type);
                pPos->mX += offset.mX;
                pPos->mY += offset.mY;
                *pAngle += fn_8012CB50((Message_800F01CC *)pEntry);
            }
        } else if (pEntry->mId == 19) {
            float distance = (unsigned int)pEntry->mUnknown1 * 0.125f;

            *pTime += (int)(distance / speed);
            *pAngle = pEntry->mUnknown2 << 17 & 0xFE0000;
            fn_80227538(&offset, *pAngle, distance);
            pPos->mX += offset.mX;
            pPos->mY += offset.mY;
        }
    }
}
