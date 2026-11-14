#ifndef ENGINE_LLUIGFMV_H
#define ENGINE_LLUIGFMV_H

#include "types.h"
#include "engine/MovieRcmpInfo.h"
#include "engine/UIGLibraries.h"
#include "engine/UIGTextureNode.h"

/* 60-byte member at +0x48 of LLUIGFmvMovie_t. */
typedef struct LLUIGFmvStream_t {
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
} LLUIGFmvStream_t;

/* 132-byte object allocated by LLUIGFmvAddInstance. */
typedef struct LLUIGFmvMovie_t {
    UIGTexNode_t Node; /* 0x00 */
    Int32 unk_3C;   /* 0x3C */
    Int32 unk_40;   /* 0x40 */
    Int16 unk_44;   /* 0x44 */
    Uint16 Flags;   /* 0x46 */
    LLUIGFmvStream_t Sub; /* 0x48 */
} LLUIGFmvMovie_t;

#ifdef __cplusplus
extern "C" {
#endif

/* src/engine/LLUIGFmv.c */
void LLUIGFmvProcess(UIGLibrary_t *pObject, LLUIGFmvMovie_t *pMovie);
void LLUIGDumpImage(LLUIGFmvStream_t *pSub);
void LLUIGFmvDecompressFrame(LLUIGFmvStream_t *pSub, Int32 a);
Int32 LLUIGFmvNextFrame(UIGLibrary_t *pObject, LLUIGFmvMovie_t *pMovie, LLUIGFmvStream_t *pSub);
void LLUIGFmvUpdate(UIGLibrary_t *pObject, LLUIGFmvMovie_t *pMovie);
void LLUIGFmvInit(void);
void LLUIGFmvShutdown(void);
void LLUIGFmvInitTexture(LLUIGFmvMovie_t *pMovie, Int32 a, Int32 b);
LLUIGFmvMovie_t *LLUIGFmvAddInstance(UIGLibrary_t *pObject, Int16 a, Int16 b);
void LLUIGFmvDeleteInstance(UIGLibrary_t *pObject, LLUIGFmvMovie_t *pMovie);
void LLUIGFmvStartInstance(UIGLibrary_t *pObject, LLUIGFmvMovie_t *pMovie);
void LLUIGFmvStopInstance(UIGLibrary_t *pObject, LLUIGFmvMovie_t *pMovie);
void LLUIGFMVSizzle32to32(Int32 Width, Int32 Height, Uint8 *pData);
void _PackTile_RGBA8(Uint8 *pSrc, Int32 x, Int32 y, Uint8 *pTile, Int32 Width, Int32 Height);
void LLUIGFmvSwapInstance(UIGLibrary_t *pObject, Int16 a, Int16 b, LLUIGFmvMovie_t *pMovie);

#ifdef __cplusplus
}
#endif

#endif
