#include <dolphin/gx/GXBump.h>
#include <dolphin/gx/GXCull.h>
#include <dolphin/gx/GXDispList.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXLighting.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/gx/GXTev.h>
#include <dolphin/gx/GXTexture.h>
#include <dolphin/gx/GXTransform.h>
#include <dolphin/os/OSCache.h>
#include "engine/MovieRcmpInfo.h"
#include <string.h>
#include "engine/Font.h"
#include "engine/llmatrix.h"
#include "engine/cu_8021A438.h"
#include "engine/viewport.h"
#include "engine/sound.h"
#include "engine/texture.h"
#include "game/fn_801D2B7C.h"
#include "game/ResOpenDevice.h"

/* Partial source for the engine range 0x80221BF0-0x80222EC4 (neutral file
   name): text layout on library fonts. Functions without a body here keep
   their original bytes. */

extern void *memcpy();

/* 4-byte element of the Text_80221BF0 array. */
typedef struct Range_80221D30 {
    Uint16 unk_00;  /* 0x00 */
    Uint16 unk_02;  /* 0x02 */
} Range_80221D30;

/* Colour: three colour bytes and an alpha byte. */
typedef struct Rgba_802227B0 {
    Uint8 c[3];     /* 0x00 */
    Uint8 a;        /* 0x03 */
} Rgba_802227B0;

/* Only the accessed members are declared; the size is not established. */
typedef struct Text_80221BF0 {
    Int16 Flags;    /* 0x00 */
    signed char unk_02; /* 0x02 */
    signed char unk_03; /* 0x03 */
    signed char unk_04; /* 0x04 */
    signed char unk_05; /* 0x05 */
    Int16 unk_06;   /* 0x06 */
    Int16 unk_08;   /* 0x08 */
    Int16 unk_0A;   /* 0x0A */
    signed char unk_0C[3]; /* 0x0C */
    Uint8 NumRanges; /* 0x0F */
    Uint8 unk_10;   /* 0x10 */
    Uint8 unk_11[0x03];
    Int16 unk_14;   /* 0x14 */
    Int16 unk_16;   /* 0x16 */
    Rgba_802227B0 unk_18; /* 0x18 */
    Rgba_802227B0 unk_1C; /* 0x1C */
    Buffer_80222E54 *pBuffer; /* 0x20 */
    union {
        Range_80221D30 *pRanges;
        Range_80221D30 Ranges[1];
    } u;            /* 0x24: inline when NumRanges is at most 1 */
} Text_80221BF0;

/* Item data of a font library entry (as in src/engine/UIGFont.c). */
typedef struct UIGFontItem_t {
    Font_t *pFont; /* 0x00 */
    Int32 unk_04;   /* 0x04 */
} UIGFontItem_t;

/* Colour table that fn_80220B4C returns: a count byte, then colour entries. */
typedef struct Palette_80220B4C {
    Uint8 Count;    /* 0x00 */
    Uint8 unk_01[3];
    Rgba_802227B0 Colors[1]; /* 0x04 */
} Palette_80220B4C;

static inline void ClampIndex(Rgba_802227B0 *pColor, Palette_80220B4C *pPalette)
{
    if (pColor->c[0] > pPalette->Count) {
        pColor->c[0] = pPalette->Count - 1;
    }
}

extern Range_80221D30 lbl_8039F9B8[];

int FontGetTextWidth(Font_t *pFont, const char *pText, unsigned int flags);
int FontGetCharWidth(Font_t *pFont, unsigned char c);
int FontGetDescent(Font_t *pFont);
int FontSetRenderFlags(unsigned int flags);
int FontClearRenderFlags(unsigned int flags);
int FontSetShadowOffset(float x, float y, float z);

void fn_80221D5C(Text_80221BF0 *pText);
Range_80221D30 *fn_80221D30(Text_80221BF0 *pText, Uint8 Index);
void fn_80221DB0(Text_80221BF0 *pText);

void UIGTextGetCursorPos(Text_80221BF0 *pText, Int32 Offset, Int32 *pA, Int32 *pB)
{
    Font_t **ppFont;
    Range_80221D30 *pRange = NULL;
    Uint32 Length;
    Int32 i;
    Int32 j;
    Int32 End;

    ppFont = (Font_t **)UIGLibraryGetItemData(UIGLibraryGetGlobal(1), pText->unk_03, pText->unk_02);
    if (pText->Flags & 0x8000) {
        fn_80221DB0(pText);
    }
    Length = strlen(pText->pBuffer->pText);
    if (Offset >= Length && Offset != 0) {
        Offset = Length - 1;
    }
    i = pText->NumRanges;
    while (i-- != 0) {
        pRange = fn_80221D30(pText, i);
        /* FAKEMATCH: unsigned compare (cmplw at 0x80221C90) written as a cast of Offset */
        if (pRange->unk_00 <= (Uint32)Offset) {
            break;
        }
    }
    if (i >= 0) {
        *pB = FontGetDescent(*ppFont) * (i - pText->unk_10);
        *pA = 0;
        End = pRange->unk_02;
        for (j = pRange->unk_00; j < End && j < Offset; j++) {
            *pA += FontGetCharWidth(*ppFont, pText->pBuffer->pText[j]);
        }
    } else {
        *pA = 0;
        *pB = 0;
    }
}

Range_80221D30 *fn_80221D30(Text_80221BF0 *pText, Uint8 Index)
{
    return (pText->NumRanges > 1) ? &pText->u.pRanges[Index] : &pText->u.Ranges[Index];
}

void fn_80221D5C(Text_80221BF0 *pText)
{
    if (pText->NumRanges > 1 && pText->u.pRanges != NULL) {
        fn_801D2BD0(pText->u.pRanges);
        pText->NumRanges = 0;
        pText->u.pRanges = NULL;
    }
}

void fn_80221DB0(Text_80221BF0 *pText)
{
    Font_t **ppFont;
    char *pString;
    char *pLine;
    Int16 Length;
    Int16 Pos;
    Int16 LineStart;
    Int16 NumLines;
    Int16 Line;
    Int32 i;
    Int32 LastSpace;
    Int32 Width;
    Int32 CharWidth;
    Int32 bSpace;
    char c;
    char ch;

    i = 0;
    NumLines = 0;
    ppFont = (Font_t **)UIGLibraryGetItemData(UIGLibraryGetGlobal(1), pText->unk_03, pText->unk_02);
    LineStart = 0;
    pLine = NULL;
    fn_80221D5C(pText);
    if (!(pText->Flags & 0x100)) {
        pText->unk_14 = 0;
    }
    pString = pText->pBuffer->pText;
    Length = strlen(pString);
    for (Pos = 0; Pos <= Length; Pos++) {
        c = pString[Pos];
        if (pLine == NULL) {
            pLine = &pString[Pos];
            LineStart = Pos;
        }
        if (c == '\n' || c == '\0') {
            pString[Pos] = '\0';
            if (pText->Flags & 0x100) {
                Width = 0;
                LastSpace = LineStart;
                for (i = LineStart; i < Pos; i++) {
                    ch = pString[i];
                    CharWidth = FontGetCharWidth(*ppFont, ch);
                    if (ch == ' ' || pString[LastSpace] == ' ') {
                        LastSpace = i;
                    }
                    if (Width + CharWidth > pText->unk_14) {
                        if (pText->Flags & 0x1000) {
                            if (LastSpace != LineStart) {
                                lbl_8039F9B8[NumLines].unk_00 = LineStart;
                                bSpace = 0;
                                if (pString[LastSpace - 1] == ' ') {
                                    lbl_8039F9B8[NumLines].unk_02 = LastSpace - 1;
                                    bSpace = 1;
                                } else {
                                    lbl_8039F9B8[NumLines].unk_02 = LastSpace;
                                }
                                NumLines++;
                                if (!bSpace && pString[LastSpace] == ' ') {
                                    LastSpace++;
                                }
                                LineStart = LastSpace;
                                Width = 0;
                                i = LineStart;
                                LastSpace = LineStart;
                            } else {
                                if (i == LineStart) {
                                    i = LineStart + 1;
                                }
                                lbl_8039F9B8[NumLines].unk_00 = LineStart;
                                lbl_8039F9B8[NumLines].unk_02 = i;
                                NumLines++;
                                if (pString[i] == ' ') {
                                    i++;
                                }
                                LineStart = i;
                                Width = 0;
                                LastSpace = LineStart;
                            }
                        } else if (pText->Flags & 0x2000) {
                            if (i == LineStart) {
                                i = LineStart + 1;
                            }
                            lbl_8039F9B8[NumLines].unk_00 = LineStart;
                            NumLines++;
                            LineStart = i;
                            lbl_8039F9B8[NumLines - 1].unk_02 = i;
                            LastSpace = LineStart;
                            Width = 0;
                        }
                    }
                    Width += CharWidth;
                }
                if (!(pText->Flags & 0x3000)) {
                    if (pText->Flags & 2) {
                        for (i = LineStart; i < Pos - 1 && Width > pText->unk_14; i++) {
                            Width -= FontGetCharWidth(*ppFont, pString[i]);
                        }
                        lbl_8039F9B8[NumLines].unk_00 = i;
                        lbl_8039F9B8[NumLines].unk_02 = Pos;
                    } else if (pText->Flags & 1) {
                        LastSpace = LineStart;
                        for (i = Pos - 1; LastSpace < i && Width > pText->unk_14;) {
                            Width -= FontGetCharWidth(*ppFont, pString[i--]);
                            if (LastSpace < i && Width > pText->unk_14) {
                                Width -= FontGetCharWidth(*ppFont, pString[LastSpace++]);
                            }
                        }
                        lbl_8039F9B8[NumLines].unk_00 = LastSpace;
                        lbl_8039F9B8[NumLines].unk_02 = i + 1;
                    } else {
                        for (i = Pos - 1; Width > pText->unk_14 && i > 1;) {
                            Width -= FontGetCharWidth(*ppFont, pString[i--]);
                        }
                        lbl_8039F9B8[NumLines].unk_00 = LineStart;
                        lbl_8039F9B8[NumLines].unk_02 = i + 1;
                    }
                } else {
                    lbl_8039F9B8[NumLines].unk_02 = Pos;
                    lbl_8039F9B8[NumLines].unk_00 = LineStart;
                }
                NumLines++;
            } else {
                lbl_8039F9B8[NumLines].unk_02 = Pos;
                lbl_8039F9B8[NumLines].unk_00 = LineStart;
                NumLines++;
                Width = FontGetTextWidth(*ppFont, &pString[LineStart], pText->Flags);
                if (Width > pText->unk_14) {
                    pText->unk_14 = Width;
                }
            }
            pString[Pos] = c;
            pLine = NULL;
        }
    }
    if (NumLines > 1) {
        UIGLibrarySetMemInfo(pText->unk_03, pText->unk_02);
        pText->u.pRanges = fn_801D2B7C(NumLines * sizeof(Range_80221D30), 0, 0);
        UIGLibraryClearMemInfo();
    }
    pText->NumRanges = NumLines;
    for (Line = 0; Line < NumLines; Line++) {
        *fn_80221D30(pText, Line) = lbl_8039F9B8[Line];
    }
    if (!(pText->Flags & 0x200)) {
        pText->unk_16 = pText->NumRanges * FontGetDescent(*ppFont);
    }
    pText->Flags &= 0x7FFF;
}

void fn_80222764(Text_80221BF0 *pText);
void UIGLibTextDraw(Text_80221BF0 *pText);
void fn_80222E0C(Text_80221BF0 *pText);
void fn_80222E54(Buffer_80222E54 *pDst, Buffer_80222E54 *pSrc);

void UIGLibTextObjAction(Text_80221BF0 *pText, Uint32 Msg, Int32 Unused, void *pData, void *pOut)
{
    switch (Msg) {
    case -1:
        pText->pBuffer = (Buffer_80222E54 *)((Int32)pText + (Int32)pText->pBuffer);
        fn_80222764(pText);
        break;
    case -2:
        UIGLibTextDraw(pText);
        break;
    case -3:
        fn_80222E0C(pText);
        pText->pBuffer = (Buffer_80222E54 *)((Int32)pText->pBuffer - (Int32)pText);
        break;
    case -4:
        break;
    case 0:
        pText->unk_18.c[0] = ((Int32 *)pData)[0];
        pText->unk_18.c[1] = ((Int32 *)pData)[1];
        pText->unk_18.c[2] = ((Int32 *)pData)[2];
        pText->unk_18.a = ((Int32 *)pData)[3];
        break;
    case 1:
        pText->unk_1C.c[0] = ((Int32 *)pData)[0];
        pText->unk_1C.c[1] = ((Int32 *)pData)[1];
        pText->unk_1C.c[2] = ((Int32 *)pData)[2];
        pText->unk_1C.a = ((Int32 *)pData)[3];
        break;
    case 2:
        pText->unk_0C[0] = ((Float32 *)pData)[0];
        pText->unk_0C[1] = ((Float32 *)pData)[1];
        pText->unk_0C[2] = ((Float32 *)pData)[2];
        break;
    case 3:
        fn_80222E54(pText->pBuffer, *(Buffer_80222E54 **)pData);
        fn_80221DB0(pText);
        break;
    case 4:
        fn_80222E54(*(Buffer_80222E54 **)pData, pText->pBuffer);
        break;
    case 5:
        pText->Flags &= ~3;
        if (*(Int32 *)pData >= 0) {
            if (*(Int32 *)pData == 0) {
                pText->Flags |= 1;
            } else {
                pText->Flags |= 2;
            }
        }
        break;
    case 6:
        pText->unk_06 = ((Float32 *)pData)[0];
        pText->unk_08 = ((Float32 *)pData)[1];
        pText->unk_0A = 0;
        break;
    case 7: {
        Int32 Index = ((Int16 *)pData)[0];
        Int32 Item = ((Int16 *)pData)[1];
        Uint8 *pItem;
        Uint8 *pSrc;
        Uint8 *pDst;
        Int32 i;

        if (Index != -1 && Item != -1) {
            pItem = (Uint8 *)UIGLibraryLoadItem(UIGLibraryGetGlobal(1), Index, Item);
            if (pItem != NULL) {
                fn_80222E0C(pText);
                pText->unk_03 = pItem[1];
                pText->unk_02 = pItem[0];
                pDst = (Uint8 *)pText->unk_0C;
                pSrc = pItem + 5;
                for (i = 0; i < 3; i++) {
                    pDst[i] = pSrc[i];
                }
                pText->Flags &= ~0x50;
                if (pItem[4] & 0x10) {
                    pText->Flags |= 0x10;
                } else if (pItem[4] & 0x40) {
                    pText->Flags |= 0x40;
                }
                fn_80222764(pText);
            }
            UIGLibraryUnLoadItem(UIGLibraryGetGlobal(1), Index, Item);
            pText->Flags |= 0x8000;
        }
        break;
    }
    case 8: {
        Int32 Index = ((Int16 *)pData)[0];
        Int32 Item = ((Int16 *)pData)[1];

        if (Index != -1 && Item != -1) {
            pText->unk_04 = Item;
            pText->unk_05 = Index;
        }
        break;
    }
    case 9: {
        signed char Hi = *(Int32 *)pData >> 16;
        signed char Lo = *(Int32 *)pData;

        fn_80222E0C(pText);
        pText->unk_02 = Lo;
        pText->unk_03 = Hi;
        fn_80222764(pText);
        break;
    }
    case 10:
        pText->unk_18.c[0] = *(Int32 *)pData;
        break;
    case 11:
        pText->unk_1C.c[0] = *(Int32 *)pData;
        break;
    case 12: {
        Int32 X;
        Int32 Y;

        UIGTextGetCursorPos(pText, *(Int32 *)pData, &X, &Y);
        *(Float32 *)pOut = X;
        break;
    }
    case 13: {
        Int32 X;
        Int32 Y;

        UIGTextGetCursorPos(pText, *(Int32 *)pData, &X, &Y);
        *(Float32 *)pOut = Y;
        break;
    }
    case 14:
        if (pText->Flags & 0x8000) {
            fn_80221DB0(pText);
        }
        *(Int32 *)pOut = pText->NumRanges;
        break;
    case 15: {
        Int32 Line = *(Int32 *)pData;

        if (pText->Flags & 0x8000) {
            fn_80221DB0(pText);
        }
        if (Line <= 0) {
            Line = 0;
        } else if (Line >= pText->NumRanges) {
            Line = pText->NumRanges - 1;
        }
        *(Int32 *)pOut = fn_80221D30(pText, Line)->unk_00;
        break;
    }
    case 16:
        pText->unk_10 = *(Int32 *)pData;
        break;
    case 17:
        *(Int32 *)pOut = pText->unk_10;
        break;
    case 18:
        if (pText->Flags & 0x100) {
            pText->unk_14 = *(Int32 *)pData;
            pText->Flags |= 0x8000;
        }
        break;
    case 19:
        if (pText->Flags & 0x200) {
            pText->unk_16 = *(Int32 *)pData;
        }
        break;
    case 20:
        *(Int32 *)pOut = pText->unk_14;
        break;
    case 21:
        *(Int32 *)pOut = pText->unk_16;
        break;
    case 22:
        *(Int32 *)pOut = (pText->unk_03 << 16) | (Uint16)pText->unk_02;
        break;
    case 23:
        *(Float32 *)pOut = pText->unk_06;
        break;
    case 24:
        *(Float32 *)pOut = pText->unk_08;
        break;
    }
}

void fn_80222764(Text_80221BF0 *pText)
{
    UIGLibraryLoadItem(UIGLibraryGetGlobal(1), pText->unk_03, pText->unk_02);
    fn_80221DB0(pText);
}

void UIGLibTextDraw(Text_80221BF0 *pText)
{
    FontColor_t Color;
    Float32 Pos[3];
    Rgba_802227B0 Color0;
    Rgba_802227B0 Color1;
    UIGFontItem_t *pItem;
    UIGMaterialColorState_t *pScale;
    Palette_80220B4C *pPalette;
    Range_80221D30 *pRange;
    Uint32 Align;
    Float32 Scale;
    Int32 Bottom;
    Int32 LineHeight;
    Uint32 Line;
    char Saved;
    char *pString;
    char *pLine;

    pItem = (UIGFontItem_t *)UIGLibraryGetItemData(UIGLibraryGetGlobal(1), pText->unk_03, pText->unk_02);
    if (pItem == NULL) {
        return;
    }
    if (pItem->unk_04 != 0) {
        UIGLibrarySetMemInfo(pText->unk_03, pText->unk_02);
        FontUploadTextures(pItem->pFont, 1);
        UIGLibraryClearMemInfo();
        pItem->unk_04 = 0;
    }
    pScale = fn_80220D34();
    Align = (Uint16)pText->Flags & 0xF0;
    Scale = 1.0f / 255.0f;
    FontClearRenderFlags(0xF0);
    FontSetRenderFlags(Align);
    Color0 = pText->unk_18;
    Color1 = pText->unk_1C;
    if (pText->unk_05 != -1 && pText->unk_04 != -1) {
        pPalette = (Palette_80220B4C *)fn_80220B4C(pText->unk_05, pText->unk_04);
        if (pPalette != NULL) {
            ClampIndex(&Color0, pPalette);
            ClampIndex(&Color1, pPalette);
            Color0 = pPalette->Colors[Color0.c[0]];
            Color1 = pPalette->Colors[Color1.c[0]];
        }
    }
    Color.r = Scale * (Color0.c[0] + pScale->unk_00[4]) * pScale->unk_00[0];
    Color.g = Scale * (Color0.c[1] + pScale->unk_00[5]) * pScale->unk_00[1];
    Color.b = Scale * (Color0.c[2] + pScale->unk_00[6]) * pScale->unk_00[2];
    Color.a = Scale * (Color0.a + pScale->unk_00[7]) * pScale->unk_00[3];
    FontSetRenderColor(0, Color);
    if (pText->Flags & 0x50) {
        Color.r = Scale * (Color1.c[0] + pScale->unk_00[4]) * pScale->unk_00[0];
        Color.g = Scale * (Color1.c[1] + pScale->unk_00[5]) * pScale->unk_00[1];
        Color.b = Scale * (Color1.c[2] + pScale->unk_00[6]) * pScale->unk_00[2];
        Color.a = Scale * (Color1.a + pScale->unk_00[7]) * pScale->unk_00[3];
        FontSetRenderColor(1, Color);
        FontSetShadowOffset(pText->unk_0C[0], pText->unk_0C[1], pText->unk_0C[2]);
    }
    if (fn_80220CE4() != 2) {
        FontLLRenderBegin();
        fn_80220CDC(2);
    }
    fn_80220CFC(2);
    if (pText->Flags & 0x8000) {
        fn_80221DB0(pText);
    }
    Pos[0] = pText->unk_06;
    Pos[1] = pText->unk_08;
    Pos[2] = pText->unk_0A;
    if (pText->Flags & 0x100) {
        if (pText->Flags & 1) {
            Pos[0] += pText->unk_14 >> 1;
        } else if (pText->Flags & 2) {
            Pos[0] += pText->unk_14;
        }
    }
    Bottom = pText->unk_16 + Pos[1];
    LineHeight = FontGetDescent(pItem->pFont);
    for (Line = pText->unk_10;
         Line < pText->NumRanges && (!(pText->Flags & 0x200) || Pos[1] + LineHeight <= Bottom); Line++) {
        pRange = fn_80221D30(pText, Line);
        pString = pText->pBuffer->pText;
        pLine = pString + pRange->unk_00;
        Saved = pString[pRange->unk_02];
        pString[pRange->unk_02] = '\0';
        FontLLRenderText(pItem->pFont, pLine, pText->Flags & 0xF, 0.0f, Pos);
        pText->pBuffer->pText[pRange->unk_02] = Saved;
        Pos[1] += LineHeight;
    }
}

void fn_80222E0C(Text_80221BF0 *pText)
{
    fn_80221D5C(pText);
    UIGLibraryUnLoadItem(UIGLibraryGetGlobal(1), pText->unk_03, pText->unk_02);
}

void fn_80222E54(Buffer_80222E54 *pDst, Buffer_80222E54 *pSrc)
{
    char *pText = pSrc->pText;
    char *pDstText = pDst->pText;
    Uint32 Size = pDst->Size;
    Uint32 Length;

    if (Size + 1 < (Length = strlen(pText) + 1)) {
        memcpy(pDstText, pText, Size);
    } else {
        memcpy(pDstText, pText, Length);
    }
}
