#ifndef GAME_CLASS_800325E8_H
#define GAME_CLASS_800325E8_H

#include "game/FlowGroupC.h"

class Class_800325E8 : public FlowGroupC {
public:
    virtual void GSProcess();
    virtual int GSTransition(int a, int id);
    virtual const char *GSGetGroupName();
    virtual FlowStageEntry_t *GSGetStageList();
    virtual FlowTransitionEntry_t *GSGetTransitionList();
    virtual ModuleDependency *GSGetStageModuleList(int id);
};

extern Class_800325E8 lbl_803068B4;

#endif
