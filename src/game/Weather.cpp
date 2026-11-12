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
extern float lbl_80366780[8];
extern Mtx44 lbl_803667A0;
extern WeatherParticle_t lbl_803667E0[96], lbl_80366DE0[96];
extern unsigned int lbl_803ECC28, lbl_803ECC2C, lbl_803ECC30;
extern int lbl_803ECC34;
extern float lbl_803ECC38;
extern unsigned char lbl_803ECC3C, lbl_803ECC3D, lbl_803ECC3E;
extern GXColor lbl_803ECC40, lbl_803ECC44, lbl_803ECC48;
extern AnimTex_t *lbl_803ECC4C;
extern int lbl_803ECC50;
extern int lbl_803EB850, lbl_803EB854;
extern unsigned int lbl_803EB858;
extern float lbl_803EB85C, lbl_803EB860;
extern Vector_80039F5C lbl_802F3A9C, lbl_802F3AA8[], lbl_802F3AD8[],
    lbl_802F3B08[];
extern WeatherBounds_t lbl_802F3A7C;
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
  GXColor *color = &lbl_803ECC40;
  lbl_803ECC4C = fn_80145118(0);
  if (lbl_803ECC34 == 2)
    color = &lbl_803ECC44;
  for (unsigned int i = 0; i < count; ++i, ++entry) {
    entry->mUnknown0.mX = fn_80237260(1) * 15.9999f;
    entry->mUnknown0.mY = fn_80237260(1) * 15.9999f;
    entry->mUnknown0.mZ = fn_80237260(1) * 7.9999f;
    entry->mUnknownC.r = color->r;
    entry->mUnknownC.g = color->g;
    entry->mUnknownC.b = color->b;
    entry->mUnknownC.a = lbl_803ECC3C;
  }
  lbl_80366780[0] = lbl_803ECC4C->mGX.mFrames[0].mU0;
  lbl_80366780[1] = lbl_803ECC4C->mGX.mFrames[0].mV0;
  lbl_80366780[2] = lbl_803ECC4C->mGX.mFrames[0].mU0;
  lbl_80366780[3] = lbl_803ECC4C->mGX.mFrames[0].mV1;
  lbl_80366780[4] = lbl_803ECC4C->mGX.mFrames[0].mU1;
  lbl_80366780[5] = lbl_803ECC4C->mGX.mFrames[0].mV1;
  lbl_80366780[6] = lbl_803ECC4C->mGX.mFrames[0].mU1;
  lbl_80366780[7] = lbl_803ECC4C->mGX.mFrames[0].mV0;
  fn_80239CEC(lbl_80366780, 32);
}
void WeatherUpdateParticles(WeatherParticle_t *entries, unsigned int count, float speed,
                 float step) {
  fn_801D0470(VptGetMatrixStack());
  fn_801D0508();
  fn_801D0C58(&lbl_802F3A9C);
  fn_801D0ADC(lbl_803EB850);
  for (unsigned int i = 0; i < count; ++i) {
    WeatherParticle_t *entry = &entries[i];
    entry->mUnknown0.mZ += speed * step;
    if (!(entry->mUnknown0.mZ > 0.0f)) {
      fn_80227CC0(&lbl_80366DE0[i], &entry->mUnknown0);
      lbl_80366DE0[i].mUnknownC.r = lbl_803ECC48.r;
      lbl_80366DE0[i].mUnknownC.g = lbl_803ECC48.g;
      lbl_80366DE0[i].mUnknownC.b = lbl_803ECC48.b;
      lbl_80366DE0[i].mUnknownC.a = lbl_803ECC3D;
      lbl_80366DE0[i].mUnknown0.mZ = 0.0f;
      entry->mUnknown0.mZ += 8.0f;
    } else if (!(entry->mUnknown0.mZ <= 8.0f)) {
      fn_80227CC0(&lbl_80366DE0[i], &entry->mUnknown0);
      lbl_80366DE0[i].mUnknownC.r = lbl_803ECC48.r;
      lbl_80366DE0[i].mUnknownC.g = lbl_803ECC48.g;
      lbl_80366DE0[i].mUnknownC.b = lbl_803ECC48.b;
      lbl_80366DE0[i].mUnknown0.mZ = 0.0f;
      lbl_80366DE0[i].mUnknownC.a = 0;
      entry->mUnknown0.mZ -= 8.0f;
    } else
      entry->mUnknownC.a = lbl_803ECC3C;
    if (lbl_80366DE0[i].mUnknownC.a) {
      int decay = (int)(lbl_803ECC3E * step);
      if (lbl_80366DE0[i].mUnknownC.a > decay)
        lbl_80366DE0[i].mUnknownC.a -= decay;
      else
        lbl_80366DE0[i].mUnknownC.a = 0;
    }
  }
  fn_801D0544();
  fn_80239D1C(lbl_803667E0, lbl_803EB858 * 16);
  fn_80239D1C(lbl_80366DE0, lbl_803EB858 * 16);
}
void WeatherSetDrawPass(int mode) {
  if (lbl_803ECC50 == mode)
    return;
  if (mode == 0) {
    GXSetArray(GX_VA_POS, lbl_803667E0, 16);
    GXSetArray(GX_VA_CLR0, &lbl_803667E0[0].mUnknownC, 16);
    GXSetArray(GX_VA_TEX0, lbl_80366780, 8);
    if (lbl_803ECC34 == 2) {
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
    GXSetArray(GX_VA_POS, lbl_80366DE0, 16);
    GXSetArray(GX_VA_CLR0, &lbl_80366DE0[0].mUnknownC, 16);
    GXSetArray(GX_VA_TEX0, lbl_80366780, 8);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetNumTevStages(1);
  }
  lbl_803ECC50 = mode;
}
void WeatherLoadCornerMatrices(int mode) {
  Vector_80039F5C *offset;
  float *matrix;
  if (mode == 1 || lbl_803ECC34 == 1) {
    matrix = fn_801D0444();
    float saved[3];
    saved[0] = matrix[3];
    saved[1] = matrix[7];
    saved[2] = matrix[11];
    offset = lbl_802F3AD8;
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
    offset = lbl_802F3B08;
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
    count = lbl_803ECC30;
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
  lbl_803ECC28 = count;
}
void WeatherUpdateDrift(float a, float b, float step) {
  Vector_80039F5C v;
  fn_80227538(&v, fn_800A33E8(), (a * b) * step);
  v.mZ = 0.0f;
  fn_8022765C(&lbl_802F3A9C, &lbl_802F3A9C, &v);
  float *position = &lbl_802F3A9C.mX;
  for (int i = 0; i < 2; ++i) {
    if (!(position[i] < 8.0f))
      position[i] = -8.0f;
    else if (!(position[i] >= -8.0f))
      position[i] = 8.0f;
  }
  if (lbl_803ECC34 == 2 && !(fabsf(lbl_803EB860 - a) <= 0.1f)) {
    lbl_803EB860 = a;
    lbl_802F3B08[0].mX = v.mX * 0.5f;
    lbl_802F3B08[0].mY = v.mY * 0.5f;
    lbl_802F3B08[1].mX = -v.mX * 0.5f;
    lbl_802F3B08[1].mY = -v.mY * 0.5f;
  }
}
void WeatherUpdateSpin(float a, float step) {
  switch (lbl_803ECC34) {
  case 1:
    lbl_803EB850 += (int)((a * 20480.0f + 4096.0f) * step);
    break;
  case 2:
    lbl_803EB850 = 0;
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
  fn_801D0664(lbl_803667A0);
  fn_80214184(0);
  unsigned int flags = fn_8021445C(&lbl_802F3A7C, 0, 0) & 63;
  if (!flags) {
    WeatherSetDrawPass(0);
    if (lbl_803ECC28 > 1) {
      for (unsigned int i = 0; i < lbl_803ECC28; ++i) {
        WeatherLoadCornerMatrices(0);
        if (lbl_803ECC34 == 2)
          WeatherDrawLines(lbl_803EB858);
        else
          WeatherDrawQuads(lbl_803EB858);
        if (lbl_803ECC34 == 1)
          fn_801D0ADC(lbl_803EB854);
        else
          fn_801D0C58(&lbl_802F3AA8[i]);
      }
    } else {
      WeatherLoadCornerMatrices(0);
      if (lbl_803ECC34 == 2)
        WeatherDrawLines(lbl_803EB858);
      else
        WeatherDrawQuads(lbl_803EB858);
    }
    ++lbl_803ECC2C;
  }
  fn_801D0544();
  if (!flags && !(z > 0.0f)) {
    WeatherSetDrawPass(1);
    WeatherLoadCornerMatrices(1);
    WeatherDrawQuads(lbl_803EB858);
  }
  fn_801D0544();
}
void WeatherInit(void) {
  lbl_803ECC34 = fn_800A33B8();
  lbl_803EB860 = 0.0f;
  if (lbl_803ECC34) {
    switch (lbl_803ECC34) {
    case 2:
      if (fn_800A3444() == 2) {
        lbl_803ECC3C = 20;
        lbl_803ECC3D = 20;
        lbl_803ECC38 = -0.3f;
        lbl_803ECC3E = 8;
        lbl_803EB858 = 10;
      } else {
        lbl_803ECC3C = 100;
        lbl_803ECC3D = 100;
        lbl_803ECC38 = -0.3f;
        lbl_803ECC3E = 8;
        lbl_803EB858 = 96;
      }
      lbl_803ECC44.r = 120;
      lbl_803ECC44.g = 120;
      lbl_803ECC44.b = 120;
      lbl_803ECC48.r = 180;
      lbl_803ECC48.g = 180;
      lbl_803ECC48.b = 180;
      lbl_803ECC30 = 1;
      break;
    case 1:
      lbl_803ECC38 = -0.05f;
      lbl_803ECC3C = 120;
      lbl_803ECC3D = 120;
      lbl_803ECC3E = 2;
      lbl_803ECC40.r = 255;
      lbl_803ECC40.g = 255;
      lbl_803ECC40.b = 255;
      lbl_803ECC48.r = 255;
      lbl_803ECC48.g = 255;
      lbl_803ECC48.b = 255;
      lbl_803ECC30 = 4;
      lbl_803EB858 = 96;
      break;
    }
    WeatherInitParticles(lbl_803667E0, 96);
  }
  fn_801C1F94(lbl_80366DE0, 0, 0x600);
  lbl_802F3A9C.mX = lbl_802F3A9C.mY = lbl_802F3A9C.mZ = 0.0f;
}
void WeatherShutdown(void) { lbl_803ECC34 = 0; }
void WeatherUpdate(float step) {
  if (!lbl_803ECC34)
    return;
  float value = fn_800A33C4();
  switch (lbl_803ECC34) {
  case 2:
    lbl_803EB858 = (unsigned int)(value * 96.0f);
    break;
  case 1:
    lbl_803EB858 = (unsigned int)(value * 96.0f);
    break;
  }
  float a = fn_800A33F4();
  WeatherUpdateDrift(a, lbl_803EB85C, step);
  WeatherUpdateSpin(a, step);
  WeatherUpdateParticles(lbl_803667E0, 96, lbl_803ECC38, step);
}
void WeatherRender(void) {
  if (!lbl_803ECC34)
    return;
  lbl_803ECC50 = -1;
  GXLoadTlut(&lbl_803ECC4C->mGX.mTlutObj, 0);
  GXLoadTexObj(&lbl_803ECC4C->mGX.mTexObj, GX_TEXMAP0);
  fn_801D0470(VptGetMatrixStack());
  Mtx44 matrix;
  fn_801D1288(2, matrix);
  fn_80214140(0);
  fn_801D0508();
  fn_801D131C(3);
  fn_801D0C58(&lbl_802F3A9C);
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
  lbl_803ECC2C = 0;
  fn_801D0508();
  fn_801D0C58(&lbl_802F3A9C);
  fn_801D0ADC(lbl_803EB850);
  fn_801D0F80(lbl_803667A0);
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
        if (lbl_803ECC2C <= 21)
          WeatherDrawCell((float)(x * 16), (float)(y * 16), (float)(z * 8));
  GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
  GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
  GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
}
}
