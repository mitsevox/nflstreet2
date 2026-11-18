/* Commentary for a tackle into a wall: remembers the player involved (the line is spoken in the
   defence bank, so most likely the tackler) and has the commentator call it. */

#include "engine/spchevnt.h"

extern "C" {
void SpchIGGetPlayerCategory(int *pResult, int value);
int fn_80178320(void);
}

static int _SpchIG_iWallTacklePlayer = 0;

extern "C" void SpchIGSayWallTackle(void)
{
    int result;

    SpchIGGetPlayerCategory(&result, _SpchIG_iWallTacklePlayer);
    if (fn_80178320() == 0) {
        gSPCH_AddEvent(fn_801AE5D4(1, 0, 0x201C), 1, result);
    } else {
        gSPCH_AddEvent(fn_801AE5D4(2, 0, 0x401C), 1, result);
    }
}

extern "C" void SpchIGSetWallTacklePlayer(int value) { _SpchIG_iWallTacklePlayer = value; }
extern "C" int SpchIGGetWallTacklePlayer(void) { return _SpchIG_iWallTacklePlayer; }
