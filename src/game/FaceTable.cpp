/* Opens and closes the game database cursor on the face table for the
   create-a-player screen. */

#include "game/DbCursor.h"

static DbCursor _FaceTable_Cursor;

extern "C" {
static void _FaceTableOpenCursor()
{
    DbCursorOpen(&_FaceTable_Cursor, 0x45434146, -1, 0, 0, 0x54415453);
}

static void _FaceTableCloseCursor()
{
    DbCursorClose(&_FaceTable_Cursor);
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
