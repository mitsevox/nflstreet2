/* Commentary for a pass that a player touched but did not catch away from the quarterback:
   remembers the player and has the commentator call it. */

#include "game/fn_80178D18.h"
#include "game/Object_80039F5C.h"
#include "engine/spchevnt.h"

extern "C" {
void SpchIGGetPlayerCategory(int *pResult, int value);
int fn_80178308(void);
int fn_80178320(void);
float fn_8022785C(Vector_80039F5C *pPosition, Vector_80039F5C *pOther);
}

static int _SpchIG_iMissedCatchPlayer = 0;

extern "C" void SpchIGSayMissedCatch(Vector_80039F5C *pOther)
{
    Vector_80039F5C position;
    unsigned short i;
    int a;
    unsigned int count;
    int result;

    position.mX = position.mY = position.mZ = 0.0f;
    a = fn_80178308();
    count = fn_80178D18(a);
    for (i = 0; i < count; i++) {
        Object_80039F5C *pObject = fn_80039F5C(a, i);
        if (pObject->mFlags & 0x10000000) {
            position.mX = pObject->mMotion.mPos.mX;
            position.mY = pObject->mMotion.mPos.mY;
            position.mZ = pObject->mMotion.mPos.mZ;
            break;
        }
    }
    if (fn_8022785C(&position, pOther) <= 4.0f) {
        return;
    }
    SpchIGGetPlayerCategory(&result, _SpchIG_iMissedCatchPlayer);
    if (fn_80178320() == 0) {
        lbl_803EBB10(fn_801AE5D4(1, 0, 0x2020), 1, result);
    } else {
        lbl_803EBB10(fn_801AE5D4(2, 0, 0x4020), 1, result);
    }
}

extern "C" void SpchIGSetMissedCatchPlayer(int value) { _SpchIG_iMissedCatchPlayer = value; }
extern "C" int SpchIGGetMissedCatchPlayer(void) { return _SpchIG_iMissedCatchPlayer; }
