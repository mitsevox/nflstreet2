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

/* Only the accessed members are declared; the size is not established. */
typedef struct Text_80221BF0 {
    Int16 Flags;    /* 0x00 */
    signed char unk_02; /* 0x02 */
    signed char unk_03; /* 0x03 */
    Uint8 unk_04[0x0B];
    Uint8 NumRanges; /* 0x0F */
    Uint8 unk_10;   /* 0x10 */
    Uint8 unk_11[0x03];
    Int16 unk_14;   /* 0x14 */
    Int16 unk_16;   /* 0x16 */
    Uint8 unk_18[0x08];
    Buffer_80222E54 *pBuffer; /* 0x20 */
    union {
        Range_80221D30 *pRanges;
        Range_80221D30 Ranges[1];
    } u;            /* 0x24: inline when NumRanges is at most 1 */
} Text_80221BF0;

extern Range_80221D30 lbl_8039F9B8[];

int fn_801CD63C(Font_801CCA64 *pFont, const char *pText, unsigned int flags);
int fn_801CD750(Font_801CCA64 *pFont, unsigned char c);
int fn_801CD790(Font_801CCA64 *pFont);

void fn_80221D5C(Text_80221BF0 *pText);
Range_80221D30 *fn_80221D30(Text_80221BF0 *pText, Uint8 Index);
void fn_80221DB0(Text_80221BF0 *pText);

void fn_80221BF0(Text_80221BF0 *pText, Int32 Offset, Int32 *pA, Int32 *pB)
{
    Font_801CCA64 **ppFont;
    Range_80221D30 *pRange = NULL;
    Uint32 Length;
    Int32 i;
    Int32 j;
    Int32 End;

    ppFont = (Font_801CCA64 **)UIGLibraryGetItemData(UIGLibraryGetGlobal(1), pText->unk_03, pText->unk_02);
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
        if (pRange->unk_00 <= Offset) {
            break;
        }
    }
    if (i >= 0) {
        *pB = fn_801CD790(*ppFont) * (i - pText->unk_10);
        *pA = 0;
        End = pRange->unk_02;
        for (j = pRange->unk_00; j < End && j < Offset; j++) {
            *pA += fn_801CD750(*ppFont, pText->pBuffer->pText[j]);
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
    Font_801CCA64 **ppFont;
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
    ppFont = (Font_801CCA64 **)UIGLibraryGetItemData(UIGLibraryGetGlobal(1), pText->unk_03, pText->unk_02);
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
                    CharWidth = fn_801CD750(*ppFont, ch);
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
                            Width -= fn_801CD750(*ppFont, pString[i]);
                        }
                        lbl_8039F9B8[NumLines].unk_00 = i;
                        lbl_8039F9B8[NumLines].unk_02 = Pos;
                    } else if (pText->Flags & 1) {
                        LastSpace = LineStart;
                        for (i = Pos - 1; LastSpace < i && Width > pText->unk_14;) {
                            Width -= fn_801CD750(*ppFont, pString[i--]);
                            if (LastSpace < i && Width > pText->unk_14) {
                                Width -= fn_801CD750(*ppFont, pString[LastSpace++]);
                            }
                        }
                        lbl_8039F9B8[NumLines].unk_00 = LastSpace;
                        lbl_8039F9B8[NumLines].unk_02 = i + 1;
                    } else {
                        for (i = Pos - 1; Width > pText->unk_14 && i > 1;) {
                            Width -= fn_801CD750(*ppFont, pString[i--]);
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
                Width = fn_801CD63C(*ppFont, &pString[LineStart], pText->Flags);
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
        pText->unk_16 = pText->NumRanges * fn_801CD790(*ppFont);
    }
    pText->Flags &= 0x7FFF;
}

void fn_80222764(Text_80221BF0 *pText)
{
    UIGLibraryLoadItem(UIGLibraryGetGlobal(1), pText->unk_03, pText->unk_02);
    fn_80221DB0(pText);
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
