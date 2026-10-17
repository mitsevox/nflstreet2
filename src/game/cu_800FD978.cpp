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
Point_8017886C fn_80177FFC(int team);
}

extern float lbl_803EAE64;
extern "C" {
void fn_800FE03C(Object_80039F5C *p, Point_8017886C *pOut);
void fn_800FF598(State_800FDA58 *pState, Object_80039F5C *p, Point_8017886C *pPoint, int angle, float value);
unsigned char fn_800C0658(void);
void fn_800FF6D8(Object_80039F5C *p);
void fn_800449B4(Object_80039F5C *p);
void fn_80051B88(Object_800B26B0 *pMotion, float value);
}

extern "C" int fn_800FD7D0(Object_80039F5C *p);

extern "C" void fn_800FD978(Object_80039F5C *p)
{
    State_800FDA58 *pState = (State_800FDA58 *)&p->mUnknown336;
    Point_8017886C point;
    int angle;
    unsigned char state;
    float value;

    fn_80177FFC(p->mIdBytes[2]);
    fn_800FE03C(p, &point);
    angle = fn_800FD7D0(p);
    state = p->mUnknown2914;
    if (fn_800AD9B4() == 2 && state == 0 && p->mMotion.mPos.mY < point.mY - 2.0f) {
        value = lbl_803EAE64;
    } else {
        value = 0.0f;
    }
    fn_800FF598(pState, p, &point, angle, value);
    if (fn_800C0658() == 0) {
        fn_800FF6D8(p);
    }
    fn_800449B4(p);
    fn_80051B88(&p->mMotion, 1.25f);
}
