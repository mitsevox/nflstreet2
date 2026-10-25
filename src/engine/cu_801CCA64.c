/* Font manager: loaded font files kept in a list, font instances, glyph lookup, text layout and render state. */

#include "engine/cu_801C665C.h"
#include "engine/cu_801CCA64.h"
#include "game/fn_801C68FC.h"
#include "engine/fn_801F7BD4.h"
#include "engine/fn_801F8014.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801EEB44.h"
#include "game/fn_801EF390.h"
#include "engine/cu_801C2EB4.h"

typedef struct FontParams_801CCA64 {
    int mMaxFonts;
    int mUnk4;
    int mHeap;
    unsigned short mUnkC;
    unsigned short mUnkE;
} FontParams_801CCA64;

typedef struct FontState_801CCA64 {
    unsigned char mNumFonts;
    void *mpList;
    void *mpBuffer;
    int mHeap;
    int mUnk10;
    unsigned short mUnk14;
    unsigned short mUnk16;
    unsigned short mUnk18;
    unsigned short mUnk1A;
    void *mpPalette0;
    void *mpPalette1;
    void *mpPalette2;
} FontState_801CCA64;

extern Lock_801F8014 lbl_80383CD0;
extern FontState_801CCA64 lbl_80383CF0;
extern FontRenderState_801CCA64 lbl_803E7600;
extern unsigned char lbl_803EBC58;

void *fn_801C1F94();


static int fn_801CCAB8(FontEntry_801CCA64 *pEntry, int *pId, FontEntry_801CCA64 **ppResult);

static FontEntry_801CCA64 *fn_801CCA64(int id)
{
    FontEntry_801CCA64 *pEntry;

    if (fn_801C6DCC(lbl_80383CF0.mpList, 0, &id, &pEntry, (ListSearchFn_801C6DCC)fn_801CCAB8) != 2) {
        pEntry = 0;
    }
    return pEntry;
}

static int fn_801CCAB8(FontEntry_801CCA64 *pEntry, int *pId, FontEntry_801CCA64 **ppResult)
{
    int result = -1;

    if (pEntry->mId == *pId) {
        *ppResult = pEntry;
        result = 0;
    }
    return result;
}

static FontGlyph_801CCA64 *fn_801CCADC(Font_801CCA64 *pFont, unsigned int c)
{
    FontGlyph_801CCA64 *pGlyphs = pFont->mpGlyphs;
    unsigned int count = pFont->mpHeader->mNumGlyphs;
    FontGlyph_801CCA64 *pResult;
    FontGlyph_801CCA64 *pGlyph;
    unsigned int half;

    if (c - ' ' < count && pGlyphs[c - ' '].mCode == c) {
        return &pGlyphs[c - ' '];
    }
    pResult = 0;
    while (count) {
        half = count >> 1;
        pGlyph = &pGlyphs[half];
        if (c < pGlyph->mCode) {
            count = half;
        } else if (c > pGlyph->mCode) {
            pGlyphs = pGlyph + 1;
            count = count - half - 1;
        } else {
            pResult = pGlyph;
            break;
        }
    }
    return pResult;
}

static int fn_801CCB5C(Font_801CCA64 *pFont, int first, int second)
{
    FontKernTable_801CCA64 *pKern = pFont->mpKern;
    FontKernPair_801CCA64 *pPair;
    int amount = 0;
    int i;

    if (pKern) {
        pPair = pKern->mPairs;
        for (i = pKern->mCount; i > 0; i--) {
            if (first == pPair->mFirst && second == pPair->mSecond) {
                amount = pPair->mAmount;
                break;
            }
            pPair++;
        }
    }
    return amount;
}

int fn_801CCBD0(FontEntry_801CCA64 *pEntry, FontHeader_801CCA64 *pData)
{
    int error = 0;

    pEntry->mpData = pData;
    if (pData->mMagic != 0x464E5447) {
        error = 0x110003;
    }
    fn_801F7BD4(error);
    return error;
}

int fn_801CCC24(FontParams_801CCA64 *pParams)
{
    int error = 0;

    if (!lbl_803EBC58) {
        fn_801F7FA8(&lbl_80383CD0);
        fn_801F8014(&lbl_80383CD0);
        lbl_80383CF0.mNumFonts = 0;
        lbl_80383CF0.mpList = fn_801C68FC(pParams->mHeap, 0, pParams->mMaxFonts, sizeof(FontEntry_801CCA64), 0, 0);
        lbl_80383CF0.mUnk10 = pParams->mUnk4;
        lbl_80383CF0.mHeap = pParams->mHeap;
        lbl_80383CF0.mUnk14 = pParams->mUnkC;
        lbl_80383CF0.mUnk16 = pParams->mUnkE;
        lbl_80383CF0.mUnk18 = pParams->mUnkC;
        lbl_80383CF0.mUnk1A = pParams->mUnkE;
        lbl_80383CF0.mpBuffer = fn_801D2BB0(lbl_80383CF0.mHeap, 0x100, 0, 0);
        fn_801CD2A4();
        lbl_803EBC58 = 1;
        fn_801F809C(&lbl_80383CD0);
    } else {
        error = 0x110001;
    }
    fn_801F7BD4(error);
    return error;
}

int fn_801CCD0C(void)
{
    int error = 0;

    if (lbl_803EBC58) {
        fn_801F8014(&lbl_80383CD0);
        fn_801C69E4(lbl_80383CF0.mpList);
        fn_801F809C(&lbl_80383CD0);
        fn_801F80D0(&lbl_80383CD0);
        lbl_803EBC58 = 0;
        fn_801D2BD0(lbl_80383CF0.mpBuffer);
        fn_801C1F94(&lbl_80383CF0, 0, sizeof(FontState_801CCA64));
    } else {
        error = 0x110002;
    }
    fn_801F7BD4(error);
    return error;
}

int fn_801CCDA4(const char *pName, int mode)
{
    int handle = 0;
    int error = 0;
    void *result;

    if (!lbl_803EBC58) {
        error = 0x110002;
    } else if (result = fn_801EEB44(pName, mode)) {
        handle = (int)result;
    } else {
        error = fn_801F7C88();
    }
    fn_801F7BD4(error);
    return handle;
}

int fn_801CCE10(int handle)
{
    int error;

    if (!lbl_803EBC58) {
        error = 0x110002;
    } else {
        error = fn_801EEFAC((void *)handle);
    }
    fn_801F7BD4(error);
    return error;
}

int fn_801CCE60(void *pFile, int id)
{
    int error;
    FontEntry_801CCA64 *pEntry = 0;
    FontHeader_801CCA64 *pData;

    if (!lbl_803EBC58) {
        error = 0x110002;
    } else {
        if (lbl_80383CF0.mNumFonts == 0) {
            fn_801CDE98(&lbl_80383CF0.mpPalette0, &lbl_80383CF0.mpPalette1, &lbl_80383CF0.mpPalette2);
        }
        if (!(pEntry = fn_801C6A20(lbl_80383CF0.mpList))) {
            error = fn_801F7C88();
        } else {
            if (pData = (FontHeader_801CCA64 *)fn_801EF390(pFile, id, lbl_80383CF0.mHeap)) {
                pEntry->mHandle = id;
                pEntry->mId = id;
                pEntry->mpFile = pFile;
                error = fn_801CCBD0(pEntry, pData);
                fn_801C6AA4(lbl_80383CF0.mpList, pEntry, 0);
            } else {
                error = fn_801F7C88();
            }
            lbl_80383CF0.mNumFonts++;
        }
    }
    if (error && pEntry) {
        fn_801C6C0C(lbl_80383CF0.mpList, pEntry);
    }
    fn_801F7BD4(error);
    return error;
}

int fn_801CCF74(void *pFile, int id, FontHeader_801CCA64 *pData)
{
    int error;
    FontEntry_801CCA64 *pEntry = 0;

    if (!lbl_803EBC58) {
        error = 0x110002;
    } else {
        if (lbl_80383CF0.mNumFonts == 0) {
            fn_801CDE98(&lbl_80383CF0.mpPalette0, &lbl_80383CF0.mpPalette1, &lbl_80383CF0.mpPalette2);
        }
        if (!(pEntry = fn_801C6A20(lbl_80383CF0.mpList))) {
            error = fn_801F7C88();
        } else {
            if (pData) {
                pEntry->mpFile = pFile;
                pEntry->mHandle = id;
                pEntry->mId = id;
                error = fn_801CCBD0(pEntry, pData);
                fn_801C6AA4(lbl_80383CF0.mpList, pEntry, 0);
            } else {
                error = fn_801F7C88();
            }
            lbl_80383CF0.mNumFonts++;
        }
    }
    if (error && pEntry) {
        fn_801C6C0C(lbl_80383CF0.mpList, pEntry);
    }
    fn_801F7BD4(error);
    return error;
}

int fn_801CD07C(int id)
{
    int error;
    FontEntry_801CCA64 *pEntry;

    if (!lbl_803EBC58) {
        error = 0x110002;
    } else {
        if (pEntry = fn_801CCA64(id)) {
            error = fn_801F010C(pEntry->mpFile, pEntry->mHandle);
            fn_801C6C0C(lbl_80383CF0.mpList, pEntry);
            lbl_80383CF0.mNumFonts--;
        } else {
            error = 0x110004;
        }
        if (lbl_80383CF0.mNumFonts == 0) {
            fn_801CDFE4(lbl_80383CF0.mpPalette0, lbl_80383CF0.mpPalette1, lbl_80383CF0.mpPalette2);
        }
    }
    fn_801F7BD4(error);
    return error;
}

Font_801CCA64 *fn_801CD130(int id)
{
    Font_801CCA64 *pFont = 0;
    int error = 0;
    FontEntry_801CCA64 *pEntry;
    FontHeader_801CCA64 *pData;

    if (!lbl_803EBC58) {
        error = 0x110002;
    } else if (pEntry = fn_801CCA64(id)) {
        pFont = fn_801D2BB0(lbl_80383CF0.mHeap, sizeof(Font_801CCA64), 0, 0);
        fn_801C1F94(pFont, 0, sizeof(Font_801CCA64));
        pFont->mpEntry = pEntry;
        pData = pEntry->mpData;
        pFont->mpHeader = pData;
        pFont->mpGlyphs = (FontGlyph_801CCA64 *)((char *)pData + pData->mGlyphOffset);
        pFont->mpTex = (FontTexHeader_801CCA64 *)((char *)pData + pData->mTexOffset);
        if (pData->mKernOffset) {
            pFont->mpKern = (FontKernTable_801CCA64 *)((char *)pData + pData->mKernOffset);
        } else {
            pFont->mpKern = 0;
        }
        fn_801CE134(pFont);
    } else {
        error = 0x110004;
    }
    fn_801F7BD4(error);
    return pFont;
}

void fn_801CD20C(Font_801CCA64 *pFont, int a)
{
    fn_801CDFE8(pFont, lbl_80383CF0.mpPalette0, lbl_80383CF0.mpPalette1, lbl_80383CF0.mpPalette2, a);
}

int fn_801CD244(Font_801CCA64 *pFont)
{
    int error;

    if (!lbl_803EBC58) {
        error = 0x110002;
    } else {
        fn_801CE108(pFont);
        error = fn_801D2BD0(pFont);
    }
    fn_801F7BD4(error);
    return error;
}

int fn_801CD2A4(void)
{
    lbl_803E7600.mFlags = 0;
    lbl_803E7600.mColor.r = 1.0f;
    lbl_803E7600.mColor.g = 1.0f;
    lbl_803E7600.mColor.b = 1.0f;
    lbl_803E7600.mColor.a = 1.0f;
    lbl_803E7600.mShadowColor.r = 0.0f;
    lbl_803E7600.mShadowColor.g = 0.0f;
    lbl_803E7600.mShadowColor.b = 0.0f;
    lbl_803E7600.mShadowColor.a = 0.5f;
    lbl_803E7600.mShadowOffset[0] = 3.0f;
    lbl_803E7600.mShadowOffset[1] = 3.0f;
    lbl_803E7600.mShadowOffset[2] = 1.0f;
    return 0;
}

int fn_801CD308(int which, FontColor_801CCA64 color)
{
    int error = 0;
    FontColor_801CCA64 *pDst;

    switch (which) {
    case 0:
        pDst = &lbl_803E7600.mColor;
        break;
    case 1:
        pDst = &lbl_803E7600.mShadowColor;
        break;
    default:
        error = 0x110005;
        fn_801F7BD4(error);
        goto done;
    }
    pDst->r = color.r;
    pDst->g = color.g;
    pDst->b = color.b;
    pDst->a = color.a;
done:
    return error;
}

int fn_801CD398(unsigned int flags)
{
    lbl_803E7600.mFlags |= flags;
    return 0;
}

int fn_801CD3B0(unsigned int flags)
{
    lbl_803E7600.mFlags &= ~flags;
    return 0;
}

int fn_801CD3C8(float x, float y, float z)
{
    lbl_803E7600.mShadowOffset[0] = x;
    lbl_803E7600.mShadowOffset[1] = y;
    lbl_803E7600.mShadowOffset[2] = z;
    return 0;
}

void fn_801CD3E4(Font_801CCA64 *pFont, const char *pText, unsigned int flags, float maxWidth,
                 FontQuad_801CCA64 *pQuads, unsigned int *pCount)
{
    int error = 0;
    int kern;
    int lineHeight;
    unsigned int len;
    unsigned int i;
    unsigned int count;
    unsigned int j;
    int y;
    int nextY;
    int x;
    int prev;
    unsigned char c;
    FontGlyph_801CCA64 *pGlyph;
    FontQuad_801CCA64 *pQuad;

    if (!lbl_803EBC58) {
        error = 0x110002;
    } else {
        kern = (flags & 4) == 0;
        lineHeight = pFont->mpHeader->mHeight;
        len = fn_801C3180(pText);
        if (len > 354) {
            return;
        }
        y = 0;
        count = 0;
        i = 0;
        pQuad = pQuads;
        while (i < len) {
            j = count;
            prev = -1;
            x = 0;
            nextY = y + lineHeight;
            while (i < len) {
                if (pText[i] == '\n') {
                    i++;
                    break;
                }
                if (!(maxWidth <= 0.0f) && !((float)x <= maxWidth)) {
                    break;
                }
                c = pText[i];
                if (pGlyph = fn_801CCADC(pFont, c)) {
                    if (prev != -1 && kern) {
                        x += fn_801CCB5C(pFont, prev, c);
                    }
                    pQuad->mX = x + pGlyph->mOffsetX;
                    pQuad->mY = y + pGlyph->mOffsetY;
                    pQuad->mWidth = pGlyph->mWidth;
                    pQuad->mHeight = pGlyph->mHeight;
                    pQuad->mU = pGlyph->mU;
                    pQuad->mV = pGlyph->mV;
                    pQuad++;
                    count++;
                    x += pGlyph->mAdvance;
                }
                prev = c;
                i++;
            }
            if (flags & 1) {
                for (; j < count; j++) {
                    pQuads[j].mX -= x / 2;
                }
            } else if (flags & 2) {
                for (; j < count; j++) {
                    pQuads[j].mX -= x;
                }
            }
            y = nextY;
        }
        *pCount = count;
    }
    fn_801F7BD4(error);
}

int fn_801CD63C(Font_801CCA64 *pFont, const char *pText, unsigned int flags)
{
    int error = 0;
    int maxWidth = 0;
    unsigned char kern;
    unsigned int i;
    unsigned int len;
    int prev;
    int width;
    unsigned char c;
    FontGlyph_801CCA64 *pGlyph;

    if (!lbl_803EBC58) {
        error = 0x110002;
    } else {
        kern = (flags & 4) == 0;
        i = 0;
        len = fn_801C3180(pText);
        while (i < len) {
            prev = -1;
            width = 0;
            while (i < len) {
                if (pText[i] == '\n') {
                    i++;
                    break;
                }
                c = pText[i];
                if (pGlyph = fn_801CCADC(pFont, c)) {
                    if (prev != -1 && kern) {
                        width += fn_801CCB5C(pFont, prev, c);
                    }
                    width += pGlyph->mAdvance;
                }
                i++;
                prev = c;
            }
            if (width > maxWidth) {
                maxWidth = width;
            }
        }
    }
    fn_801F7BD4(error);
    return maxWidth;
}

int fn_801CD750(Font_801CCA64 *pFont, unsigned char c)
{
    int width = 0;
    FontGlyph_801CCA64 *pGlyph;

    if (pGlyph = fn_801CCADC(pFont, c)) {
        width = pGlyph->mAdvance;
    }
    return width;
}

int fn_801CD790(Font_801CCA64 *pFont)
{
    return pFont->mpHeader->mHeight;
}
