#ifndef GAME_SNDGCROWD_H
#define GAME_SNDGCROWD_H

#include "game/Module.h"

struct SndgCrowdState {
    void *mpUnknown0;
    int mUnknown4;
};

struct SndgCrowdStatePtr {
    SndgCrowdStatePtr() : mp(0) {}
    SndgCrowdState *mp;
};

class SndgCrowd : public Module {
public:
    virtual int Init();
    virtual int Shutdown();
    virtual ModuleDependency *GetDependencies();
    virtual ModuleDependency *GetLinks();
    virtual const char *GetName();

private:
    SndgCrowdStatePtr mpState;
};

extern SndgCrowd gSndgCrowd;

extern "C" {
void SndgCrowdSetVolume(unsigned char value);
int SndgCrowdTriggerEvent(int index, int unknown);
}

#endif
