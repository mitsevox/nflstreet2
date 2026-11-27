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
#include "game/StoryTournament.h"
#include "game/GameModeType.h"
#include "game/MemCardUtil.h"
#include "game/fn_80218FC4.h"
#include "game/UISProcessHint.h"

extern "C" {
extern char gMainFEGroup[];
extern float gFrameTimeScale;
extern void *gUISMainInfo;
extern void *gUISSubInfo;

void MsgMainMenuGoTo(int a);
int MsgMainMenuIsShown(void);
void MsgPlayerSelectStart(int a, int b, int c);
void MsgTeamSelectQuickSetup(int a, int b);
void MsgTeamSelectNull(void);
void MsgStadiumStartGame(int a);
int MsgStartScreenIsShown(void);
void MsgTeamPickFreePool(void);
void FEPlyrUpdate(void);
void BootPlayIntroMovies(void);
void BootShowStartupScreens(void);
void BootUpdateReset(void);
int MainFEGroupIsStarted(void *p);
void PlyrObjsDrawShadows(void);
int StoryEventsGetCurrentEvent(void);
int StoryEventsIsWonPickupEvent(void);
int StoryTournamentIsComplete(void);
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
void UserProfileInit(void);
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
void GlibSwapBuffers(void);
void GlibSyncFrame(void);
int GlibGetWidescreenMode(void);
void MemCardMgrUpdate(void);
void ResTrackLabel(const char *pText);
void fn_8021956C(void *p, int a, int b, int c);
void fn_80219650(void *p, unsigned short *pA, unsigned short *pB);
int DbNiomIsModeActive(void);
int DbNiomEndMode(void);
void DbNiomModeResume(void);
int DbManagerEnterMode2(DepthChartSide_t *pRecord0, DepthChartSide_t *pRecord1);
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
    MsgMainMenuGoTo(8);
    fn_80218FC4(gUISMainInfo, 11, 1, 1, args);
    fn_80218FC4(gUISSubInfo, 1, 5, 0, 0);
}

static void _FELoopEnterMode6()
{
    int args[2];

    FELoopRefreshModeType();
    args[0] = 1;
    MsgMainMenuGoTo(6);
    fn_80218FC4(gUISMainInfo, 8, 2, 1, args);
    fn_80218FC4(gUISSubInfo, 1, 5, 0, 0);
}

static void _FELoopEnterMode7()
{
    int args[2];

    FELoopRefreshModeType();
    args[0] = StoryEventsIsWonPickupEvent() ? 401 : 1;
    MsgMainMenuGoTo(7);
    fn_80218FC4(gUISMainInfo, 12, 0, 1, args);
    fn_80218FC4(gUISSubInfo, 1, 5, 0, 0);
}

static void _FELoopEnterMode10()
{
    int args[2];

    FELoopRefreshModeType();
    args[0] = 123;
    MsgMainMenuGoTo(7);
    fn_80218FC4(gUISMainInfo, 12, 0, 1, args);
    fn_80218FC4(gUISSubInfo, 1, 5, 0, 0);
}

static void _FELoopEnterMode10Alt()
{
    int args[2];

    FELoopRefreshModeType();
    args[0] = 604;
    MsgMainMenuGoTo(7);
    fn_80218FC4(gUISMainInfo, 12, 0, 1, args);
    fn_80218FC4(gUISSubInfo, 1, 5, 0, 0);
}

static void _FELoopEnterMode11()
{
    int args[2];

    FELoopRefreshModeType();
    args[0] = 1;
    MsgMainMenuGoTo(11);
    fn_80218FC4(gUISMainInfo, 7, 17, 1, args);
    fn_80218FC4(gUISSubInfo, 1, 5, 0, 0);
}

static void _FELoopEnterMode9()
{
    int args[2];

    FELoopRefreshModeType();
    args[0] = 700;
    MsgMainMenuGoTo(9);
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
        StoryEventsGetCurrentEvent();
        _FELoopEnterMode7();
        break;
    case 10:
        StoryTournamentGetEvent();
        if (StoryTournamentIsComplete()) {
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
    if (GameOptionsGet(6) == 1 || GlibGetWidescreenMode() == 1) {
        CamSetDefaultAspect(4.0f / 3.0f);
    } else {
        CamSetupAspect();
    }
    UserProfileInit();
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
        DbManagerEnterMode2(&record0, &record1);
        SndgMusicPumpFrame(1);
        GameInfoRead();
        fn_8021956C(gUISSubInfo, 1, 5, 1);
        SndgMusicPumpFrame(1);
        gGSFlowManager.QueueTransition(2, 12);
    }
}

void FELoopConfigureEntry(int a, int b, int c, int d, int e, int f)
{
    MsgMainMenuGoTo(a);
    if (b == -1 && c == -1) {
        MsgPlayerSelectStart(-1, -1, 0);
    } else {
        MsgPlayerSelectStart(b, c, 1);
    }
    MsgTeamSelectQuickSetup(d, e);
    MsgStadiumStartGame(f);
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
            DbNiomModeResume();
        }
    } else if (DbNiomIsModeActive() == 1) {
        DbNiomModeResume();
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
    MemCardMgrUpdate();
    ConUpdateChannel(-1);
    ConProcessChannel(-1);
    FEPlyrUpdate();
    PlyrObjsDrawShadows();
    FEPlyrLoadUpdate();
    gFMCAPPORT.Update();
    fn_80219650(gUISMainInfo, &a, &b);
    if (a == 0 && b == 7) {
        MsgTeamSelectNull();
    }
    RumbleProcess();
    if (flag) {
        VptProcessViewports();
        FileDebugProcess();
        SndgUpdate(1);
        GlibSwapBuffers();
        if (_FELoop_pFrameCallback) {
            _FELoop_pFrameCallback();
        }
        if (MsgMainMenuIsShown() || MsgStartScreenIsShown()) {
            if (++_FELoop_uIdleFrames > (int)(60.0f / gFrameTimeScale) * 75) {
                UISProcessHint(gUISMainInfo, 0x80000038, 0, 0);
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
    GlibSyncFrame();
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
    if (DbNiomIsModeActive() == 1) {
        if (GameInfoIsInitialized()) {
            GameInfoShutdown();
        }
        DbNiomEndMode();
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
