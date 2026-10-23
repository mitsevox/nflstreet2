#include "game/Item_80097440.h"
#include "game/fn_80177FE0.h"

extern "C" State_8011F4EC *fn_8011F4EC(void);

/* Centre of zone box index of the play state; boxes 14-23 take their depth
   halfway between the box edge and the spot fn_80177FE0 returns. */
extern "C" void fn_8009E9EC(Object_80039F5C *p, int index, Point_8017886C *pOut)
{
    State_8011F4EC *pState = fn_8011F4EC();
    Box_8009E674 *pBox = &pState->mUnknown18[index];

    pOut->mX = (pBox->mUnknown8 + pBox->mUnknownC) * 0.5f;
    if (index >= 14 && index <= 23) {
        pOut->mY = (pBox->mUnknown0 - fn_80177FE0().mY) * 0.5f + fn_80177FE0().mY;
    } else {
        pOut->mY = (pBox->mUnknown0 + pBox->mUnknown4) * 0.5f;
    }
}
