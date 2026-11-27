/* End-of-quarter game phase. When a quarter ends the game switches to this
   phase: it shows a quarter-end screen element and waits (an input event can cut
   it short), plays the list of quarter-end clips one after another while the
   next one loads, may wait on a request, and then moves the game on
   to the next phase, chosen by the game period. */

#include "game/ScreenTransition.h"
#include "game/SyncRandGetRange.h"
#include "game/SyncStateRegister.h"
#include "game/fn_801D2B7C.h"
#include "game/AnimPlayback.h"
#include <string.h>
#include "game/fn_80218FC4.h"
#include "game/fn_800B65A0.h"

#include "game/QuarterEndPhase.h"
#include "game/GameEventFlags.h"
#include "game/Params_80092E54.h"

/* One step of the sequence that mpEntries points to; a step whose first word
   is 0x42 ends it. */
struct QuarterEndClip_t {
    int mUnknown0;
    char mUnknown4[16];
    unsigned char mUnknown20;
};

/* Allocated through SyncStateRegister under the id 'qend' (InitState). */
struct QuarterEndState_t {
    int mUnknown0;
    int mState;
    short mUnknown8;
    unsigned char mUnknown10;
    unsigned char mUnknown11;
    int mUnknown12;
    QuarterEndClip_t *mpEntries;
    int mUnknown20;
    int mUnknown24;
    int mUnknown28;
    unsigned short mUnknown32;
    unsigned char mUnknown34;
    unsigned char mUnknown35;
    unsigned char mUnknown36;
};

struct QuarterEndClipVariant_t {
    int mUnknown0;
    int mUnknown4;
};

extern "C" {
extern void *gUISMainInfo;

void PlayerObjSetDrawReady(int a);
void PauseOpenScreen(int a, int b, int c);
void PauseBlock(void);
int PauseIsOpen(void);
int AnmsIsScenePlaying(unsigned char index);
int AnmsUpdateScene(int handle);
void AnmsCastStartedScene(int handle);
void AnmsReleaseCastStates(int handle);
void AnmsEndScene(int handle);
void AnmsStopCastAnims(int handle);
int fn_8009D86C(void);
int fn_800A3444(void);
void fn_800AD910(int a, float b);
void CallbackListAdd(void (*pCallback)(int, unsigned int));
void CallbackListRemove(void (*pCallback)(int, unsigned int));
void fn_800B14E4(void);
void PlayCallStopHuddleScene(void);
void PlyrLineUpReset(int a);
void BallsSetVisible(int a);
void BallResetToSpot(void);
void PlyrStarSetShown(int a, int b);
void PlayBookSetupTeams(void);
void ScrmTeamToHuddle(int a);
int ClockRuleIsOvertime(void);
void ScrmMirrorField(int a, int b);
int ScrmGetOffenseTeam(void);
int ScrmGetDefenseTeam(void);
int ScrmGetTeamScore(int a);
void ScrmQuarterEnd(void);
void BannerClear(int a);
void HudStop(void);
void CoinTossApplyResultSwapped(void);
int ResSync(int a);
void fn_80219650(void *p, unsigned short *pA, unsigned short *pB);
void fn_8021956C(void *p, int a, int b, int c);
void *SyncStateGetData(void *pHandle);
}

static QuarterEndState_t *_QuarterEnd_pState = 0;
static QuarterEndPhase _QuarterEnd_Phase;
QuarterEndPhase *gQuarterEndPhase = &_QuarterEnd_Phase;
static unsigned char _QuarterEnd_uClipIndex = 0;
static unsigned char _QuarterEnd_uBufferIndex = 0;
static unsigned char _QuarterEnd_bElementShown = 0;
static void *_QuarterEnd_apClipBuffers[1];
static QuarterEndClipVariant_t _QuarterEnd_aClipVariants[3] = { { 1, 0 }, { 1, 1 }, { 2, 0 } };

extern "C" {
unsigned char QuarterEndNextBufferIndex(void)
{
    if (++_QuarterEnd_uBufferIndex >= sizeof(_QuarterEnd_apClipBuffers) / sizeof(_QuarterEnd_apClipBuffers[0])) {
        _QuarterEnd_uBufferIndex = 0;
    }
    return _QuarterEnd_uBufferIndex;
}

int QuarterEndIsClipPlaying(void)
{
    int result = 0;

    if (_QuarterEnd_pState->mUnknown20 != -1 && AnmsUpdateScene(_QuarterEnd_pState->mUnknown20)) {
        result = 1;
    }
    return result;
}

void QuarterEndCleanupStub(void) {}

void QuarterEndFreeBuffers(void)
{
    unsigned int i;

    for (i = 0; i < sizeof(_QuarterEnd_apClipBuffers) / sizeof(_QuarterEnd_apClipBuffers[0]); i++) {
        if (_QuarterEnd_apClipBuffers[i] != 0) {
            fn_801D2BD0(_QuarterEnd_apClipBuffers[i]);
            _QuarterEnd_apClipBuffers[i] = 0;
        }
    }
}

void QuarterEndStopClips(void)
{
    ResSync(0);
    if (_QuarterEnd_pState->mUnknown28 != -1) {
        AnmsStopCastAnims(_QuarterEnd_pState->mUnknown28);
        AnmsEndScene(_QuarterEnd_pState->mUnknown28);
        _QuarterEnd_pState->mUnknown28 = -1;
    }
    if (_QuarterEnd_pState->mUnknown20 != -1) {
        AnmsStopCastAnims(_QuarterEnd_pState->mUnknown20);
        AnmsEndScene(_QuarterEnd_pState->mUnknown20);
        _QuarterEnd_pState->mUnknown20 = -1;
    }
    if (_QuarterEnd_pState->mUnknown24 != -1) {
        AnmsEndScene(_QuarterEnd_pState->mUnknown24);
        _QuarterEnd_pState->mUnknown24 = -1;
    }
    QuarterEndCleanupStub();
    PlayerObjSetDrawReady(1);
    BallsSetVisible(1);
    QuarterEndFreeBuffers();
    ScreenTransStart(1, 20, 0x808080, 0);
}

void QuarterEndClearClipHandles(void)
{
    _QuarterEnd_pState->mUnknown20 = -1;
    _QuarterEnd_pState->mUnknown24 = -1;
    _QuarterEnd_pState->mUnknown28 = -1;
}

void QuarterEndLoadClip(int a, void *pBuffer, int size)
{
    Params_80092E54 params;
    int index;

    memset(&params, 0, sizeof(params));
    params.mUnknown0 = a;
    params.mUnknown8 = 36;
    index = SyncRandGetRange(0, 3);
    params.mUnknownE0.mUnknown0 = 1;
    params.mUnknownE0.mUnknown4.mWord = _QuarterEnd_aClipVariants[index].mUnknown0;
    params.mUnknownE0.mUnknown8.mWord = _QuarterEnd_aClipVariants[index].mUnknown4;
    _QuarterEnd_pState->mUnknown24 = AnmsStartScene(&params, pBuffer, size);
}

void QuarterEndStartLoadedClip(void)
{
    AnmsCastStartedScene(_QuarterEnd_pState->mUnknown24);
    _QuarterEnd_pState->mUnknown28 = _QuarterEnd_pState->mUnknown20;
    _QuarterEnd_pState->mUnknown20 = _QuarterEnd_pState->mUnknown24;
}

void QuarterEndSwitchClip(void)
{
    AnmsStopCastAnims(_QuarterEnd_pState->mUnknown20);
    AnmsReleaseCastStates(_QuarterEnd_pState->mUnknown20);
    AnmsEndScene(_QuarterEnd_pState->mUnknown28);
    AnmsCastStartedScene(_QuarterEnd_pState->mUnknown24);
    _QuarterEnd_pState->mUnknown28 = _QuarterEnd_pState->mUnknown20;
    _QuarterEnd_pState->mUnknown20 = _QuarterEnd_pState->mUnknown24;
    _QuarterEnd_pState->mUnknown24 = -1;
    AnmsUpdateScene(_QuarterEnd_pState->mUnknown20);
}

void QuarterEndPreloadClip(QuarterEndClip_t *pEntries, int index)
{
    if (_QuarterEnd_pState->mpEntries[index].mUnknown0 != 0x42) {
        int size = 0;
        void *pBuffer = 0;

        if (pEntries[index].mUnknown20 == 1) {
            size = 0x57800;
            pBuffer = _QuarterEnd_apClipBuffers[_QuarterEnd_uBufferIndex];
            _QuarterEnd_uBufferIndex = QuarterEndNextBufferIndex();
        }
        QuarterEndLoadClip(pEntries[index].mUnknown0, pBuffer, size);
    }
}

void QuarterEndOnEvent(int a, unsigned int b);

void QuarterEndFinish(void)
{
    CallbackListRemove(QuarterEndOnEvent);
    if (_QuarterEnd_pState->mUnknown11) {
        if (fn_8009D86C() != 6) {
            PauseOpenScreen(3, 1, -1);
            _QuarterEnd_pState->mState = 3;
        } else {
            _QuarterEnd_pState->mState = 4;
        }
    } else {
        _QuarterEnd_pState->mState = 4;
    }
}

void QuarterEndStartClips(void)
{
    if (_QuarterEnd_pState->mpEntries[_QuarterEnd_uClipIndex].mUnknown0 == 0x42) {
        QuarterEndFinish();
    } else {
        QuarterEndStartLoadedClip();
        QuarterEndPreloadClip(_QuarterEnd_pState->mpEntries, _QuarterEnd_uClipIndex + 1);
        _QuarterEnd_pState->mUnknown32 = 0;
        _QuarterEnd_pState->mState = 2;
    }
}

void QuarterEndEndWait(void)
{
    _QuarterEnd_pState->mUnknown10 = 0;
    if (_QuarterEnd_pState->mUnknown12 != -1) {
        AnimPlaybackStop(_QuarterEnd_pState->mUnknown12);
        _QuarterEnd_pState->mUnknown12 = -1;
    }
    if (_QuarterEnd_pState->mUnknown36) {
        QuarterEndStartClips();
    } else {
        QuarterEndFinish();
    }
}

void QuarterEndOnEvent(int a, unsigned int b)
{
    switch (b) {
    case 0:
        if (fn_8009D86C() != 6) {
            _QuarterEnd_pState->mUnknown8 = 181;
        }
        break;
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
        break;
    default:
        return;
    }
    if (_QuarterEnd_pState->mUnknown10) {
        if (_QuarterEnd_pState->mUnknown8 > 90) {
            _QuarterEnd_pState->mUnknown8 = 181;
            QuarterEndEndWait();
        }
    } else if (_QuarterEnd_pState->mState <= 2 && _QuarterEnd_pState->mUnknown32 > 60) {
        QuarterEndStopClips();
        QuarterEndFinish();
    }
}

void QuarterEndStartVenueEffect(void)
{
    Params_80096A58 params;

    PlayCallStopHuddleScene();
    memset(&params, 0, sizeof(params));
    params.mUnknown40 = 0xFFFF;
    params.mUnknown42 = 0xFFFF;
    switch (fn_800A3444()) {
    case 0:
        params.mUnknown0 = 14;
        break;
    case 2:
        params.mUnknown0 = 2;
        break;
    case 3:
        params.mUnknown0 = 26;
        break;
    case 1:
        params.mUnknown0 = 20;
        break;
    case 4:
        params.mUnknown0 = 8;
        break;
    case 5:
        params.mUnknown0 = 33;
        break;
    case 6:
        params.mUnknown0 = 36;
        break;
    case 7:
        params.mUnknown0 = 30;
        break;
    case 8:
        params.mUnknown0 = 11;
        break;
    case 10:
        params.mUnknown0 = 17;
        break;
    case 11:
        params.mUnknown0 = 23;
        break;
    case 9:
    default:
        params.mUnknown0 = 5;
        break;
    }
    params.mUnknown28 = SyncRandGetRange(1, 2);
    params.mUnknown20 = 2;
    params.mUnknown24 = 0;
    params.mUnknown12 |= 0x10;
    _QuarterEnd_pState->mUnknown12 = AnimPlaybackStart(&params);
}

void QuarterEndPeriodTwoStub(void) {}
}

void QuarterEndPhase::InitState()
{
    void *pHandle = SyncStateRegister(0, (void **)&_QuarterEnd_pState, sizeof(QuarterEndState_t), 0, 0x71656E64);

    SyncStateGetData(pHandle);
    SyncStateCommit(pHandle);
}

void QuarterEndPhase::OnEnter()
{
    fn_800B14E4();
    _QuarterEnd_pState->mState = 0;
    ScrmMirrorField(1, 0);
    _QuarterEnd_pState->mUnknown0 = fn_8009D86C();
    GameEventFlagsSetFlag0(0);
    _QuarterEnd_pState->mUnknown10 = 0;
    _QuarterEnd_pState->mUnknown11 = 0;
    _QuarterEnd_pState->mUnknown36 = 0;
    ScrmQuarterEnd();
    QuarterEndClearClipHandles();
    QuarterEndStartVenueEffect();
}

void QuarterEndPhase::OnUpdate(float f)
{
    unsigned short a = 0;
    unsigned short b = 0;

    PlayerObjSetDrawReady(0);
    switch (_QuarterEnd_pState->mState) {
    case 0:
        _QuarterEnd_bElementShown = 0;
        fn_80219650(gUISMainInfo, &a, &b);
        if (a == 3 && b == 2) {
            break;
        }
        BannerClear(7);
        switch (_QuarterEnd_pState->mUnknown0) {
        case 4:
        case 5:
            if (ScrmGetTeamScore(0) != ScrmGetTeamScore(1)) {
                _QuarterEnd_pState->mUnknown11 = 1;
            }
            break;
        case 2:
            _QuarterEnd_pState->mUnknown11 = 1;
            QuarterEndPeriodTwoStub();
            break;
        default:
            _QuarterEnd_pState->mUnknown11 = 0;
            break;
        }
        if (fn_800B65A0(ScrmGetOffenseTeam()) == 0xFF && fn_800B65A0(ScrmGetDefenseTeam()) == 0xFF) {
            _QuarterEnd_pState->mUnknown11 = 0;
        }
        if (_QuarterEnd_pState->mUnknown11 == 1) {
            PauseBlock();
        }
        _QuarterEnd_pState->mUnknown8 = 0;
        _QuarterEnd_pState->mUnknown10 = 1;
        CallbackListAdd(QuarterEndOnEvent);
        PlyrStarSetShown(1, 1);
        if (fn_8009D86C() == 6) {
            HudStop();
        } else if (fn_8009D86C() == 5) {
            if (ClockRuleIsOvertime()) {
                PlayBookSetupTeams();
                PlyrLineUpReset(1);
            }
        } else {
            ScrmTeamToHuddle(1);
            ScrmTeamToHuddle(0);
        }
        if (fn_8009D86C() != 6 && fn_8009D86C() == 3) {
            CoinTossApplyResultSwapped();
        }
        ScrmQuarterEnd();
        _QuarterEnd_pState->mState = 1;
        break;
    case 1:
        _QuarterEnd_pState->mUnknown8++;
        AnimPlaybackUpdate(_QuarterEnd_pState->mUnknown12);
        if (_QuarterEnd_bElementShown == 0 && _QuarterEnd_pState->mUnknown8 > 59) {
            fn_80218FC4(gUISMainInfo, 3, 5, 0, 0);
            _QuarterEnd_bElementShown = 1;
        }
        if (_QuarterEnd_pState->mUnknown8 > 600) {
            fn_8021956C(gUISMainInfo, 3, 5, 1);
            _QuarterEnd_bElementShown = 0;
            QuarterEndEndWait();
        }
        break;
    case 2:
        _QuarterEnd_pState->mUnknown32++;
        if (QuarterEndIsClipPlaying()) {
            if (AnmsIsScenePlaying(_QuarterEnd_pState->mUnknown20)) {
                PlayerObjSetDrawReady(0);
                BallsSetVisible(0);
            }
        } else {
            _QuarterEnd_uClipIndex++;
            if (_QuarterEnd_pState->mpEntries[_QuarterEnd_uClipIndex].mUnknown0 == 0x42) {
                QuarterEndStopClips();
                QuarterEndFinish();
            } else {
                QuarterEndSwitchClip();
                QuarterEndPreloadClip(_QuarterEnd_pState->mpEntries, _QuarterEnd_uClipIndex + 1);
            }
        }
        break;
    case 3:
        if (PauseIsOpen() == 0) {
            PlyrStarSetShown(1, 1);
            _QuarterEnd_pState->mState = 4;
        }
        break;
    case 4:
        if (fn_8009D86C() != 6) {
            switch (fn_8009D86C()) {
            case 5:
                fn_800AD910(9, f);
                break;
            case 3:
                CoinTossApplyResultSwapped();
                fn_800AD910(5, f);
                BallResetToSpot();
                break;
            default:
                BallResetToSpot();
                fn_800AD910(5, f);
                break;
            }
        } else {
            if (_QuarterEnd_bElementShown) {
                fn_8021956C(gUISMainInfo, 3, 5, 1);
                _QuarterEnd_bElementShown = 0;
            }
            fn_800AD910(7, 0.0f);
        }
        break;
    }
}

void QuarterEndPhase::OnExit()
{
    fn_800B14E4();
    if (_QuarterEnd_pState->mUnknown10) {
        _QuarterEnd_pState->mUnknown10 = 0;
        CallbackListRemove(QuarterEndOnEvent);
    }
    ScrmQuarterEnd();
    _QuarterEnd_pState->mUnknown35 = 0;
    _QuarterEnd_pState->mUnknown36 = 0;
    _QuarterEnd_pState->mpEntries = 0;
    _QuarterEnd_pState->mUnknown34 = 0;
    _QuarterEnd_uClipIndex = 0;
    _QuarterEnd_uBufferIndex = 0;
}

int QuarterEndPhase::IsWaiting()
{
    return _QuarterEnd_pState->mUnknown10 == 1;
}
