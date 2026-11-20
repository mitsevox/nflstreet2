/* PATH track volume (pathvol.c): sets track volume, starts volume, effect-send and dry-level fades
   and applies them each tick. */

#include "engine/pathlib.h"

extern "C" void fn_801B4824(Node_801B3FE0 *p, int value)
{
    p->mUnknown3 = value;
    if (p->mUnknown1A & 0x80)
        p->mUnknown100->vfn_13((signed char)value * (signed char)p->mUnknown2 / 100);
}

extern "C" void fn_801B4960(Node_801B3FE0 *p, int a, int b, int c)
{
    p->mUnknown1C = lbl_803EBB3C;
    p->mUnknown20 = b;
    p->mUnknown25 = c;
    p->mUnknown24 = p->mUnknown100->fn_801B45B4(0);
    p->mUnknown26 = a;
}

extern "C" void fn_801B49C4(Node_801B3FE0 *p, int a, int b, int c)
{
    p->mUnknown28 = lbl_803EBB3C;
    p->mUnknown2C = b;
    p->mUnknown31 = c;
    p->mUnknown30 = p->mUnknown100->fn_801B45AC();
    p->mUnknown32 = a;
}
