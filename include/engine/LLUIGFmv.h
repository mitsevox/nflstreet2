#ifndef ENGINE_LLUIGFMV_H
#define ENGINE_LLUIGFMV_H

#include "types.h"
#include "engine/MovieRcmpInfo.h"
#include "engine/UIGLibraries.h"
#include "engine/UIGTextureNode.h"

/* 60-byte member at +0x48 of Object_802268D4. */
typedef struct Sub_802268D4 {
    Int32 unk_00;   /* 0x00 */
    Int32 unk_04;   /* 0x04 */
    void *unk_08;   /* 0x08 */
    Uint8 unk_0C[0x04];
    struct StreamTap_801F5DA4 *pStream; /* 0x10 */
    Uint16 unk_14;  /* 0x14 */
    Int16 unk_16;   /* 0x16 */
    void *unk_18;   /* 0x18 */
    void *unk_1C;   /* 0x1C */
    struct StreamTap_801F5DA4 *pTap; /* 0x20: -1 when none */
    MovieRcmpInfo_t Info; /* 0x24 */
    Int32 unk_30;   /* 0x30 */
    Int32 unk_34;   /* 0x34 */
    struct RcmpFrame_t *pFrame; /* 0x38 */
} Sub_802268D4;

/* 132-byte object allocated by fn_802268D4. */
typedef struct Object_802268D4 {
    Node_802215F0 Node; /* 0x00 */
    Int32 unk_3C;   /* 0x3C */
    Int32 unk_40;   /* 0x40 */
    Int16 unk_44;   /* 0x44 */
    Uint16 Flags;   /* 0x46 */
    Sub_802268D4 Sub; /* 0x48 */
} Object_802268D4;

#ifdef __cplusplus
extern "C" {
#endif

/* src/engine/LLUIGFmv.c */
void fn_80226498(Object_8021E688 *pObject, Object_802268D4 *pMovie);
void fn_802264A4(Sub_802268D4 *pSub);
void fn_802264E8(Sub_802268D4 *pSub, Int32 a);
Int32 fn_80226570(Object_8021E688 *pObject, Object_802268D4 *pMovie, Sub_802268D4 *pSub);
void fn_8022666C(Object_8021E688 *pObject, Object_802268D4 *pMovie);
void fn_802267D0(void);
void fn_802267D4(void);
void fn_802267D8(Object_802268D4 *pMovie, Int32 a, Int32 b);
Object_802268D4 *fn_802268D4(Object_8021E688 *pObject, Int16 a, Int16 b);
void fn_802269C8(Object_8021E688 *pObject, Object_802268D4 *pMovie);
void fn_80226A68(Object_8021E688 *pObject, Object_802268D4 *pMovie);
void fn_80226C40(Object_8021E688 *pObject, Object_802268D4 *pMovie);
void fn_80226D20(Int32 Width, Int32 Height, Uint8 *pData);
void fn_80226E4C(Uint8 *pSrc, Int32 x, Int32 y, Uint8 *pTile, Int32 Width, Int32 Height);
void fn_80226F34(Object_8021E688 *pObject, Int16 a, Int16 b, Object_802268D4 *pMovie);

#ifdef __cplusplus
}
#endif

#endif
