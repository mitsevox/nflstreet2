#ifndef GAME_GAMESTATE_H
#define GAME_GAMESTATE_H

#include "game/Module.h"
#include "game/Record_802CC680.h"

/* Object returned by fn_80237EE8. */
struct Object_80237EE8;

struct GameStateData {
    Object_80237EE8 *mpObject;
    /* Set when Init called fn_802382F0; Shutdown then calls fn_80238358. */
    unsigned char mUnknown4;
};

struct GameStateDataPtr {
    GameStateDataPtr() : mp(0) {}
    GameStateData *mp;
};

class GameState : public Module {
public:
    virtual int Init();
    virtual int Shutdown();
    virtual ModuleDependency *GetDependencies();
    virtual ModuleDependency *GetLinks();
    virtual const char *GetName();

    static Object_80237EE8 *fn_8002900C();
    void fn_8002901C();

private:
    GameStateDataPtr mpData;
};

DECLARE_MODULE(GameStateActivate);

extern GameState gGameState;
extern GameStateActivate gGameStateActivate;

#endif
