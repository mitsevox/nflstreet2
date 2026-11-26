#include <string.h>

#include <dolphin/gx/GXBump.h>
#include <dolphin/gx/GXCull.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXLighting.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/gx/GXTev.h>
#include <dolphin/gx/GXTexture.h>
#include <dolphin/gx/GXTransform.h>
#include <dolphin/gx/GXVert.h>
#include "UIStudio/UIStudio.h"
#include "engine/Resource.h"
#include "engine/llmatrix.h"
#include "engine/cu_8021A438.h"
#include "engine/viewport.h"
#include "game/fn_801D2B7C.h"
#include "game/ResOpenDevice.h"

/* UI colour styles: looks up a colour-style item (a colour table) of the
   global UI library and caches the last lookup, so the node and text renderers
   can recolour their corners and glyphs by palette index; and resets that
   cache. The lookup is a documented holdout and keeps its original bytes. */

static Uint32 _UIGColorStyle_uCacheFile;
static Uint32 _UIGColorStyle_uCacheItem;
static UIGLibrary_t *_UIGColorStyle_pCacheLibrary;
static Int32 _UIGColorStyle_pCacheColorStyle;

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
