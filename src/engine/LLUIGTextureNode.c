/* GameCube side of the UI graphics texture nodes: builds and frees the GX
   texture of a menu texture node, rounds sizes to powers of two, sets the GX
   channel and TEV state for coloured or textured menu quads, loads a node's
   texture (with its palette, or with a second texture read through an
   indirect stage) into GX, and reads or replaces a node's palette. */

#include <string.h>

#include <dolphin/os/OSCache.h>
#include <dolphin/gx/GXBump.h>
#include <dolphin/gx/GXGet.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXLighting.h>
#include <dolphin/gx/GXTev.h>
#include <dolphin/gx/GXTexture.h>
#include "engine/texture.h"
#include "engine/UIGLibraries.h"
#include "engine/UIGTextureNode.h"
#include "game/fn_801D2B7C.h"

extern void *memset();

static UIGTexNodeCreateFunc_t *_LLUIGTexNode_pCreateFunc = 0;

GXTexObj LLUIGTexTexObj;
GXTexObj LLUIGTexTlutTexObj;
GXTlutObj LLUIGTexTlutObj;

int TexUpdateFrame(void *pSrc, Texture_t *pTex, Int32 frame);

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

UIGTexNode_t *LLUIGTexNodeSetImage(Int32 a, Int32 b, Int32 c, Int32 d, Int32 e)
{
    UIGTexNode_t *pNode = (UIGTexNode_t *)fn_801D2B7C(sizeof(UIGTexNode_t), 0, 0);
    Uint32 Width;
    Uint32 Height;

    TexCreate((void *)c, &pNode->Texture);
    TexUpdateFrame((void *)c, &pNode->Texture, d);
    if (_LLUIGTexNode_pCreateFunc != NULL) {
        _LLUIGTexNode_pCreateFunc(a, b, pNode, "UIGTexNode");
    }
    DCFlushRange(pNode->Texture.mpImage, pNode->Texture.mWidth * pNode->Texture.mHeight * 2);
    DCFlushRange(pNode->Texture.mpPalette, 1024);
    Width = LLUIGTexNodeRoundToPowerOf2(pNode->Texture.mWidth);
    Height = LLUIGTexNodeRoundToPowerOf2(pNode->Texture.mHeight);
    pNode->unk_30 = (Float32)Width / (Float32)pNode->Texture.mWidth;
    pNode->unk_34 = (Float32)Height / (Float32)pNode->Texture.mHeight;
    return pNode;
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

Int32 LLUIGTexNodeRegisterObj(Texture_t *pTex)
{
    Int32 bIndirect = 0;
    f32 Mtx[2][3];

    if (pTex->mpPalette != NULL) {
        if (pTex->mTlutFormat == GX_TF_RGBA8) {
            GXLoadTexObj(&LLUIGTexTlutTexObj, GX_TEXMAP1);
            GXSetNumIndStages(1);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR_NULL);
            GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD0, GX_TEXMAP0);
            GXSetTexCoordScaleManually(GX_TEXCOORD0, GX_TRUE, GXGetTexObjWidth(&LLUIGTexTexObj),
                                       GXGetTexObjHeight(&LLUIGTexTexObj));
            Mtx[0][0] = 1.0f / 1024.0f;
            Mtx[0][1] = 0.0f;
            /* FAKEMATCH: [1][0] before [0][2], an order found by search (row order swaps two stores). */
            Mtx[1][0] = 0.0f;
            Mtx[0][2] = 0.0f;
            Mtx[1][1] = 1.0f / 1024.0f;
            Mtx[1][2] = 0.0f;
            GXSetIndTexMtx(GX_ITM_0, Mtx, 10);
            GXSetTevIndirect(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_ITF_4, GX_ITB_NONE, GX_ITM_0, GX_ITW_0,
                             GX_ITW_0, GX_FALSE, GX_FALSE, GX_ITBA_OFF);
            bIndirect = 1;
        } else {
            GXLoadTlut(&LLUIGTexTlutObj, GX_TLUT15);
        }
    }
    GXLoadTexObj(&LLUIGTexTexObj, GX_TEXMAP0);
    return bIndirect;
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

void LLUIGSetClamp(Int32 WrapS, Int32 WrapT, Texture_t *pTex)
{
    Uint16 Width = pTex->mWidth;
    Uint16 Height = pTex->mHeight;
    Int32 Entries;

    if (pTex->mpPalette != NULL) {
        if (pTex->mTlutFormat == GX_TF_RGBA8) {
            GXInitTexObj(&LLUIGTexTexObj, pTex->mpImage, Width, Height, GX_TF_IA4, WrapS, WrapT,
                         GX_FALSE);
            GXInitTexObjLOD(&LLUIGTexTexObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE,
                            GX_ANISO_1);
            GXInitTexObj(&LLUIGTexTlutTexObj, pTex->mpPalette, 16, 16, pTex->mTlutFormat, WrapS, WrapT,
                         GX_FALSE);
            GXInitTexObjLOD(&LLUIGTexTlutTexObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE,
                            GX_ANISO_1);
        } else {
            Entries = 16;
            if (pTex->mFormat == GX_TF_C8) {
                Entries = 256;
            }
            GXInitTexObjCI(&LLUIGTexTexObj, pTex->mpImage, Width, Height, pTex->mFormat, WrapS, WrapT,
                           GX_FALSE, GX_TLUT15);
            GXInitTexObjLOD(&LLUIGTexTexObj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE,
                            GX_ANISO_1);
            GXInitTlutObj(&LLUIGTexTlutObj, pTex->mpPalette, pTex->mTlutFormat, Entries);
        }
    } else {
        GXInitTexObj(&LLUIGTexTexObj, pTex->mpImage, Width, Height, pTex->mFormat, WrapS, WrapT, GX_FALSE);
        GXInitTexObjLOD(&LLUIGTexTexObj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE,
                        GX_ANISO_1);
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
    _LLUIGTexNode_pCreateFunc = pCallback;
}
