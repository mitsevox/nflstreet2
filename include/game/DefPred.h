#ifndef GAME_DEFPRED_H
#define GAME_DEFPRED_H

#include "game/Module.h"

/* Eight-byte state block allocated by DefPred::Init. */
struct DefPredState {
    unsigned int mUnknown0;
    unsigned int mUnknown4;
};

struct DefPredStatePtr {
    DefPredStatePtr() : mp(0) {}
    DefPredState *mp;
};

/* Module 0x8030C070 (vtable 0x80297AF0); GetName returns "DefPred". */
class DefPred : public Module {
public:
    virtual int Init();
    virtual int Shutdown();
    virtual ModuleDependency *GetDependencies();
    virtual ModuleDependency *GetLinks();
    virtual const char *GetName();

private:
    DefPredStatePtr mpState;
};

extern DefPred gDefPred;

#endif
