/* GameCube side of the UI graphics texture nodes: builds and frees the GX
   texture of a menu texture node, rounds sizes to powers of two, sets the GX
   channel and TEV state for coloured or textured menu quads, and reads or
   replaces a node's palette. Functions without a body here keep their
   original bytes. */

#include <string.h>

#include <dolphin/gx/GXBump.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXLighting.h>
#include <dolphin/gx/GXTev.h>
#include <dolphin/gx/GXTexture.h>
#include "engine/texture.h"
#include "engine/UIGLibraries.h"
#include "engine/UIGTextureNode.h"
#include "game/fn_801D2B7C.h"

extern void *memset();

extern UIGTexNodeCreateFunc_t *lbl_803EBF60;

Uint32 LLUIGTexNodeRoundToPowerOf2(Uint32 x)
{
    Int32 i = 0;

    while (x & (x - 1)) {
        x = (x + (1 << i) - 1) & -(1 << i);
        i++;
    }
    return x;
}

void LLUIGTexNodeUpdate(Int32 a, Int32 b)
{
}

void LLUIGTexNodeFreeImage(Int32 a, Int32 b, UIGTexNode_t *pNode)
{
    pNode->unk_20 = -1;
    if (pNode->unk_24 != -1) {
        pNode->unk_24 = -1;
    }
    TexDelete(&pNode->Texture);
    memset(pNode, 0, sizeof(UIGTexNode_t));
    fn_801D2BD0(pNode);
}

void LLUIGSetColorChannel(Int32 a)
{
    GXSetNumChans(1);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetChanCtrl(GX_COLOR0A0, GX_TRUE, GX_SRC_VTX, GX_SRC_REG, GX_LIGHT7, GX_DF_NONE, GX_AF_NONE);
}

void LLUIGSetTexturing(Int32 a)
{
    if (a != 0) {
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    } else {
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
        GXSetNumIndStages(0);
        GXSetTevDirect(GX_TEVSTAGE0);
        GXSetNumTexGens(0);
        GXSetVtxDesc(GX_VA_TEX0, GX_NONE);
    }
}

void *LLUIGTexNodeGet(UIGLibrary_t *pObject, Int32 a, Int32 b)
{
    void *p = (void *)UIGLibraryGetItemData(pObject, a, b);

    if (p != NULL) {
        return p;
    }
    return NULL;
}

unsigned short *LLUIGTexNodeGetPalette(UIGTexNode_t *pNode)
{
    return pNode->Texture.mpPalette;
}

void LLUIGTexNodeSetPalette(UIGTexNode_t *pNode, unsigned short *pPalette)
{
    pNode->Texture.mpPalette = pPalette;
}

void LLUIGTexNodeSetCreateCallback(UIGTexNodeCreateFunc_t *pCallback)
{
    lbl_803EBF60 = pCallback;
}
