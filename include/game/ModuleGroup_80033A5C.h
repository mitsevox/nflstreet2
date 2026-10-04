#ifndef GAME_MODULEGROUP_80033A5C_H
#define GAME_MODULEGROUP_80033A5C_H

#include "game/Module.h"

/* Data block loaded by fn_801EEB44 in Init and released by fn_801EEFAC in Shutdown. */
struct ModuleDataPtr {
    ModuleDataPtr() : mp(0) {}
    void *mp;
};

/* Name of the .qkl file opened by Qkl::Init. */
struct QklFileName {
    QklFileName() { mText[0] = 0; }
    char mText[16];
};

class AnimData : public Module {
public:
    virtual int Init();
    virtual int Shutdown();
    virtual ModuleDependency *GetDependencies();
    virtual ModuleDependency *GetLinks();
    virtual const char *GetName();

    void *fn_80033AF8();

private:
    ModuleDataPtr mData;
};

class IGMisc : public Module {
public:
    virtual int Init();
    virtual int Shutdown();
    virtual ModuleDependency *GetDependencies();
    virtual ModuleDependency *GetLinks();
    virtual const char *GetName();

    /* Read directly by PlayArtMem::Init and PlayBook::fn_8003549C. */
    ModuleDataPtr mData;
};

class Qkl : public Module {
public:
    virtual int Init();
    virtual int Shutdown();
    virtual ModuleDependency *GetDependencies();
    virtual ModuleDependency *GetLinks();
    virtual const char *GetName();

private:
    QklFileName mFileName;
};

class StaData : public Module {
public:
    virtual int Init();
    virtual int Shutdown();
    virtual ModuleDependency *GetDependencies();
    virtual ModuleDependency *GetLinks();
    virtual const char *GetName();

    void *fn_80033FD4();

private:
    ModuleDataPtr mData;
};

extern AnimData gAnimData;
extern Audmon gAudmon;
extern GRand gGRand;
extern IGMisc gIGMisc;
extern MemAudit gMemAudit;
extern Qkl gQkl;
extern ScrmRule gScrmRule;
extern StaData gStaData;
extern UIS gUIS;

#endif
