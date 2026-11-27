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
typedef struct UIGCurvePoint_t {
    float mX;
    float mY;
} UIGCurvePoint_t;

/* Buffer descriptor: size and text pointer. */
typedef struct UIGTextBuffer_t {
    Uint8 unk_00[0x04];
    Uint32 Size;    /* 0x04 */
    char *pText;    /* 0x08 */
} UIGTextBuffer_t;

/* Corner data of an image or colour node: colours, texture coordinates
   (8.8 fixed point) and positions (12.4 fixed point) of its four corners. */
typedef struct UIGNodeQuad_t {
    GXColor Colors[4];      /* 0x00 */
    Uint16 Coords[4][2];    /* 0x10 */
    Int16 Pos[4][3];        /* 0x20 */
} UIGNodeQuad_t;

/* Only the accessed members are declared; the size is not established.
   Bit 15 of Flags selects the display-list form of the +0x10 member. */
typedef struct UIGNode_t {
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
            Uint16 Scale[2];       /* 0x10 */
            UIGNodeQuad_t Quad;    /* 0x14 */
        } v;
        struct {
            Uint16 unk_10;         /* 0x10 */
            Uint16 unk_12;         /* 0x12 */
            Uint8 unk_14[4];       /* 0x14 */
            Uint8 unk_18[4];       /* 0x18 */
            Float32 unk_1C[2];     /* 0x1C */
            Float32 unk_24[2];     /* 0x24 */
            Float32 unk_2C[2];     /* 0x2C */
            Float32 unk_34;        /* 0x34 */
            Float32 unk_38;        /* 0x38 */
            Float32 unk_3C[2];     /* 0x3C */
        } t;
        struct {
            Int16 unk_10;              /* 0x10 */
            Uint8 unk_12[0x02];
            Uint8 unk_14[4];           /* 0x14 */
            UIGCurvePoint_t unk_18[3];  /* 0x18 */
            UIGCurvePoint_t unk_30;     /* 0x30 */
            Float32 unk_38[3];         /* 0x38 */
        } c;
    } u;            /* 0x10 */
} UIGNode_t;

/* 40-byte element of the array that UIGRenderGetColorState returns a pointer into. */
typedef struct UIGMaterialColorState_t {
    Float32 unk_00[8]; /* 0x00 */
    GXColor mMaterialColor; /* 0x20 */
    GXColor mLightColor; /* 0x24 */
} UIGMaterialColorState_t;

#ifdef __cplusplus
extern "C" {
#endif

/* src/engine/UIGColorStyle.c and src/engine/uigrender.c */
Int32 UIGCSGetColorStyle(Int32 a, Int32 b);
void UIGCSResetColorStyleCache(void);
void UIGCSSwapPalette(Int32 a, Int32 b, Int32 c);
void UIGCSRestorePalette(Int32 a, Int32 b, Int32 c);
void UIGRenderSetActive(Int32 a);
Int32 UIGRenderGetActive(void);
void UIGRenderSetLast(Int32 a);
void UIGRenderPushColorState(Float32 *pMul, Float32 *pScale);
void *UIGRenderGetColorState(void);
void UIGRenderPopColorState(void);
long long UIGRenderIsRotated(Float32 *pV);

#ifdef __cplusplus
}
#endif

#endif
