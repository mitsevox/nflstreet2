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

extern "C" {
int fn_8011F1A4(void);
unsigned char fn_8011F4C8(void);
Object_80039F5C *fn_80124C28(Object_80039F5C *p, float *pOut, int angle, float length, float width, int facing);
void fn_8011E938(Object_80039F5C *p);
Object_80039F5C *fn_8003A130(Vector_80039F5C *pPos, float *pOut, int team);
}

extern "C" int fn_800F5AD4(Object_80039F5C *p) {
    Vector_80039F5C pos = p->mMotion.mPos;
    float distance;
    Object_80039F5C *pNear;
    Object_80039F5C *pOther;
    int flag;

    if (fn_8011F1A4() && (fn_8011F4C8() & 1)) {
        pos.mX -= 1.5f;
    } else {
        pos.mX += 1.5f;
    }
    pNear = fn_80124C28(p, &distance, 0x355555, 2.75f, 0.5f, p->mMotion.mFacing);
    flag = 0;
    if (fn_8011F1A4() && (fn_8011F4C8() & 1) && p->mMotion.mPos.mX > fn_80177FE0().mX) {
        flag = 1;
    } else if (fn_8011F1A4() && (fn_8011F4C8() & 1) == 0 && p->mMotion.mPos.mX < fn_80177FE0().mX) {
        flag = 1;
    }
    if (flag) {
        fn_8011E938(pNear);
        return 0;
    }
    pOther = fn_8003A130(&pos, &distance, p->mIdBytes[2]);
    if (!pOther || pOther == p || distance > 4.0f
        || fabsf(pOther->mMotion.mPos.mX - fn_80177FE0().mX) < fabsf(p->mMotion.mPos.mX - fn_80177FE0().mX)) {
        return 1;
    }
    if (pNear && pNear->mIdBytes[2] != p->mIdBytes[2]) {
        return 1;
    }
    return 0;
}
