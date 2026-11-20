#ifndef GAME_GAMESTATE_H
#define GAME_GAMESTATE_H

#include "game/Module.h"
#include "game/MemPoolDesc.h"

/* Object returned by SyncStateNewGroup. */
#include "engine/SyncStateGroup.h"

struct GameStateData {
    SyncStateGroup_t *mpObject;
    /* Set when Init called EvMonInit; Shutdown then calls EvMonShutdown. */
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

    static SyncStateGroup_t *GetStore();
    void Activate();

private:
    GameStateDataPtr mpData;
};

DECLARE_MODULE(GameStateActivate);

extern GameState gGameState;
extern GameStateActivate gGameStateActivate;

#endif
