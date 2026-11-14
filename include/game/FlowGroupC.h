#ifndef GAME_FLOWGROUPC_H
#define GAME_FLOWGROUPC_H

#include "game/Module.h"

/* Element of the table returned by GSGetStageList; the table ends with mId -1. */
struct FlowStageEntry_t {
    int mId;
    const char *mpName;
};

/* Element of the table returned by GSGetTransitionList; the table ends with -1, -1. */
struct FlowTransitionEntry_t {
    int mFromId;
    int mToId;
};

class FlowGroupC {
public:
    FlowGroupC();
    virtual ~FlowGroupC();
    virtual void GSProcess() = 0;
    /* Called by 0x801CC654 with the word at +4 and that function's argument. */
    virtual int GSTransition(int a, int id) = 0;
    virtual FlowStageEntry_t *GSGetStageList() = 0;
    virtual FlowTransitionEntry_t *GSGetTransitionList() = 0;
    virtual ModuleDependency *GSGetStageModuleList(int id) = 0;
    virtual const char *GSGetGroupName() = 0;
    virtual void TransitionStartCallback();
    virtual void TransitionEndCallback(int id);

    void Init();
    int Start(int id);
    int Stop();
    int IsStarted();
    int GetActiveStage();
    int GetDefaultStage();
    ModuleDependency *GetStageModuleList(int id);
    void Process();
    void TransitionStart(int id);
    void TransitionEnd(int id);
    int Transition(int id);
    const char *GetName();

    unsigned char mUnknown0;
    unsigned char mUnknown1;
    int mId;
    FlowStageEntry_t *mpRecords;
    FlowTransitionEntry_t *mpLinks;
    int mRecordCount;
    int mLinkCount;
    int mOverrideId;
    unsigned char mOverride;
};

class DebugGroup : public FlowGroupC {
public:
    virtual void GSProcess();
    virtual int GSTransition(int a, int id);
    virtual FlowStageEntry_t *GSGetStageList();
    virtual FlowTransitionEntry_t *GSGetTransitionList();
    virtual ModuleDependency *GSGetStageModuleList(int id);
    virtual const char *GSGetGroupName();
};

class SystemGroup : public FlowGroupC {
public:
    virtual void GSProcess();
    virtual int GSTransition(int a, int id);
    virtual FlowStageEntry_t *GSGetStageList();
    virtual FlowTransitionEntry_t *GSGetTransitionList();
    virtual ModuleDependency *GSGetStageModuleList(int id);
    virtual const char *GSGetGroupName();
};

extern DebugGroup gDebugGroup;
extern SystemGroup gSystemGroup;

#endif
