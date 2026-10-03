#include "game/Object_8007A334.h"

extern "C" {
int fn_8007A98C(Object_8007A334 *pObject, int a);
void fn_8007ABA4(Object_8007A334 *pObject, int a, int b);

static int lbl_802D69E0[4] = { 0x31544753, 0x32544753, 0x33544753, 0x34544753 };

int fn_80080F20(Object_8007A334 *pObject)
{
    return fn_8007A98C(pObject, 0x4E535050);
}

int fn_80080F48(Object_8007A334 *pObject, int index)
{
    return fn_8007A98C(pObject, lbl_802D69E0[index]);
}

void fn_80080F78(Object_8007A334 *pObject, int value)
{
    fn_8007ABA4(pObject, 0x4E535050, value);
}

void fn_80080FA4(Object_8007A334 *pObject, int index, int value)
{
    fn_8007ABA4(pObject, lbl_802D69E0[index], value);
}
}
