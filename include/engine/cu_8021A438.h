#ifndef ENGINE_CU_8021A438_H
#define ENGINE_CU_8021A438_H

#include "types.h"
#include <dolphin/gx/GXStruct.h>
#include "engine/texture.h"
#include "engine/UIGLibraries.h"
#include "engine/UIGTextureNode.h"
#include "engine/UIGFont.h"
#include "engine/uigdisplist.h"
#include "engine/UIGFmv.h"

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
        UIGDispList_t List;
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

#ifdef __cplusplus
extern "C" {
#endif

/* src/engine/cu_8021EFD8.c */
Int32 fn_80220B4C(Int32 a, Int32 b);
void fn_80220BE0(void);
void fn_80220C4C(Int32 a, Int32 b, Int32 c);
void fn_80220CA4(Int32 a, Int32 b, Int32 c);
void fn_80220CDC(Int32 a);
Int32 fn_80220CE4(void);
void fn_80220CFC(Int32 a);
void fn_80220DA4(Float32 *pMul, Float32 *pScale);
void *fn_80220D34(void);
void fn_80221118(void);
long long fn_80221154(Float32 *pV);

#ifdef __cplusplus
}
#endif

#endif
