#ifndef GAME_FLOWMANAGERC_H
#define GAME_FLOWMANAGERC_H

class FlowGroupC;
class ModuleNode;
struct ModuleDependency;

/* Queued group change: group index, current and requested id (12 bytes). */
struct Request_801CBC50 {
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

    int fn_801CBD80(int a, int b);
    int fn_801CBE24(int a);
    int fn_801CBE9C(int a);
    int fn_801CBEC8(int a);
    int fn_801CBEF4(int a, int b);
    int fn_801CC05C(ModuleDependency *pDeps);
    int fn_801CC0D0(ModuleDependency *pDeps);
    int fn_801CC168(ModuleDependency *pDeps);
    int fn_801CC1DC(int group, int from, int to);
    int fn_801CC280(ModuleNode *pNode);
    int fn_801CC2E8(ModuleNode *pNode);

    unsigned char mUnknown0;
    unsigned char mUnknown1;
    int mFlags;
    int mCount;
    int mPendingCount;
    FlowGroupC *mpGroups[20];
    Request_801CBC50 mPending[10];
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

extern "C" {
void fn_801CBCD0(FlowManagerC *pTable);
int fn_801CBFA0(FlowManagerC *pTable);
void fn_801CBFA8(FlowManagerC *pTable);
void fn_801CC054(FlowManagerC *pTable, int flags);
}

#endif
