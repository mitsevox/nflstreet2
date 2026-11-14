/* The in-game flow group: its three stages (loading into the game, the game
   itself, and the exit back to the front end), the stage changes it allows,
   the modules each stage needs, and the per-frame step that runs the game and
   hands control back to the front-end group when it ends. */
#include "game/InGameGroup.h"
#include "game/ModuleGroup_8003450C.h"
#include "game/GameModules.h"
#include "game/GameState.h"
#include "game/SndgCrowd.h"
#include "game/FlowManagerC.h"
#include "game/InGame.h"
#include "game/FELoop.h"
#include "game/SndgMusic.h"
#include "game/DefPred.h"


extern "C" {
void MemPoolRelease(int a);
void SndgMusicFadeIn(unsigned int delay);
void SndgMusicStop(void);
extern const char _InGameGroup_szName[];
extern FlowStageEntry_t _InGameGroup_aStages[];
extern FlowTransitionEntry_t _InGameGroup_aTransitions[];
}

FlowStageEntry_t _InGameGroup_aStages[] = {
    { 4, "IG Loading" },
    { 5, "IG DuringPlay" },
    { 6, "IG Exit" },
    { -1, 0 },
};

FlowTransitionEntry_t _InGameGroup_aTransitions[] = {
    { 4, 5 },
    { 5, 6 },
    { -1, -1 },
};

const char _InGameGroup_szName[] = "InGame Group";

extern LoadingFEToInGame gLoadingFEToInGame;
extern Timg gTimg;

InGameGroup gInGameGroup;

// FAKEMATCH: the derived entry and its second store of the same pointer only add one instruction per
// entry, so the compiler's CSE table flush falls where the target's does (same table contents)
struct InGameModuleDependency : ModuleDependency {
    InGameModuleDependency(void *pTarget) : ModuleDependency(pTarget) { void **pp = &mpTarget; *pp = pTarget; }
};

static InGameModuleDependency _InGameGroup_aLoadingModules[] = {
    &gMemAudit,
    &gLoadingFEToInGame,
    &gQkl,
    &gGRender,
    &gGameState,
    &gGRand,
    &gCelebration,
    &gScrmRule,
    &gTimg,
    &gAudmon,
    &gAnimintf,
    &gAnimScriptMan,
    &gArrow,
    &gAss,
    &gAssJoy,
    &gBall,
    &gBanner,
    &gBigObj,
    &gBlock,
    &gCamGame,
    &gCamScript,
    &gCatch,
    &gCatchUp,
    &gCld,
    &gClock,
    &gCoinToss,
    &gEffects,
    &gEnv,
    &gGameBrk,
    &gGameIntf,
    &gGamePlay,
    &gGameSkill,
    &gHotRt,
    &gID3Read,
    &gIGNetEvent,
    &gIGOnline,
    &gJoyMsg,
    &gLight,
    &gMiM,
    &gMonitor,
    &gParticles,
    &gPenalty,
    &gPlayArtMem,
    &gPlayInfo,
    &gPlayTrack,
    &gPlayBook,
    &gPlyr,
    &gPlyrCtrl,
    &gPlyrMsg,
    &gPractice,
    &gPursuit,
    &gRenderBin,
    &gScreenTint,
    &gShadows,
    &gSideAvoid,
    &gSimpShadow,
    &gSndgIG,
    &gSndgCrowd,
    &gSndgReplay,
    &gStatcoll,
    &gStatics,
    &gSub,
    &gTrk,
    &gTurbo,
    &gColorStyle,
    &gVptMgr,
    &gMiniGame,
    &gTutorialGame,
    &gGameStateActivate,
    &gPause,
    &gReplay,
    &gReplayFrame,
    &gRumble,
    &gDefPred,
    &gUIS,
    0,
};

static InGameModuleDependency _InGameGroup_aDuringPlayModules[] = {
    &gMemAudit,
    &gGRender,
    &gGameState,
    &gGRand,
    &gCelebration,
    &gScrmRule,
    &gTimg,
    &gAudmon,
    &gAnimintf,
    &gAnimScriptMan,
    &gArrow,
    &gAss,
    &gAssJoy,
    &gBall,
    &gBanner,
    &gBigObj,
    &gBlock,
    &gCamGame,
    &gCamScript,
    &gCatch,
    &gCatchUp,
    &gCld,
    &gClock,
    &gCoinToss,
    &gEffects,
    &gEnv,
    &gGameBrk,
    &gGameIntf,
    &gGamePlay,
    &gGameSkill,
    &gHotRt,
    &gID3Read,
    &gIGNetEvent,
    &gIGOnline,
    &gJoyMsg,
    &gLight,
    &gMiM,
    &gMonitor,
    &gParticles,
    &gPenalty,
    &gPlayArtMem,
    &gPlayInfo,
    &gPlayTrack,
    &gPlayBook,
    &gPlyr,
    &gPlyrCtrl,
    &gPlyrMsg,
    &gPractice,
    &gPursuit,
    &gRenderBin,
    &gScreenTint,
    &gShadows,
    &gSideAvoid,
    &gSimpShadow,
    &gSndgIG,
    &gSndgCrowd,
    &gSndgReplay,
    &gStatcoll,
    &gStatics,
    &gSub,
    &gTrk,
    &gTurbo,
    &gColorStyle,
    &gVptMgr,
    &gMiniGame,
    &gTutorialGame,
    &gGameStateActivate,
    &gPause,
    &gReplay,
    &gReplayFrame,
    &gRumble,
    &gDefPred,
    &gUIS,
    &gInGame,
    0,
};

static InGameModuleDependency _InGameGroup_aExitModules[] = {
    &gMemAudit,
    0,
};

const char *InGameGroup::GSGetGroupName() { return _InGameGroup_szName; }
FlowStageEntry_t *InGameGroup::GSGetStageList() { return _InGameGroup_aStages; }
FlowTransitionEntry_t *InGameGroup::GSGetTransitionList() { return _InGameGroup_aTransitions; }

ModuleDependency *InGameGroup::GSGetStageModuleList(int id)
{
    switch (id) {
    case 4:
        return _InGameGroup_aLoadingModules;
    case 5:
        return _InGameGroup_aDuringPlayModules;
    case 6:
        return _InGameGroup_aExitModules;
    default:
        return 0;
    }
}

void InGameGroup::GSProcess()
{
    GSFlowManagerC *p = &gGSFlowManager;

    if (p->IsGroupStarted(3) == 0) {
        switch (p->GetActiveStage(1)) {
        case 4:
            p->QueueTransition(1, 5);
            break;
        case 5:
            if (!gInGame.Update()) {
                p->QueueTransition(1, 6);
            }
            break;
        case 6:
            p->StopGroup(1);
            MemPoolRelease(1);
            p->StartGroup(2, -1);
            break;
        }
    }
}

int InGameGroup::GSTransition(int a, int id)
{
    switch (id) {
    case 5:
        if (!FELoopWasVisited()) {
            SndgMusicReshuffle();
            SndgMusicContinue();
        } else {
            SndgMusicFadeIn(250);
        }
        break;
    case 6:
        if (!FELoopWasVisited()) {
            SndgMusicStop();
        }
        break;
    }
    return 1;
}
