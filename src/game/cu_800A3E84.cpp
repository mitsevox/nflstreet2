#include "game/Object_80039F5C.h"
#include "game/fn_801BE60C.h"
#include "game/fn_8022781C.h"
#include "game/Table_80089904.h"
#include "game/Block_801BE60C.h"
#include "engine/Record_800D81C8.h"

extern "C" {
void fn_8009BD60(Object_80039F5C *p);
void fn_800A3B58(Object_80039F5C *p, int a, int b);
Object_80039F5C *fn_80137B40(void);
int fn_801CFFD0(int from, int to);
extern float lbl_802D7EA4[];
extern float lbl_802D7ED0[];
extern float lbl_803EAA04;
extern float lbl_803EAA08;
extern float lbl_803EAA0C;
}

extern "C" int fn_800A3E84(Object_80039F5C *p, int angle, int unused)
{
    float distance = 0.0f;
    int result = 0;

    Target_800A3E84 *pTarget = &p->mTarget;
    if (!(p->mFlags & 0x4000)) {
        Object_80039F5C *pOther = fn_8009BCE8(&pTarget->mRef);
        if (pOther)
            distance = fn_8022781C(&p->mMotion, &pOther->mMotion);
        if (pTarget->mMode == 2 && (p->mpState->mId == 30 || p->mpState->mId == 2))
            angle = 0x400000;
        int turn = fn_801CFFD0(p->mMotion.mFacing, angle);
        if (distance > 0.5f && (float)pTarget->mValue > lbl_802D7ED0[pTarget->mMode]
            && turn > 0x1C71C7) {
            fn_8009BD60(p);
            unsigned char style = 6;
            if (((p->mMotion.mFacing + turn) & 0xFFFFFF) == (angle & 0xFFFFFF))
                style = 3;
            unsigned char speed = 3;
            if (!((float)pTarget->mValue >= lbl_802D7EA4[pTarget->mMode]))
                speed = 1;
            p->mUnknown1008.mUnknown0 = style;
            p->mUnknown1008.mUnknown1 = speed;
            p->mUnknown1008.mUnknown2 = angle >> 17;
            if (fn_801CFFD0(p->mMotion.mFacing, (p->mUnknown1008.mUnknown2 << 17) & 0xFFFFFF) > 0x1C71C7) {
                p->mTarget.mUnknown10 = 1;
                if (distance > lbl_803EAA04 && distance < lbl_803EAA08
                    && turn < (int)(lbl_803EAA0C * 46603.38f)
                    && (pTarget->mMode == 4 || pTarget->mMode == 5))
                    fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 185, p, 1.0f);
                else if (pTarget->mMode == 2 && fn_80137B40() != 0
                         && fn_8022781C(&p->mMotion, &fn_80137B40()->mMotion) < 6.0f
                         && (p->mpState->mId == 2 || p->mpState->mId == 30))
                    fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 185, p, 1.0f);
                else
                    fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 155, p, 1.0f);
                result = 1;
                fn_800A3B58(p, 10, 0);
                p->mUnknown512.mUnknown14 = 0;
            } else {
                result = 0;
            }
        }
    }
    return result;
}

extern "C" {
void fn_80227690(void *pOut, void *pA, void *pB);
float fn_801CFB94(int angle);
int fn_801CFE40(float y, float x);
int fn_80110C10(Object_80039F5C *p);
signed char fn_8009C4B0(Table_80089904 *pTable, Key_80110630 *pKey);
extern float lbl_803EAA10;
}

extern "C" unsigned short fn_800A414C(Table_80089904 *table, Object_80039F5C *p, Block_801BE60C *block)
{
    Target_800A3E84 *pTarget = &p->mTarget;
    Object_80039F5C *pOther = fn_8009BCE8(&pTarget->mRef);
    if (pTarget->mMode == 2)
        p->mUnknown1008.mUnknown0 = 2;
    else
        p->mUnknown1008.mUnknown0 = 1;
    Pair_802270A4 delta;
    fn_80227690(&delta, &pOther->mMotion, &p->mMotion);
    int heading = fn_801CFE40(delta.mUnknown4, delta.mUnknown0) & 0xFFFFFF;
    int facing = p->mMotion.mUnknown32 & 0xFFFFFF;
    if (fn_801CFFD0(heading, facing) <= (int)(lbl_803EAA10 * 46603.38f)) {
        p->mUnknown1008.mUnknown1 = 1;
        switch (pTarget->mMode) {
        case 5:
            if (fn_801CFB94(fn_80110C10(pOther)) < 0.0f)
                p->mUnknown1008.mUnknown2 = 3;
            else
                p->mUnknown1008.mUnknown2 = 6;
            break;
        case 4:
            p->mUnknown1008.mUnknown2 = pOther->mUnknown1008.mUnknown1;
            break;
        }
    } else {
        p->mUnknown1008.mUnknown1 = ((facing - heading) & 0xFFFFFF) <= 0x7FFFFF ? 7 : 2;
    }
    p->mUnknown1011 = pTarget->mValue;
    return fn_8009C4B0(table, &p->mUnknown1008);
}
