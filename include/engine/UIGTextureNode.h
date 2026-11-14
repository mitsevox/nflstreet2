#ifndef ENGINE_UIGTEXTURENODE_H
#define ENGINE_UIGTEXTURENODE_H

#include "types.h"
#include "engine/texture.h"
#include "engine/UIGLibraries.h"

/* 60-byte object allocated by fn_802215F0: a Texture_t followed by
   further members; only the accessed members are declared. */
typedef struct Node_802215F0 {
    Texture_t Texture; /* 0x00 */
    Int32 unk_20;   /* 0x20 */
    Int32 unk_24;   /* 0x24 */
    Uint8 unk_28[0x08];
    Float32 unk_30; /* 0x30 */
    Float32 unk_34; /* 0x34 */
    Uint8 unk_38[0x04];
} Node_802215F0;

typedef void Callback_803EBF60(Int32 a, Uint32 b, void *p);

#ifdef __cplusplus
extern "C" {
#endif

/* src/engine/UIGTextureNode.c */
void fn_80221314(Object_8021E688 *pObject, Int16 a, Int16 b);
void fn_80221374(Object_8021E688 *pObject, Int16 a, Int32 b, Int32 c);
void fn_802213F8(Object_8021E688 *pObject, Int16 *pA, Int16 *pB, Int16 c, Int16 d);
void fn_80221528(Object_8021E688 *pObject, Int32 a, Int32 b, Int32 c);
unsigned short *fn_80221570(Node_802215F0 *pNode);
void fn_80221590(Node_802215F0 *pNode, unsigned short *pPalette);

/* src/engine/LLUIGTextureNode.c */
Uint32 fn_802215B0(Uint32 x);
void fn_802215EC(Int32 a, Int32 b);
Node_802215F0 *fn_802215F0(Int32 a, Int32 b, Int32 c, Int32 d, Int32 e);
void fn_80221738(Int32 a, Int32 b, Node_802215F0 *pNode);
Int32 fn_8022179C(Int32 a);
void fn_802218D4(Int32 a);
void fn_80221924(Int32 a);
void fn_802219F0(Int32 a, Int32 b);
void *fn_80221BAC(Object_8021E688 *pObject, Int32 a, Int32 b);
unsigned short *fn_80221BD8(Node_802215F0 *pNode);
void fn_80221BE0(Node_802215F0 *pNode, unsigned short *pPalette);
void fn_80221BE8(Callback_803EBF60 *pCallback);

#ifdef __cplusplus
}
#endif

#endif
