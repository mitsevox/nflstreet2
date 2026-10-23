#include "game/fn_801248D4.h"
#include "game/Queue_800EFE0C.h"
#include "game/State_800FDA58.h"
#include <math.h>
#include <string.h>
#include "game/fn_800B65A0.h"
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
#include "game/Block_801BE60C.h"

extern "C" {
Object_80039F5C *fn_80124C28(Object_80039F5C *p, float *pOut, int angle, float a, float b, int facing);
int fn_801CFE40(float y, float x);
void fn_80227690(void *pOut, void *pA, void *pB);
}

extern "C" int fn_8010A0A0(Object_80039F5C *p, int index) {
    if (index != 0xFFFF) {
        float distance;
        Object_80039F5C *pOther = fn_80124C28(p, &distance, 0x2AAAAA, 3.0f, 1.0f, p->mMotion.mFacing);

        if (pOther != 0) {
            Point_8017886C delta;
            int angle;

            fn_80227690(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
            angle = fn_801CFE40(delta.mY, delta.mX);
            if (((angle - p->mMotion.mFacing) & 0xFFFFFF) > 0x800000) {
                p->mMotion.mFacing = (p->mMotion.mFacing + 0xB60B) & 0xFFFFFF;
                p->mpUnknown800[index].mUnknownC = (p->mpUnknown800[index].mUnknownC + 0xB60B) & 0xFFFFFF;
            } else {
                p->mMotion.mFacing = (p->mMotion.mFacing - 0xB60B) & 0xFFFFFF;
                p->mpUnknown800[index].mUnknownC = (p->mpUnknown800[index].mUnknownC - 0xB60B) & 0xFFFFFF;
            }
        }
        if (p->mFlags & 4) {
            p->mFlags &= ~4;
            return 1;
        }
    } else {
        return 1;
    }
    return 0;
}
