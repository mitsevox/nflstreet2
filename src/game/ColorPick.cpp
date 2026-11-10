/* Colour-picker grid for UIStudio screens: records the grid size, turns a row and column into a palette index and returns that palette entry's RGB. */
#include "game/PaletteColor.h"
#include "game/UISGameMsg.h"

struct ColorPickMsg_t {
    int mUnknown0;
    int mUnknown4;
    int *mpUnknown8;
    int *mpUnknownC;
    int *mpUnknown10;
};

static int _ColorPick_iRows = -1;
static int _ColorPick_iColumns = -1;
static int _ColorPick_iSelected = -1;

extern "C" {
int ColorPickCellToIndex(int a, int b);

void ColorPickSetGrid(int a, int b)
{
    _ColorPick_iRows = a;
    _ColorPick_iColumns = b;
}

void ColorPickSelect(int a, int b, int *pOut0, int *pOut1, int *pOut2)
{
    PaletteColor color;
    int value = ColorPickCellToIndex(a, b);

    _ColorPick_iSelected = value;
    DbColPalGetPrimaryColor(value, &color);
    *pOut0 = color.r;
    *pOut2 = color.b;
    *pOut1 = color.g;
}

int ColorPickHandleMsg(int id, ColorPickMsg_t *pBlock, int unused, int *pResult)
{
    switch (id) {
    case 17:
        ColorPickSetGrid(pBlock->mUnknown0, pBlock->mUnknown4);
        break;
    case 18:
        ColorPickSelect(pBlock->mUnknown0, pBlock->mUnknown4, pBlock->mpUnknown8, pBlock->mpUnknownC, pBlock->mpUnknown10);
        break;
    default:
        return 0;
    }
    return 1;
}

int ColorPickCellToIndex(int a, int b)
{
    return a * _ColorPick_iColumns + b;
}

void ColorPickIndexToCell(int value, int *pQuotient, int *pRemainder)
{
    *pQuotient = value / _ColorPick_iColumns;
    *pRemainder = value % _ColorPick_iColumns;
}

int ColorPickGetSelected(void)
{
    return _ColorPick_iSelected;
}
}
