#include "game/Lookup_8012078C.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/Query_800CE770.h"
#include "game/State_803EB098.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80238174.h"

extern "C" {

extern unsigned char lbl_803EB024;
extern State_803EB098 *lbl_803EB098;

void fn_800A5A68(void *p);
int fn_800CE4A8(Query_800CE770 *pQuery);
void fn_8011E1BC(Object_80039F5C *p, Object_80039F5C *pA, Object_80039F5C *pB, int value);
void fn_8011E33C(Object_80039F5C *p, Object_80039F5C *pOther, int value);
int fn_8011A994(Object_80039F5C *p, Object_80039F5C *pOther);
unsigned char fn_8011EE18(Object_80039F5C *p, Object_80039F5C *pCarrier);
int fn_8011EFD4(void *p, void *q);
int fn_8011F1CC(void);
Object_80039F5C *fn_80137B40(void);
unsigned char fn_801383C8(void);
int fn_80178320(void);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
void fn_80227384(Point_8017886C *pOut, Point_8017886C *pIn, int angle);
void fn_80227690(void *pOut, void *pA, void *pB);
void *fn_8023816C(void *pHandle);

int fn_8011EC68(Object_80039F5C *p, Object_80039F5C *pOther)
{
    int result = 0;
    Object_80039F5C *pCarrier;

    if (fn_8011A994(p, pOther) && (pCarrier = fn_80137B40()) != 0) {
        Point_8017886C delta;
        int angle;

        fn_80227690(&delta, &p->mMotion.mPos, &pOther->mMotion.mPos);
        angle = fn_801CFE40(delta.mY, delta.mX);
        if (fn_801CFFD0(pOther->mUnknown512.mUnknown4, angle) >= (int)(lbl_803EB024 * (16777216.0f / 360.0f))) {
            Point_8017886C toBall;
            Point_8017886C ball;

            ball = fn_80177FE0();
            fn_80227690(&toBall, &ball, &pOther->mMotion.mPos);
            angle = fn_801CFE40(toBall.mY, toBall.mX);
            if (fn_801CFFD0(pOther->mUnknown512.mUnknown4, angle) > 0x400000 || !fn_8011F1CC() ||
                (pCarrier->mFlags & 0x8000)) {
                Query_800CE770 query;

                fn_800CE770(&query);
                query.mUnknown52 = 161;
                query.mUnknown44 = 0.8f;
                query.mUnknown36 = 0xE38E3;
                query.mpUnknown0 = p;
                query.mpUnknown4 = pOther;
                query.mUnknown54 = fn_8011EE18(pOther, pCarrier);
                if (fn_800CE4A8(&query)) {
                    fn_8011E1BC(p, pOther, 0, 5);
                    result = 1;
                    fn_8011E33C(pOther, p, 5);
                }
            }
        }
    }
    return result;
}

unsigned char fn_8011EE18(Object_80039F5C *p, Object_80039F5C *pCarrier)
{
    int degrees = (int)(((p->mUnknown512.mUnknown4 - p->mMotion.mFacing + 0x1000000) & 0xFFFFFF) * (360.0f / 16777216.0f));
    int rest = degrees % 45;
    int result;

    if (rest > 22) {
        degrees += 45 - rest;
    } else {
        degrees -= rest;
    }
    degrees = degrees < 90 ? 90 : degrees > 270 ? 270 : degrees;
    switch (degrees / 45 - 1) {
    case 0:
        result = 4;
        break;
    case 1:
        result = 7;
        break;
    case 2:
        result = 10;
        break;
    case 3: {
        Point_8017886C delta;
        int angle;

        fn_80227690(&delta, &pCarrier->mMotion.mPos, &p->mMotion.mPos);
        angle = fn_801CFE40(delta.mY, delta.mX);
        fn_80227384(&delta, &delta, p->mMotion.mFacing);
        angle = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
        result = 17;
        if (angle <= 0x7FFFFF) {
            result = 18;
        }
        break;
    }
    case 4:
        result = 16;
        break;
    case 5:
        result = 14;
        break;
    default:
        result = 4;
        break;
    }
    return result;
}

void fn_8011F0D8(void)
{
    unsigned char count = fn_801383C8();
    void *pHandle = fn_80238174(0, (void **)&lbl_803EB098, 576 + count * sizeof(Record_8011F4F8), 0, 0x70696E66);
    State_803EB098 *pState;

    fn_80238234(pHandle, 0, 0, 0, fn_8011EFD4);
    pState = (State_803EB098 *)fn_8023816C(pHandle);
    pState->mUnknown4 = 0;
    pState->mUnknown0 = 0.0f;
    fn_800A5A68(pState->mUnknown528);
    pState->mUnknown572 = count;
    fn_802381E0(pHandle);
}

int fn_8011FA78(void *pA, void *pB)
{
    int team = fn_80178320();
    float a = fn_80039F5C(team, *(char *)pA)->mMotion.mPos.mX;
    float b = fn_80039F5C(team, *(char *)pB)->mMotion.mPos.mX;

    if (a - b < 0.0f) {
        return -1;
    }
    return 0;
}

int fn_8011FAFC(void *pA, void *pB)
{
    int team = fn_80178320();
    float a = fn_80039F5C(team, *(char *)pA)->mMotion.mPos.mY;
    float b = fn_80039F5C(team, *(char *)pB)->mMotion.mPos.mY;

    if (a - b < 0.0f) {
        return -1;
    }
    return 0;
}

int fn_8011FB80(void *pA, void *pB)
{
    if (((Entry_8011FBE0 *)pA)->mUnknown0 - ((Entry_8011FBE0 *)pB)->mUnknown0 < 0.0f) {
        return -1;
    }
    return 0;
}

}
