#include "game/fn_8007F828.h"
#include "game/GameObjList.h"
#include "game/GameVpt.h"
#include "engine/cu_80227F14.h"

void *operator new(unsigned int size, int unknown);

extern "C" {

void fn_801422C0(int a);
int fn_801CEA08(void);
int fn_801CEA14(void);
int fn_801CEB4C(void);
int fn_801CEC74(void);
int fn_801CEC7C(void);
}

static ModuleDependency sDependencies[] = { &gSys, &gGLIB, &gVpt, &gGameObjList, 0 };
GameVpt gGameVpt;

ModuleDependency *GameVpt::GetDependencies() { return sDependencies; }
ModuleDependency *GameVpt::GetLinks() { return 0; }
const char *GameVpt::GetName() { return "GameVpt"; }

int GameVpt::Init()
{
    Desc_80228224 desc;

    mpState.mp = new (0) GameVptState;
    desc.mUnknown0 = 4;
    desc.mUnknown2 = 0;
    desc.mUnknown3 = 2;
    desc.mUnknown4[0] = 0;
    desc.mUnknown4[1] = 0;
    if (fn_8007F828(6) == 1 || fn_801CEB4C() == 1) {
        desc.mUnknown16 = fn_801CEC74();
        desc.mUnknown18 = fn_801CEC7C();
        fn_801422C0(1);
    } else {
        desc.mUnknown16 = fn_801CEA14();
        desc.mUnknown18 = fn_801CEA08();
        fn_801422C0(0);
    }
    mpState.mp->mpObject = fn_80228224(&desc);
    fn_802286D8(mpState.mp->mpObject, 45.0f, 4.0f / 3.0f, 0.1f, 750.0f);
    fn_80228780(mpState.mp->mpObject, 4.0f);
    fn_802286CC(mpState.mp->mpObject, GameObjList::fn_80028BB4(), 0);
    return 1;
}

int GameVpt::Shutdown()
{
    fn_802283FC(mpState.mp->mpObject);
    delete mpState.mp;
    mpState.mp = 0;
    return 1;
}

Object_80228224 *GameVpt::fn_800293A8()
{
    return gGameVpt.mpState.mp->mpObject;
}
