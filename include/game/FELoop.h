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

    void fn_800279AC();
    unsigned char fn_80027C58();
};

typedef void (*FELoopCallback)();

extern "C" {
void fn_80027A20(void);
void fn_80027AD8(int a, int b, int c, int d, int e, int f);
int fn_80027DF0(void);
void fn_80027E18(unsigned char value);
void fn_80027E34(unsigned char value);
void fn_80027E3C(void);
void fn_80027E88(unsigned char value);
unsigned char fn_80027E90(void);
void fn_80027E98(FELoopCallback pCallback);
void fn_80027EA0(void);
unsigned char fn_80027EAC(void);
void fn_80027EB4(void);
}

extern FELoop gFELoop;

#endif
