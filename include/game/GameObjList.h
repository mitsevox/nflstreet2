#ifndef GAME_GAMEOBJLIST_H
#define GAME_GAMEOBJLIST_H

#include "game/Module.h"

struct GameObjListState {
    int mUnknown0;
};

struct GameObjListStatePtr {
    GameObjListStatePtr() : mp(0) {}
    GameObjListState *mp;
};

class GameObjList : public Module {
public:
    virtual int Init();
    virtual int Shutdown();
    virtual ModuleDependency *GetDependencies();
    virtual ModuleDependency *GetLinks();
    virtual const char *GetName();

    static int GetListHandle();

private:
    GameObjListStatePtr mpState;
};

extern GameObjList gGameObjList;

#endif
