#ifndef GAME_DYNCLUT_80044F20_H
#define GAME_DYNCLUT_80044F20_H

#include "game/PaletteColor.h"

/* One colour-table operation of a "dynclut" data block, parsed by
   fn_80044C88 and applied by fn_80045F64 according to mMode. */
struct ColorEntry {
    int mMode;
    unsigned char mFrom;
    unsigned char mTo;
    unsigned char mColor;
    unsigned char mLevel;
};

/* The operations read from one "dynclut" block by fn_80044F20. */
struct Entry_80046004 {
    int mCount;
    ColorEntry *mpEntries;
};

/* Colour-table description copied from the texture object by fn_80045084:
   mFormat 1 holds 5:6:5 entries and mFormat 2 holds entries with a 0x8000
   flag selecting 5:5:5 over 3:4:4:4. */
struct State_80045084 {
    unsigned short mUnknown0;
    unsigned short mFormat;
    int mSize;
    unsigned short *mpData;
};

/* mCount palettes with the colour number that selects each. */
struct Palettes_8004605C {
    int mCount;
    int *mpColorNums;
    ColorPalette *mpPalettes;
};

extern "C" {
void fn_80044C88(void *pNode, ColorEntry *pEntry);
void fn_80044F20(void *pData, Entry_80046004 *pEntry);
void fn_80045084(void *p, State_80045084 *pState);
void fn_800450A8(void *p, State_80045084 *pState);
void fn_80045F64(ColorEntry *pEntry, State_80045084 *pState, Palettes_8004605C *pPalettes);
}

#endif
