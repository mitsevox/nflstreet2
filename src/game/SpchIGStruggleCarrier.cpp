/* Commentary on the ball carrier when a tackle turns into a struggle: remembers the carrier and has
   the commentator call it. */

#include "engine/spchevnt.h"

extern "C" {
void SpchIGGetPlayerCategory(int *pResult, int value);
int fn_80178308(void);
}

static int _SpchIG_iStruggleCarrier = 0;

extern "C" void SpchIGSayStruggleCarrier(void)
{
    int result;

    SpchIGGetPlayerCategory(&result, _SpchIG_iStruggleCarrier);
    if (fn_80178308() == 0) {
        gSPCH_AddEvent(fn_801AE5D4(1, 0, 0x2021), 1, result);
    } else {
        gSPCH_AddEvent(fn_801AE5D4(2, 0, 0x4021), 1, result);
    }
}

extern "C" void SpchIGSetStruggleCarrier(int value) { _SpchIG_iStruggleCarrier = value; }
extern "C" int SpchIGGetStruggleCarrier(void) { return _SpchIG_iStruggleCarrier; }
