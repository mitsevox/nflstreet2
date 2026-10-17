#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/Plan_80121264.h"

extern "C" {

int fn_80120A50(Point_8017886C *p, Point_8017886C *pA, Point_8017886C *pB, Point_8017886C *pC);
int fn_801218EC(Point_8017886C *pPos, Entry_80120E98 *pA, Entry_80120E98 *pB);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
void fn_80227690(void *pOut, void *pA, void *pB);

int fn_80121918(Object_80039F5C *p, Plan_80121264 *pPlan, Entry_801230B8 *pEntry)
{
    Point_8017886C *pPos;
    unsigned char i;
    unsigned char j;

    if (pEntry->mpUnknown4->mUnknown40 == pEntry->mpUnknown0->mUnknown40 &&
        pEntry->mpUnknown4->mUnknown44 == pEntry->mpUnknown0->mUnknown44) {
        return 0;
    }
    if (pEntry->mpUnknown4->mUnknown8.mX < pEntry->mpUnknown0->mUnknown8.mX) {
        return 0;
    }
    if (pEntry->mUnknown24 < 0.55f && !((pEntry->mpUnknown0->mUnknown36 | pEntry->mpUnknown4->mUnknown36) & 4)) {
        return 0;
    }
    if (fn_801CFFD0(p->mMotion.mFacing, pEntry->mUnknown16) > 0x51C71C) {
        return 0;
    }
    pPos = (Point_8017886C *)&p->mMotion.mPos;
    if (!fn_801218EC(pPos, pEntry->mpUnknown0, pEntry->mpUnknown4)) {
        Entry_80120E98 *pNear = pEntry->mUnknown16 > 0x400000 ? pEntry->mpUnknown4 : pEntry->mpUnknown0;
        Point_8017886C delta;
        int angle;

        delta.mX = pNear->mUnknown8.mX;
        delta.mY = pNear->mUnknown8.mY;
        fn_80227690(&delta, &delta, pPos);
        angle = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
        if (fn_801CFFD0(pEntry->mUnknown16, 0x400000) < fn_801CFFD0(angle, 0x400000)) {
            return 0;
        }
        if (fn_801CFFD0(pEntry->mUnknown16, angle) <= 0x4FA4E) {
            return 0;
        }
    }
    for (i = 0; i < pPlan->mUnknown1440 - 1; i++) {
        Entry_80120E98 *pCur = &pPlan->mUnknown0[i];
        Entry_80120E98 *pNext = &pPlan->mUnknown0[i + 1];

        if (pCur != pEntry->mpUnknown0 && pNext != pEntry->mpUnknown4 &&
            fn_80120A50(&pCur->mUnknown8, &pNext->mUnknown8, pPos, &pEntry->mUnknown8)) {
            return 0;
        }
        if ((pCur->mUnknown36 & 1) && fn_80120A50(pCur->mpUnknown0, pCur->mpUnknown4, pPos, &pEntry->mUnknown8)) {
            return 0;
        }
    }
    for (i = 1; i < pPlan->mUnknown1440 - 2; i++) {
        Entry_80120E98 *pCur = &pPlan->mUnknown0[i];

        for (j = i + 1; j < pPlan->mUnknown1440 - 1; j++) {
            Entry_80120E98 *pOther = &pPlan->mUnknown0[j];

            if ((pCur != pEntry->mpUnknown0 || pOther != pEntry->mpUnknown4) &&
                pCur->mUnknown40 == pOther->mUnknown40 && pCur->mUnknown44 == pOther->mUnknown44 &&
                fn_80120A50(&pCur->mUnknown8, &pOther->mUnknown8, pPos, &pEntry->mUnknown8)) {
                return 0;
            }
        }
    }
    return 1;
}

}
