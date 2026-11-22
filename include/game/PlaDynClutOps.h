#ifndef GAME_PLADYNCLUTOPS_H
#define GAME_PLADYNCLUTOPS_H

#include "game/PaletteColor.h"

/* One colour-table operation of a "dynclut" data block, parsed by
   PlaDynClutParseEntry and applied by PlaDynClutApplyOp according to mMode. */
struct ColorEntry {
    int mMode;
    unsigned char mFrom;
    unsigned char mTo;
    unsigned char mColor;
    unsigned char mLevel;
};

/* The operations read from one "dynclut" block by PlaDynClutParseOps. */
struct PlaDynClutEntry_t {
    int mCount;
    ColorEntry *mpEntries;
};

/* Colour-table description copied from the texture object by PlaDynClutBeginTable:
   mFormat 1 holds 5:6:5 entries and mFormat 2 holds entries with a 0x8000
   flag selecting 5:5:5 over 3:4:4:4. */
struct PlaDynClutTable_t {
    unsigned short mUnknown0;
    unsigned short mFormat;
    int mSize;
    unsigned short *mpData;
};

/* mCount palettes with the colour number that selects each. */
struct PlaDynClutPalettes_t {
    int mCount;
    int *mpColorNums;
    ColorPalette *mpPalettes;
};

extern "C" {
void PlaDynClutParseEntry(void *pNode, ColorEntry *pEntry);
void PlaDynClutParseOps(void *pData, PlaDynClutEntry_t *pEntry);
void PlaDynClutBeginTable(void *p, PlaDynClutTable_t *pState);
void PlaDynClutEndTable(void *p, PlaDynClutTable_t *pState);
void PlaDynClutApplyOp(ColorEntry *pEntry, PlaDynClutTable_t *pState, PlaDynClutPalettes_t *pPalettes);
}

#endif
