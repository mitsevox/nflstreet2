#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/Plan_80121264.h"
#include "game/fn_802270D4.h"

extern "C" {

int fn_80121918(Object_80039F5C *p, Plan_80121264 *pPlan, Entry_801230B8 *pEntry);
void fn_80121CB0(Object_80039F5C *p, Entry_801230B8 *pEntry, int angle);
int fn_801CFE40(float y, float x);
void fn_80227690(void *pOut, void *pA, void *pB);

void fn_80122670(Object_80039F5C *p, Plan_80121264 *pPlan, int angle)
{
    Vector_80039F5C *pPos = &p->mMotion.mPos;
    unsigned char i;

    pPlan->mUnknown2372 = 0;
    for (i = 0; i < pPlan->mUnknown1440 - 1; i++) {
        Entry_801230B8 *pEntry = &pPlan->mUnknown1444[pPlan->mUnknown2372];
        Point_8017886C delta;

        pEntry->mpUnknown0 = &pPlan->mUnknown0[i];
        pEntry->mpUnknown4 = &pPlan->mUnknown0[i + 1];
        pEntry->mUnknown8.mX = (pEntry->mpUnknown0->mUnknown8.mX + pEntry->mpUnknown4->mUnknown8.mX) * 0.5f;
        pEntry->mUnknown8.mY = (pEntry->mpUnknown0->mUnknown8.mY + pEntry->mpUnknown4->mUnknown8.mY) * 0.5f;
        fn_80227690(&delta, &pEntry->mUnknown8, pPos);
        pEntry->mUnknown16 = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
        pEntry->mUnknown20 = fn_802270A4(&delta);
        fn_80227690(&delta, &pEntry->mpUnknown0->mUnknown8, &pEntry->mpUnknown4->mUnknown8);
        pEntry->mUnknown24 = fn_802270A4(&delta);
        pEntry->mUnknown28 = 0.0f;
        fn_80121CB0(p, pEntry, angle);
        if (fn_80121918(p, pPlan, pEntry)) {
            pPlan->mUnknown2372++;
        }
    }
}

}
