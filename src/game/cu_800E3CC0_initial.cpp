#include "game/State_800E4494.h"
#include "game/Object_80039F5C.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800670B4.h"
#include "game/fn_80163E94.h"
#include "game/fn_80227638.h"
#include "game/fn_8022781C.h"

extern "C" {
Point_8017886C fn_80177FFC(int team);
Object_800670B4 *fn_80168708(int team);
int fn_80178308(void);
void fn_800E2550(Object_80039F5C *p, Point_8017886C *pOut, int *pAngle);

void fn_800E3CC0(Object_80039F5C *p)
{
    State_800E4494 *state = (State_800E4494 *)&p->mUnknown336;
    Object_80039F5C *pOther = state->mpUnknown36;
    Point_8017886C origin = fn_80177FFC(p->mIdBytes[2]);
    if (pOther->mpState->mId == 7) {
        Object_800670B4 *pTeam = fn_80168708(fn_80178308());
        Entry_8006719C *pEntry = fn_80163E94(pTeam, pOther->mIdBytes[1], 0);
        Point_8017886C point;
        point.mX = pTeam->mUnknown8.mUnknownF == 1 ? pEntry->mUnknown18.mX : pEntry->mUnknown10.mX;
        point.mY = pTeam->mUnknown8.mUnknownF == 1 ? pEntry->mUnknown18.mY : pEntry->mUnknown10.mY;
        fn_80227638(&point, &point, &origin);
    }
    Point_8017886C target;
    int angle;
    fn_800E2550(p, &target, &angle);
    if (!(fn_8022781C(&target, &p->mMotion.mPos) <= 2.0f)) {
        state->mUnknown1 = 1;
        p->mFlags |= 0x10;
    }
}

}
