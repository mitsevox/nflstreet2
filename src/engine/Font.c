/* Font manager: loaded font files kept in a list, font instances, glyph lookup, text layout and render state. */

#include "engine/list.h"
#include "engine/Font.h"
#include "engine/dslist.h"
#include "engine/SysSetLastErrorFunc.h"
#include "engine/fn_801F8014.h"
#include "game/fn_801D2B7C.h"
#include "game/ResOpenDevice.h"
#include "game/ResLoad.h"
#include <string.h>

typedef struct FontParams_t {
    int mMaxFonts;
    int mUnk4;
    int mHeap;
    unsigned short mUnkC;
    unsigned short mUnkE;
} FontParams_t;

typedef struct FontState_t {
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
} FontState_t;

unsigned char Font_ModuleActive = 0;

/* The font library's lock and its state (fonts loaded, their list, heap and palettes). */
static Lock_801F8014 _Font_CS;
static FontState_t _Font_State;

extern FontRenderState_t Font_RenderState;

static int _FontSearchFontNum(FontEntry_t *pEntry, int *pId, FontEntry_t **ppResult);

static FontEntry_t *_FontGetFontListPtr(int id)
{
    FontEntry_t *pEntry;

    if (DSSearchList(_Font_State.mpList, 0, &id, &pEntry, (DSListSearchFn_t)_FontSearchFontNum) != 2) {
        pEntry = 0;
    }
    return pEntry;
}

static int _FontSearchFontNum(FontEntry_t *pEntry, int *pId, FontEntry_t **ppResult)
{
    int result = -1;

    if (pEntry->mId == *pId) {
        *ppResult = pEntry;
        result = 0;
    }
    return result;
}

static FontGlyph_t *_FontLookupGlyph(Font_t *pFont, unsigned int c)
{
    FontGlyph_t *pGlyphs = pFont->mpGlyphs;
    unsigned int count = pFont->mpHeader->mNumGlyphs;
    FontGlyph_t *pResult;
    FontGlyph_t *pGlyph;
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

static int _FontGetKernAmount(Font_t *pFont, int first, int second)
{
    FontKernTable_t *pKern = pFont->mpKern;
    FontKernPair_t *pPair;
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

int FontProcessFontFile(FontEntry_t *pEntry, FontHeader_t *pData)
{
    int error = 0;

    pEntry->mpData = pData;
    if (pData->mMagic != 0x464E5447) {
        error = 0x110003;
    }
    SysSetLastErrorFunc(error);
    return error;
}

int FontInit(FontParams_t *pParams)
{
    int error = 0;

    if (!Font_ModuleActive) {
        fn_801F7FA8(&_Font_CS);
        fn_801F8014(&_Font_CS);
        _Font_State.mNumFonts = 0;
        _Font_State.mpList = DSNewList(pParams->mHeap, 0, pParams->mMaxFonts, sizeof(FontEntry_t), 0, 0);
        _Font_State.mUnk10 = pParams->mUnk4;
        _Font_State.mHeap = pParams->mHeap;
        _Font_State.mUnk14 = pParams->mUnkC;
        _Font_State.mUnk16 = pParams->mUnkE;
        _Font_State.mUnk18 = pParams->mUnkC;
        _Font_State.mUnk1A = pParams->mUnkE;
        _Font_State.mpBuffer = fn_801D2BB0(_Font_State.mHeap, 0x100, 0, 0);
        FontResetRenderState();
        Font_ModuleActive = 1;
        fn_801F809C(&_Font_CS);
    } else {
        error = 0x110001;
    }
    SysSetLastErrorFunc(error);
    return error;
}

int FontShutdown(void)
{
    int error = 0;

    if (Font_ModuleActive) {
        fn_801F8014(&_Font_CS);
        DSDelList(_Font_State.mpList);
        fn_801F809C(&_Font_CS);
        fn_801F80D0(&_Font_CS);
        Font_ModuleActive = 0;
        fn_801D2BD0(_Font_State.mpBuffer);
        memset(&_Font_State, 0, sizeof(FontState_t));
    } else {
        error = 0x110002;
    }
    SysSetLastErrorFunc(error);
    return error;
}

int FontOpenFileDevice(const char *pName, int mode)
{
    int handle = 0;
    int error = 0;
    void *result;

    if (!Font_ModuleActive) {
        error = 0x110002;
    } else if (result = ResOpenDevice(pName, mode)) {
        handle = (int)result;
    } else {
        error = SysGetLastError();
    }
    SysSetLastErrorFunc(error);
    return handle;
}

int FontCloseFile(int handle)
{
    int error;

    if (!Font_ModuleActive) {
        error = 0x110002;
    } else {
        error = ResClose((void *)handle);
    }
    SysSetLastErrorFunc(error);
    return error;
}

int FontAddFont(void *pFile, int id)
{
    int error;
    FontEntry_t *pEntry = 0;
    FontHeader_t *pData;

    if (!Font_ModuleActive) {
        error = 0x110002;
    } else {
        if (_Font_State.mNumFonts == 0) {
            FontLLUploadPalettes(&_Font_State.mpPalette0, &_Font_State.mpPalette1, &_Font_State.mpPalette2);
        }
        if (!(pEntry = DSNewListNode(_Font_State.mpList))) {
            error = SysGetLastError();
        } else {
            if (pData = (FontHeader_t *)ResLoad(pFile, id, _Font_State.mHeap)) {
                pEntry->mHandle = id;
                pEntry->mId = id;
                pEntry->mpFile = pFile;
                error = FontProcessFontFile(pEntry, pData);
                DSAddListNode(_Font_State.mpList, pEntry, 0);
            } else {
                error = SysGetLastError();
            }
            _Font_State.mNumFonts++;
        }
    }
    if (error && pEntry) {
        DSDelListNode(_Font_State.mpList, pEntry);
    }
    SysSetLastErrorFunc(error);
    return error;
}

int FontAddFontFromBuffer(void *pFile, int id, FontHeader_t *pData)
{
    int error;
    FontEntry_t *pEntry = 0;

    if (!Font_ModuleActive) {
        error = 0x110002;
    } else {
        if (_Font_State.mNumFonts == 0) {
            FontLLUploadPalettes(&_Font_State.mpPalette0, &_Font_State.mpPalette1, &_Font_State.mpPalette2);
        }
        if (!(pEntry = DSNewListNode(_Font_State.mpList))) {
            error = SysGetLastError();
        } else {
            if (pData) {
                pEntry->mpFile = pFile;
                pEntry->mHandle = id;
                pEntry->mId = id;
                error = FontProcessFontFile(pEntry, pData);
                DSAddListNode(_Font_State.mpList, pEntry, 0);
            } else {
                error = SysGetLastError();
            }
            _Font_State.mNumFonts++;
        }
    }
    if (error && pEntry) {
        DSDelListNode(_Font_State.mpList, pEntry);
    }
    SysSetLastErrorFunc(error);
    return error;
}

int FontRemoveFont(int id)
{
    int error;
    FontEntry_t *pEntry;

    if (!Font_ModuleActive) {
        error = 0x110002;
    } else {
        if (pEntry = _FontGetFontListPtr(id)) {
            error = ResUnLoad(pEntry->mpFile, pEntry->mHandle);
            DSDelListNode(_Font_State.mpList, pEntry);
            _Font_State.mNumFonts--;
        } else {
            error = 0x110004;
        }
        if (_Font_State.mNumFonts == 0) {
            FontLLReleasePalettes(_Font_State.mpPalette0, _Font_State.mpPalette1, _Font_State.mpPalette2);
        }
    }
    SysSetLastErrorFunc(error);
    return error;
}

Font_t *FontCreateFont(int id)
{
    Font_t *pFont = 0;
    int error = 0;
    FontEntry_t *pEntry;
    FontHeader_t *pData;

    if (!Font_ModuleActive) {
        error = 0x110002;
    } else if (pEntry = _FontGetFontListPtr(id)) {
        pFont = fn_801D2BB0(_Font_State.mHeap, sizeof(Font_t), 0, 0);
        memset(pFont, 0, sizeof(Font_t));
        pFont->mpEntry = pEntry;
        pData = pEntry->mpData;
        pFont->mpHeader = pData;
        pFont->mpGlyphs = (FontGlyph_t *)((char *)pData + pData->mGlyphOffset);
        pFont->mpTex = (FontTexHeader_t *)((char *)pData + pData->mTexOffset);
        if (pData->mKernOffset) {
            pFont->mpKern = (FontKernTable_t *)((char *)pData + pData->mKernOffset);
        } else {
            pFont->mpKern = 0;
        }
        FontLLCreateFont(pFont);
    } else {
        error = 0x110004;
    }
    SysSetLastErrorFunc(error);
    return pFont;
}

void FontUploadTextures(Font_t *pFont, int a)
{
    FontLLUploadTextures(pFont, _Font_State.mpPalette0, _Font_State.mpPalette1, _Font_State.mpPalette2, a);
}

int FontDestroyFont(Font_t *pFont)
{
    int error;

    if (!Font_ModuleActive) {
        error = 0x110002;
    } else {
        FontLLReleaseTextures(pFont);
        error = fn_801D2BD0(pFont);
    }
    SysSetLastErrorFunc(error);
    return error;
}

int FontResetRenderState(void)
{
    Font_RenderState.mFlags = 0;
    Font_RenderState.mColor.r = 1.0f;
    Font_RenderState.mColor.g = 1.0f;
    Font_RenderState.mColor.b = 1.0f;
    Font_RenderState.mColor.a = 1.0f;
    Font_RenderState.mShadowColor.r = 0.0f;
    Font_RenderState.mShadowColor.g = 0.0f;
    Font_RenderState.mShadowColor.b = 0.0f;
    Font_RenderState.mShadowColor.a = 0.5f;
    Font_RenderState.mShadowOffset[0] = 3.0f;
    Font_RenderState.mShadowOffset[1] = 3.0f;
    Font_RenderState.mShadowOffset[2] = 1.0f;
    return 0;
}

int FontSetRenderColor(int which, FontColor_t color)
{
    int error = 0;
    FontColor_t *pDst;

    switch (which) {
    case 0:
        pDst = &Font_RenderState.mColor;
        break;
    case 1:
        pDst = &Font_RenderState.mShadowColor;
        break;
    default:
        error = 0x110005;
        SysSetLastErrorFunc(error);
        goto done;
    }
    pDst->r = color.r;
    pDst->g = color.g;
    pDst->b = color.b;
    pDst->a = color.a;
done:
    return error;
}

int FontSetRenderFlags(unsigned int flags)
{
    Font_RenderState.mFlags |= flags;
    return 0;
}

int FontClearRenderFlags(unsigned int flags)
{
    Font_RenderState.mFlags &= ~flags;
    return 0;
}

int FontSetShadowOffset(float x, float y, float z)
{
    Font_RenderState.mShadowOffset[0] = x;
    Font_RenderState.mShadowOffset[1] = y;
    Font_RenderState.mShadowOffset[2] = z;
    return 0;
}

/* Lays out glyph quads and applies each line's horizontal alignment. */
void FontDrawText(Font_t *pFont, const char *pText, unsigned int flags, float maxWidth,
                 FontQuad_t *pQuads, unsigned int *pCount)
{
    int error = 0;
    unsigned char kern;
    int lineHeight;
    unsigned int len;
    unsigned int i;
    unsigned int count;
    unsigned int j;
    int y;
    int x;
    int prev;
    unsigned char c;
    FontGlyph_t *pGlyph;
    FontQuad_t *pQuad;

    if (!Font_ModuleActive) {
        error = 0x110002;
    } else {
        kern = (flags & 4) == 0;
        lineHeight = pFont->mpHeader->mHeight;
        len = strlen(pText);
        if (len > 354) {
            return;
        }
        y = 0;
        count = 0;
        i = 0;
        if (i < len) {
            pQuad = pQuads;
            do {
                j = count;
                prev = -1;
                x = 0;
                while (i < len) {
                    if (pText[i] == '\n') {
                        i++;
                        break;
                    }
                    if (!(maxWidth <= 0.0f) && !((float)x <= maxWidth)) {
                        break;
                    }
                    c = pText[i];
                    if (pGlyph = _FontLookupGlyph(pFont, c)) {
                        if (prev != -1 && kern) {
                            x += _FontGetKernAmount(pFont, prev, c);
                        }
                        {
                            FontQuad_t *pDest = pQuad++;
                            count++;
                            pDest->mX = x + pGlyph->mOffsetX;
                            pDest->mY = y + pGlyph->mOffsetY;
                            pDest->mWidth = pGlyph->mWidth;
                            pDest->mHeight = pGlyph->mHeight;
                            pDest->mU = pGlyph->mU;
                            pDest->mV = pGlyph->mV;
                        }
                        x += pGlyph->mAdvance;
                    }
                    prev = c;
                    i++;
                }
                if (flags & 1) {
                    int halfWidth = x / 2;
                    for (; j < count; j++) {
                        pQuads[j].mX -= halfWidth;
                    }
                } else if (flags & 2) {
                    for (; j < count; j++) {
                        pQuads[j].mX -= x;
                    }
                }
                y += lineHeight;
            } while (i < len);
        }
        *pCount = count;
    }
    SysSetLastErrorFunc(error);
}

int FontGetTextWidth(Font_t *pFont, const char *pText, unsigned int flags)
{
    int error = 0;
    int maxWidth = 0;
    unsigned char kern;
    unsigned int i;
    unsigned int len;
    int prev;
    int width;
    unsigned char c;
    FontGlyph_t *pGlyph;

    if (!Font_ModuleActive) {
        error = 0x110002;
    } else {
        kern = (flags & 4) == 0;
        i = 0;
        len = strlen(pText);
        while (i < len) {
            prev = -1;
            width = 0;
            while (i < len) {
                if (pText[i] == '\n') {
                    i++;
                    break;
                }
                c = pText[i];
                if (pGlyph = _FontLookupGlyph(pFont, c)) {
                    if (prev != -1 && kern) {
                        width += _FontGetKernAmount(pFont, prev, c);
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
    SysSetLastErrorFunc(error);
    return maxWidth;
}

int FontGetCharWidth(Font_t *pFont, unsigned char c)
{
    int width = 0;
    FontGlyph_t *pGlyph;

    if (pGlyph = _FontLookupGlyph(pFont, c)) {
        width = pGlyph->mAdvance;
    }
    return width;
}

int FontGetDescent(Font_t *pFont)
{
    return pFont->mpHeader->mHeight;
}
