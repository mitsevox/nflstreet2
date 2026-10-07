#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/cu_80067C10.h"
#include "game/fn_80178D18.h"
#include "game/fn_802270D4.h"
#include <math.h>

struct State_800E2FE4 {
  unsigned char mUnknown0, mUnknown1, mUnknown2, mUnknown3;
  Point_8017886C mUnknown4[2];
  unsigned short mUnknown14;
  unsigned char mUnknown16[8];
  unsigned short mUnknown1E;
  unsigned char mUnknown20[4];
  int mUnknown24;
  unsigned char mUnknown28[16];
  int mUnknown38;
  unsigned char mUnknown3C[16];
  unsigned char mUnknown4C, mUnknown4D;
};
struct Animation_800E2FE4 {
  void *mUnknown0, *mUnknown4, *mUnknown8;
};
extern "C" {
extern float lbl_803EAD38, lbl_803EAD3C, lbl_803EAD40, lbl_803EAD44,
    lbl_803EAD48;
Point_8017886C fn_80177FFC(int);
void fn_80227690(void *, void *, void *);
int fn_801CFE40(float, float);
int fn_801CFFD0(int, int);
int fn_800CB708(Object_80039F5C *, int *, Point_8017886C *, int, int);
int fn_800CB580(Object_80039F5C *, int *, Point_8017886C *, int, int);
void fn_800CBB00(Object_80039F5C *, int, Point_8017886C *, int, int);
void fn_800E3C30(Object_80039F5C *);
int fn_800E2F20(Object_80039F5C *, Point_8017886C *, float);
void fn_800E4120(Object_80039F5C *, State_800E2FE4 *, int, float);
void fn_800C89F0(Object_80039F5C *, int, int, int, float);
int fn_80178320(void);
int fn_80178308(void);
int fn_80124CE4(Object_80039F5C *, int, void *, int, int, float, float);
int fn_801BE648(void *);
int fn_800E1870(Object_80039F5C *);
int fn_801BE068(void *, void *, void *, unsigned short, void *, float);
void fn_800E3AE8(Object_80039F5C *, int, int);
int fn_800E3A34(Object_80039F5C *, Point_8017886C *);

void fn_800E2FE4(Object_80039F5C *player, Point_8017886C *target, int angle) {
  State_800E2FE4 *state = (State_800E2FE4 *)&player->mUnknown336;
  Point_8017886C goal = fn_80177FFC(player->mIdBytes[2]), delta;
  fn_80227690(&delta, target, &player->mMotion.mPos);
  float distance = fn_802270A4(&delta);
  int direction = fn_801CFE40(delta.mY, delta.mX);
  if (!(player->mMotion.mUnknown28 <= 0.006f)) {
    int beyond = target->mY > goal.mY + 2.0f;
    if (!state->mUnknown24) {
      int value;
      Point_8017886C point = *target;
      if (fn_800CB708(player, &value, &point, angle, beyond)) {
        point = *target;
        fn_800CBB00(player, value, &point, angle, beyond);
        state->mUnknown4C = 1;
        return;
      }
    }
  }
  if ((!(distance <= 0.65f) && !state->mUnknown24) ||
      (!(distance <= lbl_803EAD44) && state->mUnknown24) || state->mUnknown3) {
    fn_800E3C30(player);
    int facing = fn_801CFE40(delta.mY, delta.mX);
    if (fn_800E2F20(player, target, distance)) {
      fn_800E4120(player, state, facing,
                  fabsf(player->mMotion.mPos.mX - target->mX));
      return;
    }
    if (state->mUnknown3)
      return;
    if (state->mUnknown24) {
      float strength = 0.72f;
      if (!(distance > lbl_803EAD3C))
        strength = (distance / lbl_803EAD3C) * strength;
      fn_800C89F0(player, 0xC00000, 2, 0, lbl_803EAD40);
      player->mUnknown512.mUnknown0 = strength;
      player->mUnknown512.mUnknown14 = 1;
      player->mUnknown512.mUnknown8 = facing;
    } else {
      int value;
      bool selected = false;
      if (!(distance <= 8.0f)) {
        if (!(player->mMotion.mUnknown28 >= 0.006f)) {
          int option = (player->mFlags & 0x40000) != 0;
          Point_8017886C point = *target;
          selected =
              fn_800CB580(player, &value, &point, direction, option) != 0;
          if (!selected && option) {
            point = *target;
            selected = fn_800CB580(player, &value, &point, direction, 0) != 0;
          }
        }
        if (!selected) {
          player->mUnknown512.mUnknown14 = 1;
          player->mUnknown512.mUnknown0 = 0.72f;
          player->mUnknown512.mUnknown8 = facing;
          goto adjust;
        }
      } else {
        if (!(player->mMotion.mUnknown28 >= 0.006f) &&
            fn_801CFFD0(facing, angle) <= 0x11C71B) {
          int option = (player->mFlags & 0x40000) != 0;
          if (!state->mUnknown24) {
            Point_8017886C point = *target;
            selected =
                fn_800CB580(player, &value, &point, direction, option) != 0;
            if (!selected && option) {
              point = *target;
              selected = fn_800CB580(player, &value, &point, direction, 0) != 0;
            }
          }
        }
      }
      if (selected) {
        Point_8017886C point = *target;
        fn_800CBB00(player, value, &point, direction, 0);
        state->mUnknown4D = 1;
        return;
      }
      if (!(distance <= 2.0f)) {
        if (fn_801CFFD0(facing, angle) > 0x18E38E) {
          player->mUnknown512.mUnknown14 = 3;
          player->mUnknown512.mUnknown8 = angle;
          player->mUnknown512.mUnknown0 = 0.5f;
        } else {
          player->mUnknown512.mUnknown14 = 3;
          player->mUnknown512.mUnknown8 = angle;
          player->mUnknown512.mUnknown0 = 0.5f;
        }
      } else if (fn_801CFFD0(facing, angle) > 0x18E38E) {
        player->mUnknown512.mUnknown14 = 3;
        player->mUnknown512.mUnknown8 = angle;
        player->mUnknown512.mUnknown0 = 0.4f;
      } else {
        player->mUnknown512.mUnknown14 = 3;
        player->mUnknown512.mUnknown8 = angle;
        player->mUnknown512.mUnknown0 = 0.2f;
      }
    }
  adjust:
    player->mUnknown512.mUnknown4 = facing;
    unsigned int count = fn_80178D18(fn_80178320());
    for (unsigned char i = 0; i < count; ++i) {
      int value;
      if (fn_80124CE4(player, player->mIdBytes[2], &value, 0x155555, facing,
                      5.0f, 1.0f)) {
        if (fn_801CFFD0(facing, 0) <= 0x2AAAA9) {
          player->mUnknown512.mUnknown4 += (int)(lbl_803EAD48 * 46603.379f);
          break;
        }
        if (fn_801CFFD0(facing, 0x800000) <= 0x2AAAA9) {
          player->mUnknown512.mUnknown4 -= (int)(lbl_803EAD48 * 46603.379f);
          break;
        }
      }
    }
    player->mFlags &= ~0x40000u;
    return;
  }
  {
    int current = fn_801BE648(player->mpUnknown792);
    Point_8017886C point = fn_80177FFC(player->mIdBytes[2]);
    if (!(player->mMotion.mPos.mY >= point.mY + 0.15625f + lbl_803EAD38)) {
      if (current != 86) {
        player->mUnknown512.mUnknown14 = 3;
        player->mUnknown512.mUnknown0 = 0.2f;
        player->mUnknown512.mUnknown4 = 0x400000;
        player->mUnknown512.mUnknown8 = angle;
      }
      return;
    }
    int limit = state->mUnknown24 ? 0x38E38 : 0xE38E3;
    if (!state->mUnknown3 &&
        fn_801CFFD0(player->mMotion.mFacing, angle) > limit) {
      player->mUnknown512.mUnknown14 = 1;
      player->mMotion.mUnknown28 = 0.0f;
      player->mUnknown512.mUnknown4 = angle;
      player->mUnknown512.mUnknown8 = angle;
      player->mUnknown512.mUnknown0 = 0.0f;
      return;
    }
    if (fn_801CFFD0(player->mMotion.mFacing, player->mMotion.mUnknown32) >
            0x2E38E3 &&
        fn_801CFFD0(player->mMotion.mFacing, 0xC00000) <= 0x18E38D &&
        (current == 74 || current == 160 || current == 73) &&
        !fn_800E1870(player)) {
      Animation_800E2FE4 *animation =
          (Animation_800E2FE4 *)&player->mpUnknown792;
      fn_801BE068(animation->mUnknown0, animation->mUnknown4,
                  animation->mUnknown8, 73, player, 1.0f);
      fn_801BE068(animation->mUnknown0, animation->mUnknown4,
                  animation->mUnknown8, 85, player, 1.0f);
    }
    state->mUnknown1 = 0;
  }
}
void fn_800E36DC(Object_80039F5C *player) {
  State_800E2FE4 *state = (State_800E2FE4 *)&player->mUnknown336;
  switch (state->mUnknown1E) {
  case 0: {
    Point_8017886C delta;
    fn_80227690(&delta, &state->mUnknown4[state->mUnknown14],
                &player->mMotion.mPos);
    fn_802270A4(&delta);
    fn_801CFE40(delta.mY, delta.mX);
    state->mUnknown1E = 2;
    break;
  }
  case 3: {
    if (fn_801BE648(player->mpUnknown792) != 28) {
      fn_800E3AE8(player, 1, 1);
      break;
    }
    int change = 0;
    if (player->mFlags & 4) {
      player->mFlags &= ~4u;
      change = 1;
    } else if (fn_800E3A34(player, &state->mUnknown4[state->mUnknown14]) != 1 ||
               !(player->mMotion.mPos.mY >=
                 state->mUnknown4[state->mUnknown14].mY + 0.3f))
      change = 1;
    if (change == 1) {
      fn_800E3AE8(player, 8, 1);
      state->mUnknown1E = 1;
    }
    break;
  }
  case 2: {
    if (fn_800E3A34(player, &state->mUnknown4[state->mUnknown14]) == 1) {
      Point_8017886C delta;
      fn_80227690(&delta, &state->mUnknown4[state->mUnknown14],
                  &player->mMotion.mPos);
      float distance = fn_802270A4(&delta);
      int direction = fn_801CFE40(delta.mY, delta.mX);
      if (!(distance <= 0.3f) && fn_801CFFD0(direction, 0xC00000) <= 0x2AAAA9) {
        if (player->mUnknown560.mFlags.mBytes[0] ||
            !(player->mMotion.mPos.mY >=
              lbl_803EAD38 * 0.5f +
                  (fn_80177FFC(player->mIdBytes[2]).mY + 0.15625f))) {
          fn_800E3AE8(player, 1, 2);
          state->mUnknown1E = 1;
        } else {
          player->mUnknown512.mUnknown15 = 28;
          player->mUnknown512.mUnknown14 = 1;
          player->mUnknown512.mUnknown4 = direction;
          player->mUnknown512.mUnknown0 = 0.15f;
          player->mUnknown512.mUnknown8 = direction;
        }
      } else {
        Point_8017886C point = fn_80177FFC(fn_80178308()), delta;
        point.mY -= 5.0f;
        fn_80227690(&delta, &point, &player->mMotion.mPos);
        state->mUnknown38 = fn_801CFE40(delta.mY, delta.mX);
        fn_800E3AE8(player, 1, 2);
        state->mUnknown1E = 1;
      }
    } else {
      fn_800E3AE8(player, 1, 1);
      state->mUnknown1E = 1;
    }
    break;
  }
  case 1:
    if (player->mFlags & 4) {
      player->mFlags &= ~4u;
      fn_800E3AE8(player, 8, 1);
    }
    break;
  }
  if (state->mUnknown1E >= 2 && state->mUnknown1E <= 3)
    fn_80067E3C(119, &player->mMotion.mPos, player->mId, 0, 0, 0);
}
}
