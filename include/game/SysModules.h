#ifndef GAME_SYSMODULES_H
#define GAME_SYSMODULES_H

#include "game/Module.h"

class SysPreLoad : public Module {
public:
    virtual int Init();
    virtual int Shutdown();
    virtual ModuleDependency *GetDependencies();
    virtual ModuleDependency *GetLinks();
    virtual const char *GetName();

    void LoadSystems();
};

extern ARes gARes;
extern Cam gCam;
extern Context gContext;
extern Curve gCurve;
extern Db gDb;
extern DbGame gDbGame;
extern DbgPrint gDbgPrint;
extern Event gEvent;
extern Loading gLoading;
extern Math gMath;
extern MemCard gMemCard;
extern Periph gPeriph;
extern Remap gRemap;
extern Sort gSort;
extern SysPreLoad gSysPreLoad;
extern Task gTask;
extern VRAM gVRAM;
extern FMSndgMusic gFMSndgMusic;

#endif
