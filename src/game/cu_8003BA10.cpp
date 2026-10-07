#include "game/Block_80307980.h"
#include "game/Init_8004A040.h"
#include "game/Item_800476DC.h"
#include "game/ModuleGroup_80033A5C.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8003DEC4.h"
#include "game/Object_8008044C.h"
#include "game/Pair_8017055C.h"
#include "game/bitstream.h"
#include "game/cu_80047E28.h"
#include "game/fn_802270D4.h"
#include "game/fn_80227638.h"
#include <math.h>
struct Clip_8003BFCC {
  float mPoints[7][3];
  Pair_8017055C mPairs[7];
  unsigned char mCount;
  unsigned char mUnknown141[3];
};
struct Projection_8003BA10 {
  float mColor[4];
  float mPoints[4][3];
  Pair_8017055C mPairs[4];
  Clip_8003BFCC mRecords[4];
  unsigned char mUnknown672, mUnknown673;
};
struct Creation_8003D378 {
  Init_8004A040 mInit;
  int mUnknown1C;
  Ids_8015F6E8 mUnknown20;
  int mUnknown28, mUnknown2C, mUnknown30, mUnknown34;
  char mUnknown38[31];
  unsigned char mUnknown57, mUnknown58, mUnknown59, mUnknown5A, mUnknown5B;
  FMCAPPORTValues mUnknown5C;
};
struct Region_8003BDF0 {
  unsigned char mUnknown0[128];
  unsigned int mUnknown128;
  unsigned char (*mUnknown132)[48];
};
extern "C" {
extern void *lbl_803EA410, *lbl_803EA414, *lbl_803EA418;
extern Skeleton_80041930 *lbl_803EA41C;
extern Skeleton_80041930 *lbl_803EA420[2];
extern Skeleton_80041930 *lbl_803EA428, *lbl_803EA42C;
extern Object_8003DEC4 **lbl_803EA430;
extern unsigned short lbl_803EA434, lbl_803EA436;
extern unsigned char lbl_803EA438;
extern int lbl_802CCD8C[3], lbl_802CCD98[3], lbl_802CCDA4[14];
extern void *lbl_803EAB3C, *lbl_803EAAFC, *lbl_803EAAE0;
unsigned char fn_8004A238();
void fn_80042380(Object_8003DEC4 *, int, float *, int *);
void fn_8022765C(void *, void *, void *);
void fn_80227690(void *, void *, void *);
void fn_80227264(void *, void *, float);
void fn_80227248(void *, void *, float);
void fn_80227CC0(void *, void *);
void fn_802271F0(void *);
void fn_80227C2C(void *, void *);
float fn_8022781C(void *, void *);
float fn_802276E8(void *, void *);
int fn_80227040(void *, void *);
void fn_801CFC14(int, float *, float *);
float fn_801CFD28(int);
Region_8003BDF0 *fn_80054130();
int fn_80054138(float *);
void fn_800542DC(void *, void *, void *);
float fn_8005434C(void *);
void fn_8003BDF0(Object_8003DEC4 *, Pair_8017055C *, int);
void fn_8003BFCC(Object_8003DEC4 *, float *, Pair_8017055C *, Pair_8017055C *,
                 Pair_8017055C *, int, float);
int fn_8003C97C(Pair_8017055C *, Pair_8017055C *, Pair_8017055C *,
                Pair_8017055C *, float *, float *);
void fn_8003C8C8(void *, Pair_8017055C *, float *);
void fn_8022732C(void *, void *, float);
void fn_80227904(void *, void *, void *, float);
void fn_80227930(void *, void *, void *, float);

void fn_801D04C4();
void fn_801D06D4();
void fn_801D0544();
void fn_80236384(int);
unsigned int fn_80236398(int);
void fn_801A3FFC();
void fn_801A42D4();
void fn_801A45CC();
void fn_80042A08(Object_8003DEC4 *, BitStream_t *);
void fn_80042AF4(Object_8003DEC4 *, BitStream_t *, BitStream_t *, BitStream_t *,
                 BitStream_t *, float);
void fn_80190F18(BitStream_t *, int);
void fn_800B4D7C();
void fn_800B4A88();
void fn_801BE030(int, void **);
void fn_800A3D70();
void fn_800A3C14();
void fn_800AE10C();
void fn_800ADE6C();
Skeleton_80041930 *fn_801EF390(void *, int, int);
void fn_801C4DEC(Skeleton_80041930 *);
void fn_801C4F10(Skeleton_80041930 *, Skeleton_80041930 *);
void fn_800AF630(void *, int, int, int);
void fn_800AF790(int, Skeleton_80041930 *, const char *, const char *, int);
void fn_8015F484(Skeleton_80041930 *, Skeleton_80041930 **, Skeleton_80041930 *,
                 Skeleton_80041930 *);
int fn_800809FC(Object_8008044C *, int, int *);
int fn_800808F8(Object_8008044C *);
void fn_8003BA00();
void fn_8003BA04();
void fn_8003BA08();
void fn_8003BA0C();
void fn_801DCF0C(int, int, int, void (*)(), void (*)());
void fn_801DD0C8(int, int, int, int (*)(void));
void *fn_801DD268(int, int, int, void *);
void *fn_801DD168(int, int, void *);
void fn_801DD3AC(int, void *, int);
void fn_801DD320(int, void *);
int fn_8003CBFC();
int fn_8003CC20();
int fn_8003CC44();
void fn_8004A140(int, int, int);
void fn_8003D0C8(int);
void fn_80136AE4(int, int);
void fn_8003D12C();
void fn_8003D2E0();
void fn_8004A0E0(int, int);
void fn_80048EDC();
void fn_8003D988(int, int *, int);
void fn_80160C10();
int fn_8003D378(int, int);
void fn_801F282C();
void fn_801F283C();
int fn_801F7C88();
void *fn_801D2B7C(int, int, int);
void fn_8015EE74();
void fn_8015EF10();
int fn_80080D38(Object_8008044C *, char *, int);
int fn_8015F5BC(const char *);
void fn_8015F068(int, Ids_8015F6E8 *);
void fn_8015F124(int, int);
void fn_8015F1D4(int, int);
void fn_8015F298(int, int);
void fn_80080A9C(Object_8008044C *, char *, int);
void fn_80048FE8(unsigned char, unsigned char, int);
unsigned char fn_80080E48(Object_8008044C *);
int fn_80081E3C(Object_8008044C *);
int fn_80082280(Object_8008044C *);
int fn_800822D4(Object_8008044C *);
Item_800476DC *fn_800475FC(int);
void fn_800476CC(Item_800476DC *, const char *);
void fn_801611BC(int, const char *, int);
void fn_8016130C(int, int, int, int, int);
void fn_8003D958();

void fn_80160CDC();
int fn_800A3420();
void fn_80049E6C();
void fn_801613F0();
int fn_80027DF0();
void fn_80161498();
void fn_80228D58(void *);
void fn_80228DD4();
void fn_80047630(Item_800476DC *);
void fn_801D2BD0(void *);
void fn_8004A118();
void fn_800AF71C();
void fn_801F010C(void *, int);
void fn_8004A1FC(int);
int fn_801DCF8C(int);
void fn_80160F98();
void fn_80048F34();
int fn_80160C08();
void fn_8009BD48(int *, int, int, int);
int fn_800429CC(int);
void fn_80030ACC(void (*)(BitStream_t *),
                 void (*)(BitStream_t *, BitStream_t *, BitStream_t *,
                          BitStream_t *, float),
                 int, const char *);
void fn_8003BA10(Object_8003DEC4 *object, float *color, Pair_8017055C *axis,
                 int angle) {
  Projection_8003BA10 *p = (Projection_8003BA10 *)&object->mUnknown4184[72];
  p->mUnknown673 =
      fn_8004A238() && (object->mUnknown20 & 1) && !(object->mUnknown20 & 2);
  float first[4], center[4], delta[4], direction[2];
  fn_80042380(object, 4, first, 0);
  fn_80042380(object, 8, center, 0);
  fn_8022765C(center, center, first);
  fn_80227264(center, center, 0.5f);
  fn_80042380(object, 26, first, 0);
  fn_802276B4(delta, first, center);
  fn_80227CC0(center, center);
  fn_80227CC0(delta, delta);
  delta[2] = 0.0f;
  fn_801CFC14(object->mUnknown36, &direction[1], &direction[0]);
  float width = fabsf(fn_802276E8(direction, axis));
  if (!(width >= 0.65f))
    width = 0.65f;
  float length = fn_802270D4(delta);
  Pair_8017055C forward, backward;
  if (!(length >= 0.4f)) {
    if (!(length <= 0.2f)) {
      fn_80227264(delta, delta, 1.0f / length);
      float t = (length - 0.2f) * 5.0f;
      float f = t * (-width) + width + t * 0.4f;
      float b = t * (0.85f - width) + width;
      forward.mX = delta[0] * f;
      forward.mY = delta[1] * f;
      backward.mX = -delta[0] * b;
      backward.mY = -delta[1] * b;
    } else {
      delta[0] += axis->mX * (0.2f - length);
      delta[1] += axis->mY * (0.2f - length);
      fn_802271F0(delta);
      forward.mX = delta[0] * width;
      forward.mY = delta[1] * width;
      backward.mX = -delta[0] * width;
      backward.mY = -delta[1] * width;
    }
  } else {
    forward.mX = delta[0];
    forward.mY = delta[1];
    backward.mX = 0.0f;
    backward.mY = 0.0f;
    fn_80227264(delta, delta, 1.0f / length);
    backward.mX = -(delta[0] * 0.85f);
    backward.mY = -(delta[1] * 0.85f);
  }
  Pair_8017055C side;
  side.mX = delta[1];
  side.mY = -delta[0];
  fn_80227248(&side, &side, width);
  for (int i = 0; i < 4; ++i)
    p->mColor[i] = color[i];
  p->mPoints[0][0] = center[0] - side.mX + forward.mX;
  p->mPoints[0][1] = center[1] - side.mY + forward.mY;
  p->mPoints[1][0] = center[0] + side.mX + forward.mX;
  p->mPoints[1][1] = center[1] + side.mY + forward.mY;
  p->mPoints[2][0] = center[0] + side.mX + backward.mX;
  p->mPoints[2][1] = center[1] + side.mY + backward.mY;
  p->mPoints[3][0] = center[0] - side.mX + backward.mX;
  p->mPoints[3][1] = center[1] - side.mY + backward.mY;
  if (fn_80054130()) {
    unsigned int value =
        object->mUnknown4968 * lbl_803EA436 + object->mUnknown4969;
    int enabled = (value & 1) ? lbl_803EA438 : !lbl_803EA438;
    if (enabled) {
      p->mUnknown672 = 0;
      fn_8003BDF0(object, axis, angle);
    }
  }
}
void fn_8003BDF0(Object_8003DEC4 *object, Pair_8017055C *axis, int angle) {
  Region_8003BDF0 *regions = fn_80054130();
  if (!regions)
    return;
  float first[4], center[4];
  fn_80042380(object, 4, first, 0);
  fn_80042380(object, 8, center, 0);
  fn_8022765C(center, center, first);
  fn_80227264(center, center, 0.5f);
  fn_80042380(object, 26, first, 0);
  first[2] = (first[2] + center[2]) * 0.5f;
  float radius = fabsf(1.0f / fn_801CFD28(angle)) * first[2];
  Projection_8003BA10 *p = (Projection_8003BA10 *)&object->mUnknown4184[72];
  radius += fn_8022781C(p->mPoints[0], p->mPoints[2]);
  for (unsigned char i = 0; i < regions->mUnknown128; ++i) {
    Pair_8017055C a, b, mid;
    fn_800542DC(regions->mUnknown132[i], &a, &b);
    float scale = fn_8005434C(regions->mUnknown132[i]);
    mid.mX = (a.mX + b.mX) * 0.5f;
    mid.mY = (a.mY + b.mY) * 0.5f;
    float extent = fn_8022781C(&mid, &a);
    if (!(fn_8022781C(&mid, center) >= radius + extent))
      fn_8003BFCC(object, center, axis, &a, &b, angle, scale);
  }
}
void fn_8003BFCC(Object_8003DEC4 *object, float *center, Pair_8017055C *axis,
                 Pair_8017055C *a, Pair_8017055C *b, int angle, float scale) {
  Projection_8003BA10 *p = (Projection_8003BA10 *)&object->mUnknown4184[72];
  if (p->mUnknown672 > 3)
    return;
  Pair_8017055C original = {center[0], center[1]}, shifted;
  float t, u;
  fn_80227690(&shifted, &original, axis);
  if (fn_8003C97C(&original, &shifted, a, b, &t, &u) && t > 0.0f)
    return;
  float height = fn_801CFD28(angle);
  scale *= 0.7142857313156128f;
  float shift = scale / height;
  Clip_8003BFCC *out = &p->mRecords[p->mUnknown672];
  out->mCount = 0;
  int accepted = 0;
  Pair_8017055C shiftedA = *a, shiftedB = *b;
  fn_8022732C(&shiftedA, axis, shift);
  fn_8022732C(&shiftedB, axis, shift);
  float minimum = 1000000.0f, maximum = -1000000.0f;
  for (unsigned char i = 0; i < 4; ++i) {
    if (fn_8003C97C(&shiftedA, &shiftedB, (Pair_8017055C *)p->mPoints[i],
                    (Pair_8017055C *)p->mPoints[(i + 1) % 4], &t, &u) &&
        !(u <= 0.0f) && !(u >= 1.0f)) {
      if (!(t >= minimum))
        minimum = t;
      if (!(t <= maximum))
        maximum = t;
    }
  }
  for (unsigned char i = 0; i < 4; ++i) {
    original.mX = p->mPoints[i][0];
    original.mY = p->mPoints[i][1];
    shifted = original;
    fn_8022732C(&shifted, axis, -scale / height);
    if (fn_8003C97C(&original, &shifted, a, b, &t, &u) && !(t >= 1.0f) &&
        !(u <= 0.0f) && !(u >= 1.0f)) {
      if (!(t <= 0.0f))
        accepted = 1;
      for (int j = 0; j < 3; ++j)
        out->mPoints[out->mCount][j] = p->mPoints[i][j];
      out->mPairs[out->mCount] = p->mPairs[i];
      ++out->mCount;
    }
    unsigned char next = (i + 1) % 4;
    float points[3][3];
    Pair_8017055C pairs[3];
    float parameters[3];
    unsigned char count = 0;
    if (fn_8003C97C((Pair_8017055C *)p->mPoints[i],
                    (Pair_8017055C *)p->mPoints[next], &shiftedA, &shiftedB, &t,
                    &u) &&
        !(t <= 0.0f) && !(t >= 1.0f) && !(u <= 0.0f) && !(u >= 1.0f)) {
      accepted = 1;
      fn_80227930(points[count], p->mPoints[next], p->mPoints[i], t);
      fn_80227904(&pairs[count], &p->mPairs[next], &p->mPairs[i], t);
      parameters[count] = t;
      count = 1;
    }
    if (fn_8003C97C((Pair_8017055C *)p->mPoints[i],
                    (Pair_8017055C *)p->mPoints[next], a, &shiftedA, &t, &u) &&
        !(t <= 0.0f) && !(t >= 1.0f)) {
      if (!(u <= 0.0f))
        accepted = 1;
      if (u < 1.0f) {
        fn_80227930(points[count], p->mPoints[next], p->mPoints[i], t);
        fn_80227904(&pairs[count], &p->mPairs[next], &p->mPairs[i], t);
        parameters[count] = t;
        ++count;
      } else if (!(minimum > 0.0f)) {
        points[count][0] = shiftedA.mX;
        points[count][1] = shiftedA.mY;
        fn_8003C8C8(p, &shiftedA, (float *)&pairs[count]);
        parameters[count] = t;
        ++count;
      }
    }
    if (fn_8003C97C((Pair_8017055C *)p->mPoints[i],
                    (Pair_8017055C *)p->mPoints[next], b, &shiftedB, &t, &u) &&
        !(t <= 0.0f) && !(t >= 1.0f)) {
      if (!(u <= 0.0f))
        accepted = 1;
      if (u < 1.0f) {
        fn_80227930(points[count], p->mPoints[next], p->mPoints[i], t);
        fn_80227904(&pairs[count], &p->mPairs[next], &p->mPairs[i], t);
        parameters[count] = t;
        ++count;
      } else if (!(maximum < 1.0f)) {
        points[count][0] = shiftedB.mX;
        points[count][1] = shiftedB.mY;
        fn_8003C8C8(p, &shiftedB, (float *)&pairs[count]);
        parameters[count] = t;
        ++count;
      }
    }
    for (unsigned char j = 0; j < count; ++j) {
      float least = 1000000.0f;
      unsigned char index = 0;
      for (unsigned char k = 0; k < count; ++k)
        if (!(parameters[k] >= least)) {
          least = parameters[k];
          index = k;
        }
      for (int k = 0; k < 3; ++k)
        out->mPoints[out->mCount][k] = points[index][k];
      out->mPairs[out->mCount] = pairs[index];
      parameters[index] = 1000000.0f;
      ++out->mCount;
    }
  }
  if (!accepted)
    return;
  for (unsigned char i = 0; i < out->mCount; ++i) {
    original.mX = out->mPoints[i][0];
    original.mY = out->mPoints[i][1];
    fn_80227690(&shifted, out->mPoints[i], axis);
    if (fn_8003C97C(&original, &shifted, a, b, &t, &u)) {
      fn_80227904(out->mPoints[i], &shifted, &original, t);
      out->mPoints[i][2] = (t * height) * 1.4f;
    }
  }
  ++p->mUnknown672;
}
void fn_8003C8C8(void *record, Pair_8017055C *offset, float *parameters) {
  struct View {
    unsigned char pad[16];
    float points[4][3];
  };
  View *p = (View *)record;
  Pair_8017055C line;
  fn_80227690(&line, p->points[0], p->points[3]);
  fn_80227638(&line, offset, &line);
  fn_8003C97C((Pair_8017055C *)p->points[0], (Pair_8017055C *)p->points[1],
              offset, &line, parameters, 0);
  fn_80227690(&line, p->points[1], p->points[0]);
  fn_80227638(&line, offset, &line);
  fn_8003C97C((Pair_8017055C *)p->points[1], (Pair_8017055C *)p->points[2],
              offset, &line, parameters + 1, 0);
}
int fn_8003C97C(Pair_8017055C *a, Pair_8017055C *b, Pair_8017055C *c,
                Pair_8017055C *d, float *t, float *u) {
  float dy = b->mY - a->mY, dx = b->mX - a->mX;
  float cx = d->mX - c->mX, cy = d->mY - c->mY;
  float determinant = cy * dx - cx * dy;
  if (!(fabsf(determinant) >= 0.0000001f))
    return 0;
  if (t)
    *t = ((a->mY - c->mY) * cx + (c->mX - a->mX) * cy) / determinant;
  if (u)
    *u = ((a->mX - c->mX) * dy + (c->mY - a->mY) * dx) / -determinant;
  return 1;
}
void fn_8003CA20() {
  fn_801D04C4();
  fn_80236384(0);
  fn_801D06D4();
  unsigned int value = fn_80236398(0);
  float color[4] = {(float)(value & 255) * 0.0078125f,
                    (float)((value >> 8) & 255) * 0.0078125f,
                    (float)((value >> 16) & 255) * 0.0078125f,
                    (float)(value >> 24) * 0.0078125f};
  float vector[4];
  vector[0] = 0.0f;
  vector[1] = 0.0f;
  vector[2] = 1.0f;
  fn_80227C2C(vector, vector);
  vector[2] = 0.0f;
  float length = fn_802270D4(vector);
  if (!(length >= 0.0001f)) {
    vector[0] = 0.0f;
    vector[1] = 1.0f;
    length = 1.0f;
  }
  float angleVector[4] = {vector[0], vector[1], 1.0f};
  int angle = fn_80227040(angleVector, vector);
  fn_80227264(vector, vector, 1.0f / length);
  for (int i = 0; i < lbl_803EA434; ++i)
    fn_8003BA10(lbl_803EA430[i], color, (Pair_8017055C *)vector, angle);
  fn_801D0544();
  lbl_803EA438 = !lbl_803EA438;
}
int fn_8003CBFC() {
  fn_801A3FFC();
  return 0;
}
int fn_8003CC20() {
  fn_801A42D4();
  return 0;
}
int fn_8003CC44() {
  fn_801A45CC();
  return 0;
}
void fn_8003CC68(Skeleton_80041930 *skeleton) {
  unsigned short values[64][3] = {
      {65518, 0, 0},
      {65469, 65453, 65493},
      {253, 0, 0},
      {1293, 27, 0},
      {65220, 0, 0},
      {65469, 83, 43},
      {253, 0, 0},
      {1293, 65509, 0},
      {65220, 0, 0},
      {65435, 0, 0},
      {161, 0, 0},
      {0, 0, 0},
      {366, 0, 0},
      {64970, 0, 0},
      {65466, 65502, 1143},
      {54, 65, 199},
      {324, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {65466, 34, 64393},
      {54, 65471, 65337},
      {324, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {158, 0, 0},
      {158, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
  };
  for (unsigned int i = 0; i < skeleton->mUnknown6; ++i) {
    skeleton->mUnknown1040[i][0] = values[i][0];
    skeleton->mUnknown1040[i][1] = values[i][1];
    skeleton->mUnknown1040[i][2] = values[i][2];
  }
}

void fn_8003CD1C(Skeleton_80041930 *skeleton) {
  unsigned short values[19][3] = {
      {56480, 0, 0}, {8698, 0, 0},          {0, 0, 0}, {62991, 0, 0},
      {0, 0, 0},     {43390, 0, 0},         {0, 0, 0}, {40775, 5152, 0},
      {0, 0, 0},     {40775, 60384, 0},     {0, 0, 0}, {61797, 11722, 27354},
      {0, 0, 0},     {61785, 53814, 38182}, {0, 0, 0}, {35720, 28161, 65475},
      {0, 0, 0},     {35706, 37375, 60},    {0, 0, 0},
  };
  for (unsigned int i = 0; i < skeleton->mUnknown6; ++i) {
    skeleton->mUnknown1040[i][0] = values[i][0];
    skeleton->mUnknown1040[i][1] = values[i][1];
    skeleton->mUnknown1040[i][2] = values[i][2];
  }
}

void fn_8003CDF8(Skeleton_80041930 *skeleton) {
  unsigned short values[5][3] = {
      {0, 0, 0},           {64403, 64991, 18297},
      {64403, 544, 47238}, {24448, 65257, 65414},
      {5556, 65522, 88},
  };
  for (unsigned int i = 0; i < skeleton->mUnknown6; ++i) {
    skeleton->mUnknown1040[i][0] = values[i][0];
    skeleton->mUnknown1040[i][1] = values[i][1];
    skeleton->mUnknown1040[i][2] = values[i][2];
  }
}

void fn_8003CEB0(BitStream_t *stream) {
  for (unsigned int i = 0; i < lbl_803EA434; ++i) {
    Object_8003DEC4 *object = lbl_803EA430[i];
    fn_80042A08(object, stream);
    fn_80191068(stream, object->mUnknown5188.mUnknown568, 1);
    fn_80191068(stream, (unsigned long long)object->mUnknown5188.mUnknown56C,
                4);
    fn_80191068(stream, (unsigned long long)object->mUnknown5188.mUnknown570,
                4);
    fn_80191068(stream, (unsigned long long)object->mUnknown5188.mUnknown574,
                4);
  }
}
void fn_8003CF88(BitStream_t *a, BitStream_t *b, BitStream_t *c, BitStream_t *d,
                 float t) {
  for (unsigned int i = 0; i < lbl_803EA434; ++i) {
    Object_8003DEC4 *object = lbl_803EA430[i];
    fn_80042AF4(object, a, b, c, d, t);
    object->mUnknown972 = fn_80054138(object->mUnknown4);
    fn_80190F18(b, 1);
    fn_80190F18(a, 1);
    if (d)
      fn_80190F18(d, 1);
    if (c)
      fn_80190F18(c, 1);
    fn_80190F18(b, 4);
    fn_80190F18(b, 4);
    fn_80190F18(b, 4);
    fn_80190F18(a, 12);
    if (d)
      fn_80190F18(d, 12);
    if (c)
      fn_80190F18(c, 12);
  }
}
void fn_8003D0C8(int mode) {
  if (mode)
    fn_800B4D7C();
  else
    fn_800B4A88();
  fn_801BE030(1, &lbl_803EAB3C);
  fn_800A3D70();
  fn_801BE030(3, &lbl_803EAAFC);
  fn_800A3C14();
  fn_800AE10C();
  fn_801BE030(4, &lbl_803EAAE0);
  fn_800ADE6C();
}
void fn_8003D12C() {
  lbl_803EA41C = fn_801EF390(gAnimData.fn_80033AF8(), 57, 1);
  fn_801C4DEC(lbl_803EA41C);
  fn_8003CC68(lbl_803EA41C);
  for (int i = 0; i < 3; ++i) {
    lbl_802CCD98[i] = (short)lbl_803EA41C->mUnknown1040[15][i] * 16;
    lbl_802CCD8C[i] = (short)lbl_803EA41C->mUnknown1040[21][i] * 16;
  }
  lbl_803EA420[0] = fn_801EF390(gAnimData.fn_80033AF8(), 58, 1);
  fn_801C4DEC(lbl_803EA420[0]);
  for (int i = 0; i < 3; ++i)
    ((float *)((char *)lbl_803EA420[0] + 16))[i] = 0.0f;
  lbl_803EA420[1] = fn_801EF390(gAnimData.fn_80033AF8(), 59, 1);
  fn_801C4DEC(lbl_803EA420[1]);
  for (int i = 0; i < 3; ++i)
    ((float *)((char *)lbl_803EA420[1] + 16))[i] = 0.0f;
  fn_801C4F10(lbl_803EA420[0], lbl_803EA420[1]);
  lbl_803EA428 = fn_801EF390(gAnimData.fn_80033AF8(), 61, 1);
  fn_801C4DEC(lbl_803EA428);
  fn_8003CD1C(lbl_803EA428);
  for (int i = 0; i < 3; ++i)
    ((float *)((char *)lbl_803EA428 + 16))[i] = 0.0f;
  lbl_803EA42C = fn_801EF390(gAnimData.fn_80033AF8(), 62, 1);
  fn_801C4DEC(lbl_803EA42C);
  fn_8003CDF8(lbl_803EA42C);
  for (int i = 0; i < 3; ++i)
    ((float *)((char *)lbl_803EA42C + 16))[i] = 0.0f;
}
void fn_8003D2E0() {
  fn_800AF630(gAnimData.fn_80033AF8(), 60, 1, 32);
  fn_800AF790(0, lbl_803EA41C, "low_torso", "neckhi", 0);
  fn_800AF790(1, lbl_803EA41C, "lshoulder", "lwrist", 1);
  fn_800AF790(2, lbl_803EA41C, "rshoulder", "rwrist", 1);
}
int fn_8003D378(int owner, int mode) {
  Object_8008044C object;
  fn_801F282C();
  lbl_803EA430 = (Object_8003DEC4 **)fn_801D2B7C(lbl_803EA434 * 4, 0, 0);
  int result = fn_801F7C88();
  if (lbl_803EA430) {
    fn_8008044C(&object, 0, mode ? 0x54414D53 : 0x454D4147);
    fn_8003D958();
    Creation_8003D378 init;
    init.mInit.mUnknown00 = 1;
    init.mInit.mUnknown04 = (int)lbl_803EA41C;
    ((Skeleton_80041930 **)init.mInit.mUnknown08)[0] = lbl_803EA420[0];
    ((Skeleton_80041930 **)init.mInit.mUnknown08)[1] = lbl_803EA420[1];
    init.mInit.mUnknown10 = (int)lbl_803EA428;
    init.mInit.mUnknown14 = (int)lbl_803EA42C;
    fn_8015EE74();
    unsigned int order[14], keys[14];
    for (unsigned int i = 0; i < lbl_803EA434; ++i) {
      unsigned char team = mode ? 0 : (unsigned char)(i / lbl_803EA436);
      fn_800809C4(&object, lbl_802CCDA4[i], 0);
      char name[28];
      int hasName = fn_80080D38(&object, name, 27);
      fn_800496A0(i, i, team, lbl_802CCDA4[i]);
      order[i] = i;
      int a = fn_80049888(i), b = fn_800499A8(i);
      Ids_8015F6E8 ids;
      if (hasName) {
        fn_80049E00(i, name, &ids);
        keys[i] = fn_8015F5BC(name);
      } else {
        fn_80049E00(i, 0, &ids);
        keys[i] = 65535;
      }
      int c = fn_800499E8(i);
      fn_8015F068(i, &ids);
      fn_8015F124(i, a);
      fn_8015F1D4(i, b);
      fn_8015F298(i, c);
    }
    fn_8015EF10();
    for (unsigned int i = 0; i < lbl_803EA434; ++i)
      for (unsigned int j = i + 1; j < lbl_803EA434; ++j) {
        if (keys[i] > keys[j]) {
          unsigned int key = keys[i];
          keys[i] = keys[j];
          keys[j] = key;
          unsigned int index = order[i];
          order[i] = order[j];
          order[j] = index;
        }
      }
    for (unsigned int rank = 0; rank < lbl_803EA434; ++rank) {
      unsigned int index = order[rank];
      init.mUnknown57 = mode ? rank : index / lbl_803EA436;
      init.mUnknown58 = index % lbl_803EA436;
      init.mUnknown59 = index;
      init.mUnknown5A = index;
      init.mInit.mUnknown18 = lbl_802CCDA4[index];
      fn_800809C4(&object, init.mInit.mUnknown18, 0);
      fn_80080A9C(&object, init.mUnknown38, 31);
      if (!mode)
        fn_80048FE8(init.mUnknown5A, init.mUnknown57, init.mInit.mUnknown18);
      char name[28];
      int hasName = fn_80080D38(&object, name, 27);
      int value = fn_80080E20(&object);
      if (hasName) {
        init.mUnknown1C = fn_8015F5BC(name);
        fn_80049E00(init.mUnknown5A, init.mUnknown1C == 65535 ? 0 : name,
                    &init.mUnknown20);
      } else {
        fn_80049E00(init.mUnknown5A, 0, &init.mUnknown20);
        init.mUnknown1C = 65535;
      }
      init.mUnknown30 = fn_800499E8(index);
      init.mUnknown28 = fn_80049888(init.mUnknown5A);
      init.mUnknown2C = fn_800499A8(init.mUnknown5A);
      init.mUnknown34 = value;
      init.mUnknown5B = fn_80080E48(&object);
      Block_80307980 block;
      fn_80082138(&object, &block);
      fn_80046804(&block, &init.mUnknown5C);
      if (owner) {
        lbl_803EA430[index] =
            (Object_8003DEC4 *)fn_801DD268(owner, 0, 0, &init);
        fn_801DD3AC(owner, lbl_803EA430[index], 10);
        lbl_803EA430[index]->mUnknown988 =
            fn_800475FC(init.mUnknown57 * 7 + init.mUnknown58);
        fn_800476CC(lbl_803EA430[index]->mUnknown988, " ");
      } else {
        lbl_803EA430[index] = (Object_8003DEC4 *)fn_801DD168(0, 0, &init);
        lbl_803EA430[index]->mUnknown988 = 0;
      }
      if (lbl_803EA410 && lbl_803EA414) {
        Projection_8003BA10 *p =
            (Projection_8003BA10 *)&lbl_803EA430[index]->mUnknown4184[72];
        p->mUnknown672 = 0;
        p->mPairs[0].mX = 0.0f;
        p->mPairs[0].mY = 0.0f;
        p->mPairs[1].mX = 1.0f;
        p->mPairs[1].mY = 0.0f;
        p->mPairs[2].mX = 1.0f;
        p->mPairs[2].mY = 1.0f;
        p->mPairs[3].mX = 0.0f;
        p->mPairs[3].mY = 1.0f;
        for (int k = 0; k < 4; ++k)
          p->mPoints[k][2] = 0.0f;
      }
      fn_80049124(index);
      if (hasName)
        fn_801611BC(init.mUnknown5A, name, 0);
      else {
        int a = fn_80081E3C(&object) + 1, b = fn_80082280(&object),
            c = fn_800822D4(&object);
        fn_8016130C(init.mUnknown5A, a, b, c, 0);
      }
    }
    fn_8008056C(&object);
  }
  fn_801F283C();
  return result;
}
void fn_8003D958() {
  fn_8015F484(lbl_803EA41C, lbl_803EA420, lbl_803EA428, lbl_803EA42C);
}
void fn_8003D988(int value, int *out, int mode) {
  Object_8008044C object;
  Desc_8008044C desc;
  if (!mode) {
    desc.mUnknown4 = 1;
    desc.mUnknown8 = value;
    fn_8008044C(&object, &desc, 0x454D4147);
    for (unsigned int i = 0; i < lbl_803EA436; ++i) {
      fn_800809FC(&object, out[i], 0);
      out[i] = fn_800808F8(&object);
    }
    fn_8008056C(&object);
  } else {
    for (unsigned int i = 0; i < lbl_803EA436; ++i)
      out[i] = 332;
  }
}
int fn_8003DA8C() { return 13; }
int fn_8003DA94(int count, int owner, int mode) {
  fn_801DCF0C(29, 20, 1, fn_8003BA00, fn_8003BA08);
  if (owner) {
    fn_801DD0C8(owner, 29, 0, fn_8003CBFC);
    lbl_803EA410 = fn_801DD268(owner, 29, 0, 0);
    fn_801DD3AC(owner, lbl_803EA410, 2);
  }
  fn_801DCF0C(30, 20, 1, fn_8003BA00, fn_8003BA08);
  if (owner) {
    fn_801DD0C8(owner, 30, 0, fn_8003CC20);
    lbl_803EA414 = fn_801DD268(owner, 30, 0, 0);
    fn_801DD3AC(owner, lbl_803EA414, 7);
  }
  fn_801DCF0C(27, 20, 1, fn_8003BA04, fn_8003BA0C);
  if (owner) {
    fn_801DD0C8(owner, 27, 0, fn_8003CC44);
    lbl_803EA418 = fn_801DD268(owner, 27, 0, 0);
    fn_801DD3AC(owner, lbl_803EA418, 13);
  }
  fn_8004A140(owner, 0, count);
  lbl_803EA436 = (unsigned int)count >> 1;
  lbl_803EA434 = count;
  fn_8003D0C8(mode);
  fn_80136AE4(0, mode);
  fn_8003D12C();
  fn_8003D2E0();
  fn_8004A0E0((int)lbl_803EA41C, (int)lbl_803EA420);
  fn_80048EDC();
  fn_8003D988(0, lbl_802CCDA4, mode);
  fn_8003D988(1, lbl_802CCDA4 + lbl_803EA436, mode);
  fn_80160C10();
  int result = fn_8003D378(owner, mode);
  if (!mode) {
    fn_80160CDC();
    if (fn_800A3420() == 3)
      fn_80049E6C();
  } else
    fn_801613F0();
  if (!fn_80027DF0())
    fn_80161498();
  return result;
}
int fn_8003DCC0(int owner) {
  if (lbl_803EA410) {
    fn_801DD320(owner, lbl_803EA410);
    fn_80228D58(lbl_803EA410);
    fn_80228DD4();
    lbl_803EA410 = 0;
  }
  if (lbl_803EA414) {
    fn_801DD320(owner, lbl_803EA414);
    fn_80228D58(lbl_803EA414);
    fn_80228DD4();
    lbl_803EA414 = 0;
  }
  if (lbl_803EA418) {
    fn_801DD320(owner, lbl_803EA418);
    fn_80228D58(lbl_803EA418);
    fn_80228DD4();
    lbl_803EA418 = 0;
  }
  if (lbl_803EA430) {
    for (int i = 0; i < lbl_803EA434; ++i) {
      if (owner) {
        fn_80047630(lbl_803EA430[i]->mUnknown988);
        fn_801DD320(owner, lbl_803EA430[i]);
      }
      fn_80228D58(lbl_803EA430[i]);
    }
    fn_80228DD4();
    fn_801D2BD0(lbl_803EA430);
    lbl_803EA430 = 0;
  }
  fn_8004A118();
  fn_800AF71C();
  fn_801F010C(gAnimData.fn_80033AF8(), 57);
  fn_801F010C(gAnimData.fn_80033AF8(), 58);
  fn_801F010C(gAnimData.fn_80033AF8(), 59);
  fn_8004A1FC(0);
  fn_801DCF8C(29);
  fn_801DCF8C(30);
  int result = fn_801DCF8C(27);
  lbl_803EA434 = 0;
  fn_80160F98();
  fn_80048F34();
  if (fn_80027DF0() && fn_80160C08())
    fn_80161498();
  return result;
}
void fn_8003DE74(int side, int *values) {
  int *out = lbl_802CCDA4 + (side ? 7 : 0);
  for (int i = 0; i < 7; ++i)
    out[i] = values[i];
}
int fn_8003DEB4() { return lbl_803EA434; }
int fn_8003DEBC() { return 7; }
Object_8003DEC4 *fn_8003DEC4(int index) {
  return lbl_803EA430 ? lbl_803EA430[index] : 0;
}
Object_8003DEC4 *fn_8003DEE4(int value) {
  Object_8003DEC4 *result = 0;
  for (unsigned char i = 0; i < lbl_803EA434; ++i)
    if (lbl_803EA430[i]->mUnknown4956 == value) {
      result = lbl_803EA430[i];
      break;
    }
  return result;
}
Object_8003DEC4 *fn_8003DF3C(int side, int index) {
  return lbl_803EA430 ? fn_8003DEC4(side * 7 + index) : 0;
}
Object_8003DEC4 *fn_8003DF7C(Pair_8017055C *point, float *distance) {
  float value = 10000.0f;
  Object_8003DEC4 *result = 0;
  if (lbl_803EA430)
    for (unsigned int i = 0; i < lbl_803EA434; ++i) {
      float current = fn_8022781C(lbl_803EA430[i]->mUnknown4, point);
      if (!(current >= value)) {
        value = current;
        result = lbl_803EA430[i];
      }
    }
  if (distance)
    *distance = value;
  return result;
}
Skeleton_80041930 *fn_8003E028() { return lbl_803EA41C; }
Skeleton_80041930 *fn_8003E030() { return lbl_803EA428; }
void fn_8003E038(Block_80170E64 *object, int *reference) {
  fn_8009BD48(reference, 0, 0, 0);
  if (object)
    for (unsigned int team = 0; team < 2; ++team)
      for (unsigned int i = 0; i < 7; ++i) {
        Object_80039F5C *player =
            fn_80039F5C((unsigned char)team, (unsigned short)i);
        if (player->mpUnknown4 == object)
          *reference = player->mId;
      }
}
Object_80039F5C *fn_8003E0C8(Block_80170E64 *object) {
  int reference;
  Object_80039F5C *result = 0;
  fn_8003E038(object, &reference);
  if (((unsigned char *)&reference)[3] == 1)
    result = fn_8009BCE8(&reference);
  return result;
}
void fn_8003E118() {
  int size = fn_800429CC(0) + fn_8003DA8C();
  fn_80030ACC(fn_8003CEB0, fn_8003CF88, size * lbl_803EA434, "Players");
}
}
