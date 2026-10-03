#include "game/GameState.h"

void *operator new(unsigned int size, int unknown);

extern "C" {
extern char lbl_80306B34[];

int fn_80033124(void *p);
int fn_80033144(void *p);
void fn_80237E3C(int a);
void fn_80237E78(void);
Object_80237EE8 *fn_80237EE8(int a, int b, int c, Record_802CC680 desc);
void fn_80237F98(Object_80237EE8 *pObject);
void fn_80237FA4(Object_80237EE8 *pObject);
void fn_8023808C(Object_80237EE8 *pObject);
void *fn_8023811C(Object_80237EE8 *pObject);
void fn_802382F0(int a);
void fn_80238358(void);
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
    if (fn_80033124(lbl_80306B34)) {
        arg2 = 0x16C00;
        arg1 = 50;
        arg = 3;
    } else {
        arg2 = 0x44000;
        arg1 = 56;
        arg = 4;
    }
    fn_80237E3C(3);
    mpData.mp->mpObject = fn_80237EE8(0, arg1, arg2, *fn_80025E50(4));
    fn_80237F98(mpData.mp->mpObject);
    if (fn_80033144(lbl_80306B34)) {
        mpData.mp->mUnknown4 = 0;
    } else {
        fn_802382F0(arg);
        mpData.mp->mUnknown4 = 1;
    }
    return 1;
}

int GameState::Shutdown()
{
    fn_8023808C(mpData.mp->mpObject);
    fn_80237E78();
    mpData.mp->mpObject = 0;
    if (mpData.mp->mUnknown4) {
        fn_80238358();
    }
    delete mpData.mp;
    mpData.mp = 0;
    return 1;
}

Object_80237EE8 *GameState::fn_8002900C()
{
    return gGameState.mpData.mp->mpObject;
}

void GameState::fn_8002901C()
{
    fn_80237FA4(mpData.mp->mpObject);
    fn_8023811C(mpData.mp->mpObject);
}

ModuleDependency *GameStateActivate::GetDependencies() { return sGameStateActivateDependencies; }
ModuleDependency *GameStateActivate::GetLinks() { return 0; }
const char *GameStateActivate::GetName() { return "GameStateActivate"; }

int GameStateActivate::Init()
{
    gGameState.fn_8002901C();
    return 1;
}

int GameStateActivate::Shutdown()
{
    return 1;
}
