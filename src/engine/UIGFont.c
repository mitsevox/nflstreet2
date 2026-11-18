/* UI graphics fonts: opens the font packages of the menu libraries, creates
   and destroys each font as a UIGLibraries item, and gives the menus a
   font's string width or the font itself, loading it on first use. */

#include "engine/Font.h"
#include "engine/Resource.h"
#include "engine/UIGLibraries.h"
#include "engine/UIGFont.h"
#include "game/fn_801D2B7C.h"

/* 8-byte item allocated by UIGFontCreateFont. */
typedef struct UIGFontItem_t {
    Font_801CCA64 *pFont; /* 0x00 */
    Int32 unk_04;   /* 0x04 */
} UIGFontItem_t;

int fn_801CCDA4(const char *pName, int mode);
int fn_801CCE10(int handle);
int fn_801CCE60(void *pFile, int id);
int fn_801CD07C(int id);
int fn_801CD244(Font_801CCA64 *pFont);
int fn_801CD63C(Font_801CCA64 *pFont, const char *pText, unsigned int flags);
int ResGetNumResources(ResFile_t *pRes);

void UIGFontCreateFontLibrary(UIGLibrary_t *pObject, Int16 a)
{
    int Handle;

    if (a != -1 && UIGLibraryGetData(pObject, a) == 0) {
        Handle = fn_801CCDA4((const char *)UIGLibraryGetFilename(pObject, a), 44);
        UIGLibrarySetData(pObject, a, Handle);
        UIGLibrarySelfManagedInit(pObject, a, ResGetNumResources((ResFile_t *)Handle));
    }
}

void UIGFontDestroyFontLibrary(UIGLibrary_t *pObject, Int16 a)
{
    Int32 Handle;

    if (a != -1) {
        Handle = UIGLibraryGetData(pObject, a);
        if (Handle != 0) {
            fn_801CCE10(Handle);
            UIGLibrarySetData(pObject, a, 0);
        }
    }
}

void UIGFontCreateFont(UIGLibrary_t *pObject, Int16 a, Int16 b, Int32 c)
{
    Int32 Handle;
    UIGFontItem_t *pItem;

    if (a != -1 && b != -1) {
        Handle = UIGLibraryGetData(pObject, a);
        if (Handle != 0 && UIGLibraryGetItemData(pObject, a, b) == 0) {
            fn_801CCE60((void *)Handle, b);
            pItem = fn_801D2B7C(sizeof(UIGFontItem_t), 0, 0);
            pItem->pFont = fn_801CD130(b);
            pItem->unk_04 = 1;
            UIGLibrarySetItemData(pObject, a, b, (Int32)pItem);
        }
    }
}

void UIGFontDestroyFont(UIGLibrary_t *pObject, Int16 a, Int16 b)
{
    UIGFontItem_t *pItem;

    if (a != -1 && b != -1) {
        pItem = (UIGFontItem_t *)UIGLibraryGetItemData(pObject, a, b);
        if (pItem != NULL) {
            fn_801CD244(pItem->pFont);
            fn_801CD07C(b);
            UIGLibrarySetItemData(pObject, a, b, 0);
            fn_801D2BD0(pItem);
        }
    }
}

Uint32 UIGFontGetStringWidth(UIGLibrary_t *pObject, Int32 a, Int32 b, const char *pText)
{
    UIGFontItem_t *pItem;

    if (a == -1 || b == -1) {
        return 0;
    }
    pItem = (UIGFontItem_t *)UIGLibraryGetItemData(pObject, a, b);
    if (pItem == NULL) {
        UIGLibraryLoadItem(pObject, a, b);
        pItem = (UIGFontItem_t *)UIGLibraryGetItemData(pObject, a, b);
    }
    return fn_801CD63C(pItem->pFont, pText, 0);
}

Font_801CCA64 *UIGFontGetFont(UIGLibrary_t *pObject, Int32 a, Int16 b, Int32 c)
{
    Font_801CCA64 *pResult = NULL;
    UIGFontItem_t *pItem;

    UIGLibraryLoadItem(pObject, a, b);
    pItem = (UIGFontItem_t *)UIGLibraryGetItemData(pObject, a, b);
    if (pItem != NULL) {
        pResult = pItem->pFont;
    }
    if (pItem->unk_04 != 0 && c != 0) {
        UIGLibrarySetMemInfo(a, b);
        fn_801CD20C(pResult, 0);
        UIGLibraryClearMemInfo();
        pItem->unk_04 = 0;
    }
    return pResult;
}
