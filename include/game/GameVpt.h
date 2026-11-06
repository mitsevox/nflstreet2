#ifndef GAME_GAMEVPT_H
#define GAME_GAMEVPT_H

#include "game/Module.h"
#include "engine/viewporttypes.h"

/* Heap block allocated by Init and released by Shutdown. */
struct GameVptState {
    Viewport_t *mpObject;
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

    static Viewport_t *GetViewport();

private:
    GameVptStatePtr mpState;
};

extern GameVpt gGameVpt;

#endif
