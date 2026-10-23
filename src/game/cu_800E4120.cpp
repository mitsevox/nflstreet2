#include "engine/cu_801B9F00.h"
#include "game/Object_80039F5C.h"
#include "game/Object_800D81C8.h"
#include "game/Object_8017886C.h"

/* Player block at +336 as fn_800E4120 sets it. */
struct State_800E4120 {
    char mUnknown0[3];
    unsigned char mUnknown3;
    char mUnknown4[20];
    unsigned char mUnknown24;
};

extern "C" {
void fn_8009BD60(Object_80039F5C *p);
Point_8017886C fn_80177FFC(int team);
int fn_801BE068(void *a, void *b, void *c, unsigned short d, float f, void *e);
}

extern "C" void fn_800E4120(Object_80039F5C *p, State_800E4120 *pState, int heading, float speed)
{
    p->mpUnknown796->mUnknown8 = p->mMotion.mFacing = 0xC00000;
    fn_8009BD60(p);
    if (((heading - p->mMotion.mFacing) & 0xFFFFFF) > 0x800000) {
        p->mUnknown1008.mUnknown0 = 6;
    } else {
        p->mUnknown1008.mUnknown0 = 3;
    }
    if (p->mMotion.mPos.mX > fn_80177FFC(p->mIdBytes[2]).mX) {
        p->mUnknown1008.mUnknown1 = 5;
    } else {
        p->mUnknown1008.mUnknown1 = 6;
    }
    p->mFlags &= ~4;
    fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 28, 1.0f, p);
    if (fn_801BA568(p->mpUnknown796, p->mpUnknown800, 28)) {
        int index = fn_801BA5A8(p->mpUnknown796, p->mpUnknown800, 28, 0);
        float rate = speed * 1.025641f;
        if (rate > 1.4f) {
            rate = 1.4f;
        }
        p->mpUnknown800[index].mUnknown2C = rate;
        p->mUnknown512.mUnknown14 = 0;
        pState->mUnknown3 = 1;
        pState->mUnknown24 = 0;
    }
}
