#include <math.h>
#include "game/Block_803EB028.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/fn_800F06F4.h"
#include "game/fn_80177FE0.h"
#include "game/fn_8022781C.h"

extern "C" {

extern Block_803EB028 *lbl_803EB028;

Object_80039F5C *fn_80039FE8(int team, int a, unsigned char n);
int fn_8011E484(Object_80039F5C *p, Object_80039F5C *pOther);
int fn_8011F1CC(void);
int fn_80178308(void);

int fn_8011D558(Vector_80039F5C *p, Vector_80039F5C *pA, Vector_80039F5C *pB, Vector_80039F5C *pC)
{
    float d0 = p->mX * (pC->mY - pB->mY) + pC->mX * (pB->mY - p->mY) + pB->mX * (p->mY - pC->mY);
    float d1 = pB->mX * (p->mY - pA->mY) + p->mX * (pA->mY - pB->mY) + pA->mX * (pB->mY - p->mY);
    float d2 = pA->mX * (pB->mY - pC->mY) + pB->mX * (pC->mY - pA->mY) + pC->mX * (pA->mY - pB->mY);
    float d3 = pC->mX * (pA->mY - p->mY) + pA->mX * (p->mY - pC->mY) + p->mX * (pC->mY - pA->mY);

    if ((d0 >= 0.0f && d1 >= 0.0f && d2 >= 0.0f && d3 >= 0.0f)
        || (d0 <= 0.0f && d1 <= 0.0f && d2 <= 0.0f && d3 <= 0.0f)) {
        return 1;
    }
    return 0;
}

void fn_8011DBC8(Object_80039F5C *p, Block_8011DBC8 *pBlock)
{
    pBlock->mUnknown40 = 1.0f;
    pBlock->mUnknown44 = 1.0f;
    pBlock->mUnknown48 = 1.0f;
}

void fn_8011DCDC(void)
{
    if (fn_8011F1CC()) {
        Object_80039F5C *p = fn_80039FE8(fn_80178308(), 1, 0);
        int index = 0xFFFF;
        Object_80039F5C *pOther = fn_80039FE8(fn_80178308(), 2, 0);
        int otherIndex = 0xFFFF;
        int hasOther;

        if (p) {
            index = fn_800F06F4(0, p->mQueue, 31, 0xFFFF);
        }
        if (pOther) {
            otherIndex = fn_800F06F4(0, pOther->mQueue, 31, 0xFFFF);
        }
        hasOther = otherIndex != 0xFFFF;
        if ((index != 0xFFFF && !hasOther) || (index == 0xFFFF && hasOther)) {
            Point_8017886C ball;
            float x;

            if (otherIndex != 0xFFFF && index == 0xFFFF) {
                p = pOther;
            }
            ball = fn_80177FE0();
            if (fabsf(p->mMotion.mPos.mX - ball.mX) < 0.75f) {
                index = fn_800F06F4(0, p->mQueue, 3, 0xFFFF);
                if (index == 0xFFFF) {
                    index = fn_800F06F4(0, p->mQueue, 4, 0xFFFF);
                    if (index == 0xFFFF) {
                        index = fn_800F06F4(0, p->mQueue, 27, 0xFFFF);
                    }
                }
                if (index == 0xFFFF) {
                    x = p->mMotion.mPos.mX;
                } else {
                    int angle = p->mpState[index].mUnknown2 << 17;

                    if (angle > 0x400000 && angle < 0xC00000) {
                        x = p->mMotion.mPos.mX - 2.0f;
                    } else {
                        x = p->mMotion.mPos.mX + 2.0f;
                    }
                }
            } else {
                x = p->mMotion.mPos.mX;
            }
            if (x < ball.mX) {
                lbl_803EB028->mUnknown90 = 1;
            } else {
                lbl_803EB028->mUnknown90 = 2;
            }
        }
    } else {
        lbl_803EB028->mUnknown90 = 0;
    }
}

int fn_8011E3F4(Object_80039F5C *p)
{
    int result = 0;
    Object_80039F5C *pOther;

    if (p->mUnknown1032 == 7) {
        pOther = fn_8009BCE8(&p->mUnknown1040);
    } else {
        pOther = fn_8009BCE8(&p->mUnknown1036);
    }

    switch (p->mUnknown1032) {
    case 2:
    case 3:
    case 4:
        if (fn_8022781C(&p->mMotion.mPos, &pOther->mMotion.mPos) < 2.1f) {
            result = fn_8011E484(p, pOther);
        }
        break;
    }
    return result;
}

}
