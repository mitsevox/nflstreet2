#include "game/Object_8007A334.h"

extern "C" {
int fn_8022F358(int index);
int fn_8022F3D4(int handle);

void fn_80087BE4(Object_8007A334 *pObject, int index)
{
    fn_8007A334(pObject, 0x54535055, 0x776E5355, 0, 0, fn_8022F3D4(fn_8022F358(index)));
}

void fn_80087C3C(Object_8007A334 *pObject)
{
    fn_8007A3C4(pObject);
}
}
