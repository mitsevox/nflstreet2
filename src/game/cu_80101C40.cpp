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
#include "engine/cu_801B9F00.h"

extern "C" {
int fn_800FFFB0(Object_80039F5C *p);
int fn_800CA5CC(Object_80039F5C *p, int kind, int apply);
void fn_800A3B58(Object_80039F5C *p, int a, int b);
void fn_800A2190(int bit);
void fn_8009BD60(Object_80039F5C *p);
int fn_800D0B90(Object_80039F5C *p);
int fn_80101B7C(Object_80039F5C *p);
int fn_801CFFD0(int a, int b);
float fn_801CFFA0(float value);
void fn_801BD81C(void *p, float value);
void fn_80156C78(int index, int value);
void fn_80100AA0(Object_80039F5C *p, int, float *a, float *b);
}

extern float lbl_803EA2C4;
extern float lbl_803EC9E8;
extern float lbl_803EAEC0;

extern "C" int fn_80101C40(Object_80039F5C *p)
{
    int flag = p->mUnknown776 == 1;

    if ((p->mMotion.mPos.mX >= 0.0f && p->mMotion.mFacing <= 0x800000)
        || (p->mMotion.mPos.mX < 0.0f && p->mMotion.mFacing > 0x800000)) {
        return flag ? 1 : 3;
    }
    return flag ? 3 : 1;
}

extern "C" int fn_80101CB4(Object_80039F5C *p)
{
    Object_80039F5C *pOther = 0;
    State_800FDA58 *pState;
    Record_8011F4F8 *pRequest;
    Record_800D81C8 *pChannels;
    unsigned char hasBall;
    int kind;
    unsigned char mode;
    int anim;

    if (fn_800AD9B4() != 3 || fn_800FFFB0(p) == 0) {
        return 1;
    }
    pState = (State_800FDA58 *)&p->mUnknown336;
    pState->mUnknown3Byte = fn_801374E0(fn_80137C48(p));
    pRequest = fn_8011F4F8(pState->mUnknown3Byte);
    p->mFlags &= ~0x1000;
    p->mFlags &= ~4;
    pRequest->mUnknown8 = p->mpState->mUnknown3[0];
    if (pRequest->mUnknown8 == 0) {
        pState->mUnknown0Bytes[0] = 1;
    } else {
        pState->mUnknown0Bytes[0] = 0;
    }
    pState->mUnknown2 = pState->mUnknown0Bytes[1] = 0;
    pState->mUnknown4 = 0;
    pRequest->mUnknownB = 1;
    pRequest->mUnknownAByte = p->mpState->mUnknown2;
    pRequest->mUnknown1D = p->mpState->mUnknown1;
    pRequest->mUnknownC = 0.0f;
    pRequest->mUnknown10 = 0;
    if (pRequest->mUnknownAByte != 15) {
        pOther = fn_80039F5C(p->mIdBytes[2], pRequest->mUnknownAByte);
        pRequest->mUnknown14 = pOther->mMotion.mUnknown40;
        pRequest->mUnknown18 = pOther->mMotion.mUnknown44;
        pRequest->mUnknown1C[0] = pOther->mpState->mId == 20;
        if (pOther->mpState->mId == 51) {
            pOther->mFlags |= 0x80000000;
        }
    } else {
        pRequest->mUnknown14 = pRequest->mUnknown18 = 0.0f;
        pRequest->mUnknown1C[0] = 0;
    }
    kind = fn_800D0B90(p);
    hasBall = kind;
    fn_8009BD60(p);
    p->mFlags &= ~4;
    if (p->mpState->mUnknown1 != 2 && p->mpState->mUnknown1 != 5) {
        if (fn_801BE648(p->mpUnknown792) == 0xDE && fn_800D0B90(p) == 0) {
            mode = 8;
        } else if (p->mMotion.mUnknown28 > lbl_803EC9E8) {
            switch (fn_801BE648(p->mpUnknown792)) {
            case 0x54:
                if (fn_801CFFD0(p->mMotion.mFacing, p->mMotion.mUnknown32) <= 0x3FFFFF
                    && p->mMotion.mUnknown32 > 0x238E39 && p->mMotion.mUnknown32 <= 0x58E38D) {
                    mode = 2;
                } else {
                    mode = 3;
                }
                break;
            case 0x4A:
            default:
                if (p->mMotion.mUnknown28 > 40.0f / (210.0f / lbl_803EA2C4) * 0.25f) {
                    if (fn_800CA5CC(p, 5, 1) != 0) {
                        mode = 5;
                    } else if (p->mUnknown2913 == 1
                               && fn_801CFFD0(p->mMotion.mUnknown32, 0) <= 0x2AAAA9) {
                        mode = 5;
                    } else if (p->mUnknown2913 == 0
                               && fn_801CFFD0(p->mMotion.mUnknown32, 0x800000) <= 0x2AAAA9) {
                        mode = 5;
                    } else {
                        mode = 2;
                    }
                } else {
                    mode = 2;
                }
                break;
            }
        } else {
            mode = 2;
        }
    } else {
        mode = 1;
    }
    p->mUnknown1008.mUnknown0 = mode;
    if (hasBall) {
        if (kind == 4) {
            if (fn_80101B7C(p) != 0) {
                anim = fn_801BA5A8(p->mpUnknown796, p->mpUnknown800, 0xEB, 0);
                p->mFlags |= 8;
                fn_80067E3C(0x32, &p->mMotion.mPos, p->mId, 0, 0, 0);
                fn_800A2190(0);
            } else {
                fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 0xB2, 1.0f, p);
                anim = fn_801BA5A8(p->mpUnknown796, p->mpUnknown800, 0xB2, 0);
                fn_80156C78(0x19, 1);
            }
        } else {
            fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 0xB2, 1.0f, p);
            anim = fn_801BA5A8(p->mpUnknown796, p->mpUnknown800, 0xB2, 0);
            fn_80156C78(0x19, 1);
        }
        if (anim == 0xFFFF) {
            anim = fn_801BA5A8(p->mpUnknown796, p->mpUnknown800, 0x45, 0);
        }
    } else {
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 0x45, 1.0f, p);
        anim = fn_801BA5A8(p->mpUnknown796, p->mpUnknown800, 0x45, 0);
    }
    pChannels = p->mpUnknown800;
    if (pRequest->mUnknown1D != 4 && fn_801BE648(p->mpUnknown792) != 0xEB) {
        fn_801BD81C(&pChannels[anim].mUnknown4C, fn_801CFFA0(lbl_803EAEC0));
    }
    if (pRequest->mUnknownAByte != 15) {
        switch (p->mpState->mUnknown1) {
        case 0:
        case 1:
        case 6:
        case 7:
            fn_80100AA0(p, (int)&pOther->mMotion.mPos, &pRequest->mUnknown0, &pRequest->mUnknown4);
            break;
        }
    } else {
        pRequest->mUnknown0 = pRequest->mUnknown4 = 1.0f;
    }
    fn_800A3B58(p, 3, 0);
    return 0;
}
