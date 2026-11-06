/* A 24-line by 80-column debug text screen: clears lines and draws the lines that are in use with
   the debug font. */
#include <dolphin/gx/GXStruct.h>
#include "game/DbgFont.h"
#include "game/fn_801C1F94.h"

extern "C" {
/* Text screen of 24 rows of 80 columns plus a terminator; a row is drawn only while its flag is set. */
static char _DbgScreen_aszLines[24 * 81] = { 0 };
static unsigned char _DbgScreen_abLineOn[24];
static GXColor _DbgScreen_Color = { 180, 180, 180, 255 };
static unsigned char _DbgScreen_bVisible;

void DbgScreenClearLine(unsigned short row)
{
    fn_801C1F94(&_DbgScreen_aszLines[row * 81], ' ', 80);
    _DbgScreen_aszLines[row * 81 + 80] = 0;
    _DbgScreen_abLineOn[row] = 0;
}

void DbgScreenClear(void)
{
    unsigned int row;

    for (row = 0; row < 24; row++) {
        DbgScreenClearLine(row);
    }
    _DbgScreen_bVisible = 0;
}

void DbgScreenDraw(void)
{
    unsigned int row;

    DbgFontSetColor(_DbgScreen_Color.r, _DbgScreen_Color.g, _DbgScreen_Color.b);
    if (_DbgScreen_bVisible) {
        for (row = 0; row < 24; row++) {
            if (_DbgScreen_abLineOn[row]) {
                DbgFontPrint(0, row * 9, 0, &_DbgScreen_aszLines[row * 81], 0);
            }
        }
    }
}
}
