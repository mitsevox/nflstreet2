/* The GameState modules: create and activate the store that holds the game state blocks. */

#include "game/GameState.h"

void *operator new(unsigned int size, int unknown);

extern "C" {
extern char gMainFEGroup[];

int MainFEGroupIsStarted(void *p);
int MainFEGroupIsFirstStart(void *p);
void SyncStateInit(int a);
SyncStateGroup_t *SyncStateNewGroup(int a, int b, int c, MemPoolDesc_t desc);
void SyncStateDelGroup(SyncStateGroup_t *pObject);
void EvMonInit(int a);
void EvMonShutdown(void);
}

static void *sGameStateDependencies[] = { 0 };
static ModuleDependency sGameStateActivateDependencies[] = { &gGameState, 0 };
GameState gGameState;
GameStateActivate gGameStateActivate;

ModuleDependency *GameState::GetDependencies() { return (ModuleDependency *)sGameStateDependencies; }
ModuleDependency *GameState::GetLinks() { return 0; }
const char *GameState::GetName() { return "GameState"; }

int GameState::Init()
{
    int arg2;
    int arg1;
    int arg;

    mpData.mp = new (0) GameStateData;
    if (MainFEGroupIsStarted(gMainFEGroup)) {
        arg2 = 0x16C00;
        arg1 = 50;
        arg = 3;
    } else {
        arg2 = 0x44000;
        arg1 = 56;
        arg = 4;
    }
    SyncStateInit(3);
    mpData.mp->mpObject = SyncStateNewGroup(0, arg1, arg2, *MemPoolGetDesc(4));
    SyncStateOpenGroup(mpData.mp->mpObject);
    if (MainFEGroupIsFirstStart(gMainFEGroup)) {
        mpData.mp->mUnknown4 = 0;
    } else {
        EvMonInit(arg);
        mpData.mp->mUnknown4 = 1;
    }
    return 1;
}

int GameState::Shutdown()
{
    SyncStateDelGroup(mpData.mp->mpObject);
    SyncStateShutdown();
    mpData.mp->mpObject = 0;
    if (mpData.mp->mUnknown4) {
        EvMonShutdown();
    }
    delete mpData.mp;
    mpData.mp = 0;
    return 1;
}

SyncStateGroup_t *GameState::GetStore()
{
    return gGameState.mpData.mp->mpObject;
}

void GameState::Activate()
{
    SyncStateSaveGroup(mpData.mp->mpObject);
    SyncStateActivateGroup(mpData.mp->mpObject);
}

ModuleDependency *GameStateActivate::GetDependencies() { return sGameStateActivateDependencies; }
ModuleDependency *GameStateActivate::GetLinks() { return 0; }
const char *GameStateActivate::GetName() { return "GameStateActivate"; }

int GameStateActivate::Init()
{
    gGameState.Activate();
    return 1;
}

int GameStateActivate::Shutdown()
{
    return 1;
}
