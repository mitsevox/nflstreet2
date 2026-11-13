/* Pause manager: opens a menu screen over the running game (the pause menu,
   tutorials and other popups), holds the game state, camera, rumble and audio
   while it is up, and puts everything back when it closes. */

#include "game/PadInput.h"
#include "game/PauseMenu.h"
#include "game/AudmonEvent.h"
#include "game/GameEventFlags.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_80096A58.h"
#include "game/fn_80218FC4.h"
#include "game/fn_802372EC.h"
#include "game/InGame.h"
#include "game/PreSnapPhase.h"

typedef void (*PauseNotifyFn_t)(int value);

/* Camera returned by CamGameGetCamera (defined in src/game/camgame.cpp). */
struct GameCamera_t;

/* Object at lbl_803EABA4 (declared in include/game/PreSnapPhase.h). */
class PreSnapPhase;

/* mId is also read as one word, compared with 0x10002, 0x30001 and 0x30016;
   mArgs holds mArgCount words for fn_80218FC4. */
struct PauseState_t {
    int mUnknown0;
    int mState;
    union {
        int mId;
        struct {
            unsigned short mHigh;
            unsigned short mLow;
        } mPair;
    };
    int mArgCount;
    int mArgs[4];
    int mUnknown32;
    int mUnknown36;
    int mUnknown40;
    int mUnknown44;
    PauseNotifyFn_t mCallbacks[1];
    void *mHandlers[20];
    unsigned char mUnknown132;
    int mUnknown136;
    int mUnknown140;
    int mUnknown144;
};

extern "C" {
extern void *lbl_803EA368;
extern void *gUISMainInfo;

void fn_8002C9A8(void *p, int a, int b);
void fn_8002CA74(void *p, int a, int b);
int fn_8002D060(void *p);
int fn_8002D0AC(void *p);
void fn_8002D198(void *p);
int fn_8002D228(void *p);
int fn_80059004(void);
int fn_8005900C(void);
void PauseRequestInit(void);
void fn_8006F824(int a);
void fn_800719D4(void);
void SpchIGPauseChannel(int index);
void SpchIGResumeChannel(int index);
void SpchIGSetEnabled(unsigned char value);
void fn_80094DF0(void);
void fn_8009B924(void);
void fn_8009BA10(int a);
unsigned char fn_8009BA94(void);
int fn_800A3444(void);
int fn_800A8444(int a);
int fn_800A8488(int a);
void fn_800ABD80(void);
void fn_800AD910(int a, float b);
void fn_800B22E0(void);
void fn_800B43C8(void);
void fn_800B4408(void);
int fn_800B81A4(void);
void fn_800BA5B0(void);
void fn_800BF658(int a);
void fn_800BF6CC(int a);
int fn_800BF718(int a);
void fn_800C0330(void *p);
void fn_800C1CA0(void);
int fn_800C1E40(void);
int CamMainGetMode(GameCamera_t *pCamera);
void CamMainWarpToDest(GameCamera_t *pCamera);
void CamGameSelectCamera(int a);
int CamGameGetCurrentSlot(void);
GameCamera_t *CamGameGetCamera(int index);
void CamGameProcess(void);
void CamGameSetModeAll(int a);
void CamGameResumeAll(void);
void fn_80162780(int a, int b);
unsigned char fn_8016278C(void);
void fn_80178370(void);
void BannerClear(int a);
void HudHideMashPrompts(void);
void HudShowPressPrompt(int a);
void HudHidePressPrompt(int a);
void CoinTossOnShotStart(void);
unsigned char GameEventFlagsSetFlag1(unsigned char value);
void fn_80188014(int a);
void UISGameSetLastPad(int a);
void UISGameLockPad(int value);
void UISGameUnlockPad(void);
void UISHeldObjEnable(unsigned char value);
void RumbleStopAll(void);
void RumbleInit(void);
void RumbleInitAllPorts(void);
void RumbleShutdown(void);
void RumbleEnable(int a);
unsigned char RumbleIsEnabled(void);
int ScreenTransGetMode(void);
void fn_801F5D0C(void);
void fn_802195E4(void *p, unsigned short a, unsigned short b);
}

static PauseRequestFn_t *_Pause_apfnRequest = 0;
static unsigned char _Pause_bSavedSwap0 = 0;
static unsigned char _Pause_bSavedSwapUnused = 0;
static unsigned char _Pause_bSavedSwap1 = 0;
static unsigned char _Pause_bSavedRumble = 0;
static int _Pause_iValue = -1;
static unsigned char _Pause_bUnused = 0;
static unsigned char _Pause_bOpened = 1;
static unsigned char _Pause_bSavedViewFlag = 0;
static unsigned char _Pause_bResetFlag = 0;
static unsigned char _Pause_bCallOnClose = 0;
static unsigned char _Pause_bResumeHook = 0;
static unsigned char _Pause_bAudioPaused = 0;
static unsigned char _Pause_bQuit = 0;
static unsigned char _Pause_bAltAction = 0;
static int _Pause_iPollDelay = 0;
static PauseState_t _Pause_State;

extern "C" {

void PauseEnterAudio(void)
{
    fn_8006F824(0);
    fn_800719D4();
    fn_801F5D0C();
    SpchIGPauseChannel(0);
    SpchIGPauseChannel(1);
    SpchIGPauseChannel(2);
    SpchIGSetEnabled(0);
    AudmonEventPost(0x71, 0);
    _Pause_bAudioPaused = 1;
}

void PauseExitAudio(void)
{
    SpchIGSetEnabled(1);
    SpchIGResumeChannel(0);
    SpchIGResumeChannel(1);
    SpchIGResumeChannel(2);
    _Pause_bAudioPaused = 0;
}

void PauseResetState(void)
{
    _Pause_State.mPair.mHigh = 0xFFFF;
    _Pause_State.mPair.mLow = 0xFFFF;
    _Pause_State.mState = 0;
    _Pause_State.mUnknown0 = fn_800AD9B4();
    if (_Pause_State.mUnknown132) {
        PadInputRestoreHandlers(_Pause_State.mHandlers);
        PadInputResetSlot(-1);
        _Pause_State.mUnknown132 = 0;
    }
}

int PauseIsActive(void)
{
    return _Pause_State.mState > 0;
}

void PauseInstallRequests(void)
{
    PauseRequestInit();
}

void PauseCameraStart(void)
{
    Params_80096A58 params;

    _Pause_State.mUnknown136 = -1;
    if (fn_800AD9B4() == 1) {
        return;
    }
    CamGameResumeAll();
    fn_800B43C8();
    _Pause_State.mUnknown136 = -1;
    _Pause_State.mUnknown140 = CamGameGetCurrentSlot();
    _Pause_State.mUnknown144 = CamMainGetMode(CamGameGetCamera(5));
    fn_801C1F94(&params, 0, sizeof(params));
    params.mUnknown40 = 0xFFFF;
    params.mUnknown42 = 0xFFFF;
    switch (fn_800A3444()) {
    case 0:
        params.mUnknown0 = 13;
        break;
    case 2:
        params.mUnknown0 = 1;
        break;
    case 3:
        params.mUnknown0 = 25;
        break;
    case 1:
        params.mUnknown0 = 19;
        break;
    case 4:
        params.mUnknown0 = 7;
        break;
    case 5:
        params.mUnknown0 = 32;
        break;
    case 6:
        params.mUnknown0 = 35;
        break;
    case 7:
        params.mUnknown0 = 29;
        break;
    case 8:
        params.mUnknown0 = 10;
        break;
    case 10:
        params.mUnknown0 = 16;
        break;
    case 11:
        params.mUnknown0 = 22;
        break;
    case 9:
    default:
        params.mUnknown0 = 4;
        break;
    }
    params.mUnknown28 = fn_802372EC(1, 3);
    params.mUnknown20 = 2;
    params.mUnknown24 = 0;
    if (_Pause_State.mPair.mHigh != 7 && ScreenTransGetMode() != 5 && !fn_8002D0AC(lbl_803EA368)
        && fn_800AD9B4() != 7) {
        params.mUnknown12 |= 2;
    }
    params.mUnknown12 |= 0x10;
    params.mUnknown32 = 60.0f;
    _Pause_State.mUnknown136 = fn_80096A58(&params);
}

int PauseCameraUpdate(void)
{
    int result;

    if (_Pause_State.mUnknown136 != -1 && fn_800AD9B4() != 1) {
        result = fn_80096B1C(_Pause_State.mUnknown136);
        if (result) {
            CamGameProcess();
        }
    } else {
        result = 0;
    }
    return result;
}

int PauseCameraRestore(void)
{
    if (!InGameIsStopped() && fn_800AD9B4() != 1) {
        if ((fn_800C1E40() && fn_800AD9B4() == 7) || fn_800AD9B4() != 7) {
            if (_Pause_State.mUnknown136 != -1) {
                fn_80096D14(_Pause_State.mUnknown136);
                _Pause_State.mUnknown136 = -1;
            }
            fn_80162780(_Pause_bSavedViewFlag, _Pause_bSavedViewFlag);
            CamGameSelectCamera(_Pause_State.mUnknown140);
            CamGameSetModeAll(_Pause_State.mUnknown144);
            CamMainWarpToDest(CamGameGetCamera(_Pause_State.mUnknown140));
        }
        if (fn_800AD9B4() == 5 && !fn_80059004() && !fn_8005900C()) {
            fn_800B4408();
        }
    }
    return 0;
}

void PauseCloseHook(void) {}

void PauseCloseRequestHook(void) {}

void PausePollRequests(void)
{
    unsigned int i;
    int enabled = 1;

    if (_Pause_apfnRequest && !InGameIsStopped()) {
        for (i = 0; i < 1; i++) {
            if (_Pause_apfnRequest[i]) {
                unsigned short a;
                unsigned short b;
                int c;

                if (_Pause_apfnRequest[i](&a, &b, &c) && _Pause_State.mUnknown44 == 0) {
                    PauseOpenScreen(a, b, c);
                }
            }
        }
        int value = fn_800B81A4();
        if (value != 0xFF && _Pause_State.mUnknown44 == 0 && enabled) {
            int args[2];

            args[0] = value;
            args[1] = 1;
            PauseOpenScreenArgs(1, 2, value, 2, args, 0);
        }
    }
}

void PauseSetRequestCallback(int index, PauseRequestFn_t pCallback)
{
    _Pause_apfnRequest[index] = pCallback;
}

void PauseClearRequestCallback(int index)
{
    if (PauseIsActive()) {
        PauseClose();
    }
    _Pause_apfnRequest[index] = 0;
}

void PauseInit(void)
{
    int i;

    _Pause_apfnRequest = (PauseRequestFn_t *)fn_801D2B7C(sizeof(PauseRequestFn_t), 0, 0);
    fn_801C1F94(_Pause_apfnRequest, 0, sizeof(PauseRequestFn_t));
    _Pause_State.mUnknown132 = 0;
    PauseResetState();
    PauseInstallRequests();
    _Pause_State.mUnknown44 = 0;
    for (i = 0; i < 1; i++) {
        _Pause_State.mCallbacks[i] = 0;
    }
    _Pause_bResetFlag = 0;
    _Pause_bCallOnClose = 0;
}

void PauseShutdown(void)
{
    int i;

    if (_Pause_apfnRequest) {
        for (i = 0; i < 1; i++) {
            PauseClearRequestCallback(i);
        }
        fn_801D2BD0(_Pause_apfnRequest);
    }
    _Pause_apfnRequest = 0;
    PauseResetState();
}

void PauseOpenScreen(unsigned short a, unsigned short b, int c)
{
    if (a == 10 && b == 0) {
        int arg = 0;

        PauseOpenScreenArgs(10, 0, c, 1, &arg, 0);
    } else {
        PauseOpenScreenArgs(a, b, c, 0, 0, 0);
    }
}

void PauseOpenScreenArgs(unsigned short a, unsigned short b, int c, unsigned int count, int *pArgs, int keep)
{
    int i;
    unsigned char j;

    for (i = 0; i < 1; i++) {
        if (_Pause_State.mCallbacks[i]) {
            _Pause_State.mCallbacks[i](1);
        }
    }
    _Pause_State.mPair.mHigh = a;
    _Pause_State.mPair.mLow = b;
    _Pause_State.mUnknown32 = c;
    _Pause_State.mArgCount = count;
    for (j = 0; j < count && j <= 3; j++) {
        _Pause_State.mArgs[j] = pArgs[j];
    }
    _Pause_State.mState = 1;
    _Pause_bQuit = 0;
    _Pause_bAltAction = 0;
    UISGameSetLastPad(c);
    UISGameLockPad(c);
    fn_800C0330(lbl_803EABA4);
    _Pause_bSavedSwap1 = GameEventFlagsSetFlag1(0);
    _Pause_bSavedSwap0 = GameEventFlagsSetFlag0(2);
    _Pause_State.mUnknown0 = fn_800AD9B4();
    PadInputSaveHandlers(_Pause_State.mHandlers);
    _Pause_State.mUnknown132 = 1;
    PadInputSetDefaultHandler();
    if (!keep) {
        PauseCameraStart();
        _Pause_bSavedViewFlag = fn_8016278C();
    }
    _Pause_bOpened = 1;
    if (fn_8002D060(lbl_803EA368)) {
        fn_8002D198(lbl_803EA368);
    }
    InGamePause();
    _Pause_bSavedRumble = RumbleIsEnabled();
    RumbleStopAll();
    if (_Pause_State.mId == 0x10002 || _Pause_State.mId == 0x30001) {
        PauseEnterAudio();
        RumbleShutdown();
        RumbleInitAllPorts();
    }
    if (_Pause_State.mUnknown0 == 2) {
        if (fn_800A8488(0) && !fn_800A8444(0)) {
            HudHidePressPrompt(0);
        }
        if (fn_800A8488(1) && !fn_800A8444(1)) {
            HudHidePressPrompt(1);
        }
    }
    _Pause_bResumeHook = fn_8009BA94();
    if (_Pause_bResumeHook == 1) {
        fn_8009BA10(0);
    }
    HudHideMashPrompts();
    fn_8002C9A8(lbl_803EA368, 4, 0);
    PauseBlock();
    _Pause_iValue = c;
    UISHeldObjEnable(1);
}

void PauseUpdate(void)
{
    if (!PauseIsActive() && PauseIsUnblocked() && _Pause_iPollDelay == 0) {
        PausePollRequests();
    }
    if (_Pause_iPollDelay != 0) {
        _Pause_iPollDelay--;
    }
    if (PauseIsActive()) {
        fn_8002C9A8(lbl_803EA368, 4, 0);
        switch (_Pause_State.mState) {
        case 1:
            BannerClear(7);
            fn_80218FC4(gUISMainInfo, _Pause_State.mPair.mHigh, _Pause_State.mPair.mLow,
                        _Pause_State.mArgCount, _Pause_State.mArgs);
            fn_802195E4(gUISMainInfo, _Pause_State.mPair.mHigh, _Pause_State.mPair.mLow);
            _Pause_State.mState = 2;
            break;
        case 2:
            if (_Pause_State.mId != 0x10002) {
                PauseCameraUpdate();
            }
            break;
        case 3:
            PauseCloseRequestHook();
            PauseClose();
            break;
        }
    }
}

void PauseRequestClose(void)
{
    if (PauseIsActive()) {
        _Pause_State.mState = 3;
    }
}

void PauseClose(void)
{
    int i;

    _Pause_iValue = -1;
    UISGameUnlockPad();
    UISHeldObjEnable(0);
    PauseCameraRestore();
    if (_Pause_bResetFlag == 1) {
        _Pause_bResetFlag = 0;
    }
    PauseUnblock();
    PadInputRestoreHandlers(_Pause_State.mHandlers);
    PadInputResetSlot(-1);
    _Pause_State.mUnknown132 = 0;
    InGameResume();
    RumbleShutdown();
    RumbleInit();
    RumbleEnable(_Pause_bSavedRumble);
    CoinTossOnShotStart();
    fn_800ABD80();
    fn_800B22E0();
    fn_80188014(0);
    if (PauseIsAudioPaused()) {
        PauseExitAudio();
    }
    if (_Pause_State.mId == 0x30016) {
        AudmonEventPostArgs(0x72, 0, _Pause_bQuit, 0, 0);
    }
    if (_Pause_State.mUnknown0 == 2) {
        if (fn_800A8488(0) && !fn_800A8444(0)) {
            HudShowPressPrompt(0);
        }
        if (fn_800A8488(1) && !fn_800A8444(1)) {
            HudShowPressPrompt(1);
        }
    }
    if (_Pause_State.mUnknown0 != fn_800AD9B4()) {
        fn_800AD910(_Pause_State.mUnknown0, 0.0f);
    }
    PauseResetState();
    fn_800BA5B0();
    fn_8002C9A8(lbl_803EA368, 5, 0);
    GameEventFlagsSetFlag1(_Pause_bSavedSwap1);
    GameEventFlagsSetFlag0(_Pause_bSavedSwap0);
    PauseCloseHook();
    if (fn_800BF718(1)) {
        int busy = InGameIsStopped() || _Pause_bQuit || _Pause_bAltAction || _Pause_bCallOnClose;

        if (busy) {
            fn_800BF6CC(1);
        } else {
            fn_800BF658(1);
        }
    }
    for (i = 0; i < 1; i++) {
        if (_Pause_State.mCallbacks[i]) {
            _Pause_State.mCallbacks[i](0);
        }
    }
    if (_Pause_bCallOnClose) {
        fn_80178370();
        _Pause_bCallOnClose = 0;
    }
    if (_Pause_bResumeHook == 1) {
        fn_8009BA10(1);
    }
    if (_Pause_bQuit) {
        fn_8002C9A8(lbl_803EA368, 3, 0);
        if (fn_8002D228(lbl_803EA368) && !fn_8002D060(lbl_803EA368)) {
            fn_8009B924();
            fn_80094DF0();
            fn_8002CA74(lbl_803EA368, 10, PauseGetValue());
            fn_8002CA74(lbl_803EA368, 11, 0);
            fn_8002CA74(lbl_803EA368, 7, 0);
        }
    } else if (_Pause_bAltAction) {
        fn_800C1CA0();
    }
}

void PauseBlock(void)
{
    _Pause_State.mUnknown44++;
}

void PauseUnblock(void)
{
    _Pause_State.mUnknown44--;
}

void PauseClearBlocks(void)
{
    _Pause_State.mUnknown44 = 0;
}

int PauseIsUnblocked(void)
{
    return _Pause_State.mUnknown44 == 0;
}

int PauseIsOpen(void)
{
    return PauseIsActive();
}

int PauseGetSavedMode(void)
{
    return _Pause_State.mUnknown0;
}

void PauseNullHook(void) {}

void PauseClearSavedFlags(void)
{
    _Pause_bSavedSwap0 = 0;
    _Pause_bSavedSwapUnused = 0;
    _Pause_bSavedSwap1 = 0;
}

int PauseGetValue(void)
{
    return _Pause_State.mUnknown32;
}

unsigned char PauseIsAudioPaused(void)
{
    return _Pause_bAudioPaused;
}

void PauseSetQuitFlag(unsigned char value)
{
    if (PauseIsActive()) {
        _Pause_bQuit = value;
    }
}

unsigned char PauseGetQuitFlag(void)
{
    return _Pause_bQuit;
}

void PauseSetSavedRumble(unsigned char value)
{
    _Pause_bSavedRumble = value;
}

void PauseSetAltAction(unsigned char value)
{
    if (PauseIsActive()) {
        _Pause_bAltAction = value;
    }
}

void PauseSetPollDelay(int value)
{
    _Pause_iPollDelay = value;
}

}
