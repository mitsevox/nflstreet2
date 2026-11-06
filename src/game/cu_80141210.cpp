#include "game/GameCamera.h"
#include "game/cu_8013BB18.h"
#include "game/Class_80297B90.h"
#include "game/Class_80297BF8.h"
#include "game/Object_80039F5C.h"
#include "game/cu_8008E978.h"
#include "game/fn_802270D4.h"
#include "game/fn_800AD9B4.h"
#include "engine/viewport.h"
#include "engine/AnimSeqCamSample.h"

/* Views established by this caller's accesses. Their original identities
   and the contents of the opaque spans remain unknown. */
struct CamCurveActorSettings_t { unsigned char mUnknown0[0x300]; float mUnknown300; };
struct CamCurveActorEntry_t { float mUnknown0; unsigned char mUnknown4[4]; unsigned char mUnknown8; };
struct CamCurveState_t { float mUnknown0,mUnknown4; int mUnknown8; unsigned char mUnknownC[4]; };
struct CamCurveAngles_t { int mX,mY,mZ; };
struct CamCurveView_t { Vector_80039F5C mUnknown0; CamCurveAngles_t mUnknownC; int mUnknown18; };

extern "C" {
float AnimSequencerGetTicksPerSecond(void);
AnimSeqCamSample_t *AnimSeqCamFindFirstCamera(Actor_801C009C *);
AnimSeqCamSample_t *AnimSeqCamFindCamera(Actor_801C009C *bank, unsigned short id, unsigned short subId, unsigned short index);
float fn_801C5278(float,AnimSeqCamCurve_t *,int);
void fn_801D04C4(void); void fn_801D0558(void); void fn_801D0544(void); void fn_801D0508(void);
void fn_801D0F80(float (*)[4]); void fn_801D06D4(float (*)[4]); void fn_801D0ADC(int);
void QuatFromAxisAngle(float *,Vector_80039F5C *,int);
void QuatMultiply(float *,float *,float *);
void QuatToMatrix(float (*)[4],float *);
void fn_8022765C(void *,void *,void *);
float fn_80227120(void *); float fn_80227704(void *,void *);
void fn_80227264(void *,void *,float);
void fn_80227C2C(void *,void *);
void fn_80227384(void *,void *,int);
void fn_80227490(void *,void *,int,int,int);
int fn_801CFE40(float,float); float fn_80260B1C(float);
void CamCurveOffsetPosition(float,float,float,Vector_80039F5C *,CamCurveState_t *,Actor_801C009C *);
void CamCurveConvertAngles(CamCurveAngles_t *,CamCurveState_t *,Actor_801C009C *,int,int,int);
CamCurveActorEntry_t *CamCurveGetActorEntry(GameCamera_t *);
int FELoopIsMainFEActive(void);
void CamSetFieldOfView(GameCamera_t *,float,float);
CamCurveActorSettings_t *fn_800963EC(Character_80093BCC *);
int fn_801784C4(void);
GameCamera_t *CamGameGetCamera(int);
void CamFreeSetPos(GameCamera_t *,float,float,float);
void CamFreeSetAngle(GameCamera_t *,int,int,int);
float fn_800BD190(void *); float fn_800AB9EC(void *);
void CamCurveSetProjection(GameCamera_t *);
}

static CamCurveView_t _CamCurve_Views[6] = {
    { { 0.0f, -12.0f, 3.5f }, { 0xCAAAAB, 0, 0 }, 5 },
    { { 0.0f, -7.5f, 3.5f }, { 0xCAAAAB, 0, 0 }, 5 },
    { { 0.0f, -9.5f, 5.0f }, { 0xCAAAAB, 0, 0 }, 5 },
    { { 0.0f, -9.5f, 5.0f }, { 0xCAAAAB, 0, 0 }, 5 },
    { { 0.0f, -12.0f, 5.0f }, { 0xCE38E4, 0, 0 }, 5 },
    { { 0.0f, -16.0f, 10.0f }, { 0xCE38E4, 0, 0 }, 5 },
};
static CamCurveView_t _CamCurve_SideView = { { -30.0f, 0.0f, 10.0f }, { 0x38E38E, 0x800000, 0 }, 5 };

static unsigned char _CamCurve_bNarrowFov = 0;

extern "C" void CamCurveOffsetPosition(float x, float y, float z, Vector_80039F5C *out, CamCurveState_t *state, Actor_801C009C *)
{
    out->mX = state->mUnknown0 + x;
    out->mY = state->mUnknown4 + y;
    out->mZ = z;
}

extern "C" void CamCurveConvertAngles(CamCurveAngles_t *out, CamCurveState_t *, Actor_801C009C *, int x, int y, int z)
{
    out->mX = (0xC00000 - x) & 0xFFFFFF;
    out->mY = y & 0xFFFFFF;
    out->mZ = -z & 0xFFFFFF;
}

extern "C" CamCurveActorEntry_t *CamCurveGetActorEntry(GameCamera_t *camera)
{
    CamCurveState_t *state=reinterpret_cast<CamCurveState_t *>(camera->mPadF8);
    CamCurveActorEntry_t *entry=0;
    Object_80039F5C *object=fn_8009BCE8(&state->mUnknown8);
    if (object && object->mIdBytes[3]==1 && object->mpState->mId==50)
        entry=reinterpret_cast<CamCurveActorEntry_t *>(&object->mUnknown336);
    return entry;
}

/* Sample the selected actor camera curves, scale and transform them
   into the camera view, and retain the view when no sample is available. */
extern "C" void CamCurveApplyActorCurves(GameCamera_t *camera, Actor_801C009C *actor, CamCurveSelection_t *selection, float time)
{
    Vector_80039F5C offset, position, result, look, up, projection, base;
    CamCurveAngles_t angles, resultAngles, rotation;
    float matrix[4][4];
    Vector_80039F5C direction;
    float qx[4], qy[4], qz[4];
    AnimSeqCamSample_t *sample;
    float t = time / AnimSequencerGetTicksPerSecond();

    fn_801D04C4(); fn_801D0558(); fn_801D0F80(matrix); fn_801D0544();
    if (!selection->mUnknown0) return;
    if (selection->mUnknown4.mWord == -1 || selection->mUnknown8.mWord == -1)
        sample = AnimSeqCamFindFirstCamera(actor);
    else sample = AnimSeqCamFindCamera(actor,1,selection->mUnknown4.mParts[1],selection->mUnknown8.mParts[1]);
    if (!sample) return;
    base.mX = sample->mUnknown0[0]; base.mY = -sample->mUnknown0[2]; base.mZ = sample->mUnknown0[1];
    offset.mX = fn_801C5278(t,&sample->mCurves[9],0);
    offset.mY = -fn_801C5278(t,&sample->mCurves[10],0);
    offset.mZ = fn_801C5278(t,&sample->mCurves[11],0);
    offset.mX *= camera->mUnknownF4; offset.mY *= camera->mUnknownF4; offset.mZ *= camera->mUnknownF4;
    rotation.mX = (int)(fn_801C5278(t,&sample->mCurves[12],0)*46603.37890625f);
    rotation.mY = (int)(-fn_801C5278(t,&sample->mCurves[14],0)*46603.37890625f);
    rotation.mZ = (int)(fn_801C5278(t,&sample->mCurves[13],0)*46603.37890625f);
    float q[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    Vector_80039F5C axis;
    axis.mX=1.0f; axis.mY=0.0f; axis.mZ=0.0f; QuatFromAxisAngle(qx,&axis,rotation.mX);
    axis.mX=0.0f; axis.mY=1.0f; axis.mZ=0.0f; QuatFromAxisAngle(qy,&axis,rotation.mY);
    axis.mX=0.0f; axis.mY=0.0f; axis.mZ=1.0f; QuatFromAxisAngle(qz,&axis,rotation.mZ);
    QuatMultiply(q,qy,qz); QuatMultiply(q,q,qx); QuatToMatrix(matrix,q);
    position.mX=fn_801C5278(t,&sample->mCurves[0],0);
    position.mY=-fn_801C5278(t,&sample->mCurves[2],0);
    position.mZ=fn_801C5278(t,&sample->mCurves[1],0);
    position.mX*=camera->mUnknownF4; position.mY*=camera->mUnknownF4; position.mZ*=camera->mUnknownF4;
    up.mX=fn_801C5278(t,&sample->mCurves[6],0);
    up.mY=-fn_801C5278(t,&sample->mCurves[8],0);
    up.mZ=fn_801C5278(t,&sample->mCurves[7],0);
    up.mX*=camera->mUnknownF4; up.mY*=camera->mUnknownF4; up.mZ*=camera->mUnknownF4;
    fn_802276B4(&up,&up,&position);
    look.mX=fn_801C5278(t,&sample->mCurves[3],0);
    look.mY=-fn_801C5278(t,&sample->mCurves[5],0);
    look.mZ=fn_801C5278(t,&sample->mCurves[4],0);
    look.mX*=camera->mUnknownF4; look.mY*=camera->mUnknownF4; look.mZ*=camera->mUnknownF4;
    fn_802276B4(&direction,&position,&look); fn_802276B4(&look,&look,&position);
    if (fn_80227120(&look)<0.0001f) { look.mX=0.0f; look.mY=1.0f; look.mZ=0.0f; }
    if (fn_80227120(&up)<0.0001f) { up.mX=0.0f; up.mY=0.0f; up.mZ=1.0f; }
    fn_801D04C4(); fn_801D06D4(matrix);
    fn_802276B4(&position,&position,&base); fn_80227C2C(&position,&position);
    fn_8022765C(&position,&position,&base); fn_8022765C(&position,&position,&offset);
    fn_80227C2C(&up,&up); fn_80227C2C(&look,&look); fn_801D0544();
    float dot = fn_80227704(&up,&look); float length = fn_80227120(&look);
    fn_80227264(&projection,&look,dot/length); fn_802276B4(&up,&up,&projection);
    position.mX-=actor->mUnknown18->mUnknown34; position.mY+=actor->mUnknown18->mUnknown3C;
    fn_80227384(&position,&position,camera->mUnknown10C-(int)(actor->mUnknown18->mUnknown30*2670176.75f)+0x400000);
    fn_80227384(&look,&look,camera->mUnknown10C-(int)(actor->mUnknown18->mUnknown30*2670176.75f)+0x400000);
    fn_80227384(&up,&up,camera->mUnknown10C-(int)(actor->mUnknown18->mUnknown30*2670176.75f)+0x400000);
    fn_80227384(&direction,&direction,camera->mUnknown10C-(int)(actor->mUnknown18->mUnknown30*2670176.75f)+0x400000);
    fn_801D0508(); fn_801D0ADC(0x400000); fn_80227C2C(&direction,&direction); fn_801D0544();
    angles.mY=0;
    angles.mZ=fn_801CFE40(direction.mY,direction.mX);
    float horizontal=fn_80260B1C(direction.mX*direction.mX+direction.mY*direction.mY);
    angles.mX=fn_801CFE40(-direction.mZ,horizontal);
    fn_80227490(&up,&up,-angles.mZ,0,0); fn_80227490(&up,&up,0,0,-angles.mX);
    angles.mY=fn_801CFE40(up.mZ,up.mX)-0x400000;
    CamCurveOffsetPosition(position.mX,position.mY,position.mZ,&result,reinterpret_cast<CamCurveState_t *>(camera->mPadF8),actor);
    CamCurveConvertAngles(&resultAngles,reinterpret_cast<CamCurveState_t *>(camera->mPadF8),actor,angles.mX,angles.mY,angles.mZ);
    if (_CamCurve_bNarrowFov && FELoopIsMainFEActive()==0) CamSetFieldOfView(camera,35.28518295288086f,camera->mHeader.mUnknown24);
    else CamSetFieldOfView(camera,36.77341842651367f,camera->mHeader.mUnknown24);
    fn_8013C478(camera,&result); fn_8013C4BC(camera,&resultAngles.mX,5); fn_8013C6F0(camera); CamCurveSetProjection(camera);
}

/* Build the camera view from the playback sample, applying the optional
   half-turn to the sampled transform and recording the curve duration. */
extern "C" void CamCurveApplyPlaybackCurves(GameCamera_t *camera, Actor_801C009C *actor, float time, int mirror)
{
    Vector_80039F5C result, position, base, offset, up, look, projection;
    CamCurveAngles_t resultAngles, angles, rotation;
    float matrix[4][4];
    float qx[4], qy[4], qz[4];
    Playback_80096DA8 *playback = fn_80096DA8(camera->mUnknown108);
    float t = time / AnimSequencerGetTicksPerSecond();
    AnimSeqCamSample_t *sample = AnimSeqCamFindCamera(actor, playback->mUnknown14.mParts[1], playback->mUnknown18.mParts[1], playback->mUnknown1C.mParts[1]);
    if (!sample) return;
    playback->mUnknown20 = (sample->mCurves[0].mUnknown8 - sample->mCurves[0].mUnknown4) * AnimSequencerGetTicksPerSecond();
    base.mX = sample->mUnknown0[0]; base.mY = -sample->mUnknown0[2]; base.mZ = sample->mUnknown0[1];
    offset.mX = fn_801C5278(t, &sample->mCurves[11], 0);
    offset.mY = -fn_801C5278(t, &sample->mCurves[9], 0);
    offset.mZ = fn_801C5278(t, &sample->mCurves[10], 0);
    rotation.mX = (int)(fn_801C5278(t, &sample->mCurves[12], 0) * 46603.37890625f);
    rotation.mY = (int)(-fn_801C5278(t, &sample->mCurves[14], 0) * 46603.37890625f);
    rotation.mZ = (int)(fn_801C5278(t, &sample->mCurves[13], 0) * 46603.37890625f);
    float q[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    Vector_80039F5C axis;
    axis.mX=1.0f; axis.mY=0.0f; axis.mZ=0.0f; QuatFromAxisAngle(qx,&axis,rotation.mX);
    axis.mX=0.0f; axis.mY=1.0f; axis.mZ=0.0f; QuatFromAxisAngle(qy,&axis,rotation.mY);
    axis.mX=0.0f; axis.mY=0.0f; axis.mZ=1.0f; QuatFromAxisAngle(qz,&axis,rotation.mZ);
    QuatMultiply(q,qy,qz); QuatMultiply(q,q,qx); QuatToMatrix(matrix,q);
    fn_801D04C4(); fn_801D06D4(matrix); if (mirror) fn_801D0ADC(0x800000); fn_801D0F80(matrix); fn_801D0544();
    position.mX=fn_801C5278(t,&sample->mCurves[0],0);
    position.mY=-fn_801C5278(t,&sample->mCurves[2],0);
    position.mZ=fn_801C5278(t,&sample->mCurves[1],0);
    up.mX=fn_801C5278(t,&sample->mCurves[6],0);
    up.mY=-fn_801C5278(t,&sample->mCurves[8],0);
    up.mZ=fn_801C5278(t,&sample->mCurves[7],0);
    fn_802276B4(&up,&up,&position);
    look.mX=fn_801C5278(t,&sample->mCurves[3],0);
    look.mY=-fn_801C5278(t,&sample->mCurves[5],0);
    look.mZ=fn_801C5278(t,&sample->mCurves[4],0);
    fn_802276B4(&look,&look,&position);
    if (fn_80227120(&look)<0.0001f) { look.mX=0.0f; look.mY=1.0f; look.mZ=0.0f; }
    if (fn_80227120(&up)<0.0001f) { up.mX=0.0f; up.mY=0.0f; up.mZ=1.0f; }
    fn_801D04C4(); fn_801D06D4(matrix);
    fn_802276B4(&position,&position,&base); fn_80227C2C(&position,&position);
    fn_8022765C(&position,&position,&base); fn_8022765C(&position,&position,&offset);
    fn_80227C2C(&up,&up); fn_80227C2C(&look,&look); fn_801D0544();
    float dot=fn_80227704(&up,&look); float length=fn_80227120(&look);
    fn_80227264(&projection,&look,dot/length); fn_802276B4(&up,&up,&projection);
    angles.mZ=fn_801CFE40(look.mY,look.mX)-0x400000;
    fn_80227490(&look,&look,-angles.mZ,0,0);
    angles.mX=fn_801CFE40(look.mZ,look.mY);
    fn_80227490(&up,&up,-angles.mZ,0,0); fn_80227490(&up,&up,0,0,-angles.mX);
    angles.mY=fn_801CFE40(up.mZ,up.mX)-0x400000;
    CamCurveOffsetPosition(position.mX,position.mY,position.mZ,&result,reinterpret_cast<CamCurveState_t *>(camera->mPadF8),actor);
    CamCurveConvertAngles(&resultAngles,reinterpret_cast<CamCurveState_t *>(camera->mPadF8),actor,angles.mX,angles.mY,angles.mZ);
    if (_CamCurve_bNarrowFov && FELoopIsMainFEActive()==0) CamSetFieldOfView(camera,35.28518295288086f,camera->mHeader.mUnknown24);
    else CamSetFieldOfView(camera,36.77341842651367f,camera->mHeader.mUnknown24);
    fn_8013C478(camera,&result); fn_8013C4BC(camera,&resultAngles.mX,5); fn_8013C6F0(camera); CamCurveSetProjection(camera);
}

/* Update the selected-character or playback view for modes 10 and 11;
   character views refresh their scale from the actor settings. */
extern "C" void CamCurveProcess(GameCamera_t *camera)
{
    Actor_801C009C *actor;
    switch (camera->mUnknownA0) {
    case 10: {
        CamCurveActorEntry_t *entry = CamCurveGetActorEntry(camera);
        if (entry) {
            Character_80093BCC *character = fn_80093BCC(entry->mUnknown8);
            actor = fn_80093BAC(character->mUnknown0, character->mUnknown4);
            CamCurveActorSettings_t *settings = fn_800963EC(character);
            if (actor->mUnknown8 & 0x200) camera->mUnknownF4 = 1.0f;
            else camera->mUnknownF4 = settings->mUnknown300;
            CamCurveApplyActorCurves(camera, actor, &character->mUnknownE0, entry->mUnknown0);
        }
        break;
    }
    case 11: {
        Playback_80096DA8 *playback = fn_80096DA8(camera->mUnknown108);
        int mirror = 0;
        if (playback->mUnknown0 != -1 && playback->mUnknown10 == 2) {
            if ((playback->mUnknownC & 0x10) && fn_801784C4() != 0) mirror = 1;
            actor = fn_80096DCC(playback->mUnknown0, playback->mUnknown4);
            CamCurveApplyPlaybackCurves(camera, actor, playback->mUnknown24, mirror);
        }
        break;
    }
    }
}
/* Set a preset view or initialize a sampled character/playback view;
   character views capture the current facing before sampling. */
extern "C" void CamCurveStart(GameCamera_t *camera)
{
    if (camera->mUnknownA0 <= 5) {
        fn_8013C478(camera, &_CamCurve_Views[camera->mUnknownA0].mUnknown0);
        fn_8013C4BC(camera, &_CamCurve_Views[camera->mUnknownA0].mUnknownC.mX, _CamCurve_Views[camera->mUnknownA0].mUnknown18);
    }
    switch (camera->mUnknownA0) {
    case 7:
        fn_8013C478(camera, &_CamCurve_SideView.mUnknown0);
        fn_8013C4BC(camera, &_CamCurve_SideView.mUnknownC.mX, _CamCurve_SideView.mUnknown18);
        break;
    case 10: {
        CamCurveActorEntry_t *entry = CamCurveGetActorEntry(camera);
        if (entry) {
            Character_80093BCC *character = fn_80093BCC(entry->mUnknown8);
            Actor_801C009C *actor = fn_80093BAC(character->mUnknown0, character->mUnknown4);
            if (actor->mUnknown8 & 0x400) camera->mUnknown10C = character->mUnknown14[0]->mMotion.mFacing;
            else camera->mUnknown10C = character->mUnknown14[0]->mMotion.mFacing;
            CamCurveApplyActorCurves(camera, actor, &character->mUnknownE0, entry->mUnknown0);
        }
        break;
    }
    case 11: {
        Playback_80096DA8 *playback = fn_80096DA8(camera->mUnknown108);
        int mirror = 0;
        if (playback->mUnknown0 != -1 && playback->mUnknown10 == 2) {
            if ((playback->mUnknownC & 0x10) && fn_801784C4() != 0) mirror = 1;
            Actor_801C009C *actor = fn_80096DCC(playback->mUnknown0, playback->mUnknown4);
            CamCurveApplyPlaybackCurves(camera, actor, playback->mUnknown24, mirror);
        }
        break;
    }
    }
}
/* Dispatch view initialization and updates; event 4 transfers position
   and angles from the camera named by the event argument. */
extern "C" void CamCurveMsgFunc(GameCamera_t *camera, int event, int argument)
{
    switch (event) {
    case 4:
        if (argument != -1) {
            GameCamera_t *other = CamGameGetCamera(argument);
            float *position = other->mHeader.mUnknown04;
            CamFreeSetPos(camera, position[0], position[1], position[2]);
            CamFreeSetAngle(camera, other->mHeader.mUnknown14[0], other->mHeader.mUnknown14[1], other->mHeader.mUnknown14[2]);
            fn_8013C384(camera, 0, 0, 0);
        }
        break;
    case 3: CamCurveProcess(camera); break;
    case 1: CamCurveStart(camera); break;
    }
}
/* Install the curve-camera event handler and per-axis movement and
   angular easing defaults. */
extern "C" void CamCurveInit(GameCamera_t *camera, CameraDesc_t *)
{
    camera->mUnknownDC = CamCurveMsgFunc;
    camera->mUnknown5C = camera->mUnknown60 = camera->mUnknown64 = 0.2f;
    camera->mUnknown68 = camera->mUnknown6C = camera->mUnknown70 = 0.1f;
    camera->mUnknown74 = camera->mUnknown78 = camera->mUnknown7C = 0x199999;
    camera->mUnknown80 = camera->mUnknown84 = camera->mUnknown88 = 0xCCCCC;
}
extern "C" void CamCurveUninit(GameCamera_t *) {}
extern "C" {
Mode_8013FD8C CamCurveMode = { CamCurveInit, CamCurveUninit, 0 };
}
extern "C" void CamCurveSetProjection(GameCamera_t *camera)
{
    float value=0.08f;
    if (camera->mUnknownA0!=11) {
        if (fn_800AD9B4()==1) value=fn_800BD190(lbl_803EAB90);
        else if (fn_800AD9B4()==7) value=fn_800AB9EC(lbl_803EAA8C);
    }
    if (camera->mUnknown28)
        VptSetPerspective(static_cast<Viewport_t *>(camera->mUnknown28),camera->mHeader.mUnknown20,camera->mHeader.mUnknown24,value,750.0f);
}
extern "C" void CamCurveSetNarrowFov(unsigned char value) { _CamCurve_bNarrowFov=value; }
