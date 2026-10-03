#ifndef GAME_FMCAPPORT_H
#define GAME_FMCAPPORT_H

#include "game/Module.h"

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

/* Argument of fn_8008A9F8, fn_8008AA48, fn_8008AA7C, fn_8008AA9C, fn_8008AAD0,
   fn_8008AAF0, fn_8008ABA4, fn_80199968, fn_801999B0 and fn_801999F4. */
struct Object_8008A9F8 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
    int mUnknown16;
    int mUnknown20;
    int mUnknown24;
    int mUnknown28;
    int mUnknown32;
    int mUnknown36;
    int mUnknown40;
    int mUnknown44;
    int mUnknown48;
    FMCAPPORTValues mValues52;
    char mUnknown264[25];
    FMCAPPORTText mText289;
    FMCAPPORTText mText314;
    int mUnknown340[6];
    int mUnknown364;
    char mUnknown368[1268];
};

/* Object returned by fn_80228224. */
struct Object_80228224 {
    char mUnknown0[28];
    unsigned int mUnknown28;
};

/* Argument of fn_80228224. */
struct Desc_80228224 {
    short mUnknown0;
    char mUnknown2;
    char mUnknown3;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
    short mUnknown16;
    short mUnknown18;
};

class Class_8008B284 {
public:
    Class_8008B284();
    ~Class_8008B284();

private:
    char mUnknown0[44];
};

struct FMCAPPORTState {
    int mState;
    int mDelay;
    unsigned char mUnknown8;
    int mCount;
    FMCAPPORTEntry mEntries[8];
    Object_8008A9F8 mObject;
    Class_8008B284 *mUnknown4084;
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
