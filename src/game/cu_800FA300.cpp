#include <math.h>
#include <string.h>
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/Message_800F01CC.h"
#include "game/State_803EB098.h"
#include "game/fn_800F06F4.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80178D18.h"
#include "game/fn_802372EC.h"

/* View of the block at player +336 used by the state 22 handlers
   (as Block_800F8A88 in src/game/cu_800F930C.cpp). */
struct Block_800FA300 {
    int mRef;
    int mUnknown4;
    int mUnknown8;
    float mUnknown12;
    unsigned int mUnknown16;
    unsigned char mUnknown20;
    unsigned char mUnknown21;
    unsigned char mUnknown22;
    unsigned char mUnknown23;
    unsigned char mUnknown24;
    unsigned char mUnknown25;
    unsigned char mUnknown26;
    unsigned char mUnknown27;
};

extern "C" {
int fn_8010A2DC(Object_80039F5C *p, int a, short b);
int fn_800AC2C0(int team);
Object_80039F5C *fn_8009BCE8(int *pRef);
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
int fn_800FA098(Object_80039F5C *p, Object_80039F5C *pOther);
int fn_80125510(Object_80039F5C *p, Object_80039F5C *pOther);
unsigned char fn_8009FD7C(Object_80039F5C *p, Object_80039F5C *pOther);
Object_80039F5C *fn_800F9688(Object_80039F5C *p);
Object_80039F5C *fn_800F9480(Object_80039F5C *p);
Record_8011F4E0 *fn_8011F4E0(void);
int fn_8011F1CC(void);
int fn_8011F1A4(void);
int fn_8011E9D8(State_80039F5C *pState);
Object_80039F5C *fn_800F9E3C(Object_80039F5C *p, int flag);
unsigned char fn_800FC0C4(Object_80039F5C *p);
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
unsigned char fn_8009F6B4(void);
float fn_8016B974(void);
int fn_80178320(void);
Object_80039F5C *PlyrGet(int team, unsigned short index);
void fn_800F8588(Object_80039F5C *p, Object_80039F5C *pOther);
void fn_800F8A88(Object_80039F5C *p, Object_80039F5C *pOther);
void fn_80227538(Point_8017886C *pOut, int angle, float length);
void fn_80227690(void *pOut, void *pA, void *pB);
int fn_800F69C0(int angle, Object_80039F5C *p);
float fn_80178A08(void);
float fn_80178A44(void);
int fn_801CFE40(float y, float x);
int fn_800A5C04(Object_80039F5C *p, int a, int b);
void fn_800FA014(Object_80039F5C *p, Block_800FA300 *pBlock);
int fn_8009E180(Object_80039F5C *p);
int fn_800B65A0(int team);
float fn_8016B938(void);
void *fn_801374BC(void);
void fn_80137D58(void *pPlay, Vector_80039F5C *pOut);
int fn_8009F258(Object_80039F5C *p);
int MathAngleDiff(int a, int b);
unsigned char fn_800F8D24(Object_80039F5C *p);
unsigned char fn_800F8D2C(Object_80039F5C *p);
unsigned char fn_800F9024(Object_80039F5C *p);
unsigned char fn_800F930C(Object_80039F5C *p);
}

extern float gPlyrMoveFwdSpeed;

static unsigned char (*lbl_802DAB38[4])(Object_80039F5C *p) = {
    fn_800F8D24, fn_800F8D2C, fn_800F9024, fn_800F930C,
};

extern "C" int fn_800FA300(Object_80039F5C *p)
{
    Block_800FA300 *pBlock;
    Object_80039F5C *pTarget;
    Object_80039F5C *pOther;
    Message_800F01CC message;
    int active = 0;

    fn_8010A2DC(p, 0, -1);
    pBlock = (Block_800FA300 *)&p->mUnknown336;
    if (--pBlock->mUnknown20 & 0x80) {
        int range = 255 - p->mRatings[8];
        int random;

        if (range < 0) {
            range = 0;
        }
        random = fn_802372EC(0, (unsigned int)range >> 5);
        active = 1;
        pBlock->mUnknown20 = pBlock->mUnknown20 + random + fn_800AC2C0(p->mIdBytes[2]);
    }
    pTarget = fn_8009BCE8(&pBlock->mRef);
    if (p->mUnknown560.mFlags.mBytes[0] != 0) {
        active = 1;
    }
    if (pTarget) {
        if (fn_800FA098(p, pTarget) && fn_80125510(p, pTarget)) {
            return 0;
        }
        if (pTarget->mpState->mId != 20) {
            pBlock->mUnknown21 = 0;
        } else if (active && pBlock->mUnknown21 == 0) {
            pBlock->mUnknown21 = fn_8009FD7C(p, pTarget);
        }
    } else {
        pBlock->mUnknown21 = 0;
    }
    if (!(p->mFlags & 0x4000)) {
        if (active) {
            if (!pTarget) {
                Point_8017886C ball;
                Point_8017886C goal;
                Point_8017886C *pBall;
                Point_8017886C *pGoal;

                ball = fn_80177FE0();
                if (p->mMotion.mPos.mX > ball.mX) {
                    goal.mX = ball.mX + 4.0f;
                } else {
                    goal.mX = ball.mX - 4.0f;
                }
                pBall = &ball;
                pGoal = &goal;
                pGoal->mY = pBall->mY + 20.0f;
                fn_80227690(pGoal, pGoal, &p->mMotion.mPos);
                if (pGoal->mY < 0.0f) {
                    pGoal->mY = 2.0f;
                }
                if (p->mMotion.mPos.mY > fn_80178A44() - 2.0f) {
                    pGoal->mY = 0.0f;
                }
                pBlock->mUnknown8 = fn_801CFE40(pGoal->mY, goal.mX);
                pBlock->mUnknown4 = 0xC00000;
                pTarget = fn_800F9688(p);
                if (pTarget) {
                    pBlock->mUnknown23 = 1;
                    pBlock->mUnknown12 = 0.7f;
                    fn_8009BD2C(pTarget, &pBlock->mRef);
                } else {
                    pTarget = fn_800F9480(p);
                    if (pTarget) {
                        if (pTarget->mMotion.mPos.mY > p->mMotion.mPos.mY - 5.0f) {
                            pBlock->mUnknown12 = 1.0f;
                        } else {
                            pBlock->mUnknown12 = 0.7f;
                        }
                        pBlock->mUnknown23 = 1;
                        if (pTarget->mMotion.mPos.mY > pBall->mY + 7.0f) {
                            fn_8009BD2C(pTarget, &pBlock->mRef);
                        } else {
                            pTarget = 0;
                        }
                    } else {
                        pBlock->mUnknown12 = 0.7f;
                    }
                }
            } else if (fn_8011F4E0()->mUnknown0 < 0 && !(p->mFlags & 0x20000)
                       && (fn_8011F1CC() || fn_8011F1A4())) {
                if (pTarget->mUnknown1032 == 0) {
                    int id = fn_800F06F4(0, pTarget->mpState, 1, 0xFFFF);

                    if (id == 0xFFFF && fn_800F06F4(0, pTarget->mpState, 47, 0xFFFF) == id) {
                        unsigned char state = pTarget->mpState->mId;

                        if (state != 32 && state != 11 && state != 16) {
                            goto done;
                        }
                        if (fn_800F06F4(0, pTarget->mpState, 21, 0xFFFF) != 0xFFFF) {
                            goto done;
                        }
                    }
                }
                if (fn_8011E9D8(pTarget->mpState) && pBlock->mUnknown27 != 0) {
                    goto done;
                }
                switch (p->mUnknown2914) {
                case 14:
                    pOther = fn_800F9E3C(p, 0);
                    if (pOther) {
                        pTarget = pOther;
                        fn_8009BD2C(pTarget, &pBlock->mRef);
                        break;
                    }
                    p->mpState->mUnknown1 = fn_800FC0C4(pTarget);
                    memset(&message, 0, 4);
                    message.mId = 85;
                    message.mUnknown1[0] = 48;
                    fn_800F00D4(0, p->mpState, &message, p);
                    return 0;
                case 13:
                case 15:
                    pOther = fn_800F9E3C(p, 0);
                    if (pOther) {
                        pTarget = pOther;
                        fn_8009BD2C(pTarget, &pBlock->mRef);
                        break;
                    }
                    if ((unsigned int)(fn_8009F6B4() - 2) <= 1 || fn_8016B974() > 0.25f) {
                        p->mpState->mUnknown1 = fn_800FC0C4(pTarget);
                        memset(&message, 0, 4);
                        message.mId = 85;
                        message.mUnknown1[0] = 48;
                        fn_800F00D4(0, p->mpState, &message, p);
                        return 0;
                    }
                    p->mpState->mUnknown1 = fn_800FC0C4(pTarget);
                    memset(&message, 0, 4);
                    message.mId = 2;
                    fn_800F00D4(0, p->mpState, &message, p);
                    return 0;
                case 16:
                    fn_8009BD2C(0, &pBlock->mRef);
                    pBlock->mUnknown23 = 0;
                    break;
                case 17:
                case 18: {
                    int alone;
                    unsigned char i;
                    unsigned int count;

                    pOther = fn_800F9E3C(p, 1);
                    if (pOther) {
                        pTarget = pOther;
                        fn_8009BD2C(pTarget, &pBlock->mRef);
                        break;
                    }
                    alone = 1;
                    count = fn_80178D18(fn_80178320());
                    for (i = 0; i < count; i++) {
                        Object_80039F5C *pMate = PlyrGet(fn_80178320(), i);

                        if (pMate != p) {
                            int blocking = 0;

                            if (pMate->mUnknown2914 <= 18) {
                                blocking = pMate->mUnknown2914 >= 17;
                            }

                            if (blocking) {
                                int id = fn_800F06F4(0, pMate->mpState, 2, 0xFFFF);

                                if (id != 0xFFFF || fn_800F06F4(0, pMate->mpState, 30, 0xFFFF) != id) {
                                    blocking = 0;
                                }
                            }
                            if (blocking) {
                                alone = 0;
                                break;
                            }
                        }
                    }
                    p->mpState->mUnknown1 = fn_800FC0C4(pTarget);
                    memset(&message, 0, 4);
                    message.mId = 40;
                    if (alone) {
                        message.mUnknown1[0] = 0;
                    } else if (p->mMotion.mPos.mX < 0.0f) {
                        message.mUnknown1[0] = 1;
                    } else {
                        message.mUnknown1[0] = 2;
                    }
                    fn_800F00D4(0, p->mpState, &message, p);
                    return 0;
                }
                }
            }
        done:
            if (pBlock->mUnknown23 == 1) {
                pBlock->mUnknown23 = lbl_802DAB38[pBlock->mUnknown22](p);
                if (pBlock->mUnknown23 == 0) {
                    pBlock->mUnknown20 = 0;
                }
            } else if (pTarget) {
                fn_800F8588(p, pTarget);
                fn_800F8A88(p, pTarget);
            }
        }
        if (pBlock->mUnknown12 != 0.0f) {
            Point_8017886C direction;
            Point_8017886C *pDirection = &direction;

            fn_80227538(pDirection, pBlock->mUnknown8, 1.0f);
            pBlock->mUnknown8 = fn_800F69C0(pBlock->mUnknown8, p);
            if (p->mMotion.mPos.mX > fn_80178A08() - 2.0f && direction.mX > 0.0f) {
                direction.mX = 0.0f;
            } else if (p->mMotion.mPos.mX < 2.0f - fn_80178A08() && direction.mX < 0.0f) {
                direction.mX = 0.0f;
            }
            pBlock->mUnknown8 = fn_801CFE40(pDirection->mY, direction.mX);
        }
    }
    if (fn_800A5C04(p, pBlock->mUnknown8, pBlock->mUnknown4)) {
        return 0;
    }
    if (p->mFlags & 0x4000) {
        return 0;
    }
    fn_8011F4E0();
    pBlock->mUnknown16++;
    if (active) {
        int count;

        fn_800FA014(p, pBlock);
        count = fn_8009E180(p);
        if (count > 2) {
            if (count == 4) {
                if (fn_8009F258(p)) {
                    memset(&message, 0, 4);
                    message.mId = 24;
                    message.mUnknown1[0] = 2;
                    fn_800F053C(0, p->mpState, &message, p);
                    return 1;
                }
            } else {
                unsigned short chance = p->mRatings[8];
                Vector_80039F5C pos;

                if (fn_800B65A0(p->mIdBytes[2]) == 255) {
                    chance = chance + (int)(chance * fn_8016B938());
                }
                fn_80137D58(fn_801374BC(), &pos);
                if ((unsigned int)fn_802372EC(0, 255) < chance || pos.mY > fn_80177FE0().mY + 3.0f) {
                    memset(&message, 0, 4);
                    message.mId = 2;
                    fn_800F053C(0, p->mpState, &message, p);
                    return 1;
                }
            }
        }
    }
    if (pTarget && pTarget->mUnknown528.mUnknown15 == 1 && pBlock->mUnknown12 > 0.72f) {
        pBlock->mUnknown24 = 1;
    }
    if (pBlock->mUnknown12 != 0.0f) {
        p->mUnknown512.mUnknown14 = 3;
        p->mUnknown512.mUnknown4 = pBlock->mUnknown8;
        p->mUnknown512.mUnknown8 = pBlock->mUnknown4;
        p->mUnknown512.mUnknown0 = pBlock->mUnknown12;
    }
    p->mUnknown512.mUnknown15 = pBlock->mUnknown24;
    if (pBlock->mUnknown4 == pBlock->mUnknown8 && p->mMotion.mUnknown28 > gPlyrMoveFwdSpeed * 0.14f
        && MathAngleDiff(p->mMotion.mUnknown32, pBlock->mUnknown4) > 0x2E38E3
        && MathAngleDiff(p->mMotion.mFacing, 0xC00000) < 0x2AAAAA) {
        pBlock->mUnknown12 = 0.0f;
        p->mUnknown512.mUnknown14 = 3;
        p->mUnknown512.mUnknown4 = pBlock->mUnknown8;
        p->mUnknown512.mUnknown8 = pBlock->mUnknown4;
        p->mUnknown512.mUnknown0 = pBlock->mUnknown12;
        pBlock->mUnknown20 = 2;
    }
    return 0;
}
