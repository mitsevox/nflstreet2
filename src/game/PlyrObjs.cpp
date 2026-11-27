/* Player objects: creates the on-field player objects from the player and
   gear tables and loads their skeletons and bone tables, keeps the player
   list and its counts, writes and reads the list in the save-state bit
   stream, finds players by index, side or distance, and projects each
   player's drop shadow onto the level ground every frame. */
#include "game/Vec2Distance.h"
#include "game/FaceFeatures.h"
#include "game/PlayerObjInit.h"
#include "game/PlyrNameTag.h"
#include "game/GameModules.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8003DEC4.h"
#include "game/Object_8008044C.h"
#include "game/Point2.h"
#include "game/bitstream.h"
#include "game/PlayerLook.h"
#include "game/Vec3Magnitude.h"
#include "game/Vec2Add.h"
#include <math.h>
struct Region_8003BDF0 {
  unsigned char mUnknown0[128];
  unsigned int mUnknown128;
  unsigned char (*mUnknown132)[48];
};
static void *_PlyrObjs_pHandleA = 0;
static void *_PlyrObjs_pHandleB = 0;
static void *_PlyrObjs_pHandleC = 0;
static AnimSkeleton_t *_PlyrObjs_pBodySkel = 0;
static AnimSkeleton_t *_PlyrObjs_apMirrorSkels[2] = {0, 0};
static AnimSkeleton_t *_PlyrObjs_pSkel19 = 0;
static AnimSkeleton_t *_PlyrObjs_pSkel5 = 0;
static Object_8003DEC4 **_PlyrObjs_ppPlayers = 0;
static unsigned short _PlyrObjs_uNumPlayers = 0;
static unsigned short _PlyrObjs_uTeamSize = 0;
static unsigned char _PlyrObjs_bShadowPhase = 1;

static int _PlyrObjs_aiBone21Offset[3] = {0, 0, 0};
static int _PlyrObjs_aiBone15Offset[3] = {0, 0, 0};
static int _PlyrObjs_aiDefaultPlayerIds[14] = {4, 1, 7, 6, 3, 0, 5, 10, 15, 17, 11, 13, 12, 16};

extern "C" {
extern void *lbl_803EAB3C, *lbl_803EA9FC, *lbl_803EAAE0;
unsigned char PlayerObjIsDrawReady();
void PlyrPoseGetBoneTransform(Object_8003DEC4 *, int, float *, int *);
void Vec3Add(void *, void *, void *);
void Vec2Sub(void *, void *, void *);
void Vec3Scale(void *, void *, float);
void Vec2Scale(void *, void *, float);
void Vec3Mat34Mul(void *, void *);
void Vec3Normalize(void *, void *);
void Vec3Mat33Mul(void *, void *);
float Vec2DotProduct(void *, void *);
int Vec3GetAngle(void *, void *);
void MathSinCos(int, float *, float *);
float MathTan(int);
Region_8003BDF0 *LevelGetData();
int LevelFindArea(float *);
void LevelGetQuadBase(void *, void *, void *);
float LevelGetQuadHeight(void *);
void PlyrObjsClipShadowToLevel(Object_8003DEC4 *, Point2_t *, int);
void PlyrObjsClipShadowQuad(Object_8003DEC4 *, float *, Point2_t *, Point2_t *,
                 Point2_t *, int, float);
int PlyrObjsIntersectLines(Point2_t *, Point2_t *, Point2_t *,
                Point2_t *, float *, float *);
void PlyrObjsShadowGetUV(void *, Point2_t *, float *);
void Vec2ScaleAcc(void *, void *, float);
void Vec2Lerp(void *, void *, void *, float);
void Vec3Lerp(void *, void *, void *, float);

void MatPush();
void MatLoad();
void MatPop();
void LLLightGetProjectorMatrix(int);
unsigned int LLLightGetProjectorColor(int);
void PlyrRenderDrawShadows();
void PlyrRenderDrawClippedShadows();
void PlyrRenderDrawTrails();
void PlyrPoseWriteState(Object_8003DEC4 *, BitStream_t *);
void PlyrPoseReadState(Object_8003DEC4 *, BitStream_t *, BitStream_t *, BitStream_t *,
                 BitStream_t *, float);
void fn_80190F18(BitStream_t *, int);
void PlyrAnimInstallFrontEndHandlers();
void PlyrAnimInstallGameHandlers();
void fn_801BE030(int, void **);
void PlyrOverlayAnimRegisterCallbacks();
void PlyrOverlayAnimLoad();
void PlyrHandInitCallbacks();
void PlyrHandLoadFrames();
AnimSkeleton_t *ResLoad(void *, int, int);
void CharRelocateSkeleton(AnimSkeleton_t *);
void CharSkelMirrorRest(AnimSkeleton_t *, AnimSkeleton_t *);
void PlyrIKInit(void *, int, int, int);
void PlyrIKCreateChain(int, AnimSkeleton_t *, const char *, const char *, int);
void fn_8015F484(AnimSkeleton_t *, AnimSkeleton_t **, AnimSkeleton_t *,
                 AnimSkeleton_t *);
int PlayerDbSeekOriginalId(Object_8008044C *, int, int *);
int PlayerDbGetId(Object_8008044C *);
void PlyrObjsShadowAdd();
void PlyrObjsTrailAdd();
void PlyrObjsShadowDelete();
void PlyrObjsTrailDelete();
void ObjNewType_(int, int, int, void (*)(), void (*)());
void ObjSetListObjFunc(int, int, int, int (*)(void));
void *ObjNewInList(int, int, int, void *);
void *ObjNew(int, int, void *);
void ObjSetPriority(int, void *, int);
void ObjRemoveFromList(int, void *);
int PlyrObjsDrawShadowQuads();
int PlyrObjsDrawShadowClips();
int PlyrObjsDrawTrails();
void PlayerObjAddObjType(int, int, int);
void PlyrRenderSetHideFlagged(int);
int fn_8015E440(int, int);
void fn_80234A14(void *, int);
void PlyrRenderNewFrame();
void PlyrObjsInitStateTables(int);
void PlyrStatesRegister(int, int);
void PlyrObjsLoadSkeletons();
void PlyrObjsInitLimbChains();
void PlayerObjRenderInit(int, int);
void PlayerLookOpen();
void PlyrObjsResolveTeamIds(int, int *, int);
void PlaTexCacheStart();
int PlyrObjsCreatePlayers(int, int);
void ResTrackPause();
void ResTrackResume();
int SysGetLastError();
void *fn_801D2B7C(int, int, int);
void fn_8015EE74();
void fn_8015EF10();
int PlayerDbGetNameKey(Object_8008044C *, char *, int);
int fn_8015F5BC(const char *);
void fn_8015F068(int, PlayerHeadIds_t *);
void fn_8015F124(int, int);
void fn_8015F1D4(int, int);
void fn_8015F298(int, int);
void PlayerDbGetNickname(Object_8008044C *, char *, int);
void PlayerLookLoadBonuses(unsigned char, unsigned char, int);
int PlayerDbGetPlex(Object_8008044C *);
int fn_80081E3C(Object_8008044C *);
int PlayerDbGetFaceId(Object_8008044C *);
int PlayerDbGetEyebrows(Object_8008044C *);
PlyrNameTag_t *PlyrNameTagNew(int);
void PlyrNameTagSetText(PlyrNameTag_t *, const char *);
void PlaTexCacheSetFace(int, const char *, int);
void PlaTexCacheSetCapFace(int, int, int, int, int);
void PlyrObjsSetHeadSkeletons();

void PlaTexCacheLoadAllNow();
int StadiumGetSkyState();
void PlayerLookHideSwitch28();
void PlaTexCacheDiscardRequests();
int FELoopIsMainFEActive();
void PlaTexCacheCloseArchive();
void VptTrashObject(void *);
void VptFlushObjectTrash();
void PlyrNameTagDelete(PlyrNameTag_t *);
void fn_801D2BD0(void *);
void PlayerObjRenderShutdown();
void PlyrIKShutdown();
void ResUnLoad(void *, int);
void PlayerObjRemoveObjType(int);
int ObjDelType(int);
void PlaTexCacheStop();
void PlayerLookClose();
int PlaTexCacheGetArchive();
void PlyrRefSet(int *, int, int, int);
int PlyrPoseGetStreamBits(int);
void ReplayRegisterChannel(void (*)(BitStream_t *),
                 void (*)(BitStream_t *, BitStream_t *, BitStream_t *,
                          BitStream_t *, float),
                 int, const char *);
void PlyrObjsShadowAdd() {}
void PlyrObjsTrailAdd() {}
void PlyrObjsShadowDelete() {}
void PlyrObjsTrailDelete() {}
void PlyrObjsBuildShadow(Object_8003DEC4 *object, float *color, Point2_t *axis,
                 int angle) {
  if (PlayerObjIsDrawReady() && (object->mUnknown20 & 1) &&
      !(object->mUnknown20 & 2))
    object->mUnknown4256.mUnknown673 = 1;
  else
    object->mUnknown4256.mUnknown673 = 0;
  float first[4], center[4], delta[4];
  Point2_t direction;
  PlyrPoseGetBoneTransform(object, 4, first, 0);
  PlyrPoseGetBoneTransform(object, 8, center, 0);
  Vec3Add(center, center, first);
  Vec3Scale(center, center, 0.5f);
  PlyrPoseGetBoneTransform(object, 26, first, 0);
  Vec3Sub(delta, first, center);
  Vec3Mat34Mul(center, center);
  Vec3Mat34Mul(delta, delta);
  delta[2] = 0.0f;
  MathSinCos(object->mUnknown36, &direction.mY, &direction.mX);
  float width = fabsf(Vec2DotProduct(&direction, axis));
  if (!(width >= 0.65f))
    width = 0.65f;
  float length = Vec3Magnitude(delta);
  Point2_t forward, backward;
  if (!(length >= 0.4f)) {
    if (!(length <= 0.2f)) {
      Vec3Scale(delta, delta, 1.0f / length);
      float t = (length - 0.2f) * 5.0f;
      float f = width + t * -width + t * 0.4f;
      float b = width + t * (0.85f - width);
      forward.mX = delta[0] * f;
      forward.mY = delta[1] * f;
      backward.mX = -delta[0] * b;
      backward.mY = -delta[1] * b;
    } else {
      delta[0] += axis->mX * (0.2f - length);
      delta[1] += axis->mY * (0.2f - length);
      Vec3Normalize(delta, delta);
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
    Vec3Scale(delta, delta, 1.0f / length);
    backward.mX = -(delta[0] * 0.85f);
    backward.mY = -(delta[1] * 0.85f);
  }
  // FAKEMATCH: reused local; the side vector reuses direction instead of a local of its own
  direction.mX = delta[1];
  direction.mY = -delta[0];
  Vec2Scale(&direction, &direction, width);
  object->mUnknown4256.mColor[0] = color[0];
  object->mUnknown4256.mColor[1] = color[1];
  object->mUnknown4256.mColor[2] = color[2];
  object->mUnknown4256.mColor[3] = color[3];
  object->mUnknown4256.mPoints[0][0] = center[0] - direction.mX + forward.mX;
  object->mUnknown4256.mPoints[0][1] = center[1] - direction.mY + forward.mY;
  object->mUnknown4256.mPoints[1][0] = center[0] + direction.mX + forward.mX;
  object->mUnknown4256.mPoints[1][1] = center[1] + direction.mY + forward.mY;
  object->mUnknown4256.mPoints[2][0] = center[0] + direction.mX + backward.mX;
  object->mUnknown4256.mPoints[2][1] = center[1] + direction.mY + backward.mY;
  object->mUnknown4256.mPoints[3][0] = center[0] - direction.mX + backward.mX;
  object->mUnknown4256.mPoints[3][1] = center[1] - direction.mY + backward.mY;
  if (LevelGetData()) {
    unsigned int value =
        object->mUnknown4968 * _PlyrObjs_uTeamSize + object->mUnknown4969;
    int enabled = (value & 1) ? _PlyrObjs_bShadowPhase : !_PlyrObjs_bShadowPhase;
    if (enabled) {
      object->mUnknown4256.mUnknown672 = 0;
      PlyrObjsClipShadowToLevel(object, axis, angle);
    }
  }
}
void PlyrObjsClipShadowToLevel(Object_8003DEC4 *object, Point2_t *axis, int angle) {
  Region_8003BDF0 *regions = LevelGetData();
  if (!regions)
    return;
  float first[4], center[4];
  PlyrPoseGetBoneTransform(object, 4, first, 0);
  PlyrPoseGetBoneTransform(object, 8, center, 0);
  Vec3Add(center, center, first);
  Vec3Scale(center, center, 0.5f);
  PlyrPoseGetBoneTransform(object, 26, first, 0);
  first[2] = (first[2] + center[2]) * 0.5f;
  float radius = fabsf(1.0f / MathTan(angle)) * first[2];
  Projection_8003BA10 *p = &object->mUnknown4256;
  radius += Vec2Distance(p->mPoints[0], p->mPoints[2]);
  for (unsigned char i = 0; i < regions->mUnknown128; ++i) {
    Point2_t a, b, mid;
    LevelGetQuadBase(regions->mUnknown132[i], &a, &b);
    float scale = LevelGetQuadHeight(regions->mUnknown132[i]);
    mid.mX = (a.mX + b.mX) * 0.5f;
    mid.mY = (a.mY + b.mY) * 0.5f;
    float extent = Vec2Distance(&mid, &a);
    if (!(Vec2Distance(&mid, center) >= radius + extent))
      PlyrObjsClipShadowQuad(object, center, axis, &a, &b, angle, scale);
  }
}
void PlyrObjsClipShadowQuad(Object_8003DEC4 *object, float *center, Point2_t *axis,
                 Point2_t *a, Point2_t *b, int angle, float scale) {
  float position[3];
  float points[3][3];
  Point2_t pairs[3];
  float parameters[3];
  Point2_t original, shifted;
  float t, u;
  Point2_t shiftedA, shiftedB;
  Point2_t startA, endA, startB, endB;
  if (object->mUnknown4256.mUnknown672 > 3)
    return;
  position[0] = center[0];
  position[1] = center[1];
  position[2] = center[2];
  original.mX = position[0];
  original.mY = position[1];
  Vec2Sub(&shifted, &original, axis);
  if (PlyrObjsIntersectLines(&original, &shifted, a, b, &t, &u) && t > 0.0f)
    return;
  unsigned char i = 0;
  float height = MathTan(angle);
  Projection_8003BA10 *p = &object->mUnknown4256;
  scale *= 0.7142857313156128f;
  float shift = scale / height;
  int accepted = 0;
  Clip_8003BFCC *out = &p->mRecords[p->mUnknown672];
  out->mCount = 0;
  shiftedA.mX = a->mX;
  shiftedA.mY = a->mY;
  shiftedB.mX = b->mX;
  shiftedB.mY = b->mY;
  Vec2ScaleAcc(&shiftedA, axis, shift);
  Vec2ScaleAcc(&shiftedB, axis, shift);
  float minimum = 1000000.0f, maximum = -1000000.0f;
  for (; i < 4; ++i) {
    if (PlyrObjsIntersectLines(&shiftedA, &shiftedB, (Point2_t *)p->mPoints[i],
                    (Point2_t *)p->mPoints[(i + 1) % 4], &t, &u) &&
        !(u <= 0.0f) && !(u >= 1.0f)) {
      if (!(t >= minimum))
        minimum = t;
      if (!(t <= maximum))
        maximum = t;
    }
  }
  startA.mX = a->mX;
  startA.mY = a->mY;
  endA.mX = shiftedA.mX;
  endA.mY = shiftedA.mY;
  startB.mX = b->mX;
  startB.mY = b->mY;
  endB.mX = shiftedB.mX;
  endB.mY = shiftedB.mY;
  for (i = 0; i < 4; ++i) {
    original.mX = p->mPoints[i][0];
    original.mY = p->mPoints[i][1];
    shifted.mX = p->mPoints[i][0];
    shifted.mY = p->mPoints[i][1];
    Vec2ScaleAcc(&shifted, axis, -scale / height);
    unsigned char count = 0;
    if (PlyrObjsIntersectLines(&original, &shifted, a, b, &t, &u) && !(t >= 1.0f) &&
        !(u <= 0.0f) && !(u >= 1.0f)) {
      if (!(t <= 0.0f))
        accepted = 1;
      out->mPoints[out->mCount][0] = p->mPoints[i][0];
      out->mPoints[out->mCount][1] = p->mPoints[i][1];
      out->mPoints[out->mCount][2] = p->mPoints[i][2];
      out->mPairs[out->mCount].mX = p->mPairs[i].mX;
      out->mPairs[out->mCount].mY = p->mPairs[i].mY;
      ++out->mCount;
    }
    if (PlyrObjsIntersectLines((Point2_t *)p->mPoints[i],
                    (Point2_t *)p->mPoints[(i + 1) % 4], &shiftedA, &shiftedB,
                    &t, &u) &&
        !(t <= 0.0f) && !(t >= 1.0f) && !(u <= 0.0f) && !(u >= 1.0f)) {
      accepted = 1;
      Vec3Lerp(points[count], p->mPoints[(i + 1) % 4], p->mPoints[i], t);
      Vec2Lerp(&pairs[count], &p->mPairs[(i + 1) % 4], &p->mPairs[i], t);
      parameters[count] = t;
      count = 1;
    }
    if (PlyrObjsIntersectLines((Point2_t *)p->mPoints[i],
                    (Point2_t *)p->mPoints[(i + 1) % 4], &startA, &endA,
                    &t, &u) &&
        !(t <= 0.0f) && !(t >= 1.0f)) {
      if (!(u <= 0.0f))
        accepted = 1;
      if (u < 1.0f) {
        Vec3Lerp(points[count], p->mPoints[(i + 1) % 4], p->mPoints[i], t);
        Vec2Lerp(&pairs[count], &p->mPairs[(i + 1) % 4], &p->mPairs[i], t);
        parameters[count] = t;
        ++count;
      } else if (!(minimum > 0.0f)) {
        points[count][0] = shiftedA.mX;
        points[count][1] = shiftedA.mY;
        PlyrObjsShadowGetUV(p, &shiftedA, (float *)&pairs[count]);
        parameters[count] = t;
        ++count;
      }
    }
    if (PlyrObjsIntersectLines((Point2_t *)p->mPoints[i],
                    (Point2_t *)p->mPoints[(i + 1) % 4], &startB, &endB,
                    &t, &u) &&
        !(t <= 0.0f) && !(t >= 1.0f)) {
      if (!(u <= 0.0f))
        accepted = 1;
      if (u < 1.0f) {
        Vec3Lerp(points[count], p->mPoints[(i + 1) % 4], p->mPoints[i], t);
        Vec2Lerp(&pairs[count], &p->mPairs[(i + 1) % 4], &p->mPairs[i], t);
        parameters[count] = t;
        ++count;
      } else if (!(maximum < 1.0f)) {
        points[count][0] = shiftedB.mX;
        points[count][1] = shiftedB.mY;
        PlyrObjsShadowGetUV(p, &shiftedB, (float *)&pairs[count]);
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
      out->mPoints[out->mCount][0] = points[index][0];
      out->mPoints[out->mCount][1] = points[index][1];
      out->mPoints[out->mCount][2] = points[index][2];
      out->mPairs[out->mCount].mX = pairs[index].mX;
      out->mPairs[out->mCount].mY = pairs[index].mY;
      parameters[index] = 1000000.0f;
      ++out->mCount;
    }
  }
  if (!accepted)
    return;
  for (i = 0; i < out->mCount; ++i) {
    original.mX = out->mPoints[i][0];
    original.mY = out->mPoints[i][1];
    Vec2Sub(&shifted, out->mPoints[i], axis);
    if (PlyrObjsIntersectLines(&original, &shifted, a, b, &t, &u)) {
      Vec2Lerp(out->mPoints[i], &shifted, &original, t);
      out->mPoints[i][2] = t * height * 1.4f;
    }
  }
  ++p->mUnknown672;
}
void PlyrObjsShadowGetUV(void *record, Point2_t *offset, float *parameters) {
  struct View {
    unsigned char pad[16];
    float points[4][3];
  };
  View *p = (View *)record;
  Point2_t line;
  Vec2Sub(&line, p->points[0], p->points[3]);
  Vec2Add(&line, offset, &line);
  PlyrObjsIntersectLines((Point2_t *)p->points[0], (Point2_t *)p->points[1],
              offset, &line, parameters, 0);
  Vec2Sub(&line, p->points[1], p->points[0]);
  Vec2Add(&line, offset, &line);
  PlyrObjsIntersectLines((Point2_t *)p->points[1], (Point2_t *)p->points[2],
              offset, &line, parameters + 1, 0);
}
int PlyrObjsIntersectLines(Point2_t *a, Point2_t *b, Point2_t *c,
                Point2_t *d, float *t, float *u) {
  float ax = a->mX, ay = a->mY, cx0 = c->mX, cy0 = c->mY;
  float dy = b->mY - ay, cx = d->mX - cx0;
  float cy = d->mY - cy0, dx = b->mX - ax;
  float determinant = cy * dx - cx * dy;
  if (!(fabsf(determinant) >= 0.0000001f))
    return 0;
  if (t)
    *t = ((cx0 - ax) * cy + (ay - cy0) * cx) / determinant;
  if (u)
    *u = ((ax - cx0) * dy + (cy0 - ay) * dx) / -determinant;
  return 1;
}
int PlyrObjsUpdateShadows() {
  MatPush();
  LLLightGetProjectorMatrix(0);
  MatLoad();
  unsigned int value = LLLightGetProjectorColor(0);
  float color[4];
  color[0] = (float)(value & 255) * 0.0078125f;
  color[1] = (float)((value >> 8) & 255) * 0.0078125f;
  color[2] = (float)((value >> 16) & 255) * 0.0078125f;
  color[3] = (float)(value >> 24) * 0.0078125f;
  float vector[4];
  vector[0] = 0.0f;
  vector[1] = 0.0f;
  vector[2] = 1.0f;
  Vec3Mat33Mul(vector, vector);
  vector[2] = 0.0f;
  float length = Vec3Magnitude(vector);
  if (!(length >= 0.0001f)) {
    vector[0] = 0.0f;
    vector[1] = 1.0f;
    length = 1.0f;
  }
  float angleVector[3];
  angleVector[0] = vector[0];
  angleVector[1] = vector[1];
  angleVector[2] = 1.0f;
  int angle = Vec3GetAngle(angleVector, vector);
  Vec3Scale(vector, vector, 1.0f / length);
  for (int i = 0; i < _PlyrObjs_uNumPlayers; ++i)
    PlyrObjsBuildShadow(_PlyrObjs_ppPlayers[i], color, (Point2_t *)vector, angle);
  MatPop();
  _PlyrObjs_bShadowPhase = !_PlyrObjs_bShadowPhase;
  return 0;
}
int PlyrObjsDrawShadowQuads() {
  PlyrRenderDrawShadows();
  return 0;
}
int PlyrObjsDrawShadowClips() {
  PlyrRenderDrawClippedShadows();
  return 0;
}
int PlyrObjsDrawTrails() {
  PlyrRenderDrawTrails();
  return 0;
}
void PlyrObjsInitBodySkelPose(AnimSkeleton_t *skeleton) {
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

void PlyrObjsInitSkel19Pose(AnimSkeleton_t *skeleton) {
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

void PlyrObjsInitSkel5Pose(AnimSkeleton_t *skeleton) {
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

void PlyrObjsWriteState(BitStream_t *stream) {
  for (unsigned int i = 0; i < _PlyrObjs_uNumPlayers; ++i) {
    Object_8003DEC4 *object = _PlyrObjs_ppPlayers[i];
    PlyrPoseWriteState(object, stream);
    fn_80191068(stream, object->mUnknown5188.mUnknown568, 1);
    fn_80191068(stream, (unsigned long long)object->mUnknown5188.mUnknown56C,
                4);
    fn_80191068(stream, (unsigned long long)object->mUnknown5188.mUnknown570,
                4);
    fn_80191068(stream, (unsigned long long)object->mUnknown5188.mUnknown574,
                4);
  }
}
void PlyrObjsReadState(BitStream_t *a, BitStream_t *b, BitStream_t *c, BitStream_t *d,
                 float t) {
  for (unsigned int i = 0; i < _PlyrObjs_uNumPlayers; ++i) {
    Object_8003DEC4 *object = _PlyrObjs_ppPlayers[i];
    PlyrPoseReadState(object, a, b, c, d, t);
    object->mUnknown972 = LevelFindArea(object->mUnknown4);
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
void PlyrObjsInitStateTables(int mode) {
  if (mode)
    PlyrAnimInstallFrontEndHandlers();
  else
    PlyrAnimInstallGameHandlers();
  fn_801BE030(1, &lbl_803EAB3C);
  PlyrOverlayAnimRegisterCallbacks();
  fn_801BE030(3, &lbl_803EA9FC);
  PlyrOverlayAnimLoad();
  PlyrHandInitCallbacks();
  fn_801BE030(4, &lbl_803EAAE0);
  PlyrHandLoadFrames();
}
static inline void ZeroRoot(AnimSkeleton_t *skeleton) {
  float *root = (float *)((char *)skeleton + 16);
  root[0] = root[1] = root[2] = 0.0f;
}
void PlyrObjsLoadSkeletons() {
  // FAKEMATCH: local that only aliases the global gAnimData
  AnimData *anim = &gAnimData;
  _PlyrObjs_pBodySkel = ResLoad(anim->GetArchive(), 57, 1);
  CharRelocateSkeleton(_PlyrObjs_pBodySkel);
  PlyrObjsInitBodySkelPose(_PlyrObjs_pBodySkel);
  _PlyrObjs_aiBone15Offset[0] = (short)_PlyrObjs_pBodySkel->mUnknown1040[15][0] * 16;
  _PlyrObjs_aiBone15Offset[1] = (short)_PlyrObjs_pBodySkel->mUnknown1040[15][1] * 16;
  _PlyrObjs_aiBone15Offset[2] = (short)_PlyrObjs_pBodySkel->mUnknown1040[15][2] * 16;
  _PlyrObjs_aiBone21Offset[0] = (short)_PlyrObjs_pBodySkel->mUnknown1040[21][0] * 16;
  _PlyrObjs_aiBone21Offset[1] = (short)_PlyrObjs_pBodySkel->mUnknown1040[21][1] * 16;
  _PlyrObjs_aiBone21Offset[2] = (short)_PlyrObjs_pBodySkel->mUnknown1040[21][2] * 16;
  _PlyrObjs_apMirrorSkels[0] = ResLoad(anim->GetArchive(), 58, 1);
  CharRelocateSkeleton(_PlyrObjs_apMirrorSkels[0]);
  ZeroRoot(_PlyrObjs_apMirrorSkels[0]);
  _PlyrObjs_apMirrorSkels[1] = ResLoad(anim->GetArchive(), 59, 1);
  CharRelocateSkeleton(_PlyrObjs_apMirrorSkels[1]);
  ZeroRoot(_PlyrObjs_apMirrorSkels[1]);
  CharSkelMirrorRest(_PlyrObjs_apMirrorSkels[0], _PlyrObjs_apMirrorSkels[1]);
  _PlyrObjs_pSkel19 = ResLoad(anim->GetArchive(), 61, 1);
  CharRelocateSkeleton(_PlyrObjs_pSkel19);
  PlyrObjsInitSkel19Pose(_PlyrObjs_pSkel19);
  ZeroRoot(_PlyrObjs_pSkel19);
  _PlyrObjs_pSkel5 = ResLoad(anim->GetArchive(), 62, 1);
  CharRelocateSkeleton(_PlyrObjs_pSkel5);
  PlyrObjsInitSkel5Pose(_PlyrObjs_pSkel5);
  ZeroRoot(_PlyrObjs_pSkel5);
}
void PlyrObjsInitLimbChains() {
  PlyrIKInit(gAnimData.GetArchive(), 60, 1, 32);
  PlyrIKCreateChain(0, _PlyrObjs_pBodySkel, "low_torso", "neckhi", 0);
  PlyrIKCreateChain(1, _PlyrObjs_pBodySkel, "lshoulder", "lwrist", 1);
  PlyrIKCreateChain(2, _PlyrObjs_pBodySkel, "rshoulder", "rwrist", 1);
}
int PlyrObjsCreatePlayers(int owner, int mode) {
  // FAKEMATCH: dead initializer; result is set from SysGetLastError before any read
  int result = 0;
  Object_8008044C object;
  ResTrackPause();
  _PlyrObjs_ppPlayers = (Object_8003DEC4 **)fn_801D2B7C(_PlyrObjs_uNumPlayers * 4, 0, 0);
  result = SysGetLastError();
  if (_PlyrObjs_ppPlayers) {
    PlayerCursorOpen(&object, 0, mode ? 0x54415453 : 0x454D4147);
    PlyrObjsSetHeadSkeletons();
    unsigned int order[14], keys[14];
    Creation_8003D378 init;
    init.mInit.mUnknown00 = 0;
    init.mInit.mUnknown02 = 1;
    init.mInit.mUnknown04 = (int)_PlyrObjs_pBodySkel;
    ((AnimSkeleton_t **)init.mInit.mUnknown08)[0] = _PlyrObjs_apMirrorSkels[0];
    ((AnimSkeleton_t **)init.mInit.mUnknown08)[1] = _PlyrObjs_apMirrorSkels[1];
    init.mInit.mUnknown10 = (int)_PlyrObjs_pSkel19;
    init.mInit.mUnknown14 = (int)_PlyrObjs_pSkel5;
    fn_8015EE74();
    unsigned int i, j;
    for (i = 0; i < _PlyrObjs_uNumPlayers; ++i) {
      unsigned char team;
      if (mode)
        team = 27;
      else
        team = i / _PlyrObjs_uTeamSize;
      PlayerDbSeekId(&object, _PlyrObjs_aiDefaultPlayerIds[i], 0);
      char name[28];
      int hasName = PlayerDbGetNameKey(&object, name, 27);
      PlayerLookLoadForPlayer(i, i, team, _PlyrObjs_aiDefaultPlayerIds[i]);
      order[i] = i;
      int a = PlayerLookGetHatModel(i), b = PlayerLookGetSlot1Model(i);
      PlayerHeadIds_t ids;
      if (hasName) {
        PlayerLookGetHeadIds(i, name, &ids);
        keys[i] = fn_8015F5BC(name);
      } else {
        PlayerLookGetHeadIds(i, 0, &ids);
        keys[i] = 65535;
      }
      int c = PlayerLookGetAccessoryModel(i);
      fn_8015F068(i, &ids);
      fn_8015F124(i, a);
      fn_8015F1D4(i, b);
      fn_8015F298(i, c);
    }
    fn_8015EF10();
    for (i = 0; i < _PlyrObjs_uNumPlayers; ++i)
      for (j = i + 1; j < _PlyrObjs_uNumPlayers; ++j) {
        if (keys[i] > keys[j]) {
          unsigned int key = keys[i];
          keys[i] = keys[j];
          keys[j] = key;
          unsigned int index = order[i];
          order[i] = order[j];
          order[j] = index;
        }
      }
    for (j = 0; j < _PlyrObjs_uNumPlayers; ++j) {
      i = order[j];
      if (mode)
        init.mUnknown57 = 27;
      else
        init.mUnknown57 = i / _PlyrObjs_uTeamSize;
      init.mUnknown58 = i % _PlyrObjs_uTeamSize;
      init.mUnknown59 = i;
      init.mUnknown5A = i;
      init.mInit.mUnknown18 = _PlyrObjs_aiDefaultPlayerIds[i];
      PlayerDbSeekId(&object, init.mInit.mUnknown18, 0);
      PlayerDbGetNickname(&object, init.mUnknown38, 31);
      if (!mode)
        PlayerLookLoadBonuses(init.mUnknown5A, init.mUnknown57, init.mInit.mUnknown18);
      char name[28];
      int hasName = PlayerDbGetNameKey(&object, name, 27);
      int value = PlayerDbGetPybt(&object);
      int key;
      PlayerHeadIds_t ids;
      if (hasName) {
        key = fn_8015F5BC(name);
        if (key == 65535)
          PlayerLookGetHeadIds(init.mUnknown5A, 0, &ids);
        else
          PlayerLookGetHeadIds(init.mUnknown5A, name, &ids);
      } else {
        PlayerLookGetHeadIds(init.mUnknown5A, 0, &ids);
        key = 65535;
      }
      // FAKEMATCH: call results held in locals so the stores below come out in field order
      int accessory = PlayerLookGetAccessoryModel(i);
      int hat = PlayerLookGetHatModel(init.mUnknown5A);
      int slot1 = PlayerLookGetSlot1Model(init.mUnknown5A);
      init.mUnknown1C = key;
      init.mUnknown20 = ids;
      init.mUnknown28 = hat;
      init.mUnknown2C = slot1;
      init.mUnknown30 = accessory;
      init.mUnknown34 = value;
      init.mUnknown5B = PlayerDbGetPlex(&object);
      FaceFeatures_t block;
      PlayerDbGetFaceFeatures(&object, &block);
      FaceMorphBuildWeights(&block, &init.mUnknown5C);
      if (owner) {
        _PlyrObjs_ppPlayers[i] =
            (Object_8003DEC4 *)ObjNewInList(owner, 0, 0, &init);
        ObjSetPriority(owner, _PlyrObjs_ppPlayers[i], 10);
        _PlyrObjs_ppPlayers[i]->mUnknown988 =
            PlyrNameTagNew(init.mUnknown57 * 7 + init.mUnknown58);
        PlyrNameTagSetText(_PlyrObjs_ppPlayers[i]->mUnknown988, " ");
      } else {
        _PlyrObjs_ppPlayers[i] = (Object_8003DEC4 *)ObjNew(0, 0, &init);
        _PlyrObjs_ppPlayers[i]->mUnknown988 = 0;
      }
      if (_PlyrObjs_pHandleA && _PlyrObjs_pHandleB) {
        Object_8003DEC4 *player = _PlyrObjs_ppPlayers[i];
        player->mUnknown4256.mUnknown672 = 0;
        player->mUnknown4256.mPairs[0].mX = 0.0f;
        player->mUnknown4256.mPairs[0].mY = 0.0f;
        player->mUnknown4256.mPairs[1].mX = 1.0f;
        player->mUnknown4256.mPairs[1].mY = 0.0f;
        player->mUnknown4256.mPairs[2].mX = 1.0f;
        player->mUnknown4256.mPairs[2].mY = 1.0f;
        player->mUnknown4256.mPairs[3].mX = 0.0f;
        player->mUnknown4256.mPairs[3].mY = 1.0f;
        player->mUnknown4256.mPoints[0][2] = 0.0f;
        player->mUnknown4256.mPoints[1][2] = 0.0f;
        player->mUnknown4256.mPoints[2][2] = 0.0f;
        player->mUnknown4256.mPoints[3][2] = 0.0f;
      }
      PlayerLookApply(i);
      if (hasName)
        PlaTexCacheSetFace(init.mUnknown5A, name, 0);
      else
        PlaTexCacheSetCapFace(init.mUnknown5A, fn_80081E3C(&object) + 1,
                              PlayerDbGetFaceId(&object), PlayerDbGetEyebrows(&object), 0);
    }
    PlayerCursorClose(&object);
  }
  ResTrackResume();
  return result;
}
void PlyrObjsSetHeadSkeletons() {
  fn_8015F484(_PlyrObjs_pBodySkel, _PlyrObjs_apMirrorSkels, _PlyrObjs_pSkel19, _PlyrObjs_pSkel5);
}
void PlyrObjsResolveTeamIds(int value, int *out, int mode) {
  Object_8008044C object;
  Desc_8008044C desc;
  unsigned int i;
  if (!mode) {
    desc.mUnknown4 = 1;
    desc.mUnknown8 = value;
    PlayerCursorOpen(&object, &desc, 0x454D4147);
    for (i = 0; i < _PlyrObjs_uTeamSize; ++i) {
      PlayerDbSeekOriginalId(&object, out[i], 0);
      out[i] = PlayerDbGetId(&object);
    }
    PlayerCursorClose(&object);
  } else {
    for (i = 0; i < _PlyrObjs_uTeamSize; ++i)
      out[i] = 332;
  }
}
int PlyrObjsGetStreamBits() { return 13; }
int PlyrObjsCreate(int count, int owner, int mode) {
  ObjNewType_(29, 20, 1, PlyrObjsShadowAdd, PlyrObjsShadowDelete);
  if (owner) {
    ObjSetListObjFunc(owner, 29, 0, PlyrObjsDrawShadowQuads);
    _PlyrObjs_pHandleA = ObjNewInList(owner, 29, 0, 0);
    ObjSetPriority(owner, _PlyrObjs_pHandleA, 2);
  }
  ObjNewType_(30, 20, 1, PlyrObjsShadowAdd, PlyrObjsShadowDelete);
  if (owner) {
    ObjSetListObjFunc(owner, 30, 0, PlyrObjsDrawShadowClips);
    _PlyrObjs_pHandleB = ObjNewInList(owner, 30, 0, 0);
    ObjSetPriority(owner, _PlyrObjs_pHandleB, 7);
  }
  ObjNewType_(27, 20, 1, PlyrObjsTrailAdd, PlyrObjsTrailDelete);
  if (owner) {
    ObjSetListObjFunc(owner, 27, 0, PlyrObjsDrawTrails);
    _PlyrObjs_pHandleC = ObjNewInList(owner, 27, 0, 0);
    ObjSetPriority(owner, _PlyrObjs_pHandleC, 13);
  }
  PlayerObjAddObjType(owner, 0, count);
  _PlyrObjs_uTeamSize = (unsigned int)count >> 1;
  _PlyrObjs_uNumPlayers = count;
  PlyrObjsInitStateTables(mode);
  PlyrStatesRegister(0, mode);
  PlyrObjsLoadSkeletons();
  PlyrObjsInitLimbChains();
  PlayerObjRenderInit((int)_PlyrObjs_pBodySkel, (int)_PlyrObjs_apMirrorSkels);
  PlayerLookOpen();
  PlyrObjsResolveTeamIds(0, _PlyrObjs_aiDefaultPlayerIds, mode);
  PlyrObjsResolveTeamIds(1, _PlyrObjs_aiDefaultPlayerIds + _PlyrObjs_uTeamSize, mode);
  PlaTexCacheStart();
  int result = PlyrObjsCreatePlayers(owner, mode);
  if (!mode) {
    PlaTexCacheLoadAllNow();
    if (StadiumGetSkyState() == 3)
      PlayerLookHideSwitch28();
  } else
    PlaTexCacheDiscardRequests();
  if (!FELoopIsMainFEActive())
    PlaTexCacheCloseArchive();
  return result;
}
int PlyrObjsDestroy(int owner) {
  // FAKEMATCH: dead initializer; result is set from ObjDelType(27) before any read
  int result = 0;
  if (_PlyrObjs_pHandleA) {
    ObjRemoveFromList(owner, _PlyrObjs_pHandleA);
    VptTrashObject(_PlyrObjs_pHandleA);
    VptFlushObjectTrash();
    _PlyrObjs_pHandleA = 0;
  }
  if (_PlyrObjs_pHandleB) {
    ObjRemoveFromList(owner, _PlyrObjs_pHandleB);
    VptTrashObject(_PlyrObjs_pHandleB);
    VptFlushObjectTrash();
    _PlyrObjs_pHandleB = 0;
  }
  if (_PlyrObjs_pHandleC) {
    ObjRemoveFromList(owner, _PlyrObjs_pHandleC);
    VptTrashObject(_PlyrObjs_pHandleC);
    VptFlushObjectTrash();
    _PlyrObjs_pHandleC = 0;
  }
  if (_PlyrObjs_ppPlayers) {
    for (int i = 0; i < _PlyrObjs_uNumPlayers; ++i) {
      if (owner) {
        PlyrNameTagDelete(_PlyrObjs_ppPlayers[i]->mUnknown988);
        ObjRemoveFromList(owner, _PlyrObjs_ppPlayers[i]);
      }
      VptTrashObject(_PlyrObjs_ppPlayers[i]);
    }
    VptFlushObjectTrash();
    fn_801D2BD0(_PlyrObjs_ppPlayers);
    _PlyrObjs_ppPlayers = 0;
  }
  PlayerObjRenderShutdown();
  PlyrIKShutdown();
  // FAKEMATCH: local that only aliases the global gAnimData
  AnimData *anim = &gAnimData;
  ResUnLoad(anim->GetArchive(), 57);
  ResUnLoad(anim->GetArchive(), 58);
  ResUnLoad(anim->GetArchive(), 59);
  PlayerObjRemoveObjType(0);
  ObjDelType(29);
  ObjDelType(30);
  result = ObjDelType(27);
  _PlyrObjs_uNumPlayers = 0;
  PlaTexCacheStop();
  PlayerLookClose();
  if (FELoopIsMainFEActive() && PlaTexCacheGetArchive())
    PlaTexCacheCloseArchive();
  return result;
}
void PlyrObjsSetTeamIds(int side, int *values) {
  int offset = side ? 7 : 0;
  for (int i = 0; i < 7; ++i)
    _PlyrObjs_aiDefaultPlayerIds[offset + i] = values[i];
}
int PlyrObjsGetCount() { return _PlyrObjs_uNumPlayers; }
int PlyrObjsGetPerTeam() { return 7; }
Object_8003DEC4 *PlyrObjsGet(int index) {
  Object_8003DEC4 *result = 0;
  if (_PlyrObjs_ppPlayers)
    result = _PlyrObjs_ppPlayers[index];
  return result;
}
Object_8003DEC4 *PlyrObjsFindByKey(int value) {
  Object_8003DEC4 *result = 0;
  for (unsigned char i = 0; i < _PlyrObjs_uNumPlayers; ++i)
    if (_PlyrObjs_ppPlayers[i]->mUnknown4956 == value) {
      result = _PlyrObjs_ppPlayers[i];
      break;
    }
  return result;
}
Object_8003DEC4 *PlyrObjsGetBySide(int side, unsigned char index) {
  Object_8003DEC4 *result = 0;
  if (_PlyrObjs_ppPlayers)
    result = PlyrObjsGet(side * 7 + index);
  return result;
}
Object_8003DEC4 *PlyrObjsFindNearest(Point2_t *point, float *distance) {
  float value = 10000.0f;
  Object_8003DEC4 *result = 0;
  if (_PlyrObjs_ppPlayers)
    for (unsigned int i = 0; i < _PlyrObjs_uNumPlayers; ++i) {
      Object_8003DEC4 *player = _PlyrObjs_ppPlayers[i];
      float current = Vec2Distance(player->mUnknown4, point);
      if (!(current >= value)) {
        result = player;
        value = current;
      }
    }
  if (distance)
    *distance = value;
  return result;
}
AnimSkeleton_t *PlyrObjsGetBodySkeleton() { return _PlyrObjs_pBodySkel; }
AnimSkeleton_t *PlyrObjsGetSkel19() { return _PlyrObjs_pSkel19; }
void PlyrObjsGetPlayerRef(Block_80170E64 *object, int *reference) {
  PlyrRefSet(reference, 0, 0, 0);
  if (object)
    for (unsigned int team = 0; team < 2; ++team)
      for (unsigned int i = 0; i < 7; ++i) {
        Object_80039F5C *player =
            PlyrGet((unsigned char)team, (unsigned short)i);
        if (player->mpUnknown4 == object)
          *reference = player->mId;
      }
}
Object_80039F5C *PlyrObjsFindPlayer(Block_80170E64 *object) {
  struct {
    unsigned char mBytes[3];
    unsigned char mKind;
  } reference;
  int *key = (int *)&reference;
  Object_80039F5C *result = 0;
  PlyrObjsGetPlayerRef(object, key);
  if (reference.mKind == 1)
    result = fn_8009BCE8(key);
  return result;
}
void PlyrObjsRegisterState() {
  int size = PlyrPoseGetStreamBits(0) + PlyrObjsGetStreamBits();
  ReplayRegisterChannel(PlyrObjsWriteState, PlyrObjsReadState, size * _PlyrObjs_uNumPlayers, "Players");
}
void PlyrObjsSetDrawFlag(int a) { PlyrRenderSetHideFlagged(a); }
void PlyrObjsSetBodyType(int index, int value) {
  Object_8003DEC4 *object = PlyrObjsGet(index);
  if (value == 7)
    value = 2;
  object->mUnknown1016 = value;
  object->mUnknown1020 = fn_8015E440(0, value);
  fn_80234A14(&object->mBytes992[172], 1);
}
void PlyrObjsDrawShadows() {
  PlyrRenderNewFrame();
  PlyrObjsUpdateShadows();
}
}
