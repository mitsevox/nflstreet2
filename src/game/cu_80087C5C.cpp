#include "game/Object_8007A334.h"

extern "C" {
int fn_8007AA90(Object_8007A334 *pObject, int key, int value);
int fn_8007A934(Object_8007A334 *pObject, int key);
}

static int lbl_802D6BD8[15] = {
    0x776E5355, 0x6C6E5355, 0x73775355,
    0x74725355, 0x74705355, 0x54445455,
    0x69645355, 0x72665355, 0x73645355,
    0x46535355, 0x46505250, 0x54505455,
    0x42475355, 0x54424755, 0x43535355
};

extern "C" int fn_80087C5C(Object_8007A334 *pObject, unsigned int index, int value)
{
    return fn_8007AA90(pObject, lbl_802D6BD8[index], value);
}

extern "C" int fn_80087C8C(Object_8007A334 *pObject, unsigned int index)
{
    return fn_8007A934(pObject, lbl_802D6BD8[index]);
}
