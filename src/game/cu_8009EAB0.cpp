#include "game/Item_80097440.h"
#include "game/Object_8017886C.h"
#include "game/fn_80177FE0.h"

extern "C" {
State_8011F4EC *fn_8011F4EC(void);
int fn_80178308(void);
void fn_8009F928(Object_80039F5C *p, Point_8017886C *pOut, unsigned int distance, int predict);
}

/* Rebuilds the play state's roster list from the flagged players (state id
   not 31 or 32) whose spot lies inside zone box index. For boxes 0-9 the
   box's mUnknown4 edge is first lowered to 3 below p's depth, then raised to
   at least 4 past fn_80177FE0's depth. Returns the new count. */
extern "C" unsigned char fn_8009EAB0(Object_80039F5C *p, unsigned int index)
{
    State_8011F4EC *pState = fn_8011F4EC();
    float depth = fn_80177FE0().mY;
    Box_8009E674 *pBox = &fn_8011F4EC()->mUnknown18[index];
    Box_8009E674 box;
    unsigned char i;
    int team;

    box.mUnknown0 = pBox->mUnknown0;
    box.mUnknown4 = pBox->mUnknown4;
    box.mUnknown8 = pBox->mUnknown8;
    box.mUnknownC = pBox->mUnknownC;
    if (index <= 9) {
        float edge = p->mMotion.mPos.mY - 3.0f;

        if (edge < box.mUnknown4) {
            box.mUnknown4 = edge;
        }
        box.mUnknown4 = box.mUnknown4 < depth + 4.0f ? depth + 4.0f : box.mUnknown4;
    }
    team = fn_80178308();
    pState->mUnknown1A3 = 0;
    pState->mUnknown1A4 = 0;
    for (i = 0; i < pState->mUnknown198; i++) {
        Object_80039F5C *pPlayer = fn_80039F5C(team, pState->mUnknown199[i]);

        if (pPlayer->mpState->mId != 31 && pPlayer->mpState->mId != 32 && pState->mUnknown19C[i] != 0) {
            Point_8017886C at;

            fn_8009F928(pPlayer, &at, 5, 1);
            if (at.mX > box.mUnknown8 && at.mX < box.mUnknownC && at.mY > box.mUnknown4 && at.mY < box.mUnknown0) {
                pState->mUnknown1A5[pState->mUnknown1A3] = pState->mUnknown199[i];
                pState->mUnknown1A3++;
            }
        }
    }
    return pState->mUnknown1A3;
}
