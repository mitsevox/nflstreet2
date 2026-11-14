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

static Object_8021E688 *lbl_803EBF38[2] = { 0 };
static Callback_803EBF40 *lbl_803EBF40 = 0;
static Callback_803EBF44 *lbl_803EBF44 = 0;

Int32 fn_8021DE9C(Entry_8021E688 *pEntry, Int32 Item)
{
    Int32 Result;
    Item_8021E688 *pItem;

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

Object_8021E688 *fn_8021DEFC(UISResListDesc *pDesc)
{
    Int32 Size;
    Object_8021E688 *pObject;

    fn_80220BE0();
    Size = pDesc->NumA * sizeof(Entry_8021E688) + sizeof(Object_8021E688) +
           pDesc->NumB * sizeof(Entry_8021E688);
    pObject = fn_801D2B7C(Size, pDesc->unk_08, 0);
    memset(pObject, 0, Size);
    if (pDesc->NumB != 0) {
        pObject->pB = (Entry_8021E688 *)(pObject + 1);
    }
    pObject->pA = (Entry_8021E688 *)(pObject + 1) + pDesc->NumB;
    pObject->NumA = pDesc->NumA;
    pObject->NumB = pDesc->NumB;
    return pObject;
}

void fn_8021DF9C(Object_8021E688 *pObject)
{
    Int32 i;
    Int32 Count;

    fn_80220BE0();
    if (pObject != NULL) {
        Count = pObject->NumA;
        for (i = 0; i < Count; i++) {
            fn_8021E72C(pObject, i, -2);
        }
        Count = pObject->NumB;
        for (i = 0; i < Count; i++) {
            fn_8021E9AC(pObject, i, &pObject->pB[i]);
        }
        memset(pObject, 0, sizeof(Object_8021E688));
        fn_801D2BD0(pObject);
    }
}

void fn_8021E050(Object_8021E688 *pObject, Int32 Index, const char *pName, Int32 a, Int32 b)
{
    Entry_8021E688 *pEntry;

    pEntry = &pObject->pB[Index];
    pEntry->Flags = 0x80000000;
    pEntry->pData = ResOpenDevice(pName, 44);
    pEntry->u.unk_0C = (Int32)pName;
    pEntry->unk_00 = a;
    pEntry->unk_04 = b;
}

void fn_8021E0B0(Object_8021E688 *pObject, Int32 Index, Int32 Name, Int32 a, Int32 b,
                 Uint32 Flags)
{
    Entry_8021E688 *pEntry;

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
        fn_8021E160(pObject, Index, pEntry);
    }
    if (pEntry->Flags & 0x40) {
        fn_8021E504(pObject, Index, -1);
    }
}

void fn_8021E160(Object_8021E688 *pObject, Int32 Index, Entry_8021E688 *pEntry)
{
    Entry_8021E688 *pParent;
    Int32 Size;

    fn_8021EF04(Index, -1);
    if (!(pEntry->Flags & 10)) {
        if (pEntry->Flags & 0x80000000) {
            pParent = &pObject->pB[pEntry->u.Ref.Index];
            pEntry->pData = ResOpenRam(pParent->pData, pEntry->u.Ref.Item, pParent->unk_00,
                                        pParent->unk_04);
        } else {
            pEntry->pData = ResOpenDevice((const char *)pEntry->u.unk_0C, 44);
        }
        pEntry->NumItems = ResGetNumResources(pEntry->pData);
        Size = pEntry->NumItems * sizeof(Item_8021E688);
        pEntry->pItems = fn_801D2B7C(Size, pObject->unk_00, 0);
        memset(pEntry->pItems, 0, Size);
        pEntry->bItems = 1;
    }
    fn_8021ECB0(pObject, pEntry->Flags, Index);
    fn_80220BE0();
    fn_8021EF34();
}

void fn_8021E244(Object_8021E688 *pObject, Int32 Index, Int32 Count)
{
    Entry_8021E688 *pEntry;
    Int32 Size;

    pEntry = &pObject->pA[Index];
    pEntry->NumItems = Count;
    Size = pEntry->NumItems * sizeof(Item_8021E688);
    pEntry->pItems = fn_801D2B7C(Size, pObject->unk_00, 0);
    memset(pEntry->pItems, 0, Size);
    pEntry->bItems = 1;
}

Int32 fn_8021E2B4(Object_8021E688 *pObject, Int32 Index, Int32 Item)
{
    Entry_8021E688 *pEntry;
    Item_8021E688 *pItem;
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
        fn_8021E160(pObject, Index, pEntry);
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
                    fn_8021EF04(Index, Item);
                    fn_8021EF74(pEntry->Flags);
                    Result = ResLoadAsync(pEntry->pData, Item, pEntry->unk_00, 100, fn_8021E950, pItem);
                    fn_8021EFA4();
                    fn_8021EF34();
                }
            }
            if (pItem->unk_02 == 1) {
                Result = 0;
            } else {
                fn_8021EBB4(pObject, pEntry->Flags, Index, Item, Result);
            }
        }
    } else {
        for (i = First; i < End; i++) {
            pItem = &pEntry->pItems[i];
            if (pItem->unk_04 != 0 && (pEntry->Flags & 0x80)) {
                pItem->unk_00++;
            } else {
                if (!(pEntry->Flags & 10) && ResGetSize(pEntry->pData, i) != 0) {
                    fn_8021EF04(Index, i);
                    fn_8021EF74(pEntry->Flags);
                    Result = ResLoad(pEntry->pData, i, pEntry->unk_00);
                    fn_8021EFA4();
                    fn_8021EF34();
                }
                pItem->unk_00++;
                fn_8021EBB4(pObject, pEntry->Flags, Index, i, Result);
            }
        }
    }
    return Result;
}

Int32 fn_8021E504(Object_8021E688 *pObject, Int32 Index, Int32 Item)
{
    Entry_8021E688 *pEntry;
    Int32 Result;
    Int32 bAll;
    Int32 First;
    Int32 End;

    pEntry = &pObject->pA[Index];
    Result = 0;
    bAll = 0;
    if (pEntry->bItems == 0) {
        fn_8021E160(pObject, Index, pEntry);
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
        fn_8021EF04(Index, 0);
        fn_8021EF74(pEntry->Flags);
        ResLoadAll(pEntry->pData, pEntry->unk_00, 1);
        fn_8021EFA4();
        fn_8021EF34();
    } else if (!(pEntry->Flags & 10)) {
        for (Item = First; Item < End; Item++) {
            if (ResGetSize(pEntry->pData, Item) != 0) {
                fn_8021EF04(Index, Item);
                fn_8021EF74(pEntry->Flags);
                Result = ResLoad(pEntry->pData, Item, pEntry->unk_00);
                fn_8021EFA4();
                fn_8021EF34();
            }
        }
    }
    for (Item = First; Item < End; Item++) {
        pEntry->pItems[Item].unk_03++;
    }
    return Result;
}

Int32 fn_8021E688(Object_8021E688 *pObject, Int32 Index, Int32 Item)
{
    Entry_8021E688 *pEntry;
    Item_8021E688 *pItem;

    pEntry = &pObject->pA[Index];
    pItem = &pEntry->pItems[Item];
    return pItem->unk_04;
}

void fn_8021E6A8(Object_8021E688 *pObject, Int32 Index, Int32 Item, Int32 Value)
{
    Entry_8021E688 *pEntry;
    Item_8021E688 *pItem;

    pEntry = &pObject->pA[Index];
    pItem = &pEntry->pItems[Item];
    pItem->unk_04 = Value;
    if (Value != 0) {
        pItem->unk_02 = 0;
    }
}

Int16 fn_8021E6D8(Object_8021E688 *pObject, Int32 Index, Int32 Item)
{
    Entry_8021E688 *pEntry;
    Item_8021E688 *pItem;

    pEntry = &pObject->pA[Index];
    if (pEntry->bItems == 0) {
        fn_8021E160(pObject, Index, pEntry);
    }
    pItem = &pEntry->pItems[Item];
    return pItem->unk_00;
}

void fn_8021E72C(Object_8021E688 *pObject, Int32 Index, Int32 Item)
{
    Entry_8021E688 *pEntry;
    Item_8021E688 *pItem;
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
                    fn_8021EB54(pObject, pEntry->Flags, Index, i);
                } else {
                    bInUse = 1;
                }
            }
        }
        if (bInUse == 0) {
            if (!(pEntry->Flags & 10)) {
                ResUnLoadAll(pEntry->pData);
            }
            fn_8021E9AC(pObject, Index, pEntry);
            if (Item == -2) {
                pEntry->Flags = 0;
            }
        }
    } else {
        pItem = &pEntry->pItems[Item];
        pItem->unk_00--;
        if ((pEntry->Flags & 0x10) && pItem->unk_00 < 0) {
            pItem->unk_00 = 0;
            if (!(pEntry->Flags & 10) && pItem->unk_03 == 0 && fn_8021DE9C(pEntry, Item) != 0) {
                ResUnLoad(pEntry->pData, Item);
                pItem->unk_02 = 0;
            }
        } else if (pItem->unk_00 <= 0) {
            fn_8021EB54(pObject, pEntry->Flags, Index, Item);
            if (!(pEntry->Flags & 10) && pItem->unk_03 == 0 && fn_8021DE9C(pEntry, Item) != 0) {
                ResUnLoad(pEntry->pData, Item);
                pItem->unk_02 = 0;
            }
        }
    }
}

Uint32 fn_8021E924(Object_8021E688 *pObject, Int32 Index)
{
    Entry_8021E688 *pEntry;

    pEntry = &pObject->pA[Index];
    return pEntry->Flags & 0x7FFFFFFF;
}

Int32 fn_8021E93C(Object_8021E688 *pObject, Int32 Index)
{
    Entry_8021E688 *pEntry;

    pEntry = &pObject->pA[Index];
    return pEntry->unk_08;
}

void fn_8021E950(void *pRes, unsigned int index, void *pBuffer, unsigned int err, void *pUser)
{
    fn_8021EE54(pRes, index, pBuffer, err, pUser);
}

Int32 fn_8021E970(Object_8021E688 *pObject, Int32 Index)
{
    Entry_8021E688 *pEntry;

    pEntry = &pObject->pA[Index];
    return pEntry->u.unk_0C;
}

void *fn_8021E984(Object_8021E688 *pObject, Int32 Index)
{
    Entry_8021E688 *pEntry;

    pEntry = &pObject->pA[Index];
    return pEntry->pData;
}

void fn_8021E998(Object_8021E688 *pObject, Int32 Index, void *pData)
{
    Entry_8021E688 *pEntry;

    pEntry = &pObject->pA[Index];
    pEntry->pData = pData;
}

void fn_8021E9AC(Object_8021E688 *pObject, Int32 Index, Entry_8021E688 *pEntry)
{
    if (pEntry->Flags != 0) {
        fn_8021ECFC(pObject, pEntry->Flags, Index);
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

void fn_8021EA34(Int32 Index, Object_8021E688 *pObject)
{
    lbl_803EBF38[Index] = pObject;
}

Object_8021E688 *fn_8021EA44(Int32 Index)
{
    return lbl_803EBF38[Index];
}

Int32 fn_8021EA54(Object_8021E688 *pObject, Int32 Index, Int32 Item)
{
    Entry_8021E688 *pEntry;
    Item_8021E688 *pItem;
    Int32 Result;

    pEntry = &pObject->pA[Index];
    pItem = &pEntry->pItems[Item];
    Result = 0;
    if ((pEntry->Flags & 0x10) && pItem->unk_04 == 0 && !(pEntry->Flags & 10) &&
        ResIsLoaded(pEntry->pData, Item) != 0) {
        fn_8021EF04(Index, Item);
        fn_8021EF74(pEntry->Flags);
        Result = ResLoad(pEntry->pData, Item, pEntry->unk_00);
        fn_8021EFA4();
        fn_8021EF34();
    }
    if (pItem->unk_00 != 0) {
        fn_8021EBB4(pObject, pEntry->Flags, Index, Item, Result);
    }
    return pItem->unk_04;
}

void fn_8021EB2C(Object_8021E688 *pObject, Int32 Index, Int32 Value)
{
    Entry_8021E688 *pEntry;

    pEntry = &pObject->pA[Index];
    pEntry->unk_18 = Value;
}

Int32 fn_8021EB40(Object_8021E688 *pObject, Int32 Index)
{
    Entry_8021E688 *pEntry;

    pEntry = &pObject->pA[Index];
    return pEntry->unk_18;
}

void fn_8021EB54(Object_8021E688 *pObject, Uint32 Flags, Int32 a, Int32 b)
{
    if (Flags & 4) {
        fn_80221314(pObject, a, b);
    } else if (Flags & 8) {
        fn_80225F10(pObject, a, b);
    } else if (Flags & 2) {
        fn_802262C4(pObject, a, b);
    }
}

void fn_8021EBB4(Object_8021E688 *pObject, Uint32 Flags, Int32 Index, Int32 Item, Int32 Value)
{
    fn_8021EF04(Index, Item);
    if (Flags & 4) {
        fn_80221374(pObject, Index, Item, Value);
    } else if (Flags & 8) {
        fn_80225E64(pObject, Index, Item, Value);
    } else if (Flags & 2) {
        fn_802261D4(pObject, Index, Item);
    }
    if ((Flags & 0x8A) == 0x80 && Value != 0 && pObject->pA[Index].pItems[Item].unk_03 == 0) {
        ResUnLoad(pObject->pA[Index].pData, Item);
        pObject->pA[Index].pItems[Item].unk_02 = 0;
    }
    fn_8021EF34();
}

void fn_8021ECB0(Object_8021E688 *pObject, Uint32 Flags, Int32 a)
{
    if (!(Flags & 4)) {
        if (Flags & 8) {
            fn_80225D90(pObject, a);
        } else if (Flags & 2) {
            fn_802260F8(pObject, a);
        }
    }
    fn_80220BE0();
}

void fn_8021ECFC(Object_8021E688 *pObject, Uint32 Flags, Int32 a)
{
    if (!(Flags & 4)) {
        if (Flags & 8) {
            fn_80225E10(pObject, a);
        } else if (Flags & 2) {
            fn_8022615C(pObject, a);
        }
    }
    fn_80220BE0();
}

void fn_8021ED48(Object_8021E688 *pObject, Uint32 Flags, Int32 a, Int32 b)
{
    if (!(Flags & 4)) {
        if (!(Flags & 8)) {
            if (Flags & 2) {
                fn_8022618C(pObject, a, b);
            }
        }
    }
}

void fn_8021ED88(Object_8021E688 *pObject)
{
    Int32 Index;
    Int32 NumA;
    Int32 Item;
    Int32 NumItems;
    Entry_8021E688 *pEntry;

    if (pObject != 0) {
        NumA = pObject->NumA;
        for (Index = 0; Index < NumA; Index++) {
            pEntry = &pObject->pA[Index];
            NumItems = pEntry->NumItems;
            for (Item = 0; Item < NumItems; Item++) {
                fn_8021ED48(pObject, pEntry->Flags, Index, Item);
            }
        }
    }
}

Int32 fn_8021EE10(Object_8021E688 *pObject, Int32 Index, Int32 Item)
{
    Entry_8021E688 *pEntry;

    pEntry = &pObject->pA[Index];
    if (pEntry->Flags & 0x10) {
        return ResIsLoading(pEntry->pData, Item);
    }
    return 0;
}

void fn_8021EE54(void *pRes, unsigned int index, void *pBuffer, unsigned int err, void *pUser)
{
}

void fn_8021EE58(Object_8021E688 *pObject, Int32 a, Int32 b, Int32 c, Int32 d)
{
    Entry_8021E688 *pDst;
    Entry_8021E688 *pSrc;
    Item_8021E688 *pDstItem;
    Item_8021E688 *pSrcItem;
    Int32 Value;

    pDst = &pObject->pA[a];
    pSrc = &pObject->pA[c];
    Value = fn_8021E688(pObject, c, d);
    fn_8021E6A8(pObject, c, d, 0);
    fn_8021E6A8(pObject, a, b, Value);
    pSrcItem = &pSrc->pItems[d];
    pDstItem = &pDst->pItems[b];
    pSrcItem->unk_00--;
    pDstItem->unk_00++;
}

void fn_8021EF04(Int32 a, Int32 b)
{
    if (lbl_803EBF40 != 0) {
        lbl_803EBF40(a, b);
    }
}

void fn_8021EF34(void)
{
    if (lbl_803EBF40 != 0) {
        lbl_803EBF40(-1, -1);
    }
}

void fn_8021EF6C(Callback_803EBF44 *pCallback)
{
    lbl_803EBF44 = pCallback;
}

void fn_8021EF74(Int32 a)
{
    if (lbl_803EBF44 != 0) {
        lbl_803EBF44(a);
    }
}

void fn_8021EFA4(void)
{
    if (lbl_803EBF44 != 0) {
        lbl_803EBF44(0);
    }
}
