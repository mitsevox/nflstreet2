/* Dynamic colour tables: the operations of a "dynclut" data block, each
   setting, blending or scaling a range of colour-table entries from palette
   colours or from other entries of the same table. */
#include "game/DynClut_80044F20.h"
#include "game/fn_801D2B7C.h"

extern "C" {
void *fn_80216BFC(void *pNode, const char *pName);
void *fn_80216E34(void *pNode);
int fn_80217070(void *pNode, const char *pName, int value);
void fn_80239D1C(void *p, int size);
void fn_8024E034(void);
}

static inline void UnpackColor(const unsigned short *pData, int index, PaletteColor *pColor, int format)
{
    unsigned int value = pData[index];

    switch (format) {
    case 2:
        if (value & 0x8000) {
            pColor->r = (value >> 7) & 0xF8;
            pColor->g = (value >> 2) & 0xF8;
            pColor->b = value << 3;
        } else {
            pColor->r = (value >> 4) & 0xF0;
            pColor->g = value & 0xF0;
            pColor->b = value << 4;
        }
        break;
    case 1:
        pColor->r = (value >> 8) & 0xF8;
        pColor->g = (value >> 3) & 0xFC;
        pColor->b = value << 3;
        break;
    }
}

static inline void PackColor(unsigned short *pData, int index, unsigned int r, unsigned int g,
                             unsigned int b, int format)
{
    switch (format) {
    case 2:
        if (pData[index] & 0x8000) {
            pData[index] = (pData[index] & 0x8000) | ((r << 7) & 0x7C00) | ((g << 2) & 0x3E0) | (b >> 3);
        } else {
            pData[index] = (pData[index] & 0xF000) | ((r << 4) & 0xF00) | (g & 0xF0) | (b >> 4);
        }
        break;
    case 1:
        pData[index] = ((r << 8) & 0xF800) | ((g << 3) & 0x7E0) | (b >> 3);
        break;
    }
}

static inline void PackColor(unsigned short *pData, int index, const PaletteColor *pColor, int format)
{
    PackColor(pData, index, pColor->r, pColor->g, pColor->b, format);
}

static inline int BlendChannel(int a, int b, int weightA, int weightB, int total)
{
    int value = (a * weightA + b * weightB) / total;

    if (value > 255) {
        value = 255;
    }
    return value;
}

static inline int ScaleChannel(int value, int scale)
{
    value = value * (scale * 2) / 255;
    if (value > 255) {
        value = 255;
    }
    return value;
}

static inline void ScaleColor(PaletteColor *pColor, const PaletteColor *pScale)
{
    pColor->r = ScaleChannel(pColor->r, pScale->r);
    pColor->g = ScaleChannel(pColor->g, pScale->g);
    pColor->b = ScaleChannel(pColor->b, pScale->b);
}

static inline void BlendRange(unsigned short *pData, int format, const ColorEntry *pEntry,
                              const PaletteColor *pFrom, const PaletteColor *pTo)
{
    int total = pEntry->mTo - pEntry->mFrom;
    int weightFrom = total;
    int weightTo = 0;

    for (int i = pEntry->mFrom; i <= pEntry->mTo; i++) {
        PaletteColor color;

        color.r = BlendChannel(pFrom->r, pTo->r, weightFrom, weightTo, total);
        color.g = BlendChannel(pFrom->g, pTo->g, weightFrom, weightTo, total);
        color.b = BlendChannel(pFrom->b, pTo->b, weightFrom, weightTo, total);
        PackColor(pData, i, color.r, color.g, color.b, format);
        weightFrom--;
        weightTo++;
    }
}

extern "C" {
void fn_80044F20(void *pData, Entry_80046004 *pEntry)
{
    void *pNode;
    void *pFirst;
    int count = 0;

    pNode = fn_80216BFC(pData, "dynclut");
    fn_80217070(pNode, "version", 0);
    pNode = fn_80216BFC(pNode, "operations");
    pNode = fn_80216BFC(pNode, "op");
    for (pFirst = pNode; pNode; pNode = fn_80216E34(pNode)) {
        count++;
    }
    pEntry->mCount = count;
    if (count > 0) {
        pEntry->mpEntries = (ColorEntry *)fn_801D2B7C(count * sizeof(ColorEntry), 4, 0);
    } else {
        pEntry->mpEntries = 0;
    }
    pNode = pFirst;
    for (int i = 0; i < pEntry->mCount; i++) {
        fn_80044C88(pNode, &pEntry->mpEntries[i]);
        pNode = fn_80216E34(pNode);
    }
}

ColorPalette *fn_80045020(Palettes_8004605C *pPalettes, int colorNum)
{
    ColorPalette *pPalette = 0;

    for (int i = 0; i < pPalettes->mCount; i++) {
        if (pPalettes->mpColorNums[i] == colorNum) {
            pPalette = &pPalettes->mpPalettes[i];
            break;
        }
    }
    return pPalette;
}

void fn_80045084(void *p, State_80045084 *pState)
{
    const State_80045084 *pSource = (const State_80045084 *)p;

    pState->mUnknown0 = pSource->mUnknown0;
    pState->mFormat = pSource->mFormat;
    pState->mSize = pSource->mSize;
    pState->mpData = pSource->mpData;
}

void fn_800450A8(void *p, State_80045084 *pState)
{
    fn_80239D1C(pState->mpData, pState->mSize);
    fn_8024E034();
}

void fn_800450D8(ColorEntry *pEntry, State_80045084 *pState, Palettes_8004605C *pPalettes)
{
    unsigned short *pData = pState->mpData;
    int format = pState->mFormat;
    PaletteColor color = fn_80045020(pPalettes, pEntry->mColor)->mColors[pEntry->mLevel];

    for (int i = pEntry->mFrom; i <= pEntry->mTo; i++) {
        PackColor(pData, i, &color, format);
    }
}

void fn_800451D0(ColorEntry *pEntry, State_80045084 *pState)
{
    unsigned short *pData = pState->mpData;
    int format = pState->mFormat;
    PaletteColor color;

    UnpackColor(pData, pEntry->mColor, &color, format);
    for (int i = pEntry->mFrom; i <= pEntry->mTo; i++) {
        PackColor(pData, i, &color, format);
    }
}

void fn_800452F8(ColorEntry *pEntry, State_80045084 *pState)
{
    unsigned short *pData = pState->mpData;
    int format = pState->mFormat;
    PaletteColor from;
    PaletteColor to;

    UnpackColor(pData, pEntry->mFrom, &from, format);
    UnpackColor(pData, pEntry->mTo, &to, format);
    BlendRange(pData, format, pEntry, &from, &to);
}

void fn_80045524(ColorEntry *pEntry, State_80045084 *pState, Palettes_8004605C *pPalettes)
{
    unsigned short *pData = pState->mpData;
    int format = pState->mFormat;
    PaletteColor to;
    PaletteColor from = fn_80045020(pPalettes, pEntry->mColor)->mColors[pEntry->mLevel];

    UnpackColor(pData, pEntry->mTo, &to, format);
    BlendRange(pData, format, pEntry, &from, &to);
}

void fn_80045714(ColorEntry *pEntry, State_80045084 *pState, Palettes_8004605C *pPalettes)
{
    unsigned short *pData = pState->mpData;
    int format = pState->mFormat;
    PaletteColor from;
    PaletteColor to = fn_80045020(pPalettes, pEntry->mColor)->mColors[pEntry->mLevel];

    UnpackColor(pData, pEntry->mFrom, &from, format);
    BlendRange(pData, format, pEntry, &from, &to);
}

void fn_80045904(ColorEntry *pEntry, State_80045084 *pState)
{
    unsigned short *pData = pState->mpData;
    int format = pState->mFormat;
    PaletteColor from;
    PaletteColor to;

    UnpackColor(pData, pEntry->mColor, &from, format);
    UnpackColor(pData, pEntry->mTo, &to, format);
    BlendRange(pData, format, pEntry, &from, &to);
}

void fn_80045B30(ColorEntry *pEntry, State_80045084 *pState)
{
    unsigned short *pData = pState->mpData;
    int format = pState->mFormat;
    PaletteColor to;
    PaletteColor from;

    UnpackColor(pData, pEntry->mColor, &to, format);
    UnpackColor(pData, pEntry->mFrom, &from, format);
    BlendRange(pData, format, pEntry, &from, &to);
}

void fn_80045D5C(ColorEntry *pEntry, State_80045084 *pState, Palettes_8004605C *pPalettes)
{
    unsigned short *pData = pState->mpData;
    int format = pState->mFormat;
    PaletteColor color;
    PaletteColor scale = fn_80045020(pPalettes, pEntry->mColor)->mColors[pEntry->mLevel];

    UnpackColor(pData, pEntry->mColor, &color, format);
    for (int i = pEntry->mFrom; i <= pEntry->mTo; i++) {
        ScaleColor(&color, &scale);
        PackColor(pData, i, &color, format);
    }
}

void fn_80045F64(ColorEntry *pEntry, State_80045084 *pState, Palettes_8004605C *pPalettes)
{
    switch (pEntry->mMode) {
    case 0:
        fn_800450D8(pEntry, pState, pPalettes);
        break;
    case 1:
        fn_800451D0(pEntry, pState);
        break;
    case 2:
        fn_800452F8(pEntry, pState);
        break;
    case 3:
        fn_80045524(pEntry, pState, pPalettes);
        break;
    case 4:
        fn_80045714(pEntry, pState, pPalettes);
        break;
    case 5:
        fn_80045904(pEntry, pState);
        break;
    case 6:
        fn_80045B30(pEntry, pState);
        break;
    case 7:
        fn_80045D5C(pEntry, pState, pPalettes);
        break;
    }
}
}
