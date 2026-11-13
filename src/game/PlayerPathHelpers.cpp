/* Helpers for players walking to field positions: a test that no player of
   a given team stands in the lane to the next point, a side-step animation
   chosen by which side of his team spot the player is on, and the release of
   the joint controllers a player was holding. */

#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/fn_80178D18.h"
#include <math.h>

struct PlayerJointCtrlFlags_t {
    char mUnknown0[50];
    unsigned char mUnknown50;
    unsigned char mUnknown51;
    unsigned short mUnknown52;
};

extern "C" {
void fn_8009CE88(Object_80039F5C *p, int *pRecord, int a);
int fn_80178320(void);
void fn_8009BD60(Object_80039F5C *p);
Point_8017886C fn_80177FFC(int team);
int fn_801BE068(void *, void *, void *, unsigned short, float, void *);
}

extern "C" int PlayerPathIsLaneClear(Object_80039F5C *p, Point_8017886C *pTarget)
{
    int team = fn_80178320();
    int i;
    int count = fn_80178D18(team);

    for (i = 0; i < count; i++) {
        Object_80039F5C *pOther = PlyrGet(team, i);
        if (pOther != p && fabsf(pOther->mMotion.mPos.mX - pTarget->mX) < 0.7f
            && p->mMotion.mPos.mY > pOther->mMotion.mPos.mY) {
            return 0;
        }
    }
    return 1;
}

extern "C" void PlayerPathStartSideAnim(Object_80039F5C *p, int a, int b)
{
    p->mFlags &= ~4;
    fn_8009BD60(p);
    p->mUnknown1008.mUnknown0 = a;
    p->mUnknown1008.mUnknown1 = b;
    if (p->mMotion.mPos.mX > fn_80177FFC(p->mIdBytes[2]).mX) {
        p->mUnknown1008.mUnknown1 = 2;
    } else {
        p->mUnknown1008.mUnknown1 = 3;
    }
    p->mFlags &= ~4;
    fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 189, 1.0f, p);
}

extern "C" void PlayerReleaseFlaggedJointCtrls(Object_80039F5C *p)
{
    PlayerJointCtrlFlags_t *pBlock = (PlayerJointCtrlFlags_t *)&p->mUnknown336;
    if (pBlock->mUnknown50 == 1 && (p->mFlags & 0x80)) {
        p->mFlags &= ~0x80;
        fn_8009CE88(p, &p->mUnknown16, 10);
        pBlock->mUnknown50 = 0;
        if (pBlock->mUnknown51 == 1) {
            if (pBlock->mUnknown52 == 0) {
                fn_8009CE88(p, &p->mUnknown108, 20);
            } else {
                fn_8009CE88(p, &p->mUnknown200, 20);
            }
            pBlock->mUnknown51 = 0;
        }
    }
}

extern "C" void PlayerReleaseJointCtrls(Object_80039F5C *p)
{
    PlayerJointCtrlFlags_t *pBlock = (PlayerJointCtrlFlags_t *)&p->mUnknown336;
    if (pBlock->mUnknown50 == 1) {
        fn_8009CE88(p, &p->mUnknown16, 10);
        pBlock->mUnknown50 = 0;
    }
    if (pBlock->mUnknown51 == 1) {
        if (pBlock->mUnknown52 == 0) {
            fn_8009CE88(p, &p->mUnknown108, 20);
        } else {
            fn_8009CE88(p, &p->mUnknown200, 20);
        }
        pBlock->mUnknown51 = 0;
    }
}
