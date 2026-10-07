#include "engine/cu_80227F14.h"
#include "engine/vptmanager.h"
#include "game/Object_80039F5C.h"
#include "game/fn_801C1F94.h"
#include <dolphin/gx/GXStruct.h>
#include <dolphin/mtx.h>
#include <math.h>

struct Entry_801A69A8 {
  Vector_80039F5C mUnknown0;
  GXColor mUnknownC;
};
struct Bounds_801A6FC8 {
  float mUnknown0[3];
  unsigned char mUnknownC[4];
  float mUnknown10[3];
};
struct Resource_801A69A8 {
  unsigned char mUnknown0[0x7C];
  GXTexObj mUnknown7C;
  GXTlutObj mUnknown9C;
  float *mUnknownA8;
};
struct View_801A7170 {
  unsigned char mUnknown0[4];
  Vector_80039F5C mUnknown4;
  unsigned char mUnknown10[0x10];
  float mUnknown20;
  unsigned char mUnknown24[4];
  Object_80228224 *mUnknown28;
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
extern Entry_801A69A8 lbl_803667E0[96], lbl_80366DE0[96];
extern unsigned int lbl_803ECC28, lbl_803ECC2C, lbl_803ECC30;
extern int lbl_803ECC34;
extern float lbl_803ECC38;
extern unsigned char lbl_803ECC3C, lbl_803ECC3D, lbl_803ECC3E;
extern GXColor lbl_803ECC40, lbl_803ECC44, lbl_803ECC48;
extern Resource_801A69A8 *lbl_803ECC4C;
extern int lbl_803ECC50;
extern int lbl_803EB850, lbl_803EB854;
extern unsigned int lbl_803EB858;
extern float lbl_803EB85C, lbl_803EB860;
extern Vector_80039F5C lbl_802F3A9C, lbl_802F3AA8[], lbl_802F3AD8[],
    lbl_802F3B08[];
extern Bounds_801A6FC8 lbl_802F3A7C;
int fn_80145118(int);
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
void fn_8024DC48(int, void *, int);
void fn_80252034(int, int, int, int);
void fn_80251B28(int, int, int, int);
void fn_80251604(int, int);
void fn_80251CC4(int);
float *fn_801D0444(void);
void fn_8025251C(float *, int);
float *fn_801D0EE4(void);
int fn_801784C4(void);
void *fn_800A33E8(void);
void fn_80227538(void *, void *, float);
void fn_8022765C(void *, void *, void *);
void fn_801D0664(void *);
void fn_80214184(int);
unsigned int fn_8021445C(void *, int, int);
void fn_801A6924(unsigned int);
void fn_801A6870(unsigned int);
int fn_800A33B8(void);
int fn_800A3444(void);
float fn_800A33C4(void);
float fn_800A33F4(void);
extern "C" void GXLoadTlut(GXTlutObj *, int);
extern "C" void GXLoadTexObj(GXTexObj *, int);
void fn_801D1288(int, void *);
void fn_80214140(int);
void fn_801D131C(int);
void fn_801D0F80(void *);
void fn_8024DCD4(void);
void fn_8024D418(void);
void fn_8024CB90(int, int);
void fn_8024D450(int, int, int, int, int);
void fn_8024FC48(int);
void fn_8024FC84(int, int, int, int, int, int, int);
void fn_8024DF64(int);
void fn_8024DCE4(int, int, int, int, int, int);

void fn_801A69A8(Entry_801A69A8 *entry, unsigned int count) {
  GXColor *color = &lbl_803ECC40;
  lbl_803ECC4C = (Resource_801A69A8 *)fn_80145118(0);
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
  lbl_80366780[0] = lbl_803ECC4C->mUnknownA8[0];
  lbl_80366780[1] = lbl_803ECC4C->mUnknownA8[1];
  lbl_80366780[2] = lbl_803ECC4C->mUnknownA8[0];
  lbl_80366780[3] = lbl_803ECC4C->mUnknownA8[3];
  lbl_80366780[4] = lbl_803ECC4C->mUnknownA8[2];
  lbl_80366780[5] = lbl_803ECC4C->mUnknownA8[3];
  lbl_80366780[6] = lbl_803ECC4C->mUnknownA8[2];
  lbl_80366780[7] = lbl_803ECC4C->mUnknownA8[1];
  fn_80239CEC(lbl_80366780, 32);
}
void fn_801A6AF8(Entry_801A69A8 *entry, unsigned int count, float speed,
                 float step) {
  fn_801D0470(fn_80228668());
  fn_801D0508();
  fn_801D0C58(&lbl_802F3A9C);
  fn_801D0ADC(lbl_803EB850);
  Entry_801A69A8 *trail = lbl_80366DE0;
  float advance = speed * step;
  for (unsigned int i = 0; i < count; ++i, ++entry, ++trail) {
    entry->mUnknown0.mZ += advance;
    if (!(entry->mUnknown0.mZ > 0.0f)) {
      fn_80227CC0(trail, &entry->mUnknown0);
      trail->mUnknownC.r = lbl_803ECC48.r;
      trail->mUnknownC.g = lbl_803ECC48.g;
      trail->mUnknownC.b = lbl_803ECC48.b;
      trail->mUnknownC.a = lbl_803ECC3D;
      trail->mUnknown0.mZ = 0.0f;
      entry->mUnknown0.mZ += 8.0f;
    } else if (!(entry->mUnknown0.mZ <= 8.0f)) {
      fn_80227CC0(trail, &entry->mUnknown0);
      trail->mUnknownC.r = lbl_803ECC48.r;
      trail->mUnknownC.g = lbl_803ECC48.g;
      trail->mUnknownC.b = lbl_803ECC48.b;
      trail->mUnknown0.mZ = 0.0f;
      trail->mUnknownC.a = 0;
      entry->mUnknown0.mZ -= 8.0f;
    } else
      entry->mUnknownC.a = lbl_803ECC3C;
    int alpha = trail->mUnknownC.a;
    if (alpha) {
      int decay = (int)((float)lbl_803ECC3E * step);
      if (alpha > decay)
        trail->mUnknownC.a = alpha - decay;
      else
        trail->mUnknownC.a = 0;
    }
  }
  fn_801D0544();
  fn_80239D1C(lbl_803667E0, lbl_803EB858 * 16);
  fn_80239D1C(lbl_80366DE0, lbl_803EB858 * 16);
}
void fn_801A6CF8(int mode) {
  if (lbl_803ECC50 == mode)
    return;
  if (mode == 0) {
    fn_8024DC48(9, lbl_803667E0, 16);
    fn_8024DC48(11, &lbl_803667E0[0].mUnknownC, 16);
    fn_8024DC48(13, lbl_80366780, 8);
    if (lbl_803ECC34 == 2) {
      fn_80252034(0, 4, 5, 5);
      fn_80251B28(0, 255, 255, 4);
      fn_80251604(0, 4);
    } else {
      fn_80252034(1, 4, 5, 5);
      fn_80251B28(0, 0, 0, 4);
      fn_80251604(0, 3);
    }
    fn_80251CC4(1);
  } else if (mode == 1) {
    fn_8024DC48(9, lbl_80366DE0, 16);
    fn_8024DC48(11, &lbl_80366DE0[0].mUnknownC, 16);
    fn_8024DC48(13, lbl_80366780, 8);
    fn_80252034(1, 4, 5, 5);
    fn_80251B28(0, 0, 0, 4);
    fn_80251604(0, 0);
    fn_80251CC4(1);
  }
  lbl_803ECC50 = mode;
}
void fn_801A6E78(int mode) {
  if (mode == 1 || lbl_803ECC34 == 1) {
    float *matrix = fn_801D0444();
    float saved[3] = {matrix[3], matrix[7], matrix[11]};
    Vector_80039F5C *offset = lbl_802F3AD8;
    for (int slot = 3; offset <= lbl_802F3AD8 + 3; slot += 3, ++offset) {
      matrix[3] = saved[0] + offset->mX;
      matrix[7] = saved[1] + offset->mY;
      matrix[11] = saved[2] + offset->mZ;
      fn_8025251C(matrix, slot);
    }
    matrix[3] = saved[0];
    matrix[7] = saved[1];
    matrix[11] = saved[2];
  } else {
    fn_801D04C4();
    fn_801D0C58(lbl_802F3B08);
    fn_8025251C(fn_801D0444(), 3);
    fn_801D0544();
    fn_801D04C4();
    fn_801D0C58(lbl_802F3B08 + 1);
    fn_8025251C(fn_801D0444(), 6);
    fn_801D0544();
  }
}
void fn_801A6F88(float *matrix, Vector_80039F5C *out, float depth) {
  out->mX = ((matrix[14] - matrix[2]) * depth) / matrix[0];
  out->mZ = depth;
  out->mY = ((matrix[14] - matrix[6]) * depth) / matrix[5];
}
void fn_801A6FC8(float *matrix, Bounds_801A6FC8 *bounds, float a, float b) {
  fn_801D0470(fn_80228668());
  fn_801D04C4();
  fn_801D0EE4();
  Vector_80039F5C low, high, point, transformed;
  fn_801A6F88(matrix, &low, a);
  fn_801A6F88(matrix, &high, b);
  bounds->mUnknown0[0] = bounds->mUnknown0[1] = bounds->mUnknown0[2] = 10000.0f;
  bounds->mUnknown10[0] = bounds->mUnknown10[1] = bounds->mUnknown10[2] =
      -10000.0f;
  for (int i = 0; i <= 7; ++i) {
    Vector_80039F5C *v = (i & 4) ? &high : &low;
    point.mX = v->mX;
    if (!(i & 1))
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
void fn_801A7170(Bounds_801A6FC8 *bounds, float *matrix,
                 Vector_80039F5C *position) {
  View_801A7170 *view = (View_801A7170 *)fn_8002B550(0);
  Object_80228224 *object = view->mUnknown28;
  position->mX = view->mUnknown4.mX;
  position->mY = view->mUnknown4.mY;
  position->mZ = view->mUnknown4.mZ;
  Vector_80039F5C point;
  int special = 0;
  switch (view->mUnknown9C) {
  case 14:
    point = view->mUnknown14C;
    if (fn_801784C4()) {
      point.mX = -point.mX;
      point.mY = -point.mY;
    }
    special = 1;
    break;
  case 15:
    point = view->mUnknown104;
    special = 1;
    break;
  case 17:
    if (!(view->mUnknown20 >= 30.0f)) {
      point = view->mUnknownF4C;
      special = 1;
    }
    break;
  }
  float depth = !(view->mUnknown20 <= 55.0f) ? -16.0f : -32.0f;
  unsigned int count;
  if (special) {
    bounds->mUnknown0[0] = point.mX - 16.0f;
    bounds->mUnknown0[1] = point.mY - 16.0f;
    bounds->mUnknown10[0] = point.mX + 16.0f;
    bounds->mUnknown10[1] = point.mY + 16.0f;
    bounds->mUnknown0[2] = bounds->mUnknown10[2] = 0.0f;
    count = lbl_803ECC30;
  } else {
    fn_801A6FC8(matrix, bounds, -object->mUnknown232,
                -object->mUnknown232 + depth);
    count = 1;
  }
  lbl_803ECC28 = count;
}
void fn_801A7324(float a, float b, float step) {
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
void fn_801A7460(float a, float step) {
  switch (lbl_803ECC34) {
  case 1:
    lbl_803EB850 += (int)((a * 20480.0f + 4096.0f) * step);
    break;
  case 2:
    lbl_803EB850 = 0;
    break;
  }
}
void fn_801A74BC(float x, float y, float z) {
  Vector_80039F5C point = {x, y, z};
  fn_801D04C4();
  fn_801D0C58(&point);
  fn_801D04C4();
  fn_801D0664(lbl_803667A0);
  fn_80214184(0);
  unsigned int flags = fn_8021445C(&lbl_802F3A7C, 0, 0) & 63;
  if (!flags) {
    fn_801A6CF8(0);
    if (lbl_803ECC28 > 1) {
      Vector_80039F5C *offset = lbl_802F3AA8;
      for (unsigned int i = 0; i < lbl_803ECC28; ++i, ++offset) {
        fn_801A6E78(0);
        if (lbl_803ECC34 == 2)
          fn_801A6924(lbl_803EB858);
        else
          fn_801A6870(lbl_803EB858);
        if (lbl_803ECC34 == 1)
          fn_801D0ADC(lbl_803EB854);
        else
          fn_801D0C58(offset);
      }
    } else {
      fn_801A6E78(0);
      if (lbl_803ECC34 == 2)
        fn_801A6924(lbl_803EB858);
      else
        fn_801A6870(lbl_803EB858);
    }
    ++lbl_803ECC2C;
  }
  fn_801D0544();
  if (!flags && !(z > 0.0f)) {
    fn_801A6CF8(1);
    fn_801A6E78(1);
    fn_801A6870(lbl_803EB858);
  }
  fn_801D0544();
}
void fn_801A762C(void) {
  lbl_803ECC34 = fn_800A33B8();
  lbl_803EB860 = 0.0f;
  if (lbl_803ECC34) {
    switch (lbl_803ECC34) {
    case 2:
      if (fn_800A3444() == 2) {
        lbl_803ECC3D = 20;
        lbl_803EB858 = 10;
        lbl_803ECC3C = 20;
      } else {
        lbl_803ECC3D = 100;
        lbl_803EB858 = 96;
        lbl_803ECC3C = 100;
      }
      lbl_803ECC38 = -0.3f;
      lbl_803ECC3E = 8;
      lbl_803ECC30 = 1;
      lbl_803ECC44.r = lbl_803ECC44.g = lbl_803ECC44.b = 120;
      lbl_803ECC48.r = lbl_803ECC48.g = lbl_803ECC48.b = 180;
      break;
    case 1:
      lbl_803ECC38 = -0.05f;
      lbl_803ECC3D = 120;
      lbl_803ECC3E = 2;
      lbl_803ECC30 = 4;
      lbl_803EB858 = 96;
      lbl_803ECC3C = 120;
      lbl_803ECC40.r = lbl_803ECC40.g = lbl_803ECC40.b = 255;
      lbl_803ECC48.r = lbl_803ECC48.g = lbl_803ECC48.b = 255;
      break;
    }
    fn_801A69A8(lbl_803667E0, 96);
  }
  fn_801C1F94(lbl_80366DE0, 0, 0x600);
  lbl_802F3A9C.mX = lbl_802F3A9C.mY = lbl_802F3A9C.mZ = 0.0f;
}
void fn_801A7778(void) { lbl_803ECC34 = 0; }
void fn_801A7784(float step) {
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
  fn_801A7324(a, lbl_803EB85C, step);
  fn_801A7460(a, step);
  fn_801A6AF8(lbl_803667E0, 96, lbl_803ECC38, step);
}
void fn_801A7880(void) {
  if (!lbl_803ECC34)
    return;
  lbl_803ECC50 = -1;
  GXLoadTlut(&lbl_803ECC4C->mUnknown9C, 0);
  GXLoadTexObj(&lbl_803ECC4C->mUnknown7C, 0);
  fn_801D0470(fn_80228668());
  Mtx44 matrix;
  fn_801D1288(2, matrix);
  fn_80214140(0);
  fn_801D0508();
  fn_801D131C(3);
  fn_801D0C58(&lbl_802F3A9C);
  Bounds_801A6FC8 bounds;
  Vector_80039F5C position;
  fn_801A7170(&bounds, matrix[0], &position);
  fn_801D0544();
  int minX = (int)((bounds.mUnknown0[0] - 15.0f) * 0.0625f),
      maxX = (int)((bounds.mUnknown10[0] + 15.0f) * 0.0625f);
  int minY = (int)((bounds.mUnknown0[1] - 15.0f) * 0.0625f),
      maxY = (int)((bounds.mUnknown10[1] + 15.0f) * 0.0625f);
  int minZ = (int)(bounds.mUnknown0[2] * 0.125f),
      maxZ = (int)((bounds.mUnknown10[2] + 7.0f) * 0.125f);
  if (minZ < 0)
    minZ = 0;
  if (maxZ < 0)
    maxZ = 0;
  lbl_803ECC2C = 0;
  fn_801D0508();
  fn_801D0C58(&lbl_802F3A9C);
  fn_801D0ADC(lbl_803EB850);
  fn_801D0F80(lbl_803667A0);
  fn_801D0544();
  fn_8024DCD4();
  fn_8024D418();
  fn_8024CB90(0, 1);
  fn_8024CB90(9, 2);
  fn_8024CB90(11, 2);
  fn_8024CB90(13, 2);
  fn_8024D450(1, 11, 1, 5, 0);
  fn_8024D450(1, 9, 1, 4, 0);
  fn_8024D450(1, 13, 1, 4, 0);
  fn_8024FC48(1);
  fn_8024FC84(4, 0, 1, 1, 0, 0, 2);
  fn_8024DF64(1);
  fn_8024DCE4(0, 1, 4, 60, 0, 125);
  for (int z = minZ; z <= maxZ; ++z)
    for (int x = minX; x <= maxX; ++x)
      for (int y = minY; y <= maxY; ++y)
        if (lbl_803ECC2C <= 21)
          fn_801A74BC((float)(x * 16), (float)(y * 16), (float)(z * 8));
  fn_80251604(0, 4);
  fn_80252034(1, 4, 5, 5);
  fn_80251B28(0, 0, 0, 255);
}
}
