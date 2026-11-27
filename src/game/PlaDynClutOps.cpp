/* Dynamic colour tables: the operations of a "dynclut" data block, each
   setting, blending or scaling a range of colour-table entries from palette
   colours or from other entries of the same table. */
#include "game/PlaDynClutOps.h"
#include "game/fn_801D2B7C.h"
#include <dolphin/gx/GXManage.h>

extern "C" {
void *XmlFindInElement(void *pNode, const char *pName);
void *XmlFindNext(void *pNode);
int XmlGetAttrInt(void *pNode, const char *pName, int value);
void DCStoreRange(void *p, int size);
}

static inline void UnpackColor(const unsigned short *pData, int index, PaletteColor *pColor, int format)
{
    // FAKEMATCH: the entry is read through a byte offset (index << 1), which the target computes with slwi
    unsigned int value = *(const unsigned short *)((const char *)pData + (index << 1));

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
    unsigned short *p = &pData[index];

    switch (format) {
    case 2:
        if (*p & 0x8000) {
            *p = (*p & 0x8000) | ((r << 7) & 0x7C00) | ((g << 2) & 0x3E0) | (b >> 3);
        } else {
            *p = (*p & 0xF000) | ((r << 4) & 0xF00) | (g & 0xF0) | (b >> 4);
        }
        break;
    case 1:
        *p = ((r << 8) & 0xF800) | ((g << 3) & 0x7E0) | (b >> 3);
        break;
    }
}

static inline void PackColor(unsigned short *pData, int index, const PaletteColor *pColor, int format)
{
    PackColor(pData, index, pColor->r, pColor->g, pColor->b, format);
}

static inline int BlendChannel(int a, int b, int weightA, int weightB, int total)
{
    int value = (weightA * a + weightB * b) / total;

    if (value > 255) {
        value = 255;
    }
    return value;
}

static inline int ScaleChannel(int value, int scale)
{
    int result = scale * 2 * value / 255;

    if (result > 255) {
        result = 255;
    }
    return result;
}

extern "C" {
void PlaDynClutParseOps(void *pData, PlaDynClutEntry_t *pEntry)
{
    void *pNode;
    void *pFirst;
    int count = 0;

    pNode = XmlFindInElement(pData, "dynclut");
    XmlGetAttrInt(pNode, "version", 0);
    pNode = XmlFindInElement(pNode, "operations");
    pNode = XmlFindInElement(pNode, "op");
    for (pFirst = pNode; pNode; pNode = XmlFindNext(pNode)) {
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
        PlaDynClutParseEntry(pNode, &pEntry->mpEntries[i]);
        pNode = XmlFindNext(pNode);
    }
}

ColorPalette *PlaDynClutFindPalette(PlaDynClutPalettes_t *pPalettes, int colorNum)
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

static inline void GetPaletteColor(PlaDynClutPalettes_t *pPalettes, const ColorEntry *pEntry, PaletteColor *pColor)
{
    *pColor = PlaDynClutFindPalette(pPalettes, pEntry->mColor)->mColors[pEntry->mLevel];
}

void PlaDynClutBeginTable(void *p, PlaDynClutTable_t *pState)
{
    const PlaDynClutTable_t *pSource = (const PlaDynClutTable_t *)p;

    pState->mUnknown0 = pSource->mUnknown0;
    pState->mFormat = pSource->mFormat;
    pState->mSize = pSource->mSize;
    pState->mpData = pSource->mpData;
}

void PlaDynClutEndTable(void *p, PlaDynClutTable_t *pState)
{
    DCStoreRange(pState->mpData, pState->mSize);
    GXFlush();
}

void PlaDynClutSetRange(ColorEntry *pEntry, PlaDynClutTable_t *pState, PlaDynClutPalettes_t *pPalettes)
{
    unsigned short *pData = pState->mpData;
    int format = pState->mFormat;
    PaletteColor color = PlaDynClutFindPalette(pPalettes, pEntry->mColor)->mColors[pEntry->mLevel];

    for (int i = pEntry->mFrom; i <= pEntry->mTo; i++) {
        PackColor(pData, i, &color, format);
    }
}

void PlaDynClutFillRange(ColorEntry *pEntry, PlaDynClutTable_t *pState)
{
    unsigned short *pData = pState->mpData;
    int format = pState->mFormat;
    PaletteColor color;

    UnpackColor(pData, pEntry->mColor, &color, format);
    for (int i = pEntry->mFrom; i <= pEntry->mTo; i++) {
        PackColor(pData, i, &color, format);
    }
}

void PlaDynClutBlendRange(ColorEntry *pEntry, PlaDynClutTable_t *pState)
{
    unsigned short *pData = pState->mpData;
    int format = pState->mFormat;
    PaletteColor from;
    PaletteColor to;

    UnpackColor(pData, pEntry->mFrom, &from, format);
    UnpackColor(pData, pEntry->mTo, &to, format);
    int total = pEntry->mTo - pEntry->mFrom;
    int weightFrom = total;
    int weightTo = 0;

    for (int i = pEntry->mFrom; i <= pEntry->mTo; i++) {
        PaletteColor color;

        color.r = BlendChannel(from.r, to.r, weightFrom, weightTo, total);
        color.g = BlendChannel(from.g, to.g, weightFrom, weightTo, total);
        color.b = BlendChannel(from.b, to.b, weightFrom, weightTo, total);
        PackColor(pData, i, color.r, color.g, color.b, format);
        weightFrom--;
        weightTo++;
    }
}

void PlaDynClutBlendPaletteToEnd(ColorEntry *pEntry, PlaDynClutTable_t *pState, PlaDynClutPalettes_t *pPalettes)
{
    unsigned short *pData = pState->mpData;
    int format = pState->mFormat;
    PaletteColor to;
    PaletteColor from;

    GetPaletteColor(pPalettes, pEntry, &from);
    UnpackColor(pData, pEntry->mTo, &to, format);
    int total = pEntry->mTo - pEntry->mFrom;
    int weightFrom = total;
    int weightTo = 0;

    for (int i = pEntry->mFrom; i <= pEntry->mTo; i++) {
        PaletteColor color;

        color.r = BlendChannel(from.r, to.r, weightFrom, weightTo, total);
        color.g = BlendChannel(from.g, to.g, weightFrom, weightTo, total);
        color.b = BlendChannel(from.b, to.b, weightFrom, weightTo, total);
        PackColor(pData, i, color.r, color.g, color.b, format);
        weightFrom--;
        weightTo++;
    }
}

void PlaDynClutBlendStartToPalette(ColorEntry *pEntry, PlaDynClutTable_t *pState, PlaDynClutPalettes_t *pPalettes)
{
    unsigned short *pData = pState->mpData;
    int format = pState->mFormat;
    PaletteColor from;
    PaletteColor to;

    GetPaletteColor(pPalettes, pEntry, &to);
    UnpackColor(pData, pEntry->mFrom, &from, format);
    int total = pEntry->mTo - pEntry->mFrom;
    int weightFrom = total;
    int weightTo = 0;

    for (int i = pEntry->mFrom; i <= pEntry->mTo; i++) {
        PaletteColor color;

        color.r = BlendChannel(from.r, to.r, weightFrom, weightTo, total);
        color.g = BlendChannel(from.g, to.g, weightFrom, weightTo, total);
        color.b = BlendChannel(from.b, to.b, weightFrom, weightTo, total);
        PackColor(pData, i, color.r, color.g, color.b, format);
        weightFrom--;
        weightTo++;
    }
}

void PlaDynClutBlendSourceToEnd(ColorEntry *pEntry, PlaDynClutTable_t *pState)
{
    unsigned short *pData = pState->mpData;
    int format = pState->mFormat;
    PaletteColor from;
    PaletteColor to;

    UnpackColor(pData, pEntry->mColor, &from, format);
    UnpackColor(pData, pEntry->mTo, &to, format);
    int total = pEntry->mTo - pEntry->mFrom;
    int weightFrom = total;
    int weightTo = 0;

    for (int i = pEntry->mFrom; i <= pEntry->mTo; i++) {
        PaletteColor color;

        color.r = BlendChannel(from.r, to.r, weightFrom, weightTo, total);
        color.g = BlendChannel(from.g, to.g, weightFrom, weightTo, total);
        color.b = BlendChannel(from.b, to.b, weightFrom, weightTo, total);
        PackColor(pData, i, color.r, color.g, color.b, format);
        weightFrom--;
        weightTo++;
    }
}

void PlaDynClutBlendStartToSource(ColorEntry *pEntry, PlaDynClutTable_t *pState)
{
    unsigned short *pData = pState->mpData;
    int format = pState->mFormat;
    PaletteColor to;
    PaletteColor from;

    UnpackColor(pData, pEntry->mColor, &to, format);
    UnpackColor(pData, pEntry->mFrom, &from, format);
    int total = pEntry->mTo - pEntry->mFrom;
    int weightFrom = total;
    int weightTo = 0;

    for (int i = pEntry->mFrom; i <= pEntry->mTo; i++) {
        PaletteColor color;

        color.r = BlendChannel(from.r, to.r, weightFrom, weightTo, total);
        color.g = BlendChannel(from.g, to.g, weightFrom, weightTo, total);
        color.b = BlendChannel(from.b, to.b, weightFrom, weightTo, total);
        PackColor(pData, i, color.r, color.g, color.b, format);
        weightFrom--;
        weightTo++;
    }
}

void PlaDynClutScaleRange(ColorEntry *pEntry, PlaDynClutTable_t *pState, PlaDynClutPalettes_t *pPalettes)
{
    unsigned short *pData = pState->mpData;
    int format = pState->mFormat;
    PaletteColor color;
    PaletteColor scale;

    GetPaletteColor(pPalettes, pEntry, &scale);
    UnpackColor(pData, pEntry->mColor, &color, format);
    for (int i = pEntry->mFrom; i <= pEntry->mTo; i++) {
        color.r = ScaleChannel(color.r, scale.r);
        color.g = ScaleChannel(color.g, scale.g);
        color.b = ScaleChannel(color.b, scale.b);
        PackColor(pData, i, &color, format);
    }
}

void PlaDynClutApplyOp(ColorEntry *pEntry, PlaDynClutTable_t *pState, PlaDynClutPalettes_t *pPalettes)
{
    switch (pEntry->mMode) {
    case 0:
        PlaDynClutSetRange(pEntry, pState, pPalettes);
        break;
    case 1:
        PlaDynClutFillRange(pEntry, pState);
        break;
    case 2:
        PlaDynClutBlendRange(pEntry, pState);
        break;
    case 3:
        PlaDynClutBlendPaletteToEnd(pEntry, pState, pPalettes);
        break;
    case 4:
        PlaDynClutBlendStartToPalette(pEntry, pState, pPalettes);
        break;
    case 5:
        PlaDynClutBlendSourceToEnd(pEntry, pState);
        break;
    case 6:
        PlaDynClutBlendStartToSource(pEntry, pState);
        break;
    case 7:
        PlaDynClutScaleRange(pEntry, pState, pPalettes);
        break;
    }
}
}
