#ifndef GAME_MAINFEGROUP_H
#define GAME_MAINFEGROUP_H

#include "game/FlowGroupC.h"

/* The main front-end flow group (GSGetGroupName returns "MainFE Group"). */
class MainFEGroup : public FlowGroupC {
public:
    virtual void GSProcess();
    virtual int GSTransition(int a, int b);
    virtual FlowStageEntry_t *GSGetStageList();
    virtual FlowTransitionEntry_t *GSGetTransitionList();
    virtual ModuleDependency *GSGetStageModuleList(int id);
    virtual const char *GSGetGroupName();
};

extern MainFEGroup gMainFEGroup;

extern "C" {
int MainFEGroupIsStarted(FlowGroupC *pGroup);
int MainFEGroupIsFirstStart(FlowGroupC *pGroup);
}

#endif
