/* Play camera: the game camera mode used while a play runs. It follows the ball between the
   views of its camera definition, pans with the ball, adds a short random shake when the game
   asks for one, can swing half way around the field on request, and keeps the camera inside
   the field limits. */

#include "game/fn_80177FE0.h"
#include "game/GameCamera.h"
#include "game/GameOptions.h"
#include <string.h>
#include "game/Vec3Magnitude.h"
#include "game/Vec2Add.h"
#include "game/PlayBookTeam.h"
#include <math.h>
#include "engine/viewport.h"
#include "game/Lookup_8012078C.h"

struct CamPlayVec3_t { float mX,mY,mZ; };
struct CamPlayAngles_t { int mX,mY,mZ; };
struct CamPlayView_t { CamPlayVec3_t mUnknown0; CamPlayAngles_t mUnknownC; int mUnknown18; };
struct CamPlayState_t {
    unsigned int mUnknown0[3];
    unsigned int mUnknownC;
    int mUnknown10;
    unsigned char mUnknown14[12];
    CamPlayVec3_t mUnknown20;
    CamPlayAngles_t mUnknown2C;
    float mUnknown38;
};
struct CamPlayDef_t {
    CamPlayView_t *mUnknown0;
    int mUnknown4;
    float mUnknown8;
    float mUnknownC[2];
    float mUnknown14[2][2];
    CamPlayVec3_t mUnknown24;
    CamPlayVec3_t mUnknown30;
    CamPlayVec3_t mUnknown3C;
    CamPlayVec3_t mUnknown48;
    CamPlayVec3_t mUnknown54;
    CamPlayVec3_t mUnknown60;
};
struct CamPlayJitter_t {
    unsigned int mUnknown0,mUnknown4;
    float mUnknown8,mUnknownC;
    CamPlayVec3_t mUnknown10;
    unsigned char mUnknown1C,mUnknown1D;
    unsigned char mUnknown1E[2];
};
struct CamPlayJitterCtl_t {
    unsigned char mUnknown0;
    unsigned char mUnknown1[3];
    unsigned int mUnknown4,mUnknown8,mUnknownC;
};
static CamPlayJitterCtl_t _CamPlay_Jitter = {0, {0, 0, 0}, 0, 0, 0};
static CamPlayJitter_t _CamPlay_aJitterDefs[3] = {
    {1, 20, -0.1f, 0.1f, {0.0f, 0.0f, 0.0f}, 1, 0, {0, 0}},
    {1, 20, -0.2f, 0.2f, {0.0f, 0.0f, 0.0f}, 1, 0, {0, 0}},
    {1, 20, -0.3f, 0.3f, {0.0f, 0.0f, 0.0f}, 1, 1, {0, 0}},
};
extern "C" CamPlayDef_t lbl_802DC718[];
static CamPlayVec3_t _CamPlay_PanPoint;
static CamPlayAngles_t _CamPlay_PanAngles;
static float _CamPlay_fOrbitDir = 1.0f;
static unsigned char _CamPlay_bOrbitToggled = 0;
static float _CamPlay_fBlendFrames = 120.0f;
static CamPlayView_t *_CamPlay_pViews;
static float _CamPlay_fYOffset;
extern "C" {
void CamPresetSetEaseRates(GameCamera_t *, int);
unsigned int SyncRandGetRange(unsigned int,unsigned int);
void Vec3Add(void *,void *,void *);
int MathArcSin(float);
void CamFreeClearVelocity(GameCamera_t *);
int fn_800AD9B4(void);
int fn_801784C4(void);
void CamMainProcess(void *,int,int,int);
void CamMainWarpToDest(GameCamera_t *);
void Orient3Lerp(void *,void *,void *,float);
void CamMainSetAngle(GameCamera_t *,void *,int);
void Vec3Lerp(void *,void *,void *,float);
void MatSetStack(int);
void MatPushUnit(void);
void MatTranslate(void *);
void MatRotZ(int);
void MatRotX(int);
void Vec3Mat34Mul(void *,void *);
void MatPop(void);
void CamGameSetModeAll(int);
int BallsExist(void);
void *BallGetCurrent(void);
void BallGetPosition(void *,void *);
int fn_801486A0(void);
void CamMainSetOffset(GameCamera_t *,void *);
int fn_801783AC(int);
int fn_80178308(void);
void PlyrFindNearest(void *,float *,int);
int fn_800BA6F8(void);
int fn_800BAA24(void);
void Orient3Add(void *,void *,void *);
int fn_80178320(void);
void CamMainFollowBall(GameCamera_t *);
void CamMainFollow(void *,int,int,int);
void AudmonEventPost(int,int);
void CamPlayMsgFunc(GameCamera_t *,int,int);
void CamPlayStart(GameCamera_t *);

void CamPlayApplyJitter(GameCamera_t *camera, CamPlayVec3_t *point)
{
    unsigned int index = _CamPlay_Jitter.mUnknown4;
    if (_CamPlay_Jitter.mUnknown0) {
        unsigned int ticks = ++_CamPlay_Jitter.mUnknown8;
        unsigned int total = ++_CamPlay_Jitter.mUnknownC;
        float scale = 1.0f;
        if (_CamPlay_aJitterDefs[index].mUnknown1C) scale -= (float)(total / _CamPlay_aJitterDefs[index].mUnknown4);
        if (ticks >= _CamPlay_aJitterDefs[index].mUnknown0 && total <= _CamPlay_aJitterDefs[index].mUnknown4) {
            CamPlayVec3_t value;
            float low = _CamPlay_aJitterDefs[index].mUnknown8;
            float range = _CamPlay_aJitterDefs[index].mUnknownC-low;
            value.mX = scale*(low+range*((float)SyncRandGetRange(1,100)*0.01f));
            value.mZ = scale*(low+range*((float)SyncRandGetRange(1,100)*0.01f));
            value.mY = _CamPlay_aJitterDefs[index].mUnknown1D == 1 ? scale*(low+range*((float)SyncRandGetRange(1,100)*0.01f)) : 0.0f;
            value.mX = value.mX < -0.3f ? -0.3f : (value.mX > 0.3f ? 0.3f : value.mX);
            value.mY = value.mY < -0.3f ? -0.3f : (value.mY > 0.3f ? 0.3f : value.mY);
            value.mZ = value.mZ < -0.3f ? -0.3f : (value.mZ > 0.3f ? 0.3f : value.mZ);
            CamPlayVec3_t *dst = &_CamPlay_aJitterDefs[index].mUnknown10;
            dst->mX = value.mX;
            dst->mY = value.mY;
            dst->mZ = value.mZ;
            _CamPlay_Jitter.mUnknown8 = 0;
        }
        Vec3Add(point,point,&_CamPlay_aJitterDefs[index].mUnknown10);
        if (_CamPlay_Jitter.mUnknownC >= _CamPlay_aJitterDefs[index].mUnknown4) {
            _CamPlay_Jitter.mUnknown8 = 0;
            if (_CamPlay_Jitter.mUnknownC >= _CamPlay_aJitterDefs[index].mUnknown4+10) _CamPlay_Jitter.mUnknown0 = 0;
        }
        CamPresetSetEaseRates(camera,2);
    }
}
void CamPlayPanWithBall(CamPlayVec3_t *point, CamPlayAngles_t *angles, CamPlayVec3_t *velocity, int index, int mode)
{
    float base = lbl_802DC718[index].mUnknown8;
    float amount = velocity->mX/base*(lbl_802DC718[index].mUnknownC[1]-base);
    float length = Vec3Magnitude(point);
    int reset = 0;
    switch (mode) {
    case 4: length = -length; break;
    case 3: reset = 1; break;
    }
    if (reset) {
        angles->mZ = _CamPlay_PanAngles.mZ;
        point->mX = _CamPlay_PanPoint.mX;
    } else {
        angles->mZ -= MathArcSin(amount/length);
        if (mode == 4) amount = -amount;
        point->mX += amount;
        _CamPlay_PanAngles.mZ = angles->mZ;
        _CamPlay_PanPoint.mX = point->mX;
    }
}
void CamPlayInit(GameCamera_t *camera)
{
    _CamPlay_pViews = lbl_802DC718[camera->mUnknown9C].mUnknown0;
    camera->mUnknownE0 = 0.0f;
    camera->mUnknownE4 = 0;
    camera->mUnknownE5 = 0;
    _CamPlay_bOrbitToggled = 0;
    camera->mUnknownF0 = 0.0f;
    camera->mUnknownEC = 0.0f;
    camera->mUnknownE8 = 0.0f;
    camera->mUnknownDC = CamPlayMsgFunc;
    camera->mUnknown94 |= 0x10;
}
void CamPlayUninit(GameCamera_t *camera) { camera->mUnknown94 &= ~0x10; }
void CamPlayStartOrbit(GameCamera_t *camera)
{
    CamPlayState_t *state = (CamPlayState_t *)&camera->mPadF8;
    camera->mUnknownE5 = 0;
    _CamPlay_bOrbitToggled = 0;
    CamFreeClearVelocity(camera);
    if (fn_800AD9B4() == 3) {
        camera->mUnknownE0 = 180.0f;
        camera->mUnknownE4 = 1;
        if (camera->mHeader.mUnknown04[0] > 0.0f) {
            if (fn_801784C4()) _CamPlay_fOrbitDir = 1.0f; else _CamPlay_fOrbitDir = -1.0f;
        } else {
            if (fn_801784C4()) _CamPlay_fOrbitDir = -1.0f; else _CamPlay_fOrbitDir = 1.0f;
        }
        state->mUnknown0[2] = 0;
        state->mUnknown0[1] = 0;
        state->mUnknown0[0] = 0;
        state->mUnknown20.mX = camera->mUnknownC4;
        state->mUnknown20.mY = camera->mUnknownC8;
        state->mUnknown20.mZ = camera->mUnknownCC;
        state->mUnknown2C.mX = camera->mUnknownD0;
        state->mUnknown2C.mY = camera->mUnknownD4;
        state->mUnknown2C.mZ = camera->mUnknownD8;
        camera->mUnknownE8 = camera->mHeader.mUnknown04[0];
        camera->mUnknownEC = camera->mHeader.mUnknown04[1];
        camera->mUnknownF0 = camera->mHeader.mUnknown04[2];
        Vec2Add(&camera->mUnknownE8,&camera->mUnknownE8,&camera->mUnknownC4);
    } else {
        CamMainProcess(camera,0,0,0);
        CamMainWarpToDest(camera);
    }
}
unsigned char CamPlayProcessOrbit(GameCamera_t *camera)
{
    CamPlayState_t *state = (CamPlayState_t *)&camera->mPadF8;
    CamPlayAngles_t angles;
    CamPlayVec3_t offset;
    CamPlayVec3_t point;
    CamPlayVec3_t zero = {0.0f, 0.0f, 0.0f};
    float blend = 0.0f;
    camera->mUnknownE0 += _CamPlay_fOrbitDir*6.0f;
    if (fabsf(camera->mUnknownE0-180.0f) <= 180.0f && fn_800AD9B4() != 10) {
        blend = fabsf(camera->mUnknownE0-180.0f)*0.0055555557f;
        blend = blend < 0.0f ? 0.0f : (blend > 1.0f ? 1.0f : blend);
        Orient3Lerp(&angles,&_CamPlay_pViews[1].mUnknownC,&state->mUnknown2C,blend);
        angles.mZ = (int)(camera->mUnknownE0*46603.37890625f);
        CamMainSetAngle(camera,&angles,_CamPlay_pViews[camera->mUnknownA0].mUnknown18);
        Vec3Lerp(&point,&_CamPlay_pViews[1],&state->mUnknown20,blend);
        float z = point.mZ;
        MatSetStack(VptGetMatrixStack());MatPushUnit();MatTranslate(&zero);
        MatRotZ(-(int)(camera->mUnknownE0*46603.37890625f));
        MatRotX(0x400000);
        offset.mY = offset.mX = 0.0f;
        offset.mZ = Vec2Magnitude(&state->mUnknown20);
        Vec3Mat34Mul(&point,&offset);
        MatPop();
        camera->mUnknownCC = z;
        camera->mUnknownC4 = point.mX;
        camera->mUnknownC8 = point.mY;
        CamMainWarpToDest(camera);
    } else {
        camera->mUnknownE4 = 0;
        CamFreeClearVelocity(camera);
        CamGameSetModeAll(1);
        camera->mUnknown94 |= 0x10;
    }
    return camera->mUnknownE4;
}
unsigned char CamPlayIsOrbiting(GameCamera_t *camera) { return camera->mUnknownE4; }
#define ANGLES_FROM_DEGREES(dst, degrees) \
    { \
        CamPlayAngles_t angles_ = {0, 0, 0}; \
        angles_.mX = (int)((degrees).mX*46603.37890625f); \
        angles_.mY = (int)((degrees).mY*46603.37890625f); \
        angles_.mZ = (int)((degrees).mZ*46603.37890625f); \
        (dst) = angles_; \
    }
void CamPlayProcess(GameCamera_t *camera)
{
    CamPlayState_t *state = (CamPlayState_t *)&camera->mPadF8;
    CamPlayVec3_t point;
    CamPlayVec3_t velocity;
    CamPlayAngles_t angles;
    CamPlayAngles_t offset;
    if (BallsExist()) {
        BallGetPosition(BallGetCurrent(),&velocity);
        float bound = lbl_802DC718[camera->mUnknown9C].mUnknown8;
        velocity.mX = velocity.mX < -bound ? -bound : (velocity.mX > bound ? bound : velocity.mX);
    } else velocity.mX = velocity.mY = velocity.mZ = 0.0f;
    fn_80177FE0();
    CamPresetSetEaseRates(camera,0);
    switch (camera->mUnknownA0) {
    case 12:
        if (fn_801486A0() == 1) {
            ANGLES_FROM_DEGREES(offset, lbl_802DC718[camera->mUnknown9C].mUnknown48);
            CamMainSetOffset(camera,&lbl_802DC718[camera->mUnknown9C].mUnknown3C);
            CamMainSetAngle(camera,&offset,5);
        }
        break;
    case 3: CamPresetSetEaseRates(camera,1);
    case 1: case 2: case 4: {
        int gameMode = fn_800AD9B4();
        float extra = 0.0f;
        float blend = 0.0f;
        if (camera->mUnknownA4 == 0 && gameMode == 2) {
            if (state->mUnknown38 < 1.0f) {
                state->mUnknown38 += 1.0f/_CamPlay_fBlendFrames;
                state->mUnknown38 = state->mUnknown38 < 0.0f ? 0.0f : (state->mUnknown38 > 1.0f ? 1.0f : state->mUnknown38);
                Vec3Lerp(&point,&_CamPlay_pViews[1],&state->mUnknown20,state->mUnknown38);
                Orient3Lerp(&angles,&_CamPlay_pViews[1].mUnknownC,&state->mUnknown2C,state->mUnknown38);
                goto apply;
            }
        } else if (state->mUnknown38 < 1.0f) {
            state->mUnknown38 = 1.0f;
            Vec3Lerp(&point,&_CamPlay_pViews[1],&state->mUnknown20,state->mUnknown38);
            Orient3Lerp(&angles,&_CamPlay_pViews[1].mUnknownC,&state->mUnknown2C,state->mUnknown38);
        }
        if (fn_801783AC(0)) {
            PlyrFindNearest(&velocity,&extra,fn_80178308());
            extra -= 4.0f;
            if (extra > 0.0f) {
                blend = extra*0.16666667f;
                blend = blend < 0.0f ? 0.0f : (blend > 1.0f ? 1.0f : blend);
            }
        }
        if (fn_800BA6F8() && fn_800BAA24()) blend = 0.0f;
        Vec3Lerp(&point,&_CamPlay_pViews[1],&_CamPlay_pViews[camera->mUnknownA0],blend);
        Orient3Lerp(&angles,&_CamPlay_pViews[1].mUnknownC,&_CamPlay_pViews[camera->mUnknownA0].mUnknownC,blend);
    apply:
        if (gameMode != 2) CamPlayPanWithBall(&point,&angles,&velocity,camera->mUnknown9C,camera->mUnknownA0);
        if (fn_801486A0() == 0) {
            CamPlayAngles_t unused; // FAKEMATCH: unused local (compiled-out debug filler) gives the target's frame slots
            Vec3Add(&point,&point,&lbl_802DC718[camera->mUnknown9C].mUnknown24);
            ANGLES_FROM_DEGREES(offset, lbl_802DC718[camera->mUnknown9C].mUnknown30);
            Orient3Add(&angles,&angles,&offset);
        }
        if (fn_801486A0() == 2) {
            Vec3Add(&point,&point,&lbl_802DC718[camera->mUnknown9C].mUnknown54);
            ANGLES_FROM_DEGREES(offset, lbl_802DC718[camera->mUnknown9C].mUnknown60);
            Orient3Add(&angles,&angles,&offset);
        } else if (!GameOptionsGet(18) && !fn_800BA6F8() && fn_800AD9B4() == 3 && camera->mUnknownA0 == 1) {
            int side = fn_80178320();
            Object_80039F5C *player = PlyrGet(side,*fn_8012078C()->mpUnknown4);
            if (player) {
                float adjustment = player->mMotion.mPos.mY;
                float ballY = velocity.mY;
                if (ballY > adjustment) {
                    adjustment = (ballY - adjustment) * 0.5f;
                    float cameraY = point.mY;
                    point.mY = cameraY - (adjustment < 0.0f ? 0.0f : (adjustment > 10.0f ? 10.0f : adjustment));
                }
            }
        }
        CamPlayApplyJitter(camera,&point);
        point.mY -= _CamPlay_fYOffset;
        CamMainSetOffset(camera,&point);
        CamMainSetAngle(camera,&angles,_CamPlay_pViews[camera->mUnknownA0].mUnknown18);
        break;
    }
    case 5: state->mUnknownC = 0; break;
    }
}
unsigned char CamPlayWasOrbitToggled(void) { return _CamPlay_bOrbitToggled; }
void CamPlayMsgFunc(GameCamera_t *camera, int message, int)
{
    CamPlayState_t *state = (CamPlayState_t *)&camera->mPadF8;
    switch (message) {
    case 3:
        if (CamPlayIsOrbiting(camera)) CamPlayProcessOrbit(camera);
        else CamPlayProcess(camera);
        break;
    case 1: CamPlayStart(camera); break;
    case 2: camera->mUnknownE5 ^= 1; _CamPlay_bOrbitToggled = 1; break;
    case 0: case 4: case 11: break;
    case 5: if (camera->mUnknownE5) CamPlayStartOrbit(camera); break;
    case 6: case 7: case 8: case 9: case 10: state->mUnknownC |= 1u << message; break;
    }
}
void CamPlayStart(GameCamera_t *camera)
{
    CamPlayState_t *state = (CamPlayState_t *)&camera->mPadF8;
    state->mUnknown38 = 0.0f;
    state->mUnknown10 = 0;
    state->mUnknown20.mX = camera->mUnknownC4;
    state->mUnknown20.mY = camera->mUnknownC8;
    state->mUnknown20.mZ = camera->mUnknownCC;
    state->mUnknown2C.mX = camera->mUnknownD0;
    state->mUnknown2C.mY = camera->mUnknownD4;
    state->mUnknown2C.mZ = camera->mUnknownD8;
    CamFreeClearVelocity(camera);
    _CamPlay_Jitter.mUnknown0 = 0;
    switch (camera->mUnknownA0) {
    case 1:
        if (BallsExist()) CamMainFollowBall(camera);
        if (camera->mUnknownA4 == 0 || camera->mUnknownA4 == 5) break;
        CamMainSetOffset(camera,&_CamPlay_pViews[camera->mUnknownA0]);
        CamMainSetAngle(camera,&_CamPlay_pViews[camera->mUnknownA0].mUnknownC,_CamPlay_pViews[camera->mUnknownA0].mUnknown18);
        break;
    case 4:
        CamMainFollow(camera,6,0,0);
        state->mUnknown38 = 1.0f;
        break;
    case 5: state->mUnknownC = 0;
    case 2:
    default:
        if (BallsExist()) CamMainFollowBall(camera);
        CamMainSetOffset(camera,&_CamPlay_pViews[camera->mUnknownA0]);
        CamMainSetAngle(camera,&_CamPlay_pViews[camera->mUnknownA0].mUnknownC,_CamPlay_pViews[camera->mUnknownA0].mUnknown18);
        break;
    case 10: case 11: case 12: break;
    }
    int mode = fn_801486A0();
    if (mode != 15) {
        if (mode == 1 && (unsigned int)camera->mUnknownA0 <= 2) camera->mUnknownA0 = 12;
    }
}
int CamPlayGetDefMode(int index) { return lbl_802DC718[index].mUnknown4; }
void CamPlayGetPosLimits(int index, unsigned int mode, float *a, float *b)
{
    int alternate = 0;
    switch (mode) {
    case 0: case 1: case 4: case 7: case 8: case 9: case 10: case 11: case 12: alternate = 0; break;
    case 2: case 3: case 5: alternate = 1; break;
    }
    float *pa = lbl_802DC718[index].mUnknownC;
    /* FAKEMATCH: the target adds the pair offset and the row offset before
       the table base ((alternate * 8 + index * 0x6C) + &mUnknown14); every
       array-index form adds the row offset to the base first. */
    float *pb = (float *)((char *)lbl_802DC718[0].mUnknown14 +
                          (alternate * sizeof(lbl_802DC718[0].mUnknown14[0]) + index * sizeof(CamPlayDef_t)));
    a[0] = pa[0];
    a[1] = pa[1];
    b[0] = pb[0];
    b[1] = pb[1];
}
void CamPlayStartJitter(unsigned int index)
{
    if (!_CamPlay_Jitter.mUnknown0 && GameOptionsGet(10)) {
        _CamPlay_Jitter.mUnknown0 = 1;
        _CamPlay_Jitter.mUnknown4 = index;
        _CamPlay_Jitter.mUnknown8 = 100;
        _CamPlay_Jitter.mUnknownC = 0;
        AudmonEventPost(17,0);
    }
}
void CamPlaySetYOffset(float amount) { _CamPlay_fYOffset = amount; }
}
