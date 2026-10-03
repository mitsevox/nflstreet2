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

    unsigned char fn_8002854C();
};

extern "C" {
void fn_800282DC(void);
int fn_80028310(void);
void fn_8002885C(void);
void fn_800288B0(void);
void fn_80028918(int unknown);
void fn_80028920(void);
unsigned char fn_8002892C(void);
int fn_80028934(void);
int fn_8002894C(void);
int fn_800289A8(void);
}

extern InGame gInGame;

#endif
