/* Loading screen. While the game loads between the front end and a match it
   shows a full-screen picture from loaddata.dat and, on most screens, a small
   red square that slides back and forth along a strip near the bottom. A
   retrace callback redraws and copies the frame while the loader runs, so
   the screen keeps moving during long disc reads. */
#include <dolphin/vi.h>
#include "game/ResLoad.h"
#include "game/ResOpenDevice.h"
#include "game/GameOptions.h"
#include "engine/rand.h"
#include <dolphin/mtx.h>
#include <dolphin/gx/GXStruct.h>
#include <dolphin/gx/GXVert.h>
#include <string.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXManage.h>
#include <dolphin/gx/GXTev.h>
#include <dolphin/gx/GXCull.h>
#include <dolphin/gx/GXPixel.h>

/* A picture loaded for the screen: the texture copied out of the texture
   library, and the preload region it was loaded into. */
struct LoadingTexture_t {
    unsigned char mUnknown0[0x54];
    GXTexRegion *mpRegion;
};
struct LoadingPoint_t { float mX, mY; };
/* A textured four-corner polygon drawn in screen coordinates. */
struct LoadingPoly_t {
    LoadingTexture_t *mpTexture;
    LoadingPoint_t maCorner[4];
    float maTexCoord[4][2];
};
struct LoadingTexLib_t { unsigned char mUnknown0[0x28]; };
struct LoadingClut_t { unsigned char mUnknown0[4]; GXTlutObj mTlut; };
static LoadingTexture_t _Loading_Image;
static LoadingPoly_t _Loading_BackgroundPoly;
static LoadingPoly_t _Loading_MarkerTrackPoly;
static GXTexRegion _Loading_aImageRegions[2];
static Mtx44 _Loading_MatOldProj;
static GXTexRegion _Loading_TexCacheRegion;
static void *_Loading_pImageFile = 0;
static unsigned char _Loading_iMode = 0;
static unsigned char _Loading_bShowMarker = 0;
static unsigned char _Loading_iFrontEndImage = 0;
static unsigned char _Loading_iNextImage = 0;
static LoadingPoint_t _Loading_MarkerPos;
static float _Loading_fMarkerStep;
typedef GXTexRegion *(*LoadingTexRegionFunc_t)(GXTexObj *, GXTexMapID);
static LoadingTexRegionFunc_t _Loading_pOldTexRegionFunc;
extern "C" const char lbl_802EBE14[];
extern "C" const signed char _Loading_aImageGroup[40];

extern "C" {
int fn_800A3444(void);
void TMTexLibLoad(LoadingTexLib_t *, int);
void TMTexLibUnload(LoadingTexLib_t *);
LoadingTexture_t *TMTexLibGetTexture(LoadingTexLib_t *, int);
LoadingClut_t *TMTexLibGetClut(LoadingTexLib_t *, int, int);
extern "C" void GXPreLoadEntireTexture(LoadingTexture_t *, GXTexRegion *);
extern "C" void GXLoadTlut(GXTlutObj *, int);
extern "C" void GXInitTexObjTlut(LoadingTexture_t *, int);
extern "C" void GXLoadTexObjPreLoaded(LoadingTexture_t *, GXTexRegion *, int);
void fn_8024FB58(int, GXColor);
void fn_8024FC48(int);
void fn_8024FC84(int,int,int,int,int,int,int);
void GXSetClipMode(int);
void GXGetProjectionv(float *);
void GXSetProjection(Mtx44,int);
void fn_801D03D0(Mtx44);
void GXLoadPosMtxImm(Mtx44,int);
void GXSetCurrentMtx(int);
void fn_801CE720(void);
void fn_801CE774(void);
extern "C" void GXInitTexPreLoadRegion(GXTexRegion *,int,int,int,int);
extern "C" void GXInvalidateTexAll(void);
void fn_801CEA7C(int);
int fn_801CEA08(void);
int fn_801CEA14(void);
void fn_801CEC48(int,int,int,int);
void fn_801CE22C(void (*)(void));
void fn_801CE23C(void);
extern "C" void GXInitTexCacheRegion(GXTexRegion *,int,unsigned int,int,unsigned int,int);
extern "C" LoadingTexRegionFunc_t GXSetTexRegionCallback(LoadingTexRegionFunc_t);
int fn_801CE930(void);
int fn_801CE944(int);
void GXCopyDisp(int,int);

void LoadingBeginDraw(int alpha);
void LoadingDrawScreen(void);

/* Picks the next background for the in-game loading screens: walks the
   pictures 4 to 43 from where the last call stopped and takes the first one
   whose group matches the current game value, or that fits any (-1). */
int LoadingPickImage(void)
{
    unsigned int index = _Loading_iNextImage;
    int value = fn_800A3444();
    while (_Loading_aImageGroup[index - 4] != value && _Loading_aImageGroup[index - 4] != -1) {
        if (++index > 43) index = 4;
    }
    _Loading_iNextImage = index + 1;
    if (_Loading_iNextImage > 43) _Loading_iNextImage = 4;
    return index;
}
GXTexRegion *LoadingTexRegionFunc(GXTexObj *, GXTexMapID)
{
    return &_Loading_TexCacheRegion;
}
/* Retrace callback: slides the marker, bouncing it off the ends of its
   track, then redraws the screen and copies it out. */
void LoadingVSyncCallback(void)
{
    if (_Loading_bShowMarker) {
        _Loading_MarkerPos.mX += _Loading_fMarkerStep;
        if (_Loading_MarkerPos.mX < _Loading_MarkerTrackPoly.maCorner[0].mX || _Loading_MarkerPos.mX + 32.0f > _Loading_MarkerTrackPoly.maCorner[1].mX) {
            _Loading_fMarkerStep = -_Loading_fMarkerStep;
            _Loading_MarkerPos.mX += 2.0f * _Loading_fMarkerStep;
        }
        LoadingBeginDraw(128);
        LoadingDrawScreen();
        GXCopyDisp(fn_801CE944((unsigned char)fn_801CE930()), 1);
        GXPixModeSync();
        GXFlush();
    }
}
/* Loads picture `index` of loaddata.dat into texture memory region
   `region` and copies its texture object out. */
void LoadingLoadImage(int index, LoadingTexture_t *out, int region)
{
    LoadingTexLib_t lib;
    TMTexLibLoad(&lib, ResLoad(_Loading_pImageFile, index, 1));
    LoadingTexture_t *texture = TMTexLibGetTexture(&lib, 0xFF000000);
    LoadingClut_t *clut = TMTexLibGetClut(&lib, 0xFF000000, 0);
    out->mpRegion = &_Loading_aImageRegions[region];
    GXPreLoadEntireTexture(texture, out->mpRegion);
    GXDrawDone();
    if (clut) {
        GXLoadTlut(&clut->mTlut, region + 4);
        GXInitTexObjTlut(texture, region + 4);
    }
    memcpy(out, texture, 0x2C);
    TMTexLibUnload(&lib);
    ResUnLoad(_Loading_pImageFile, index);
}
void LoadingFreeImage(LoadingTexture_t *) {}
void LoadingSetPolyTexCoords(LoadingPoly_t *poly, float u, float v)
{
    poly->maTexCoord[0][0] = 0.0f;
    poly->maTexCoord[0][1] = 0.0f;
    poly->maTexCoord[1][0] = u;
    poly->maTexCoord[1][1] = 0.0f;
    poly->maTexCoord[2][0] = 0.0f;
    poly->maTexCoord[2][1] = v;
    poly->maTexCoord[3][0] = u;
    poly->maTexCoord[3][1] = v;
}
void LoadingSetPolyTexture(LoadingPoly_t *poly, LoadingTexture_t *texture) { poly->mpTexture = texture; }
void LoadingSetPolyVertices(LoadingPoly_t *poly, int, unsigned int left, unsigned int top, unsigned int right, unsigned int bottom)
{
    poly->maCorner[2].mX = poly->maCorner[0].mX = (float)left;
    poly->maCorner[1].mY = poly->maCorner[0].mY = (float)top;
    poly->maCorner[3].mX = poly->maCorner[1].mX = (float)right;
    poly->maCorner[3].mY = poly->maCorner[2].mY = (float)bottom;
}
void LoadingDrawPoly(LoadingPoly_t *poly)
{
    if (poly->mpTexture) {
        GXLoadTexObjPreLoaded(poly->mpTexture, poly->mpTexture->mpRegion, 0);
        GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    } else {
        GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    }
    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 4);
    for (int i = 0; i < 4; ++i) {
        GXPosition3f32(poly->maCorner[i].mX, poly->maCorner[i].mY, -1.5f);
        GXTexCoord2f32(poly->maTexCoord[i][0], poly->maTexCoord[i][1]);
    }
}
/* Draws the 32-pixel marker in plain red, then restores white. */
void LoadingDrawMarker(void)
{
    GXColor color;
    color.r = 255;
    color.g = 0;
    color.b = 0;
    color.a = 255;
    fn_8024FB58(4, color);
    GXLoadTexObjPreLoaded(_Loading_BackgroundPoly.mpTexture, _Loading_BackgroundPoly.mpTexture->mpRegion, 0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 4);
    GXPosition3f32(_Loading_MarkerPos.mX, _Loading_MarkerPos.mY, -1.5f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(_Loading_MarkerPos.mX + 32.0f, _Loading_MarkerPos.mY, -1.5f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(_Loading_MarkerPos.mX, _Loading_MarkerPos.mY + 32.0f, -1.5f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXPosition3f32(_Loading_MarkerPos.mX + 32.0f, _Loading_MarkerPos.mY + 32.0f, -1.5f);
    GXTexCoord2f32(1.0f, 1.0f);
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;
    fn_8024FB58(4, color);
}
/* Sets up GX for flat 2D drawing over a 640x480 orthographic projection,
   saving the game's projection first. `alpha` 128 is fully opaque. */
void LoadingBeginDraw(int alpha)
{
    Mtx44 view;
    Mtx44 projection;
    GXColor color = {255,255,255,(unsigned char)(alpha * 2 - 1)};
    fn_8024FC48(1);
    fn_8024FB58(4, color);
    fn_8024FC84(4,0,0,0,1,0,2);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetCullMode(GX_CULL_NONE);
    GXSetClipMode(1);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXGetProjectionv(_Loading_MatOldProj[0]);
    C_MTXOrtho(projection,0.0f, 480.0f, 0.0f, 640.0f, 1.0f, 2.0f);
    GXSetProjection(projection,1);
    fn_801D03D0(view);
    GXLoadPosMtxImm(view,0);
    GXSetCurrentMtx(0);
}
void LoadingEndDraw(void)
{
    GXSetBlendMode(GX_BM_NONE, GX_BL_ZERO, GX_BL_ZERO, GX_LO_NOOP);
    GXSetProjection(_Loading_MatOldProj,0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetClipMode(0);
}
void LoadingDrawScreen(void)
{
    if (_Loading_bShowMarker) LoadingDrawMarker();
    LoadingDrawPoly(&_Loading_BackgroundPoly);
}
void LoadingRenderFrame(int, int alpha)
{
    fn_801CE720();
    LoadingBeginDraw(alpha);
    LoadingDrawScreen();
    LoadingEndDraw();
    fn_801CE774();
}
void LoadingInit(void)
{
    LoadingSetPolyTexCoords(&_Loading_BackgroundPoly,1.0f,1.0f);
    LoadingSetPolyTexCoords(&_Loading_MarkerTrackPoly,1.0f,1.0f);
    GXInitTexPreLoadRegion(&_Loading_aImageRegions[0],0,0x60000,0,0);
    GXInitTexPreLoadRegion(&_Loading_aImageRegions[1],0x60000,0x20000,0,0);
    void *p = MathNewRandomStream(0,MathGetRandomSeed());
    _Loading_iFrontEndImage = MathGetRandomRange(p,2);
    _Loading_iNextImage = MathGetRandomRange(p,40) + 4;
    MathDelRandomStream(p);
}
/* Starts a loading screen. Mode 1 shows picture 0, mode 4 alternates the
   front-end pictures 1 and 2, modes 2 and 3 pick an in-game picture with
   LoadingPickImage, and mode 5 keeps the picture already loaded and shows
   no marker. */
void LoadingBegin(int mode)
{
    _Loading_pImageFile = ResOpenDevice(lbl_802EBE14,44);
    GXInvalidateTexAll();
    GXTexModeSync();
    fn_801CEA7C(0);
    _Loading_bShowMarker = 0;
    switch (mode) {
    case 1:
        LoadingLoadImage(0,&_Loading_Image,0);
        LoadingSetPolyTexture(&_Loading_BackgroundPoly,&_Loading_Image);
        LoadingSetPolyVertices(&_Loading_BackgroundPoly,0,0,0,640,480);
        LoadingSetPolyVertices(&_Loading_MarkerTrackPoly,0,17,432,273,464);
        break;
    case 4: {
        int index = _Loading_iFrontEndImage + 1;
        _Loading_iFrontEndImage++;
        if (_Loading_iFrontEndImage == 2) _Loading_iFrontEndImage = 0;
        if (GameOptionsGet(6) == 1) {
            int a = fn_801CEA08();
            int b = fn_801CEA14();
            fn_801CEC48(0,a,0,b);
        }
        LoadingLoadImage(index,&_Loading_Image,0);
        LoadingSetPolyTexture(&_Loading_BackgroundPoly,&_Loading_Image);
        LoadingSetPolyVertices(&_Loading_BackgroundPoly,0,0,0,640,480);
        LoadingSetPolyVertices(&_Loading_MarkerTrackPoly,0,17,432,273,464);
        break;
    }
    case 2: case 3: {
        int a = fn_801CEA08();
        int b = fn_801CEA14();
        fn_801CEC48(0,a,0,b);
        LoadingLoadImage(LoadingPickImage(),&_Loading_Image,0);
        LoadingSetPolyTexture(&_Loading_BackgroundPoly,&_Loading_Image);
        LoadingSetPolyVertices(&_Loading_BackgroundPoly,0,0,0,640,480);
        LoadingSetPolyVertices(&_Loading_MarkerTrackPoly,0,17,432,273,464);
        break;
    }
    case 5:
        LoadingSetPolyTexture(&_Loading_BackgroundPoly,&_Loading_Image);
        LoadingSetPolyVertices(&_Loading_BackgroundPoly,0,0,0,640,480);
        break;
    }
    ResClose(_Loading_pImageFile);
    _Loading_pImageFile = 0;
    if (mode != 5) {
        _Loading_fMarkerStep = 6.0f;
        _Loading_MarkerPos = _Loading_MarkerTrackPoly.maCorner[0];
        _Loading_bShowMarker = 1;
    } else {
        _Loading_bShowMarker = 0;
    }
    LoadingRenderFrame(mode,128);
    LoadingBeginDraw(128);
    fn_801CE22C(LoadingVSyncCallback);
    GXInitTexCacheRegion(&_Loading_TexCacheRegion,0,0x80000,1,0x80000,1);
    _Loading_pOldTexRegionFunc = GXSetTexRegionCallback(LoadingTexRegionFunc);
    _Loading_iMode = mode;
}
/* Ends the loading screen: draws and copies one last frame, removes the
   retrace callback and restores the texture region callback. */
void LoadingEnd(int clear)
{
    VIWaitForRetrace();
    fn_801CE23C();
    LoadingBeginDraw(128);
    LoadingDrawScreen();
    GXCopyDisp(fn_801CE944((unsigned char)fn_801CE930()),clear);
    GXPixModeSync();
    GXFlush();
    LoadingEndDraw();
    fn_801CEA7C(1);
    LoadingFreeImage(&_Loading_Image);
    GXSetTexRegionCallback(_Loading_pOldTexRegionFunc);
    _Loading_iMode = 0;
}
const signed char _Loading_aImageGroup[40] = {
-1,2,-1,-1,0,-1,-1,11,-1,-1,-1,-1,4,-1,-1,-1,
-1,9,-1,-1,-1,-1,1,-1,2,-1,-1,-1,-1,-1,4,-1,
9,9,-1,6,-1,-1,-1,8
};
}
