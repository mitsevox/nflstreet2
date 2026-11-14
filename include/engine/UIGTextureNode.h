#ifndef ENGINE_UIGTEXTURENODE_H
#define ENGINE_UIGTEXTURENODE_H

#include "types.h"
#include "engine/texture.h"
#include "engine/UIGLibraries.h"

/* 60-byte object allocated by LLUIGTexNodeSetImage: a Texture_t followed by
   further members; only the accessed members are declared. */
typedef struct UIGTexNode_t {
    Texture_t Texture; /* 0x00 */
    Int32 unk_20;   /* 0x20 */
    Int32 unk_24;   /* 0x24 */
    Uint8 unk_28[0x08];
    Float32 unk_30; /* 0x30 */
    Float32 unk_34; /* 0x34 */
    Uint8 unk_38[0x04];
} UIGTexNode_t;

typedef void UIGTexNodeCreateFunc_t(Int32 a, Uint32 b, void *p);

#ifdef __cplusplus
extern "C" {
#endif

/* src/engine/UIGTextureNode.c */
void UIGTexNodeUnLoad(UIGLibrary_t *pObject, Int16 a, Int16 b);
void UIGTexNodeLoad(UIGLibrary_t *pObject, Int16 a, Int32 b, Int32 c);
void UIGTexNodeSwap(UIGLibrary_t *pObject, Int16 *pA, Int16 *pB, Int16 c, Int16 d);
void UIGTexNodeUpdate(UIGLibrary_t *pObject, Int32 a, Int32 b, Int32 c);
unsigned short *UIGTexNodeGetPalette(UIGTexNode_t *pNode);
void UIGTexNodeSetPalette(UIGTexNode_t *pNode, unsigned short *pPalette);

/* src/engine/LLUIGTextureNode.c */
Uint32 LLUIGTexNodeRoundToPowerOf2(Uint32 x);
void LLUIGTexNodeUpdate(Int32 a, Int32 b);
UIGTexNode_t *LLUIGTexNodeSetImage(Int32 a, Int32 b, Int32 c, Int32 d, Int32 e);
void LLUIGTexNodeFreeImage(Int32 a, Int32 b, UIGTexNode_t *pNode);
Int32 LLUIGTexNodeRegisterObj(Int32 a);
void LLUIGSetColorChannel(Int32 a);
void LLUIGSetTexturing(Int32 a);
void LLUIGSetClamp(Int32 a, Int32 b);
void *LLUIGTexNodeGet(UIGLibrary_t *pObject, Int32 a, Int32 b);
unsigned short *LLUIGTexNodeGetPalette(UIGTexNode_t *pNode);
void LLUIGTexNodeSetPalette(UIGTexNode_t *pNode, unsigned short *pPalette);
void LLUIGTexNodeSetCreateCallback(UIGTexNodeCreateFunc_t *pCallback);

#ifdef __cplusplus
}
#endif

#endif
