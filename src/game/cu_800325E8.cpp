#include "game/Class_800325E8.h"
#include "game/ModuleGroup_8003450C.h"
#include "game/GameModules.h"
#include "game/GameState.h"
#include "game/SndgCrowd.h"
#include "game/FlowManagerC.h"
#include "game/InGame.h"
#include "game/FELoop.h"
#include "game/fn_80072AA8.h"


extern "C" {
void MemPoolRelease(int a);
void fn_80072D98(unsigned int delay);
void fn_80073094(void);
extern const char lbl_8028AD04[];
extern char lbl_8030C070[];
extern FlowStageEntry_t lbl_802CCBBC[];
extern FlowTransitionEntry_t lbl_802CCBDC[];
}

extern LoadingFEToInGame gLoadingFEToInGame;
extern Timg gTimg;

Class_800325E8 lbl_803068B4;

static ModuleDependency lbl_803068D8[] = {
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
    lbl_8030C070,
    &gUIS,
    0,
};

static ModuleDependency lbl_80306A08[] = {
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
    lbl_8030C070,
    &gUIS,
    &gInGame,
    0,
};

static ModuleDependency lbl_803EC680[] = {
    &gMemAudit,
    0,
};

const char *Class_800325E8::GSGetGroupName() { return lbl_8028AD04; }
FlowStageEntry_t *Class_800325E8::GSGetStageList() { return lbl_802CCBBC; }
FlowTransitionEntry_t *Class_800325E8::GSGetTransitionList() { return lbl_802CCBDC; }

ModuleDependency *Class_800325E8::GSGetStageModuleList(int id)
{
    switch (id) {
    case 4:
        return lbl_803068D8;
    case 5:
        return lbl_80306A08;
    case 6:
        return lbl_803EC680;
    default:
        return 0;
    }
}

void Class_800325E8::GSProcess()
{
    GSFlowManagerC *p = &gGSFlowManager;

    if (p->fn_801CBE9C(3) == 0) {
        switch (p->fn_801CBEC8(1)) {
        case 4:
            p->fn_801CBEF4(1, 5);
            break;
        case 5:
            if (!gInGame.Update()) {
                p->fn_801CBEF4(1, 6);
            }
            break;
        case 6:
            p->fn_801CBE24(1);
            MemPoolRelease(1);
            p->fn_801CBD80(2, -1);
            break;
        }
    }
}

int Class_800325E8::GSTransition(int a, int id)
{
    switch (id) {
    case 5:
        if (!FELoopWasVisited()) {
            fn_80072AA8();
            fn_80072F90();
        } else {
            fn_80072D98(250);
        }
        break;
    case 6:
        if (!FELoopWasVisited()) {
            fn_80073094();
        }
        break;
    }
    return 1;
}
