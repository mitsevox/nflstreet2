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
int fn_800E96EC(Object_80039F5C *p, Object_80039F5C *pOther);
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
extern float lbl_803ECB08;
void fn_800A5A8C(int a, Object_80039F5C *p, Object_80039F5C *pOther);
void fn_80148108(int mode);
int fn_801BE068(void *a, void *b, void *c, unsigned short d, void *pRecord, float e);
int fn_801BE068(void *a, void *b, void *c, unsigned short d, void *p, float e);
}

struct State_801021C0 {
    char mUnknown0[2];
    unsigned char mUnknown2;
    unsigned char mUnknown3;
    int mUnknown4;
    char mUnknown8[3];
    unsigned char mUnknown11;
};
extern "C" {
int fn_80103CB0(Object_80039F5C *p);
void fn_800D4D84(Object_80039F5C *p);
int fn_80104610(Object_80039F5C *p);
void fn_80176B8C(Object_80039F5C *p);
}

struct State_80102470 {
    char mUnknown0[2];
    unsigned char mUnknown2;
};

extern "C" int fn_800FFFB0(Object_80039F5C *p);
extern "C" int fn_80103CB0(Object_80039F5C *p);
extern "C" int fn_80104610(Object_80039F5C *p);
Record_8011F4F8 *fn_8011F4F8(int index);

extern "C" int fn_801021C0(Object_80039F5C *p)
{
    State_801021C0 *pState = (State_801021C0 *)&p->mUnknown336;

    if (fn_800FFFB0(p)) {
        Record_8011F4F8 *pRecord;
        unsigned char kind;

        if (fn_800AD9B4() != 3) {
            return 1;
        }
        pRecord = fn_8011F4F8(pState->mUnknown3);
        kind = pRecord->mUnknown1D;
        if (p->mFlags & 0x1000) {
            fn_80103CB0(p);
            pState->mUnknown4 = 0;
            p->mFlags &= ~0x1000;
            pRecord->mUnknownB = 0;
        }
        if ((p->mFlags & 0x2000) && kind == 4) {
            fn_800A5A8C(2, p, fn_80039F5C(p->mIdBytes[2], (unsigned char)pRecord->mUnknownA[0]));
            fn_800D4D84(p);
            if (p->mFlags & 0x4000) {
                fn_80148108(0);
            }
        }
        if (p->mFlags & 4) {
            if (fn_801BE648(p->mpUnknown792) == 235) {
                p->mFlags = (p->mFlags & ~4) | 8;
                p->mUnknown1008.mUnknown0 = pState->mUnknown11;
                p->mUnknown1008.mUnknown1 = 1;
                p->mUnknown1008.mUnknown2 = 1;
                p->mUnknown1011 = 6;
                fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 236, p, 1.0f);
            } else {
                if (kind == 4) {
                    p->mFlags &= ~0x2000;
                }
                p->mFlags &= ~4;
                p->mUnknown512.mUnknown14 = 1;
                p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
                p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
                p->mUnknown512.mUnknown0 = 0.0f;
                return 1;
            }
        }
    } else {
        Object_80039F5C *pOther;

        pState->mUnknown4++;
        pOther = fn_8009BCE8(&p->mUnknown560.mUnknown40);
        if (pOther && (pOther->mpState->mId == 12 || p->mUnknown560.mUnknown32 > lbl_803ECB08 * 50310.56f)) {
            switch (p->mUnknown560.mUnknown55) {
            case 0:
            case 5:
            case 7:
                if (pState->mUnknown4 > fn_80104610(p)) {
                    fn_80176B8C(pOther);
                }
                pState->mUnknown2 = 1;
                if (fn_800E96EC(p, pOther) == 1) {
                    Record_800B15FC *pEvent = fn_800B15FC();

                    fn_8009BD2C(pOther, &pEvent->mUnknown0);
                    pEvent->mUnknownC = p->mMotion.mPos.mX;
                    pEvent->mUnknown10 = p->mMotion.mPos.mY;
                    pEvent->mUnknown14 = 34;
                    fn_800B1508();
                } else {
                    pState->mUnknown2 = 0;
                }
                break;
            }
        }
        p->mFlags &= ~0x3000;
        if (p->mFlags & 4) {
            p->mFlags &= ~4;
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
            p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
            p->mUnknown512.mUnknown0 = 0.0f;
            return 1;
        }
    }
    return 0;
}

extern "C" int fn_80102470(Object_80039F5C *p)
{
    State_80102470 *pState = (State_80102470 *)&p->mUnknown336;
    unsigned int flags;

    if (pState->mUnknown2 != 0 || fn_800FFFB0(p) == 0) {
        flags = p->mFlags;
        p->mFlags = flags & ~0x2000;
        if (flags & 0x4000) {
            int facing = p->mMotion.mFacing;

            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown8 = facing;
            p->mUnknown512.mUnknown4 = facing;
            p->mUnknown512.mUnknown0 = 0.0f;
        }
        p->mFlags &= ~8;
        return 1;
    }
    return 0;
}
