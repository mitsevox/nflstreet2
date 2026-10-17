#include "game/fn_801248D4.h"
#include "game/Queue_800EFE0C.h"
#include "game/State_800FDA58.h"
#include <math.h>
#include <string.h>
#include "game/fn_800B65A0.h"
#include "game/Class_80297CE8.h"
#include "game/Command_800CEE74.h"
#include "game/Input_800B6D34.h"
#include "game/Lookup_8012078C.h"
#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/Plan_80121264.h"
#include "game/Record_800B15FC.h"
#include "game/Record_8011F518.h"
#include "game/Team_80167A8C.h"
#include "game/State_803EB098.h"
#include "game/cu_80067C10.h"
#include "game/Query_800CE770.h"
#include "game/Table_80089904.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800670B4.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_800F06F4.h"
#include "game/fn_80163E94.h"
#include "game/fn_8016871C.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80178D18.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_802270D4.h"
#include "game/fn_80227638.h"
#include "game/fn_8022781C.h"
#include "game/fn_802372EC.h"
#include "game/fn_80238174.h"
#include "game/Record_800DB60C.h"
#include "game/fn_801BE60C.h"

extern "C" {
int fn_80178308(void);
int fn_80178320(void);
int fn_801CFE40(float y, float x);
void fn_80227690(void *pOut, void *pA, void *pB);
int fn_801783AC(int bit);
extern float lbl_803ECB08;
void fn_800FD978(Object_80039F5C *p);
Point_8017886C fn_80177FFC(int team);
}

struct State_800FDAC8 {
    short mUnknown0;
    char mUnknown2[6];
    Point_8017886C mUnknown8;
    char mUnknown16[32];
    int mUnknown48;
    unsigned char mUnknown52;
    unsigned char mUnknown53;
};
extern "C" {
int fn_800CB708(Object_80039F5C *p, int *pOut, Point_8017886C target, int angle, int flag);
int fn_800CB580(Object_80039F5C *p, int *pOut, Point_8017886C target, int angle, int flag);
void fn_800CBB00(Object_80039F5C *p, int value, Point_8017886C target, int angle, int flag);
int fn_800FF094(Object_80039F5C *p);
int fn_80177F70(void);
}

extern "C" int fn_800F06F4(int a, void *pRecord, int id, int value);
extern "C" void fn_800FD978(Object_80039F5C *p);

extern "C" int fn_800FDAC8(Object_80039F5C *p)
{
    unsigned char state = p->mUnknown2914;
    Point_8017886C target = {0.0f, 0.0f};
    State_800FDAC8 *pState = (State_800FDAC8 *)&p->mUnknown336;
    Point_8017886C base;
    int angle = 0;
    int result;

    base = fn_80177FFC(p->mIdBytes[2]);
    switch (pState->mUnknown48) {
    case 0:
        break;
    case 1:
        p->mFlags &= ~0x40000;
        if (p->mFlags & 4) {
            fn_800FD978(p);
            pState->mUnknown0 = 0;
            pState->mUnknown48 = 2;
        }
        break;
    case 2: {
        Point_8017886C *pBase;
        int index;
        float distance;
        int flag;

        target = pState->mUnknown8;
        index = fn_800F06F4(0, p->mpState, 6, 0xFFFF);
        distance = fn_8022781C(&target, &p->mMotion.mPos);
        if (index == 0xFFFF) {
            index = fn_800F06F4(0, p->mpState, 87, 0xFFFF);
            if (index != 0xFFFF) {
                angle = p->mpState[index].mUnknown2 << 16;
            } else {
                angle = 0x400000;
                if (p->mIdBytes[2] == fn_80178320()) {
                    angle = 0xC00000;
                }
            }
        } else {
            angle = p->mpState[index].mUnknown1 << 16;
        }
        pBase = &base;
        p->mFlags &= ~0x40000;
        if ((p->mIdBytes[2] == fn_80178320() && target.mY > pBase->mY + 2.0f)
            || ((state == 19 || state == 23) && fn_80177F70() == 0) || state == 20) {
            flag = 1;
        } else {
            flag = 0;
        }
        if (distance < 3.5f && fn_800CB708(p, &result, target, angle, flag)) {
            pState->mUnknown48 = 4;
            fn_800CBB00(p, result, target, angle, flag);
            break;
        }
        if (pState->mUnknown53 == 0 && lbl_803EABA4->fn_800C0414() == 3 && p->mIdBytes[2] == fn_80178308()) {
            pState->mUnknown53 = 1;
            pState->mUnknown0 = pState->mUnknown0 / 2;
        }
        if (pState->mUnknown52 == 0 && pState->mUnknown0 - 1 <= 0) {
            Point_8017886C delta;
            int run = 1;

            fn_80227690(&delta, &target, &p->mMotion.mPos);
            angle = fn_801CFE40(delta.mY, delta.mX);
            if (pBase->mY > p->mMotion.mPos.mY && pBase->mY - p->mMotion.mPos.mY < 1.5f
                && fabsf(p->mMotion.mPos.mX - pBase->mX) < 7.0f
                && ((p->mMotion.mPos.mX > pBase->mX && target.mX < p->mMotion.mPos.mX)
                    || (p->mMotion.mPos.mX < pBase->mX && target.mX > p->mMotion.mPos.mX))) {
                run = 0;
            }
            if (run && fn_800CB580(p, &result, target, angle, 0)) {
                fn_800CBB00(p, result, target, angle, 1);
                pState->mUnknown48 = 5;
            }
            pState->mUnknown52 = 1;
        }
        if (pState->mUnknown48 == 2) {
            if (p->mUnknown545 == 0 || fn_801783AC(21) == 0) {
                if (fn_800FF094(p) == 1) {
                    p->mFlags &= ~0x10;
                    p->mUnknown512.mUnknown14 = 1;
                    p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
                    p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
                    p->mUnknown512.mUnknown0 = 0.0f;
                    return 1;
                }
            } else {
                p->mUnknown512.mUnknown14 = 1;
                p->mUnknown512.mUnknown8 = p->mMotion.mUnknown32;
                p->mUnknown512.mUnknown4 = p->mMotion.mUnknown32;
                p->mUnknown512.mUnknown0 = p->mMotion.mUnknown28 / lbl_803ECB08;
            }
        }
        break;
    }
    case 5:
        if (p->mFlags & 4) {
            p->mFlags &= ~4;
            pState->mUnknown48 = 2;
        }
        break;
    case 3:
        if (p->mFlags & 4) {
            p->mFlags &= ~4;
            p->mFlags &= ~0x10;
            return 1;
        }
        p->mFlags &= ~0x40000;
        break;
    case 4:
        if (p->mFlags & 4) {
            p->mFlags &= ~4;
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
            p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
            p->mUnknown512.mUnknown0 = 0.0f;
            return 1;
        }
        p->mFlags &= ~0x40000;
        break;
    }
    return 0;
}
