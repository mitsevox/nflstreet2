/* Switches the on-screen debug text printer on and off for the DbgPrint module. */
#include "game/DbgFont.h"

extern "C" {
void DbgPrintEnable(void)
{
    DbgFontSetEnabled(1);
}

void DbgPrintDisable(void)
{
    DbgFontSetEnabled(0);
}
}
