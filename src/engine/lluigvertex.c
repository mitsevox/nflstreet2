/* UI graphics vertex output: the callbacks the UI shape drawing hands to
   its strip builder, which send each vertex of a UI polygon (position,
   colour and, for textured shapes, texture coordinate) to the GX FIFO. */

#include <dolphin/gx/GXBump.h>
#include <dolphin/gx/GXCull.h>
#include <dolphin/gx/GXDispList.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXLighting.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/gx/GXTev.h>
#include <dolphin/gx/GXTexture.h>
#include <dolphin/gx/GXTransform.h>
#include <dolphin/gx/GXVert.h>
#include <dolphin/os/OSCache.h>
#include "engine/MovieRcmpInfo.h"
#include <string.h>
#include "engine/Font.h"
#include "engine/llmatrix.h"
#include "engine/cu_8021A438.h"
#include "engine/viewport.h"
#include "engine/sound.h"
#include "engine/texture.h"
#include "game/fn_801D2B7C.h"
#include "game/ResOpenDevice.h"

extern Float32 lbl_803A0400[][2];
extern GXColor lbl_803A1400[];

void LLUIGVertexSend(UIGNode_t *pNode, Int32 Index, Float32 *pCoord)
{
    GXPosition3f32(lbl_803A0400[Index][0], lbl_803A0400[Index][1], 0.0f);
    // FAKEMATCH: the flag test reads the node's first word (lwz/rlwinm) where Flags is a halfword
    if ((*(Uint32 *)pNode & 0x60000) != 0x40000) {
        GXColor4u8(lbl_803A1400[Index].r, lbl_803A1400[Index].g, lbl_803A1400[Index].b,
                   lbl_803A1400[Index].a);
    } else {
        GXColor4u8(0xFF, 0xFF, 0xFF, lbl_803A1400[Index].a);
    }
    if (pNode->Flags & 4) {
        GXTexCoord2f32(pCoord[0], pCoord[1]);
    }
}

void LLUIGVertexEnd(UIGNode_t *pNode, Int32 Index, Float32 *pCoord)
{
}
