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

#define MIN(a, b) ((a) > (b) ? (b) : (a))

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
int fn_800BA6F8(void);
int fn_800BAA24(void);
void fn_8010DAB4(Object_80039F5C *p, Steer_8010DAB4 *pOut);
void fn_8010E15C(Object_80039F5C *p, Steer_8010DAB4 *pOut);
unsigned int fn_8011E188(void);
int fn_8011F1A4(void);
unsigned char fn_8011F4C8(void);
float fn_8011F4D4(void);
int fn_80120794(Object_800B26B0 *pA, Object_800B26B0 *pB, float *pC, float e, float f, int d, float g);
int fn_801783AC(int flag);
int fn_801787A0(void);
int fn_80178C9C(void);
float fn_801CFB94(int angle);
int fn_801CFFD0(int a, int b);
void fn_80227690(void *pOut, void *pA, void *pB);
extern float lbl_803ECB08;
}

/* Updates the player's steering toward pTarget, or along the play when
   there is none, once its countdown runs out. */
extern "C" void fn_8010E59C(Object_80039F5C *p, Object_80039F5C *pTarget, Steer_8010DAB4 *pOut) {
    Object_800B26B0 *pMotion = &p->mMotion;
    Object_80039F5C *pCarrier;
    Point_8017886C aim;
    Point_8017886C toward;
    float distance;
    float limit;
    int heading;
    int side;
    int off;
    int state;
    int rating;

    if (--pOut->mTimer < 0 || fn_801787A0()) {
        if (!fn_80178C9C() || (fn_800BA6F8() && fn_800BAA24() == 1)) {
            pOut->mUnknown21 = 1;
        } else {
            rating = p->mRatings[7] * 2;
            pOut->mTimer = rating / 2;
            pOut->mTimer = (255 - pOut->mTimer) / 32 + 2;
            if (pTarget) {
                /* The point is fetched and dropped (0x8010E65C). */
                fn_80177FE0();
                aim.mX = pTarget->mMotion.mUnknown40 * 10.0f + pTarget->mMotion.mPos.mX;
                aim.mY = pTarget->mMotion.mUnknown44 * 10.0f + pTarget->mMotion.mPos.mY;
                if (fn_801BE648(pTarget->mpUnknown792) == 0x56) aim.mY -= 0.75f;
                fn_80227690(&toward, &aim, pMotion);
                heading = toward.Heading();
                distance = fn_802270A4(&toward);
                if (distance < 2.5f) pOut->mTimer = 0;
                limit = 6.0f;
                pOut->mUnknown22 = 1;
                pOut->mSpeed = 1.0f;
                pOut->mHeading = heading;
                if (pTarget->mMotion.mUnknown28 != 0.0f &&
                    (fn_801BE648(pTarget->mpUnknown792) == 0x4A || fn_801BE648(pTarget->mpUnknown792) == 0x49 ||
                     fn_801BE648(pTarget->mpUnknown792) == 0xA0)) {
                    if (fn_801CFFD0(heading, pTarget->mMotion.mUnknown32) > 0x6E38E3) {
                        if (distance < limit) pOut->mSpeed = distance / limit * 0.86f + 0.14f;
                    } else if (distance > 1.75f) {
                        if (fn_801BE648(pTarget->mpUnknown792) == 0xA0 && pTarget->mpState->mId != 2) {
                            pOut->mHeading = heading;
                        } else {
                            pOut->mHeading = fn_80120794(pMotion, &pTarget->mMotion, &pTarget->mMotion.mUnknown40,
                                                         pMotion->mUnknown28, pTarget->mMotion.mUnknown28,
                                                         pTarget->mMotion.mUnknown32, distance);
                        }
                        if (distance < 2.5f && fn_8011E188() <= 44) {
                            switch (p->mUnknown2914) {
                            case 4:
                            case 5:
                            case 6:
                            case 7:
                            case 8:
                            case 9:
                            case 24:
                                off = fn_801CFFD0(heading, pOut->mHeading);
                                if (((heading - pOut->mHeading) & 0xFFFFFF) > 0x800000) {
                                    pOut->mHeading = pOut->mHeading - off / 2;
                                } else {
                                    pOut->mHeading = pOut->mHeading + off / 2;
                                }
                                break;
                            }
                        }
                        if (distance < limit) pOut->mSpeed = distance / limit * (1.0f - 0.72f) + 0.72f;
                        if (fn_8011E188() <= 59 && distance > 2.0f && fn_8011F1A4() && fn_8011F4C8() > 3 && !fn_801783AC(0) &&
                            fn_801CFFD0(pMotion->mFacing, 0x400000) <= 0x3FFFFF) {
                            toward.mX = fn_8011F4D4();
                            toward.mY = fn_80177FE0().mY;
                            if (fabsf(toward.mX) > fabsf(pMotion->mPos.mX) && aim.mY - toward.mY > 3.0f &&
                                pMotion->mPos.mY - toward.mY < 1.5f) {
                                fn_80227690(&toward, &toward, pMotion);
                                side = toward.Heading();
                                off = fn_801CFFD0(heading, side);
                                if (off <= 0x671C71 && off > fn_801CFFD0(heading, pOut->mHeading)) {
                                    int least = 0x18E38E;

                                    if (off < least) off = least;
                                    if (fn_801CFFD0(side, heading) < fn_801CFFD0(side, pOut->mHeading)) pOut->mHeading = heading;
                                    if (((side - heading) & 0xFFFFFF) > 0x800000) {
                                        pOut->mHeading -= off / 2;
                                    } else {
                                        pOut->mHeading += off / 2;
                                    }
                                }
                            }
                        }
                    } else {
                        if (pTarget == fn_8009BCE8(&p->mUnknown560.mUnknown40)) {
                            pOut->mSpeed = distance * 0.18285717f + 0.4f;
                        } else {
                            pOut->mSpeed = distance * 0.16f + 0.72f;
                        }
                        pOut->mUnknown22 = 0;
                    }
                    pCarrier = fn_80137B40();
                    if (pCarrier) {
                        state = pCarrier->mpState->mId;
                        if (state == 1 || state == 0x23 || state == 0x22 || state == 0x24) {
                            fn_80227690(&toward, &pCarrier->mMotion.mPos, pMotion);
                            distance = fn_802270A4(&toward);
                            if (distance < 10.0f) {
                                side = toward.Heading() & 0xFFFFFF;
                                if (distance < 5.0f && fn_801CFFD0(heading, side) > 0x58E38E &&
                                    fn_801CFFD0(pCarrier->mMotion.mFacing, side) > 0x755555) {
                                    off = fn_801CFFD0(heading, pOut->mHeading);
                                    if (((pOut->mHeading - heading) & 0xFFFFFF) > 0x800000) {
                                        pOut->mHeading = (pOut->mHeading + off / 2) & 0xFFFFFF;
                                    } else {
                                        pOut->mHeading = (pOut->mHeading - off / 2) & 0xFFFFFF;
                                    }
                                } else if (fn_801CFFD0(heading, side) <= 0x355554) {
                                    if (((pOut->mHeading - heading) & 0xFFFFFF) > 0x800000) {
                                        if (((side - heading) & 0xFFFFFF) > 0x800000 &&
                                            fn_801CFFD0(pOut->mHeading, heading) > fn_801CFFD0(side, heading)) {
                                            pOut->mHeading = heading;
                                            pOut->mHeading = (pOut->mHeading - fn_801CFFD0(side, heading) / 2) & 0xFFFFFF;
                                        }
                                    } else if (((side - heading) & 0xFFFFFF) <= 0x7FFFFF &&
                                               fn_801CFFD0(pOut->mHeading, heading) > fn_801CFFD0(side, heading)) {
                                        pOut->mHeading = heading;
                                        pOut->mHeading = (pOut->mHeading + fn_801CFFD0(side, heading) / 2) & 0xFFFFFF;
                                    }
                                }
                            }
                        }
                    }
                } else {
                    pOut->mUnknown22 = 0;
                    if (distance < 1.75f) pOut->mSpeed = distance * 0.34285718f + 0.4f;
                    if (fn_8011F1A4() && fn_8011F4C8() > 3 && fn_8011E188() <= 59) {
                        toward.mX = fn_8011F4D4();
                        if (fabsf(pMotion->mPos.mX) < fabsf(toward.mX) && fabsf(pMotion->mPos.mX - toward.mX) < 3.0f) {
                            toward.mY = fn_80177FE0().mY;
                            fn_80227690(&toward, &toward, pMotion);
                            side = toward.Heading();
                            off = fn_801CFFD0(heading, side);
                            if (off <= 0x3FFFFF) {
                                if (((pOut->mHeading - side) & 0xFFFFFF) <= 0x7FFFFF) {
                                    pOut->mHeading = pOut->mHeading - off / 2;
                                } else {
                                    pOut->mHeading = pOut->mHeading + off / 2;
                                }
                            }
                        }
                    }
                }
                fn_8010E15C(p, pOut);
                pOut->mHeading &= 0xFFFFFF;
                pOut->mFacing = pOut->mHeading;
                off = fn_801CFFD0(pOut->mHeading, pMotion->mFacing);
                if (off > 0x18E38E) {
                    off /= 2;
                    pOut->mSpeed = MIN(pOut->mSpeed, fn_801CFB94(off) * 0.72f);
                    pOut->mUnknown22 = 0;
                }
            } else {
                fn_8010DAB4(p, pOut);
                heading = pMotion->mFacing;
            }
            if (pMotion->mUnknown28 > lbl_803ECB08 * 0.05f && fn_801CFFD0(pMotion->mUnknown32, pMotion->mFacing) > 0x400000 &&
                fn_801CFFD0(pMotion->mUnknown32, pOut->mFacing) > 0x38E38E) {
                pOut->mFacing = heading;
                pOut->mSpeed = 0.0f;
                pOut->mTimer = 0;
            }
        }
    }
    if (fn_801787A0()) pOut->mSpeed = MIN(pOut->mSpeed, 0.4f);
}
