#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"

struct Pair_8011BAE0 {
    float mUnknown0;
    float mUnknown4;
};

extern "C" {

void fn_8009BD2C(Object_80039F5C *p, int *pRef);
int fn_80118B4C(Object_80039F5C *p, Pair_8011BAE0 *pPair);
int fn_80178D70(int team);
void fn_80227538(Point_8017886C *pOut, int angle, float length);
void fn_80227638(void *pOut, void *pA, void *pB);

int fn_8011EAC0(Object_80039F5C *p, Object_80039F5C *pOther)
{
    Block_8011E240 *pBlock = &p->mBlock1032;
    Block_8011E240 *pOtherBlock = &pOther->mBlock1032;
    Block_8011E240 saved;
    Block_8011E240 otherSaved;
    Point_8017886C point;
    unsigned char team;
    unsigned char i;

    saved.mUnknown0 = pBlock->mUnknown0;
    saved.mUnknown4 = pBlock->mUnknown4;
    otherSaved.mUnknown0 = pOtherBlock->mUnknown0;
    otherSaved.mUnknown4 = pOtherBlock->mUnknown4;
    p->mUnknown1032 = 2;
    fn_8009BD2C(pOther, &p->mUnknown1036);
    pOther->mUnknown1032 = 8;
    fn_8009BD2C(p, &pOther->mUnknown1036);
    fn_80227538(&point, (p->mMotion.mFacing + 0x800000) & 0xFFFFFF, 2.0f);
    fn_80227638(&point, &point, &p->mMotion.mPos);
    if (fn_80118B4C(p, (Pair_8011BAE0 *)&point)) {
        for (team = 0; team <= 1; team++) {
            unsigned int count = fn_80178D70(team);

            for (i = 0; i < count; i++) {
                Object_80039F5C *pPlayer = fn_80039F5C(team, i);

                if (pPlayer != p && pOther != pPlayer) {
                    Block_8011E240 *pPlayerBlock = &pPlayer->mBlock1032;
                    Object_80039F5C *pRef;

                    if (pPlayer->mUnknown1032 == 2) {
                        pRef = fn_8009BCE8(&pPlayer->mUnknown1036);
                        if (pRef == p || pRef == pOther) {
                            pPlayer->mUnknown1032 = 1;
                            pPlayerBlock->mUnknown4 = 0;
                        }
                    } else if (pPlayer->mUnknown1032 == 8) {
                        pRef = fn_8009BCE8(&pPlayer->mUnknown1036);
                        if (pRef == p || pRef == pOther) {
                            pPlayer->mUnknown1032 = 0;
                            pPlayerBlock->mUnknown4 = 0;
                        }
                    }
                }
            }
        }
        return 1;
    }
    p->mUnknown1032 = saved.mUnknown0;
    pBlock->mUnknown4 = saved.mUnknown4;
    pOther->mUnknown1032 = otherSaved.mUnknown0;
    pOtherBlock->mUnknown4 = otherSaved.mUnknown4;
    return 0;
}

}
