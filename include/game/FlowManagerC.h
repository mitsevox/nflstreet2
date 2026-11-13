#ifndef GAME_FLOWMANAGERC_H
#define GAME_FLOWMANAGERC_H

class FlowGroupC;
class FlowModuleC;
struct ModuleDependency;

/* Queued group change: group index, current and requested id (12 bytes). */
struct FlowQueuedTransition_t {
    int mGroup;
    int mFrom;
    int mTo;
};

class FlowManagerC {
public:
    FlowManagerC();
    virtual ~FlowManagerC();
    virtual int GSGetNumGroups() = 0;
    virtual void *GSCreateGroup(int index) = 0;
    virtual void GSDestroyGroup() = 0;

    void Init();
    int StartGroup(int a, int b);
    int StopGroup(int a);
    int IsGroupStarted(int a);
    int GetActiveStage(int a);
    int QueueTransition(int a, int b);
    int GetNumQueuedTransitions();
    void Process();
    void SetVerboseFlags(int flags);
    int PreStartModuleList(ModuleDependency *pDeps);
    int StartModuleList(ModuleDependency *pDeps);
    int StopModuleList(ModuleDependency *pDeps);
    int Transition(int group, int from, int to);
    int StartModule(FlowModuleC *pNode);
    int StopModule(FlowModuleC *pNode);

    unsigned char mUnknown0;
    unsigned char mUnknown1;
    int mFlags;
    int mCount;
    int mPendingCount;
    FlowGroupC *mpGroups[20];
    FlowQueuedTransition_t mPending[10];
    int mUnknownD8;
};

class GSFlowManagerC : public FlowManagerC {
public:
    virtual ~GSFlowManagerC() {}
    virtual int GSGetNumGroups();
    virtual void *GSCreateGroup(int index);
    virtual void GSDestroyGroup();
};
extern GSFlowManagerC gGSFlowManager;

#endif
