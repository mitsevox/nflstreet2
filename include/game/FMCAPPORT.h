#ifndef GAME_FMCAPPORT_H
#define GAME_FMCAPPORT_H

#include "game/Class_8008B284.h"
#include "game/Module.h"
#include "game/Object_80228224.h"

struct FMCAPPORTText {
    char mChars[25];
};

struct FMCAPPORTValues {
    float mValues[53];
};

struct FMCAPPORTEntry {
    int mId;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
    int mUnknown16;
    FMCAPPORTText mText20;
    int mUnknown48;
    int mUnknown52;
    int mUnknown56;
    FMCAPPORTText mText60;
    FMCAPPORTValues mValues88;
    int mUnknown300;
};

struct Desc_802347EC {
    char *mpName;
    char mUnknown4[20];
    void *mpUnknown24;
    char mUnknown28[4];
};

/* Three halfwords copied together between the tables below. */
struct Triple_80198D98 {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    unsigned short mUnknown4;
};

struct Object_80233BB8 {
    char mUnknown0[12];
};

struct Object_8023488C {
    char mUnknown0[8];
};

struct Object_80234A30 {
    char mUnknown0[12];
    void *mpUnknown12;
    char mUnknown16[4];
    char mUnknown20[204];
    Object_80233BB8 *mpUnknown224;
    char mUnknown228[12];
};

/* Argument of fn_8008A9F8, fn_8008AA48, fn_8008AA7C, fn_8008AA9C, fn_8008AAD0,
   fn_8008AAF0, fn_8008ABA4, fn_80199968, fn_801999B0 and fn_801999F4. */
struct Object_8008A9F8 {
    int mUnknown0;
    void *mpUnknown4;
    void *mpUnknown8;
    int mUnknown12[4];
    int mUnknown28[4];
    int mUnknown44[2];
    FMCAPPORTValues mValues52;
    FMCAPPORTText mText264[4];
    int mUnknown364;
    void *mpUnknown368[4];
    Desc_802347EC mUnknown384[4];
    void *mpUnknown512[2];
    char mUnknown520[68];
    Object_80233BB8 mUnknown588[2];
    Object_8023488C mUnknown612;
    Object_80234A30 mUnknown620[3];
    Triple_80198D98 mUnknown1340[30];
    Triple_80198D98 mUnknown1520[19];
    Class_8008B284 *mpUnknown1636;
};

struct FMCAPPORTState {
    int mState;
    int mDelay;
    unsigned char mUnknown8;
    int mCount;
    FMCAPPORTEntry mEntries[8];
    Object_8008A9F8 mObject;
    Object_80228224 *mUnknown4088;
    int mUnknown4092;
    int mUnknown4096;
};

struct FMCAPPORTStatePtr {
    FMCAPPORTStatePtr() : mp(0) {}
    FMCAPPORTState *mp;
};

class FMCAPPORT : public Module {
public:
    virtual int Init();
    virtual int Shutdown();
    virtual ModuleDependency *GetDependencies();
    virtual ModuleDependency *GetLinks();
    virtual const char *GetName();

    void fn_8008C010();
    void fn_8008C0EC();
    void fn_8008C12C();
    void fn_8008C1FC();
    void SetEntry(int id, int unknown4, int unknown8, int unknown12, int unknown16,
                  const FMCAPPORTText *pText20, int unknown48, int unknown52, int unknown56,
                  const FMCAPPORTText *pText60, const FMCAPPORTValues *pValues88, int unknown300);
    void ClearEntries();
    int IsBusy();
    void Start();
    void Update();
    void fn_8008C870();

private:
    FMCAPPORTStatePtr mpState;
};

extern FMCAPPORT gFMCAPPORT;

#endif
