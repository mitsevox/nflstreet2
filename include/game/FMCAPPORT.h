#ifndef GAME_FMCAPPORT_H
#define GAME_FMCAPPORT_H

#include "game/ColorQuantizer.h"
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

struct ModelTexSlot {
    char *mpName;
    char mUnknown4[20];
    void *mpUnknown24;
    char mUnknown28[4];
};

/* Three halfwords copied together between the tables below. */
struct SkeletonJointTriple {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    unsigned short mUnknown4;
};

struct SkeletonPose {
    char mUnknown0[12];
};

struct ModelPartBinding {
    char mUnknown0[8];
};

struct ModelDrawObject {
    char mUnknown0[12];
    void *mpUnknown12;
    char mUnknown16[4];
    char mUnknown20[204];
    SkeletonPose *mpUnknown224;
    char mUnknown228[12];
};

/* Argument of PortraitJobAllocImage, PortraitJobLoad, PortraitJobIsLoaded, PortraitJobUnload, PortraitJobQuantize,
   PortraitJobIsDone, PortraitJobSave, fn_80199968, fn_801999B0 and fn_801999F4. */
struct PortraitJob {
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
    ModelTexSlot mUnknown384[4];
    void *mpUnknown512[2];
    char mUnknown520[68];
    SkeletonPose mUnknown588[2];
    ModelPartBinding mUnknown612;
    ModelDrawObject mUnknown620[3];
    SkeletonJointTriple mUnknown1340[30];
    SkeletonJointTriple mUnknown1520[19];
    ColorQuantizer *mpUnknown1636;
};

struct FMCAPPORTState {
    int mState;
    int mDelay;
    unsigned char mUnknown8;
    int mCount;
    FMCAPPORTEntry mEntries[8];
    PortraitJob mObject;
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

    void CreateCamera();
    void DestroyCamera();
    void CreateRenderPass();
    void DestroyRenderPass();
    void SetEntry(int id, int unknown4, int unknown8, int unknown12, int unknown16,
                  const FMCAPPORTText *pText20, int unknown48, int unknown52, int unknown56,
                  const FMCAPPORTText *pText60, const FMCAPPORTValues *pValues88, int unknown300);
    void ClearEntries();
    int IsBusy();
    void Start();
    void Update();
    void CaptureFrame();

private:
    FMCAPPORTStatePtr mpState;
};

extern FMCAPPORT gFMCAPPORT;

#endif
