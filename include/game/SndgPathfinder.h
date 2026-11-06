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

/* Entry of the 20-entry table gSndgAramRegions. */
struct SndgAramRegion_t {
    int mUnknown0;
    unsigned int mUnknown4;
    unsigned int mUnknown8;
};

/* Argument of SndgAmbIsPathNodeName, which compares the string at +8 with the names of
   _SndgAmb_apszPathNodeNames; SndgSoundObjUpdateFromEvent reads the float at +4. */
struct SndgAmbObjInfo_t {
    int mUnknown0;
    float mUnknown4;
    char mUnknown8[1];
};

extern "C" {
extern SndgAramRegion_t gSndgAramRegions[];

int SndgPathLoadMap(void *pData, int unknown);
int SndgPathUnloadMap(int handle);
int SndgPathCreateTrack(void *pData, int unknown, int id, float value);
int SndgPathDestroyTrack(int id);
void SndgPathSetTrackVolume(int id, unsigned int value);
int SndgPathPostEvent(int id, int unknown);
int SndgPathControl(int id, int unknown);
}

#endif
