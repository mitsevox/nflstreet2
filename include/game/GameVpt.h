#ifndef GAME_GAMEVPT_H
#define GAME_GAMEVPT_H

#include "game/Module.h"
#include "game/Object_80228224.h"

/* Heap block allocated by Init and released by Shutdown. */
struct GameVptState {
    Object_80228224 *mpObject;
};

struct GameVptStatePtr {
    GameVptStatePtr() : mp(0) {}
    GameVptState *mp;
};

class GameVpt : public Module {
public:
    virtual int Init();
    virtual int Shutdown();
    virtual ModuleDependency *GetDependencies();
    virtual ModuleDependency *GetLinks();
    virtual const char *GetName();

    static Object_80228224 *fn_800293A8();

private:
    GameVptStatePtr mpState;
};

extern GameVpt gGameVpt;

#endif
