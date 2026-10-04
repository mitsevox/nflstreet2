#include "game/Object_8007A334.h"

extern "C" {

static int lbl_802D69E0[4] = { 0x31544753, 0x32544753, 0x33544753, 0x34544753 };

int fn_80080F20(void *pObject)
{
    return fn_8007A98C(pObject, 0x4E535050);
}

int fn_80080F48(void *pObject, int index)
{
    return fn_8007A98C(pObject, lbl_802D69E0[index]);
}

int fn_80080F78(void *pObject, int value)
{
    return fn_8007ABA4(pObject, 0x4E535050, value);
}

int fn_80080FA4(void *pObject, int index, int value)
{
    return fn_8007ABA4(pObject, lbl_802D69E0[index], value);
}
}
