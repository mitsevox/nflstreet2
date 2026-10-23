#include <math.h>
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/Message_800F01CC.h"
#include "game/Lookup_8012078C.h"
#include "game/State_803EB098.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_800F06F4.h"
#include "game/fn_8016871C.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80178D18.h"
#include "game/fn_801C1F94.h"
#include "game/fn_802270D4.h"
#include "game/fn_80227638.h"
#include "game/fn_8022781C.h"
#include "game/fn_802372EC.h"

extern "C" {
int fn_8011F1A4(void);
unsigned char fn_8011F4C8(void);
Object_80039F5C *fn_80124C28(Object_80039F5C *p, float *pOut, int angle, float length, float width, int facing);
void fn_8011E938(Object_80039F5C *p);
Object_80039F5C *fn_8003A130(Vector_80039F5C *pPos, float *pOut, int team);
float fn_8011F4D4(void);
int fn_8011F1CC(void);
int fn_801783AC(int bit);
int fn_8013BA58(Object_80137ABC *pBall, int *pOut);
int fn_80178320(void);
Object_80039F5C *fn_801245DC(Object_80039F5C *p, int team, unsigned char a, unsigned char count, int angle, float *pOut, int b);
int fn_8011E9B4(Object_80039F5C *p);
unsigned int fn_8011E188(void);
void fn_8011E1BC(Object_80039F5C *p, Object_80039F5C *pA, Object_80039F5C *pB, int value);
Object_80039F5C *fn_8011F54C(void);
int fn_8011F228(void);
int fn_80178C9C(void);
int fn_800BA6F8(void);
int fn_800BAA24(void);
int fn_800C8BAC(Object_80039F5C *p, int a);
float fn_802270A4(void *pV);
int fn_8011E95C(void);
extern float lbl_803EAE28;
int fn_801CFFD0(int a, int b);
float fn_801CFB94(int angle);
void fn_80227690(void *pOut, void *pA, void *pB);
}

/* Record passed by the caller at 0x800F6548/0x800F6594 to fn_800F5208 and
   fn_800F5CBC. Only the accessed members are declared; the size is unknown. */
struct Record_800F4E88 {
    Point_8017886C mUnknown0;
    float mUnknown8;
    float mUnknown12;
    char mUnknown16[4];
    int mUnknown20;
    unsigned char mUnknown24;
};

extern "C" int fn_800F5208(Object_80039F5C *p, Record_800F4E88 *pRecord) {
    Object_800B26B0 *pMotion = &p->mMotion;
    Object_800B26B0 *pBallMotion;
    Object_80039F5C *pTarget;
    Object_80039F5C *pBall;
    Object_80039F5C *pOther;
    Point_8017886C delta;
    float distance;
    float reach;
    int heading;
    int spread;
    int facing;
    int half;
    int flag;

    if (fn_8011F1CC()) {
        if (fn_801783AC(13) || fn_8013BA58(fn_801374BC(), 0) == 4) {
            return 1;
        }
        delta = fn_80177FE0();
        if (fabsf(p->mMotion.mPos.mX - delta.mX) > 4.0f) {
            int team = fn_80178320();

            pTarget = fn_801245DC(p, team, 0, fn_80178D18(fn_80178320()), 0x18E38E, &distance, 1);
            if (delta.mY < pMotion->mPos.mY) {
                delta.mY = pMotion->mPos.mY;
            }
            if (pTarget && pTarget->mMotion.mPos.mY - delta.mY < lbl_803EAE28 && distance < 5.0f
                && fn_801CFFD0(pTarget->mMotion.mUnknown32, 0xC00000) <= 0x3FFFFF && !fn_8011E9B4(pTarget)
                && fn_8011E188() > 30) {
                fn_8011E1BC(p, pTarget, 0, 3);
                return 1;
            }
        }
    }
    pBall = fn_80137B40();
    if (!pBall) {
        Vector_80039F5C velocity;
        Vector_80039F5C ballPos;

        if (fn_8013BA58(fn_801374BC(), 0) != 3) {
            return 0;
        }
        fn_80137EC4(fn_801374BC(), &velocity);
        fn_80137D58(fn_801374BC(), &ballPos);
        fn_80227690(&delta, &p->mMotion.mPos, &ballPos);
        if (fn_801CFFD0(fn_801CFE40(velocity.mY, velocity.mX), delta.Heading()) <= 0x1FFFFF) {
            return 0;
        }
        pBall = fn_80137BEC();
        if (!pBall) {
            return 0;
        }
    }
    if (fn_8011F1CC() && !(pBall->mFlags & 0x8000)) {
        if (!p->mUnknown560.mFlags.mBytes[0]) {
            return 0;
        }
        pOther = fn_8009BCE8(&p->mUnknown560.mUnknown40);
        if (!pOther) {
            return 0;
        }
        if (fn_8011E9B4(pOther) == 0) {
            return 1;
        }
        return 0;
    }
    pTarget = fn_8011F54C();
    pBallMotion = &pBall->mMotion;
    if (pBall->mpState->mId >= 0x19 && pBall->mpState->mId <= 0x1B) {
        return 0;
    }
    if (pBall != pTarget && pBall->mUnknown2914 != 7 && pBall->mUnknown2914 != 0x18) {
        if (pMotion->mPos.mY < pBallMotion->mPos.mY) {
            return 1;
        }
        if (fn_801CFFD0(pMotion->mUnknown32, pBallMotion->mUnknown32) > 0x671C72) {
            return 1;
        }
        if (pBallMotion->mUnknown32 >= 0x98E38F && pBallMotion->mUnknown32 <= 0xE71C71 && !fn_8011F228()) {
            return 1;
        }
        if (fn_8011F1A4() && fn_8011F4C8() > 3 && fn_801CFFD0(pMotion->mFacing, 0x400000) <= 0x155554
            && fn_80177FE0().mY - pMotion->mPos.mY < 1.5f && pRecord->mUnknown24) {
            return 1;
        }
        if (p->mUnknown560.mFlags.mBytes[0]) {
            pOther = fn_8009BCE8(&p->mUnknown560.mUnknown40);
            if (pOther && pOther->mUnknown1032 != 4 && pOther->mUnknown1032 != 5) {
                return 1;
            }
        }
    }
    if (fn_80178C9C() && (!fn_800BA6F8() || !fn_800BAA24())
        && pMotion->mPos.mY > fn_80039F5C(fn_80178320(), *fn_8012078C()->mpUnknown4)->mMotion.mPos.mY) {
        return 1;
    }
    if (fabsf(pMotion->mPos.mX - pBallMotion->mPos.mX) > 10.0f) {
        return 1;
    }
    if (fabsf(pMotion->mPos.mY - pBallMotion->mPos.mY) > 10.0f) {
        return 1;
    }
    flag = 0;
    if (fn_801783AC(0)
        || (fn_8011F1A4() && (fn_8011F4C8() & 1) && pMotion->mPos.mX < fn_80177FE0().mX)
        || (fn_8011F1A4() && !(fn_8011F4C8() & 1) && pMotion->mPos.mX > fn_80177FE0().mX)) {
        flag = 1;
    }
    if (!flag) {
        return 0;
    }
    spread = 0x438E39;
    if (!pRecord->mUnknown24 && (!fn_8011F1A4() || fn_8011F4C8() <= 3)) {
        spread = 0x21C71C;
    }
    facing = pMotion->mFacing;
    spread = (spread + fn_801CFFD0(fn_800C8BAC(p, 0) + facing, facing)) & 0xFFFFFF;
    {
        int team = fn_80178320();

        pTarget = fn_801245DC(p, team, 0, fn_80178D18(fn_80178320()), spread, &distance, 1);
    }
    if (!pTarget || (pTarget->mFlags & 0x800)) {
        return 0;
    }
    fn_80227690(&delta, &pTarget->mMotion.mPos, pMotion);
    heading = delta.Heading();
    if (fn_8011F1A4() && fn_8011F4C8() > 3) {
        switch (p->mUnknown2914) {
        case 1:
        case 2:
        case 5:
        case 6:
        case 8:
        case 9:
            if (pTarget->mMotion.mPos.mY > fn_80177FE0().mY
                && fabsf(pMotion->mPos.mX - fn_80177FE0().mX) < 5.0f) {
                return 0;
            }
            break;
        }
        if (pTarget->mUnknown1032 == 8) {
            fn_80227690(&delta, &fn_8009BCE8(&pTarget->mUnknown1036)->mMotion.mPos, pMotion);
            if (fn_801CFFD0(heading, delta.Heading()) <= 0x11C71B && fn_802270A4(&delta) < distance) {
                return 0;
            }
        }
    }
    reach = 3.5f;
    if (fn_8011F1A4() && (fn_8011F4C8() & 1)) {
        if (fn_8011F1A4() && fn_8011F4C8() > 3 && pMotion->mPos.mX < fn_8011F4D4()) {
            reach += (float)(fn_8011F4C8() - 1);
        } else {
            reach += (float)(fn_8011F4C8() - 1) / 3.0f;
        }
    } else if (fn_8011F1A4() && !(fn_8011F4C8() & 1)) {
        if (fn_8011F1A4() && fn_8011F4C8() > 3 && pMotion->mPos.mX > fn_8011F4D4()) {
            int level = fn_8011F4C8();

            reach += level;
        } else {
            int level = fn_8011F4C8();

            reach += level / 3.0f;
        }
    }
    if (fn_8011F1A4() && fn_8011F4C8() > 3) {
        half = fn_801CFFD0(pMotion->mFacing, heading) / 2;
    } else {
        half = fn_801CFFD0(pMotion->mFacing, heading) / 4;
    }
    reach *= fn_801CFB94(half);
    if (pMotion->mPos.mY > fn_80177FE0().mY) {
        reach *= 2.0f;
    } else {
        int ahead = 0;

        if (pTarget->mMotion.mPos.mY > fn_80177FE0().mY && fn_8011E95C()) {
            ahead = 1;
        }
        if (ahead) {
            reach /= 3.0f;
        }
    }
    if (distance < reach) {
        if (pTarget->mpState->mId == 0x20) {
            if (pTarget->mUnknown1032 == 6) {
                return 1;
            }
            return 0;
        }
        if (pTarget->mUnknown1032 != 4) {
            return 1;
        }
    }
    return 0;
}

extern "C" int fn_800F5AD4(Object_80039F5C *p) {
    Vector_80039F5C pos = p->mMotion.mPos;
    float distance;
    Object_80039F5C *pNear;
    Object_80039F5C *pOther;
    int flag;

    if (fn_8011F1A4() && (fn_8011F4C8() & 1)) {
        pos.mX -= 1.5f;
    } else {
        pos.mX += 1.5f;
    }
    pNear = fn_80124C28(p, &distance, 0x355555, 2.75f, 0.5f, p->mMotion.mFacing);
    flag = 0;
    if (fn_8011F1A4() && (fn_8011F4C8() & 1) && p->mMotion.mPos.mX > fn_80177FE0().mX) {
        flag = 1;
    } else if (fn_8011F1A4() && (fn_8011F4C8() & 1) == 0 && p->mMotion.mPos.mX < fn_80177FE0().mX) {
        flag = 1;
    }
    if (flag) {
        fn_8011E938(pNear);
        return 0;
    }
    pOther = fn_8003A130(&pos, &distance, p->mIdBytes[2]);
    if (!pOther || pOther == p || distance > 4.0f
        || fabsf(pOther->mMotion.mPos.mX - fn_80177FE0().mX) < fabsf(p->mMotion.mPos.mX - fn_80177FE0().mX)) {
        return 1;
    }
    if (pNear && pNear->mIdBytes[2] != p->mIdBytes[2]) {
        return 1;
    }
    return 0;
}

extern "C" int fn_800F5CBC(Object_80039F5C *p, Record_800F4E88 *pRecord) {
    Object_800B26B0 *pMotion;
    Object_80039F5C *pNear;
    Vector_80039F5C target;
    Point_8017886C delta;
    Point_8017886C point;
    float distance;
    float range;
    float scale;
    int result = pRecord->mUnknown20;
    int angle;
    int facing;
    int step;
    int onBall;
    int span;

    pNear = fn_80124C28(p, &distance, 0x2AAAAA, 3.5f, 0.5f, p->mMotion.mFacing);
    pMotion = &p->mMotion;
    onBall = 0;
    if (pNear) {
        range = 3.5f;
        if (pNear->mIdBytes[2] == p->mIdBytes[2]) {
            if (pRecord->mUnknown12 < 1e-7f) {
                return result;
            }
            if (pNear->mUnknown1032 != 4) {
                range *= 0.5f;
            }
        }
        if (distance < range) {
            if (pNear->mUnknown1032 != 4) {
                target = pNear->mMotion.mPos;
                target.mX += 2.0f * pNear->mMotion.mUnknown40;
                target.mY += 2.0f * pNear->mMotion.mUnknown44;
            } else {
                Object_80039F5C *pPartner = fn_8009BCE8(&pNear->mUnknown1036);

                target.mX = (pNear->mMotion.mPos.mX + pPartner->mMotion.mPos.mX) * 0.5f;
                target.mY = (pNear->mMotion.mPos.mY + pPartner->mMotion.mPos.mY) * 0.5f;
            }
            fn_80227690(&delta, &target, pMotion);
            angle = delta.Heading();
            facing = pMotion->mFacing;
            scale = distance / 3.5f;
            if (pNear->mpState->mId == 0x1A) {
                onBall = 1;
                point.mX = pNear->mMotion.mPos.mX;
                point.mY = fn_80177FE0().mY;
                fn_80227690(&point, &point, pMotion);
                facing = point.Heading();
            }
            step = (int)((1.0f - scale) * 2796202.0f);
            step = (int)(fn_801CFB94(fn_801CFFD0(angle, pMotion->mFacing) / 2) * (float)step);
            if (!onBall && fn_8011F1A4() && fn_801CFFD0(pMotion->mFacing, angle) <= 0xE38E2
                && pMotion->mPos.mY < fn_80177FE0().mY) {
                point.mX = fn_8011F4D4();
                point.mY = fn_80177FE0().mY;
                fn_80227690(&point, &point, pMotion);
                angle = point.Heading();
                if (((angle - facing) & 0xFFFFFF) > 0x800000) {
                    step = -step;
                }
            } else if (fn_801CFFD0(pMotion->mFacing, angle) <= 0xE38E2
                       || fn_801CFFD0(pMotion->mFacing, 0xC00000) <= 0x38E38D) {
                if (((angle - pRecord->mUnknown20) & 0xFFFFFF) <= 0x7FFFFF) {
                    step = -step;
                }
            } else if (((angle - facing) & 0xFFFFFF) <= 0x7FFFFF) {
                step = -step;
            }
            result = (pMotion->mFacing + step) & 0xFFFFFF;
            span = (result - pMotion->mFacing) & 0xFFFFFF;
            if ((span <= 0x7FFFFF && ((pRecord->mUnknown20 - pMotion->mFacing) & 0xFFFFFF) <= 0x7FFFFF)
                || (span > 0x800000 && ((pRecord->mUnknown20 - pMotion->mFacing) & 0xFFFFFF) > 0x800000)) {
                if (fn_801CFFD0(pRecord->mUnknown20, angle) > fn_801CFFD0(result, angle)) {
                    result = pRecord->mUnknown20 & 0xFFFFFF;
                }
            }
            p->mUnknown512.mUnknown15 = 0;
        }
    }
    return result;
}
