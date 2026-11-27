/* The instant replay: records every play into a ring of packed frames that
   the player, ball, object, particle and sound code write through registered
   channels, then plays it back with the replay camera, either under the
   player's control (pause, rewind, step, free camera cursor) or as an
   automatic replay that picks a scripted camera sequence from the play's
   recorded events. */
#include "game/Vec2Distance.h"
#include "game/ScreenTransition.h"
#include "game/fn_8009D990.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "engine/vptmanager.h"
#include "game/GameCamera.h"
#include "game/GameVpt.h"
#include "game/Object_80039F5C.h"
#include "game/ScrmPlayResult.h"
#include "game/RecordList_8002E7C0.h"
#include "game/Ball.h"
#include "game/cammain.h"
#include "game/Replay.h"
#include "game/ReplayEvent.h"
#include "game/fn_800AD9B4.h"
#include "game/PlayBookGetPlay.h"
#include "game/MemCardUtil.h"
#include <string.h>
#include "engine/dslist.h"
#include "game/Vec2Add.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))
#define CLAMP(x, lo, hi) ((x) < (lo) ? (lo) : ((x) > (hi) ? (hi) : (x)))
/* Compiled-out assert of the release build. */
#define REPLAY_ASSERT(e) do { } while (0)

/* Camera description set up by ReplayCamInitDesc (12 bytes cleared, +4 filled by
   fn_8009BD2C, +8 set to 1) and consumed by ReplayEnterPlayback, ReplayCamStart and
   ReplayCamCreate (+0 selects the camera mode, +8 attaches it). */
struct ReplayCamDesc_t {
    int mUnknown00;
    int mUnknown04;
    unsigned char mUnknown08;
};

/* One {op, arg} word of a condition list read by ReplayTestConditions; op -1 ends
   the list. Ops 0 and 27 read only the low byte of the argument. */
struct ReplayCond_t {
    short mOp;
    union {
        short mArg;
        struct {
            char mArgPad;
            unsigned char mArgLow;
        };
    };
};

/* One {op, arg} word of a replay camera script (ReplayFindScript); op -1 ends it. */
struct ReplayCommand_t {
    short mOp;
    short mArg;
};

/* {id, script} row of the table ReplayFindScript searches; id -1 ends it. */
struct ReplayScript_t {
    int mId;
    ReplayCommand_t *mpCommands;
};

/* 12-byte row of the table ReplayGetScriptTable returns: a script id and the
   condition list ReplayPickScript tests for it; id -1 ends the table. */
struct ReplayScriptConds_t {
    int mId;
    ReplayCond_t *mpConds;
    int mUnknown08;
};

/* 0x14-byte focus block of the replay camera at 0x8030660C (cleared as a
   whole by ReplayCamStart); mPos is the focus point. */
struct ReplayFocus_t {
    int mUnknown00;
    Vector_80039F5C mPos;
    int mUnknown10;
};

/* 16-byte bit stream opened on a frame buffer by fn_80190ED4 (buffer, mode,
   bit position, 0x3F) and closed by fn_80190EF0. */
struct Type_80190ED4 {
    char *mpBuffer;
    int mMode;
    int mUnknown08;
    int mUnknown0C;
};

/* 12-byte replay channel record of the _Replay_pChannels pool, registered by
   ReplayRegisterChannel: write and read callbacks and the record size in bits. */
struct ReplayChannel_t {
    void (*mpWrite)(Type_80190ED4 *pStream);
    void (*mpRead)(Type_80190ED4 *pStream0, Type_80190ED4 *pStream1, Type_80190ED4 *pStream2,
                   Type_80190ED4 *pStream3, float t);
    unsigned int mSize;
};

extern "C" {
extern char lbl_802EC330[];
extern void *gUISMainInfo;

double fabs(double);

void PadInputRead(void);
void PadInputSaveHandlers(void **pHandlers);
void PadInputRestoreHandlers(void **pHandlers);
void PadInputResetSlot(int slot);
void InGamePause(void);
void InGameResume(void);
unsigned char InGameIsDemo(void);
void ReplayCursorSetPos(const float *pValue, int a);
void ReplayCursorSetVisible(unsigned char value);
void PlyrMgrSetLeadFlags(void);
void PlyrMgrClearLeadFlags(void);
void PlyrMgrRefreshModels(void);
Block_80170E64 *PlyrObjsFindNearest(Vector_80039F5C *pPos, float *pDist);
void PlyrObjsGetPlayerRef(Block_80170E64 *pBlock, int *pOut);
Block_80170E64 *BigObjFindNearest(Vector_80039F5C *pPos, float *pDist);
void PlyrPoseSetBlendFlag(int a);
void DivotSaveState(void);
void DivotRestoreState(void);
void EnvObjUpdateFades(void);
void FieldLinesUpdate(void);
void PauseBlock(void);
void PauseUnblock(void);
int PauseIsOpen(void);
void PauseSetPollDelay(int value);
void AudmonEventPost(int type, Vector_80039F5C *pPos);
int SndgSfxPlay(int index, Vector_80039F5C *pPos);
void SndgReplayReset(void);
void SndgEventSetReplayKind(int a);
void SndgEventReloadCrowdBanks(void);
void SndgEventOnReplayCase1(void);
void SndgEventOnReplayCase2(void);
void SndgEventPlayReplaySfx(int a);
void SndgMusicSetMode(int a);
void SndgMusicResume(void);
void fn_8009BB50(int a, int b);
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
void fn_8009D818(int state);
unsigned int fn_8009D86C(void);
void fn_8009D964(int index, int value);
void fn_800A3120(float a);
float fn_800A32B4(void);
int fn_800A3444(void);
void fn_800A8644(void);
void fn_800A866C(void);
void fn_800B50E8(int a);
int fn_800B81A4(void);
void BallsSetVisible(int on);
void CamReplayNextRecord(void);
void CamGameResumeAll(void);
void ParticleSysUpdate(float a);
void ParticlesProcess(float a);
void ParticlesStopOnEnter(void);
void ParticlesFlush(void);
void ParticlesStopOnLeave(void);
void ParticleTrailUpdateAll(void);
unsigned char ParticleTrailSetEnabled(unsigned char a);
void PassIconObjSetEnabled(int value);
void PlyrStarSetShown(int a, int b);
void ScrmMirrorField(int a, int b);
int ScrmGetDown(void);
int ScrmGetPlayDown(void);
void ScrmSetDown(int a);
FieldPoint_t ScrmGetBallSpot(void);
void ScrmSetBallSpot(FieldPoint_t pos);
float ScrmGetLineToGain(void);
void ScrmSetLineToGain(float line);
int ScrmGetOffenseTeam(void);
int ScrmGetDefenseTeam(void);
int ScrmGetSnapOffense(void);
int ScrmIsFieldFlipped(void);
int ScrmGetTeamScore(int a);
void ScrmSetTeamScore(int which, short value);
float ScrmGetSidelineX(void);
float ScrmGetEndLineY(void);
unsigned int ScrmGetTeamPlayerCount(int team);
void BannerClear(int a);
void HudPost3AOn(void);
void HudHide(void);
void HudUnhide(void);
void HudHideOverlay(void);
void HudShowOverlay(void);
unsigned char HudIsHidden(void);
void DebugWindowClose(void);
unsigned char GameEventFlagsSetFlag0(unsigned char value);
unsigned char GameEventFlagsSetFlag1(unsigned char value);
void UISGameHandleInput(int a, unsigned int id, float value);
void fn_80190ED4(Type_80190ED4 *pStream, char *pBuffer, int mode);
int fn_80190EF0(Type_80190ED4 *pStream);
unsigned long long fn_80190F18(void *pStream, int bits);
void fn_80191068(void *pStream, unsigned long long value, int bits);
int ScreenTransCanCapture(int id);
void ReplayAuxRamStoreFrame(char *pSrc, int index, int size);
char *ReplayAuxRamGetScratch(int index, int size);
char *ReplayAuxRamLoadFrame(int index, int size);
void ReplayAuxRamInit(int count, int size);
void ReplayAuxRamShutdown(void);
void *CamCreate(int a, CameraDesc_t *pDesc);
void CamDestroy(void *pCamera);
void CamSetNearPlane(GameCamera_t *pCamera, float value);
int ConSetChannelInfo(int a, int b, int c);
int ConGetChannelInfo(int a, int b);
void *DSNewListNode(void *pool);
void *DSGetListNode(void *pool, void *item);
void *DSNextListNode(void *pool, void *item);
void *fn_801D2B7C(int size, int a, int b);
int fn_801D2BD0(void *p);
void RemapCopyTable(int a, int b);
int SysGetSystemTime(void);
void fn_80219650(void *p, unsigned short *pA, unsigned short *pB);
void UISProcessEvent(void *p, int a, int b, int c, float *pD, unsigned char e);
void Vec2Rotate(FieldPoint_t *pOut, FieldPoint_t *pIn, int angle);
float Vec3Distance(Vector_80039F5C *pPos, Vector_80039F5C *pOther);
void Vec3Lerp(Vector_80039F5C *pOut, Vector_80039F5C *pA, Vector_80039F5C *pB, float t);
int SyncTimeGetGameTime(void);

/* Animation state and animation of each player ([team][index]), filled by
   PlyrAnimReplayRead. */
extern unsigned short lbl_803192BC[2][7];
extern unsigned short lbl_803192D8[2][7];

/* File-static: nothing on GameCube calls these, and the linker drops them. */
extern "C" {
static Block_80170E64 *GetHighlightedObject(void);
static void PrintPlayerDebugLine(int line, char *pBuf, int);
static void PrintDebugHelpLine(int line, char *pBuf, int, int *pCount);
static void SetFocusHeight(unsigned char reset, float height);
}

void ReplayDebugWindowOpen(void);
void ReplayDebugWindowClose(void);
unsigned char ReplayDebugWindowIsOpen(void);
void ReplayDebugWindowToggle(void);
void ReplaySaveGameState(ReplayGameState_t *p);
void ReplayRestoreGameState(ReplayGameState_t *p);
int ReplayClear(Type_803EA368 *p);
int ReplayStartRecording(Type_803EA368 *p);
int ReplayStopRecording(Type_803EA368 *p);
int ReplayRecordSkip(Type_803EA368 *p);
void ReplayRecordUpdate(Type_803EA368 *p);
int ReplayGetCameraMode(Type_803EA368 *p, int event, int a);
void ReplayHandlePlayRequest(Type_803EA368 *p);
void ReplayUpdateAutoPlay(Type_803EA368 *p);
void ReplayUpdateUserPlay(Type_803EA368 *p);
int ReplayEnterPlayback(Type_803EA368 *p, ReplayCamDesc_t *pDesc);
int ReplayExitPlayback(Type_803EA368 *p);
void ReplayRefreshFrame(Type_803EA368 *p);
void ReplayStepBackward(Type_803EA368 *p, int delta);
void ReplayStepForward(Type_803EA368 *p, int delta);
void ReplayTakeControllerInput(Type_803EA368 *p);
void ReplayReleaseControllerInput(Type_803EA368 *p);
void ReplayTriggerMarkEffect(int type);
void ReplayStartRecordingStub(Type_803EA368 *p);
int ReplaySeek(Type_803EA368 *p, int value);
void ReplaySetSpeed(Type_803EA368 *p, int value);
int ReplayGetStartFrame(Type_803EA368 *p);
void ReplaySetPlayEnd(Type_803EA368 *p, int value);
int ReplayGetLength(Type_803EA368 *p);
void ReplaySetEndHere(Type_803EA368 *p);
void ReplayDirectorEnter(void);
void ReplayDirectorExit(void);
int ReplayDirectorIsActive(void);
void ReplayDirectorHandleInput(Type_803EA368 *p, int a, unsigned int id, float value);
void ReplayDirectorUpdateFocus(ReplayFocus_t *pFocus, Block_80170E64 **ppTarget);
void ReplayDirectorUpdate(Type_803EA368 *p);
void ReplayShotListStartStub(void);
void ReplaySetEventMark(Type_803EA368 *p, int id, int value, int index);
void ReplayInitShotTimer(Type_803EA368 *p, Timer_8002E7C0 *pTimer);
Record_8002E7C0 *ReplayShotListAdd(RecordList_8002E7C0 *pList);
float ReplayEventDeltaY(int a, int b);
int ReplayTestConditions(ReplayCond_t *pCond);
void ReplayBuildShotList(Type_803EA368 *p, RecordList_8002E7C0 *pList);
void ReplayStartShot(Type_803EA368 *p, Timer_8002E7C0 *pTimer);
void ReplayShotListClear(RecordList_8002E7C0 *pList);
void ReplayShotListStart(Type_803EA368 *p, RecordList_8002E7C0 *pList);
int ReplayPickScript(int mode);
void ReplayCamInit(GameCamera_t *pCamera, CameraDesc_t *pDesc);
void ReplayCamUninit(GameCamera_t *pCamera);
void ReplayCamUpdate(void *p, GameCamera_t *pCamera);
GameCamera_t *ReplayCamCreate(ReplayCamDesc_t *pDesc);
void ReplayCamSetBallHighlight(Object_80039F5C *p);
void ReplayCamUpdateFocus(void);
void ReplayCamGetMoveOffset(FieldPoint_t *pOut, unsigned int input, float amount);
Block_80170E64 *ReplayCamFindNearestObject(GameCamera_t *pCamera, float *pDist, unsigned char *pFound);
void ReplayCamSetFieldMargins(void);
void ReplayCamApplyDistance(GameCamera_t *pCamera);
void ReplayCamMoveCursor(GameCamera_t *pCamera, unsigned int input, float amount);
GameCamera_t *ReplayCamStart(ReplayCamDesc_t *pDesc);
void ReplayCamPush(GameCamera_t *pCamera);
void ReplayCamProcess(GameCamera_t *pCamera);
void ReplayCamProcessAuto(GameCamera_t *pCamera);
void ReplayCamDestroy(GameCamera_t *pCamera, int detach);
void ReplayCamHandleInput(GameCamera_t *pCamera, int unused, unsigned int input, float amount);
void ReplayCamHandleMenuInput(GameCamera_t *pCamera, int player, unsigned int input, float amount);
void ReplayCamInitDesc(ReplayCamDesc_t *pDesc);
int ReplayBufferNextFrame(void);
void ReplayBufferWriteFrame(int index);
void ReplayReadFrameStub(void);
void ReplayBufferReset(void);
void ReplayRecordFrame(Type_803EA368 *p);
void ReplayBufferFinish(Type_803EA368 *p);
void ReplayHideGameIcons(Type_803EA368 *p);
void ReplayShowGameIcons(Type_803EA368 *p);
void ReplayReadFrame(Type_803EA368 *p);
void ReplayChannelsShutdown(void);
Object_80039F5C *ReplayGetFocusPlayers(Object_80039F5C **ppA, Object_80039F5C **ppB);
void ReplaySetBallIndex(int value);
unsigned char ReplayIsBufferFull(Type_803EA368 *p);
void ReplayCamProcessStub(void);
float ReplayGetFrameBlend(void);
ReplayScriptConds_t *ReplayGetScriptTable(void);
ReplayCommand_t *ReplayFindScript(int id);
}

/* .sdata */
static int _Replay_iFadeTicks = 0;
static unsigned char _Replay_bSavedEventFlag1 = 0;
static unsigned char _Replay_bSavedEventFlag0 = 0;
static unsigned int _Replay_iPlayFrames = 0;
static unsigned char _Replay_bSuspended = 0;
static unsigned char _Replay_bSavedTrails = 0;
static unsigned char _Replay_bStepped = 0;
Type_803EA368 *gpReplay = 0;
static unsigned char _Replay_bDebugWindowOpen = 0;
static int _Replay_iScript = -1;
static unsigned char _Replay_bScriptOption = 0;
static unsigned char _Replay_bDefaultShot = 1;
static unsigned char _Replay_bScriptFlag = 0;
static int _Replay_iScriptWeight = 0;
static int _Replay_iEdgeLimit = 0;
static float _Replay_fFocusHeight = 1.2f;
static unsigned char _Replay_bCamActive = 0;
static int _Replay_iBallIndex = 0;

/* .sbss */
static int _Replay_iCreateCleared;
static int _Replay_iUnreferenced;
static int _Replay_iCamYaw;
static Block_80170E64 *_Replay_pTarget;
static int _Replay_iTargetTime;
static unsigned char _Replay_bTargetIsBall;
static float _Replay_fMaxDist;
static float _Replay_fCamDist;
static unsigned char _Replay_bFreeCam;
static float _Replay_fCamMarginY;
static float _Replay_fCamMarginX;
static float _Replay_fViewMarginX;
static float _Replay_fViewMarginY;
static void *_Replay_pChannels;
static unsigned int _Replay_uBufferSize;
static unsigned int _Replay_uFrameSize;
static unsigned char _Replay_bWrapped;
static int _Replay_iFrameCount;
static int _Replay_iFirstFrame;
static int _Replay_iFrameIndex;
static Object_80039F5C *_Replay_pFocusA;
static Object_80039F5C *_Replay_pFocusB;
static float _Replay_fFrameBlend;

/* .bss */
static ReplayFocus_t _Replay_Focus;

/* .data */
static char _Replay_szFileTag[] = "REPLAY.C";

/* The replay camera's callbacks; 0x802DBDA0 points to this table. */
CamTypeDef_t _Replay_CamType = { ReplayCamInit, ReplayCamUninit, ReplayCamUpdate };

static ReplayCommand_t _Replay_aScript0Commands[] = {
    { 1, 0 }, { 0x26, 0x2D }, { 0x28, 10000 }, { 5, 14 }, { 0x1A, 0 }, { 0x1B, -6 }, { 0x1C, 4 }, { -1, 0 },
};
static ReplayCommand_t _Replay_aScript1Commands[] = {
    { 1, 0 }, { 0x26, 0x2D }, { 0x28, 10000 }, { 5, 14 }, { 0x1A, 0 }, { 0x1B, 6 }, { 0x1C, 4 }, { -1, 0 },
};
static ReplayCommand_t _Replay_aScript3Commands[] = {
    { 1, 0 }, { 0x26, 0x2D }, { 0x28, 10000 }, { 5, 14 }, { 0x1A, 1 }, { 0x1B, 6 }, { 0x1C, 3 }, { -1, 0 },
};
static ReplayCommand_t _Replay_aScript2Commands[] = {
    { 1, 0 }, { 0x26, 0x2D }, { 0x28, 10000 }, { 5, 7 }, { 2, 7 }, { 0x1A, -1 }, { 0x1B, 5 }, { 0x1C, 4 }, { -1, 0 },
};
static ReplayCommand_t _Replay_aScript5Commands[] = {
    { 1, 0 }, { 0x26, 0x2D }, { 0x28, 10000 }, { 5, 7 }, { 2, 4 }, { 0x1A, 0 }, { 0x1B, -5 }, { 0x1C, 4 }, { -1, 0 },
};
static ReplayCommand_t _Replay_aScript4Commands[] = {
    { 1, 0 }, { 0x26, 0x2D }, { 0x28, 10000 }, { 5, 7 }, { 2, 3 }, { 0x1A, -1 }, { 0x1B, -6 }, { 0x1C, 4 }, { -1, 0 },
};
static ReplayCommand_t _Replay_aScript6Commands[] = {
    { 1, 0 }, { 0x26, 0x2D }, { 0x28, 10000 }, { 5, 7 }, { 2, 0x35 }, { 0x1A, 0 }, { 0x1B, 6 }, { 0x1C, 4 }, { -1, 0 },
};

static ReplayScript_t _Replay_aScripts[] = {
    { 0, _Replay_aScript0Commands }, { 1, _Replay_aScript1Commands }, { 3, _Replay_aScript3Commands }, { 2, _Replay_aScript2Commands },
    { 4, _Replay_aScript4Commands }, { 5, _Replay_aScript5Commands }, { 6, _Replay_aScript6Commands }, { -1, 0 },
};

static ReplayCond_t _Replay_aScript01Conds[] = { { 0x19, 100 }, { -1, 0 } };
static ReplayCond_t _Replay_aScript2Conds[] = { { 3, 7 }, { 0x19, 100 }, { -1, 0 } };
static ReplayCond_t _Replay_aScript3Conds[] = { { 3, 0xB }, { 0x19, 100 }, { -1, 0 } };
static ReplayCond_t _Replay_aScript5Conds[] = { { 3, 4 }, { 0x19, 100 }, { -1, 0 } };
static ReplayCond_t _Replay_aScript4Conds[] = { { 3, 3 }, { 0x19, 100 }, { -1, 0 } };
static ReplayCond_t _Replay_aScript6Conds[] = { { 3, 0x35 }, { 0x19, 100 }, { -1, 0 } };

static ReplayScriptConds_t _Replay_aScriptConds[] = {
    { 0, _Replay_aScript01Conds, -1 }, { 1, _Replay_aScript01Conds, -1 }, { 2, _Replay_aScript2Conds, -1 }, { 3, _Replay_aScript3Conds, -1 },
    { 4, _Replay_aScript4Conds, -1 }, { 5, _Replay_aScript5Conds, -1 }, { 6, _Replay_aScript6Conds, -1 }, { -1, 0, 0 },
};

/* Unreferenced on GameCube. The Xbox build has the same eight floats right
   after its copy of _Replay_aScriptConds (0x5012E0), stored into every player
   (+0xEEC) by a function next to the ReplayFindScript counterpart that the
   GameCube link discarded. */
static float _Replay_afPlayerPose[8] = { -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 3.0f, 1.0f, 0.0f };

extern "C" void ReplayDebugWindowOpen(void) {}

extern "C" void ReplayDebugWindowClose(void)
{
    DebugWindowClose();
    _Replay_bDebugWindowOpen = 0;
}

extern "C" unsigned char ReplayDebugWindowIsOpen(void) { return _Replay_bDebugWindowOpen; }

extern "C" void ReplayDebugWindowToggle(void)
{
    if (ReplayDebugWindowIsOpen()) {
        ReplayDebugWindowClose();
    } else {
        ReplayDebugWindowOpen();
    }
}



extern "C" void ReplaySaveGameState(ReplayGameState_t *p)
{
    unsigned char team;
    unsigned int i;
    unsigned int count;
    Object_80039F5C *pObject;

    for (team = 0; team <= 1; team++) {
        count = ScrmGetTeamPlayerCount(team);
        for (i = 0; i < count; i++) {
            pObject = PlyrGet(team, i);
            p->mUnknown000[team][i] = *(Block_80039F5C_B54 *)((char *)pObject + 0xB54);
            p->mUnknown578[team][i] = *(Block_80039F5C_BB8 *)pObject->mRatings;
        }
    }
    p->mUnknown690 = fn_8009D86C();
    p->mUnknown694 = ScrmGetDown();
    p->mUnknown6A4[0] = fn_8009D990(0);
    p->mUnknown6A4[1] = fn_8009D990(1);
    p->mUnknown6A4[2] = fn_8009D990(2);
    p->mUnknown6B0[0] = ScrmGetTeamScore(0);
    p->mUnknown6B0[1] = ScrmGetTeamScore(1);
    p->mUnknown6B4 = BallGetCurrentIndex();
    p->mUnknown698 = ScrmGetBallSpot();
    p->mUnknown6A0 = ScrmGetLineToGain();
    p->mUnknown6B6 = 0;
}

extern "C" void ReplayRestoreGameState(ReplayGameState_t *p)
{
    unsigned char team;
    unsigned int i;
    unsigned int count;
    Object_80039F5C *pObject;

    for (team = 0; team <= 1; team++) {
        count = ScrmGetTeamPlayerCount(team);
        for (i = 0; i < count; i++) {
            pObject = PlyrGet(team, i);
            PauseIsOpen();
            *(Block_80039F5C_B54 *)((char *)pObject + 0xB54) = p->mUnknown000[team][i];
            *(Block_80039F5C_BB8 *)pObject->mRatings = p->mUnknown578[team][i];
        }
    }
    fn_8009D818(p->mUnknown690);
    ScrmSetDown(p->mUnknown694);
    fn_8009D964(0, p->mUnknown6A4[0]);
    fn_8009D964(1, p->mUnknown6A4[1]);
    fn_8009D964(2, p->mUnknown6A4[2]);
    ScrmSetTeamScore(0, p->mUnknown6B0[0]);
    ScrmSetTeamScore(1, p->mUnknown6B0[1]);
    BallSetCurrent(p->mUnknown6B4);
    ScrmSetBallSpot(p->mUnknown698);
    ScrmSetLineToGain(p->mUnknown6A0);
}

extern "C" int ReplayClear(Type_803EA368 *p)
{
    if (p->mUnknownD90 == 2) {
        ReplayEventClearAll(p);
        p->mUnknownD90 = 0;
        memset(p->mUnknown148C, 0, sizeof(p->mUnknown148C));
    }
    return 0;
}

extern "C" int ReplayStartRecording(Type_803EA368 *p)
{
    if (p->mUnknownD90 == 0) {
        ReplaySaveGameState(&p->mUnknown000);
        p->mUnknownD8C = -1;
        p->mUnknownD74 = p->mUnknownD70 = SyncTimeGetGameTime();
        p->mUnknownD90 = 1;
        p->mUnknown14B4 = ScrmIsFieldFlipped();
        ReplaySetBallIndex(BallGetCurrentIndex());
    }
    ReplayStartRecordingStub(p);
    return 0;
}

extern "C" int ReplayStopRecording(Type_803EA368 *p)
{
    if (p->mUnknownD90 == 1) {
        ReplayEventAdd(p, 0x34, 0, 0, 0);
        p->mUnknownD80 = p->mUnknownD7C = SyncTimeGetGameTime();
        ReplayBufferFinish(p);
        p->mUnknownD90 = 2;
        p->mUnknownD94 &= ~0x10;
    }
    return 0;
}

extern "C" int ReplayRecordSkip(Type_803EA368 *p)
{
    return 0;
}

extern "C" void ReplayRecordUpdate(Type_803EA368 *p)
{
    if (p->mUnknownD94 & 0x10) {
        ReplayRecordSkip(p);
    } else if (p->mUnknownD90 == 1) {
        ReplayRecordFrame(p);
    }
    if (p->mUnknownD94 & 0x20) {
        p->mUnknownD94 &= ~0x10;
    }
}

extern "C" int ReplayGetCameraMode(Type_803EA368 *p, int event, int a)
{
    int result = 3;

    switch (event) {
    case 6:
        result = 1;
        break;
    case 7:
        result = 4;
        break;
    case 0x16:
        result = 5;
        break;
    }
    return result;
}

extern "C" void ReplayHandlePlayRequest(Type_803EA368 *p)
{
    ReplayCamDesc_t args;

    ReplayCamInitDesc(&args);
    if (p->mUnknownD94 & 0x80) {
        args.mUnknown00 = ReplayGetCameraMode(p, 7, 0);
        ReplayEnterPlayback(p, &args);
    } else if (p->mUnknownD94 & 0x400000) {
        args.mUnknown00 = ReplayGetCameraMode(p, 0x16, 0);
        ReplayEnterPlayback(p, &args);
    }
}

extern "C" void ReplayUpdateAutoPlay(Type_803EA368 *p)
{
    unsigned int i;

    p->mUnknownD80 = p->mUnknownD80 > p->mUnknownD7C ? p->mUnknownD7C : p->mUnknownD80;
    if (fn_800B81A4() != 0xFF && _Replay_iPlayFrames > 0x1D) {
        p->mUnknownD94 |= 0x200;
    }
    BallsSetVisible(1);
    for (i = 0; i <= 4; i++) {
        if (p->mUnknown148C[i].mUnknown0 == p->mUnknownD74 && p->mUnknownD78 == 0) {
            ReplayTriggerMarkEffect(p->mUnknown148C[i].mUnknown4);
        }
    }
    if (p->mUnknownD74 >= p->mUnknownD80 && p->mUnknownD88 != 0) {
        ReplayReadFrame(p);
        p->mUnknownD88 = 0;
        CamReplayNextRecord();
    }
    _Replay_iFadeTicks += p->mUnknownD88;
    if (_Replay_iFadeTicks > 60) {
        EnvObjUpdateFades();
        ParticleTrailUpdateAll();
        _Replay_iFadeTicks = 0;
    }
    if (p->mUnknownD88 < 60) {
        ParticleSysUpdate(p->mUnknownD88 / 60.0f);
        ParticlesProcess(1.0f);
        fn_800A3120(p->mUnknownD88 / 60.0f);
    } else {
        ParticleSysUpdate(1.0f);
        ParticlesProcess(1.0f);
        fn_800A3120(p->mUnknownD88 / 60.0f);
    }
    FieldLinesUpdate();
    if (p->mUnknownD94 & 0x200) {
        if (_Replay_iPlayFrames > 0x1D) {
            ReplayExitPlayback(p);
            AudmonEventPost(0x7F, 0);
            PauseSetPollDelay(4);
        }
    } else if (p->mUnknownD88 > 0) {
        ReplayStepForward(p, p->mUnknownD88);
    } else if (p->mUnknownD88 < 0) {
        ReplayStepBackward(p, p->mUnknownD88);
    }
    if (p->mpUnknownDA0) {
        ReplayCamProcessAuto(p->mpUnknownDA0);
    }
}

extern "C" void ReplayUpdateUserPlay(Type_803EA368 *p)
{
    unsigned short a;
    unsigned short b;

    _Replay_bStepped = 0;
    if (p->mUnknownD74 >= p->mUnknownD7C && p->mUnknownD8C == -1) {
        p->mUnknownD94 |= 0x200;
    }
    if (_Replay_bSuspended == 0) {
        fn_80219650(gUISMainInfo, &a, &b);
        if (fn_800B81A4() != 0xFF) {
            p->mUnknownD94 |= 0x200;
        }
        FieldLinesUpdate();
        if (p->mUnknownD94 & 0x1000200) {
            if (_Replay_iPlayFrames > 0x1D) {
                ReplayExitPlayback(p);
            }
        } else if (!(p->mUnknownD94 & 0x100) && (p->mUnknownD94 & 0xF000)) {
            if (p->mUnknownD88 > 0) {
                ReplayStepForward(p, p->mUnknownD88);
                _Replay_iFadeTicks += p->mUnknownD88;
            } else if (p->mUnknownD88 < 0) {
                ReplayStepBackward(p, p->mUnknownD88);
                _Replay_iFadeTicks -= p->mUnknownD88;
            }
            if (_Replay_iFadeTicks > 60) {
                EnvObjUpdateFades();
                ParticleTrailUpdateAll();
                _Replay_iFadeTicks = 0;
            }
            ParticleSysUpdate(p->mUnknownD88 / 60.0f);
            ParticlesFlush();
            fn_800A3120(p->mUnknownD88 / 60.0f);
            _Replay_bStepped = 1;
        }
        if (p->mUnknownD94 & 0x2000000) {
            ReplayDirectorUpdate(p);
        }
        if (p->mpUnknownDA0) {
            ReplayCamProcess(p->mpUnknownDA0);
        }
    }
}

extern "C" int ReplayEnterPlayback(Type_803EA368 *p, ReplayCamDesc_t *pDesc)
{
    int result = -1;

    _Replay_iPlayFrames = 0;
    if (p->mUnknownD90 == 2 || (p->mUnknownD94 & 0x400000)) {
        if (p->mUnknownD94 & 0x400000) {
            p->mUnknownD94 |= 0x800000;
        } else {
            SndgSfxPlay(0x77, 0);
            InGamePause();
            PauseBlock();
            ReplaySaveGameState(&p->mUnknown6B8);
            ReplayRestoreGameState(&p->mUnknown000);
            if ((p->mUnknownD94 & 0x2000000) && ScrmIsFieldFlipped()) {
                ScrmMirrorField(0, 0);
            }
            fn_800B50E8(0);
            fn_800B50E8(1);
            PlyrMgrSetLeadFlags();
            DivotSaveState();
            p->mUnknownD78 = 0;
            p->mUnknownD74 = p->mUnknownD70;
            ReplayHideGameIcons(p);
            if (!(p->mUnknownD94 & 0x10000)) {
                ReplayReadFrame(p);
                SndgMusicResume();
                SndgMusicSetMode(0xC);
            }
            HudHide();
            p->mUnknownD90 = 4;
        }
        if (p->mUnknownD94 & 0x2000000) {
            ReplayDirectorEnter();
        }
        ReplayTakeControllerInput(p);
        p->mpUnknownDA0 = ReplayCamStart(pDesc);
        ReplayCamProcess(p->mpUnknownDA0);
        if (p->mUnknown14B4 && !(p->mUnknownD94 & 0x400000)) {
            CamMainRotate(p->mpUnknownDA0, 0x800000);
            CamMainProcess(p->mpUnknownDA0, 0, 0, 0);
            CamMainWarpToDest(p->mpUnknownDA0);
        }
        _Replay_bSavedEventFlag1 = GameEventFlagsSetFlag1(0);
        _Replay_bSavedEventFlag0 = GameEventFlagsSetFlag0(2);
        fn_800A8644();
        ParticlesStopOnEnter();
        result = 0;
    }
    _Replay_bSavedTrails = ParticleTrailSetEnabled(0);
    ReplayDebugWindowOpen();
    return result;
}

extern "C" int ReplayExitPlayback(Type_803EA368 *p)
{
    int result = -1;
    GameCamera_t *pCamera;

    ParticleTrailSetEnabled(_Replay_bSavedTrails);
    if (p->mUnknownD90 == 4 || (p->mUnknownD94 & 0x1000000)) {
        if (p->mUnknownD94 & 0x1000000) {
            p->mUnknownD94 &= ~0x800000;
        } else {
            ReplayRestoreGameState(&p->mUnknown6B8);
            HudUnhide();
            if ((p->mUnknownD94 & 0x2000000) && ScrmIsFieldFlipped()) {
                CamGameResumeAll();
            }
            if (!(p->mUnknownD94 & 0x10000)) {
                SndgSfxPlay(0x78, 0);
                SndgMusicSetMode(0xD);
                PauseSetPollDelay(4);
            }
            if (PauseIsOpen() == 0) {
                fn_800B50E8(0);
                fn_800B50E8(1);
            }
            PlyrMgrClearLeadFlags();
            PlyrMgrRefreshModels();
            DivotRestoreState();
            p->mUnknownD94 &= ~0x1000;
            p->mUnknownD94 &= ~0x10000;
            ReplayShowGameIcons(p);
            p->mUnknownD8C = -1;
            p->mUnknownD90 = 2;
            InGameResume();
            PauseUnblock();
        }
        if (p->mUnknownD94 & 0x2000000) {
            p->mUnknownD94 &= ~0x2000000;
            ReplayDirectorExit();
        }
        ReplayReleaseControllerInput(p);
        pCamera = p->mpUnknownDA0;
        ReplayCamDestroy(pCamera, VptManagerGetCurrentCamera(GameVpt::GetViewport()) == p->mpUnknownDA0);
        p->mpUnknownDA0 = 0;
        GameEventFlagsSetFlag1(_Replay_bSavedEventFlag1);
        GameEventFlagsSetFlag0(_Replay_bSavedEventFlag0);
        fn_800A866C();
        ParticlesStopOnLeave();
        SndgEventReloadCrowdBanks();
        result = 0;
    }
    ReplayDebugWindowClose();
    return result;
}

extern "C" void ReplayRefreshFrame(Type_803EA368 *p)
{
    SyncTimeGetGameTime();
    ReplayReadFrame(p);
}

extern "C" void ReplayStepBackward(Type_803EA368 *p, int delta)
{
    p->mUnknownD78 += delta;
    while (p->mUnknownD78 <= -60) {
        p->mUnknownD78 += 60;
        if (p->mUnknownD74 > p->mUnknownD70) {
            p->mUnknownD74--;
        }
    }
    if (p->mUnknownD74 == p->mUnknownD70) {
        p->mUnknownD78 = 0;
    }
    ReplayRefreshFrame(p);
}

extern "C" void ReplayStepForward(Type_803EA368 *p, int delta)
{
    p->mUnknownD78 += delta;
    while (p->mUnknownD78 >= 60) {
        p->mUnknownD78 -= 60;
        if (p->mUnknownD74 < p->mUnknownD7C) {
            p->mUnknownD74++;
        }
    }
    if (p->mUnknownD74 == p->mUnknownD7C) {
        p->mUnknownD78 = 0;
    }
    ReplayRefreshFrame(p);
}

extern "C" void ReplayTakeControllerInput(Type_803EA368 *p)
{
    PadInputSaveHandlers(p->mUnknownDA8);
    if (!InGameIsDemo() && p->mUnknownD8C != -1) {
        ConSetChannelInfo(9, 0, ConGetChannelInfo(p->mUnknownD8C, 0));
        ConSetChannelInfo(9, 2, (int)PadInputRead);
        ConSetChannelInfo(9, 4, 1);
        ConSetChannelInfo(-1, 3, (int)lbl_802EC330);
        RemapCopyTable(9, p->mUnknownD8C);
    }
}

extern "C" void ReplayReleaseControllerInput(Type_803EA368 *p)
{
    PadInputRestoreHandlers(p->mUnknownDA8);
    PadInputResetSlot(-1);
    if (!InGameIsDemo()) {
        ConSetChannelInfo(9, 4, 0);
    }
}

extern "C" void ReplayTriggerMarkEffect(int type)
{
    switch (type) {
    case 0:
        break;
    case 1:
        SndgEventOnReplayCase1();
        break;
    case 2:
        SndgEventOnReplayCase2();
        break;
    case 3:
        break;
    case 4:
        SndgEventPlayReplaySfx(8);
        break;
    case 5:
        SndgEventPlayReplaySfx(9);
        break;
    }
}

extern "C" Type_803EA368 *ReplayCreate(void)
{
    Type_803EA368 *p;

    p = (Type_803EA368 *)fn_801D2B7C(sizeof(Type_803EA368), 0, 0);
    memset(p, 0, sizeof(Type_803EA368));
    p->mUnknownD7C = 0;
    p->mUnknownD70 = 0;
    p->mUnknownD78 = 0;
    p->mUnknownD74 = 0;
    p->mUnknownD94 = 0;
    p->mpUnknownDA0 = 0;
    p->mUnknownD90 = 2;
    ReplayClear(p);
    p->mUnknown14B5 = 0;
    p->mUnknownD98 = -1;
    _Replay_iCreateCleared = 0;
    memset(p->mUnknown148C, 0, sizeof(p->mUnknown148C));
    ConSetChannelInfo(9, 4, 0);
    return p;
}

extern "C" void ReplayDestroy(Type_803EA368 *p)
{
    ReplayStopRecording(p);
    ReplayExitPlayback(p);
    ReplayChannelsShutdown();
    fn_801D2BD0(p);
}

extern "C" void ReplayStartRecordingStub(Type_803EA368 *p)
{
}


extern "C" int ReplayHandleCommand(Type_803EA368 *p, int msg, int value)
{
    int result = -1;

    if (p == 0) {
        return -2;
    }
    if (p->mUnknownD90 != 4) {
        switch (msg) {
        case 3:
            result = 0;
            ReplayStopRecording(p);
            break;
        case 1:
            p->mUnknownD94 |= 2;
            result = 0;
            ReplayClear(p);
            break;
        case 2:
            p->mUnknownD94 |= 4;
            result = 0;
            ReplayStartRecording(p);
            ReplayBufferReset();
            break;
        default:
            p->mUnknownD94 |= 1 << msg;
            result = 0;
            break;
        }
    }
    return result;
}

extern "C" int ReplayHandleControl(Type_803EA368 *p, int msg, int value)
{
    int result = -1;

    switch (msg) {
    case 10:
        p->mUnknownD8C = value;
        break;
    case 11:
        p->mUnknownD94 |= 0x800;
        result = 0;
        break;
    case 7:
        if (p->mUnknownD90 == 2) {
            result = 0;
            p->mUnknownD94 &= ~0x800;
            p->mUnknownD94 &= ~0x100;
            p->mUnknownD94 |= 0x80;
            _Replay_iFadeTicks = 0;
        }
        break;
    case 25:
        p->mUnknownD94 |= 0x2000000;
        result = 0;
        break;
    case 8:
        if (p->mUnknownD90 == 4) {
            if (p->mUnknownD94 & 0x100) {
                p->mUnknownD94 &= ~0x100;
            } else {
                p->mUnknownD94 |= 0x100;
            }
            result = 0;
        }
        break;
    case 9:
        if (p->mUnknownD90 == 4) {
            p->mUnknownD94 = (p->mUnknownD94 | 1 << msg) & ~0x100;
            result = 0;
            if (p->mUnknown14B5) {
                p->mUnknown14B5 = 0;
            }
        }
        break;
    case 22:
    case 24:
        p->mUnknownD94 |= 1 << msg;
        result = 0;
        break;
    }
    return result;
}

extern "C" void ReplayHandleInput(Type_803EA368 *p, int a, unsigned int id, float value)
{
    if (a == 9) {
        MemCardUtilHandleEvent(9, id, value);
        if (p->mUnknownD94 & 0x10000) {
            if (p->mUnknownD90 == 4) {
                switch (id) {
                case 0: /* 0 and 1: the cmplwi 1 test at 0x8002CC10 */
                case 1:
                    break;
                case 6:
                    if (value == 1.0f) {
                        if (p->mUnknownD88 == 15) {
                            p->mUnknownD88 = 45;
                        } else {
                            p->mUnknownD88 = 15;
                        }
                    }
                    break;
                case 8:
                    if (value == 1.0f) {
                        ReplaySetEndHere(p);
                    }
                    break;
                case 9:
                    if (value == 1.0f && ReplayPickScript(1)) {
                        RecordList_8002E7C0 *pList = &p->mpUnknownDA0->mUnknown128;

                        ReplayShotListClear(pList);
                        ReplayBuildShotList(p, pList);
                        ReplayShotListStart(p, pList);
                        p->mUnknownD74 = p->mUnknownD70;
                        p->mUnknownD78 = 0;
                        CamMainSetMode(p->mpUnknownDA0, 8, 0, 0);
                    }
                    break;
                case 10: /* placeholder values: the compare tree needs two */
                case 11: /* empty labels above 9; values not recovered */
                    break;
                }
            }
            return;
        }
        if (p->mUnknownD94 & 0x100) {
            UISGameHandleInput(9, id, value);
            return;
        }
        if (p->mUnknownD94 & 0x800000) {
            ReplayCamHandleMenuInput(p->mpUnknownDA0, 9, id, value);
            UISGameHandleInput(9, id, value);
            return;
        }
        if ((p->mUnknownD94 & 0x2000000) && ReplayDirectorIsActive()) {
            ReplayDirectorHandleInput(p, 9, id, value);
            return;
        }
        if (p->mUnknownD94 & 0x200) {
            return;
        }
        {
            unsigned short s0;
            unsigned short s1;

            ReplayCamHandleInput(p->mpUnknownDA0, a, id, value);
            fn_80219650(gUISMainInfo, &s0, &s1);
            UISGameHandleInput(a, id, value);
        }
        if (id == 0 && _Replay_iPlayFrames > 29) {
            p->mUnknownD94 |= 0x200;
            HudPost3AOn();
        }
        switch (id) {
        case 0x50:
            if (value == 1.0f) {
                if (HudIsHidden()) {
                    HudShowOverlay();
                } else {
                    HudHideOverlay();
                }
            }
            break;
        case 0x4B:
            if (p->mUnknownD94 & 0x1000) {
                p->mUnknownD94 &= ~0x1000;
                p->mUnknownD88 = 0;
            } else {
                p->mUnknownD94 |= 0x1000;
                p->mUnknownD88 = 60;
            }
            break;
        case 0x3B:
        case 0x4C:
            p->mUnknownD94 = (p->mUnknownD94 & ~0x1000) | 0x2000;
            if (value < 1.0f) {
                p->mUnknownD88 = (int)(-value * 90.0f);
            } else {
                p->mUnknownD88 = (int)(-value * 180.0f);
            }
            break;
        case 0x3C:
        case 0x4E:
            p->mUnknownD94 = (p->mUnknownD94 & ~0x1000) | 0x4000;
            p->mUnknownD88 = (int)(value * (value < 1.0f ? 90.0f : 180.0f));
            break;
        case 0x15:
            if (value == 1.0f) {
                ReplayDebugWindowToggle();
            }
            break;
        }
    }
}

extern "C" void ReplayUpdate(Type_803EA368 *p)
{
    int state = p->mUnknownD90;

    if (state == 4 || (p->mUnknownD94 & 0x800000)) {
        _Replay_iPlayFrames++;
        if (p->mUnknownD94 & 0x10000) {
            ReplayUpdateAutoPlay(p);
        } else {
            ReplayUpdateUserPlay(p);
        }
    } else {
        if (state == 1 && fn_800AD9B4() != 3 && ReplayIsBufferFull(p)) {
            ReplayStopRecording(p);
        }
        ReplayRecordUpdate(p);
        ReplayHandlePlayRequest(p);
    }
    p->mUnknownD94 &= 0x2811950;
}

extern "C" void ReplayStartAutoPlayback(Type_803EA368 *p)
{
    ReplayCamDesc_t args;

    args.mUnknown00 = 1;
    args.mUnknown04 = 1;
    args.mUnknown08 = 1;
    p->mUnknownD84 = SysGetSystemTime();
    p->mUnknownD94 = (p->mUnknownD94 | 0x10000) & ~0x40;
    ReplayCursorSetVisible(0);
    ReplayEnterPlayback(p, &args);
}

extern "C" unsigned char ReplayIsStepping(void) { return _Replay_bStepped; }

extern "C" unsigned char ReplayIsShowing(Type_803EA368 *p)
{
    unsigned char result = 0;

    if (p != 0) {
        result = (p->mUnknownD90 == 4);
        result |= (p->mUnknownD94 >> 7) & 1;
        result |= (p->mUnknownD94 >> 11) & 1;
        result |= (p->mUnknownD94 >> 22) & 1;
        result |= (p->mUnknownD94 >> 23) & 1;
    }
    return result;
}

extern "C" int ReplayIsRecording(Type_803EA368 *p)
{
    int result = 0;

    if (p != 0) {
        result = p->mUnknownD90 == 1;
    }
    return result;
}

extern "C" int ReplayGetLength(Type_803EA368 *p)
{
    int result = 0;

    if (p->mUnknownD90 == 2 || p->mUnknownD90 == 4) {
        result = p->mUnknownD7C - p->mUnknownD70;
    }
    return result;
}

extern "C" int ReplayGetPosition(Type_803EA368 *p)
{
    int result = 0;

    if (p->mUnknownD90 == 2 || p->mUnknownD90 == 4) {
        result = p->mUnknownD74 - p->mUnknownD70;
    }
    return result;
}

extern "C" void ReplaySetSpeed(Type_803EA368 *p, int value)
{
    p->mUnknownD88 = value;
    p->mUnknownD88 = CLAMP(p->mUnknownD88, -120, 120);
}

extern "C" int ReplayGetSpeed(Type_803EA368 *p) { return p->mUnknownD88; }

extern "C" int ReplayGetStartFrame(Type_803EA368 *p) { return p->mUnknownD70; }

extern "C" void ReplaySetPlayEnd(Type_803EA368 *p, int value)
{
    p->mUnknownD80 = p->mUnknownD74 + value;
    p->mUnknownD80 = CLAMP(p->mUnknownD80, p->mUnknownD70, p->mUnknownD7C);
}

extern "C" int ReplayRequestExit(Type_803EA368 *p)
{
    if (_Replay_iPlayFrames > 29) {
        p->mUnknownD94 |= 0x200;
    }
    return 0;
}

extern "C" int ReplaySeek(Type_803EA368 *p, int value)
{
    if (value < p->mUnknownD70) {
        value = p->mUnknownD70;
    } else if (value > p->mUnknownD7C - 1) {
        value = p->mUnknownD7C - 1;
    }
    p->mUnknownD74 = value;
    PlyrPoseSetBlendFlag(0);
    ReplayReadFrame(p);
    PlyrPoseSetBlendFlag(1);
    return 0;
}

extern "C" int ReplayIsHalted(Type_803EA368 *p)
{
    // FAKEMATCH: compiled-out entry assert; its empty do-while keeps the +0xD94 load ahead of +0xD90
    REPLAY_ASSERT(p != 0);
    return ((p->mUnknownD94 >> 8) & 1) | (((p->mUnknownD94 >> 9) & 1) | (p->mUnknownD90 == 2));
}

extern "C" void ReplaySetEndHere(Type_803EA368 *p)
{
    if (p->mUnknownD74 - p->mUnknownD70 > 2) {
        p->mUnknownD80 = p->mUnknownD74;
        p->mUnknownD88 = 60;
    }
}

extern "C" void ReplayStopAndClear(Type_803EA368 *p)
{
    ReplayHandleCommand(p, 3, 0);
    ReplayHandleCommand(p, 1, 0);
    ReplayUpdate(p);
}

extern "C" unsigned char ReplayIsSuspended(void) { return _Replay_bSuspended; }

extern "C" void ReplaySetHoldFlag(Type_803EA368 *p, unsigned char value) { p->mUnknown14B5 = value; }

/* Debug-window callbacks for the highlighted player (Xbox 0x20830 and
   0x209F0, PS2 0x1B4F30). Nothing on GameCube installs them, so the linker
   drops both; only their strings remain (0x8028A9F0-0x8028AB28). The PS2
   build reads the two animation tables through out-of-line getters of the
   PlyrAnimTurn.cpp file (0x271490, 0x2714C0) that GameCube also discards; with
   no GameCube address for them, the tables are read directly here, as the
   Xbox build does after inlining. State is taken from the lower table as on
   PS2 (Xbox reads the two the other way round). The window calls this slot
   with three arguments on both platforms (GameCube DebugWindowHandleMsg sets r3-r5
   before the call at 0x8017F8CC; Xbox 0x17C502 pushes three through
   0x623644); the bodies read only the first two. This code is not
   measured. */
static void PrintPlayerDebugLine(int line, char *pBuf, int)
{
    int id;
    Object_80039F5C *p;

    PlyrObjsGetPlayerRef(GetHighlightedObject(), &id);
    p = fn_8009BCE8(&id);
    if (p != 0) {
        switch (line) {
        case 0:
            sprintf(pBuf, "O-Moves: %d     Jumping: %d", p->mRatings[0], p->mRatings[1]);
            break;
        case 1:
            sprintf(pBuf, "Run Power: %d   Catching: %d", p->mRatings[2], p->mRatings[3]);
            break;
        case 2:
            sprintf(pBuf, "Speed: %d       Tackling: %d", p->mRatings[4], p->mRatings[5]);
            break;
        case 3:
            sprintf(pBuf, "Passing: %d     Blocking: %d", p->mRatings[6], p->mRatings[7]);
            break;
        case 4:
            sprintf(pBuf, "Coverage: %d    D-Moves: %d", p->mRatings[8], p->mRatings[9]);
            break;
        case 5:
            sprintf(pBuf, "State: 0x%04X    Anim: %d",
                    lbl_803192BC[(p->mId >> 8) & 0xFF][(p->mId >> 16) & 0xFF],
                    lbl_803192D8[(p->mId >> 8) & 0xFF][(p->mId >> 16) & 0xFF]);
            break;
        default:
            pBuf[0] = 0;
            break;
        }
    } else {
        switch (line) {
        case 0:
            sprintf(pBuf, "Highlight a player for debug info.");
            break;
        case 2:
            sprintf(pBuf, "Press Z to toggle this window.");
            break;
        default:
            pBuf[0] = 0;
            break;
        }
    }
}

static void PrintDebugHelpLine(int line, char *pBuf, int, int *pCount)
{
    *pCount = 4;
    switch (line) {
    case 0:
        sprintf(pBuf, "Highlight a player for debug info");
        break;
    case 2:
        sprintf(pBuf, "Press Z to toggle this window.");
        break;
    case 4:
        sprintf(pBuf, "(Nothing else to see here)");
        break;
    default:
        pBuf[0] = 0;
        break;
    }
}

extern "C" void ReplayDirectorEnter(void) {}

extern "C" void ReplayDirectorExit(void) {}

extern "C" int ReplayDirectorIsActive(void) { return 0; }

extern "C" void ReplayDirectorHandleInput(Type_803EA368 *p, int a, unsigned int id, float value) {}

extern "C" void ReplayDirectorUpdateFocus(ReplayFocus_t *p, Block_80170E64 **ppTarget) {}

extern "C" void ReplayDirectorUpdate(Type_803EA368 *p) {}

extern "C" void ReplayShotListStartStub(void) {}

extern "C" void ReplaySetEventMark(Type_803EA368 *p, int id, int value, int index)
{
    p->mUnknown148C[index].mUnknown0 = ReplayEventGetTime(p, id);
    p->mUnknown148C[index].mUnknown4 = value;
}

extern "C" void ReplayInitShotTimer(Type_803EA368 *p, Timer_8002E7C0 *pTimer)
{
    pTimer->mUnknown00 = ReplayGetStartFrame(p);
    pTimer->mUnknown08 = ReplayGetLength(p);
    pTimer->mUnknown0C = 45;
    pTimer->mUnknown04 = 0;
    if (ReplayEventExists(p, 0x25)) {
        int end = ReplayEventGetTime(p, 0x25) + 150;

        pTimer->mUnknown08 = end - ReplayGetStartFrame(p);
    }
}

extern "C" Record_8002E7C0 *ReplayShotListAdd(RecordList_8002E7C0 *pList)
{
    Record_8002E7C0 *pRecord = 0;

    if (pList->mUnknown57C <= 8) {
        pRecord = &pList->mUnknown000[pList->mUnknown57C++];
        memset(pRecord, 0, sizeof(Record_8002E7C0));
    }
    return pRecord;
}

extern "C" float ReplayEventDeltaY(int a, int b)
{
    float va[3];
    float vb[3];
    float result;

    if (ReplayEventInWindow(gpReplay, a) && ReplayEventInWindow(gpReplay, b)) {
        ReplayEventGetPos(gpReplay, a, va);
        ReplayEventGetPos(gpReplay, b, vb);
        result = vb[1] - va[1];
    } else {
        result = 0.0f;
    }
    return result;
}

extern "C" int ReplayTestConditions(ReplayCond_t *pCond)
{
    int last = -1;
    int sum = 0;
    int minGap = -3600;
    int maxGap = 7200;
    unsigned char ordered = 0;
    int minDy = -150;
    int maxDy = 150;
    int ok = 1;
    int needMatch = 0;
    int matched = 0;
    int hasCall = 0;
    int flag = 0;
    int callA = 0;
    int callB = 0;
    unsigned char value374 = 0;

    for (; pCond->mOp != -1; pCond++) {
        if (!ok) {
            return 0;
        }
        switch (pCond->mOp) {
        case 0:
            ordered = pCond->mArgLow;
            break;
        case 1:
            minGap = pCond->mArg;
            break;
        case 2:
            maxGap = pCond->mArg;
            break;
        case 3:
            if (needMatch && !matched) {
                ok = 0;
            }
            needMatch = 0;
            matched = 0;
            if (!ReplayEventInWindow(gpReplay, pCond->mArg)) {
                ok = 0;
                break;
            }
            if (last != -1) {
                if (ordered && ReplayEventGetTime(gpReplay, last) > ReplayEventGetTime(gpReplay, pCond->mArg)) {
                    ok = 0;
                }
                if (minDy > ReplayEventDeltaY(last, pCond->mArg)) {
                    ok = 0;
                }
                if (maxDy < ReplayEventDeltaY(last, pCond->mArg)) {
                    ok = 0;
                }
                if (minGap > ABS(ReplayEventGetTime(gpReplay, last) - ReplayEventGetTime(gpReplay, pCond->mArg))) {
                    ok = 0;
                }
                if (maxGap < ABS(ReplayEventGetTime(gpReplay, last) - ReplayEventGetTime(gpReplay, pCond->mArg))) {
                    ok = 0;
                }
            }
            last = pCond->mArg;
            break;
        case 4:
            if (ReplayEventInWindow(gpReplay, pCond->mArg)) {
                ok = 0;
            }
            break;
        case 5:
            if (last == -1) {
                ok = 0;
            } else {
                Object_80039F5C *pObject;

                needMatch = 1;
                pObject = ReplayEventGetObject(gpReplay, last);
                if (pObject == 0) {
                    ok = 0;
                } else if (pObject->mUnknown2914 == pCond->mArg) {
                    matched = 1;
                }
            }
            break;
        case 6:
            if (last == -1) {
                ok = 0;
            } else {
                float pos[3] = { 0.0f };

                if (ReplayEventGetPos(gpReplay, last, pos) == -1 || pos[0] < pCond->mArg) {
                    ok = 0;
                }
            }
            break;
        case 8:
            if (last == -1) {
                ok = 0;
            } else {
                float pos[3] = { 0.0f };

                if (ReplayEventGetPos(gpReplay, last, pos) == -1 || pos[0] > pCond->mArg) {
                    ok = 0;
                }
            }
            break;
        case 7:
            if (last == -1) {
                ok = 0;
            } else {
                float pos[3] = { 0.0f };

                if (ReplayEventGetPos(gpReplay, last, pos) == -1 || pos[1] < pCond->mArg) {
                    ok = 0;
                }
            }
            break;
        case 9:
            if (last == -1) {
                ok = 0;
            } else {
                float pos[3] = { 0.0f };

                if (ReplayEventGetPos(gpReplay, last, pos) == -1 || pos[1] > pCond->mArg) {
                    ok = 0;
                }
            }
            break;
        case 11:
            minDy = pCond->mArg;
            break;
        case 10:
            maxDy = pCond->mArg;
            break;
        case 12: /* placeholder values; see the source-form row */
        case 13:
            break;
        case 14:
            if (ScrmGetPlayDown() < pCond->mArg) {
                ok = 0;
            }
            break;
        case 15:
            if (ScrmGetPlayDown() > pCond->mArg) {
                ok = 0;
            }
            break;
        case 16:
        case 17:
            break;
        case 18:
            if (fn_8009D86C() < pCond->mArg) {
                ok = 0;
            }
            break;
        case 19:
            if (fn_8009D990(1) > pCond->mArg) {
                ok = 0;
            }
            break;
        case 20:
        case 21:
            break;
        case 22: {
            int gap = pCond->mArg;

            if (ABS(ScrmGetTeamScore(0) - ScrmGetTeamScore(1)) < gap) {
                ok = 0;
            }
            break;
        }
        case 23: {
            int gap = pCond->mArg;

            if (ABS(ScrmGetTeamScore(0) - ScrmGetTeamScore(1)) > gap) {
                ok = 0;
            }
            break;
        }
        case 25:
            sum += pCond->mArg;
            break;
        case 26:
            break;
        case 27:
            value374 = pCond->mArgLow;
            break;
        case 30:
            flag = 1;
            break;
        case 24:
            if (pCond->mArg) {
                if (ScrmGetTeamScore(ScrmGetOffenseTeam()) <= ScrmGetTeamScore(ScrmGetDefenseTeam())) {
                    ok = 0;
                }
            } else {
                if (ScrmGetTeamScore(ScrmGetOffenseTeam()) >= ScrmGetTeamScore(ScrmGetDefenseTeam())) {
                    ok = 0;
                }
            }
            break;
        case 31:
            if (PlayBookGetPlay(ScrmGetSnapOffense())->mUnknown14 != pCond->mArg) {
                ok = 0;
            }
            break;
        case 32:
            needMatch = 1;
            if (ReplayEventGetObject(gpReplay, pCond->mArg)) {
                ok = 0;
            }
            break;
        case 28:
            hasCall = 1;
            callA = pCond->mArg;
            break;
        case 29:
            callB = pCond->mArg;
            break;
        }
    }
    if (needMatch && !matched) {
        ok = 0;
    }
    if (ok) {
        _Replay_iScriptWeight = sum;
        _Replay_bScriptOption = value374;
        _Replay_bScriptFlag = flag;
        if (hasCall) {
            fn_8009BB50(callA, callB);
        }
    } else {
        _Replay_iScriptWeight = 0;
    }
    return ok;
}

extern "C" void ReplayBuildShotList(Type_803EA368 *p, RecordList_8002E7C0 *pList)
{
    Record_8002E7C0 *pRecord = 0;
    Timer_8002E7C0 *pTimer = 0;
    int last = -1;
    int count = 0;
    ReplayCommand_t *pCmd;
    Vector_80039F5C origin;
    FieldPoint_t pt;
    float range[3];

    pt = ScrmGetBallSpot();
    origin.mX = pt.mX;
    origin.mY = pt.mY;
    origin.mZ = 0.0f;

    pCmd = ReplayFindScript(_Replay_iScript);
    if (pCmd == 0) {
        return;
    }
    while (pCmd->mOp != -1) {
        switch (pCmd->mOp) {
        case 1:
            pRecord = ReplayShotListAdd(pList);
            pTimer = &pRecord->mUnknown04;
            pRecord->mUnknown00 = 0;
            ReplayInitShotTimer(p, pTimer);
            pTimer->mUnknown08 = 0;
            pRecord->mUnknown1C.mUnknown34 = 0;
            pRecord->mUnknown1C.mUnknown00[0] = 0.0f;
            pRecord->mUnknown1C.mUnknown00[1] = 55.0f;
            pRecord->mUnknown1C.mUnknown00[2] = 30.0f;
            pRecord->mUnknown1C.mUnknown18 = 45.0f;
            pRecord->mUnknown1C.mUnknown1C[0] = origin.mX;
            pRecord->mUnknown1C.mUnknown1C[1] = origin.mY;
            pRecord->mUnknown1C.mUnknown1C[2] = origin.mZ;
            pRecord->mUnknown5C.mUnknown34 = 0;
            pRecord->mUnknown5C.mUnknown00[0] = 0.0f;
            pRecord->mUnknown5C.mUnknown00[1] = 55.0f;
            pRecord->mUnknown5C.mUnknown00[2] = 30.0f;
            pRecord->mUnknown5C.mUnknown18 = 45.0f;
            pRecord->mUnknown5C.mUnknown1C[0] = origin.mX;
            pRecord->mUnknown5C.mUnknown1C[1] = origin.mY;
            pRecord->mUnknown5C.mUnknown1C[2] = origin.mZ;
            break;
        case 2:
            pRecord->mUnknown1C.mUnknown38 = ReplayEventGetObject(p, pCmd->mArg);
            break;
        case 3:
            if (pCmd->mArg <= 4) {
                pList->mUnknown584 |= 1 << pCmd->mArg;
            } else {
                pRecord->mUnknown18 |= 1 << pCmd->mArg;
            }
            break;
        case 4:
            pRecord->mUnknown00 = pCmd->mArg;
            _Replay_bDefaultShot = 0;
            break;
        case 9:
            ReplayEventGetPos(p, pCmd->mArg, pRecord->mUnknown1C.mUnknown1C);
            break;
        case 0xA:
            *(Vector_80039F5C *)pRecord->mUnknown1C.mUnknown1C = origin;
            break;
        case 0xB:
            pRecord->mUnknown1C.mUnknown1C[0] = pCmd->mArg;
            break;
        case 0xC:
            pRecord->mUnknown1C.mUnknown1C[1] = pCmd->mArg;
            break;
        case 0xD:
            pRecord->mUnknown1C.mUnknown1C[2] = pCmd->mArg;
            break;
        case 0xE:
            pRecord->mUnknown1C.mUnknown1C[0] += pCmd->mArg;
            break;
        case 0xF:
            pRecord->mUnknown1C.mUnknown1C[1] += pCmd->mArg;
            break;
        case 0x10:
            pRecord->mUnknown1C.mUnknown1C[2] += pCmd->mArg;
            break;
        case 0x11:
            ReplayEventGetPos(p, pCmd->mArg, pRecord->mUnknown1C.mUnknown28);
            break;
        case 0x12:
            pRecord->mUnknown1C.mUnknown28[0] = pCmd->mArg;
            break;
        case 0x13:
            pRecord->mUnknown1C.mUnknown28[1] = pCmd->mArg;
            break;
        case 0x14:
            pRecord->mUnknown1C.mUnknown28[2] = pCmd->mArg;
            break;
        case 0x15:
            pRecord->mUnknown1C.mUnknown28[0] += pCmd->mArg;
            break;
        case 0x16:
            pRecord->mUnknown1C.mUnknown28[1] += pCmd->mArg;
            break;
        case 0x17:
            pRecord->mUnknown1C.mUnknown28[2] += pCmd->mArg;
            break;
        case 5:
            pRecord->mUnknown1C.mUnknown34 = pCmd->mArg;
            break;
        case 6:
            _Replay_bDefaultShot = 0;
        case 0x29:
            pRecord->mUnknown1C.mUnknown3C = pCmd->mArg;
            break;
        case 0x18:
            ReplayEventGetPos(p, pCmd->mArg, pRecord->mUnknown1C.mUnknown00);
            break;
        case 0x19:
            *(Vector_80039F5C *)pRecord->mUnknown1C.mUnknown00 = origin;
            break;
        case 0x1A:
            pRecord->mUnknown1C.mUnknown00[0] = pCmd->mArg;
            break;
        case 0x1D:
            pRecord->mUnknown1C.mUnknown00[0] += pCmd->mArg;
            break;
        case 0x1B:
            pRecord->mUnknown1C.mUnknown00[1] = pCmd->mArg;
            break;
        case 0x1E:
            pRecord->mUnknown1C.mUnknown00[1] += pCmd->mArg;
            break;
        case 0x1C:
            pRecord->mUnknown1C.mUnknown00[2] = pCmd->mArg;
            break;
        case 0x1F:
            pRecord->mUnknown1C.mUnknown00[2] += pCmd->mArg;
            break;
        case 7: {
            float limit;
            ReplayEventGetPos(p, pCmd->mArg, range);
            limit = _Replay_iEdgeLimit;
            if (limit > fn_800A32B4() - (float)fabs(range[0])) {
                switch (pRecord->mUnknown1C.mUnknown34) {
                case 0:
                case 1:
                case 2:
                case 3: {
                    float d = pRecord->mUnknown1C.mUnknown00[0] - range[0];

                    if ((range[0] > 0.0f && d > 0.0f) || (range[1] < 0.0f && d < 0.0f)) {
                        pRecord->mUnknown1C.mUnknown00[0] -= d + d;
                    }
                    break;
                }
                case 7:
                case 8:
                case 9:
                case 10:
                    if ((range[0] > 0.0f && pRecord->mUnknown1C.mUnknown00[0] > 0.0f)
                        || (range[0] < 0.0f && pRecord->mUnknown1C.mUnknown00[0] < 0.0f)) {
                        pRecord->mUnknown1C.mUnknown00[0] = -pRecord->mUnknown1C.mUnknown00[0];
                    }
                    break;
                }
            }
            break;
        }
        case 8:
            _Replay_iEdgeLimit = pCmd->mArg;
            break;
        /* Placeholder label values: the compare tree needs empty labels
           at 0, 0x20-0x23 and one value above 0x3F; 0x40 is not recovered. */
        case 0:
        case 0x20:
        case 0x21:
        case 0x22:
        case 0x23:
        case 0x40:
            break;
        case 0x24:
            pTimer->mUnknown00 = ReplayEventGetTime(p, pCmd->mArg);
            break;
        case 0x25:
            pTimer->mUnknown00 += pCmd->mArg;
            pTimer->mUnknown00 = pTimer->mUnknown00 < p->mUnknownD70 ? p->mUnknownD70 : pTimer->mUnknown00;
            pTimer->mUnknown00 = pTimer->mUnknown00 > p->mUnknownD7C - 1 ? p->mUnknownD7C - 1 : pTimer->mUnknown00;
            break;
        case 0x26:
            pTimer->mUnknown0C = pCmd->mArg;
            break;
        case 0x27:
            pTimer->mUnknown08 = ReplayEventGetTime(p, pCmd->mArg) - pTimer->mUnknown00;
            break;
        case 0x28:
            pTimer->mUnknown08 += pCmd->mArg;
            break;
        case 0x2A:
            ReplaySetEventMark(p, last, pCmd->mArg, count);
            count++;
            _Replay_bDefaultShot = 0;
            break;
        case 0x2B:
            p->mUnknown148C[count - 1].mUnknown0 += pCmd->mArg;
            break;
        case 0x2C:
            last = pCmd->mArg;
            break;
        case 0x2D:
            pRecord->mUnknown5C.mUnknown38 = ReplayEventGetObject(p, pCmd->mArg);
            break;
        case 0x2E:
            ReplayEventGetPos(p, pCmd->mArg, pRecord->mUnknown5C.mUnknown1C);
            break;
        case 0x2F:
            *(Vector_80039F5C *)pRecord->mUnknown5C.mUnknown1C = origin;
            break;
        case 0x30:
            pRecord->mUnknown5C.mUnknown1C[0] = pCmd->mArg;
            break;
        case 0x31:
            pRecord->mUnknown5C.mUnknown1C[0] += pCmd->mArg;
            break;
        case 0x32:
            pRecord->mUnknown5C.mUnknown1C[1] = pCmd->mArg;
            break;
        case 0x33:
            pRecord->mUnknown5C.mUnknown1C[1] += pCmd->mArg;
            break;
        case 0x34:
            pRecord->mUnknown5C.mUnknown1C[2] = pCmd->mArg;
            break;
        case 0x35:
            pRecord->mUnknown5C.mUnknown1C[2] += pCmd->mArg;
            break;
        case 0x36:
            pRecord->mUnknown5C.mUnknown34 = pCmd->mArg;
            pList->mUnknown584 |= 0x10;
            break;
        case 0x37:
            pRecord->mUnknown5C.mUnknown3C = pCmd->mArg;
            _Replay_bDefaultShot = 0;
            break;
        case 0x38:
            ReplayEventGetPos(p, pCmd->mArg, pRecord->mUnknown5C.mUnknown00);
            break;
        case 0x39:
            *(Vector_80039F5C *)pRecord->mUnknown5C.mUnknown00 = origin;
            break;
        case 0x3A:
            pRecord->mUnknown5C.mUnknown00[0] = pCmd->mArg;
            break;
        case 0x3B:
            pRecord->mUnknown5C.mUnknown00[0] += pCmd->mArg;
            break;
        case 0x3C:
            pRecord->mUnknown5C.mUnknown00[1] = pCmd->mArg;
            break;
        case 0x3D:
            pRecord->mUnknown5C.mUnknown00[1] += pCmd->mArg;
            break;
        case 0x3E:
            pRecord->mUnknown5C.mUnknown00[2] = pCmd->mArg;
            break;
        case 0x3F:
            pRecord->mUnknown5C.mUnknown00[2] += pCmd->mArg;
            break;
        }
        pCmd++;
    }
}

extern "C" void ReplayStartShot(Type_803EA368 *p, Timer_8002E7C0 *pTimer)
{
    SndgReplayReset();
    ReplaySeek(p, pTimer->mUnknown00 - pTimer->mUnknown04);
    ReplaySetSpeed(p, pTimer->mUnknown0C);
    ReplaySetPlayEnd(p, pTimer->mUnknown08);
    pTimer->mUnknown10 = 0;
}

extern "C" Record_8002E7C0 *ReplayShotListGetCurrent(RecordList_8002E7C0 *pList)
{
    return &pList->mUnknown000[pList->mUnknown580];
}

extern "C" int ReplayShotListHasNext(RecordList_8002E7C0 *pList)
{
    return pList->mUnknown580 + 1 < pList->mUnknown57C;
}

extern "C" void ReplayShotListAdvance(Type_803EA368 *p, RecordList_8002E7C0 *pList)
{
    Record_8002E7C0 *pCur = &pList->mUnknown000[pList->mUnknown580];
    Record_8002E7C0 *pNext = &pList->mUnknown000[pList->mUnknown580 + 1];

    if (pNext->mUnknown18 & 0x40) {
        pNext->mUnknown1C.mUnknown1C[0] = pCur->mUnknown1C.mUnknown0C[0];
        pNext->mUnknown1C.mUnknown1C[1] = pCur->mUnknown1C.mUnknown0C[1];
        pNext->mUnknown1C.mUnknown1C[2] = pCur->mUnknown1C.mUnknown0C[2];
    }
    if (pNext->mUnknown18 & 0x80) {
        pNext->mUnknown1C.mUnknown00[0] = p->mpUnknownDA0->mHeader.mUnknown04[0];
        pNext->mUnknown1C.mUnknown00[1] = p->mpUnknownDA0->mHeader.mUnknown04[1];
        pNext->mUnknown1C.mUnknown00[2] = p->mpUnknownDA0->mHeader.mUnknown04[2];
    }
    pList->mUnknown580++;
    ReplayStartShot(p, &pList->mUnknown000[pList->mUnknown580].mUnknown04);
}

extern "C" void ReplayShotListClear(RecordList_8002E7C0 *pList)
{
    memset(pList, 0, sizeof(RecordList_8002E7C0));
}

extern "C" void ReplayShotListStart(Type_803EA368 *p, RecordList_8002E7C0 *pList)
{
    BannerClear(7);
    if (pList->mUnknown584 & 1) {
        ReplayShotListStartStub();
    }
    ReplayStartShot(p, &pList->mUnknown000[0].mUnknown04);
    if (pList->mUnknown584 & 2) {
        SndgEventSetReplayKind(0);
    } else if (pList->mUnknown584 & 4) {
        SndgEventSetReplayKind(1);
    } else if (pList->mUnknown584 & 8) {
        SndgEventSetReplayKind(2);
    } else {
        SndgEventSetReplayKind(3);
    }
}

extern "C" int ReplayPickScript(int mode)
{
    int searching = 1;
    ReplayScriptConds_t *pEntry = ReplayGetScriptTable();
    ReplayScriptConds_t *pStart;

    switch (mode) {
    case 0:
        _Replay_iScript = mode;
        break;
    case 1:
        _Replay_iScript++;
        pEntry += _Replay_iScript;
        if (pEntry->mId == -1) {
            pEntry = ReplayGetScriptTable();
        }
        break;
    }
    pStart = pEntry;
    while (searching) {
        if (ReplayTestConditions(pEntry->mpConds)) {
            _Replay_iScript = pEntry->mId;
            return 1;
        }
        pEntry++;
        if (pEntry->mId == -1) {
            pEntry = ReplayGetScriptTable();
        }
        if (pEntry == pStart) {
            searching = 0;
        }
    }
    return 0;
}

extern "C" void ReplayCamInit(GameCamera_t *pCamera, CameraDesc_t *pDesc)
{
    CamMainInit(pCamera, pDesc);
}

extern "C" void ReplayCamUninit(GameCamera_t *pCamera)
{
    CamMainUninit(pCamera);
}

extern "C" void ReplayCamUpdate(void *p, GameCamera_t *pCamera)
{
    CamMainUpdate(p, pCamera);
}

extern "C" GameCamera_t *ReplayCamCreate(ReplayCamDesc_t *pDesc)
{
    CameraDesc_t desc;
    Object_80039F5C *pObject;
    GameCamera_t *pCamera;

    CamMainInitDesc(&desc);
    pObject = fn_8009BCE8(&pDesc->mUnknown04);
    if (pObject) {
        desc.mUnknown08 = pDesc->mUnknown04;
    }
    switch (pDesc->mUnknown00) {
    case 1:
    case 2:
        desc.mUnknown00 = 4;
        desc.mUnknown04 = 15;
        break;
    case 3:
    default:
        desc.mUnknown00 = 1;
        desc.mUnknown04 = 13;
        break;
    }
    pCamera = (GameCamera_t *)CamCreate(3, &desc);
    pCamera->mUnknownF5C = 0;
    if (ReplayDirectorIsActive()) {
        _Replay_bFreeCam = 1;
    } else {
        _Replay_bFreeCam = 0;
    }
    if (pDesc->mUnknown00 == 1) {
        RecordList_8002E7C0 *pList = &pCamera->mUnknown128;
        Type_803EA368 *p = gpReplay;

        ReplayShotListClear(pList);
        ReplayBuildShotList(p, pList);
        ReplayShotListStart(p, pList);
    }
    CamMainSetMode(pCamera, 8, 0, 0);
    if (pObject == 0) {
        if (BallsExist()) {
            _Replay_pTarget = BallGetModel(BallGetCurrent());
        } else {
            _Replay_pTarget = 0;
        }
    } else {
        _Replay_pTarget = pObject->mpUnknown4;
    }
    CamMainFollow(pCamera, 5, (int)&_Replay_Focus, 0);
    return pCamera;
}

extern "C" void ReplayCamSetBallHighlight(Object_80039F5C *p)
{
    int on = 0;
    Block_80170E64 *pBlock;

    if (p && (p->mpUnknown4->mUnknown20 & 0x200)) {
        on = 1;
    }
    pBlock = BallGetModel(BallGetCurrent());
    if (on == 1) {
        pBlock->mUnknown20 |= 8;
    } else {
        pBlock->mUnknown20 &= ~8;
    }
}

extern "C" void ReplayCamUpdateFocus(void)
{
    Object_80039F5C *pA;
    Object_80039F5C *pB;
    Object_80039F5C *p = ReplayGetFocusPlayers(&pA, &pB);

    if (_Replay_pTarget) {
        if (_Replay_bTargetIsBall == 1 && p) {
            if (pA != pB) {
                float t = ReplayGetFrameBlend();

                if (pA == 0) {
                    Vec3Lerp(&_Replay_Focus.mPos, &p->mpUnknown4->mUnknown4, &_Replay_pTarget->mUnknown4, t);
                } else if (pB == 0) {
                    Vec3Lerp(&_Replay_Focus.mPos, &_Replay_pTarget->mUnknown4, &p->mpUnknown4->mUnknown4, t);
                } else {
                    Vec3Lerp(&_Replay_Focus.mPos, &pB->mpUnknown4->mUnknown4, &pA->mpUnknown4->mUnknown4, t);
                }
            } else {
                Vector_80039F5C *pFocus = &_Replay_Focus.mPos;

                pFocus->mX = p->mpUnknown4->mUnknown4.mX;
                pFocus->mY = p->mpUnknown4->mUnknown4.mY;
                pFocus->mZ = p->mpUnknown4->mUnknown4.mZ;
            }
        } else {
            Block_80170E64 *pBlock = _Replay_pTarget;
            Vector_80039F5C *pFocus = &_Replay_Focus.mPos;

            pFocus->mX = pBlock->mUnknown4.mX;
            pFocus->mY = pBlock->mUnknown4.mY;
            pFocus->mZ = pBlock->mUnknown4.mZ;
        }
    }
    if (BallsExist()) {
        ReplayCamSetBallHighlight(p);
    }
}

extern "C" void ReplayCamGetMoveOffset(FieldPoint_t *pOut, unsigned int dir, float speed)
{
    pOut->mY = 0.0f;
    pOut->mX = 0.0f;
    switch (dir) {
    case 0x35:
        pOut->mX = -speed;
        break;
    case 0x10:
    case 0x36:
        pOut->mX = speed;
        break;
    case 0x34:
        pOut->mY = -speed;
        break;
    case 0x11:
    case 0x33:
        pOut->mY = speed;
        break;
    }
    Vec2Rotate(pOut, pOut, -_Replay_iCamYaw);
}

extern "C" Block_80170E64 *ReplayCamFindNearestObject(GameCamera_t *pCamera, float *pDist, unsigned char *pFound)
{
    Block_80170E64 *pBest = PlyrObjsFindNearest(&_Replay_Focus.mPos, pDist);
    Block_80170E64 *p;
    float dist;

    if (_Replay_bFreeCam) {
        p = BigObjFindNearest(&_Replay_Focus.mPos, &dist);
        if (p && dist < *pDist) {
            *pDist = dist;
            pBest = p;
        }
    }
    if (BallsExist()) {
        *pFound = 0;
        if (ReplayGetFocusPlayers(0, 0) == 0) {
            p = BallGetModel(BallGetCurrent());
            dist = Vec2Distance(&p->mUnknown4, &_Replay_Focus.mPos);
            if (dist < *pDist) {
                *pDist = dist;
                *pFound = 1;
                pBest = p;
            }
        }
    }
    return pBest;
}

extern "C" void ReplayCamSetFieldMargins(void)
{
    switch (fn_800A3444()) {
    case 9:
        _Replay_fCamMarginY = -1.5f;
        _Replay_fCamMarginX = -0.5f;
        _Replay_fViewMarginY = 3.5f;
        _Replay_fViewMarginX = 2.5f;
        break;
    case 2:
        _Replay_fCamMarginY = -4.0f;
        _Replay_fCamMarginX = -0.5f;
        _Replay_fViewMarginY = 6.0f;
        _Replay_fViewMarginX = 2.5f;
        break;
    case 7:
        _Replay_fCamMarginY = -8.5f;
        _Replay_fCamMarginX = -0.5f;
        _Replay_fViewMarginY = 10.5f;
        _Replay_fViewMarginX = 2.5f;
        break;
    case 1:
        _Replay_fCamMarginY = -1.0f;
        _Replay_fCamMarginX = -0.5f;
        _Replay_fViewMarginY = 3.0f;
        _Replay_fViewMarginX = 2.5f;
        break;
    case 5:
        _Replay_fCamMarginY = -0.5f;
        _Replay_fCamMarginX = -0.75f;
        _Replay_fViewMarginY = 2.5f;
        _Replay_fViewMarginX = 2.75f;
        break;
    case 3:
        _Replay_fCamMarginY = -1.0f;
        _Replay_fCamMarginX = -0.5f;
        _Replay_fViewMarginY = 3.0f;
        _Replay_fViewMarginX = 2.5f;
        break;
    case 11:
        _Replay_fCamMarginY = -1.0f;
        _Replay_fCamMarginX = -0.5f;
        _Replay_fViewMarginY = 3.0f;
        _Replay_fViewMarginX = 2.5f;
        break;
    default:
        _Replay_fCamMarginY = -0.5f;
        _Replay_fCamMarginX = -0.5f;
        _Replay_fViewMarginY = 2.5f;
        _Replay_fViewMarginX = 2.5f;
        break;
    }
}

extern "C" void ReplayCamComputeMaxDistance(GameCamera_t *pCamera, ReplayFocus_t *pTarget)
{
    float dist = Vec3Distance(&pTarget->mPos, (Vector_80039F5C *)pCamera->mHeader.mUnknown04);
    float overX = fabsf(pCamera->mHeader.mUnknown04[0]) - (ScrmGetSidelineX() + _Replay_fViewMarginX + _Replay_fCamMarginX);
    float overY = fabsf(pCamera->mHeader.mUnknown04[1]) - (ScrmGetEndLineY() + _Replay_fViewMarginY + _Replay_fCamMarginY);
    float overZ = fabsf(pCamera->mHeader.mUnknown04[2]) - 9.2f;
    float limitX = 16.0f;
    float limitY = 16.0f;
    float limitZ = 16.0f;

    if (overX > 0.0f) {
        limitX = dist * ((ScrmGetSidelineX() + _Replay_fViewMarginX + _Replay_fCamMarginX - fabsf(pTarget->mPos.mX))
                         / (fabsf(pCamera->mHeader.mUnknown04[0]) - fabsf(pTarget->mPos.mX)));
    }
    if (overY > 0.0f) {
        limitY = dist * ((ScrmGetEndLineY() + _Replay_fViewMarginY + _Replay_fCamMarginY - fabsf(pTarget->mPos.mY))
                         / (fabsf(pCamera->mHeader.mUnknown04[1]) - fabsf(pTarget->mPos.mY)));
    }
    if (overZ > 0.0f) {
        limitZ = dist * ((9.2f - fabsf(pTarget->mPos.mZ))
                         / (fabsf(pCamera->mHeader.mUnknown04[2]) - fabsf(pTarget->mPos.mZ)));
    }
    _Replay_fMaxDist = limitY <= limitX ? limitY : limitX;
    _Replay_fMaxDist = limitZ <= _Replay_fMaxDist ? limitZ : _Replay_fMaxDist;
}

extern "C" void ReplayCamApplyDistance(GameCamera_t *pCamera)
{
    if (_Replay_fCamDist > _Replay_fMaxDist) {
        pCamera->mUnknown30 = _Replay_fMaxDist;
    } else {
        pCamera->mUnknown30 = _Replay_fCamDist;
    }
}

extern "C" void ReplayCamZoom(GameCamera_t *pCamera, float amount)
{
    float v = amount * 0.2f + _Replay_fCamDist;

    if (_Replay_bFreeCam) {
        _Replay_fCamDist = v < 0.0f ? 0.0f : v;
    } else {
        _Replay_fCamDist = CLAMP(v, 2.0f, _Replay_fMaxDist);
    }
}

extern "C" void ReplayCamMoveCursor(GameCamera_t *pCamera, unsigned int input, float amount)
{
    FieldPoint_t offset;

    if ((unsigned int)(SysGetSystemTime() - _Replay_iTargetTime) > 29) {
        if (_Replay_pTarget == 0) {
            float dist;
            unsigned char flag;
            Block_80170E64 *pTarget = ReplayCamFindNearestObject(pCamera, &dist, &flag);

            if (pTarget != 0) {
                FieldPoint_t clamped;
                clamped.mX = CLAMP(pTarget->mUnknown4.mX, -ScrmGetSidelineX(), ScrmGetSidelineX());
                clamped.mY = CLAMP(pTarget->mUnknown4.mY, -ScrmGetEndLineY(), ScrmGetEndLineY());
                if (dist >= 0.25f || clamped.mX != pTarget->mUnknown4.mX
                    || clamped.mY != pTarget->mUnknown4.mY) {
                    ReplayCamGetMoveOffset(&offset, input, amount * 0.15f);
                    Vec2Add(&_Replay_Focus.mPos, &_Replay_Focus.mPos, &offset);
                } else {
                    _Replay_pTarget = pTarget;
                    _Replay_iTargetTime = SysGetSystemTime();
                    _Replay_bTargetIsBall = flag;
                    ReplayCursorSetVisible(0);
                }
            } else {
                ReplayCamGetMoveOffset(&offset, input, amount * 0.15f);
                Vec2Add(&_Replay_Focus.mPos, &_Replay_Focus.mPos, &offset);
                _Replay_Focus.mPos.mX = CLAMP(_Replay_Focus.mPos.mX, -ScrmGetSidelineX(), ScrmGetSidelineX());
                _Replay_Focus.mPos.mY = CLAMP(_Replay_Focus.mPos.mY, -ScrmGetEndLineY(), ScrmGetEndLineY());
            }
        } else {
            float step = 0.275f;
            if (amount < 0.0f) {
                step = -step;
            }
            ReplayCamGetMoveOffset(&offset, input, step);
            Vec2Add(&_Replay_Focus.mPos, &_Replay_Focus.mPos, &offset);
            _Replay_pTarget = 0;
            ReplayCursorSetVisible(1);
        }
    }
}

extern "C" void ReplayCamRotate(GameCamera_t *pCamera, float amount)
{
    CamMainRotate(pCamera, -(int)((amount + amount) * 46603.37890625f));
}

extern "C" void ReplayCamPitch(GameCamera_t *pCamera, float amount)
{
    int base = pCamera->mUnknownD0 & 0xFFFFFF;
    int angle = base + (int)(amount * 37282.703125f);

    if (!_Replay_bFreeCam) {
        angle = CLAMP(angle, 0xC00000, 0xFF49F5);
    }
    CamMainPitch(pCamera, angle - base);
}

extern "C" void ReplayCamAdjustHeight(GameCamera_t *pCamera, float amount)
{
    float v = amount * 0.2f + pCamera->mUnknownCC;

    v = CLAMP(v, 1.0f, 9.2f);
    pCamera->mUnknownCC = v;
}

extern "C" GameCamera_t *ReplayCamStart(ReplayCamDesc_t *pDesc)
{
    GameCamera_t *pCamera;
    GameCameraKind1_t *pBase;

    memset(&_Replay_Focus, 0, sizeof(ReplayFocus_t));
    _Replay_pTarget = 0;
    _Replay_iCamYaw = 0;
    _Replay_iTargetTime = SysGetSystemTime();
    _Replay_bTargetIsBall = 1;
    _Replay_fMaxDist = 16.0f;
    pCamera = ReplayCamCreate(pDesc);
    if (pDesc->mUnknown08) {
        ReplayCamPush(pCamera);
    }
    _Replay_fCamDist = pCamera->mUnknown30;
    ReplayCursorSetVisible(0);
    pBase = (GameCameraKind1_t *)pCamera;
    pBase->mUnknown90 = 0x200000;
    pBase->mUnknown88 = 0x400000;
    pBase->mUnknown64 = 0.3f;
    pBase->mUnknown68 = 0.3f;
    pBase->mUnknown6C = 0.3f;
    pBase->mUnknown70 = 0.2f;
    pBase->mUnknown74 = 0.3f;
    pBase->mUnknown78 = 0.3f;
    pBase->mUnknown8C = 0x200000;
    pBase->mUnknown84 = 0x400000;
    pBase->mUnknown7C = 0.3f;
    pBase->mUnknown80 = 0.2f;
    CamSetNearPlane(pCamera, 0.1f);
    pCamera->mUnknown94 |= 4;
    _Replay_bCamActive = 1;
    ReplayCamSetFieldMargins();
    return pCamera;
}

extern "C" void ReplayCamPush(GameCamera_t *pCamera)
{
    VptManagerPushCamera(0, pCamera, 0, 0);
}

extern "C" void ReplayCamProcess(GameCamera_t *pCamera)
{
    ReplayCamProcessStub();
    if (!_Replay_bFreeCam) {
        FieldPoint_t clamped;
        float y;
        clamped.mX = CLAMP(_Replay_Focus.mPos.mX, -ScrmGetSidelineX(), ScrmGetSidelineX());
        clamped.mY = y = CLAMP(_Replay_Focus.mPos.mY, -ScrmGetEndLineY(), ScrmGetEndLineY());
        if (clamped.mX != _Replay_Focus.mPos.mX || y != _Replay_Focus.mPos.mY) {
            _Replay_Focus.mPos.mX = clamped.mX;
            _Replay_Focus.mPos.mY = y;
            _Replay_pTarget = 0;
            _Replay_bTargetIsBall = 0;
            ReplayCursorSetVisible(1);
        }
    }
    ReplayCamUpdateFocus();
    _Replay_Focus.mPos.mZ = _Replay_fFocusHeight;
    if (!_Replay_bFreeCam) {
        _Replay_fMaxDist = 16.0f;
        ReplayCamApplyDistance(pCamera);
        pCamera->mUnknown94 |= 4;
        CamMainProcess(pCamera, 0, 0, 0);
        ReplayCamComputeMaxDistance(pCamera, &_Replay_Focus);
        pCamera->mUnknown94 |= 4;
    }
    ReplayCamApplyDistance(pCamera);
    ReplayDirectorUpdateFocus(&_Replay_Focus, &_Replay_pTarget);
    ReplayCursorSetPos(&_Replay_Focus.mPos.mX, 0);
    CamMainProcess(pCamera, 0, 0, 0);
    _Replay_iCamYaw = pCamera->mUnknown38;
    if (!_Replay_bFreeCam) {
        pCamera->mHeader.mUnknown04[0] = CLAMP(pCamera->mHeader.mUnknown04[0], -ScrmGetSidelineX() - _Replay_fCamMarginX, ScrmGetSidelineX() + _Replay_fCamMarginX);
        pCamera->mHeader.mUnknown04[1] = CLAMP(pCamera->mHeader.mUnknown04[1], -ScrmGetEndLineY() - _Replay_fCamMarginY, ScrmGetEndLineY() + _Replay_fCamMarginY);
    }
}

extern "C" void ReplayCamProcessAuto(GameCamera_t *pCamera)
{
    CamMainProcess(pCamera, 0, 0, 0);
}

extern "C" void ReplayCamDestroy(GameCamera_t *pCamera, int detach)
{
    if (detach) {
        VptManagerPopCamera(0, pCamera);
    }
    CamDestroy(pCamera);
    ReplayCursorSetVisible(0);
    if (ScreenTransCanCapture(0x23000)) {
        ScreenTransStart(1, 15, 0x808080, 0);
    }
    _Replay_bCamActive = 0;
}

extern "C" unsigned char ReplayCamIsActive(void)
{
    return _Replay_bCamActive;
}

extern "C" void ReplayCamHandleInput(GameCamera_t *pCamera, int unused, unsigned int input, float amount)
{
    switch (input) {
    case 0x12:
        ReplayCamRotate(pCamera, amount);
        break;
    case 0x13:
        ReplayCamPitch(pCamera, amount);
        break;
    case 0x3A:
        ReplayCamZoom(pCamera, 1.0f);
        break;
    case 0x37:
        ReplayCamZoom(pCamera, -1.0f);
        break;
    case 8:
        break;
    }
    if (pCamera->mUnknownF5C & 1) {
        switch (input) {
        case 0x36:
            ReplayCamRotate(pCamera, 1.0f);
            break;
        case 0x35:
            ReplayCamRotate(pCamera, -1.0f);
            break;
        case 0x33:
            ReplayCamPitch(pCamera, 1.0f);
            break;
        case 0x34:
            ReplayCamPitch(pCamera, -1.0f);
            break;
        case 0x10:
            ReplayCamRotate(pCamera, amount);
            break;
        case 0x11:
            ReplayCamPitch(pCamera, amount);
            break;
        }
    } else {
        switch (input) {
        case 0x10:
        case 0x11:
        case 0x33:
        case 0x34:
        case 0x35:
        case 0x36:
            ReplayCamMoveCursor(pCamera, input, amount);
            break;
        }
    }
}

extern "C" void ReplayCamHandleMenuInput(GameCamera_t *pCamera, int player, unsigned int input, float amount)
{
    unsigned int action;

    switch (input) {
    case 0x37:
        action = 0;
        break;
    case 0x3A:
        action = 1;
        break;
    case 0x33:
        action = 2;
        break;
    case 0x34:
        action = 3;
        break;
    case 0x11:
        action = 4;
        break;
    case 0x12:
        action = 5;
        break;
    case 0x13:
        action = 6;
        break;
    default:
        action = 7;
        break;
    }
    switch (action) {
    case 0:
        ReplayCamZoom(pCamera, -1.0f);
        UISProcessEvent(gUISMainInfo, player, 20, 0, 0, 1);
        break;
    case 1:
        ReplayCamZoom(pCamera, 1.0f);
        UISProcessEvent(gUISMainInfo, player, 20, 0, 0, 1);
        break;
    case 2:
        ReplayCamAdjustHeight(pCamera, 1.0f);
        UISProcessEvent(gUISMainInfo, player, 20, 0, 0, 1);
        break;
    case 3:
        ReplayCamAdjustHeight(pCamera, -1.0f);
        UISProcessEvent(gUISMainInfo, player, 20, 0, 0, 1);
        break;
    case 4:
        ReplayCamAdjustHeight(pCamera, amount);
        UISProcessEvent(gUISMainInfo, player, 20, 0, 0, 1);
        break;
    case 5:
        ReplayCamRotate(pCamera, amount);
        UISProcessEvent(gUISMainInfo, player, 20, 0, 0, 1);
        break;
    case 6:
        ReplayCamPitch(pCamera, amount);
        UISProcessEvent(gUISMainInfo, player, 20, 0, 0, 1);
        break;
    }
}

extern "C" void ReplayCamInitDesc(ReplayCamDesc_t *pDesc)
{
    memset(pDesc, 0, sizeof(ReplayCamDesc_t));
    fn_8009BD2C(0, &pDesc->mUnknown04);
    pDesc->mUnknown08 = 1;
}


/* Accessors that nothing on GameCube calls; the linker drops them. */
static Block_80170E64 *GetHighlightedObject(void) { return _Replay_pTarget; }

static void SetFocusHeight(unsigned char reset, float height)
{
    if (reset) {
        _Replay_fFocusHeight = 1.2f;
    } else {
        _Replay_fFocusHeight = height;
    }
}

extern "C" int ReplayBufferNextFrame(void)
{
    if (_Replay_iFrameIndex >= _Replay_iFrameCount) {
        _Replay_bWrapped = 1;
        _Replay_iFrameIndex = 0;
    }
    return _Replay_iFrameIndex++;
}

extern "C" void ReplayBufferWriteFrame(int index)
{
    char *pBuffer = ReplayAuxRamGetScratch(index, _Replay_uFrameSize);

    if (pBuffer != 0) {
        Type_80190ED4 stream;
        ReplayChannel_t *pEntry;

        fn_80190ED4(&stream, pBuffer, 1);
        for (pEntry = (ReplayChannel_t *)DSGetListNode(_Replay_pChannels, 0); pEntry != 0;
             pEntry = (ReplayChannel_t *)DSNextListNode(_Replay_pChannels, pEntry)) {
            pEntry->mpWrite(&stream);
        }
        fn_80190EF0(&stream);
        ReplayAuxRamStoreFrame(pBuffer, index, _Replay_uFrameSize);
    }
}


extern "C" void ReplayBufferGetFrames(Type_803EA368 *pGame, char **ppCur, char **ppNext, char **ppPrev, char **ppNext2,
                            float *pT)
{
    int ticks;
    int frame;
    int cur;
    int next;
    int next2 = -1;
    int prev = -1;

    *ppPrev = *ppNext2 = 0;
    ticks = (pGame->mUnknownD74 - pGame->mUnknownD70) * 60 + pGame->mUnknownD78;
    frame = ticks / 120;
    *pT = (float)(ticks % 120) * (1.0f / 120.0f);
    cur = (frame + _Replay_iFirstFrame) % _Replay_iFrameCount;
    if (_Replay_bWrapped) {
        if (cur != _Replay_iFirstFrame) {
            if (cur == 0) {
                prev = _Replay_iFrameCount - 1;
            } else {
                prev = cur - 1;
            }
        }
        if (cur == _Replay_iFrameIndex) {
            next = cur;
        } else {
            next = (cur + 1) % _Replay_iFrameCount;
            if (next != _Replay_iFrameIndex) {
                next2 = (next + 1) % _Replay_iFrameCount;
            }
        }
    } else {
        if (cur > 0 && cur <= _Replay_iFrameIndex) {
            prev = cur - 1;
        }
        if (cur != _Replay_iFrameIndex) {
            next = (cur + 1) % _Replay_iFrameCount;
            next2 = next + 1;
        } else {
            next = cur;
        }
        if (next2 > _Replay_iFrameIndex) {
            next2 = -1;
        }
    }
    *ppCur = ReplayAuxRamLoadFrame(cur, _Replay_uFrameSize);
    *ppNext = ReplayAuxRamLoadFrame(next, _Replay_uFrameSize);
    if (prev >= 0) {
        *ppPrev = ReplayAuxRamLoadFrame(prev, _Replay_uFrameSize);
    } else {
        ReplayAuxRamLoadFrame(cur, _Replay_uFrameSize);
        *ppPrev = 0;
    }
    if (next2 >= 0) {
        *ppNext2 = ReplayAuxRamLoadFrame(next2, _Replay_uFrameSize);
    } else {
        ReplayAuxRamLoadFrame(next, _Replay_uFrameSize);
        *ppNext2 = 0;
    }
}

extern "C" void ReplayReadFrameStub(void) {}

extern "C" void ReplayReadPacked2(void *pStream, float *pValues, int bits, float scale)
{
    long long value = fn_80190F18(pStream, bits * 2);
    float x = (int)((value << (64 - bits * 2)) >> (64 - bits));
    float y = (int)((value << (64 - bits)) >> (64 - bits));

    scale = 1.0f / scale;
    pValues[0] = x * scale;
    pValues[1] = y * scale;
}

extern "C" void ReplayReadPacked3(void *pStream, float *pValues, int bits, float scale)
{
    long long value = fn_80190F18(pStream, bits * 3);
    float x = (int)((value << (64 - bits * 3)) >> (64 - bits));
    float y = (int)((value << (64 - bits * 2)) >> (64 - bits));
    float z = (int)((value << (64 - bits)) >> (64 - bits));

    scale = 1.0f / scale;
    pValues[0] = x * scale;
    pValues[1] = y * scale;
    pValues[2] = z * scale;
}

extern "C" void ReplayReadPacked4(void *pStream, float *pValues, int bits, float scale)
{
    long long value = fn_80190F18(pStream, bits * 4);
    float x = (int)((value << (64 - bits * 4)) >> (64 - bits));
    float y = (int)((value << (64 - bits * 3)) >> (64 - bits));
    float z = (int)((value << (64 - bits * 2)) >> (64 - bits));
    float w = (int)((value << (64 - bits)) >> (64 - bits));

    scale = 1.0f / scale;
    pValues[0] = x * scale;
    pValues[1] = y * scale;
    pValues[2] = z * scale;
    pValues[3] = w * scale;
}

extern "C" void ReplayWritePacked2(void *pStream, float *pValues, int bits, float scale)
{
    unsigned long long mask = (1ULL << bits) - 1;
    unsigned long long x = ((long long)(int)(pValues[0] * scale) & mask) << bits;
    unsigned long long y = (long long)(int)(pValues[1] * scale) & mask;

    fn_80191068(pStream, x | y, bits * 2);
}

extern "C" void ReplayWritePacked3(void *pStream, float *pValues, int bits, float scale)
{
    unsigned long long mask = (1ULL << bits) - 1;
    unsigned long long x = ((long long)(int)(pValues[0] * scale) & mask) << bits * 2;
    unsigned long long y = ((long long)(int)(pValues[1] * scale) & mask) << bits;
    unsigned long long z = (long long)(int)(pValues[2] * scale) & mask;

    fn_80191068(pStream, x | y | z, bits * 3);
}

extern "C" void ReplayWritePacked4(void *pStream, float *pValues, int bits, float scale)
{
    unsigned long long mask = (1ULL << bits) - 1;
    unsigned long long x = ((long long)(int)(pValues[0] * scale) & mask) << bits * 3;
    unsigned long long y = ((long long)(int)(pValues[1] * scale) & mask) << bits * 2;
    unsigned long long z = ((long long)(int)(pValues[2] * scale) & mask) << bits;
    unsigned long long w = (long long)(int)(pValues[3] * scale) & mask;

    fn_80191068(pStream, x | y | z | w, bits * 4);
}

extern "C" void ReplayBufferReset(void)
{
    _Replay_bWrapped = _Replay_iFrameIndex = _Replay_iFirstFrame = 0;
}

extern "C" void ReplayRecordFrame(Type_803EA368 *pGame)
{
    if (((pGame->mUnknownD74 - pGame->mUnknownD70) & 1) == 0) {
        ReplayBufferWriteFrame(ReplayBufferNextFrame());
        if (_Replay_bWrapped) {
            pGame->mUnknownD70 += 2;
        }
    }
    pGame->mUnknownD74++;
}

extern "C" void ReplayBufferFinish(Type_803EA368 *pGame)
{
    int count = _Replay_iFrameIndex - 1;

    _Replay_iFrameIndex = count;
    if (_Replay_iFrameCount == 0) {
        _Replay_iFrameIndex = _Replay_iFirstFrame = 0;
        count = 1;
    } else if (_Replay_bWrapped == 1) {
        if (count < 0) {
            _Replay_iFrameIndex = _Replay_iFrameCount - 1;
            _Replay_iFirstFrame = 0;
        } else {
            _Replay_iFirstFrame = (count + 1) % _Replay_iFrameCount;
        }
        count = _Replay_iFrameCount;
    }
    pGame->mUnknownD7C = pGame->mUnknownD70 + (count - 1) * 2;
}

extern "C" void ReplayHideGameIcons(Type_803EA368 *pGame)
{
    _Replay_pFocusB = 0;
    _Replay_pFocusA = 0;
    PlyrStarSetShown(!(pGame->mUnknownD94 & 0x10000), 0);
    PassIconObjSetEnabled(0);
}

extern "C" void ReplayShowGameIcons(Type_803EA368 *p)
{
    if (fn_800AD9B4() == 4 || PauseIsOpen()) {
        PlyrStarSetShown(0, 0);
    } else {
        PlyrStarSetShown(1, 1);
    }
    PassIconObjSetEnabled(1);
}

extern "C" void ReplayReadFrame(Type_803EA368 *pGame)
{
    char *pCur;
    char *pNext;
    char *pPrev;
    char *pNext2;
    Type_80190ED4 streams[4];
    ReplayChannel_t *pRecord;

    ReplayBufferGetFrames(pGame, &pCur, &pNext, &pPrev, &pNext2, &_Replay_fFrameBlend);
    fn_80190ED4(&streams[0], pCur, 0);
    fn_80190ED4(&streams[1], pNext, 0);
    if (pPrev) {
        fn_80190ED4(&streams[2], pPrev, 0);
    }
    if (pNext2) {
        fn_80190ED4(&streams[3], pNext2, 0);
    }
    for (pRecord = (ReplayChannel_t *)DSGetListNode(_Replay_pChannels, 0); pRecord;
         pRecord = (ReplayChannel_t *)DSNextListNode(_Replay_pChannels, pRecord)) {
        if (pPrev == 0) {
            if (pNext2 == 0) {
                pRecord->mpRead(&streams[1], &streams[0], 0, 0, _Replay_fFrameBlend);
            } else {
                pRecord->mpRead(&streams[1], &streams[0], 0, &streams[3], _Replay_fFrameBlend);
            }
        } else if (pNext2 == 0) {
            pRecord->mpRead(&streams[1], &streams[0], &streams[2], 0, _Replay_fFrameBlend);
        } else {
            pRecord->mpRead(&streams[1], &streams[0], &streams[2], &streams[3], _Replay_fFrameBlend);
        }
    }
    fn_80190EF0(&streams[0]);
    fn_80190EF0(&streams[1]);
    if (pPrev) {
        fn_80190EF0(&streams[2]);
    }
    if (pNext2) {
        fn_80190EF0(&streams[3]);
    }
    ReplayReadFrameStub();
}

extern "C" void ReplayRegisterChannel(void (*pWrite)(Type_80190ED4 *),
                            void (*pRead)(Type_80190ED4 *, Type_80190ED4 *, Type_80190ED4 *, Type_80190ED4 *, float),
                            unsigned int size, const char *pName)
{
    ReplayChannel_t *pRecord = (ReplayChannel_t *)DSNewListNode(_Replay_pChannels);

    pRecord->mpWrite = pWrite;
    pRecord->mpRead = pRead;
    pRecord->mSize = size;
    DSAddListNode(_Replay_pChannels, pRecord, 0);
    _Replay_uFrameSize += size;
}

extern "C" void ReplayBufferInit(void)
{
    ReplayChannel_t *pRecord;

    for (pRecord = (ReplayChannel_t *)DSGetListNode(_Replay_pChannels, 0); pRecord;
         pRecord = (ReplayChannel_t *)DSNextListNode(_Replay_pChannels, pRecord)) {
        _Replay_uFrameSize += pRecord->mSize;
    }
    _Replay_uFrameSize = ((((_Replay_uFrameSize / 2 + 7) / 8 + 7) & ~7) + 31) & ~31;
    _Replay_iFrameCount = _Replay_uBufferSize / _Replay_uFrameSize;
    ReplayAuxRamInit(_Replay_iFrameCount, _Replay_uFrameSize);
}

extern "C" void ReplayChannelsInit(int size)
{
    _Replay_pChannels = DSNewList(1, 0, 11, 12, 0, 0);
    _Replay_uFrameSize = 0;
    _Replay_uBufferSize = 0x400000 - size;
    if (size > 0x400000 || _Replay_uBufferSize < 0x3C000) {
        _Replay_uBufferSize = 0x3C000;
    }
}

extern "C" void ReplayChannelsShutdown(void)
{
    DSDelList(_Replay_pChannels);
    _Replay_pChannels = 0;
    ReplayAuxRamShutdown();
}

extern "C" Object_80039F5C *ReplayGetFocusPlayers(Object_80039F5C **ppA, Object_80039F5C **ppB)
{
    if (ppA && ppB) {
        *ppA = _Replay_pFocusA;
        *ppB = _Replay_pFocusB;
    }
    if (_Replay_pFocusA) {
        return _Replay_pFocusA;
    }
    return _Replay_pFocusB;
}

extern "C" void ReplaySetFocusPlayers(Object_80039F5C *pA, Object_80039F5C *pB)
{
    _Replay_pFocusA = pA;
    _Replay_pFocusB = pB;
}

extern "C" void ReplaySetBallIndex(int value) { _Replay_iBallIndex = value; }

extern "C" int ReplayGetBallIndex(void) { return _Replay_iBallIndex; }

extern "C" unsigned char ReplayIsBufferFull(Type_803EA368 *pGame)
{
    unsigned char result = _Replay_bWrapped;

    if (!result && ((pGame->mUnknownD74 - pGame->mUnknownD70) & 1) == 0 && _Replay_iFrameIndex >= _Replay_iFrameCount) {
        result = 1;
    }
    return result;
}

extern "C" void ReplayCamProcessStub(void) {}

extern "C" float ReplayGetFrameBlend(void) { return _Replay_fFrameBlend; }

extern "C" ReplayScriptConds_t *ReplayGetScriptTable(void) { return _Replay_aScriptConds; }

extern "C" ReplayCommand_t *ReplayFindScript(int id)
{
    ReplayScript_t *pEntry;

    for (pEntry = _Replay_aScripts; pEntry->mId != -1; pEntry++) {
        if (pEntry->mId == id) {
            return pEntry->mpCommands;
        }
    }
    return 0;
}

/* Replay movie start, discarded by the GameCube link (no caller). Rebuilt from
   the Xbox build's copy, which plays a named movie at a 4:3 aspect with a
   finished and an update callback and then points every player at a second
   pose table. The callees and globals it uses have no identified GameCube
   counterpart and stay declared only. */
struct ReplayMoviePlayer {
    char mPad[0xEEC];
    const float *mpPose;
};

extern "C" {
extern unsigned char gReplayMovieDone;
extern int *gpReplayMovieScreen;
extern ReplayMoviePlayer **gppReplayMoviePlayers;
extern const float gReplayMoviePose[8];
void ReplayMoviePlay(int a, int b, const char *pName, int screen, float aspect, void (*pDone)(void),
                     void (*pUpdate)(void));
void ReplayMovieFinished(void);
void ReplayMovieUpdate(void);

static void _StrippedReplayMovieStart(int a, int b, const char *pName)
{
    int i;

    gReplayMovieDone = 0;
    ReplayMoviePlay(a, b, pName, *gpReplayMovieScreen, 4.0f / 3.0f, ReplayMovieFinished, ReplayMovieUpdate);
    for (i = 0; i < 14; i++) {
        ReplayMoviePlayer *pPlayer = gppReplayMoviePlayers ? gppReplayMoviePlayers[i] : 0;
        pPlayer->mpPose = gReplayMoviePose;
    }
}
}
