/* Appearance item names for create-a-player: a small class that keeps a database
   cursor open on the item table while the screen lists the items, and returns each
   item's name. */

#include "game/AppearanceNameTable.h"

extern "C" {
int DbFileTblLoad(int a, int b);
int DbFileTblDestroy(int a, int b);
}

AppearanceNameTable::AppearanceNameTable()
{
    DbFileTblLoad(0x54415453, 0x4B414D46);
    mUnknown0.OpenTable(0x4B414D46, 0x44494D46, 0, 0, 0x54415453);
}

AppearanceNameTable::~AppearanceNameTable()
{
    mUnknown0.CloseTable();
    DbFileTblDestroy(0x54415453, 0x4B414D46);
}

void AppearanceNameTable::GetItemName(int a, int b, int c)
{
    mUnknown0.FindColumnValue(0x44494D46, a, 0, 0);
    mUnknown0.GetColumnString(0x43444D46, b, c);
}
