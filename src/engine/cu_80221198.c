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
#include "engine/Info_801D86B4.h"
#include "engine/cu_801C2EB4.h"
#include "engine/cu_801CCA64.h"
#include "engine/cu_801D03D0.h"
#include "engine/cu_8021A438.h"
#include "engine/cu_80227F14.h"
#include "engine/sound.h"
#include "engine/texture.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801EEB44.h"

/* Partial source for the engine range 0x80221198-0x80226F9C (neutral file
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

/* 8-byte item allocated by fn_80225E64. */
typedef struct Item_80225E64 {
    Font_801CCA64 *pFont; /* 0x00 */
    Int32 unk_04;   /* 0x04 */
} Item_80225E64;

/* 60-byte member at +0x48 of Object_802268D4. */
typedef struct Sub_802268D4 {
    Int32 unk_00;   /* 0x00 */
    Int32 unk_04;   /* 0x04 */
    void *unk_08;   /* 0x08 */
    Uint8 unk_0C[0x04];
    struct StreamTap_801F5DA4 *pStream; /* 0x10 */
    Uint16 unk_14;  /* 0x14 */
    Int16 unk_16;   /* 0x16 */
    void *unk_18;   /* 0x18 */
    void *unk_1C;   /* 0x1C */
    struct StreamTap_801F5DA4 *pTap; /* 0x20: -1 when none */
    Info_801D86B4 Info; /* 0x24 */
    Int32 unk_30;   /* 0x30 */
    Int32 unk_34;   /* 0x34 */
    struct Frame_801D86B4 *pFrame; /* 0x38 */
} Sub_802268D4;

/* 132-byte object allocated by fn_802268D4. */
typedef struct Object_802268D4 {
    Node_802215F0 Node; /* 0x00 */
    Int32 unk_3C;   /* 0x3C */
    Int32 unk_40;   /* 0x40 */
    Int16 unk_44;   /* 0x44 */
    Uint16 Flags;   /* 0x46 */
    Sub_802268D4 Sub; /* 0x48 */
} Object_802268D4;

typedef void Callback_803EBF60(Int32 a, Uint32 b, void *p);
typedef void Callback_8022482C(Node_80223874 *pNode, Int32 Index, Float32 *pCoord);

extern Callback_803EBF60 *lbl_803EBF60;
extern GXColor lbl_803EBF68;
extern GXColor lbl_803EBF6C;
extern GXColor lbl_803EBF70;
extern GXColor lbl_803EBF74;
extern Uint8 lbl_803EBF78;
extern Uint8 lbl_803EBF79;
extern Uint8 lbl_803EBF7A;
extern Int32 lbl_803EBF7C;
extern void *lbl_803EBF80;
extern Uint8 lbl_803EBF84;
extern Uint8 lbl_803EBF85;
extern GXLightObj lbl_803E9880;
extern Range_80221D30 lbl_8039F9B8[];
extern Float32 lbl_802F9FE0[3][4];
extern Float32 lbl_803A0400[][2];
extern GXColor lbl_803A1400[];

void fn_80210388(void);
void fn_80221198(void *p);
void fn_801CE910(void);
void fn_8024F9EC(GXLightObj *pLight, GXLightID Light);
int fn_801CCDA4(const char *pName, int mode);
int fn_801CCE10(int handle);
int fn_801CCE60(void *pFile, int id);
int fn_801CD07C(int id);
int fn_801CD244(Font_801CCA64 *pFont);
int fn_801CD63C(Font_801CCA64 *pFont, const char *pText, unsigned int flags);
int fn_801CD750(Font_801CCA64 *pFont, unsigned char c);
int fn_801CD790(Font_801CCA64 *pFont);
int fn_801F0D34(Res_801EDC2C *pRes);
unsigned char fn_801F3E28(void);
struct StreamTap_801F5DA4 *fn_801F687C(int numRequests, int numFilters, int numTaps, void *pMem,
                                       int memSize);
void fn_801F6AC8(struct StreamTap_801F5DA4 *h, int index, unsigned int mask, unsigned int value,
                 int tap);
void fn_801F6B84(struct StreamTap_801F5DA4 *h);
struct StreamTap_801F5DA4 *fn_801F6CE8(struct StreamTap_801F5DA4 *h, int tap);
int fn_801F6D54(struct StreamTap_801F5DA4 *h, StreamFile_801F6D54 *pFile, int offset,
                unsigned int endMarker);
int fn_801DC86C(Uint8 *pY, Uint8 *pU, Uint8 *pV, Int32 a, Int32 b, Int32 c, void *pDst,
                 Int32 Stride, Int32 d);

void fn_80221294(void *p);
void fn_802215EC(Int32 a, Int32 b);
void fn_8022623C(Object_8021E688 *pObject, Int32 a, Int32 b, Int32 c, Int32 d);
void fn_80225958(Node_80223874 *pNode, Int32 Item);
void fn_8022482C(Node_80223874 *pNode, Float32 (*pCoords)[2], GXColor *pColors, Int32 *pSize,
                 Int32 Count, Callback_8022482C *pVertex, Callback_8022482C *pEnd);
void fn_80225AAC(Node_80223874 *pNode, Int32 a, Int32 Item);
void fn_80225B50(Uint32 Flags);
void fn_80225CBC(Node_80223874 *pNode, Int32 Index, Float32 *pCoord);
void fn_80225D8C(Node_80223874 *pNode, Int32 Index, Float32 *pCoord);
Node_802215F0 *fn_802215F0(Int32 a, Int32 b, Int32 c, Int32 d, Int32 e);
void fn_80221738(Int32 a, Int32 b, Node_802215F0 *pNode);
unsigned short *fn_80221BD8(Node_802215F0 *pNode);
void fn_80221BE0(Node_802215F0 *pNode, unsigned short *pPalette);
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
Uint8 fn_80226384(void);
Int32 fn_8022638C(void);
Int32 fn_802263D4(void);
void fn_80226498(Object_8021E688 *pObject, Object_802268D4 *pMovie);
void fn_802264A4(Sub_802268D4 *pSub);
void fn_802264E8(Sub_802268D4 *pSub, Int32 a);
Int32 fn_80226570(Object_8021E688 *pObject, Object_802268D4 *pMovie, Sub_802268D4 *pSub);
void fn_8022666C(Object_8021E688 *pObject, Object_802268D4 *pMovie);
void fn_802267D0(void);
void fn_802267D4(void);
void fn_802267D8(Object_802268D4 *pMovie, Int32 a, Int32 b);
Object_802268D4 *fn_802268D4(Object_8021E688 *pObject, Int16 a, Int16 b);
void fn_802269C8(Object_8021E688 *pObject, Object_802268D4 *pMovie);
void fn_80226A68(Object_8021E688 *pObject, Object_802268D4 *pMovie);
void fn_80226C40(Object_8021E688 *pObject, Object_802268D4 *pMovie);
void fn_80226D20(Int32 Width, Int32 Height, Uint8 *pData);
void fn_80226E4C(Uint8 *pSrc, Int32 x, Int32 y, Uint8 *pTile, Int32 Width, Int32 Height);
void fn_80226F34(Object_8021E688 *pObject, Int16 a, Int16 b, Object_802268D4 *pMovie);

void fn_80221294(void *p)
{
    fn_801D0470(fn_80228668());
    fn_801D0544();
    fn_80221118();
    fn_80220CFC(0);
}

void fn_802212C8(Uint32 Type, void *p)
{
    switch (Type) {
    case 0:
        break;
    case 1:
        fn_80221198(p);
        break;
    case 2:
        fn_80221294(p);
        break;
    }
}

void fn_80221314(Object_8021E688 *pObject, Int16 a, Int16 b)
{
    Node_802215F0 *pNode = (Node_802215F0 *)fn_8021E688(pObject, a, b);

    if (pNode != NULL) {
        fn_80221738(a, b, pNode);
        fn_8021E6A8(pObject, a, b, 0);
    }
}

void fn_80221374(Object_8021E688 *pObject, Int16 a, Int32 b, Int32 c)
{
    Int32 Item = fn_8021E688(pObject, a, b);

    if (c != 0 && Item == 0) {
        Item = (Int32)fn_802215F0(a, b, c, 0, fn_8021E93C(pObject, a));
        fn_8021E6A8(pObject, a, b, Item);
    }
}

void fn_802213F8(Object_8021E688 *pObject, Int16 *pA, Int16 *pB, Int16 c, Int16 d)
{
    if (*pA == c && *pB == d) {
        return;
    }
    if (*pA != -1 && *pB != -1 && c != -1 && d != -1) {
        if ((fn_8021E924(pObject, *pA) & 2) && (fn_8021E924(pObject, c) & 2)) {
            fn_8022623C(pObject, c, d, *pA, *pB);
        } else {
            fn_801CE910();
            fn_8021E72C(pObject, *pA, *pB);
            fn_8021E2B4(pObject, c, d);
        }
    } else if (*pA != -1 && *pB != -1) {
        fn_8021E72C(pObject, *pA, *pB);
    } else if (c != -1 && d != -1) {
        fn_8021E2B4(pObject, c, d);
    }
    *pA = c;
    *pB = d;
}

void fn_80221528(Object_8021E688 *pObject, Int32 a, Int32 b, Int32 c)
{
    if (a != -1 && b != -1) {
        fn_802215EC(c, fn_8021E688(pObject, a, b));
    }
}

unsigned short *fn_80221570(Node_802215F0 *pNode)
{
    return fn_80221BD8(pNode);
}

void fn_80221590(Node_802215F0 *pNode, unsigned short *pPalette)
{
    fn_80221BE0(pNode, pPalette);
}

Uint32 fn_802215B0(Uint32 x)
{
    Int32 i = 0;

    while (x & (x - 1)) {
        x = (x + (1 << i) - 1) & -(1 << i);
        i++;
    }
    return x;
}

void fn_802215EC(Int32 a, Int32 b)
{
}

void fn_80221738(Int32 a, Int32 b, Node_802215F0 *pNode)
{
    pNode->unk_20 = -1;
    if (pNode->unk_24 != -1) {
        pNode->unk_24 = -1;
    }
    fn_8020E258(&pNode->Texture);
    memset(pNode, 0, sizeof(Node_802215F0));
    fn_801D2BD0(pNode);
}

void fn_802218D4(Int32 a)
{
    GXSetNumChans(1);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetChanCtrl(GX_COLOR0A0, GX_TRUE, GX_SRC_VTX, GX_SRC_REG, GX_LIGHT7, GX_DF_NONE, GX_AF_NONE);
}

void fn_80221924(Int32 a)
{
    if (a != 0) {
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    } else {
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
        GXSetNumIndStages(0);
        GXSetTevDirect(GX_TEVSTAGE0);
        GXSetNumTexGens(0);
        GXSetVtxDesc(GX_VA_TEX0, GX_NONE);
    }
}

void *fn_80221BAC(Object_8021E688 *pObject, Int32 a, Int32 b)
{
    void *p = (void *)fn_8021E688(pObject, a, b);

    if (p != NULL) {
        return p;
    }
    return NULL;
}

unsigned short *fn_80221BD8(Node_802215F0 *pNode)
{
    return pNode->Texture.mpPalette;
}

void fn_80221BE0(Node_802215F0 *pNode, unsigned short *pPalette)
{
    pNode->Texture.mpPalette = pPalette;
}

void fn_80221BE8(Callback_803EBF60 *pCallback)
{
    lbl_803EBF60 = pCallback;
}

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
    Length = fn_801C3180(pText->pBuffer->pText);
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
    Length = fn_801C3180(pString);
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

    if (Size + 1 < (Length = fn_801C3180(pText) + 1)) {
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
    fn_8024F9EC(&lbl_803E9880, GX_LIGHT7);
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
    fn_80210388();
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

void fn_80225654(Node_80223874 *pNode, Uint32 Msg, Int32 a, void *pData)
{
    Int16 First;
    Int16 Second;

    switch (Msg) {
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
        switch (Msg) {
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
            Second = ((Int16 *)pData)[0];
            pNode->unk_0E = Second;
            pNode->unk_0C = ((Int16 *)pData)[1];
            if (Second == 0) {
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
    fn_8024F9EC(&lbl_803E9880, GX_LIGHT7);
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
    fn_80210388();
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

void fn_80225D90(Object_8021E688 *pObject, Int16 a)
{
    int Handle;

    if (a != -1 && fn_8021EB40(pObject, a) == 0) {
        Handle = fn_801CCDA4((const char *)fn_8021E970(pObject, a), 44);
        fn_8021EB2C(pObject, a, Handle);
        fn_8021E244(pObject, a, fn_801F0D34((Res_801EDC2C *)Handle));
    }
}

void fn_80225E10(Object_8021E688 *pObject, Int16 a)
{
    Int32 Handle;

    if (a != -1) {
        Handle = fn_8021EB40(pObject, a);
        if (Handle != 0) {
            fn_801CCE10(Handle);
            fn_8021EB2C(pObject, a, 0);
        }
    }
}

void fn_80225E64(Object_8021E688 *pObject, Int16 a, Int16 b, Int32 c)
{
    Int32 Handle;
    Item_80225E64 *pItem;

    if (a != -1 && b != -1) {
        Handle = fn_8021EB40(pObject, a);
        if (Handle != 0 && fn_8021E688(pObject, a, b) == 0) {
            fn_801CCE60((void *)Handle, b);
            pItem = fn_801D2B7C(sizeof(Item_80225E64), 0, 0);
            pItem->pFont = fn_801CD130(b);
            pItem->unk_04 = 1;
            fn_8021E6A8(pObject, a, b, (Int32)pItem);
        }
    }
}

void fn_80225F10(Object_8021E688 *pObject, Int16 a, Int16 b)
{
    Item_80225E64 *pItem;

    if (a != -1 && b != -1) {
        pItem = (Item_80225E64 *)fn_8021E688(pObject, a, b);
        if (pItem != NULL) {
            fn_801CD244(pItem->pFont);
            fn_801CD07C(b);
            fn_8021E6A8(pObject, a, b, 0);
            fn_801D2BD0(pItem);
        }
    }
}

Uint32 fn_80225F88(Object_8021E688 *pObject, Int32 a, Int32 b, const char *pText)
{
    Item_80225E64 *pItem;

    if (a == -1 || b == -1) {
        return 0;
    }
    pItem = (Item_80225E64 *)fn_8021E688(pObject, a, b);
    if (pItem == NULL) {
        fn_8021E2B4(pObject, a, b);
        pItem = (Item_80225E64 *)fn_8021E688(pObject, a, b);
    }
    return fn_801CD63C(pItem->pFont, pText, 0);
}

Font_801CCA64 *fn_8022601C(Object_8021E688 *pObject, Int32 a, Int16 b, Int32 c)
{
    Font_801CCA64 *pResult = NULL;
    Item_80225E64 *pItem;

    fn_8021E2B4(pObject, a, b);
    pItem = (Item_80225E64 *)fn_8021E688(pObject, a, b);
    if (pItem != NULL) {
        pResult = pItem->pFont;
    }
    if (pItem->unk_04 != 0 && c != 0) {
        fn_8021EF04(a, b);
        fn_801CD20C(pResult, 0);
        fn_8021EF34();
        pItem->unk_04 = 0;
    }
    return pResult;
}

void fn_802260B0(DisplayList_802260D0 *pList)
{
    pList->Offset += (Int32)pList;
}

void fn_802260C0(DisplayList_802260D0 *pList)
{
    pList->Offset -= (Int32)pList;
}

void fn_802260D0(DisplayList_802260D0 *pList)
{
    GXCallDisplayList((void *)pList->Offset, pList->Size);
}

void fn_802260F8(Object_8021E688 *pObject, Int32 a)
{
    void *p = fn_801EEB44((const char *)fn_8021E970(pObject, a), 44);

    fn_8021E244(pObject, a, fn_801F0D34(p));
    fn_8021E998(pObject, a, p);
    fn_802267D0();
}

void fn_8022615C(Object_8021E688 *pObject, Int32 a)
{
    void *p = fn_8021E984(pObject, a);

    if (p != NULL) {
        fn_801EEFAC(p);
        fn_802267D4();
    }
}

void fn_8022618C(Object_8021E688 *pObject, Int32 a, Int32 b)
{
    Object_802268D4 *pMovie = (Object_802268D4 *)fn_8021E688(pObject, a, b);

    if (pMovie != NULL && lbl_803EBF78) {
        fn_80226498(pObject, pMovie);
    }
}

void fn_802261D4(Object_8021E688 *pObject, Int32 a, Int32 b)
{
    Object_802268D4 *pMovie = (Object_802268D4 *)fn_8021E688(pObject, a, b);

    if (pMovie == NULL) {
        pMovie = fn_802268D4(pObject, a, b);
        fn_8021E6A8(pObject, a, b, (Int32)pMovie);
        lbl_803EBF78 = 0;
    }
}

void fn_8022623C(Object_8021E688 *pObject, Int32 a, Int32 b, Int32 c, Int32 d)
{
    Object_802268D4 *pMovie;

    if (c == -1) {
        pMovie = NULL;
    } else {
        pMovie = (Object_802268D4 *)fn_8021E688(pObject, c, d);
    }
    if (pMovie != NULL) {
        fn_80226F34(pObject, a, b, pMovie);
    } else {
        fn_802261D4(pObject, a, b);
    }
    lbl_803EBF78 = 0;
}

void fn_802262C4(Object_8021E688 *pObject, Int32 a, Int32 b)
{
    Object_802268D4 *pMovie = (Object_802268D4 *)fn_8021E688(pObject, a, b);

    if (pMovie != NULL) {
        fn_802269C8(pObject, pMovie);
        fn_8021E6A8(pObject, a, b, 0);
    }
}

void fn_80226320(Object_8021E688 *pObject, Int32 a, Int32 b)
{
    Object_802268D4 *pMovie = (Object_802268D4 *)fn_8021E688(pObject, a, b);

    if (pMovie != NULL && lbl_803EBF78) {
        fn_8021EF04(a, b);
        fn_8022666C(pObject, pMovie);
        fn_8021EF34();
    }
}

Uint8 fn_80226384(void)
{
    return lbl_803EBF79;
}

Int32 fn_8022638C(void)
{
    Int32 Result = 0;

    if (lbl_803EBF7A && fn_801F3E28()) {
        Result = 1;
    }
    return Result;
}

Int32 fn_802263D4(void)
{
    return lbl_803EBF7C;
}

void fn_802263DC(Object_8021E688 *pObject, Int32 a, Int32 b)
{
    Object_802268D4 *pMovie = (Object_802268D4 *)fn_8021E688(pObject, a, b);

    if (pMovie != NULL && !lbl_803EBF78) {
        fn_8021EF04(a, b);
        fn_80226A68(pObject, pMovie);
        fn_8021EF34();
        lbl_803EBF78 = 1;
    }
}

void fn_80226448(Object_8021E688 *pObject, Int32 a, Int32 b)
{
    Object_802268D4 *pMovie = (Object_802268D4 *)fn_8021E688(pObject, a, b);

    if (pMovie != NULL && lbl_803EBF78) {
        fn_80226C40(pObject, pMovie);
        lbl_803EBF78 = 0;
    }
}

void fn_80226498(Object_8021E688 *pObject, Object_802268D4 *pMovie)
{
    pMovie->unk_44 = 1;
}

void fn_802264A4(Sub_802268D4 *pSub)
{
    if (pSub->pFrame != NULL) {
        fn_801D9290(&pSub->Info, pSub->pFrame);
        pSub->pFrame = NULL;
    }
}

void fn_802264E8(Sub_802268D4 *pSub, Int32 a)
{
    Uint8 *pY;
    Uint8 *pU;
    Uint8 *pV;

    if (pSub->pFrame != NULL) {
        fn_801D92B8(pSub->pFrame, &pY, &pU, &pV);
        fn_801DC86C(pY, pU, pV, pSub->unk_30, pSub->unk_30, pSub->unk_34, pSub->unk_1C,
                    pSub->unk_00 * 4, a);
        fn_801D9290(&pSub->Info, pSub->pFrame);
        pSub->pFrame = NULL;
    }
}

Int32 fn_80226570(Object_8021E688 *pObject, Object_802268D4 *pMovie, Sub_802268D4 *pSub)
{
    struct Frame_801D86B4 *pFrame = NULL;

    if (pSub->pStream != NULL) {
        if (pSub->pFrame != NULL) {
            fn_801D9290(&pSub->Info, pSub->pFrame);
            pSub->pFrame = NULL;
        }
        pFrame = fn_801D923C(&pSub->Info, fn_801D9224(&pSub->Info));
        pSub->pFrame = pFrame;
        if (pFrame != NULL && pSub->unk_34 == 0 && pSub->unk_30 == 0) {
            fn_801D9320(pFrame, &pSub->unk_30, &pSub->unk_34);
        }
    }
    if (pFrame == NULL) {
        pMovie->Flags |= 2;
        if (pMovie->Flags & 1) {
            fn_80226C40(pObject, pMovie);
            fn_80226A68(pObject, pMovie);
        } else {
            lbl_803EBF85 = 1;
            lbl_803EBF84 = 1;
        }
    }
    return pFrame != NULL;
}

void fn_8022666C(Object_8021E688 *pObject, Object_802268D4 *pMovie)
{
    Sub_802268D4 *pSub;

    if (pMovie->unk_44 != 0) {
        pSub = &pMovie->Sub;
        if (pSub->Info.mpAudio != NULL && pSub->Info.mpVideo != NULL) {
            pMovie->unk_44 = 0;
            pSub->unk_14++;
            if (fn_801D900C(&pSub->Info)) {
                if (pSub->unk_16 != 0) {
                    if (!(fn_801D9230(&pSub->Info) & 1)) {
                        fn_802264A4(pSub);
                        fn_80226570(pObject, pMovie, pSub);
                    } else {
                        fn_802264E8(pSub, 2);
                        if (fn_80226570(pObject, pMovie, pSub)) {
                            fn_802264E8(pSub, 1);
                            fn_80226570(pObject, pMovie, pSub);
                            fn_80226D20(pSub->unk_00, pSub->unk_04, pSub->unk_1C);
                            DCStoreRange(pSub->unk_1C, pSub->unk_00 * pSub->unk_04 * 4);
                        }
                    }
                } else {
                    fn_802264E8(pSub, 0);
                    fn_80226570(pObject, pMovie, pSub);
                    fn_80226D20(pSub->unk_00, pSub->unk_04, pSub->unk_1C);
                    DCStoreRange(pSub->unk_1C, pSub->unk_00 * pSub->unk_04 * 4);
                }
            }
        }
    }
}

void fn_802267D0(void)
{
}

void fn_802267D4(void)
{
}

Object_802268D4 *fn_802268D4(Object_8021E688 *pObject, Int16 a, Int16 b)
{
    Int32 Heap = fn_802263D4();
    Object_802268D4 *pMovie;
    Sub_802268D4 *pSub;

    fn_8021EF04(a, b);
    pMovie = fn_801D2B7C(sizeof(Object_802268D4), 0, 0);
    memset(pMovie, 0, sizeof(Object_802268D4));
    pSub = &pMovie->Sub;
    fn_8021EF34();
    pMovie->Flags = 0;
    pSub->unk_04 = 240;
    pSub->unk_00 = 320;
    pSub->unk_1C = fn_801D2BB0(Heap, 0x4B000, 0, 0);
    memset(pSub->unk_1C, 0, 0x4B000);
    DCStoreRange(pSub->unk_1C, pSub->unk_00 * pSub->unk_04 * 4);
    fn_802267D8(pMovie, 320, 240);
    pMovie->unk_40 = b;
    pMovie->unk_3C = a;
    lbl_803EBF84 = 1;
    return pMovie;
}

void fn_802269C8(Object_8021E688 *pObject, Object_802268D4 *pMovie)
{
    Sub_802268D4 *pSub = &pMovie->Sub;

    fn_80226C40(pObject, pMovie);
    if (lbl_803EBF80 != NULL) {
        fn_801D2BD0(lbl_803EBF80);
        lbl_803EBF80 = NULL;
    }
    if (pSub->unk_08 != NULL) {
        fn_801D2BD0(pSub->unk_08);
        pSub->unk_08 = NULL;
    }
    if (pSub->unk_1C != NULL) {
        fn_801D2BD0(pSub->unk_1C);
        pSub->unk_1C = NULL;
    }
    if (pSub->unk_18 != NULL) {
        fn_801D2BD0(pSub->unk_18);
        pSub->unk_18 = NULL;
    }
    fn_801D2BD0(pMovie);
    lbl_803EBF85 = 1;
}

void fn_80226A68(Object_8021E688 *pObject, Object_802268D4 *pMovie)
{
    Int32 Heap = fn_802263D4();
    Sub_802268D4 *pSub = &pMovie->Sub;
    StreamFile_801F6D54 File;
    Int32 Queued;

    if (pSub->unk_1C == NULL) {
        pSub->unk_1C = fn_801D2BB0(Heap, 0x4B000, 0, 0);
        memset(pSub->unk_1C, 0, 0x4B000);
        DCStoreRange(pSub->unk_1C, pSub->unk_00 * pSub->unk_04 * 4);
    }
    pSub->unk_08 = fn_801D2BB0(Heap, 0x4B000, 0, 0);
    pSub->pStream = fn_801F687C(2, 2, 2, pSub->unk_08, 0x4B000);
    if (fn_8022638C()) {
        pSub->pTap = fn_801F6CE8(pSub->pStream, 2);
        fn_801F6AC8(pSub->pStream, 1, 0xFFFF, 17235, 2);
    } else {
        pSub->pTap = (struct StreamTap_801F5DA4 *)-1;
        fn_801F6AC8(pSub->pStream, 1, 0xFFFF, 17235, -1);
    }
    File.pRes = fn_8021E984(pObject, pMovie->unk_3C);
    File.mIndex = pMovie->unk_40;
    Queued = fn_801F6D54(pSub->pStream, &File, 0, 0);
    fn_801D8A2C(&pSub->Info, pSub->pStream);
    pSub->unk_30 = 0;
    pSub->unk_34 = 0;
    pSub->pFrame = fn_801D923C(&pSub->Info, 0);
    if (pSub->pFrame != NULL) {
        fn_801D9320(pSub->pFrame, &pSub->unk_30, &pSub->unk_34);
    }
    if (fn_8022638C()) {
        fn_801D8BC8(&pSub->Info, pSub->pTap, Queued);
    }
    pMovie->unk_44 = 1;
    pSub->unk_14 = 0;
    pSub->unk_16 = fn_80226384();
    lbl_803EBF85 = 0;
    lbl_803EBF84 = 0;
}

void fn_80226C40(Object_8021E688 *pObject, Object_802268D4 *pMovie)
{
    Sub_802268D4 *pSub;

    if (pMovie->unk_40 == -1) {
        lbl_803EBF85 = 1;
        return;
    }
    pSub = &pMovie->Sub;
    if (pSub->pStream != NULL) {
        if (fn_8022638C() && pSub->pTap != (struct StreamTap_801F5DA4 *)-1) {
            fn_801D8C84(&pSub->Info);
        }
        fn_801D8B54(&pSub->Info);
        fn_801F6B84(pSub->pStream);
        pSub->pStream = NULL;
        pSub->Info.mpAudio = NULL;
        pSub->Info.mpVideo = NULL;
    }
    if (pSub->unk_08 != NULL) {
        fn_801D2BD0(pSub->unk_08);
        pSub->unk_08 = NULL;
    }
    if (pSub->unk_1C != NULL) {
        fn_801D2BD0(pSub->unk_1C);
        pSub->unk_1C = NULL;
    }
    if (pSub->unk_18 != NULL) {
        fn_801D2BD0(pSub->unk_18);
        pSub->unk_18 = NULL;
    }
    lbl_803EBF84 = 1;
}

void fn_80226D20(Int32 Width, Int32 Height, Uint8 *pData)
{
    Int32 Heap = fn_802263D4();
    Int32 TilesX = (Width + 3) >> 2;
    Int32 TilesY = (Height + 3) >> 2;
    Uint32 x;
    Uint32 y;
    Uint8 *pTile;

    if (lbl_803EBF80 == NULL) {
        lbl_803EBF80 = fn_801D2BB0(Heap, TilesX * TilesY * 64, 0, 0);
    }
    pTile = lbl_803EBF80;
    for (y = 0; y < TilesY; y++) {
        for (x = 0; x < TilesX; x++) {
            fn_80226E4C(pData, x * 4, y * 4, pTile, Width, Height);
            pTile += 64;
        }
    }
    memcpy(pData, lbl_803EBF80, TilesX * TilesY * 64);
}

void fn_80226E00(Uint8 *pSrc, Int32 Width, Int32 x, Int32 y, Uint8 *pA, Uint8 *pB, Uint8 *pC)
{
    Uint8 *p = &pSrc[(y * Width + x) * 4];
    Uint8 First = p[3];
    Uint8 Second = p[2];

    pA[1] = First;
    pA[0] = Second;
    if (pB != NULL) {
        *pB = p[1];
    }
    if (pC != NULL) {
        *pC = p[0];
    }
}

void fn_80226E4C(Uint8 *pSrc, Int32 x, Int32 y, Uint8 *pTile, Int32 Width, Int32 Height)
{
    Uint32 Rows = Height - y;
    Uint32 Cols = Width - x;
    Uint32 i;
    Uint32 j;
    Uint8 *pAR;
    Uint8 *pGB;
    Uint8 Texel[4];

    if (Rows > 4) {
        Rows = 4;
    }
    if (Cols > 4) {
        Cols = 4;
    }
    for (j = 0; j < Rows; j++) {
        pAR = &pTile[j * 8];
        pGB = &pTile[j * 8 + 32];
        for (i = 0; i < Cols; i++) {
            fn_80226E00(pSrc, Width, x + i, y + j, &Texel[0], &Texel[2], &Texel[3]);
            pAR[0] = Texel[1];
            pAR[1] = Texel[0];
            pGB[0] = Texel[2];
            pGB[1] = Texel[3];
            pAR += 2;
            pGB += 2;
        }
    }
}

void fn_80226F34(Object_8021E688 *pObject, Int16 a, Int16 b, Object_802268D4 *pMovie)
{
    fn_8021EE58(pObject, a, b, pMovie->unk_3C, pMovie->unk_40);
    fn_80226C40(pObject, pMovie);
    pMovie->unk_3C = a;
    pMovie->unk_40 = b;
    lbl_803EBF84 = 0;
    pMovie->Flags &= ~2;
}
