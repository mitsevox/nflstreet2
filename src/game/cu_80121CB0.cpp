#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/Plan_80121264.h"
#include <math.h>

extern "C" {

int fn_801486A0(void);
float fn_80178A08(void);
float fn_80178A2C(void);
float fn_80178A44(void);
int fn_801218EC(Point_8017886C *pPos, Entry_80120E98 *pA, Entry_80120E98 *pB);
int fn_801CFFD0(int a, int b);
float fn_801CFB94(int angle);
void fn_80227690(void *pOut, void *pA, void *pB);

void fn_80121CB0(Object_80039F5C *p, Entry_801230B8 *pEntry, int angle)
{
    Point_8017886C *pPos = (Point_8017886C *)&p->mMotion.mPos;
    int flagsB = pEntry->mpUnknown4->mUnknown36;
    int flagsA = pEntry->mpUnknown0->mUnknown36;
    int facing = p->mMotion.mFacing;
    float weight = 0.0f;
    int adjust = 0;
    int inside = fn_801218EC(pPos, pEntry->mpUnknown0, pEntry->mpUnknown4);
    Point_8017886C delta;
    int heading;

    if (!inside && !((flagsA | flagsB) & 0x40)) {
        if (pPos->mX > pEntry->mpUnknown4->mUnknown8.mX &&
            pEntry->mpUnknown4->mUnknown8.mY < pEntry->mpUnknown0->mUnknown8.mY) {
            fn_80227690(&delta, &pEntry->mpUnknown4->mUnknown8, &pEntry->mUnknown8);
            adjust = 1;
            weight = fn_801CFB94(fn_801CFFD0(delta.Heading() & 0xFFFFFF, (pEntry->mUnknown16 + 0x800000) & 0xFFFFFF));
            delta = pEntry->mpUnknown0->mUnknown8;
        } else if (pPos->mX < pEntry->mpUnknown0->mUnknown8.mX &&
                   pEntry->mpUnknown4->mUnknown8.mY > pEntry->mpUnknown0->mUnknown8.mY) {
            fn_80227690(&delta, &pEntry->mpUnknown0->mUnknown8, &pEntry->mUnknown8);
            adjust = 1;
            weight = fn_801CFB94(fn_801CFFD0(delta.Heading() & 0xFFFFFF, (pEntry->mUnknown16 + 0x800000) & 0xFFFFFF));
            delta = pEntry->mpUnknown4->mUnknown8;
        }
    } else if ((flagsA & 1) && (flagsB & 1)) {
        if (pEntry->mUnknown20 > 1.5f && pEntry->mUnknown24 < 4.0f) {
            if (pEntry->mpUnknown4->mUnknown8.mY > pEntry->mpUnknown0->mUnknown8.mY) {
                fn_80227690(&delta, &pEntry->mpUnknown4->mUnknown8, &pEntry->mpUnknown0->mUnknown8);
                heading = delta.Heading() & 0xFFFFFF;
                delta = pEntry->mpUnknown4->mUnknown8;
            } else {
                fn_80227690(&delta, &pEntry->mpUnknown0->mUnknown8, &pEntry->mpUnknown4->mUnknown8);
                heading = delta.Heading() & 0xFFFFFF;
                delta = pEntry->mpUnknown0->mUnknown8;
            }
            adjust = 1;
            weight = fn_801CFB94(fn_801CFFD0(heading, 0x400000));
        } else if (pEntry->mUnknown24 > 8.0f && fn_801CFFD0(pEntry->mUnknown16, angle) > 0x271C71 &&
                   fn_801CFFD0(pEntry->mUnknown16, facing) > 0x271C71) {
            pEntry->mUnknown16 = angle;
        } else if (inside && pPos->mY > fn_80178A2C() - 5.0f && fn_801486A0()) {
            pEntry->mUnknown16 = angle;
        }
    } else if ((flagsA & 2) && (flagsB & 1) || (flagsA & 1) && (flagsB & 2)) {
        Entry_80120E98 *pOther;

        if (flagsA & 2) {
            delta = pEntry->mpUnknown4->mUnknown8;
            pOther = pEntry->mpUnknown0;
        } else {
            delta = pEntry->mpUnknown0->mUnknown8;
            pOther = pEntry->mpUnknown4;
        }
        if (delta.mY < pOther->mUnknown8.mY) {
            adjust = 1;
        }
        if (adjust) {
            fn_80227690(&delta, &delta, &pEntry->mUnknown8);
            weight = fn_801CFB94(fn_801CFFD0(delta.Heading() & 0xFFFFFF, (pEntry->mUnknown16 + 0x800000) & 0xFFFFFF) / 2);
            if (flagsA & 2) {
                delta = pEntry->mpUnknown0->mUnknown8;
            } else {
                delta = pEntry->mpUnknown4->mUnknown8;
            }
        }
    } else if ((flagsA & 8) && (flagsB & 1) || (flagsA & 1) && (flagsB & 8) || (flagsA & 8) && (flagsB & 2) ||
               (flagsA & 2) && (flagsB & 8)) {
        if (pEntry->mUnknown20 > 1.5f && pEntry->mUnknown24 > 4.0f || !fn_801486A0()) {
            Entry_80120E98 *pEnd;

            if (flagsA & 3) {
                pEnd = pEntry->mpUnknown0;
            } else {
                pEnd = pEntry->mpUnknown4;
            }
            delta = pEnd->mUnknown8;
            heading = (pEnd->mUnknown20 + 0x800000) & 0xFFFFFF;
            if (fn_801CFFD0(heading, pEntry->mUnknown16) > 0x400000 &&
                fn_801CFFD0(pEntry->mUnknown16, facing) > 0x200000) {
                pEntry->mUnknown16 = angle;
            } else if (fn_801CFFD0(heading, pEntry->mUnknown16) > 0x200000 &&
                       fabsf(pPos->mX - delta.mX) > 0.55f) {
                adjust = 1;
                weight = 0.35f;
            }
        } else {
            delta.mX = pPos->mX;
            adjust = 1;
            delta.mY = fn_80178A44();
            weight = 1.0f - pEntry->mUnknown20 / 1.5f;
        }
    } else if ((flagsA & 0x40) && (flagsB & 1) || (flagsA & 1) && (flagsB & 0x40) || (flagsA & 0x40) && (flagsB & 2) ||
               (flagsA & 2) && (flagsB & 0x40)) {
        if (fabsf(pPos->mX) > fabsf(pEntry->mUnknown8.mX)) {
            pEntry->mUnknown16 = angle;
        } else if (pEntry->mUnknown24 > 4.0f) {
            Entry_80120E98 *pEnd;

            if (flagsA & 3) {
                pEnd = pEntry->mpUnknown0;
            } else {
                pEnd = pEntry->mpUnknown4;
            }
            delta = pEnd->mUnknown8;
            weight = pEnd->mUnknown28;
            if (weight < 2.0f) {
                adjust = 1;
                weight *= 0.175f;
            }
        }
    } else if ((flagsA & 2) && (flagsB & 2)) {
        if (pEntry->mUnknown8.mY - pPos->mY < 2.0f) {
            adjust = 1;
            weight = 0.35f;
            if (fabsf(pEntry->mpUnknown4->mUnknown8.mX - pPos->mX) < fabsf(pEntry->mpUnknown0->mUnknown8.mX - pPos->mX)) {
                delta = pEntry->mpUnknown4->mUnknown8;
            } else {
                delta = pEntry->mpUnknown0->mUnknown8;
            }
        }
    } else if ((flagsA & 8) && (flagsB & 8)) {
        if (inside) {
            pEntry->mUnknown16 = angle;
        }
    } else if ((flagsA & 0x40) && (flagsB & 8) || (flagsA & 8) && (flagsB & 0x40)) {
        if (fabsf(pPos->mX) > fabsf(pEntry->mUnknown8.mX)) {
            pEntry->mUnknown16 = angle;
        } else if ((flagsA | flagsB) & 0x10) {
            if (pEntry->mUnknown24 > 4.0f) {
                adjust = 1;
                weight = 0.35f;
                if (flagsA & 0x10) {
                    delta = pEntry->mpUnknown0->mUnknown8;
                } else {
                    delta = pEntry->mpUnknown4->mUnknown8;
                }
            }
        } else if (inside && pEntry->mUnknown24 > fn_80178A08() * 0.5f) {
            if (angle < pEntry->mUnknown16) {
                fn_80227690(&delta, &pEntry->mpUnknown4->mUnknown8, pPos);
                heading = delta.Heading() & 0xFFFFFF;
                pEntry->mUnknown16 = angle < heading ? heading : angle;
            } else {
                fn_80227690(&delta, &pEntry->mpUnknown0->mUnknown8, pPos);
                heading = delta.Heading() & 0xFFFFFF;
                pEntry->mUnknown16 = angle > heading ? heading : angle;
            }
            delta = pEntry->mUnknown8;
            weight = 0.35f;
            adjust = 1;
        }
    } else if ((flagsA & 0x40) && (flagsB & 0x40)) {
        pEntry->mUnknown16 = angle;
    }

    if (inside && pEntry->mUnknown24 > 4.0f && fn_801CFFD0(angle, 0x400000) <= 0x238E38) {
        fn_80227690(&delta, &pEntry->mpUnknown4->mUnknown8, pPos);
        heading = delta.Heading() & 0xFFFFFF;
        if (angle > heading) {
            fn_80227690(&delta, &pEntry->mpUnknown0->mUnknown8, pPos);
            heading = delta.Heading() & 0xFFFFFF;
            if (angle < heading) {
                pEntry->mUnknown16 = angle;
                adjust = 0;
            }
        }
    }
    if (adjust) {
        fn_80227690(&delta, &delta, pPos);
        heading = delta.Heading() & 0xFFFFFF;
        if (((heading - pEntry->mUnknown16) & 0xFFFFFF) > 0x800000) {
            pEntry->mUnknown16 = (pEntry->mUnknown16 - (int)(fn_801CFFD0(heading, pEntry->mUnknown16) * weight)) & 0xFFFFFF;
        } else {
            pEntry->mUnknown16 = (pEntry->mUnknown16 + (int)(fn_801CFFD0(heading, pEntry->mUnknown16) * weight)) & 0xFFFFFF;
        }
    }
}

}
