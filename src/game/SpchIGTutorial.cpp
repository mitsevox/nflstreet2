/* Has the tutorial narrator introduce each drill, react when the drill is passed or failed, and
   speak when the player moves on to the next drill. */

#include "engine/spchevnt.h"

extern "C" {
int SpchIGGetTutorialDrillIndex(unsigned int a, int b);
}

static int _SpchIG_iTutorialDrill = -1;

extern "C" void SpchIGSayTutorialIntro(int a, int b)
{
    int value = SpchIGGetTutorialDrillIndex(a, b);

    _SpchIG_iTutorialDrill = value;
    lbl_803EBB10(fn_801AE5D4(3, 0, 0x6000), 2, value, 1);
}

extern "C" void SpchIGSayTutorialPassed(void)
{
    int value = _SpchIG_iTutorialDrill;

    lbl_803EBB10(fn_801AE5D4(3, 0, 0x6000), 2, value, 4);
}

extern "C" void SpchIGSayTutorialFailed(void)
{
    int value = _SpchIG_iTutorialDrill;

    lbl_803EBB10(fn_801AE5D4(3, 0, 0x6000), 2, value, 2);
}

extern "C" void SpchIGSayTutorialAdvance(void)
{
    int value = _SpchIG_iTutorialDrill;

    lbl_803EBB10(fn_801AE5D4(3, 0, 0x6000), 2, value, 8);
}
