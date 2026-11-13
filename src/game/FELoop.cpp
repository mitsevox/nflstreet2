/* The front-end loop module: boot screens, the per-frame update of the menus, the screen to return to after a game, and the idle timeout. */

#include "game/GameOptions.h"
#include "game/SndgMusic.h"
#include "engine/viewport.h"
#include "game/FlowManagerC.h"
#include "game/FELoop.h"
#include "game/FMCAPPORT.h"
#include "game/DemoLaunch.h"
#include "game/PadInput.h"
#include "game/GameInfo.h"
#include "game/DepthChartSide.h"
#include "game/fn_80061AD4.h"
#include "game/GameModeType.h"
#include "game/MemCardUtil.h"
#include "game/fn_80218FC4.h"
#include "game/fn_8021D7B8.h"

extern "C" {
extern char gMainFEGroup[];
extern float gFrameTimeScale;
extern void *gUISMainInfo;
extern void *gUISSubInfo;

void fn_80010150(int a);
int fn_80010194(void);
void fn_80011600(int a, int b, int c);
void fn_80014294(int a, int b);
void fn_8001442C(void);
void fn_80015D28(int a);
int fn_80015F2C(void);
void MsgTeamPickFreePool(void);
void FEPlyrUpdate(void);
void BootPlayIntroMovies(void);
void BootShowStartupScreens(void);
void BootUpdateReset(void);
int MainFEGroupIsStarted(void *p);
void fn_8003E1F0(void);
int fn_8005FC7C(void);
int fn_800602E8(void);
int fn_80061CAC(void);
void MemCardScreenSetFlag(unsigned char a);
int PlayBookDbOpen(unsigned int id, int a, int b, int c, int d, int e);
void PlayBookDbClose(unsigned int id, int a);
void SndgUpdate(int a);
void SndgApplyVolumeOptions(void);
void SndgMusicFadeOut(int a, int b);
void SndgMusicPumpFrame(int a);
void fn_8009418C(void);
void CamSetupAspect(void);
void FEPlyrLoadUpdate(void);
void MsgGameSetFEStarted(int a);
void fn_80186EF4(void);
void GameTextReset(void);
void GameTextServiceReset(void);
void GameTextSetSetupActive(int a);
void TeamLogoInit(void);
void TeamLogoShutdown(void);
void UISGameHandleInput(int a, unsigned int id, float value);
void UISGameRefreshAll(void);
void RumbleProcess(void);
int ConUpdateChannel(int a);
int ConProcessChannel(int a);
int ConSetChannelInfo(int a, int b, void *pValue);
void CamSetDefaultAspect(float a);
void FileDebugProcess(void);
void fn_801CE82C(void);
void fn_801CE910(void);
int fn_801CEB4C(void);
void fn_801D6F58(void);
void ResTrackLabel(const char *pText);
void fn_8021956C(void *p, int a, int b, int c);
void fn_80219650(void *p, unsigned short *pA, unsigned short *pB);
int fn_802294F4(void);
int fn_80229554(void);
void fn_802297B0(void);
int fn_80232FD4(DepthChartSide_t *pRecord0, DepthChartSide_t *pRecord1);
}

static unsigned char _FELoop_uResumeMode = 0;
static unsigned char _FELoop_bResume = 0;
static unsigned int _FELoop_uIdleFrames = 0;
static unsigned char _FELoop_bIdleTimeout = 0;
static FELoopCallback _FELoop_pFrameCallback = 0;
static void *sDependencies[] = { 0 };
static unsigned char _FELoop_bVisited = 0;
static unsigned int _FELoop_uModeType;
static unsigned char _FELoop_bRunning;

FELoop gFELoop;

static void _FELoopEnterDefault()
{
    int args[2];
    void *p;

    MsgGameSetFEStarted(1);
    p = gUISMainInfo;
    args[0] = 0;
    if (_FELoop_bVisited) {
        args[1] = 100;
    } else {
        args[1] = 101;
    }
    fn_80218FC4(p, 0, 2, 2, args);
    fn_80218FC4(gUISSubInfo, 1, 5, 0, 0);
}

static void _FELoopEnterMode0()
{
    int args[2];
    void *p;

    MsgGameSetFEStarted(1);
    p = gUISMainInfo;
    args[0] = 0;
    args[1] = 100;
    fn_80218FC4(p, 0, 2, 2, args);
    fn_80218FC4(gUISSubInfo, 1, 5, 0, 0);
}

static void _FELoopEnterMode8()
{
    int args[2];

    FELoopRefreshModeType();
    args[0] = 1;
    fn_80010150(8);
    fn_80218FC4(gUISMainInfo, 11, 1, 1, args);
    fn_80218FC4(gUISSubInfo, 1, 5, 0, 0);
}

static void _FELoopEnterMode6()
{
    int args[2];

    FELoopRefreshModeType();
    args[0] = 1;
    fn_80010150(6);
    fn_80218FC4(gUISMainInfo, 8, 2, 1, args);
    fn_80218FC4(gUISSubInfo, 1, 5, 0, 0);
}

static void _FELoopEnterMode7()
{
    int args[2];

    FELoopRefreshModeType();
    args[0] = fn_800602E8() ? 401 : 1;
    fn_80010150(7);
    fn_80218FC4(gUISMainInfo, 12, 0, 1, args);
    fn_80218FC4(gUISSubInfo, 1, 5, 0, 0);
}

static void _FELoopEnterMode10()
{
    int args[2];

    FELoopRefreshModeType();
    args[0] = 123;
    fn_80010150(7);
    fn_80218FC4(gUISMainInfo, 12, 0, 1, args);
    fn_80218FC4(gUISSubInfo, 1, 5, 0, 0);
}

static void _FELoopEnterMode10Alt()
{
    int args[2];

    FELoopRefreshModeType();
    args[0] = 604;
    fn_80010150(7);
    fn_80218FC4(gUISMainInfo, 12, 0, 1, args);
    fn_80218FC4(gUISSubInfo, 1, 5, 0, 0);
}

static void _FELoopEnterMode11()
{
    int args[2];

    FELoopRefreshModeType();
    args[0] = 1;
    fn_80010150(11);
    fn_80218FC4(gUISMainInfo, 7, 17, 1, args);
    fn_80218FC4(gUISSubInfo, 1, 5, 0, 0);
}

static void _FELoopEnterMode9()
{
    int args[2];

    FELoopRefreshModeType();
    args[0] = 700;
    fn_80010150(9);
    fn_80218FC4(gUISMainInfo, 13, 0, 1, args);
    fn_80218FC4(gUISSubInfo, 1, 5, 0, 0);
}

static void _FELoopEnterMode2()
{
    int args[2];

    FELoopRefreshModeType();
    args[0] = 1;
    args[1] = 109;
    fn_80218FC4(gUISMainInfo, 0, 2, 2, args);
    fn_80218FC4(gUISSubInfo, 1, 5, 0, 0);
}

static void _FELoopEnterModeScreen(int mode)
{
    FELoopSetResume(0);
    switch (mode) {
    case 3:
    case 4:
    case 5:
    case 13:
        break;
    case 9:
        _FELoopEnterMode9();
        break;
    case 6:
        _FELoopEnterMode6();
        break;
    case 0:
        _FELoopEnterMode0();
        break;
    case 2:
        _FELoopEnterMode2();
        break;
    case 8:
        _FELoopEnterMode8();
        break;
    case 7:
        fn_8005FC7C();
        _FELoopEnterMode7();
        break;
    case 10:
        fn_80061AD4();
        if (fn_80061CAC()) {
            _FELoopEnterMode10Alt();
        } else {
            _FELoopEnterMode10();
        }
        break;
    case 11:
        _FELoopEnterMode11();
        break;
    default:
        if (DemoLaunchIsFlagSet()) {
            DemoLaunchSetFlag(0);
        }
        _FELoopEnterDefault();
        break;
    }
    FELoopSetResumeMode(0);
}

static void _FELoopPadHandler(int a, int b, float c)
{
    if (b == 0x46) {
        _FELoop_bRunning = 0;
    }
    MemCardUtilHandleEvent(a, b, c);
    if (!gFMCAPPORT.IsBusy()) {
        UISGameHandleInput(a, b, c);
    }
    UISGameRefreshAll();
    if (b != 0x8F) {
        MemCardScreenSetFlag(0);
        _FELoop_uIdleFrames = 0;
    }
}

static void _FELoopBootSetup()
{
    ConSetChannelInfo(-1, 1, (void *)_FELoopPadHandler);
    PadInputSetDefaultHandler();
    GameOptionsShutdown();
    BootShowStartupScreens();
    GameOptionsInit(0);
    SndgApplyVolumeOptions();
    SndgMusicReshuffle();
    ConSetChannelInfo(-1, 1, 0);
}

void FELoop::Boot()
{
    ResTrackLabel("FELoopBootStart");
    _FELoopBootSetup();
    GameTextServiceReset();
    if (GameOptionsGet(6) == 1 || fn_801CEB4C() == 1) {
        CamSetDefaultAspect(4.0f / 3.0f);
    } else {
        CamSetupAspect();
    }
    fn_80186EF4();
    BootPlayIntroMovies();
    ResTrackLabel("FELoopBootFinish");
}

void FELoopStartGame()
{
    if (_FELoop_bRunning) {
        DepthChartSide_t record0;
        DepthChartSide_t record1;

        _FELoop_bRunning = 0;
        MsgTeamPickFreePool();
        SndgMusicPumpFrame(1);
        DepthChartGetSide(0, &record0);
        SndgMusicPumpFrame(1);
        DepthChartGetSide(1, &record1);
        SndgMusicPumpFrame(1);
        fn_80232FD4(&record0, &record1);
        SndgMusicPumpFrame(1);
        GameInfoRead();
        fn_8021956C(gUISSubInfo, 1, 5, 1);
        SndgMusicPumpFrame(1);
        gGSFlowManager.fn_801CBEF4(2, 12);
    }
}

void FELoopConfigureEntry(int a, int b, int c, int d, int e, int f)
{
    fn_80010150(a);
    if (b == -1 && c == -1) {
        fn_80011600(-1, -1, 0);
    } else {
        fn_80011600(b, c, 1);
    }
    fn_80014294(d, e);
    fn_80015D28(f);
}

ModuleDependency *FELoop::GetDependencies() { return (ModuleDependency *)sDependencies; }
ModuleDependency *FELoop::GetLinks() { return 0; }
const char *FELoop::GetName() { return "FELoop"; }

int FELoop::Init()
{
    GameTextSetSetupActive(0);
    ConSetChannelInfo(-1, 1, (void *)_FELoopPadHandler);
    PadInputSetDefaultHandler();
    PlayBookDbOpen(0x31544250, 2, 4, 0, 0, 1);
    PlayBookDbOpen(0x31444250, 1, 4, 0, 0, 0);
    _FELoop_bRunning = 1;
    GameTextReset();
    if (_FELoop_bResume == 1) {
        if (_FELoop_uResumeMode != 3) {
            fn_802297B0();
        }
    } else if (fn_802294F4() == 1) {
        fn_802297B0();
        FELoopRefreshModeType();
    }
    _FELoop_uModeType = GameModeTypeGet();
    TeamLogoInit();
    _FELoopEnterModeScreen(_FELoop_uModeType);
    _FELoop_uIdleFrames = 0;
    _FELoop_bIdleTimeout = 0;
    return 1;
}

unsigned char FELoop::Update()
{
    unsigned short a;
    unsigned short b;
    int flag = 1;

    BootUpdateReset();
    UISGameRefreshAll();
    fn_801D6F58();
    ConUpdateChannel(-1);
    ConProcessChannel(-1);
    FEPlyrUpdate();
    fn_8003E1F0();
    FEPlyrLoadUpdate();
    gFMCAPPORT.Update();
    fn_80219650(gUISMainInfo, &a, &b);
    if (a == 0 && b == 7) {
        fn_8001442C();
    }
    RumbleProcess();
    if (flag) {
        VptProcessViewports();
        FileDebugProcess();
        SndgUpdate(1);
        fn_801CE82C();
        if (_FELoop_pFrameCallback) {
            _FELoop_pFrameCallback();
        }
        if (fn_80010194() || fn_80015F2C()) {
            if (++_FELoop_uIdleFrames > (int)(60.0f / gFrameTimeScale) * 75) {
                fn_8021D7B8(gUISMainInfo, 0x80000038, 0, 0);
                SndgMusicFadeOut(0xFA, 1);
                _FELoop_bIdleTimeout = 1;
            }
        }
    }
    return _FELoop_bRunning;
}

int FELoop::Shutdown()
{
    TeamLogoShutdown();
    fn_801CE910();
    PlayBookDbClose(0x31544250, 0);
    PlayBookDbClose(0x31444250, 0);
    fn_8009418C();
    ConSetChannelInfo(-1, 1, 0);
    _FELoop_uIdleFrames = 0;
    _FELoop_bIdleTimeout = 0;
    return 1;
}

int FELoopIsMainFEActive()
{
    return MainFEGroupIsStarted(gMainFEGroup);
}

void FELoopSetResume(unsigned char value)
{
    if (_FELoop_bVisited) {
        _FELoop_bResume = value;
    } else {
        _FELoop_bResume = 0;
    }
}

void FELoopSetResumeMode(unsigned char value)
{
    _FELoop_uResumeMode = value;
}

void FELoopRefreshModeType()
{
    FELoopSetResume(0);
    if (fn_802294F4() == 1) {
        if (GameInfoIsInitialized()) {
            GameInfoShutdown();
        }
        fn_80229554();
    }
    _FELoop_uModeType = GameModeTypeGet();
}

void FELoopSetVisited(unsigned char value)
{
    _FELoop_bVisited = value;
}

unsigned char FELoopWasVisited()
{
    return _FELoop_bVisited;
}

void FELoopSetFrameCallback(FELoopCallback pCallback)
{
    _FELoop_pFrameCallback = pCallback;
}

void FELoopResetIdle()
{
    _FELoop_uIdleFrames = 0;
}

unsigned char FELoopIsIdleTimedOut()
{
    return _FELoop_bIdleTimeout;
}

void FELoopCheckDemoLaunch(int a)
{
    if (_FELoop_bRunning) {
        DemoLaunchIsAllowed();
    }
}
