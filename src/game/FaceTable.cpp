/* Opens and closes the game database cursor on the face table for the
   create-a-player screen. */

#include "game/Object_8007A334.h"

static Object_8007A334 _FaceTable_Cursor;

extern "C" {
static void _FaceTableOpenCursor()
{
    fn_8007A334(&_FaceTable_Cursor, 0x45434146, -1, 0, 0, 0x54415453);
}

static void _FaceTableCloseCursor()
{
    fn_8007A3C4(&_FaceTable_Cursor);
}

void FaceTableOpen()
{
    _FaceTableOpenCursor();
}

void FaceTableClose()
{
    _FaceTableCloseCursor();
}
}
