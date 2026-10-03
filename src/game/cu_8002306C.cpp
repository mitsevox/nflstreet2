#include "game/Object_8007A334.h"

static Object_8007A334 lbl_8037DEA4;

extern "C" {
static void fn_8002306C()
{
    fn_8007A334(&lbl_8037DEA4, 0x45434146, -1, 0, 0, 0x54415453);
}

static void fn_800230B0()
{
    fn_8007A3C4(&lbl_8037DEA4);
}

void fn_800230D8()
{
    fn_8002306C();
}

void fn_800230F8()
{
    fn_800230B0();
}
}
