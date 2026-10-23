#ifndef ENGINE_CU_8021A438_H
#define ENGINE_CU_8021A438_H

#include "types.h"

/* 8-byte item of an Entry_8021E688 item array. */
typedef struct Item_8021E688 {
    Int16 unk_00;     /* 0x00 */
    Uint8 unk_02;     /* 0x02 */
    Uint8 unk_03[1];
    Int32 unk_04;     /* 0x04 */
} Item_8021E688;

/* 36-byte entry of the array at Object_8021E688 +0x0C. */
typedef struct Entry_8021E688 {
    Uint8 unk_00[0x08];
    Int32 unk_08;  /* 0x08 */
    Int32 unk_0C;  /* 0x0C */
    Uint32 Flags;  /* 0x10 */
    void *pData;   /* 0x14 */
    Int32 unk_18;  /* 0x18 */
    Uint16 bItems; /* 0x1C: set once pItems is allocated */
    Int16 NumItems;            /* 0x1E */
    Item_8021E688 *pItems;     /* 0x20 */
} Entry_8021E688;

/* Only the accessed members are declared; the size is not established. */
typedef struct Object_8021E688 {
    Uint8 unk_00[0x04];
    Uint16 NumA;               /* 0x04: number of entries at pA */
    Uint8 unk_06[0x06];
    Entry_8021E688 *pA;        /* 0x0C */
} Object_8021E688;

#ifdef __cplusplus
extern "C" {
#endif

/* src/engine/cu_8021A438.c */
Int32 fn_8021E688(Object_8021E688 *pObject, Int32 Index, Int32 Item);
void fn_8021E6A8(Object_8021E688 *pObject, Int32 Index, Int32 Item, Int32 Value);
Uint32 fn_8021E924(Object_8021E688 *pObject, Int32 Index);
Int32 fn_8021E93C(Object_8021E688 *pObject, Int32 Index);
Int32 fn_8021E970(Object_8021E688 *pObject, Int32 Index);
void *fn_8021E984(Object_8021E688 *pObject, Int32 Index);
void fn_8021E998(Object_8021E688 *pObject, Int32 Index, void *pData);
Object_8021E688 *fn_8021EA44(Int32 Index);
void fn_8021EB2C(Object_8021E688 *pObject, Int32 Index, Int32 Value);
Int32 fn_8021EB40(Object_8021E688 *pObject, Int32 Index);
Int32 fn_8021EE10(Object_8021E688 *pObject, Int32 Index, Int32 Item);
void fn_8021EF04(Int32 a, Int32 b);
void fn_8021EF34(void);

/* src/engine/cu_80221198.c */
void fn_80221314(Object_8021E688 *pObject, Int16 a, Int16 b);
void fn_80225D90(Object_8021E688 *pObject, Int16 a);
void fn_80225E10(Object_8021E688 *pObject, Int16 a);
void fn_80225F10(Object_8021E688 *pObject, Int16 a, Int16 b);
void fn_802260F8(Object_8021E688 *pObject, Int32 a);
void fn_8022615C(Object_8021E688 *pObject, Int32 a);
void fn_8022618C(Object_8021E688 *pObject, Int32 a, Int32 b);
void fn_802262C4(Object_8021E688 *pObject, Int32 a, Int32 b);

#ifdef __cplusplus
}
#endif

#endif
