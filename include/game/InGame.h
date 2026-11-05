#ifndef GAME_INGAME_H
#define GAME_INGAME_H

#include "game/Module.h"

class InGame : public Module {
public:
    virtual int Init();
    virtual int Shutdown();
    virtual ModuleDependency *GetDependencies();
    virtual ModuleDependency *GetLinks();
    virtual const char *GetName();

    unsigned char Update();
};

extern "C" {
void InGameStop(void);
int InGameIsStopped(void);
void InGamePause(void);
void InGameResume(void);
void InGameSetInputPaused(int unknown);
void InGameSetDemo(void);
unsigned char InGameIsDemo(void);
int InGameIsPaused(void);
int InGameIsPlaying(void);
int InGameGetFrameCount(void);
}

extern InGame gInGame;

#endif
