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
    Font_t *pFont; /* 0x00 */
    Int32 unk_04;   /* 0x04 */
} UIGFontItem_t;

int FontOpenFileDevice(const char *pName, int mode);
int FontCloseFile(int handle);
int FontAddFont(void *pFile, int id);
int FontRemoveFont(int id);
int FontDestroyFont(Font_t *pFont);
int FontGetTextWidth(Font_t *pFont, const char *pText, unsigned int flags);
int ResGetNumResources(ResFile_t *pRes);

void UIGFontCreateFontLibrary(UIGLibrary_t *pObject, Int16 a)
{
    int Handle;

    if (a != -1 && UIGLibraryGetData(pObject, a) == 0) {
        Handle = FontOpenFileDevice((const char *)UIGLibraryGetFilename(pObject, a), 44);
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
            FontCloseFile(Handle);
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
            FontAddFont((void *)Handle, b);
            pItem = fn_801D2B7C(sizeof(UIGFontItem_t), 0, 0);
            pItem->pFont = FontCreateFont(b);
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
            FontDestroyFont(pItem->pFont);
            FontRemoveFont(b);
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
    return FontGetTextWidth(pItem->pFont, pText, 0);
}

Font_t *UIGFontGetFont(UIGLibrary_t *pObject, Int32 a, Int16 b, Int32 c)
{
    Font_t *pResult = NULL;
    UIGFontItem_t *pItem;

    UIGLibraryLoadItem(pObject, a, b);
    pItem = (UIGFontItem_t *)UIGLibraryGetItemData(pObject, a, b);
    if (pItem != NULL) {
        pResult = pItem->pFont;
    }
    if (pItem->unk_04 != 0 && c != 0) {
        UIGLibrarySetMemInfo(a, b);
        FontUploadTextures(pResult, 0);
        UIGLibraryClearMemInfo();
        pItem->unk_04 = 0;
    }
    return pResult;
}
