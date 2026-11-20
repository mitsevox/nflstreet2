#include "game/Item_80097440.h"
#include "game/Object_8017886C.h"
#include "game/Ball.h"

#include "game/Object_80039F5C.h"
#include "engine/AnimChannel.h"
#include "game/fn_802270D4.h"
#include "game/fn_80177FE0.h"
#include "game/fn_802372EC.h"

extern "C" {
State_8011F4EC *fn_8011F4EC(void);
int fn_80178308(void);
void fn_8009F928(Object_80039F5C *p, Point_8017886C *pOut, unsigned int distance, int predict);
}

/* Returns the index-th player of the play state's roster list after sorting
   it by depth (mode 1), and that player's spot through pOut. */
extern "C" Object_80039F5C *fn_8009EC60(unsigned int index, Point_8017886C *pOut)
{
    State_8011F4EC *pState;
    Object_80039F5C *p;

    if (pOut != 0) {
        pOut->mX = pOut->mY = 0.0f;
    }
    pState = fn_8011F4EC();
    if (index < pState->mUnknown1A3) {
        int team = fn_80178308();

        if (pState->mUnknown1A4 != 1) {
            int swapped;

            pState->mUnknown1A4 = 1;
            do {
                unsigned char i;

                swapped = 0;
                for (i = 0; i < pState->mUnknown1A3 - 1; i++) {
                    Object_80039F5C *pB;
                    Point_8017886C a;
                    Point_8017886C b;

                    p = PlyrGet(team, pState->mUnknown1A5[i]);
                    pB = PlyrGet(team, pState->mUnknown1A5[i + 1]);
                    fn_8009F928(p, &a, 5, 1);
                    fn_8009F928(pB, &b, 5, 1);
                    if (a.mY < b.mY) {
                        unsigned char temp = pState->mUnknown1A5[i];

                        pState->mUnknown1A5[i] = pState->mUnknown1A5[i + 1];
                        pState->mUnknown1A5[i + 1] = temp;
                        swapped = 1;
                    }
                }
            } while (swapped == 1);
        }
        p = PlyrGet(team, pState->mUnknown1A5[index]);
        if (pOut != 0) {
            fn_8009F928(p, pOut, 5, 1);
        }
    } else {
        p = 0;
    }
    return p;
}

extern "C" {
void fn_80227690(void *pOut, void *pA, void *pB);
int fn_800C8BAC(Object_80039F5C *, int);
float fn_80178A08(void);
int MathAngleDiff(int a, int b);
int fn_8009EFDC(int index);
}

extern "C" Object_80039F5C *fn_8009EDD4(unsigned int index, int side, Point_8017886C *pOut)
{
    State_8011F4EC *pState = fn_8011F4EC();
    Object_80039F5C *p;
    int team;
    int n;

    if (index < pState->mUnknown1A3) {
    team = fn_80178308();
    if (pState->mUnknown1A4 != 2) {
        int swapped;

        pState->mUnknown1A4 = 2;
        do {
            unsigned char i;

            swapped = 0;
            for (i = 0; i < pState->mUnknown1A3 - 1; i++) {
                Object_80039F5C *pB;
                Point_8017886C a;
                Point_8017886C b;

                p = PlyrGet(team, pState->mUnknown1A5[i]);
                pB = PlyrGet(team, pState->mUnknown1A5[i + 1]);
                fn_8009F928(p, &a, 5, 1);
                fn_8009F928(pB, &b, 5, 1);
                if (a.mX > b.mX) {
                    unsigned char temp = pState->mUnknown1A5[i];

                    pState->mUnknown1A5[i] = pState->mUnknown1A5[i + 1];
                    pState->mUnknown1A5[i + 1] = temp;
                    swapped = 1;
                }
            }
        } while (swapped == 1);
    }
    if (fn_8009EFDC(side) == 1) {
        index = pState->mUnknown1A3 - index - 1;
    }
    p = 0;
    for (n = index; n >= 0 && p == 0; n--) {
        p = PlyrGet(team, pState->mUnknown1A5[n]);
        if (pOut != 0) {
            fn_8009F928(p, pOut, 5, 1);
        }
        if (p->mpState->mId == 31 || p->mpState->mId == 32) {
            p = 0;
        }
    }
    } else {
        p = 0;
    }
    return p;
}

extern "C" int fn_8009EF6C(Object_80039F5C *p)
{
    State_8011F4EC *pState = fn_8011F4EC();
    unsigned char id = p->mIdBytes[1];
    unsigned char i;

    for (i = 0; i < pState->mUnknown1A3; i++) {
        if (id == pState->mUnknown1A5[i]) {
            return 1;
        }
    }
    return 0;
}

extern "C" int fn_8009EFDC(int index)
{
    Entry_8011F4EC *pEntry = &fn_8011F4EC()->mUnknown18[index];

    if (pEntry->mUnknown8 != -fn_80178A08()) {
        return pEntry->mUnknownC == fn_80178A08();
    }
    return pEntry->mUnknownC == fn_80178A08() ? 0 : -1;
}

extern "C" int fn_8009F058(Object_80039F5C *p, Object_80039F5C *pOther, int angle)
{
    Point_8017886C delta;

    fn_80227690(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
    return MathAngleDiff(fn_801CFE40(delta.mY, delta.mX), p->mMotion.mFacing) < angle;
}

extern "C" int fn_8009F0B8(Object_80039F5C *p, int angle)
{
    Vector_80039F5C ball;
    Point_8017886C delta;
    int heading;

    BallGetPosition(BallGetCurrent(), &ball);
    fn_80227690(&delta, &ball, &p->mMotion.mPos);
    heading = fn_801CFE40(delta.mY, delta.mX);
    return MathAngleDiff(heading, p->mMotion.mFacing + fn_800C8BAC(p, 0)) < angle;
}

extern "C" int fn_8009F13C(Object_80039F5C *p)
{
    if (p->mpState->mId == 28 || p->mUnknown16 == 2) {
        return 1;
    }
    return 0;
}

extern "C" {
int fn_801CFE40(float y, float x);
float fn_801CFB18(int angle);
float fn_801CFB94(int angle);
int fn_801CFDD0(float value);
}

extern "C" float fn_8009F168(Vector_80039F5C *p, Pair_802270A4 *pVelocity,
                              Vector_80039F5C *pOther, float speed)
{
    Vector_80039F5C delta;
    fn_802276B4(&delta, pOther, p);
    float distance = fn_802270A4(&delta);
    float velocity = fn_802270A4(pVelocity);
    int angle = fn_801CFE40(pVelocity->mUnknown4, pVelocity->mUnknown0);
    angle = angle - fn_801CFE40(delta.mY, delta.mX);
    float sine = fn_801CFB18(angle);
    int correction = fn_801CFDD0(velocity * sine / speed);
    float closing = speed * fn_801CFB94(correction) + velocity * fn_801CFB94(angle);
    float time = distance / closing;
    if (time <= 0.0f || !(time <= 5.0f)) {
        time = distance / speed;
    }
    return time;
}

extern "C" {
Object_80039F5C *fn_8009BCE8(int *pRef);
int fn_800AD2CC(int team, int flag);
int fn_8009F0B8(Object_80039F5C *p, int angle);
int fn_8009F13C(Object_80039F5C *p);
void fn_8009F5A4(unsigned int *pValue);
int fn_80178320(void);
int fn_80178308(void);
int fn_8009AE1C(int team, int value);
void fn_800ACAF8(int team, unsigned int *pValue);
int fn_800B65A0(int team);
unsigned int fn_8011E188(void);
}

extern float lbl_803EA9BC;
extern float lbl_803EA9C0;

/* Rolls whether p goes for the ball in flight to the current target. In
   state 22, with the target being p's mark (or a mark in state 23), the
   chance is 450 when p faces the ball or the mark qualifies (fn_8009F13C),
   otherwise twice the landing time capped at 35 while the ball descends; a
   p not on the target's mark gets 1700 when facing the ball. In states 40
   and 92 the chance is 350 when facing, twice the landing time capped at 35
   while the ball descends, otherwise 2400. The chance is adjusted by
   fn_8009F5A4, fn_8009AE1C and fn_800ACAF8 and scaled by lbl_803EA9C0 under
   the fn_8011E188 threshold, then rolled against rating 8. With no current
   target it returns 1. */
extern "C" int fn_8009F258(Object_80039F5C *p)
{
    unsigned int chance = 0;
    Point_8017886C ballSpot = fn_80177FE0();
    int result = 0;
    Ball_t *pBall = BallGetCurrent();
    Vector_80039F5C landing;
    Vector_80039F5C velocity;
    unsigned char state;
    Object_80039F5C *pTarget;

    BallGetVelocity(pBall, &velocity);
    BallGetLandingPoint(pBall, &landing);
    state = p->mpState->mId;
    pTarget = BallGetCurrentTarget();
    if (pTarget != 0) {
        short rating = p->mRatings[8];

        switch (state) {
        case 22: {
            Object_80039F5C *pMark = fn_8009BCE8(&p->mUnknown336);
            int facing = fn_8009F0B8(p, fn_800AD2CC(p->mIdBytes[2], 0));

            if (pTarget == pMark || (pMark != 0 && pMark->mpState->mId == 23)) {
                if (facing || fn_8009F13C(pMark)) {
                    chance = 450;
                } else if (velocity.mZ < 0.0f) {
                    float time;

                    if (BallGetLandingTime(pBall, &time)) {
                        chance = (unsigned int)(time * 2.0f);
                        if (chance > 35) {
                            chance = 35;
                        }
                    }
                }
            } else if (facing) {
                chance = 1700;
            }
            break;
        }
        case 40:
        case 92:
            if (fn_8009F0B8(p, fn_800AD2CC(p->mIdBytes[2], 1))) {
                chance = 350;
            } else if (velocity.mZ < 0.0f) {
                float time;

                if (BallGetLandingTime(pBall, &time)) {
                    chance = (unsigned int)(time * 2.0f);
                    if (chance > 35) {
                        chance = 35;
                    }
                }
            } else {
                chance = 2400;
            }
            break;
        }
        if (!result && chance != 0) {
            fn_8009F5A4(&chance);
            chance = fn_8009AE1C(fn_80178320(), chance);
            fn_800ACAF8(fn_80178320(), &chance);
            if (fn_800B65A0(fn_80178308()) != 0xFF && (float)fn_8011E188() < lbl_803EA9BC) {
                chance = (unsigned int)(chance * lbl_803EA9C0);
            }
            if (fn_802372EC(0, chance) < rating) {
                result = 1;
            }
        }
    } else {
        result = 1;
    }
    return result;
}
