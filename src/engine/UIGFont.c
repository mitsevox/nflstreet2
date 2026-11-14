/* UI graphics fonts: opens the font packages of the menu libraries, creates
   and destroys each font as a UIGLibraries item, and gives the menus a
   font's string width or the font itself, loading it on first use. */

#include "engine/Font.h"
#include "engine/Resource.h"
#include "engine/UIGLibraries.h"
#include "engine/UIGFont.h"
#include "game/fn_801D2B7C.h"

/* 8-byte item allocated by fn_80225E64. */
typedef struct Item_80225E64 {
    Font_801CCA64 *pFont; /* 0x00 */
    Int32 unk_04;   /* 0x04 */
} Item_80225E64;

int fn_801CCDA4(const char *pName, int mode);
int fn_801CCE10(int handle);
int fn_801CCE60(void *pFile, int id);
int fn_801CD07C(int id);
int fn_801CD244(Font_801CCA64 *pFont);
int fn_801CD63C(Font_801CCA64 *pFont, const char *pText, unsigned int flags);
int ResGetNumResources(ResFile_t *pRes);

void fn_80225D90(Object_8021E688 *pObject, Int16 a)
{
    int Handle;

    if (a != -1 && fn_8021EB40(pObject, a) == 0) {
        Handle = fn_801CCDA4((const char *)fn_8021E970(pObject, a), 44);
        fn_8021EB2C(pObject, a, Handle);
        fn_8021E244(pObject, a, ResGetNumResources((ResFile_t *)Handle));
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
