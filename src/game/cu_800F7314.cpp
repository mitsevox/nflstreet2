#include <math.h>
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/cu_80136B1C.h"
#include "game/fn_80177FE0.h"

/* View of the block at player +336 (same layout as Block_800F8A88 in
   src/game/cu_800F81C0.cpp). */
struct Block_800F7314 {
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
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
float fn_801CFB18(int angle);
void fn_80227690(void *pOut, void *pA, void *pB);
float fn_802270A4(void *p);
void fn_80227538(void *pOut, int angle, float length);
float fn_80178A2C(void);
float fn_80178A44(void);
int fn_800F6878(Object_80039F5C *p, Object_80039F5C *pOther);
void fn_800F6AD8(float *p);
void fn_800F6B2C(Object_80039F5C *p, Vector_80039F5C *pDelta);
void fn_800F6D40(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pTarget, Vector_80039F5C *pOut);
void fn_800F6E30(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pTarget, Vector_80039F5C *pOut);
void fn_800F70D0(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pTarget, Vector_80039F5C *pOut);
void fn_800F722C(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pTarget, Vector_80039F5C *pOut);
void fn_8009F928(Object_80039F5C *p, Point_8017886C *pOut, int a, int b);
int fn_8012CAB4(Object_80039F5C *p);
void fn_8012CD4C(Object_80039F5C *p, Point_8017886C *pOut);
int fn_80120794(Object_800B26B0 *pA, Object_800B26B0 *pB, float *pC, float e, float f, int d, float g);
void fn_800F7314(Object_80039F5C *p, Object_80039F5C *pOther, Vector_80039F5C *pOut);
void fn_800F7798(Object_80039F5C *p, Object_80039F5C *pOther, Vector_80039F5C *pOut);
extern float lbl_803ECB08;
extern float lbl_803EAE2C;
extern const float lbl_803ED6CC;
}

extern "C" void fn_800F7314(Object_80039F5C *p, Object_80039F5C *pOther, Vector_80039F5C *pOut) {
    float speed = 0.0f;

    if (p && pOther && pOut) {
        Object_80137ABC *pBall = fn_801374BC();
        Vector_80039F5C *pPos = &p->mMotion.mPos;
        Point_8017886C toBall;
        Block_800F7314 *pBlock = (Block_800F7314 *)&p->mUnknown336;
        Point_8017886C spot;
        Point_8017886C toSpot;
        int heading;
        int direction;

        fn_80227690(&toBall, &pBall->mState.mPos, pPos);
        fn_8009F928(pOther, &spot, 5, pBlock->mUnknown21);
        fn_80227690(&toSpot, &spot, pPos);
        fn_800F6D40(p, pOther, &spot, pOut);
        fn_800F6E30(p, pOther, &spot, pOut);
        fn_800F6B2C(p, pOut);
        heading = fn_801CFE40(pOut->mY, pOut->mX);
        direction = heading & 0xFFFFFF;
        if (p->mMotion.mPos.mY >= fn_80178A44() - 5.0f && fn_801CFFD0(p->mMotion.mUnknown32, 0x400000) > 0x1C71C7
            && fn_802270A4(&toSpot) < 2.0f) {
            pOut->mY = 0.0f;
            pBlock->mUnknown24 = 0;
            pBlock->mUnknown8 = fn_801CFE40(0.0f, pOut->mX);
            pBlock->mUnknown4 = 0xC00000;
            pBlock->mUnknown12 = 0.66f;
        } else if (pOther->mMotion.mUnknown28 < lbl_803ECB08 * 0.14f) {
            if (fn_801CFFD0(p->mMotion.mFacing, toBall.Heading()) > 0x11C71C) {
                pBlock->mUnknown8 = (toBall.Heading() + 0x400000) & 0xFFFFFF;
                pBlock->mUnknown12 = 0.25f;
            } else {
                pBlock->mUnknown8 = (toBall.Heading() + 0x400000) & 0xFFFFFF;
                pBlock->mUnknown12 = 0.0f;
            }
            pBlock->mUnknown4 = toBall.Heading();
            pBlock->mUnknown24 = 0;
        } else if (fn_801CFFD0(direction, pOther->mMotion.mUnknown32) <= 0x3FFFFF) {
            int facing = pOther->mMotion.mUnknown32;
            Point_8017886C flat;

            if (fn_801CFFD0(direction, facing) > 0x200000 && p->mMotion.mPos.mY < fn_80178A2C()) {
                int delta = (facing - direction) & 0xFFFFFF;
                direction = facing - 0x200000;
                if (delta > 0x800000) {
                    direction = facing + 0x200000;
                }
            }
            pBlock->mUnknown4 = direction;
            pBlock->mUnknown8 = direction;
            flat = toSpot;
            flat.mX = 0.0f;
            speed = pOther->mMotion.mUnknown28
                / (lbl_803ECB08 * ((1.0f - lbl_803ED6CC) * (p->mRatings[4] / 255.0f) + lbl_803ED6CC));
            if (fn_802270A4(&flat) > 1.5f) {
                speed = 1.0f;
            }
            pBlock->mUnknown12 = speed;
            pBlock->mUnknown12 = speed > 1.0f ? 1.0f : speed;
            if (fn_801CFFD0(pBlock->mUnknown8, p->mMotion.mUnknown32) < 0xAAAAA) {
                pBlock->mUnknown24 = 1;
            } else {
                pBlock->mUnknown24 = 0;
            }
        } else {
            int near;

            pBlock->mUnknown8 = direction;
            pBlock->mUnknown4 = 0xC00000;
            near = fn_800F6878(p, pOther);
            if (near || fn_801CFFD0(direction, pOther->mMotion.mUnknown32) <= 0x3FFFFF) {
                if (pBall->mState.mPos.mX > pOther->mMotion.mPos.mX) {
                    pBlock->mUnknown4 = 0x31C71C;
                    pBlock->mUnknown8 = 0x31C71C;
                } else if (pBall->mState.mPos.mX < pOther->mMotion.mPos.mX) {
                    pBlock->mUnknown4 = 0x4E38E3;
                    pBlock->mUnknown8 = 0x4E38E3;
                }
                pBlock->mUnknown24 = 1;
                pBlock->mUnknown12 = 1.0f;
            } else {
                if (fn_801CFFD0(pOther->mMotion.mUnknown32, 0x400000) <= 0x11C71B
                    && p->mMotion.mPos.mX - pOther->mMotion.mPos.mX < lbl_803EAE2C
                    && p->mMotion.mPos.mY > pOther->mMotion.mPos.mY + 2.0f) {
                    pBlock->mUnknown23 = 1;
                    pBlock->mUnknown22 = 2;
                    pBlock->mUnknown20 = 0;
                }
                pBlock->mUnknown24 = 0;
                pBlock->mUnknown12 = 0.66f;
            }
        }
    }
}

extern "C" void fn_800F7798(Object_80039F5C *p, Object_80039F5C *pOther, Vector_80039F5C *pOut) {
    if (p && pOther && pOut) {
        Vector_80039F5C *pPos = &p->mMotion.mPos;
        Block_800F7314 *pBlock = (Block_800F7314 *)&p->mUnknown336;
        Point_8017886C toBall;
        Point_8017886C spot;
        Point_8017886C toSpot;
        int heading;
        int direction;

        fn_80227690(&toBall, &fn_801374BC()->mState.mPos, pPos);
        fn_8009F928(pOther, &spot, 5, pBlock->mUnknown21);
        fn_80227690(&toSpot, &spot, pPos);
        fn_800F70D0(p, pOther, &spot, pOut);
        fn_800F722C(p, pOther, &spot, pOut);
        fn_800F6B2C(p, pOut);
        heading = fn_801CFE40(pOut->mY, pOut->mX);
        direction = heading & 0xFFFFFF;
        if (p->mMotion.mPos.mY >= fn_80178A44() - 5.0f && fn_801CFFD0(p->mMotion.mUnknown32, 0x400000) > 0x1C71C7
            && fn_802270A4(&toSpot) < 2.0f) {
            pOut->mY = 0.0f;
            pBlock->mUnknown24 = 0;
            pBlock->mUnknown8 = fn_801CFE40(0.0f, pOut->mX);
            pBlock->mUnknown4 = 0xC00000;
            pBlock->mUnknown12 = 0.66f;
        } else if (pOther->mMotion.mUnknown28 < lbl_803ECB08 * 0.14f) {
            if (fn_801CFFD0(p->mMotion.mFacing, toBall.Heading()) > 0x11C71C) {
                pBlock->mUnknown8 = (toBall.Heading() + 0x800000) & 0xFFFFFF;
                pBlock->mUnknown12 = 0.25f;
            } else {
                pBlock->mUnknown8 = (toBall.Heading() + 0x800000) & 0xFFFFFF;
                pBlock->mUnknown12 = 0.0f;
            }
            pBlock->mUnknown4 = toBall.Heading();
            pBlock->mUnknown24 = 0;
            return;
        } else if (fn_801CFFD0(direction, pOther->mMotion.mUnknown32) <= 0x3FFFFF) {
            int facing = pOther->mMotion.mUnknown32;
            Point_8017886C flat;
            float speed;

            if (fn_801CFFD0(direction, facing) > 0x200000 && p->mMotion.mPos.mY < fn_80178A2C()) {
                int delta = (facing - direction) & 0xFFFFFF;
                direction = facing - 0x200000;
                if (delta > 0x800000) {
                    direction = facing + 0x200000;
                }
            }
            pBlock->mUnknown4 = direction;
            pBlock->mUnknown8 = direction;
            flat = toSpot;
            flat.mY = 0.0f;
            speed = pOther->mMotion.mUnknown28
                / (lbl_803ECB08 * ((1.0f - lbl_803ED6CC) * (p->mRatings[4] / 255.0f) + lbl_803ED6CC));
            if (fn_802270A4(&flat) > 1.5f) {
                speed = 1.0f;
            }
            pBlock->mUnknown12 = speed;
            pBlock->mUnknown12 = speed > 1.0f ? 1.0f : speed;
            if (fn_801CFFD0(pBlock->mUnknown8, p->mMotion.mUnknown32) < 0xAAAAA) {
                pBlock->mUnknown24 = 1;
            } else {
                pBlock->mUnknown24 = 0;
            }
            return;
        } else {
            if (p->mMotion.mPos.mY - pOther->mMotion.mPos.mY < 7.0f && pOther->mMotion.mUnknown32 < 0x800000) {
                direction = pOther->mMotion.mUnknown32;
            }
            pBlock->mUnknown24 = 0;
            pBlock->mUnknown8 = direction;
        }
        pBlock->mUnknown4 = 0xC00000;
        pBlock->mUnknown12 = 0.66f;
    }
}

extern "C" void fn_800F7B64(Object_80039F5C *p, Object_80039F5C *pOther, Vector_80039F5C *pOut) {
    float lift = 0.0f;
    float side = lift;

    if (p && pOther && pOut) {
        Point_8017886C toOther;
        Block_800F7314 *pBlock;

        fn_80227690(&toOther, &pOther->mMotion.mPos, &p->mMotion.mPos);
        pBlock = (Block_800F7314 *)&p->mUnknown336;
        if (pOther->mpState->mId == 0x14 && pBlock->mUnknown21 != 0) {
            Point_8017886C spot;
            int angle;

            fn_8012CD4C(pOther, &spot);
            angle = fn_8012CAB4(pOther) & 0xFFFFFF;
            if (fn_801CFFD0(angle, 0) < 0x200000) {
                side = 1.0f;
            } else if (fn_801CFFD0(angle, 0x800000) < 0x200000) {
                side = -1.0f;
            } else {
                int diff = fn_801CFFD0(angle, 0x400000);

                if (diff < 0x200000) {
                    if (p->mMotion.mPos.mX > pOther->mMotion.mPos.mX) {
                            side = 1.0f;
                        } else {
                            side = -1.0f;
                        }
                        side *= fn_801CFB18(0x400000 - diff);
                    if ((angle < 0x355555 && side > 0.0f) || (angle > 0x4AAAAB && side < 0.0f)) {
                        side *= 0.25f;
                    }
                    lift = 1.0f;
                } else {
                    diff = fn_801CFFD0(angle, 0xC00000);
                    if (diff < 0x200000) {
                        if (p->mMotion.mPos.mX > pOther->mMotion.mPos.mX) {
                            side = 1.0f;
                        } else {
                            side = -1.0f;
                        }
                        side *= fn_801CFB18(0xC00000 - diff);
                        if ((angle > 0xCE38E4 && side > 0.0f) || (angle < 0xB55556 && side < 0.0f)) {
                            side *= 0.25f;
                        }
                    }
                }
            }
            if ((unsigned int)(pOther->mpState->mUnknown2 - 8) <= 1 && fn_801CFFD0(angle, 0x400000) < 0x1C71C7) {
                side = 0.0f;
                lift = 2.0f;
            }
            if (p->mMotion.mPos.mY > pOther->mMotion.mPos.mY) {
                pOut->mX = spot.mX - p->mMotion.mPos.mX + side;
                pOut->mY = pOther->mMotion.mPos.mY - p->mMotion.mPos.mY + 1.0f + lift;
                fn_800F6AD8(&pOut->mX);
                fn_800F6B2C(p, pOut);
                pBlock->mUnknown8 = fn_801CFE40(pOut->mY, pOut->mX);
                pBlock->mUnknown24 = 0;
                pBlock->mUnknown12 = 0.66f;
                if (fn_801CFFD0(angle, 0xC00000) < 0x200000) {
                    pBlock->mUnknown4 = toOther.Heading();
                } else {
                    pBlock->mUnknown4 = pBlock->mUnknown8;
                }
            } else {
                pOut->mX = spot.mX - p->mMotion.mPos.mX + side;
                pOut->mY = pOther->mMotion.mPos.mY - p->mMotion.mPos.mY - 1.0f + lift;
                fn_800F6AD8(&pOut->mX);
                fn_800F6B2C(p, pOut);
                pBlock->mUnknown4 = pBlock->mUnknown8 = fn_801CFE40(pOut->mY, pOut->mX);
                pBlock->mUnknown12 = 0.66f;
                pBlock->mUnknown24 = 0;
            }
        } else if (fn_801CFFD0(pOther->mMotion.mUnknown32, 0) < 0x1C71C7
                   || fn_801CFFD0(pOther->mMotion.mUnknown32, 0x800000) < 0x1C71C7) {
            fn_800F7798(p, pOther, pOut);
        } else {
            fn_800F7314(p, pOther, pOut);
        }
    }
}

extern "C" void fn_800F7F68(Object_80039F5C *p, Object_80039F5C *pOther, Vector_80039F5C *pOut) {
    if (p && pOther && pOut) {
        Vector_80039F5C *pPos = &p->mMotion.mPos;
        Point_8017886C toOther;
        Point_8017886C fromOther;
        Block_800F7314 *pBlock;
        Point_8017886C origin;
        Vector_80039F5C target;
        int angle;

        fn_80227690(&toOther, &pOther->mMotion.mPos, pPos);
        fn_80227690(&fromOther, pPos, &pOther->mMotion.mPos);
        pBlock = (Block_800F7314 *)&p->mUnknown336;
        origin = fn_80177FE0();
        if ((fn_801CFFD0(pOther->mMotion.mUnknown32, fromOther.Heading()) < 0xE38E3 && fn_802270A4(&toOther) < 12.0f
             && (pOther->mMotion.mUnknown28 >= lbl_803ECB08 * 0.14f
                 || fabsf(pOther->mMotion.mPos.mY - origin.mY) < 2.5f))
            || pOther->mpState->mId == 0x34) {
            pBlock->mUnknown8 = pOther->mMotion.mUnknown32;
            pBlock->mUnknown4 = toOther.Heading();
            pBlock->mUnknown12 = 0.5f;
            pBlock->mUnknown24 = 0;
            pOut->mX = pOut->mY = pOut->mZ = 0.0f;
            return;
        }
        fn_80227538(&target, (pOther->mMotion.mUnknown32 + 0x800000) & 0xFFFFFF, 1.0f);
        fn_800F6B2C(p, &target);
        target.mX += pOther->mMotion.mPos.mX;
        target.mZ = 0.0f;
        target.mY += pOther->mMotion.mPos.mY;
        fn_80227690(pOut, &target, pPos);
        angle = fn_80120794(&p->mMotion, (Object_800B26B0 *)&target, &pOther->mMotion.mUnknown40,
                            p->mMotion.mUnknown28, pOther->mMotion.mUnknown28, pOther->mMotion.mUnknown32,
                            fn_802270A4(&toOther));
        pBlock->mUnknown8 = angle;
        pBlock->mUnknown12 = 1.0f;
        pBlock->mUnknown4 = angle;
        if (fn_801CFFD0(p->mMotion.mFacing, angle) < 0xAAAAA) {
            pBlock->mUnknown24 = 1;
        } else {
            pBlock->mUnknown24 = 0;
        }
    }
}
