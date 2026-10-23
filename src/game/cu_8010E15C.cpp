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

/* Steering state fn_8010E59C keeps per player: a speed scale, the heading
   to run on, the heading to face, a countdown to the next update and two
   flag bytes. fn_8010DAB4 and fn_8010E15C fill and adjust it. */
struct Steer_8010DAB4 {
    float mSpeed;
    int mHeading;
    int mFacing;
    int mTimer;
    char mUnknown16[5];
    unsigned char mUnknown21;
    unsigned char mUnknown22;
};

extern "C" {
Object_80039F5C *fn_80124C28(Object_80039F5C *p, float *pOut, int angle, int facing, float a, float b);
float fn_801CFB94(int angle);
int fn_801CFFD0(int a, int b);
void fn_80227690(void *pOut, void *pA, void *pB);
}

/* The target compares the state against 4 with a greater-or-equal store
   flag (0x8010E218), which only survives when the bound reaches the
   comparison as an inlined argument; a literal is folded to "> 3". */
static inline int InRange(int v, int lo, int hi) { return v <= hi && v >= lo; }

/* Steers the player around the nearest other player ahead of its heading. */
extern "C" void fn_8010E15C(Object_80039F5C *p, Steer_8010DAB4 *pOut) {
    Object_800B26B0 *pMotion = &p->mMotion;
    Object_80039F5C *pMark = fn_8009BCE8(&p->mUnknown1036);
    Vector_80039F5C aim;
    Point_8017886C toward;
    Object_80039F5C *pOther;
    Object_80039F5C *pPartner;
    float distance;
    float limit;
    float scale;
    int second = 0;
    int first = 0;
    int turn = 0;
    int pair;
    int between;
    int heading;
    int off;

    aim.mX = aim.mY = aim.mZ = 0.0f;
    pOther = fn_80124C28(p, &distance, 0x38E38E, pOut->mHeading, 3.0f, 0.5f);
    if (pOther && distance < 3.0f && pOther != pMark && pOther != fn_80137B40()) {
        limit = 3.0f;
        between = 0;
        pair = InRange(pOther->mUnknown1032, 4, 7);
        if (pOther->mIdBytes[2] == p->mIdBytes[2] && !pair) limit *= 0.5f;
        /* The distance is computed and dropped (0x8010E254). */
        if (pMark) fn_8022781C(&pMark->mMotion.mPos, &pMotion->mPos);
        if (distance < limit) {
            if (pair) {
                pPartner = fn_8009BCE8(&pOther->mUnknown1036);
                aim.mX = (pOther->mMotion.mPos.mX + pPartner->mMotion.mPos.mX) * 0.5f;
                aim.mY = (pOther->mMotion.mPos.mY + pPartner->mMotion.mPos.mY) * 0.5f;
                fn_80227690(&toward, &pOther->mMotion.mPos, &pMotion->mPos);
                first = toward.Heading();
                fn_80227690(&toward, &pPartner->mMotion.mPos, &pMotion->mPos);
                second = toward.Heading();
                if ((((first - second) & 0xFFFFFF) <= 0x7FFFFF && ((pOut->mHeading - second) & 0xFFFFFF) <= 0x7FFFFF) ||
                    (((first - second) & 0xFFFFFF) > 0x800000 && ((pOut->mHeading - second) & 0xFFFFFF) > 0x800000)) {
                    if (fn_801CFFD0(first - second, 0) > fn_801CFFD0(pOut->mHeading - second, 0)) between = 1;
                }
            } else {
                aim.mX = pOther->mMotion.mPos.mX;
                aim.mY = pOther->mMotion.mPos.mY;
                aim.mZ = pOther->mMotion.mPos.mZ;
                aim.mX = pOther->mMotion.mUnknown40 * 10.0f + aim.mX;
                aim.mY = pOther->mMotion.mUnknown44 * 10.0f + aim.mY;
            }
            fn_80227690(&toward, &aim, &pMotion->mPos);
            heading = toward.Heading();
            scale = distance * 0.4f;
            if (scale > 1.0f) scale = 1.0f;
            if (fn_801CFFD0(heading, pOut->mHeading) <= 0x271C70) {
                if (((heading - pOut->mHeading) & 0xFFFFFF) > 0x800000) {
                    turn = (int)((1.0f - scale) * 3728270.0f);
                    if (pair && between) {
                        if (((first - heading) & 0xFFFFFF) <= 0x7FFFFF) {
                            turn += fn_801CFFD0(first, pOut->mHeading);
                        } else {
                            turn += fn_801CFFD0(second, pOut->mHeading);
                        }
                    }
                } else {
                    turn = (int)-((1.0f - scale) * 3728270.0f);
                    if (pair && between) {
                        if (((first - heading) & 0xFFFFFF) > 0x800000) {
                            turn -= fn_801CFFD0(first, pOut->mHeading);
                        } else {
                            turn -= fn_801CFFD0(second, pOut->mHeading);
                        }
                    }
                }
                off = fn_801CFFD0(pOut->mHeading + turn, pMotion->mFacing);
                if (off > 0x11C71C) {
                    pOut->mSpeed = fn_801CFB94(off / 2) * 0.72f;
                    pOut->mUnknown22 = 0;
                } else if (distance < 2.1f && fn_801CFFD0(heading, pMotion->mFacing) <= 0x1FFFFF) {
                    pOut->mUnknown22 = 0;
                }
            }
            pOut->mHeading = (pOut->mHeading + turn) & 0xFFFFFF;
        }
    }
}
