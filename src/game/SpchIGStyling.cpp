/* Commentary for a ball carrier who starts styling (showboating): remembers the player and has the
   commentator call it. */

#include "engine/spchevnt.h"

extern "C" {
void SpchIGGetPlayerCategory(int *pResult, int value);
int fn_80178308(void);
}

static int _SpchIG_iStylingPlayer = 0;

extern "C" void SpchIGSayStyling(void)
{
    int result;

    SpchIGGetPlayerCategory(&result, _SpchIG_iStylingPlayer);
    if (fn_80178308() == 0) {
        gSPCH_AddEvent(fn_801AE5D4(1, 0, 0x201D), 1, result);
    } else {
        gSPCH_AddEvent(fn_801AE5D4(2, 0, 0x401D), 1, result);
    }
}

extern "C" void SpchIGSetStylingPlayer(int value) { _SpchIG_iStylingPlayer = value; }
extern "C" int SpchIGGetStylingPlayer(void) { return _SpchIG_iStylingPlayer; }
