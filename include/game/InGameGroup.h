#ifndef GAME_INGAMEGROUP_H
#define GAME_INGAMEGROUP_H

#include "game/FlowGroupC.h"

/* The in-game flow group (GSGetGroupName returns "InGame Group"). */
class InGameGroup : public FlowGroupC {
public:
    virtual void GSProcess();
    virtual int GSTransition(int a, int id);
    virtual const char *GSGetGroupName();
    virtual FlowStageEntry_t *GSGetStageList();
    virtual FlowTransitionEntry_t *GSGetTransitionList();
    virtual ModuleDependency *GSGetStageModuleList(int id);
};

extern InGameGroup gInGameGroup;

#endif
