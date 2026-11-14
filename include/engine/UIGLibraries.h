#ifndef ENGINE_UIGLIBRARIES_H
#define ENGINE_UIGLIBRARIES_H

#include "types.h"

/* 8-byte item of an UIGLibraryType_t item array. */
typedef struct UIGLibraryItem_t {
    Int16 unk_00;     /* 0x00 */
    Uint8 unk_02;     /* 0x02 */
    signed char unk_03; /* 0x03 */
    Int32 unk_04;     /* 0x04 */
} UIGLibraryItem_t;

/* 36-byte entry of the arrays at UIGLibrary_t +0x08 and +0x0C. */
typedef struct UIGLibraryType_t {
    Int32 unk_00;  /* 0x00 */
    Int32 unk_04;  /* 0x04 */
    Int32 unk_08;  /* 0x08 */
    union {
        Int32 unk_0C;
        struct {
            Uint16 Index; /* 0x0C: entry of the +0x08 array */
            Uint16 Item;  /* 0x0E */
        } Ref;
    } u;           /* 0x0C: a reference when Flags bit 31 is set */
    Uint32 Flags;  /* 0x10 */
    void *pData;   /* 0x14 */
    Int32 unk_18;  /* 0x18 */
    Uint16 bItems; /* 0x1C: set once pItems is allocated */
    Int16 NumItems;            /* 0x1E */
    UIGLibraryItem_t *pItems;     /* 0x20 */
} UIGLibraryType_t;

/* 16-byte header allocated by UIGLibraryInit, followed by its two entry
   arrays. */
typedef struct UIGLibrary_t {
    Int32 unk_00;              /* 0x00 */
    Uint16 NumA;               /* 0x04: number of entries at pA */
    Uint16 NumB;               /* 0x06: number of entries at pB */
    UIGLibraryType_t *pB;        /* 0x08 */
    UIGLibraryType_t *pA;        /* 0x0C */
} UIGLibrary_t;

/* 12-byte argument of UIGLibraryInit. */
typedef struct UISResListDesc {
    Int32 NumA;     /* 0x00 */
    Int32 NumB;     /* 0x04 */
    Int32 unk_08;   /* 0x08 */
} UISResListDesc;

typedef void UIGLibraryMemInfoFunc_t(Int32, Int32);
typedef void UIGLibraryLoadFlagsFunc_t(Int32);

#ifdef __cplusplus
extern "C" {
#endif

/* src/engine/UIGLibraries.c */
Int32 UIGLibraryIsItemLoaded(UIGLibraryType_t *pEntry, Int32 Item);
UIGLibrary_t *UIGLibraryInit(UISResListDesc *pDesc);
void UIGLibraryShutdown(UIGLibrary_t *pObject);
void UIGLibrarySetDevice(UIGLibrary_t *pObject, Int32 Index, const char *pName, Int32 a, Int32 b);
void UIGLibrarySet(UIGLibrary_t *pObject, Int32 Index, Int32 Name, Int32 a, Int32 b,
                 Uint32 Flags);
void _UIGLibraryOpen(UIGLibrary_t *pObject, Int32 Index, UIGLibraryType_t *pEntry);
void UIGLibrarySelfManagedInit(UIGLibrary_t *pObject, Int32 Index, Int32 Count);
Int32 UIGLibraryLoadItem(UIGLibrary_t *pObject, Int32 Index, Int32 Item);
Int32 UIGLibraryPreloadItem(UIGLibrary_t *pObject, Int32 Index, Int32 Item);
Int32 UIGLibraryGetItemData(UIGLibrary_t *pObject, Int32 Index, Int32 Item);
void UIGLibrarySetItemData(UIGLibrary_t *pObject, Int32 Index, Int32 Item, Int32 Value);
Int16 UIGLibraryReferenceCount(UIGLibrary_t *pObject, Int32 Index, Int32 Item);
void UIGLibraryUnLoadItem(UIGLibrary_t *pObject, Int32 Index, Int32 Item);
Uint32 UIGLibraryGetType(UIGLibrary_t *pObject, Int32 Index);
Int32 UIGLibraryGetVramHeapID(UIGLibrary_t *pObject, Int32 Index);
void _UIGLibraryAsyncCallback(void *pRes, unsigned int index, void *pBuffer, unsigned int err, void *pUser);
Int32 UIGLibraryGetFilename(UIGLibrary_t *pObject, Int32 Index);
void *UIGLibraryGetResFile(UIGLibrary_t *pObject, Int32 Index);
void UIGLibrarySetResFile(UIGLibrary_t *pObject, Int32 Index, void *pData);
void _UIGLibraryClose(UIGLibrary_t *pObject, Int32 Index, UIGLibraryType_t *pEntry);
void UIGLibrarySetGlobal(Int32 Index, UIGLibrary_t *pObject);
UIGLibrary_t *UIGLibraryGetGlobal(Int32 Index);
Int32 UIGLibraryIsItemDataAvailable(UIGLibrary_t *pObject, Int32 Index, Int32 Item);
void UIGLibrarySetData(UIGLibrary_t *pObject, Int32 Index, Int32 Value);
Int32 UIGLibraryGetData(UIGLibrary_t *pObject, Int32 Index);
void UIGLibraryUnLoadType(UIGLibrary_t *pObject, Uint32 Flags, Int32 a, Int32 b);
void UIGLibraryLoadType(UIGLibrary_t *pObject, Uint32 Flags, Int32 Index, Int32 Item, Int32 Value);
void UIGLibraryInitType(UIGLibrary_t *pObject, Uint32 Flags, Int32 a);
void UIGLibraryShutdownType(UIGLibrary_t *pObject, Uint32 Flags, Int32 a);
void UIGLibraryProcessType(UIGLibrary_t *pObject, Uint32 Flags, Int32 a, Int32 b);
void UIGLibraryProcess(UIGLibrary_t *pObject);
Int32 UIGLibraryIsItemLoading(UIGLibrary_t *pObject, Int32 Index, Int32 Item);
void _UIGLibraryFlushCache(void *pRes, unsigned int index, void *pBuffer, unsigned int err, void *pUser);
void UIGLibraryMoveItem(UIGLibrary_t *pObject, Int32 a, Int32 b, Int32 c, Int32 d);
void UIGLibrarySetMemInfo(Int32 a, Int32 b);
void UIGLibraryClearMemInfo(void);
void UIGLibrarySetLoadFlagsFunc(UIGLibraryLoadFlagsFunc_t *pCallback);
void UIGLibrarySetLoadFlags(Int32 a);
void UIGLibraryClearLoadFlags(void);

#ifdef __cplusplus
}
#endif

#endif
