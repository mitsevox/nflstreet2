#include "engine/cu_801B9F00.h"
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

/* View of the block at player +336 that fn_8010AFB8 reads: a request word
   and two flag bytes. */
struct Block_8010AFB8 {
    int mUnknown0;
    short mUnknown4;
    unsigned char mUnknown6;
    unsigned char mUnknown7;
};

extern "C" {
int fn_800B0F98(void);
int fn_8010A2DC(Object_80039F5C *p, int a, short b);
void fn_8010AECC(Object_80039F5C *p, unsigned char a, unsigned char b, unsigned char c);
void fn_8010B1FC(Object_80039F5C *p, int a, short b);
int fn_801486A0(void);
int fn_8016E928(void);
Point_8017886C fn_80177FFC(int team);
int fn_801BE068(void *a, void *b, void *c, unsigned short d, void *pRecord, float e);
float fn_80237260(int stream);
}

extern "C" int fn_8010AFB8(Object_80039F5C *p) {
    Block_8010AFB8 *pBlock = (Block_8010AFB8 *)&p->mUnknown336;
    int team;

    fn_8010A2DC(p, 0, 5);
    if (!(p->mFlags & 0x40000) && fn_801BE648(p->mpUnknown792) != 0x5B) {
        if (p->mFlags & 4) {
            p->mFlags |= 0x40000;
            p->mFlags &= ~4;
            fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 0x5B, p, 1.0f);
            if (pBlock->mUnknown6 != 0) {
                pBlock->mUnknown6 = 0;
                if (p->mpState[1].mId != 0) {
                    return 1;
                }
            }
        }
    } else {
        if (fn_800B65A0(p->mIdBytes[2]) == 0xFF && pBlock->mUnknown7 == 0 && fn_8016E928() && fn_801486A0() != 2) {
            if (fn_80237260(0) < 0.5f) {
                fn_8010B1FC(p, 2, 0);
            }
            pBlock->mUnknown7 = 1;
        }
        team = p->mIdBytes[2];
        switch (pBlock->mUnknown0) {
        case -1:
            break;
        case 1:
            if (fn_80177FFC(team).mY - p->mMotion.mPos.mY < 3.0f) {
                int id = fn_800B0F98();
                Object_80039F5C *pOther = fn_8009BCE8(&id);

                if (pOther != 0) {
                    fn_8010AECC(p, 6, p->mMotion.mPos.mX > pOther->mMotion.mPos.mX ? 3 : 6, 0xFF);
                }
            }
            break;
        case 2:
            if (fn_80177FFC(team).mY - p->mMotion.mPos.mY < 3.0f) {
                fn_8010AECC(p, 7, 0xFF, 0xFF);
            }
            break;
        }
        pBlock->mUnknown0 = -1;
    }
    return 0;
}
