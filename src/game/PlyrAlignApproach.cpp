/* Selects approach commands and advances lane movement during player alignment. */

#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/AudmonEvent.h"
#include "game/fn_80178D18.h"
#include "game/Vec3Magnitude.h"
#include "game/fn_801BE60C.h"
#include <math.h>

struct PlyrAlignApproachState_t {
  unsigned char unk_0x0, unk_0x1, unk_0x2, unk_0x3;
  Point_8017886C mLaneTargets[2];
  unsigned short mLaneTargetIndex;
  unsigned char unk_0x16[8];
  unsigned short mLanePhase;
  unsigned char unk_0x20[4];
  int unk_0x24;
  unsigned char unk_0x28[16];
  int mLaneApproachHeading;
  unsigned char unk_0x3C[16];
  unsigned char unk_0x4C, unk_0x4D;
};
extern "C" {
extern float lbl_803EAD38, lbl_803EAD3C, lbl_803EAD40, lbl_803EAD44,
    lbl_803EAD48;
Point_8017886C fn_80177FFC(int);
void Vec2Sub(void *, void *, void *);
int fn_801CFE40(float, float);
int MathAngleDiff(int, int);
int fn_800CB708(Object_80039F5C *, int *, Point_8017886C, int, int);
int fn_800CB580(Object_80039F5C *, int *, Point_8017886C, int, int);
int fn_800CBB00(Object_80039F5C *, int, Point_8017886C, int, int);
void PlayerReleaseJointCtrls(Object_80039F5C *);
int PlayerActionIsFacingPoint(Object_80039F5C *, Point_8017886C *, float);
void PlyrAlignStartShuffle(Object_80039F5C *, PlyrAlignApproachState_t *, int, float);
void fn_800C89F0(Object_80039F5C *, int, int, int, float);
int fn_80178320(void);
int fn_80178308(void);
int fn_80124CE4(Object_80039F5C *, int, void *, int, float, int, float);
int PlayerActionIsNearLine(Object_80039F5C *);
void PlayerPathStartSideAnim(Object_80039F5C *, int, int);
int PlayerPathIsLaneClear(Object_80039F5C *, Point_8017886C *);

void PlyrAlignMoveToTarget(Object_80039F5C *player, Point_8017886C *target, int angle) {
  PlyrAlignApproachState_t *state = (PlyrAlignApproachState_t *)&player->mUnknown336;
  Point_8017886C goal;
  Point_8017886C delta;
  goal = fn_80177FFC(player->mIdBytes[2]);
  int value;
  Vec2Sub(&delta, target, &player->mMotion.mPos);
  float distance = Vec2Magnitude(&delta);
  int direction = fn_801CFE40(delta.mY, delta.mX);
  if (!(player->mMotion.mUnknown28 <= 0.006f)) {
    int beyond = target->mY > goal.mY + 2.0f;
    if (!state->unk_0x24) {
      if (fn_800CB708(player, &value, *target, angle, beyond)) {
        fn_800CBB00(player, value, *target, angle, beyond);
        state->unk_0x4C = 1;
        return;
      }
    }
  }
  if ((!(distance <= 0.65f) && !state->unk_0x24) ||
      (!(distance <= lbl_803EAD44) && state->unk_0x24) || state->unk_0x3) {
    PlayerReleaseJointCtrls(player);
    int facing = fn_801CFE40(delta.mY, delta.mX);
    if (PlayerActionIsFacingPoint(player, target, distance)) {
      PlyrAlignStartShuffle(player, state, facing,
                  fabsf(player->mMotion.mPos.mX - target->mX));
      return;
    }
    if (state->unk_0x3)
      return;
    if (state->unk_0x24) {
      float strength = 0.72f;
      if (!(distance > lbl_803EAD3C))
        strength = (distance / lbl_803EAD3C) * strength;
      fn_800C89F0(player, 0xC00000, 2, 0, lbl_803EAD40);
      player->mUnknown512.mUnknown0 = strength;
      player->mUnknown512.mUnknown14 = 1;
      player->mUnknown512.mUnknown8 = facing;
    } else {
      if (!(distance <= 8.0f)) {
        if (!(player->mMotion.mUnknown28 >= 0.006f)) {
          int option = 0;
          if (player->mFlags & 0x40000)
            option = 1;
          if (fn_800CB580(player, &value, *target, direction, option))
            goto selected;
          if (option) {
            if (fn_800CB580(player, &value, *target, direction, 0))
              goto selected;
          }
        }
        player->mUnknown512.mUnknown14 = 1;
        player->mUnknown512.mUnknown0 = 0.72f;
        player->mUnknown512.mUnknown8 = facing;
        goto adjust;
      } else {
        if (!(player->mMotion.mUnknown28 >= 0.006f) &&
            MathAngleDiff(facing, angle) <= 0x11C71B) {
          int option = 0;
          if (player->mFlags & 0x40000)
            option = 1;
          if (!state->unk_0x24) {
            if (fn_800CB580(player, &value, *target, direction, option))
              goto selected;
            if (option) {
              if (fn_800CB580(player, &value, *target, direction, 0))
                goto selected;
            }
          }
        }
        goto rest;
      }
    selected: {
        fn_800CBB00(player, value, *target, direction, 0);
        state->unk_0x4D = 1;
        return;
      }
    rest:
      if (!(distance <= 2.0f)) {
        if (MathAngleDiff(facing, angle) > 0x18E38E) {
          player->mUnknown512.mUnknown14 = 3;
          player->mUnknown512.mUnknown8 = angle;
          player->mUnknown512.mUnknown0 = 0.5f;
        } else {
          player->mUnknown512.mUnknown14 = 3;
          player->mUnknown512.mUnknown8 = angle;
          player->mUnknown512.mUnknown0 = 0.5f;
        }
      } else if (MathAngleDiff(facing, angle) > 0x18E38E) {
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
      if (fn_80124CE4(player, player->mIdBytes[2], &value, 0x155555, 5.0f,
                      facing, 1.0f)) {
        if (MathAngleDiff(facing, 0) <= 0x2AAAA9) {
          player->mUnknown512.mUnknown4 += (int)(lbl_803EAD48 * 46603.379f);
          break;
        }
        if (MathAngleDiff(facing, 0x800000) <= 0x2AAAA9) {
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
    if (!(player->mMotion.mPos.mY >=
          fn_80177FFC(player->mIdBytes[2]).mY + 0.15625f + lbl_803EAD38)) {
      if (current != 86) {
        player->mUnknown512.mUnknown14 = 3;
        player->mUnknown512.mUnknown4 = 0x400000;
        player->mUnknown512.mUnknown8 = angle;
        player->mUnknown512.mUnknown0 = 0.2f;
      }
      return;
    }
    int limit = 0x38E38;
    if (!state->unk_0x24)
      limit = 0xE38E3;
    if (!state->unk_0x3 &&
        MathAngleDiff(player->mMotion.mFacing, angle) > limit) {
      player->mUnknown512.mUnknown8 = angle;
      player->mUnknown512.mUnknown14 = 1;
      player->mUnknown512.mUnknown4 = angle;
      player->mUnknown512.mUnknown0 = 0.0f;
      player->mMotion.mUnknown28 = 0.0f;
      return;
    }
    if (MathAngleDiff(player->mMotion.mFacing, player->mMotion.mUnknown32) >
            0x2E38E3 &&
        MathAngleDiff(player->mMotion.mFacing, 0xC00000) <= 0x18E38D &&
        (current == 74 || current == 160 || current == 73) &&
        !PlayerActionIsNearLine(player)) {
      fn_801BE068(player->mpUnknown792, player->mpUnknown796,
                  player->mpUnknown800, 73, 1.0f, player);
      fn_801BE068(player->mpUnknown792, player->mpUnknown796,
                  player->mpUnknown800, 85, 1.0f, player);
    }
    state->unk_0x1 = 0;
  }
}
void PlyrAlignUpdateLane(Object_80039F5C *player) {
  PlyrAlignApproachState_t *state = (PlyrAlignApproachState_t *)&player->mUnknown336;
  Point_8017886C delta;
  switch (state->mLanePhase) {
  case 0: {
    Vec2Sub(&delta, &state->mLaneTargets[state->mLaneTargetIndex],
                &player->mMotion.mPos);
    Vec2Magnitude(&delta);
    fn_801CFE40(delta.mY, delta.mX);
    state->mLanePhase = 2;
    break;
  }
  case 3: {
    if (fn_801BE648(player->mpUnknown792) != 28) {
      PlayerPathStartSideAnim(player, 1, 1);
      break;
    }
    int change = 0;
    if (player->mFlags & 4) {
      player->mFlags &= ~4u;
      change = 1;
    } else if (PlayerPathIsLaneClear(player, &state->mLaneTargets[state->mLaneTargetIndex]) != 1 ||
               !(player->mMotion.mPos.mY >=
                 state->mLaneTargets[state->mLaneTargetIndex].mY + 0.3f))
      change = 1;
    if (change == 1) {
      PlayerPathStartSideAnim(player, 8, 1);
      state->mLanePhase = 1;
    }
    break;
  }
  case 2: {
    if (PlayerPathIsLaneClear(player, &state->mLaneTargets[state->mLaneTargetIndex]) == 1) {
      Vec2Sub(&delta, &state->mLaneTargets[state->mLaneTargetIndex],
                  &player->mMotion.mPos);
      float distance = Vec2Magnitude(&delta);
      int direction = fn_801CFE40(delta.mY, delta.mX);
      if (!(distance <= 0.3f) && MathAngleDiff(direction, 0xC00000) <= 0x2AAAA9) {
        if (player->mUnknown560.mFlags.mBytes[0] ||
            !(player->mMotion.mPos.mY >=
              fn_80177FFC(player->mIdBytes[2]).mY + 0.15625f +
                  lbl_803EAD38 * 0.5f)) {
          PlayerPathStartSideAnim(player, 1, 2);
          state->mLanePhase = 1;
        } else {
          player->mUnknown512.mUnknown15 = 28;
          player->mUnknown512.mUnknown14 = 1;
          player->mUnknown512.mUnknown8 = direction;
          player->mUnknown512.mUnknown4 = direction;
          player->mUnknown512.mUnknown0 = 0.15f;
        }
      } else {
        Point_8017886C goal = fn_80177FFC(fn_80178308());
        Point_8017886C point = goal;
        Point_8017886C offset;
        point.mY -= 5.0f;
        Vec2Sub(&offset, &point, &player->mMotion.mPos);
        state->mLaneApproachHeading = fn_801CFE40(offset.mY, offset.mX);
        PlayerPathStartSideAnim(player, 1, 2);
        state->mLanePhase = 1;
      }
    } else {
      PlayerPathStartSideAnim(player, 1, 1);
      state->mLanePhase = 1;
    }
    break;
  }
  case 1:
    if (player->mFlags & 4) {
      player->mFlags &= ~4u;
      PlayerPathStartSideAnim(player, 8, 1);
    }
    break;
  }
  switch (state->mLanePhase) {
  case 2:
  case 3:
    AudmonEventPostId(119, &player->mMotion.mPos, player->mId, 0, 0, 0);
    break;
  }
}
}
