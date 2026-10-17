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

/* Input of fn_801076F0 and fn_80108074. Partial layout. */
struct Input_801076F0 {
    char mUnknown0[4];
    Point_8017886C mUnknown4;
    char mUnknown12[4];
    Point_8017886C mUnknown16;
    char mUnknown24[16];
    Point_8017886C mUnknown40;
};

extern "C" {

}

extern "C" void fn_801079BC(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pA, Point_8017886C *pB,
                            Input_801076F0 *pIn) {
    float x;
    float dx;

    x = pIn->mUnknown4.mX;
    pA->mX = x;
    pA->mY = pIn->mUnknown4.mY;
    pB->mX = x;
    pB->mY = pA->mY;
    dx = pIn->mUnknown4.mX - p->mMotion.mPos.mX;
    if (dx > 0.0f) {
        dx *= 0.33333334f;
        if (dx > 2.0f) {
            dx = 2.0f;
        }
    } else {
        dx *= 0.33333334f;
        if (dx < -2.0f) {
            dx = -2.0f;
        }
    }
    pB->mX = x - dx;
    if (pOther != 0) {
        float y = pOther->mMotion.mPos.mY + 4.0f;
        float low = pIn->mUnknown4.mY - 1.0f;

        if (y < low) {
            y = low;
        } else {
            float high = pIn->mUnknown4.mY + 2.0f;

            if (y > high) {
                y = high;
            }
        }
        pB->mY = y;
    }
}
