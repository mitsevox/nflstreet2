/* UI graphics libraries: the table of resource libraries the menus draw from
   (textures, fonts and movies kept in the uis_*.dat packages), with
   reference-counted loading and unloading of each library item, the per-type
   init/load/unload hooks, and the callbacks the game installs around every
   load. */

#include <string.h>

#include "engine/Resource.h"
#include "engine/UIGLibraries.h"
#include "engine/UIGTextureNode.h"
#include "engine/UIGFont.h"
#include "engine/UIGFmv.h"
#include "game/fn_801D2B7C.h"
#include "game/ResOpenDevice.h"

int ResIsLoaded(void *pData, int index);
int ResIsLoading(void *pData, int index);
ResFile_t *ResOpenRam(ResFile_t *pParent, unsigned int index, int heap, int mode);
unsigned int ResLoadAsync(ResFile_t *pRes, unsigned int index, int heap, int a, ResDoneCallback_t pDone,
                         void *pUser);
int ResLoadAll(ResFile_t *pRes, int heap, int a);
int ResUnLoadAll(ResFile_t *pRes);
int ResGetNumResources(ResFile_t *pRes);
int ResGetAlignment(ResFile_t *pRes);
void fn_80220BE0(void);

static UIGLibrary_t *_pLibraryInfo[2] = { 0 };
static UIGLibraryMemInfoFunc_t *_UIGLibraryMemInfoFunc = 0;
static UIGLibraryLoadFlagsFunc_t *_UIGLibraryLoadFlagsFunc = 0;

Int32 UIGLibraryIsItemLoaded(UIGLibraryType_t *pEntry, Int32 Item)
{
    Int32 Result;
    UIGLibraryItem_t *pItem;

    Result = 0;
    if (ResIsLoaded(pEntry->pData, Item) != 0) {
        Result = 1;
    } else {
        pItem = &pEntry->pItems[Item];
        if (pItem->unk_02 != 0) {
            Result = 1;
        }
    }
    return Result;
}

UIGLibrary_t *UIGLibraryInit(UISResListDesc *pDesc)
{
    Int32 Size;
    UIGLibrary_t *pObject;

    fn_80220BE0();
    Size = pDesc->NumA * sizeof(UIGLibraryType_t) + sizeof(UIGLibrary_t) +
           pDesc->NumB * sizeof(UIGLibraryType_t);
    pObject = fn_801D2B7C(Size, pDesc->unk_08, 0);
    memset(pObject, 0, Size);
    if (pDesc->NumB != 0) {
        pObject->pB = (UIGLibraryType_t *)(pObject + 1);
    }
    pObject->pA = (UIGLibraryType_t *)(pObject + 1) + pDesc->NumB;
    pObject->NumA = pDesc->NumA;
    pObject->NumB = pDesc->NumB;
    return pObject;
}

void UIGLibraryShutdown(UIGLibrary_t *pObject)
{
    Int32 i;
    Int32 Count;

    fn_80220BE0();
    if (pObject != NULL) {
        Count = pObject->NumA;
        for (i = 0; i < Count; i++) {
            UIGLibraryUnLoadItem(pObject, i, -2);
        }
        Count = pObject->NumB;
        for (i = 0; i < Count; i++) {
            _UIGLibraryClose(pObject, i, &pObject->pB[i]);
        }
        memset(pObject, 0, sizeof(UIGLibrary_t));
        fn_801D2BD0(pObject);
    }
}

void UIGLibrarySetDevice(UIGLibrary_t *pObject, Int32 Index, const char *pName, Int32 a, Int32 b)
{
    UIGLibraryType_t *pEntry;

    pEntry = &pObject->pB[Index];
    pEntry->Flags = 0x80000000;
    pEntry->pData = ResOpenDevice(pName, 44);
    pEntry->u.unk_0C = (Int32)pName;
    pEntry->unk_00 = a;
    pEntry->unk_04 = b;
}

void UIGLibrarySet(UIGLibrary_t *pObject, Int32 Index, Int32 Name, Int32 a, Int32 b,
                 Uint32 Flags)
{
    UIGLibraryType_t *pEntry;

    pEntry = &pObject->pA[Index];
    pEntry->Flags = Flags;
    pEntry->unk_00 = a;
    pEntry->unk_08 = b;
    pEntry->unk_04 = 0;
    pEntry->pData = NULL;
    if (Name & 0x42000000) {
        pEntry->u.Ref.Index = (Name >> 16) & 0xFF;
        pEntry->Flags |= 0x80000000;
        pEntry->u.Ref.Item = Name;
    } else {
        pEntry->u.unk_0C = Name;
    }
    if (pEntry->Flags & 0x20) {
        _UIGLibraryOpen(pObject, Index, pEntry);
    }
    if (pEntry->Flags & 0x40) {
        UIGLibraryPreloadItem(pObject, Index, -1);
    }
}

void _UIGLibraryOpen(UIGLibrary_t *pObject, Int32 Index, UIGLibraryType_t *pEntry)
{
    UIGLibraryType_t *pParent;
    Int32 Size;

    UIGLibrarySetMemInfo(Index, -1);
    if (!(pEntry->Flags & 10)) {
        if (pEntry->Flags & 0x80000000) {
            pParent = &pObject->pB[pEntry->u.Ref.Index];
            pEntry->pData = ResOpenRam(pParent->pData, pEntry->u.Ref.Item, pParent->unk_00,
                                        pParent->unk_04);
        } else {
            pEntry->pData = ResOpenDevice((const char *)pEntry->u.unk_0C, 44);
        }
        pEntry->NumItems = ResGetNumResources(pEntry->pData);
        Size = pEntry->NumItems * sizeof(UIGLibraryItem_t);
        pEntry->pItems = fn_801D2B7C(Size, pObject->unk_00, 0);
        memset(pEntry->pItems, 0, Size);
        pEntry->bItems = 1;
    }
    UIGLibraryInitType(pObject, pEntry->Flags, Index);
    fn_80220BE0();
    UIGLibraryClearMemInfo();
}

void UIGLibrarySelfManagedInit(UIGLibrary_t *pObject, Int32 Index, Int32 Count)
{
    UIGLibraryType_t *pEntry;
    Int32 Size;

    pEntry = &pObject->pA[Index];
    pEntry->NumItems = Count;
    Size = pEntry->NumItems * sizeof(UIGLibraryItem_t);
    pEntry->pItems = fn_801D2B7C(Size, pObject->unk_00, 0);
    memset(pEntry->pItems, 0, Size);
    pEntry->bItems = 1;
}

Int32 UIGLibraryLoadItem(UIGLibrary_t *pObject, Int32 Index, Int32 Item)
{
    UIGLibraryType_t *pEntry;
    UIGLibraryItem_t *pItem;
    Int32 Result;
    Int32 First;
    Int32 End;
    Int32 i;

    pEntry = &pObject->pA[Index];
    Result = 0;
    if (pEntry->Flags == 0) {
        return 0;
    }
    if (pEntry->bItems == 0) {
        _UIGLibraryOpen(pObject, Index, pEntry);
    }
    if (Item == -1) {
        First = 0;
        End = pEntry->NumItems;
    } else {
        First = Item;
        End = First + 1;
    }
    if (pEntry->Flags & 0x10) {
        pItem = &pEntry->pItems[Item];
        if ((pItem->unk_04 != 0 || pItem->unk_02 == 1) && (pEntry->Flags & 0x80)) {
            pItem->unk_00++;
        } else {
            if (!(pEntry->Flags & 10)) {
                pItem->unk_00++;
                if (pItem->unk_00 == 1 && pItem->unk_03 == 0) {
                    pItem->unk_02 = 1;
                }
                if (ResIsLoading(pEntry->pData, Item) == 0) {
                    UIGLibrarySetMemInfo(Index, Item);
                    UIGLibrarySetLoadFlags(pEntry->Flags);
                    Result = ResLoadAsync(pEntry->pData, Item, pEntry->unk_00, 100, _UIGLibraryAsyncCallback, pItem);
                    UIGLibraryClearLoadFlags();
                    UIGLibraryClearMemInfo();
                }
            }
            if (pItem->unk_02 == 1) {
                Result = 0;
            } else {
                UIGLibraryLoadType(pObject, pEntry->Flags, Index, Item, Result);
            }
        }
    } else {
        for (i = First; i < End; i++) {
            pItem = &pEntry->pItems[i];
            if (pItem->unk_04 != 0 && (pEntry->Flags & 0x80)) {
                pItem->unk_00++;
            } else {
                if (!(pEntry->Flags & 10) && ResGetSize(pEntry->pData, i) != 0) {
                    UIGLibrarySetMemInfo(Index, i);
                    UIGLibrarySetLoadFlags(pEntry->Flags);
                    Result = ResLoad(pEntry->pData, i, pEntry->unk_00);
                    UIGLibraryClearLoadFlags();
                    UIGLibraryClearMemInfo();
                }
                pItem->unk_00++;
                UIGLibraryLoadType(pObject, pEntry->Flags, Index, i, Result);
            }
        }
    }
    return Result;
}

Int32 UIGLibraryPreloadItem(UIGLibrary_t *pObject, Int32 Index, Int32 Item)
{
    UIGLibraryType_t *pEntry;
    Int32 Result;
    Int32 bAll;
    Int32 First;
    Int32 End;

    pEntry = &pObject->pA[Index];
    Result = 0;
    bAll = 0;
    if (pEntry->bItems == 0) {
        _UIGLibraryOpen(pObject, Index, pEntry);
    }
    if (Item == -1) {
        First = 0;
        End = pEntry->NumItems;
    } else {
        First = Item;
        End = Item + 1;
    }
    if (Item == -1) {
        if (pEntry->Flags & 10) {
            bAll = 0;
        } else if (pEntry->Flags & 4) {
            bAll = ResGetAlignment(pEntry->pData) == 128;
        } else {
            bAll = 1;
        }
    }
    if (bAll) {
        UIGLibrarySetMemInfo(Index, 0);
        UIGLibrarySetLoadFlags(pEntry->Flags);
        ResLoadAll(pEntry->pData, pEntry->unk_00, 1);
        UIGLibraryClearLoadFlags();
        UIGLibraryClearMemInfo();
    } else if (!(pEntry->Flags & 10)) {
        for (Item = First; Item < End; Item++) {
            if (ResGetSize(pEntry->pData, Item) != 0) {
                UIGLibrarySetMemInfo(Index, Item);
                UIGLibrarySetLoadFlags(pEntry->Flags);
                Result = ResLoad(pEntry->pData, Item, pEntry->unk_00);
                UIGLibraryClearLoadFlags();
                UIGLibraryClearMemInfo();
            }
        }
    }
    for (Item = First; Item < End; Item++) {
        pEntry->pItems[Item].unk_03++;
    }
    return Result;
}

Int32 UIGLibraryGetItemData(UIGLibrary_t *pObject, Int32 Index, Int32 Item)
{
    UIGLibraryType_t *pEntry;
    UIGLibraryItem_t *pItem;

    pEntry = &pObject->pA[Index];
    pItem = &pEntry->pItems[Item];
    return pItem->unk_04;
}

void UIGLibrarySetItemData(UIGLibrary_t *pObject, Int32 Index, Int32 Item, Int32 Value)
{
    UIGLibraryType_t *pEntry;
    UIGLibraryItem_t *pItem;

    pEntry = &pObject->pA[Index];
    pItem = &pEntry->pItems[Item];
    pItem->unk_04 = Value;
    if (Value != 0) {
        pItem->unk_02 = 0;
    }
}

Int16 UIGLibraryReferenceCount(UIGLibrary_t *pObject, Int32 Index, Int32 Item)
{
    UIGLibraryType_t *pEntry;
    UIGLibraryItem_t *pItem;

    pEntry = &pObject->pA[Index];
    if (pEntry->bItems == 0) {
        _UIGLibraryOpen(pObject, Index, pEntry);
    }
    pItem = &pEntry->pItems[Item];
    return pItem->unk_00;
}

void UIGLibraryUnLoadItem(UIGLibrary_t *pObject, Int32 Index, Int32 Item)
{
    UIGLibraryType_t *pEntry;
    UIGLibraryItem_t *pItem;
    Int32 bInUse;
    Int32 i;

    pEntry = &pObject->pA[Index];
    bInUse = 0;
    if (pEntry->pItems == NULL) {
        return;
    }
    if (Item == -1 || Item == -2) {
        for (i = 0; i < pEntry->NumItems; i++) {
            pItem = &pEntry->pItems[i];
            if (pItem->unk_00 != 0) {
                if (Item == -2) {
                    pItem->unk_00 = 0;
                } else {
                    pItem->unk_00--;
                }
                if (pItem->unk_00 == 0) {
                    UIGLibraryUnLoadType(pObject, pEntry->Flags, Index, i);
                } else {
                    bInUse = 1;
                }
            }
        }
        if (bInUse == 0) {
            if (!(pEntry->Flags & 10)) {
                ResUnLoadAll(pEntry->pData);
            }
            _UIGLibraryClose(pObject, Index, pEntry);
            if (Item == -2) {
                pEntry->Flags = 0;
            }
        }
    } else {
        pItem = &pEntry->pItems[Item];
        pItem->unk_00--;
        if ((pEntry->Flags & 0x10) && pItem->unk_00 < 0) {
            pItem->unk_00 = 0;
            if (!(pEntry->Flags & 10) && pItem->unk_03 == 0 && UIGLibraryIsItemLoaded(pEntry, Item) != 0) {
                ResUnLoad(pEntry->pData, Item);
                pItem->unk_02 = 0;
            }
        } else if (pItem->unk_00 <= 0) {
            UIGLibraryUnLoadType(pObject, pEntry->Flags, Index, Item);
            if (!(pEntry->Flags & 10) && pItem->unk_03 == 0 && UIGLibraryIsItemLoaded(pEntry, Item) != 0) {
                ResUnLoad(pEntry->pData, Item);
                pItem->unk_02 = 0;
            }
        }
    }
}

Uint32 UIGLibraryGetType(UIGLibrary_t *pObject, Int32 Index)
{
    UIGLibraryType_t *pEntry;

    pEntry = &pObject->pA[Index];
    return pEntry->Flags & 0x7FFFFFFF;
}

Int32 UIGLibraryGetVramHeapID(UIGLibrary_t *pObject, Int32 Index)
{
    UIGLibraryType_t *pEntry;

    pEntry = &pObject->pA[Index];
    return pEntry->unk_08;
}

void _UIGLibraryAsyncCallback(void *pRes, unsigned int index, void *pBuffer, unsigned int err, void *pUser)
{
    _UIGLibraryFlushCache(pRes, index, pBuffer, err, pUser);
}

Int32 UIGLibraryGetFilename(UIGLibrary_t *pObject, Int32 Index)
{
    UIGLibraryType_t *pEntry;

    pEntry = &pObject->pA[Index];
    return pEntry->u.unk_0C;
}

void *UIGLibraryGetResFile(UIGLibrary_t *pObject, Int32 Index)
{
    UIGLibraryType_t *pEntry;

    pEntry = &pObject->pA[Index];
    return pEntry->pData;
}

void UIGLibrarySetResFile(UIGLibrary_t *pObject, Int32 Index, void *pData)
{
    UIGLibraryType_t *pEntry;

    pEntry = &pObject->pA[Index];
    pEntry->pData = pData;
}

void _UIGLibraryClose(UIGLibrary_t *pObject, Int32 Index, UIGLibraryType_t *pEntry)
{
    if (pEntry->Flags != 0) {
        UIGLibraryShutdownType(pObject, pEntry->Flags, Index);
        if (!(pEntry->Flags & 10) && pEntry->pData != NULL) {
            ResClose(pEntry->pData);
            pEntry->pData = NULL;
        }
        if (pEntry->pItems != NULL) {
            fn_801D2BD0(pEntry->pItems);
        }
        pEntry->bItems = 0;
        pEntry->unk_18 = 0;
        pEntry->NumItems = 0;
        pEntry->pItems = NULL;
    }
}

void UIGLibrarySetGlobal(Int32 Index, UIGLibrary_t *pObject)
{
    _pLibraryInfo[Index] = pObject;
}

UIGLibrary_t *UIGLibraryGetGlobal(Int32 Index)
{
    return _pLibraryInfo[Index];
}

Int32 UIGLibraryIsItemDataAvailable(UIGLibrary_t *pObject, Int32 Index, Int32 Item)
{
    UIGLibraryType_t *pEntry;
    UIGLibraryItem_t *pItem;
    Int32 Result;

    pEntry = &pObject->pA[Index];
    pItem = &pEntry->pItems[Item];
    Result = 0;
    if ((pEntry->Flags & 0x10) && pItem->unk_04 == 0 && !(pEntry->Flags & 10) &&
        ResIsLoaded(pEntry->pData, Item) != 0) {
        UIGLibrarySetMemInfo(Index, Item);
        UIGLibrarySetLoadFlags(pEntry->Flags);
        Result = ResLoad(pEntry->pData, Item, pEntry->unk_00);
        UIGLibraryClearLoadFlags();
        UIGLibraryClearMemInfo();
    }
    if (pItem->unk_00 != 0) {
        UIGLibraryLoadType(pObject, pEntry->Flags, Index, Item, Result);
    }
    return pItem->unk_04;
}

void UIGLibrarySetData(UIGLibrary_t *pObject, Int32 Index, Int32 Value)
{
    UIGLibraryType_t *pEntry;

    pEntry = &pObject->pA[Index];
    pEntry->unk_18 = Value;
}

Int32 UIGLibraryGetData(UIGLibrary_t *pObject, Int32 Index)
{
    UIGLibraryType_t *pEntry;

    pEntry = &pObject->pA[Index];
    return pEntry->unk_18;
}

void UIGLibraryUnLoadType(UIGLibrary_t *pObject, Uint32 Flags, Int32 a, Int32 b)
{
    if (Flags & 4) {
        UIGTexNodeUnLoad(pObject, a, b);
    } else if (Flags & 8) {
        UIGFontDestroyFont(pObject, a, b);
    } else if (Flags & 2) {
        UIGFmvDeleteInstance(pObject, a, b);
    }
}

void UIGLibraryLoadType(UIGLibrary_t *pObject, Uint32 Flags, Int32 Index, Int32 Item, Int32 Value)
{
    UIGLibrarySetMemInfo(Index, Item);
    if (Flags & 4) {
        UIGTexNodeLoad(pObject, Index, Item, Value);
    } else if (Flags & 8) {
        UIGFontCreateFont(pObject, Index, Item, Value);
    } else if (Flags & 2) {
        UIGFmvAddInstance(pObject, Index, Item);
    }
    if ((Flags & 0x8A) == 0x80 && Value != 0 && pObject->pA[Index].pItems[Item].unk_03 == 0) {
        ResUnLoad(pObject->pA[Index].pData, Item);
        pObject->pA[Index].pItems[Item].unk_02 = 0;
    }
    UIGLibraryClearMemInfo();
}

void UIGLibraryInitType(UIGLibrary_t *pObject, Uint32 Flags, Int32 a)
{
    if (!(Flags & 4)) {
        if (Flags & 8) {
            UIGFontCreateFontLibrary(pObject, a);
        } else if (Flags & 2) {
            UIGFmvInit(pObject, a);
        }
    }
    fn_80220BE0();
}

void UIGLibraryShutdownType(UIGLibrary_t *pObject, Uint32 Flags, Int32 a)
{
    if (!(Flags & 4)) {
        if (Flags & 8) {
            UIGFontDestroyFontLibrary(pObject, a);
        } else if (Flags & 2) {
            UIGFmvShutdown(pObject, a);
        }
    }
    fn_80220BE0();
}

void UIGLibraryProcessType(UIGLibrary_t *pObject, Uint32 Flags, Int32 a, Int32 b)
{
    if (!(Flags & 4)) {
        if (!(Flags & 8)) {
            if (Flags & 2) {
                UIGFmvProcess(pObject, a, b);
            }
        }
    }
}

void UIGLibraryProcess(UIGLibrary_t *pObject)
{
    Int32 Index;
    Int32 NumA;
    Int32 Item;
    Int32 NumItems;
    UIGLibraryType_t *pEntry;

    if (pObject != 0) {
        NumA = pObject->NumA;
        for (Index = 0; Index < NumA; Index++) {
            pEntry = &pObject->pA[Index];
            NumItems = pEntry->NumItems;
            for (Item = 0; Item < NumItems; Item++) {
                UIGLibraryProcessType(pObject, pEntry->Flags, Index, Item);
            }
        }
    }
}

Int32 UIGLibraryIsItemLoading(UIGLibrary_t *pObject, Int32 Index, Int32 Item)
{
    UIGLibraryType_t *pEntry;

    pEntry = &pObject->pA[Index];
    if (pEntry->Flags & 0x10) {
        return ResIsLoading(pEntry->pData, Item);
    }
    return 0;
}

void _UIGLibraryFlushCache(void *pRes, unsigned int index, void *pBuffer, unsigned int err, void *pUser)
{
}

void UIGLibraryMoveItem(UIGLibrary_t *pObject, Int32 a, Int32 b, Int32 c, Int32 d)
{
    UIGLibraryType_t *pDst;
    UIGLibraryType_t *pSrc;
    UIGLibraryItem_t *pDstItem;
    UIGLibraryItem_t *pSrcItem;
    Int32 Value;

    pDst = &pObject->pA[a];
    pSrc = &pObject->pA[c];
    Value = UIGLibraryGetItemData(pObject, c, d);
    UIGLibrarySetItemData(pObject, c, d, 0);
    UIGLibrarySetItemData(pObject, a, b, Value);
    pSrcItem = &pSrc->pItems[d];
    pDstItem = &pDst->pItems[b];
    pSrcItem->unk_00--;
    pDstItem->unk_00++;
}

void UIGLibrarySetMemInfo(Int32 a, Int32 b)
{
    if (_UIGLibraryMemInfoFunc != 0) {
        _UIGLibraryMemInfoFunc(a, b);
    }
}

void UIGLibraryClearMemInfo(void)
{
    if (_UIGLibraryMemInfoFunc != 0) {
        _UIGLibraryMemInfoFunc(-1, -1);
    }
}

void UIGLibrarySetLoadFlagsFunc(UIGLibraryLoadFlagsFunc_t *pCallback)
{
    _UIGLibraryLoadFlagsFunc = pCallback;
}

void UIGLibrarySetLoadFlags(Int32 a)
{
    if (_UIGLibraryLoadFlagsFunc != 0) {
        _UIGLibraryLoadFlagsFunc(a);
    }
}

void UIGLibraryClearLoadFlags(void)
{
    if (_UIGLibraryLoadFlagsFunc != 0) {
        _UIGLibraryLoadFlagsFunc(0);
    }
}
