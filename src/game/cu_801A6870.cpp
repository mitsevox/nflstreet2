#include <dolphin/gx/GXEnum.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXVert.h>

extern "C" void fn_801A6870(int count)
{
    int i;

    GXBegin(GX_QUADS, GX_VTXFMT1, count * 4);
    for (i = 0; i < count; i++) {
        GXMatrixIndex1x8(GX_PNMTX1);
        GXPosition1x8(i);
        GXColor1x8(i);
        GXTexCoord1x8(0);
        GXMatrixIndex1x8(GX_PNMTX2);
        GXPosition1x8(i);
        GXColor1x8(i);
        GXTexCoord1x8(1);
        GXMatrixIndex1x8(GX_PNMTX3);
        GXPosition1x8(i);
        GXColor1x8(i);
        GXTexCoord1x8(2);
        GXMatrixIndex1x8(GX_PNMTX4);
        GXPosition1x8(i);
        GXColor1x8(i);
        GXTexCoord1x8(3);
    }
}

extern "C" void fn_801A6924(int count)
{
    int i;

    GXBegin(GX_LINES, GX_VTXFMT1, count * 2);
    for (i = 0; i < count; i++) {
        GXMatrixIndex1x8(GX_PNMTX1);
        GXPosition1x8(i);
        GXColor1x8(i);
        GXTexCoord1x8(0);
        GXMatrixIndex1x8(GX_PNMTX2);
        GXPosition1x8(i);
        GXColor1x8(i);
        GXTexCoord1x8(0);
    }
}
