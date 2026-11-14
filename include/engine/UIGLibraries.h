#ifndef ENGINE_UIGLIBRARIES_H
#define ENGINE_UIGLIBRARIES_H

#include "types.h"

/* 8-byte item of an Entry_8021E688 item array. */
typedef struct Item_8021E688 {
    Int16 unk_00;     /* 0x00 */
    Uint8 unk_02;     /* 0x02 */
    signed char unk_03; /* 0x03 */
    Int32 unk_04;     /* 0x04 */
} Item_8021E688;

/* 36-byte entry of the arrays at Object_8021E688 +0x08 and +0x0C. */
typedef struct Entry_8021E688 {
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
    Item_8021E688 *pItems;     /* 0x20 */
} Entry_8021E688;

/* 16-byte header allocated by fn_8021DEFC, followed by its two entry
   arrays. */
typedef struct Object_8021E688 {
    Int32 unk_00;              /* 0x00 */
    Uint16 NumA;               /* 0x04: number of entries at pA */
    Uint16 NumB;               /* 0x06: number of entries at pB */
    Entry_8021E688 *pB;        /* 0x08 */
    Entry_8021E688 *pA;        /* 0x0C */
} Object_8021E688;

/* 12-byte argument of fn_8021DEFC. */
typedef struct UISResListDesc {
    Int32 NumA;     /* 0x00 */
    Int32 NumB;     /* 0x04 */
    Int32 unk_08;   /* 0x08 */
} UISResListDesc;

typedef void Callback_803EBF40(Int32, Int32);
typedef void Callback_803EBF44(Int32);

#ifdef __cplusplus
extern "C" {
#endif

/* src/engine/UIGLibraries.c */
Int32 fn_8021DE9C(Entry_8021E688 *pEntry, Int32 Item);
Object_8021E688 *fn_8021DEFC(UISResListDesc *pDesc);
void fn_8021DF9C(Object_8021E688 *pObject);
void fn_8021E050(Object_8021E688 *pObject, Int32 Index, const char *pName, Int32 a, Int32 b);
void fn_8021E0B0(Object_8021E688 *pObject, Int32 Index, Int32 Name, Int32 a, Int32 b,
                 Uint32 Flags);
void fn_8021E160(Object_8021E688 *pObject, Int32 Index, Entry_8021E688 *pEntry);
void fn_8021E244(Object_8021E688 *pObject, Int32 Index, Int32 Count);
Int32 fn_8021E2B4(Object_8021E688 *pObject, Int32 Index, Int32 Item);
Int32 fn_8021E504(Object_8021E688 *pObject, Int32 Index, Int32 Item);
Int32 fn_8021E688(Object_8021E688 *pObject, Int32 Index, Int32 Item);
void fn_8021E6A8(Object_8021E688 *pObject, Int32 Index, Int32 Item, Int32 Value);
Int16 fn_8021E6D8(Object_8021E688 *pObject, Int32 Index, Int32 Item);
void fn_8021E72C(Object_8021E688 *pObject, Int32 Index, Int32 Item);
Uint32 fn_8021E924(Object_8021E688 *pObject, Int32 Index);
Int32 fn_8021E93C(Object_8021E688 *pObject, Int32 Index);
void fn_8021E950(void *pRes, unsigned int index, void *pBuffer, unsigned int err, void *pUser);
Int32 fn_8021E970(Object_8021E688 *pObject, Int32 Index);
void *fn_8021E984(Object_8021E688 *pObject, Int32 Index);
void fn_8021E998(Object_8021E688 *pObject, Int32 Index, void *pData);
void fn_8021E9AC(Object_8021E688 *pObject, Int32 Index, Entry_8021E688 *pEntry);
void fn_8021EA34(Int32 Index, Object_8021E688 *pObject);
Object_8021E688 *fn_8021EA44(Int32 Index);
Int32 fn_8021EA54(Object_8021E688 *pObject, Int32 Index, Int32 Item);
void fn_8021EB2C(Object_8021E688 *pObject, Int32 Index, Int32 Value);
Int32 fn_8021EB40(Object_8021E688 *pObject, Int32 Index);
void fn_8021EB54(Object_8021E688 *pObject, Uint32 Flags, Int32 a, Int32 b);
void fn_8021EBB4(Object_8021E688 *pObject, Uint32 Flags, Int32 Index, Int32 Item, Int32 Value);
void fn_8021ECB0(Object_8021E688 *pObject, Uint32 Flags, Int32 a);
void fn_8021ECFC(Object_8021E688 *pObject, Uint32 Flags, Int32 a);
void fn_8021ED48(Object_8021E688 *pObject, Uint32 Flags, Int32 a, Int32 b);
void fn_8021ED88(Object_8021E688 *pObject);
Int32 fn_8021EE10(Object_8021E688 *pObject, Int32 Index, Int32 Item);
void fn_8021EE54(void *pRes, unsigned int index, void *pBuffer, unsigned int err, void *pUser);
void fn_8021EE58(Object_8021E688 *pObject, Int32 a, Int32 b, Int32 c, Int32 d);
void fn_8021EF04(Int32 a, Int32 b);
void fn_8021EF34(void);
void fn_8021EF6C(Callback_803EBF44 *pCallback);
void fn_8021EF74(Int32 a);
void fn_8021EFA4(void);

#ifdef __cplusplus
}
#endif

#endif
