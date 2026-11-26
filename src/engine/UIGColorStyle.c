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

static Int32 lbl_803ECFFC;
static Int32 lbl_803ED000;
static UIGLibrary_t *lbl_803ED004;
static Int32 lbl_803ED008;

Int32 fn_80220B4C(Int32 a, Int32 b)
{
    UIGLibrary_t *pObject;

    Int32 Result;

    pObject = UIGLibraryGetGlobal(1);
    Result = 0;
    if (pObject != NULL) {
        Result = lbl_803ED008;
        if (Result == 0 || lbl_803ED004 != pObject || lbl_803ECFFC != a || lbl_803ED000 != b) {
            Result = UIGLibraryLoadItem(pObject, a, b);
            lbl_803ED004 = pObject;
            lbl_803ECFFC = a;
            lbl_803ED000 = b;
            lbl_803ED008 = Result;
        }
    }
    return Result;
}

void fn_80220BE0(void)
{
    lbl_803ED008 = 0;
    lbl_803ECFFC = -1;
    lbl_803ED004 = NULL;
    lbl_803ED000 = -1;
}
