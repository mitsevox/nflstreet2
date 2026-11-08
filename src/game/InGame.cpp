/* The in-game loop module: the per-frame game update, pausing, the idle state and the attract-mode demo. */

#include "game/cu_8007F12C.h"
#include "engine/viewport.h"
#include "game/PadInput.h"
#include "game/FlowManagerC.h"
#include "game/Class_80297B90.h"
#include "game/Class_80297BF8.h"
#include "game/fn_8007F828.h"
#include "game/fn_800AD9B4.h"
#include "game/GameModeType.h"
#include "game/fn_801FCE10.h"
#include "game/InGame.h"
#include "game/GameModules.h"
#include "game/TimeScale.h"
#include "game/DepthChartSide.h"
#include "game/MemCardUtil.h"
#include "game/fn_80218FC4.h"
#include "game/AudmonEvent.h"
#include <dolphin/os.h>

extern "C" {
double fabs(double);
extern char lbl_8030716C[];
extern char lbl_803072C4[];
extern float gFrameTimeScale;
extern void *lbl_803EA368;
extern void *gUISMainInfo;
extern void *gUISSubInfo;

void VptManagerMarketCamInit(void);
void fn_8002CBB0(void *p, int a, float c, int b);
void fn_8002CF34(void *p);
int fn_8002D060(void *p);
int fn_8002D2C0(void);
void fn_8003E1F0(void);
void fn_80043F50(void);
void fn_80057F28(void);
void fn_800582D0(void);
void fn_8005BF18(void);
void MemCardScreenSetFlag(unsigned char a);
void PauseUpdate(void);
void PauseRequestClose(void);
int PauseIsOpen(void);
void PauseRequestHandleInput(int a, int b, float c);
void fn_80066D5C(void);
void SndgUpdate(int a);
void fn_800726B8(void);
void fn_800728F8(void);
void fn_80072C90(int a, int b);
void fn_80085A7C(void);
void fn_80085AA0(int a, DepthChartSide_t *pRecord0, int b, DepthChartSide_t *pRecord1);
void PlaybookSideClearAll(void);
void fn_8008FE5C(int a);
void fn_80099568(int a);
void fn_800A216C(int a);
void fn_800A3120(float a);
void fn_800A7F6C(void);
void fn_800A8EB8(void);
int fn_800A937C(void);
void fn_800A9478(int a);
int fn_800A9680(void);
void fn_800AB944(void *p);
void fn_800AD888(float a);
void fn_800AD910(int a, float b);
void fn_800AE8B4(void);
void fn_800AFD58(int a, int b, float c);
void fn_800B3AF4(float a);
void fn_800B410C(void);
void fn_800B4184(int a);
int fn_800BA6F8(void);
void fn_800BCF7C(void *p);
int fn_800C1E40(void);
void fn_800C1E50(void);
int fn_800C8704(int *pA, int *pB);
void BallsPark(void);
void fn_8013CF98(void);
void CamGameApplyUserCamera(void);
int CamGameGetSideYaw();
void fn_80144EDC(float a);
void ParticlesProcess(float a);
void DriveLogInit(void);
void DriveLogEndDrive(void);
void ScoringLogInit(void);
void ScoringLogReset(void);
int BannerUpdate(float a);
void GameModeTypeInvalidate(void);
void fn_80187C0C(void);
void UISGameHandleInput(int a, unsigned int id, float value);
void UISGameLoadKeyItem(int a, int b);
void UISGameFreeKeyItem(int a, int b);
void UISGameRefreshAll(void);
void MemCardUtilInit(void);
void MemCardUtilShutdown(void);
void fn_80194AEC(int a);
void RumbleInit(void);
void RumbleShutdown(void);
void RumbleProcess(void);
void RumbleEnable(int a);
void fn_80195F80(void);
void fn_80196130(void);
void PadStateSetValue(int a, int b, float c);
int ConUpdateChannel(int a);
int ConProcessChannel(int a);
int ConSetChannelInfo(int a, int b, void *pValue);
int ConGetChannelInfo(int a, int b);
void FileDebugProcess(void);
void fn_801CE82C(void);
void fn_801CE910(void);
void fn_801D6F58(void);
int fn_801E15D0(int a);
int fn_801E17D0(int a, char *p);
void PerCheckConnectSingle(unsigned char a);
int PerIsDeviceConnected(unsigned char a);
float RemapCheckEntry(int a, int b, char *p);
void fn_8021956C(void *p, int a, int b, int c);
void fn_802345C4(struct EngineParamWords *pDesc, int count);
void fn_80236F34(void);
void fn_80237830(int a);
unsigned int fn_802378C8(void);
void fn_80239CEC(int a, int b);
}

/* Argument of fn_802345C4. */
struct EngineParamWords {
    int mUnknown0;
    int mUnknown4;
};

static unsigned char _InGame_bCancelRequest = 0;
/* Called by Update when non-null. */
static void (*_InGame_pFrameCallback)() = 0;
static unsigned char _InGame_bDemo = 0;
static unsigned int _InGame_uIdleFrames = 0;
static unsigned char _InGame_bIdle = 0;
static unsigned char _InGame_bRunning;
static int _InGame_iFrameCount;
static int _InGame_iPauseCount;
static int _InGame_bInputPaused;

static ModuleDependency sDependencies[] = { &gUIS, lbl_8030716C, lbl_803072C4, 0 };
InGame gInGame;

static void _InGamePadHandler(int a, int b, float c)
{
    MemCardUtilHandleEvent(a, b, c);
    if (b != 0x8F) {
        _InGame_uIdleFrames = 0;
    }
    if (_InGame_bInputPaused == 0) {
        PadStateSetValue(a, b, c);
        if (b != 0x8F) {
            fn_800AFD58(a, b, c);
            PauseRequestHandleInput(a, b, c);
            if (!fn_8002D060(lbl_803EA368) || fn_8002D2C0()) {
                UISGameHandleInput(a, b, c);
            } else {
                fn_8002CBB0(lbl_803EA368, a, c, b);
            }
        }
    } else if (b != 0x8F) {
        if (!fn_8002D060(lbl_803EA368) || fn_8002D2C0()) {
            UISGameHandleInput(a, b, c);
        } else {
            fn_8002CBB0(lbl_803EA368, a, c, b);
        }
    }
    if (!PauseIsOpen() || fn_8002D060(lbl_803EA368) || b == 0x8F) {
        PauseIsOpen();
    } else {
        UISGameRefreshAll();
    }
    if (_InGame_bCancelRequest == 1) {
        PauseRequestClose();
        _InGame_bCancelRequest = 0;
    }
}

static void _InGameEndDemo();
static void _InGameDemoPadHook();

static void _InGameDemoPadRead(int a, InputValues *pPrevious, InputValues *pCurrent)
{
    char *p;
    int count;
    int handle;
    int i;
    int done;

    PadInputRead(a, pPrevious, pCurrent);
    p = PadInputGetDeviceData();
    count = PadInputGetValueCount();
    handle = ConGetChannelInfo(a, 0);
    PerCheckConnectSingle(handle);
    if (PerIsDeviceConnected(handle)) {
        fn_801E15D0(handle);
        fn_801E17D0(handle, p);
        _InGameDemoPadHook();
        if (_InGame_bDemo && PadInputIsDeviceReady(handle)) {
            done = 0;
            for (i = 0; i < count; i++) {
                float value = fabs(RemapCheckEntry(handle, i, p + 8));

                if (value <= 0.5f || done) {
                    continue;
                }
                done = 1;
                _InGameEndDemo();
            }
        }
    }
}

static void _InGameUpdateHook1() {}
static void _InGameUpdateHook2() {}
static void _InGameUpdateHook3() {}

static void _InGameEndDemo()
{
    fn_80072C90(0xFA, 1);
    _InGame_uIdleFrames = 0;
    if (_InGame_bIdle) {
        _InGame_bIdle = 0;
        fn_8007F6F8(9, 1);
        RumbleShutdown();
        RumbleInit();
        RumbleEnable(1);
    }
    InGameStop();
    ConSetChannelInfo(-1, 2, (void *)PadInputRead);
}

static void _InGameDemoPadHook() {}

ModuleDependency *InGame::GetDependencies() { return sDependencies; }
ModuleDependency *InGame::GetLinks() { return 0; }
const char *InGame::GetName() { return "InGame"; }

void InGameStop()
{
    AudmonEventPost(0x84, 0);
    fn_800C1E50();
    _InGame_bRunning = 0;
}

int InGameIsStopped()
{
    return !_InGame_bRunning;
}

int InGame::Init()
{
    DepthChartSide_t record0;
    DepthChartSide_t record1;
    int a;
    int b;
    int result;

    result = 0;
    _InGame_iFrameCount = 0;
    _InGame_uIdleFrames = 0;
    _InGame_bIdle = 0;
    fn_8007F394(1);
    fn_8008FE5C(0);
    fn_80099568(1);
    fn_8013CF98();
    MemCardUtilInit();
    fn_80066D5C();
    fn_800A216C(1);
    fn_800AE8B4();
    VptManagerMarketCamInit();
    ConSetChannelInfo(-1, 1, (void *)_InGamePadHandler);
    _InGame_bRunning = 1;
    fn_800C8704(&a, &b);
    DepthChartGetSide(0, &record0);
    DepthChartGetSide(1, &record1);
    fn_80085AA0(a, &record0, b, &record1);
    DriveLogInit();
    DriveLogEndDrive();
    ScoringLogInit();
    ScoringLogReset();
    BallsPark();
    _InGame_iPauseCount = 0;
    InGameSetInputPaused(0);
    PadInputSetAxisCallback(CamGameGetSideYaw);
    fn_801FCE10(0, "select 'PNIG' into \x82 from 'FNIG'\n", &result);
    fn_80057F28();
    if (result) {
        fn_800AD910(10, 0.0f);
    } else {
        unsigned int value = GameModeTypeGet();

        if (value <= 11 || value == 13) {
            fn_800AD910(1, 0.0f);
        }
    }
    fn_80187C0C();
    fn_8005BF18();
    if (!fn_800BA6F8()) {
        CamGameApplyUserCamera();
        if (!result && !fn_800C1E40()) {
            fn_800BCF7C(lbl_803EAB90);
        }
    } else {
        CamGameApplyUserCamera();
    }
    if (InGameIsDemo()) {
        ConSetChannelInfo(-1, 2, (void *)_InGameDemoPadRead);
    }
    fn_80194AEC(0);
    fn_80239CEC(0x80000000, (u32)OSGetArenaHi() + 0x80000000);
    EngineParamWords desc = { 4, 14 };
    fn_802345C4(&desc, 2);
    UISGameLoadKeyItem(1, 3);
    UISGameLoadKeyItem(1, 0);
    AudmonEventPost(0x6A, 0);
    fn_80218FC4(gUISSubInfo, 1, 5, 0, 0);
    return _InGame_bRunning;
}

unsigned char InGame::Update()
{
    int handled;
    unsigned int count;

    fn_80236F34();
    handled = 0;
    UISGameRefreshAll();
    _InGameUpdateHook1();
    _InGameUpdateHook2();
    _InGameUpdateHook3();
    fn_801D6F58();
    if (_InGame_uIdleFrames > 10800) {
        if (fn_8007F828(9)) {
            _InGame_bIdle = 1;
            fn_8007F6F8(9, 0);
            RumbleShutdown();
            RumbleInit();
            RumbleEnable(0);
        }
    } else {
        if (_InGame_bIdle) {
            _InGame_bIdle = 0;
            fn_8007F6F8(9, 1);
            RumbleShutdown();
            RumbleInit();
            RumbleEnable(1);
        }
        _InGame_uIdleFrames++;
    }
    RumbleProcess();
    TimeScaleUpdate();
    if (_InGame_iPauseCount == 0) {
        _InGame_iFrameCount++;
        fn_80237830(1);
    }
    while ((count = fn_802378C8()) != 0) {
        float value = count;

        handled = 1;
        fn_800AD888(value * gFrameTimeScale);
        BannerUpdate(value);
    }
    if (!handled) {
        ConUpdateChannel(-1);
        ConProcessChannel(-1);
    }
    PauseUpdate();
    fn_8002CF34(lbl_803EA368);
    if (!fn_8002D060(lbl_803EA368)) {
        ParticlesProcess(gFrameTimeScale);
        fn_80144EDC(gFrameTimeScale);
        fn_800A3120(gFrameTimeScale);
    }
    FileDebugProcess();
    fn_8003E1F0();
    fn_80043F50();
    fn_800A7F6C();
    fn_800728F8();
    fn_800726B8();
    fn_80195F80();
    SndgUpdate(1);
    fn_801CE82C();
    VptProcessViewports();
    fn_80236F34();
    if (_InGame_pFrameCallback) {
        _InGame_pFrameCallback();
    }
    if (!_InGame_bRunning) {
        if (fn_800A937C() || fn_800A9680()) {
            fn_800A9478(1);
        }
    }
    return _InGame_bRunning;
}

int InGame::Shutdown()
{
    TimeScaleReset();
    fn_800A8EB8();
    if (_InGame_bDemo) {
        _InGame_uIdleFrames = 0;
        if (_InGame_bIdle) {
            _InGame_bIdle = 0;
            fn_8007F6F8(9, 1);
            RumbleShutdown();
            RumbleInit();
            RumbleEnable(1);
        }
    }
    UISGameFreeKeyItem(1, 0);
    UISGameFreeKeyItem(1, 3);
    fn_8021956C(gUISSubInfo, 1, 5, 0);
    EngineParamWords desc = { 6, 14 };
    fn_802345C4(&desc, 2);
    fn_80085A7C();
    fn_8007F394(0);
    PadInputSetAxisCallback(0);
    fn_80196130();
    PauseUpdate();
    fn_801CE910();
    fn_800582D0();
    fn_800AB944(lbl_803EAA8C);
    PlaybookSideClearAll();
    MemCardUtilShutdown();
    ConSetChannelInfo(-1, 2, (void *)PadInputRead);
    GameModeTypeInvalidate();
    MemCardScreenSetFlag(_InGame_bDemo);
    _InGame_bDemo = 0;
    return 1;
}

void InGamePause()
{
    _InGame_iPauseCount++;
    InGameSetInputPaused(1);
    if (fn_800AD9B4() == 5) {
        fn_800B410C();
        fn_8021956C(gUISMainInfo, 3, 2, 1);
    }
}

void InGameResume()
{
    if (--_InGame_iPauseCount == 0) {
        InGameSetInputPaused(0);
        if (fn_800AD9B4() == 5 && _InGame_bRunning) {
            fn_800B3AF4(0.0f);
        } else {
            fn_800B4184(1);
        }
    }
}

void InGameSetInputPaused(int unknown)
{
    _InGame_bInputPaused = unknown;
}

void InGameSetDemo()
{
    _InGame_bDemo = 1;
}

unsigned char InGameIsDemo()
{
    return _InGame_bDemo;
}

int InGameIsPaused()
{
    return _InGame_iPauseCount != 0;
}

int InGameIsPlaying()
{
    int result = 0;
    GSFlowManagerC *p = &gGSFlowManager;

    if (p->fn_801CBE9C(1)) {
        result = !p->fn_801CBE9C(3);
    }
    return result;
}

int InGameGetFrameCount()
{
    return _InGame_iFrameCount;
}
