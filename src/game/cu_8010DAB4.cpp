#include "engine/cu_801B9F00.h"
#include "game/fn_801248D4.h"
#include "game/Queue_800EFE0C.h"
#include "game/State_800FDA58.h"
#include <math.h>
#include <string.h>
#include "game/fn_800B65A0.h"
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
#include "game/Block_801BE60C.h"

#define CLAMP(x, lo, hi) ((x) < (lo) ? (lo) : ((x) > (hi) ? (hi) : (x)))

/* Steering output fn_8010DAB4 fills for fn_8010E59C: a speed scale, the
   heading to run on, the heading to face and a flag byte at +22. */
struct Steer_8010DAB4 {
    float mSpeed;
    int mHeading;
    int mFacing;
    char mUnknown12[10];
    unsigned char mUnknown22;
};

extern "C" {
int fn_80177F70(void);
float fn_80178A08(void);
int fn_80178320(void);
int fn_801783AC(int flag);
int fn_801787A0(void);
int fn_8011F1A4(void);
int fn_8013BA58(Object_80137ABC *pBall, int which);
int fn_801CFFD0(int a, int b);
void fn_80227538(Point_8017886C *pOut, int angle, float length);
void fn_80227690(void *pOut, void *pA, void *pB);
void fn_8010E15C(Object_80039F5C *p, Steer_8010DAB4 *pOut);
extern float lbl_803ECB08;
}

/* Partial: one instruction off. The target loads the player's y straight
   into f12 at 0x8010DC38; this source loads it into f0 and copies it with
   fmr before the compare. Everything else matches. */
extern "C" void fn_8010DAB4(Object_80039F5C *p, Steer_8010DAB4 *pOut) {
    Object_80039F5C *pCarrier = fn_80137B40();
    Object_800B26B0 *pMotion = &p->mMotion;
    Object_80137ABC *pBall = fn_801374BC();
    int open = fn_80177F70() == 0;
    int ahead = open;
    int last;
    Object_80039F5C *pMate;
    Vector_80039F5C ballPos;
    Vector_80039F5C vel;
    Point_8017886C target;

    pOut->mUnknown22 = 0;
    if (!pCarrier && fn_8013BA58(pBall, 0) == 3) pCarrier = fn_80137B88(pBall);
    if (pCarrier) {
        Object_800B26B0 *pCarrierMotion = &pCarrier->mMotion;

        if (pCarrier->mpState->mId == 1) {
            fn_80137D58(fn_801374BC(), &ballPos);
            if (pCarrier->mMotion.mPos.mX < pMotion->mPos.mX) {
                target.mX = pCarrier->mMotion.mPos.mX + 3.0f;
            } else {
                target.mX = pCarrier->mMotion.mPos.mX - 3.0f;
            }
            target.mX = CLAMP(target.mX, 2.0f - fn_80178A08(), fn_80178A08() - 2.0f);
            last = (unsigned int)fn_80178D70(fn_80178320()) / 2;
            last--;
            if (last < 0) last = 0;
            pMate = fn_80039F5C(fn_80178320(), fn_8012078C()->mpUnknown4[last]);
            if (pMate->mMotion.mPos.mY < pCarrierMotion->mPos.mY) {
                ahead = 0;
                target.mY = pCarrierMotion->mPos.mY - 2.0f;
            } else if (pMotion->mPos.mY < pCarrierMotion->mPos.mY) {
                target.mY = pCarrierMotion->mPos.mY + 3.0f;
                if (pCarrierMotion->mUnknown32 > 0x200000 && pCarrierMotion->mUnknown32 < 0x600000) {
                    target.mY += 3.0f;
                }
            } else if (pCarrierMotion->mUnknown44 <= 0.0f && pCarrierMotion->mUnknown28 > 0.0f) {
                target.mY = pMotion->mPos.mY - 3.0f;
            } else {
                target.mY = pMotion->mPos.mY + 3.0f;
            }
            fn_80227690(&target, &target, &pMotion->mPos);
            pOut->mHeading = target.Heading();
        } else {
            pOut->mHeading = pMotion->mFacing & 0xFFFFFF;
            pOut->mHeading = CLAMP(pOut->mHeading, 0x200000, 0x600000);
        }
        pOut->mHeading &= 0xFFFFFF;
        if (pMotion->mPos.mY < pCarrierMotion->mPos.mY || fabsf(pCarrierMotion->mPos.mX - pMotion->mPos.mX) > 8.0f) {
            if (pOut->mHeading <= 0x7FFFFF) {
                if (pOut->mHeading <= 0x3FFFFF) {
                    pOut->mHeading += fn_801CFFD0(pOut->mHeading, 0x400000) / 3;
                } else {
                    pOut->mHeading -= fn_801CFFD0(pOut->mHeading, 0x400000) / 3;
                }
            }
            pOut->mSpeed = 0.72f;
            if (fn_801783AC(0) && !open) pOut->mSpeed = 0.4f;
        } else {
            pOut->mSpeed = 0.72f;
        }
        pMate = fn_80039F5C(fn_80178320(), fn_8012078C()->mpUnknown4[0]);
        if (p->mMotion.mPos.mY > pMate->mMotion.mPos.mY && fn_801CFFD0(pOut->mHeading, 0x400000) <= 0x3FFFFF) {
            target.mX = pCarrierMotion->mPos.mX;
            target.mX = CLAMP(target.mX, 2.0f - fn_80178A08(), fn_80178A08() - 2.0f);
            target.mY = pMate->mMotion.mPos.mY;
            fn_80227690(&target, &target, &p->mMotion.mPos);
            pOut->mHeading = target.Heading();
        }
        fn_8010E15C(p, pOut);
        pOut->mHeading &= 0xFFFFFF;
        if (open && ahead && pOut->mHeading > 0x800000 && pMotion->mPos.mY > pCarrierMotion->mPos.mY) {
            pOut->mFacing = 0x400000;
        } else {
            pOut->mFacing = pOut->mHeading;
        }
    } else {
        if (fn_801787A0()) {
            pOut->mHeading = pMotion->mFacing;
            pOut->mSpeed = pMotion->mUnknown28 / lbl_803ECB08;
        } else {
            pOut->mSpeed = 0.72f;
            if (!fn_80138064(pBall, &ballPos)) {
                fn_80137D58(pBall, &ballPos);
                vel.mX = vel.mY = vel.mZ = 0.0f;
            } else {
                fn_80137EC4(pBall, &vel);
                if (fn_8013BA58(pBall, 0) == 4) pOut->mSpeed = 0.4f;
            }
            if (open && vel.mZ < 0.0f) {
                ballPos.mX = (ballPos.mX + pMotion->mPos.mX) * 0.5f;
                ballPos.mY += 8.0f;
            } else if (fn_8013BA58(pBall, 0) == 4) {
                ballPos.mX = (ballPos.mX + pMotion->mPos.mX) * 0.5f;
                ballPos.mY += 4.0f;
            } else {
                fn_80227690(&target, &pMotion->mPos, &ballPos);
                fn_80227538(&target, target.Heading(), 5.0f);
                ballPos.mX += target.mX;
                ballPos.mY += target.mY;
            }
            fn_80227690(&target, &ballPos, &pMotion->mPos);
            pOut->mHeading = target.Heading();
            if (!fn_8011F1A4() && fn_802270A4(&target) < 1.0f) pOut->mSpeed = 0.0f;
        }
        fn_8010E15C(p, pOut);
        pOut->mFacing = pOut->mHeading;
    }
}
