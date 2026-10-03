#include "game/GameObjList.h"

void *operator new(unsigned int size, int unknown);

extern "C" {

int fn_801DCFF0(int a, int b, int c, int d, int e, int f, int g, int h);
void fn_801DD0E8(int handle);
}

static ModuleDependency sDependencies[] = { &gSys, &gObj, 0 };
GameObjList gGameObjList;

ModuleDependency *GameObjList::GetDependencies() { return sDependencies; }
ModuleDependency *GameObjList::GetLinks() { return 0; }
const char *GameObjList::GetName() { return "GameObjList"; }

int GameObjList::Init()
{
    mpState.mp = new (0) GameObjListState;
    mpState.mp->mUnknown0 = fn_801DCFF0(1, 336, 0, 0, 0, 1, 0, -1);
    return 1;
}

int GameObjList::Shutdown()
{
    fn_801DD0E8(mpState.mp->mUnknown0);
    delete mpState.mp;
    mpState.mp = 0;
    return 1;
}

int GameObjList::fn_80028BB4()
{
    return gGameObjList.mpState.mp->mUnknown0;
}
