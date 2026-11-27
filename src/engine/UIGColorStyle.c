#include "engine/cu_8021A438.h"

/* UI colour styles: looks up a colour-style item (a colour table) of the
   global UI library and caches the last lookup, so the node and text renderers
   can recolour their corners and glyphs by palette index; resets that cache;
   and swaps a texture node's palette for a library palette around a draw,
   saving the node's own palette in _PaletteData. */

static Uint32 _UIGColorStyle_uCacheFile;
static Uint32 _UIGColorStyle_uCacheItem;
static UIGLibrary_t *_UIGColorStyle_pCacheLibrary;
static Int32 _UIGColorStyle_pCacheColorStyle;
static unsigned short *_PaletteData = NULL;

Int32 UIGCSGetColorStyle(Int32 a, Int32 b)
{
    UIGLibrary_t *pObject;

    Int32 Result;

    pObject = UIGLibraryGetGlobal(1);
    Result = 0;
    if (pObject != NULL) {
        Result = _UIGColorStyle_pCacheColorStyle;
        if (Result == 0 || _UIGColorStyle_pCacheLibrary != pObject || _UIGColorStyle_uCacheFile != a || _UIGColorStyle_uCacheItem != b) {
            Result = UIGLibraryLoadItem(pObject, a, b);
            _UIGColorStyle_pCacheLibrary = pObject;
            _UIGColorStyle_uCacheFile = a;
            _UIGColorStyle_uCacheItem = b;
            _UIGColorStyle_pCacheColorStyle = Result;
        }
    }
    return Result;
}

void UIGCSResetColorStyleCache(void)
{
    _UIGColorStyle_pCacheColorStyle = 0;
    _UIGColorStyle_uCacheFile = -1;
    _UIGColorStyle_pCacheLibrary = NULL;
    _UIGColorStyle_uCacheItem = -1;
}

Int32 UIGCSLoadPalette(Int32 a, Int32 b)
{
    UIGLibrary_t *pObject;

    pObject = UIGLibraryGetGlobal(1);
    if (pObject == NULL) {
        return 0;
    }
    return UIGLibraryLoadItem(pObject, a, b);
}

void UIGCSSwapPalette(Int32 a, Int32 b, Int32 c)
{
    Int32 p;

    _PaletteData = UIGTexNodeGetPalette((struct UIGTexNode_t *)c);
    p = UIGCSLoadPalette(a, b);
    if (p != 0) {
        UIGTexNodeSetPalette((struct UIGTexNode_t *)c, (unsigned short *)p);
    }
}

void UIGCSRestorePalette(Int32 a, Int32 b, Int32 c)
{
    if (_PaletteData != NULL) {
        UIGTexNodeSetPalette((struct UIGTexNode_t *)c, _PaletteData);
    }
    _PaletteData = NULL;
}
