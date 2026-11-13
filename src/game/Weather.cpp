/* Level weather: keeps a box of falling particles (spinning textured flakes
   or line streaks, by the level's weather mode) that drift with the wind and leave
   splash records when they wrap, and draws that box tiled over the part of
   the field the camera sees. */
#include "engine/animTexLib.h"
#include "game/cu_801444D8.h"
#include "engine/viewport.h"
#include "engine/vptmanager.h"
#include "game/Object_80039F5C.h"
#include "game/fn_801C1F94.h"
#include <dolphin/gx/GXStruct.h>
#include <dolphin/mtx.h>
#include <math.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXTev.h>
#include <dolphin/gx/GXPixel.h>

struct WeatherParticle_t {
  Vector_80039F5C mUnknown0;
  GXColor mUnknownC;
};
struct WeatherBounds_t {
  float mUnknown0[3];
  unsigned char mUnknownC[4];
  float mUnknown10[3];
};
struct WeatherCameraView_t {
  unsigned char mUnknown0[4];
  Vector_80039F5C mUnknown4;
  unsigned char mUnknown10[0x10];
  float mUnknown20;
  unsigned char mUnknown24[4];
  Viewport_t *mUnknown28;
  unsigned char mUnknown2C[0x70];
  int mUnknown9C;
  unsigned char mUnknownA0[0x64];
  Vector_80039F5C mUnknown104;
  unsigned char mUnknown110[0x3C];
  Vector_80039F5C mUnknown14C;
  unsigned char mUnknown158[0xDF4];
  Vector_80039F5C mUnknownF4C;
};
extern "C" {
static float _Weather_afCellBox[2][4] = {{0.0f, 0.0f, 0.0f, 0.0f}, {16.0f, 16.0f, 8.0f, 0.0f}};
static Vector_80039F5C _Weather_vDrift = {0.0f, 0.0f, 0.0f};
static Vector_80039F5C _Weather_avRepeatSteps[4] = {
    {0.0f, 0.0f, 0.0f}, {-1.0f, -1.0f, 1.0f}, {1.0f, -1.0f, 0.0f}, {-1.0f, 1.0f, 1.0f}};
static Vector_80039F5C _Weather_avCornerOffsets[4] = {
    {-0.12f, -0.12f, 0.0f}, {-0.12f, 0.12f, 0.0f}, {0.12f, 0.12f, 0.0f}, {0.12f, -0.12f, 0.0f}};
static Vector_80039F5C _Weather_avLineEnds[2] = {{0.0f, 0.0f, -0.05f}, {0.0f, 0.0f, 0.05f}};
static int _Weather_iSpinAngle = 0;
static int _Weather_iRepeatSpin = 0x400000;
static unsigned int _Weather_uParticleCount = 96;
static float _Weather_fWindScale = 0.285f;
static float _Weather_fLastWind = 0.0f;
static float _Weather_afTexCoords[8];
static Mtx44 _Weather_afViewMatrix;
static WeatherParticle_t _Weather_aParticles[96];
static WeatherParticle_t _Weather_aSplashes[96];
static unsigned int _Weather_uRepeats;
static unsigned int _Weather_uCellsDrawn;
static unsigned int _Weather_uCloseRepeats;
static int _Weather_iMode;
static float _Weather_fFallSpeed;
static unsigned char _Weather_uParticleAlpha;
static unsigned char _Weather_uSplashAlpha;
static unsigned char _Weather_uSplashFade;
static unsigned char _Weather_auFlakeColor[4];
static unsigned char _Weather_auStreakColor[4];
static unsigned char _Weather_auSplashColor[4];
static AnimTex_t *_Weather_pAnimTex;
static int _Weather_iDrawPass;
float fn_80237260(int);
void fn_80239CEC(void *, int);
void fn_80239D1C(void *, int);
void fn_801D0470(int);
void fn_801D0508(void);
void fn_801D0544(void);
void fn_801D04C4(void);
void fn_801D0C58(void *);
void fn_801D0ADC(int);
void fn_80227CC0(void *, void *);
float *fn_801D0444(void);
void fn_8025251C(float *, int);
float *fn_801D0EE4(void);
int fn_801784C4(void);
int fn_800A33E8(void);
void fn_80227538(void *, int, float);
void fn_8022765C(void *, void *, void *);
void fn_801D0664(void *);
void fn_80214184(int);
unsigned int fn_8021445C(void *, void *, int);
void WeatherDrawLines(unsigned int);
void WeatherDrawQuads(unsigned int);
int fn_800A33B8(void);
int fn_800A3444(void);
float fn_800A33C4(void);
float fn_800A33F4(void);
void fn_801D1288(int, void *);
void fn_80214140(int);
void fn_801D131C(int);
void fn_801D0F80(void *);
void fn_8024FC48(int);
void fn_8024FC84(int, int, int, int, int, int, int);

void WeatherInitParticles(WeatherParticle_t *entry, unsigned int count) {
  unsigned char *color = _Weather_auFlakeColor;
  _Weather_pAnimTex = fn_80145118(0);
  if (_Weather_iMode == 2)
    color = _Weather_auStreakColor;
  for (unsigned int i = 0; i < count; ++i, ++entry) {
    entry->mUnknown0.mX = fn_80237260(1) * 15.9999f;
    entry->mUnknown0.mY = fn_80237260(1) * 15.9999f;
    entry->mUnknown0.mZ = fn_80237260(1) * 7.9999f;
    entry->mUnknownC.r = color[0];
    entry->mUnknownC.g = color[1];
    entry->mUnknownC.b = color[2];
    entry->mUnknownC.a = _Weather_uParticleAlpha;
  }
  _Weather_afTexCoords[0] = _Weather_pAnimTex->mGX.mFrames[0].mU0;
  _Weather_afTexCoords[1] = _Weather_pAnimTex->mGX.mFrames[0].mV0;
  _Weather_afTexCoords[2] = _Weather_pAnimTex->mGX.mFrames[0].mU0;
  _Weather_afTexCoords[3] = _Weather_pAnimTex->mGX.mFrames[0].mV1;
  _Weather_afTexCoords[4] = _Weather_pAnimTex->mGX.mFrames[0].mU1;
  _Weather_afTexCoords[5] = _Weather_pAnimTex->mGX.mFrames[0].mV1;
  _Weather_afTexCoords[6] = _Weather_pAnimTex->mGX.mFrames[0].mU1;
  _Weather_afTexCoords[7] = _Weather_pAnimTex->mGX.mFrames[0].mV0;
  fn_80239CEC(_Weather_afTexCoords, 32);
}
void WeatherUpdateParticles(WeatherParticle_t *entries, unsigned int count, float speed,
                 float step) {
  fn_801D0470(VptGetMatrixStack());
  fn_801D0508();
  fn_801D0C58(&_Weather_vDrift);
  fn_801D0ADC(_Weather_iSpinAngle);
  for (unsigned int i = 0; i < count; ++i) {
    WeatherParticle_t *entry = &entries[i];
    entry->mUnknown0.mZ += speed * step;
    if (!(entry->mUnknown0.mZ > 0.0f)) {
      fn_80227CC0(&_Weather_aSplashes[i], &entry->mUnknown0);
      _Weather_aSplashes[i].mUnknownC.r = _Weather_auSplashColor[0];
      _Weather_aSplashes[i].mUnknownC.g = _Weather_auSplashColor[1];
      _Weather_aSplashes[i].mUnknownC.b = _Weather_auSplashColor[2];
      _Weather_aSplashes[i].mUnknownC.a = _Weather_uSplashAlpha;
      _Weather_aSplashes[i].mUnknown0.mZ = 0.0f;
      entry->mUnknown0.mZ += 8.0f;
    } else if (!(entry->mUnknown0.mZ <= 8.0f)) {
      fn_80227CC0(&_Weather_aSplashes[i], &entry->mUnknown0);
      _Weather_aSplashes[i].mUnknownC.r = _Weather_auSplashColor[0];
      _Weather_aSplashes[i].mUnknownC.g = _Weather_auSplashColor[1];
      _Weather_aSplashes[i].mUnknownC.b = _Weather_auSplashColor[2];
      _Weather_aSplashes[i].mUnknown0.mZ = 0.0f;
      _Weather_aSplashes[i].mUnknownC.a = 0;
      entry->mUnknown0.mZ -= 8.0f;
    } else
      entry->mUnknownC.a = _Weather_uParticleAlpha;
    if (_Weather_aSplashes[i].mUnknownC.a) {
      int decay = (int)(_Weather_uSplashFade * step);
      if (_Weather_aSplashes[i].mUnknownC.a > decay)
        _Weather_aSplashes[i].mUnknownC.a -= decay;
      else
        _Weather_aSplashes[i].mUnknownC.a = 0;
    }
  }
  fn_801D0544();
  fn_80239D1C(_Weather_aParticles, _Weather_uParticleCount * 16);
  fn_80239D1C(_Weather_aSplashes, _Weather_uParticleCount * 16);
}
void WeatherSetDrawPass(int mode) {
  if (_Weather_iDrawPass == mode)
    return;
  if (mode == 0) {
    GXSetArray(GX_VA_POS, _Weather_aParticles, 16);
    GXSetArray(GX_VA_CLR0, &_Weather_aParticles[0].mUnknownC, 16);
    GXSetArray(GX_VA_TEX0, _Weather_afTexCoords, 8);
    if (_Weather_iMode == 2) {
      GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
      GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
      GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    } else {
      GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
      GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
      GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    }
    GXSetNumTevStages(1);
  } else if (mode == 1) {
    GXSetArray(GX_VA_POS, _Weather_aSplashes, 16);
    GXSetArray(GX_VA_CLR0, &_Weather_aSplashes[0].mUnknownC, 16);
    GXSetArray(GX_VA_TEX0, _Weather_afTexCoords, 8);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetNumTevStages(1);
  }
  _Weather_iDrawPass = mode;
}
void WeatherLoadCornerMatrices(int mode) {
  Vector_80039F5C *offset;
  float *matrix;
  if (mode == 1 || _Weather_iMode == 1) {
    matrix = fn_801D0444();
    float saved[3];
    saved[0] = matrix[3];
    saved[1] = matrix[7];
    saved[2] = matrix[11];
    offset = _Weather_avCornerOffsets;
    int slot = 3;
    for (int i = 0; i <= 3; ++i) {
      matrix[3] = saved[0] + offset[i].mX;
      matrix[7] = saved[1] + offset[i].mY;
      matrix[11] = saved[2] + offset[i].mZ;
      fn_8025251C(matrix, slot);
      slot += 3;
    }
    matrix[3] = saved[0];
    matrix[7] = saved[1];
    matrix[11] = saved[2];
  } else {
    offset = _Weather_avLineEnds;
    fn_801D04C4();
    fn_801D0C58(&offset[0]);
    fn_8025251C(fn_801D0444(), 3);
    fn_801D0544();
    fn_801D04C4();
    fn_801D0C58(&offset[1]);
    fn_8025251C(fn_801D0444(), 6);
    fn_801D0544();
  }
}
void WeatherGetViewExtent(float *matrix, Vector_80039F5C *out, float depth) {
  out->mX = ((-matrix[2] + matrix[14]) * depth) / matrix[0];
  out->mY = ((-matrix[6] + matrix[14]) * depth) / matrix[5];
  out->mZ = depth;
}
void WeatherGetFrustumBounds(float *matrix, WeatherBounds_t *bounds, float a, float b) {
  fn_801D0470(VptGetMatrixStack());
  fn_801D04C4();
  fn_801D0EE4();
  Vector_80039F5C low, high, point, transformed;
  WeatherGetViewExtent(matrix, &low, a);
  WeatherGetViewExtent(matrix, &high, b);
  bounds->mUnknown0[0] = bounds->mUnknown0[1] = bounds->mUnknown0[2] = 10000.0f;
  bounds->mUnknown10[0] = bounds->mUnknown10[1] = bounds->mUnknown10[2] =
      -10000.0f;
  for (unsigned int i = 0; i <= 7; ++i) {
    Vector_80039F5C *v = (i & 4) ? &high : &low;
    point.mX = v->mX;
    if ((i & 1) == 0)
      point.mX = -point.mX;
    point.mY = v->mY;
    if (!(i & 2))
      point.mY = -point.mY;
    point.mZ = v->mZ;
    fn_80227CC0(&transformed, &point);
    if (!(transformed.mZ >= bounds->mUnknown0[2]))
      bounds->mUnknown0[2] = transformed.mZ;
    if (!(transformed.mZ <= bounds->mUnknown10[2]))
      bounds->mUnknown10[2] = transformed.mZ;
    if (!(transformed.mY >= bounds->mUnknown0[1]))
      bounds->mUnknown0[1] = transformed.mY;
    if (!(transformed.mY <= bounds->mUnknown10[1]))
      bounds->mUnknown10[1] = transformed.mY;
    if (!(transformed.mX >= bounds->mUnknown0[0]))
      bounds->mUnknown0[0] = transformed.mX;
    if (!(transformed.mX <= bounds->mUnknown10[0]))
      bounds->mUnknown10[0] = transformed.mX;
  }
  fn_801D0544();
}
void WeatherGetDrawBounds(WeatherBounds_t *bounds, float *matrix,
                 Vector_80039F5C *position) {
  int special = 0;
  WeatherCameraView_t *view = (WeatherCameraView_t *)VptManagerGetCurrentCamera(0);
  Viewport_t *object = view->mUnknown28;
  position->mX = view->mUnknown4.mX;
  position->mY = view->mUnknown4.mY;
  position->mZ = view->mUnknown4.mZ;
  Vector_80039F5C point;
  switch (view->mUnknown9C) {
  case 14:
    point.mX = view->mUnknown14C.mX;
    point.mY = view->mUnknown14C.mY;
    point.mZ = view->mUnknown14C.mZ;
    if (fn_801784C4()) {
      point.mX = -point.mX;
      point.mY = -point.mY;
    }
    special = 1;
    break;
  case 15:
    point.mX = view->mUnknown104.mX;
    point.mY = view->mUnknown104.mY;
    point.mZ = view->mUnknown104.mZ;
    special = 1;
    break;
  case 17:
    if (!(view->mUnknown20 >= 30.0f)) {
      point.mX = view->mUnknownF4C.mX;
      point.mY = view->mUnknownF4C.mY;
      point.mZ = view->mUnknownF4C.mZ;
      special = 1;
    }
    break;
  }
  float depth = !(view->mUnknown20 <= 55.0f) ? -16.0f : -32.0f;
  unsigned int count;
  if (special) {
    count = _Weather_uCloseRepeats;
    bounds->mUnknown0[0] = point.mX - 16.0f;
    bounds->mUnknown10[0] = point.mX + 16.0f;
    bounds->mUnknown0[1] = point.mY - 16.0f;
    bounds->mUnknown10[1] = point.mY + 16.0f;
    bounds->mUnknown10[2] = bounds->mUnknown0[2] = 0.0f;
  } else {
    WeatherGetFrustumBounds(matrix, bounds, -object->mUnknown232,
                -object->mUnknown232 + depth);
    count = 1;
  }
  _Weather_uRepeats = count;
}
void WeatherUpdateDrift(float a, float b, float step) {
  Vector_80039F5C v;
  fn_80227538(&v, fn_800A33E8(), (a * b) * step);
  v.mZ = 0.0f;
  fn_8022765C(&_Weather_vDrift, &_Weather_vDrift, &v);
  float *position = &_Weather_vDrift.mX;
  for (int i = 0; i < 2; ++i) {
    if (!(position[i] < 8.0f))
      position[i] = -8.0f;
    else if (!(position[i] >= -8.0f))
      position[i] = 8.0f;
  }
  if (_Weather_iMode == 2 && !(fabsf(_Weather_fLastWind - a) <= 0.1f)) {
    _Weather_fLastWind = a;
    _Weather_avLineEnds[0].mX = v.mX * 0.5f;
    _Weather_avLineEnds[0].mY = v.mY * 0.5f;
    _Weather_avLineEnds[1].mX = -v.mX * 0.5f;
    _Weather_avLineEnds[1].mY = -v.mY * 0.5f;
  }
}
void WeatherUpdateSpin(float a, float step) {
  switch (_Weather_iMode) {
  case 1:
    _Weather_iSpinAngle += (int)((a * 20480.0f + 4096.0f) * step);
    break;
  case 2:
    _Weather_iSpinAngle = 0;
    break;
  }
}
void WeatherDrawCell(float x, float y, float z) {
  Vector_80039F5C point;
  point.mX = x;
  point.mY = y;
  point.mZ = z;
  fn_801D04C4();
  fn_801D0C58(&point);
  fn_801D04C4();
  fn_801D0664(_Weather_afViewMatrix);
  fn_80214184(0);
  unsigned int flags = fn_8021445C(_Weather_afCellBox, 0, 0) & 63;
  if (!flags) {
    WeatherSetDrawPass(0);
    if (_Weather_uRepeats > 1) {
      for (unsigned int i = 0; i < _Weather_uRepeats; ++i) {
        WeatherLoadCornerMatrices(0);
        if (_Weather_iMode == 2)
          WeatherDrawLines(_Weather_uParticleCount);
        else
          WeatherDrawQuads(_Weather_uParticleCount);
        if (_Weather_iMode == 1)
          fn_801D0ADC(_Weather_iRepeatSpin);
        else
          fn_801D0C58(&_Weather_avRepeatSteps[i]);
      }
    } else {
      WeatherLoadCornerMatrices(0);
      if (_Weather_iMode == 2)
        WeatherDrawLines(_Weather_uParticleCount);
      else
        WeatherDrawQuads(_Weather_uParticleCount);
    }
    ++_Weather_uCellsDrawn;
  }
  fn_801D0544();
  if (!flags && !(z > 0.0f)) {
    WeatherSetDrawPass(1);
    WeatherLoadCornerMatrices(1);
    WeatherDrawQuads(_Weather_uParticleCount);
  }
  fn_801D0544();
}
void WeatherInit(void) {
  _Weather_iMode = fn_800A33B8();
  _Weather_fLastWind = 0.0f;
  if (_Weather_iMode) {
    switch (_Weather_iMode) {
    case 2:
      if (fn_800A3444() == 2) {
        _Weather_uParticleAlpha = 20;
        _Weather_uSplashAlpha = 20;
        _Weather_fFallSpeed = -0.3f;
        _Weather_uSplashFade = 8;
        _Weather_uParticleCount = 10;
      } else {
        _Weather_uParticleAlpha = 100;
        _Weather_uSplashAlpha = 100;
        _Weather_fFallSpeed = -0.3f;
        _Weather_uSplashFade = 8;
        _Weather_uParticleCount = 96;
      }
      _Weather_auStreakColor[0] = 120;
      _Weather_auStreakColor[1] = 120;
      _Weather_auStreakColor[2] = 120;
      _Weather_auSplashColor[0] = 180;
      _Weather_auSplashColor[1] = 180;
      _Weather_auSplashColor[2] = 180;
      _Weather_uCloseRepeats = 1;
      break;
    case 1:
      _Weather_fFallSpeed = -0.05f;
      _Weather_uParticleAlpha = 120;
      _Weather_uSplashAlpha = 120;
      _Weather_uSplashFade = 2;
      _Weather_auFlakeColor[0] = 255;
      _Weather_auFlakeColor[1] = 255;
      _Weather_auFlakeColor[2] = 255;
      _Weather_auSplashColor[0] = 255;
      _Weather_auSplashColor[1] = 255;
      _Weather_auSplashColor[2] = 255;
      _Weather_uCloseRepeats = 4;
      _Weather_uParticleCount = 96;
      break;
    }
    WeatherInitParticles(_Weather_aParticles, 96);
  }
  fn_801C1F94(_Weather_aSplashes, 0, 0x600);
  _Weather_vDrift.mX = _Weather_vDrift.mY = _Weather_vDrift.mZ = 0.0f;
}
void WeatherShutdown(void) { _Weather_iMode = 0; }
void WeatherUpdate(float step) {
  if (!_Weather_iMode)
    return;
  float value = fn_800A33C4();
  switch (_Weather_iMode) {
  case 2:
    _Weather_uParticleCount = (unsigned int)(value * 96.0f);
    break;
  case 1:
    _Weather_uParticleCount = (unsigned int)(value * 96.0f);
    break;
  }
  float a = fn_800A33F4();
  WeatherUpdateDrift(a, _Weather_fWindScale, step);
  WeatherUpdateSpin(a, step);
  WeatherUpdateParticles(_Weather_aParticles, 96, _Weather_fFallSpeed, step);
}
void WeatherRender(void) {
  if (!_Weather_iMode)
    return;
  _Weather_iDrawPass = -1;
  GXLoadTlut(&_Weather_pAnimTex->mGX.mTlutObj, 0);
  GXLoadTexObj(&_Weather_pAnimTex->mGX.mTexObj, GX_TEXMAP0);
  fn_801D0470(VptGetMatrixStack());
  Mtx44 matrix;
  fn_801D1288(2, matrix);
  fn_80214140(0);
  fn_801D0508();
  fn_801D131C(3);
  fn_801D0C58(&_Weather_vDrift);
  WeatherBounds_t bounds;
  int range[3][2];
  Vector_80039F5C position;
  WeatherGetDrawBounds(&bounds, matrix[0], &position);
  fn_801D0544();
  range[0][0] = (int)((bounds.mUnknown0[0] - 15.0f) * 0.0625f);
  range[1][0] = (int)((bounds.mUnknown0[1] - 15.0f) * 0.0625f);
  range[2][0] = (int)(bounds.mUnknown0[2] * 0.125f);
  range[0][1] = (int)((bounds.mUnknown10[0] + 15.0f) * 0.0625f);
  range[1][1] = (int)((bounds.mUnknown10[1] + 15.0f) * 0.0625f);
  range[2][1] = (int)((bounds.mUnknown10[2] + 7.0f) * 0.125f);
  if (range[2][0] < 0)
    range[2][0] = 0;
  if (range[2][1] < 0)
    range[2][1] = 0;
  _Weather_uCellsDrawn = 0;
  fn_801D0508();
  fn_801D0C58(&_Weather_vDrift);
  fn_801D0ADC(_Weather_iSpinAngle);
  fn_801D0F80(_Weather_afViewMatrix);
  fn_801D0544();
  GXInvalidateVtxCache();
  GXClearVtxDesc();
  GXSetVtxDesc(GX_VA_PNMTXIDX, GX_DIRECT);
  GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
  GXSetVtxDesc(GX_VA_CLR0, GX_INDEX8);
  GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
  GXSetVtxAttrFmt(GX_VTXFMT1, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
  GXSetVtxAttrFmt(GX_VTXFMT1, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
  GXSetVtxAttrFmt(GX_VTXFMT1, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
  fn_8024FC48(1);
  fn_8024FC84(4, 0, 1, 1, 0, 0, 2);
  GXSetNumTexGens(1);
  GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
  for (int z = range[2][0]; z <= range[2][1]; ++z)
    for (int x = range[0][0]; x <= range[0][1]; ++x)
      for (int y = range[1][0]; y <= range[1][1]; ++y)
        if (_Weather_uCellsDrawn <= 21)
          WeatherDrawCell((float)(x * 16), (float)(y * 16), (float)(z * 8));
  GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
  GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
  GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
}
}
