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

/* Partial source for the engine range 0x80221BF0-0x80225D90 (neutral file
   name). Functions without a body here keep their original bytes. */

extern void *memset();
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

typedef void Callback_8022482C(Node_80223874 *pNode, Int32 Index, Float32 *pCoord);

extern GXColor lbl_803EBF68;
extern GXColor lbl_803EBF6C;
extern GXColor lbl_803EBF70;
extern GXColor lbl_803EBF74;
extern GXLightObj lbl_803E9880;
extern Range_80221D30 lbl_8039F9B8[];
extern Float32 lbl_802F9FE0[4][4];
extern Float32 lbl_803A0400[][2];
extern GXColor lbl_803A1400[];


void TMRenderReset(void);
void fn_801CE910(void);
void GXLoadLightObjImm(GXLightObj *pLight, GXLightID Light);
int fn_801CCDA4(const char *pName, int mode);
int fn_801CCE10(int handle);
int fn_801CCE60(void *pFile, int id);
int fn_801CD07C(int id);
int fn_801CD244(Font_801CCA64 *pFont);
int fn_801CD63C(Font_801CCA64 *pFont, const char *pText, unsigned int flags);
int fn_801CD750(Font_801CCA64 *pFont, unsigned char c);
int fn_801CD790(Font_801CCA64 *pFont);
int ResGetNumResources(ResFile_t *pRes);
unsigned char SndEnabled(void);
struct StreamTap_801F5DA4 *fn_801F687C(int numRequests, int numFilters, int numTaps, void *pMem,
                                       int memSize);
void fn_801F6AC8(struct StreamTap_801F5DA4 *h, int index, unsigned int mask, unsigned int value,
                 int tap);
void fn_801F6B84(struct StreamTap_801F5DA4 *h);
struct StreamTap_801F5DA4 *fn_801F6CE8(struct StreamTap_801F5DA4 *h, int tap);
int fn_801F6D54(struct StreamTap_801F5DA4 *h, SndFileDesc_t *pFile, int offset,
                unsigned int endMarker);
int fn_801DC86C(Uint8 *pY, Uint8 *pU, Uint8 *pV, Int32 a, Int32 b, Int32 c, void *pDst,
                 Int32 Stride, Int32 d);

void fn_80225958(Node_80223874 *pNode, Int32 Item);
void fn_8022482C(Node_80223874 *pNode, Float32 (*pCoords)[2], GXColor *pColors, Int32 *pSize,
                 Int32 Count, Callback_8022482C *pVertex, Callback_8022482C *pEnd);
void fn_80225AAC(Node_80223874 *pNode, Int32 a, Int32 Item);
void fn_80225B50(Uint32 Flags);
void fn_80225CBC(Node_80223874 *pNode, Int32 Index, Float32 *pCoord);
void fn_80225D8C(Node_80223874 *pNode, Int32 Index, Float32 *pCoord);
void fn_80221D5C(Text_80221BF0 *pText);
Range_80221D30 *fn_80221D30(Text_80221BF0 *pText, Uint8 Index);
void fn_80221DB0(Text_80221BF0 *pText);
void fn_80223AA0(Node_80223874 *pNode);
void fn_80223AD0(Node_80223874 *pNode);
void fn_80223B00(Node_80223874 *pNode, Int32 a);
void fn_80223C4C(void);
void fn_80225928(Node_80223874 *pNode);
void fn_802258F8(Node_80223874 *pNode);
void fn_80225AE4(void);

void fn_80221BF0(Text_80221BF0 *pText, Int32 Offset, Int32 *pA, Int32 *pB)
{
    Font_801CCA64 **ppFont;
    Range_80221D30 *pRange = NULL;
    Uint32 Length;
    Int32 i;
    Int32 j;
    Int32 End;

    ppFont = (Font_801CCA64 **)fn_8021E688(fn_8021EA44(1), pText->unk_03, pText->unk_02);
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
    ppFont = (Font_801CCA64 **)fn_8021E688(fn_8021EA44(1), pText->unk_03, pText->unk_02);
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
        fn_8021EF04(pText->unk_03, pText->unk_02);
        pText->u.pRanges = fn_801D2B7C(NumLines * sizeof(Range_80221D30), 0, 0);
        fn_8021EF34();
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
    fn_8021E2B4(fn_8021EA44(1), pText->unk_03, pText->unk_02);
    fn_80221DB0(pText);
}

void fn_80222E0C(Text_80221BF0 *pText)
{
    fn_80221D5C(pText);
    fn_8021E72C(fn_8021EA44(1), pText->unk_03, pText->unk_02);
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

void fn_80223874(Node_80223874 *pNode)
{
    Object_8021E688 *pObject;
    Int32 Item = 0;

    if ((pNode->Flags & 2) && pNode->unk_06 != -1 && pNode->unk_04 != -1) {
        pObject = fn_8021EA44(1);
        if (fn_8021E924(pObject, pNode->unk_06) & 2) {
            fn_80226320(pObject, pNode->unk_06, pNode->unk_04);
        }
        if (pNode->unk_0C != -1 && pNode->unk_0E != -1 &&
            fn_8021EE10(pObject, pNode->unk_06, pNode->unk_04) == 0) {
            fn_802213F8(pObject, &pNode->unk_06, &pNode->unk_04, pNode->unk_0E, pNode->unk_0C);
            pNode->unk_0C = -1;
            pNode->unk_0E = -1;
        }
        Item = fn_8021EA54(pObject, pNode->unk_06, pNode->unk_04);
    }
    if (Item != 0 && (pNode->Flags & 0x10) && pNode->unk_08 != -1 && pNode->unk_0A != -1) {
        fn_80220C4C(pNode->unk_0A, pNode->unk_08, Item);
    }
    fn_80223B00(pNode, Item);
    if (Item != 0 && (pNode->Flags & 0x10) && pNode->unk_08 != -1 && pNode->unk_0A != -1) {
        fn_80220CA4(pNode->unk_0A, pNode->unk_08, Item);
    }
}

void fn_802239D0(Node_80223874 *pNode)
{
    Object_8021E688 *pObject;

    if (pNode->Flags & 2) {
        pObject = fn_8021EA44(1);
        if (pNode->unk_06 != -1 && pNode->unk_04 != -1) {
            fn_8021E2B4(pObject, pNode->unk_06, pNode->unk_04);
        }
    }
    pNode->unk_0C = pNode->unk_04;
    pNode->unk_0E = pNode->unk_06;
    fn_80223AA0(pNode);
}

void fn_80223A40(Node_80223874 *pNode)
{
    Object_8021E688 *pObject;

    if (pNode->Flags & 2) {
        pObject = fn_8021EA44(1);
        if (pNode->unk_06 != -1 && pNode->unk_04 != -1) {
            fn_8021E72C(pObject, pNode->unk_06, pNode->unk_04);
        }
    }
    fn_80223AD0(pNode);
}

void fn_80223AA0(Node_80223874 *pNode)
{
    if (pNode->Flags & 0x8000) {
        fn_802260B0(&pNode->u.List);
    }
}

void fn_80223AD0(Node_80223874 *pNode)
{
    if (pNode->Flags & 0x8000) {
        fn_802260C0(&pNode->u.List);
    }
}

void fn_80223C4C(void)
{
    Color_80223C4C *pColor = fn_80220D34();
    GXColor MatColor = pColor->unk_20;
    GXColor LightColor = pColor->unk_24;

    GXSetChanMatColor(GX_COLOR0A0, MatColor);
    GXInitLightColor(&lbl_803E9880, LightColor);
    GXLoadLightObjImm(&lbl_803E9880, GX_LIGHT7);
    lbl_803EBF68 = MatColor;
    lbl_803EBF6C = LightColor;
}

void fn_80223CB8(Uint32 Flags)
{
    Int32 bColor = 1;
    Int32 bTex;

    if ((Flags & 3) == 2) {
        bColor = 0;
    }
    TMRenderReset();
    bTex = Flags & 2;
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    fn_802218D4(bColor);
    fn_80221924(bTex);
    fn_80223C4C();
    if (Flags & 0x8000) {
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 4);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_S16, 8);
    } else {
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    }
    GXSetCullMode((Flags & 4) ? GX_CULL_BACK : GX_CULL_NONE);
    GXLoadPosMtxImm((f32 (*)[4])fn_801D0444(), GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetZCompLoc(GX_FALSE);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_GREATER, 0);
}

void fn_8022479C(Node_80223874 *pNode)
{
    Object_8021E688 *pObject;

    if (pNode->Flags & 4) {
        pObject = fn_8021EA44(1);
        if (pNode->unk_06 != -1 && pNode->unk_04 != -1) {
            fn_8021E2B4(pObject, pNode->unk_06, pNode->unk_04);
        }
    }
    pNode->unk_0C = pNode->unk_04;
    pNode->unk_0E = pNode->unk_06;
    fn_80225928(pNode);
}

void fn_8022480C(Node_80223874 *pNode)
{
    fn_802258F8(pNode);
}

void fn_802254F8(Node_80223874 *pNode)
{
    Object_8021E688 *pObject;
    Int32 Item = 0;

    if ((pNode->Flags & 4) && pNode->unk_06 != -1 && pNode->unk_04 != -1) {
        pObject = fn_8021EA44(1);
        if (fn_8021E924(pObject, pNode->unk_06) & 2) {
            fn_80226320(pObject, pNode->unk_06, pNode->unk_04);
        }
        if (pNode->unk_0C != -1 && pNode->unk_0E != -1 &&
            fn_8021EE10(pObject, pNode->unk_06, pNode->unk_04) == 0) {
            fn_802213F8(pObject, &pNode->unk_06, &pNode->unk_04, pNode->unk_0E, pNode->unk_0C);
            pNode->unk_0C = -1;
            pNode->unk_0E = -1;
        }
        Item = fn_8021EA54(pObject, pNode->unk_06, pNode->unk_04);
    }
    if (Item != 0 && (pNode->Flags & 0x100) && pNode->unk_08 != -1 && pNode->unk_0A != -1) {
        fn_80220C4C(pNode->unk_0A, pNode->unk_08, Item);
    }
    fn_80225958(pNode, Item);
    if (Item != 0 && (pNode->Flags & 0x100) && pNode->unk_08 != -1 && pNode->unk_0A != -1) {
        fn_80220CA4(pNode->unk_0A, pNode->unk_08, Item);
    }
}

void fn_80225654(Node_80223874 *pNode, Uint32 Action, Int32 a, void *pData)
{
    Int16 First;
    Int16 Second;
    Int16 Value;

    switch (Action) {
    case -1:
        fn_8022479C(pNode);
        break;
    case -2:
        fn_802254F8(pNode);
        break;
    case -3:
        fn_8022480C(pNode);
        break;
    case -4:
        break;
    }
    if (!(pNode->Flags & 0x8000)) {
        switch (Action) {
        case 0:
            pNode->u.t.unk_3C[0] = ((Float32 *)pData)[0];
            pNode->u.t.unk_3C[1] = ((Float32 *)pData)[1];
            break;
        case 1:
            pNode->u.t.unk_24[0] = ((Float32 *)pData)[0];
            pNode->u.t.unk_24[1] = ((Float32 *)pData)[1];
            break;
        case 2:
            pNode->u.t.unk_2C[0] = ((Float32 *)pData)[0];
            pNode->u.t.unk_2C[1] = ((Float32 *)pData)[1];
            break;
        case 3:
            pNode->u.t.unk_34 = ((Float32 *)pData)[0];
            break;
        case 4:
            pNode->u.t.unk_38 = ((Float32 *)pData)[0];
            break;
        case 5:
            pNode->u.t.unk_1C[0] = ((Float32 *)pData)[0];
            pNode->u.t.unk_1C[1] = ((Float32 *)pData)[1];
            break;
        case 6:
            pNode->u.t.unk_14[0] = ((Int32 *)pData)[0];
            pNode->u.t.unk_14[1] = ((Int32 *)pData)[1];
            pNode->u.t.unk_14[2] = ((Int32 *)pData)[2];
            pNode->u.t.unk_14[3] = ((Int32 *)pData)[3];
            break;
        case 7:
            pNode->u.t.unk_18[0] = ((Int32 *)pData)[0];
            pNode->u.t.unk_18[1] = ((Int32 *)pData)[1];
            pNode->u.t.unk_18[2] = ((Int32 *)pData)[2];
            pNode->u.t.unk_18[3] = ((Int32 *)pData)[3];
            break;
        case 8:
            pNode->u.t.unk_10 = ((Int32 *)pData)[0];
            break;
        case 9:
            Value = ((Int16 *)pData)[0];
            pNode->unk_0E = Value;
            pNode->unk_0C = ((Int16 *)pData)[1];
            if (Value == 0) {
                pNode->unk_0E = pNode->unk_06;
            }
            if (pNode->unk_0E == -1) {
                pNode->unk_0E = pNode->unk_06;
            }
            if (pNode->unk_0C == -1) {
                pNode->unk_0C = pNode->unk_04;
            }
            if (pNode->unk_0C != pNode->unk_04 || pNode->unk_0E != pNode->unk_06) {
                fn_802213F8(fn_8021EA44(1), &pNode->unk_06, &pNode->unk_04, pNode->unk_0E,
                            pNode->unk_0C);
            }
            break;
        case 10:
            if (pNode->unk_02 != ((Int32 *)pData)[0]) {
                fn_80221528(fn_8021EA44(1), pNode->unk_06, pNode->unk_04,
                            (Int16)((Int32 *)pData)[0]);
            }
            break;
        case 11:
            First = ((Int16 *)pData)[0];
            Second = ((Int16 *)pData)[1];
            if ((pNode->Flags & 0x100) || (First != -1 && Second != -1)) {
                pNode->unk_08 = Second;
                pNode->unk_0A = First;
            }
            break;
        case 12:
            pNode->u.t.unk_14[0] = ((Int32 *)pData)[0];
            break;
        case 13:
            pNode->u.t.unk_18[0] = ((Int32 *)pData)[0];
            break;
        }
    }
}

void fn_802258F8(Node_80223874 *pNode)
{
    if (pNode->Flags & 0x8000) {
        fn_802260C0(&pNode->u.List);
    }
}

void fn_80225928(Node_80223874 *pNode)
{
    if (pNode->Flags & 0x8000) {
        fn_802260B0(&pNode->u.List);
    }
}

void fn_80225958(Node_80223874 *pNode, Int32 Item)
{
    Int32 bTex = 0;
    Int32 Count;
    Int32 Size;

    fn_80225B50(pNode->Flags);
    if (pNode->Flags & 4) {
        if (Item == 0) {
            return;
        }
        lbl_802F9FE0[0][0] = ((Node_802215F0 *)Item)->unk_30;
        lbl_802F9FE0[1][1] = ((Node_802215F0 *)Item)->unk_34;
        GXLoadTexMtxImm(lbl_802F9FE0, GX_TEXMTX0, GX_MTX2x4);
        fn_80225AAC(pNode, 0, Item);
        bTex = fn_8022179C(Item);
    }
    if (pNode->Flags & 0x8000) {
        fn_802260D0(&pNode->u.List);
    } else {
        Size = 512;
        if (!(pNode->Flags & 4) && !(pNode->Flags & 1)) {
            Count = pNode->u.t.unk_10 + 2;
            GXBegin(GX_TRIANGLEFAN, GX_VTXFMT0, Count);
        } else {
            Count = pNode->u.t.unk_10 * 4;
            GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, Count);
        }
        fn_8022482C(pNode, lbl_803A0400, lbl_803A1400, &Size, Count, fn_80225CBC, fn_80225D8C);
    }
    GXSetCullMode(GX_CULL_NONE);
    if (bTex) {
        GXSetNumIndStages(0);
        GXSetTevDirect(GX_TEVSTAGE0);
        GXSetTexCoordScaleManually(GX_TEXCOORD0, GX_FALSE, 0, 0);
    }
}

void fn_80225AAC(Node_80223874 *pNode, Int32 a, Int32 Item)
{
    Int32 First = 0;
    Int32 Second = 0;

    if (a != 0) {
        First = 1;
        Second = 1;
    }
    fn_802219F0(First, Second);
}

void fn_80225AE4(void)
{
    Color_80223C4C *pColor = fn_80220D34();
    GXColor MatColor = pColor->unk_20;
    GXColor LightColor = pColor->unk_24;

    GXSetChanMatColor(GX_COLOR0A0, MatColor);
    GXInitLightColor(&lbl_803E9880, LightColor);
    GXLoadLightObjImm(&lbl_803E9880, GX_LIGHT7);
    lbl_803EBF70 = MatColor;
    lbl_803EBF74 = LightColor;
}

void fn_80225B50(Uint32 Flags)
{
    Int32 bColor = 1;
    Int32 bTex;

    if ((Flags & 6) == 4) {
        bColor = 0;
    }
    TMRenderReset();
    bTex = Flags & 4;
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    fn_802218D4(bColor);
    fn_80221924(bTex);
    fn_80225AE4();
    if (Flags & 0x8000) {
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 4);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_S16, 8);
    } else {
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    }
    GXSetCullMode(!(Flags & 8) ? GX_CULL_BACK : GX_CULL_NONE);
    GXLoadPosMtxImm((f32 (*)[4])fn_801D0444(), GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetZCompLoc(GX_FALSE);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_GREATER, 0);
}

void fn_80225D8C(Node_80223874 *pNode, Int32 Index, Float32 *pCoord)
{
}
