#ifndef GAME_SNDGPATHFINDER_H
#define GAME_SNDGPATHFINDER_H

#include "game/Module.h"

class SndgPathfinder : public Module {
public:
    virtual int Init();
    virtual int Shutdown();
    virtual ModuleDependency *GetDependencies();
    virtual ModuleDependency *GetLinks();
    virtual const char *GetName();
};

extern SndgPathfinder gSndgPathfinder;

extern "C" {
int fn_8006DBF8(void *pData, int unknown);
int fn_8006DC4C(int handle);
int fn_8006DC98(void *pData, int unknown, int id, float value);
int fn_8006DD24(int id);
void fn_8006DD70(int id, unsigned int value);
int fn_8006DE00(int id, int unknown);
int fn_8006DE54(int id, int unknown);
}

#endif
