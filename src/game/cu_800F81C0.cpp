#include <math.h>
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/Message_800F01CC.h"
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

/* View of the block at player +336 used by fn_800F81C0, fn_800F846C,
   fn_800F8588, fn_800F8828, fn_800F8A88 and fn_800FA0DC. */
struct Block_800F8A88 {
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
void fn_80227690(void *pOut, void *pA, void *pB);
int fn_80178320(void);
int fn_800F6878(Object_80039F5C *p, Object_80039F5C *pOther);
void fn_800F6B2C(Object_80039F5C *p, Vector_80039F5C *pDelta);
int fn_8011E9D8(State_80039F5C *pState);
unsigned int fn_800F67E8(Object_80039F5C *pTarget);
int fn_8012CC04(int a);
int fn_8012CCA0(Object_80039F5C *p);
float fn_80178A2C(void);
void fn_8009F928(Object_80039F5C *p, Point_8017886C *pOut, int a, int b);
void fn_800F6C90(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pTarget, Vector_80039F5C *pOut);
void fn_800F6E30(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pTarget, Vector_80039F5C *pOut);
void fn_800F7314(Object_80039F5C *p, Object_80039F5C *pOther, Vector_80039F5C *pOut);
void fn_800F7798(Object_80039F5C *p, Object_80039F5C *pOther, Vector_80039F5C *pOut);
void fn_800F7B64(Object_80039F5C *p, Object_80039F5C *pOther, Vector_80039F5C *pOut);
void fn_800F7F68(Object_80039F5C *p, Object_80039F5C *pOther, Vector_80039F5C *pOut);
extern float lbl_803ECB08;
extern float lbl_803EAE40;
extern float lbl_803EAE44;
extern float lbl_803EAE48;
}

extern "C" void fn_800F81C0(Object_80039F5C *p, Object_80039F5C *pOther, Vector_80039F5C *pOut) {
    if (p && pOther && pOut) {
        Object_80137ABC *pBall = fn_801374BC();
        Vector_80039F5C *pPos = &p->mMotion.mPos;
        Block_800F8A88 *pBlock = (Block_800F8A88 *)&p->mUnknown336;
        Point_8017886C origin;
        Point_8017886C toBall;
        Point_8017886C spot;
        Point_8017886C toSpot;
        int direction;

        origin = fn_80177FE0();
        fn_80227690(&toBall, &pBall->mState.mPos, pPos);
        fn_8009F928(pOther, &spot, 5, pBlock->mUnknown21);
        fn_80227690(&toSpot, &spot, pPos);
        fn_800F6C90(p, pOther, &spot, pOut);
        fn_800F6E30(p, pOther, &spot, pOut);
        fn_800F6B2C(p, pOut);
        direction = fn_801CFE40(pOut->mY, pOut->mX) & 0xFFFFFF;
        if (pOther->mMotion.mUnknown28 < lbl_803ECB08 * 0.14f) {
            if (fn_801CFFD0(p->mMotion.mFacing, fn_801CFE40(toBall.mY, toBall.mX)) > 0x71C71) {
                pBlock->mUnknown8 = (fn_801CFE40(toBall.mY, toBall.mX) + 0x800000) & 0xFFFFFF;
                pBlock->mUnknown12 = 0.66f;
            } else {
                pBlock->mUnknown8 = (fn_801CFE40(toBall.mY, toBall.mX) + 0x800000) & 0xFFFFFF;
                pBlock->mUnknown12 = 0.0f;
            }
            pBlock->mUnknown4 = fn_801CFE40(toBall.mY, toBall.mX);
            pBlock->mUnknown24 = 0;
        } else if (fn_801CFFD0(direction, pOther->mMotion.mUnknown32) < 0x400000) {
            pBlock->mUnknown8 = direction;
            pBlock->mUnknown4 = direction;
            pBlock->mUnknown12 = 1.0f;
            if (fn_801CFFD0(p->mMotion.mFacing, direction) < 0xAAAAA) {
                pBlock->mUnknown24 = 1;
            } else {
                pBlock->mUnknown24 = 0;
            }
        } else if (pOther->mMotion.mPos.mY < origin.mY + 6.0f) {
            pBlock->mUnknown8 = direction;
            pBlock->mUnknown4 = fn_801CFE40(toSpot.mY, toSpot.mX);
            pBlock->mUnknown24 = 0;
            pBlock->mUnknown12 = 1.0f;
        } else {
            fn_80227690(&toSpot, &spot, pPos);
            pBlock->mUnknown8 = pOther->mMotion.mUnknown32;
            pBlock->mUnknown4 = fn_801CFE40(toSpot.mY, toSpot.mX);
            if (fn_800F6878(p, pOther)) {
                pBlock->mUnknown24 = 1;
                pBlock->mUnknown12 = 1.0f;
            } else {
                pBlock->mUnknown24 = 0;
                pBlock->mUnknown12 = 0.66f;
            }
        }
    }
}

extern "C" void fn_800F846C(Object_80039F5C *p, Object_80039F5C *pOther, Vector_80039F5C *pOut) {
    if (p && pOther && pOut) {
        Block_800F8A88 *pBlock = (Block_800F8A88 *)&p->mUnknown336;
        float offset;
        float distance;

        pOut->mY = lbl_803EAE40 + fn_80177FE0().mY - p->mMotion.mPos.mY;
        if (pOther->mMotion.mPos.mX > fn_80177FE0().mX) {
            offset = lbl_803EAE48;
        } else {
            offset = -lbl_803EAE48;
        }
        pOut->mX = pOther->mMotion.mPos.mX + offset - p->mMotion.mPos.mX;
        fn_800F6B2C(p, pOut);
        distance = fn_802270A4(pOut);
        pBlock->mUnknown8 = fn_801CFE40(pOut->mY, pOut->mX) & 0xFFFFFF;
        pBlock->mUnknown4 = 0xC00000;
        if (distance > lbl_803EAE44) {
            pBlock->mUnknown12 = 0.5f;
        } else {
            pBlock->mUnknown12 = 0.25f;
        }
        pBlock->mUnknown24 = 0;
    }
}

extern "C" void fn_800F8588(Object_80039F5C *p, Object_80039F5C *pOther) {
    if (p && pOther) {
        Block_800F8A88 *pBlock = (Block_800F8A88 *)&p->mUnknown336;
        Point_8017886C origin;
        Point_8017886C delta;

        origin = fn_80177FE0();
        fn_80227690(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
        if (pBlock->mUnknown26 != 3 && pBlock->mUnknown26 != 7
            && pOther->mMotion.mUnknown28 <= lbl_803ECB08 * 0.14f) {
            return;
        }
        if (fn_8011E9D8(pOther->mpState) && pBlock->mUnknown27) {
            pBlock->mUnknown26 = 6;
        } else if ((p->mUnknown2914 == 17 || p->mUnknown2914 == 18) && fn_800F67E8(pOther) > 1) {
            pBlock->mUnknown26 = 4;
        } else if (fabsf(delta.mX) > 4.0f && p->mMotion.mPos.mY < fn_80178A2C()
                   && (p->mMotion.mPos.mY > origin.mY + 4.0f || pOther->mMotion.mPos.mY < origin.mY - 1.0f)) {
            pBlock->mUnknown26 = 3;
        } else if (pOther->mpState->mId == 20) {
            float total = fn_8012CC04(pOther->mpState->mUnknown2);
            float done = fn_8012CCA0(pOther);

            if (done / total > (1.0f - p->mRatings[8] * 0.003921569f) * 0.75f) {
                pBlock->mUnknown26 = 2;
            } else if (pBlock->mUnknown26 == 7) {
                pBlock->mUnknown26 = 0;
            } else {
                return;
            }
        } else {
            float limit = p->mMotion.mPos.mY < fn_80178A2C() ? 25.0f : 58.0f;

            if (fn_801CFFD0(pOther->mMotion.mUnknown32, 0x400000) < (int)(limit * 46603.38f)
                || fn_801CFFD0(pOther->mMotion.mUnknown32, 0xC00000) < (int)(limit * 46603.38f)) {
                pBlock->mUnknown26 = 0;
            } else {
                pBlock->mUnknown26 = 1;
            }
        }
    }
}

extern "C" void fn_800F8828(Object_80039F5C *p, Object_80039F5C *pOther, Block_800F8A88 *pBlock) {
    if (p && pOther) {
        Point_8017886C origin;

        origin = fn_80177FE0();
        p->mpState->mUnknown2 |= pBlock->mUnknown25;
        if (fabsf(p->mMotion.mPos.mY - origin.mY) <= 5.0f && fabsf(pOther->mMotion.mPos.mY - origin.mY) <= 5.0f
            && pBlock->mUnknown25 == 2) {
            p->mpState->mUnknown2 &= ~pBlock->mUnknown25;
        }
    }
}

extern "C" void fn_800F88E4(Object_80039F5C *p, Object_80039F5C *pTarget) {
    unsigned char *pMine = &p->mpState->mUnknown2;
    unsigned char *pTheirs = 0;
    Object_80039F5C *pFound = 0;
    unsigned short i;
    unsigned int n = fn_80178D18(fn_80178320());

    for (i = 0; i < n; i++) {
        Object_80039F5C *pOther = fn_80039F5C(fn_80178320(), i);

        if (pOther->mpState->mId == 22 && pTarget == fn_8009BCE8(&pOther->mUnknown336) && pOther != p) {
            pFound = pOther;
            pTheirs = &pFound->mpState->mUnknown2;
        }
    }
    if (pFound && fn_8022781C(&pFound->mMotion.mPos, &pTarget->mMotion.mPos) < 5.0f
        && fn_8022781C(&p->mMotion.mPos, &pTarget->mMotion.mPos) < 5.0f) {
        Vector_80039F5C ball;
        int right;

        fn_80137D58(fn_801374BC(), &ball);
        right = pTarget->mMotion.mPos.mX > ball.mX;
        *pTheirs &= ~1;
        *pMine &= ~1;
        *pTheirs &= ~2;
        *pMine &= ~2;
        if ((right && pFound->mMotion.mPos.mX < p->mMotion.mPos.mX)
            || (!right && pFound->mMotion.mPos.mX > p->mMotion.mPos.mX)) {
            *pTheirs |= 2;
            *pMine |= 1;
        } else {
            *pTheirs |= 1;
            *pMine |= 2;
        }
    }
}

extern "C" void fn_800F8A88(Object_80039F5C *p, Object_80039F5C *pOther) {
    Block_800F8A88 *pBlock = (Block_800F8A88 *)&p->mUnknown336;
    Point_8017886C delta;

    pBlock->mUnknown24 = 0;
    fn_80227690(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
    if (pOther->mpState->mId == 56) {
        pBlock->mUnknown12 = 0.0f;
    } else {
        Vector_80039F5C out;
        int unknown32;

        fn_800F8828(p, pOther, pBlock);
        fn_800F88E4(p, pOther);
        out.mX = out.mY = out.mZ = 0.0f;
        switch (pBlock->mUnknown26) {
        case 0:
            fn_800F7314(p, pOther, &out);
            break;
        case 1:
            fn_800F7798(p, pOther, &out);
            break;
        case 2:
            fn_800F7B64(p, pOther, &out);
            break;
        case 3:
            fn_800F7F68(p, pOther, &out);
            break;
        case 4:
            fn_800F81C0(p, pOther, &out);
            break;
        case 5:
            break;
        case 6:
            fn_800F846C(p, pOther, &out);
            break;
        }
        unknown32 = p->mMotion.mUnknown32;
        if (fn_801CFFD0(pBlock->mUnknown8, p->mMotion.mFacing) > 0x600000
            && pOther->mMotion.mUnknown28 >= lbl_803ECB08 * 0.14f && pBlock->mUnknown12 >= lbl_803ECB08 * 0.14f
            && fn_802270A4(&delta) < 5.0f) {
            int angle = ((pBlock->mUnknown8 + unknown32) / 2) & 0xFFFFFF;

            if (fn_801CFFD0(angle, pBlock->mUnknown8) > 0x400000) {
                angle = (angle + 0x800000) & 0xFFFFFF;
            }
            pBlock->mUnknown8 = angle;
            pBlock->mUnknown12 = 0.66f;
            pBlock->mUnknown20 = 0;
        }
        pBlock->mUnknown8 &= 0xFFFFFF;
        pBlock->mUnknown4 &= 0xFFFFFF;
        if (pBlock->mUnknown16 <= 44 && p->mpState->mUnknown1 == 2 && pOther->mUnknown1052 != 0) {
            switch (p->mUnknown2914) {
            case 13:
            case 15:
                pBlock->mUnknown12 = 0.65f;
                break;
            case 17:
            case 18:
                pBlock->mUnknown12 = 0.45f;
                break;
            }
        }
        pBlock->mUnknown12 = pBlock->mUnknown12 < 0.0f ? 0.0f : pBlock->mUnknown12;
    }
}
