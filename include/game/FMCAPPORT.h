#ifndef GAME_FMCAPPORT_H
#define GAME_FMCAPPORT_H

#include "game/ColorQuantizer.h"
#include "game/Module.h"
#include "engine/viewporttypes.h"

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

struct ModelTexSlot_t {
    char *mpName;
    char mUnknown4[20];
    void *mpUnknown24;
    char mUnknown28[4];
};

/* Three halfwords copied together between the tables below. */
struct SkeletonJointTriple_t {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    unsigned short mUnknown4;
};

struct SkeletonPose_t {
    char mUnknown0[12];
};

struct ModelPartBinding_t {
    char mUnknown0[8];
};

struct ModelDrawObject_t {
    char mUnknown0[12];
    void *mpUnknown12;
    char mUnknown16[4];
    char mUnknown20[204];
    SkeletonPose_t *mpUnknown224;
    char mUnknown228[12];
};

/* Argument of PortraitJobAllocImage, PortraitJobLoad, PortraitJobIsLoaded, PortraitJobUnload, PortraitJobQuantize,
   PortraitJobIsDone, PortraitJobSave, PortraitRenderInit, PortraitRenderShutdown and PortraitRenderDraw. */
struct PortraitJob_t {
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
    ModelTexSlot_t mUnknown384[4];
    void *mpUnknown512[2];
    char mUnknown520[68];
    SkeletonPose_t mUnknown588[2];
    ModelPartBinding_t mUnknown612;
    ModelDrawObject_t mUnknown620[3];
    SkeletonJointTriple_t mUnknown1340[30];
    SkeletonJointTriple_t mUnknown1520[19];
    ColorQuantizer *mpUnknown1636;
};

struct FMCAPPORTState {
    int mState;
    int mDelay;
    unsigned char mUnknown8;
    int mCount;
    FMCAPPORTEntry mEntries[8];
    PortraitJob_t mObject;
    Viewport_t *mUnknown4088;
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
