/* Commentary for a receiver who has got open: remembers the receiver and has the commentator call
   it. */

#include "engine/spchevnt.h"

extern "C" {
void SpchIGGetPlayerCategory(int *pResult, int value);
int fn_80178308(void);
}

static int _SpchIG_iReceiverOpenPlayer = 0;

extern "C" void SpchIGSayReceiverOpen(void)
{
    int result;

    SpchIGGetPlayerCategory(&result, _SpchIG_iReceiverOpenPlayer);
    if (fn_80178308() == 0) {
        lbl_803EBB10(fn_801AE5D4(1, 0, 0x2004), 1, result);
    } else {
        lbl_803EBB10(fn_801AE5D4(2, 0, 0x4004), 1, result);
    }
}

extern "C" void SpchIGSetReceiverOpenPlayer(int value) { _SpchIG_iReceiverOpenPlayer = value; }
extern "C" int SpchIGGetReceiverOpenPlayer(void) { return _SpchIG_iReceiverOpenPlayer; }
