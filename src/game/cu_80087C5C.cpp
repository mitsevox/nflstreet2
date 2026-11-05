#include "game/DbCursor.h"

extern "C" {
int DbCursorGetValue(DbCursor *pObject, int key);
}

static int lbl_802D6BD8[15] = {
    0x776E5355, 0x6C6E5355, 0x73775355,
    0x74725355, 0x74705355, 0x54445455,
    0x69645355, 0x72665355, 0x73645355,
    0x46535355, 0x46505250, 0x54505455,
    0x42475355, 0x54424755, 0x43535355
};

extern "C" void fn_80087C5C(DbCursor *pObject, unsigned int index, int value)
{
    fn_8007AA90(pObject, lbl_802D6BD8[index], value);
}

extern "C" int fn_80087C8C(DbCursor *pObject, unsigned int index)
{
    return DbCursorGetValue(pObject, lbl_802D6BD8[index]);
}
