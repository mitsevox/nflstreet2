#ifndef GAME_FELOOP_H
#define GAME_FELOOP_H

#include "game/Module.h"

class FELoop : public Module {
public:
    virtual int Init();
    virtual int Shutdown();
    virtual ModuleDependency *GetDependencies();
    virtual ModuleDependency *GetLinks();
    virtual const char *GetName();

    void Boot();
    unsigned char Update();
};

typedef void (*FELoopCallback)();

extern "C" {
void FELoopStartGame(void);
void FELoopConfigureEntry(int a, int b, int c, int d, int e, int f);
int FELoopIsMainFEActive(void);
void FELoopSetResume(unsigned char value);
void FELoopSetResumeMode(unsigned char value);
void FELoopRefreshModeType(void);
void FELoopSetVisited(unsigned char value);
unsigned char FELoopWasVisited(void);
void FELoopSetFrameCallback(FELoopCallback pCallback);
void FELoopResetIdle(void);
unsigned char FELoopIsIdleTimedOut(void);
void FELoopCheckDemoLaunch(int a);
}

extern FELoop gFELoop;

#endif
