/* UI graphics texture nodes: loads and unloads the menu textures kept as
   UIGLibraries items, swaps the texture shown in a slot (handing movie items
   to the FMV player), and reads or replaces a texture's palette. */

#include "engine/UIGLibraries.h"
#include "engine/UIGTextureNode.h"
#include "engine/UIGFmv.h"

void fn_801CE910(void);

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
