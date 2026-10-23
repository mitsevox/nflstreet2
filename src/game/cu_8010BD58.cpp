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

extern "C" {
int fn_800A2178(void);
int fn_8010B224(Object_80039F5C *p);
int fn_801485D4(void);
int fn_80156704(void);
unsigned char fn_80156D14(void);
void fn_80227690(void *pOut, void *pA, void *pB);
float fn_80237260(int stream);
extern float lbl_802DAB74[];
}

extern "C" int fn_8010BD58(Object_80039F5C *p) {
    int result = 0;

    if (fn_8010B224(p)) {
        Vector_80039F5C toBall;
        float dist;
        float chance;
        float limit;
        int index;

        fn_80137D58(fn_801374BC(), &toBall);
        fn_80227690(&toBall, &toBall, &p->mMotion.mPos);
        dist = fn_802270A4(&toBall);
        chance = 1.2f;
        chance -= dist * 0.15f;
        index = fn_800A2178();
        limit = lbl_802DAB74[index];
        if (fn_80156704() && !fn_801485D4()) {
            if (fn_80156D14()) {
                limit = 1.0f;
            } else {
                limit = 0.75f;
            }
        }
        if (chance < limit) {
            chance = limit;
        }
        if (fn_80237260(0) < chance) {
            result = 1;
        }
    }
    return result;
}
