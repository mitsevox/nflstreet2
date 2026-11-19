/* Commentary on the tackler when a tackle turns into a struggle: remembers the tackler and has the
   commentator call it. */

#include "engine/spchevnt.h"

extern "C" {
void SpchIGGetPlayerCategory(int *pResult, int value);
int fn_80178320(void);
}

static int _SpchIG_iStruggleTackler = 0;

extern "C" void SpchIGSayStruggleTackler(void)
{
    int result;

    SpchIGGetPlayerCategory(&result, _SpchIG_iStruggleTackler);
    if (fn_80178320() == 0) {
        gSPCH_AddEvent(SPCH_MakeEventSpec(1, 0, 0x2022), 1, result);
    } else {
        gSPCH_AddEvent(SPCH_MakeEventSpec(2, 0, 0x4022), 1, result);
    }
}

extern "C" void SpchIGSetStruggleTackler(int value) { _SpchIG_iStruggleTackler = value; }
extern "C" int SpchIGGetStruggleTackler(void) { return _SpchIG_iStruggleTackler; }
