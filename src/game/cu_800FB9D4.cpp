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
int fn_80178320(void);
void fn_80227690(void *pOut, void *pA, void *pB);
unsigned int fn_80178D18(int team);
}

extern "C" Object_80039F5C *fn_800FB9D4(Object_80039F5C *p);

extern "C" Object_80039F5C *fn_800FB9D4(Object_80039F5C *p)
{
    Object_80039F5C *pResult = 0;
    float best = 1000.0f;

    if (p) {
        unsigned int count = fn_80178D18(fn_80178320());
        unsigned char i;

        for (i = 0; i < count; i++) {
            Object_80039F5C *pOther = fn_80039F5C(fn_80178320(), i);

            if (pOther->mpState->mId == 22) {
                Object_80039F5C *pTarget = fn_8009BCE8(&pOther->mUnknown336);

                if (pTarget && pTarget == p) {
                    Point_8017886C delta;
                    float distance;

                    fn_80227690(&delta, &p->mMotion.mPos, &pOther->mMotion.mPos);
                    distance = fn_802270A4(&delta);
                    if (distance < best) {
                        pResult = pOther;
                        best = distance;
                    }
                }
            }
        }
    }
    return pResult;
}
