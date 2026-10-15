#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/cu_80136B1C.h"
#include "game/fn_802270D4.h"
#include "game/fn_801BE60C.h"
#include "game/fn_80163E94.h"
#include "game/fn_800F06F4.h"

extern "C" {
void fn_80227690(void *pOut, void *pA, void *pB);
int fn_801CFE40(float y, float x);
int fn_8011F1A4(void);
unsigned char fn_8011F4C8(void);
void fn_8009BD60(Object_80039F5C *p);
}

extern "C" int fn_8010C8F8(Object_80039F5C *p) {
    float limit = 1.0f;
    int result = 0;
    Object_80137ABC *pBall;
    Vector_80039F5C pos;
    Point_8017886C delta;

    fn_80137B40();
    pBall = fn_80137CD0(p);
    if (pBall == 0) {
        pBall = fn_801374BC();
        limit = 1.5f;
    }
    fn_80137D58(pBall, &pos);
    fn_80227690(&delta, &pos, &p->mMotion);
    if (fn_802270A4(&delta) < limit) {
        result = 1;
    }
    return result;
}

extern "C" void fn_8010C98C(Object_80039F5C *p) {
    int pending = 1;
    Object_80137ABC *pBall;
    Vector_80039F5C pos;
    int index;

    pBall = fn_80137CD0(p);
    if (pBall == 0) {
        pBall = fn_801374BC();
    }
    fn_80137D58(pBall, &pos);
    fn_8009BD60(p);
    index = fn_800F06F4(0, p->mpState, 26, 0xFFFF);
    if (index != 0xFFFF) {
        switch (p->mpState[index].mUnknown2) {
        case 2:
        case 3:
            p->mUnknown1008.mUnknown0 = 1;
            pending = 0;
            break;
        case 4:
        case 5:
            p->mUnknown1008.mUnknown0 = 2;
            pending = 0;
            break;
        default:
            pending = 1;
            break;
        }
    }
    if (pending) {
        if (fn_8011F1A4()) {
            if (fn_8011F1A4() && (fn_8011F4C8() & 1)) {
                p->mUnknown1008.mUnknown0 = 1;
            } else {
                p->mUnknown1008.mUnknown0 = 2;
            }
        } else {
            Point_8017886C delta;

            fn_80227690(&delta, &pos, &p->mMotion);
            if (((fn_801CFE40(delta.mY, delta.mX) - p->mMotion.mFacing) & 0xFFFFFF) > 0x800000) {
                p->mUnknown1008.mUnknown0 = 1;
            } else {
                p->mUnknown1008.mUnknown0 = 2;
            }
        }
    }
    fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 78, p, 1.0f);
    p->mUnknown512.mUnknown14 = 0;
}
