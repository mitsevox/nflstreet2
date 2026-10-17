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

/* Object pointer, three positions, a pair and a float filled by fn_800F39FC
   and passed to fn_800F2EC8, fn_800F30AC, fn_800F3284, fn_800F3838,
   fn_800F3A6C, fn_800F3B54, fn_800F3D38, fn_800F3F90 and fn_800F4038. Only
   the accessed prefix is declared; the size is unknown. */
struct Points_800F3A6C {
    Object_80137ABC *mpUnknown0;
    Vector_80039F5C mUnknown4;
    Vector_80039F5C mUnknown16;
    Vector_80039F5C mUnknown28;
    Point_8017886C mUnknown40;
    float mUnknown48;
};
extern "C" {
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
void fn_80227690(void *pOut, void *pA, void *pB);
int fn_8013BA58(Object_80137ABC *pBall, int *pOut);
void fn_800C89F0(Object_80039F5C *p, int angle, int a, int b, float scale);
void fn_8013AA00(Object_80137ABC *pBall, float height, float *pTime, Vector_80039F5C *pLanding);
}

extern "C" void fn_801074B4(Object_80039F5C *p, Points_800F3A6C *pInfo) {
    Object_800B26B0 *pMotion;
    Point_8017886C delta;
    int angle;
    float distance;
    float strength;
    Object_80039F5C *pOther = fn_80137B88(pInfo->mpUnknown0);

    if (pOther == 0) {
        return;
    }
    pMotion = &p->mMotion;
    fn_80227690(&delta, &pOther->mMotion.mPos, &pMotion->mPos);
    angle = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
    distance = fn_802270A4(&delta);
    if (fn_801CFFD0(angle, pMotion->mFacing) > 0x555554 && distance >= 3.5f) {
        return;
    }
    strength = 0.0f;
    if (pMotion->mPos.mY > pOther->mMotion.mPos.mY) {
        if (distance < 8.0f) {
            distance -= 1.0f;
            if (distance < 0.0f) {
                distance = 0.0f;
            }
            strength = distance / 8.0f;
            strength = 1.0f - strength;
        }
        if (fn_801CFFD0(pMotion->mFacing, 0x400000) <= 0x1FFFFF && fn_8013BA58(pInfo->mpUnknown0, 0) == 4) {
            fn_80227690(&delta, &pInfo->mUnknown16, &pMotion->mPos);
            angle = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
        }
    } else if (distance < 2.5f) {
        distance -= 1.0f;
        if (distance < 0.0f) {
            distance = 0.0f;
        }
        strength = distance / 2.5f;
        strength = 1.0f - strength;
    }
    if (strength != 0.0f) {
        fn_800C89F0(p, angle, 2, 0, strength);
    }
}

extern "C" void fn_80107680(Points_800F3A6C *pInfo, int index) {
    pInfo->mpUnknown0 = fn_80137ABC(index);
    fn_80138064(pInfo->mpUnknown0, &pInfo->mUnknown4);
    fn_8013AA00(pInfo->mpUnknown0, 1.5f, &pInfo->mUnknown48, (Vector_80039F5C *)&pInfo->mUnknown40);
    fn_80137EC4(pInfo->mpUnknown0, &pInfo->mUnknown28);
    fn_80137D58(pInfo->mpUnknown0, &pInfo->mUnknown16);
}
