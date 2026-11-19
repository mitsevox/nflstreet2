/* The GameVpt module: creates the game's 3D viewport and sets its projection. */

#include "game/GameOptions.h"
#include "game/GameObjList.h"
#include "game/GameVpt.h"
#include "engine/viewport.h"

void *operator new(unsigned int size, int unknown);

extern "C" {

void CamCurveSetNarrowFov(int a);
int GlibGetScreenWidth(void);
int GlibGetScreenHeight(void);
int GlibGetWidescreenMode(void);
int GlibGetScreenLetterBoxHeight(void);
int GlibGetScreenLetterBoxWidth(void);
}

static ModuleDependency sDependencies[] = { &gSys, &gGLIB, &gVpt, &gGameObjList, 0 };
GameVpt gGameVpt;

ModuleDependency *GameVpt::GetDependencies() { return sDependencies; }
ModuleDependency *GameVpt::GetLinks() { return 0; }
const char *GameVpt::GetName() { return "GameVpt"; }

int GameVpt::Init()
{
    ViewportDesc_t desc;

    mpState.mp = new (0) GameVptState;
    desc.mUnknown0 = 4;
    desc.mUnknown2 = 0;
    desc.mUnknown3 = 2;
    desc.mUnknown4[0] = 0;
    desc.mUnknown4[1] = 0;
    if (GameOptionsGet(6) == 1 || GlibGetWidescreenMode() == 1) {
        desc.mUnknown16 = GlibGetScreenLetterBoxHeight();
        desc.mUnknown18 = GlibGetScreenLetterBoxWidth();
        CamCurveSetNarrowFov(1);
    } else {
        desc.mUnknown16 = GlibGetScreenHeight();
        desc.mUnknown18 = GlibGetScreenWidth();
        CamCurveSetNarrowFov(0);
    }
    mpState.mp->mpObject = VptOpen(&desc);
    VptSetPerspective(mpState.mp->mpObject, 45.0f, 4.0f / 3.0f, 0.1f, 750.0f);
    VptSetZScale(mpState.mp->mpObject, 4.0f);
    VptSetObjectList(mpState.mp->mpObject, GameObjList::GetListHandle(), 0);
    return 1;
}

int GameVpt::Shutdown()
{
    VptClose(mpState.mp->mpObject);
    delete mpState.mp;
    mpState.mp = 0;
    return 1;
}

Viewport_t *GameVpt::GetViewport()
{
    return gGameVpt.mpState.mp->mpObject;
}
