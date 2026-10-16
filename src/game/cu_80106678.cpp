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
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
void fn_80106678(Record_8011F518 *pRecord, Object_80039F5C *p, int a, int b);
}

extern "C" void fn_80105168(int mode, Object_80137ABC *pBall, Object_80039F5C *p, Object_80039F5C *pOther, Vector_80039F5C *pTarget, int unused, float speed);

extern "C" float fn_80104C9C(Object_80039F5C *p, Object_80039F5C *pTarget);

extern float lbl_803EAEEC;

extern float lbl_803EAEF0;

extern "C" void fn_80227350(Vector_80039F5C *pOut, Vector_80039F5C *pV, float scale);

extern "C" void fn_80106678(Record_8011F518 *pRecord, Object_80039F5C *p, int a, int b) {
    fn_8009BD2C(p, &pRecord->mUnknown0);
    pRecord->mUnknown4 = b;
    pRecord->mUnknown5 = a;
    pRecord->mUnknown8 = 0.0f;
    pRecord->mUnknown12 = 0;
}

extern "C" int fn_801066D0(Object_80039F5C *p, Object_80039F5C *pTarget, int kind) {
    unsigned char filter[2] = {1, 0x11};
    int result = 1;

    if (kind == 9) {
        Object_80137ABC *pBall = fn_801374BC();
        Vector_80039F5C pos;
        Vector_80039F5C target;

        fn_80105168(6, pBall, p, pTarget, &target, 0, fn_80104C9C(p, pTarget));
        pos.mX = p->mMotion.mPos.mX;
        pos.mY = p->mMotion.mPos.mY;
        pos.mZ = p->mMotion.mPos.mZ;
        fn_80227350(&pos, (Vector_80039F5C *)&p->mMotion.mUnknown40, 40.0f);
        result = fn_801248D4(p, &pos, &target, 0, (Filter_801248D4 *)filter, pTarget, lbl_803EAEF0, lbl_803EAEEC);
    }
    return result;
}
