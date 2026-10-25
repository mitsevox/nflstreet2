#ifndef ENGINE_CU_8021A438_H
#define ENGINE_CU_8021A438_H

#include "types.h"
#include <dolphin/gx/GXStruct.h>
#include "engine/texture.h"

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

/* Two-float point of the curve helpers 0x80222EC4, 0x80222F8C and 0x802233DC
   (8-byte elements, copied as two words). */
typedef struct Point_80222EC4 {
    float mX;
    float mY;
} Point_80222EC4;

/* Buffer descriptor: size and text pointer. */
typedef struct Buffer_80222E54 {
    Uint8 unk_00[0x04];
    Uint32 Size;    /* 0x04 */
    char *pText;    /* 0x08 */
} Buffer_80222E54;

/* Display-list reference: the list address is kept relative to the
   reference itself while stored. */
typedef struct DisplayList_802260D0 {
    Uint32 Size;    /* 0x00 */
    Int32 Offset;   /* 0x04 */
} DisplayList_802260D0;

/* Only the accessed members are declared; the size is not established.
   Bit 15 of Flags selects the display-list form of the +0x10 member. */
typedef struct Node_80223874 {
    Uint16 Flags;   /* 0x00 */
    Uint16 unk_02;  /* 0x02 */
    Int16 unk_04;   /* 0x04 */
    Int16 unk_06;   /* 0x06 */
    Int16 unk_08;   /* 0x08 */
    Int16 unk_0A;   /* 0x0A */
    Int16 unk_0C;   /* 0x0C */
    Int16 unk_0E;   /* 0x0E */
    union {
        DisplayList_802260D0 List;
        struct {
            Uint8 unk_00[0x04];
            GXColor Colors[4];     /* 0x14 */
            Uint16 Coords[4][2];   /* 0x24 */
        } v;
        struct {
            Uint16 unk_10;         /* 0x10 */
            Uint8 unk_12[0x02];
            Uint8 unk_14[4];       /* 0x14 */
            Uint8 unk_18[4];       /* 0x18 */
            Float32 unk_1C[2];     /* 0x1C */
            Float32 unk_24[2];     /* 0x24 */
            Float32 unk_2C[2];     /* 0x2C */
            Float32 unk_34;        /* 0x34 */
            Float32 unk_38;        /* 0x38 */
            Float32 unk_3C[2];     /* 0x3C */
        } t;
    } u;            /* 0x10 */
} Node_80223874;

/* 40-byte element of the array that fn_80220D34 returns a pointer into. */
typedef struct Color_80223C4C {
    Float32 unk_00[8]; /* 0x00 */
    GXColor unk_20; /* 0x20 */
    GXColor unk_24; /* 0x24 */
} Color_80223C4C;

/* 60-byte object allocated by fn_802215F0: a Texture_8020DB34 followed by
   further members; only the accessed members are declared. */
typedef struct Node_802215F0 {
    Texture_8020DB34 Texture; /* 0x00 */
    Int32 unk_20;   /* 0x20 */
    Int32 unk_24;   /* 0x24 */
    Uint8 unk_28[0x08];
    Float32 unk_30; /* 0x30 */
    Float32 unk_34; /* 0x34 */
    Uint8 unk_38[0x04];
} Node_802215F0;

#ifdef __cplusplus
extern "C" {
#endif

/* src/engine/cu_8021A438.c */
void fn_8021E244(Object_8021E688 *pObject, Int32 Index, Int32 Count);
Int32 fn_8021E2B4(Object_8021E688 *pObject, Int32 Index, Int32 Item);
Int32 fn_8021E688(Object_8021E688 *pObject, Int32 Index, Int32 Item);
void fn_8021E6A8(Object_8021E688 *pObject, Int32 Index, Int32 Item, Int32 Value);
void fn_8021E72C(Object_8021E688 *pObject, Int32 Index, Int32 Item);
Uint32 fn_8021E924(Object_8021E688 *pObject, Int32 Index);
Int32 fn_8021E93C(Object_8021E688 *pObject, Int32 Index);
Int32 fn_8021E970(Object_8021E688 *pObject, Int32 Index);
void *fn_8021E984(Object_8021E688 *pObject, Int32 Index);
void fn_8021E998(Object_8021E688 *pObject, Int32 Index, void *pData);
Object_8021E688 *fn_8021EA44(Int32 Index);
Int32 fn_8021EA54(Object_8021E688 *pObject, Int32 Index, Int32 Item);
void fn_8021EB2C(Object_8021E688 *pObject, Int32 Index, Int32 Value);
Int32 fn_8021EB40(Object_8021E688 *pObject, Int32 Index);
Int32 fn_8021EE10(Object_8021E688 *pObject, Int32 Index, Int32 Item);
void fn_8021EE58(Object_8021E688 *pObject, Int32 a, Int32 b, Int32 c, Int32 d);
void fn_8021EF04(Int32 a, Int32 b);
void fn_8021EF34(void);
Int32 fn_80220B4C(Int32 a, Int32 b);
void fn_80220BE0(void);
void fn_80220C4C(Int32 a, Int32 b, Int32 c);
void fn_80220CA4(Int32 a, Int32 b, Int32 c);
void fn_80220CDC(Int32 a);
Int32 fn_80220CE4(void);
void fn_80220CFC(Int32 a);
void *fn_80220D34(void);
void fn_80221118(void);

/* src/engine/cu_80221198.c */
void fn_80221314(Object_8021E688 *pObject, Int16 a, Int16 b);
void fn_80221374(Object_8021E688 *pObject, Int16 a, Int32 b, Int32 c);
void fn_802213F8(Object_8021E688 *pObject, Int16 *pA, Int16 *pB, Int16 c, Int16 d);
void fn_80221528(Object_8021E688 *pObject, Int32 a, Int32 b, Int32 c);
unsigned short *fn_80221570(struct Node_802215F0 *pNode);
void fn_80221590(struct Node_802215F0 *pNode, unsigned short *pPalette);
Int32 fn_8022179C(Int32 a);
void fn_802218D4(Int32 a);
void fn_80221924(Int32 a);
void fn_802219F0(Int32 a, Int32 b);
void fn_80225D90(Object_8021E688 *pObject, Int16 a);
void fn_80225E10(Object_8021E688 *pObject, Int16 a);
void fn_80225E64(Object_8021E688 *pObject, Int16 a, Int16 b, Int32 c);
void fn_80225F10(Object_8021E688 *pObject, Int16 a, Int16 b);
void fn_802260B0(DisplayList_802260D0 *pList);
void fn_802260C0(DisplayList_802260D0 *pList);
void fn_802260D0(DisplayList_802260D0 *pList);
void fn_802260F8(Object_8021E688 *pObject, Int32 a);
void fn_8022615C(Object_8021E688 *pObject, Int32 a);
void fn_8022618C(Object_8021E688 *pObject, Int32 a, Int32 b);
void fn_802261D4(Object_8021E688 *pObject, Int32 a, Int32 b);
void fn_802262C4(Object_8021E688 *pObject, Int32 a, Int32 b);
void fn_80226320(Object_8021E688 *pObject, Int32 a, Int32 b);
void fn_802263DC(Object_8021E688 *pObject, Int32 a, Int32 b);
void fn_80226448(Object_8021E688 *pObject, Int32 a, Int32 b);

#ifdef __cplusplus
}
#endif

#endif
