/* Weather particle drawing: emits the indexed quads or lines of the level's
   weather particles with one matrix per corner. */
#include <dolphin/gx/GXEnum.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXVert.h>

extern "C" void WeatherDrawQuads(int count)
{
    int i;

    GXBegin(GX_QUADS, GX_VTXFMT1, count * 4);
    for (i = 0; i < count; i++) {
        GXMatrixIndex1u8(GX_PNMTX1);
        GXPosition1x8(i);
        GXColor1x8(i);
        GXTexCoord1x8(0);
        GXMatrixIndex1u8(GX_PNMTX2);
        GXPosition1x8(i);
        GXColor1x8(i);
        GXTexCoord1x8(1);
        GXMatrixIndex1u8(GX_PNMTX3);
        GXPosition1x8(i);
        GXColor1x8(i);
        GXTexCoord1x8(2);
        GXMatrixIndex1u8(GX_PNMTX4);
        GXPosition1x8(i);
        GXColor1x8(i);
        GXTexCoord1x8(3);
    }
}

extern "C" void WeatherDrawLines(int count)
{
    int i;

    GXBegin(GX_LINES, GX_VTXFMT1, count * 2);
    for (i = 0; i < count; i++) {
        GXMatrixIndex1u8(GX_PNMTX1);
        GXPosition1x8(i);
        GXColor1x8(i);
        GXTexCoord1x8(0);
        GXMatrixIndex1u8(GX_PNMTX2);
        GXPosition1x8(i);
        GXColor1x8(i);
        GXTexCoord1x8(0);
    }
}
