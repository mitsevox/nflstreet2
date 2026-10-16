#include <math.h>
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/Message_800F01CC.h"
#include "game/State_803EB098.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_800F06F4.h"
#include "game/fn_8016871C.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80178D18.h"
#include "game/fn_801C1F94.h"
#include "game/fn_802270D4.h"
#include "game/fn_80227638.h"
#include "game/fn_8022781C.h"
#include "game/fn_802372EC.h"

/* View of the block whose address fn_8011F4EC returns. */
struct Block_800FAD2C {
    char mUnknown0[409];
    unsigned char mUnknown409[3];
};

extern "C" {
Record_8011F4E0 *fn_8011F4E0(void);
int fn_80178308(void);
void *fn_8011F4EC(void);
unsigned char fn_80164B78(void);
}

extern "C" void fn_800FAD2C(void) {
    Record_8011F4E0 *pRecord = fn_8011F4E0();
    unsigned char i = 0;
    int team;
    int mode;
    int swapped;

    pRecord->mUnknown0 = 1;
    pRecord->mUnknown2 = 150;
    team = fn_80178308();
    fn_8016871C(team);
    mode = fn_800AD9B4();
    for (; i <= 2; i++) {
        pRecord->mUnknown8[i] = ((Block_800FAD2C *)fn_8011F4EC())->mUnknown409[i];
        if (mode == 2 && fn_80039F5C(fn_80178308(), pRecord->mUnknown8[i])->mUnknown2914 == 0) {
            pRecord->mUnknown8[i] = fn_80164B78();
        }
    }
    do {
        swapped = 0;
        for (i = 0; i <= 1; i++) {
            float x0 = fn_80039F5C(team, pRecord->mUnknown8[i])->mMotion.mPos.mX;
            float x1 = fn_80039F5C(team, pRecord->mUnknown8[i + 1])->mMotion.mPos.mX;
            float y0 = fn_80039F5C(team, pRecord->mUnknown8[i])->mMotion.mPos.mY;
            float y1 = fn_80039F5C(team, pRecord->mUnknown8[i + 1])->mMotion.mPos.mY;

            if (x0 < x1 + 0.5f && (fabsf(x1 - x0) > 0.5f || y0 < y1)) {
                unsigned char slot = pRecord->mUnknown8[i];

                swapped = 1;
                pRecord->mUnknown8[i] = pRecord->mUnknown8[i + 1];
                pRecord->mUnknown8[i + 1] = slot;
            }
        }
    } while (swapped == 1);
    for (i = 0; i <= 2; i++) {
        pRecord->mUnknown12[i] = pRecord->mUnknown8[i];
    }
}
