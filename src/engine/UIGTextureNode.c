/* UI graphics texture nodes: loads and unloads the menu textures kept as
   UIGLibraries items, swaps the texture shown in a slot (handing movie items
   to the FMV player), and reads or replaces a texture's palette. */

#include "engine/UIGLibraries.h"
#include "engine/UIGTextureNode.h"
#include "engine/UIGFmv.h"

void fn_801CE910(void);

void UIGTexNodeUnLoad(UIGLibrary_t *pObject, Int16 a, Int16 b)
{
    UIGTexNode_t *pNode = (UIGTexNode_t *)UIGLibraryGetItemData(pObject, a, b);

    if (pNode != NULL) {
        LLUIGTexNodeFreeImage(a, b, pNode);
        UIGLibrarySetItemData(pObject, a, b, 0);
    }
}

void UIGTexNodeLoad(UIGLibrary_t *pObject, Int16 a, Int32 b, Int32 c)
{
    Int32 Item = UIGLibraryGetItemData(pObject, a, b);

    if (c != 0 && Item == 0) {
        Item = (Int32)LLUIGTexNodeSetImage(a, b, c, 0, UIGLibraryGetVramHeapID(pObject, a));
        UIGLibrarySetItemData(pObject, a, b, Item);
    }
}

void UIGTexNodeSwap(UIGLibrary_t *pObject, Int16 *pA, Int16 *pB, Int16 c, Int16 d)
{
    if (*pA == c && *pB == d) {
        return;
    }
    if (*pA != -1 && *pB != -1 && c != -1 && d != -1) {
        if ((UIGLibraryGetType(pObject, *pA) & 2) && (UIGLibraryGetType(pObject, c) & 2)) {
            UIGFmvSwapInstance(pObject, c, d, *pA, *pB);
        } else {
            fn_801CE910();
            UIGLibraryUnLoadItem(pObject, *pA, *pB);
            UIGLibraryLoadItem(pObject, c, d);
        }
    } else if (*pA != -1 && *pB != -1) {
        UIGLibraryUnLoadItem(pObject, *pA, *pB);
    } else if (c != -1 && d != -1) {
        UIGLibraryLoadItem(pObject, c, d);
    }
    *pA = c;
    *pB = d;
}

void UIGTexNodeUpdate(UIGLibrary_t *pObject, Int32 a, Int32 b, Int32 c)
{
    if (a != -1 && b != -1) {
        LLUIGTexNodeUpdate(c, UIGLibraryGetItemData(pObject, a, b));
    }
}

unsigned short *UIGTexNodeGetPalette(UIGTexNode_t *pNode)
{
    return LLUIGTexNodeGetPalette(pNode);
}

void UIGTexNodeSetPalette(UIGTexNode_t *pNode, unsigned short *pPalette)
{
    LLUIGTexNodeSetPalette(pNode, pPalette);
}
