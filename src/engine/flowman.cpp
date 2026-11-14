// Flow manager: owns the game's flow groups (front end, in-game, system and so on), starts and
// stops them, queues stage transitions and, on each transition, stops the modules the old stage
// needed and starts the modules the new stage needs, following each module's dependency list.
#include "game/FlowGroupC.h"
#include "game/FlowManagerC.h"

extern "C" {
void fn_801D3318(int ident, const char *pLabel);
void fn_801D339C(int ident);
void fn_801D342C(int ident);
}

extern "C" {
int FlowModulePreStart(FlowModuleC *pNode);
int FlowModuleStart(FlowModuleC *pNode, unsigned char flags);
int FlowModuleStop(FlowModuleC *pNode, unsigned char flags);
}

FlowManagerC::FlowManagerC()
{
    int i;

    for (i = 0; i < 20; i++) {
        mpGroups[i] = 0;
    }
    mCount = 0;
    mFlags = 0;
    mUnknownD8 = 0;
    mUnknown0 = 0;
    mUnknown1 = 0;
}

FlowManagerC::~FlowManagerC()
{
}

void FlowManagerC::Init()
{
    int i;

    FlowModuleC::LockModuleList(1);
    mCount = GSGetNumGroups();
    mPendingCount = 0;
    for (i = 0; i < mCount; i++) {
        mpGroups[i] = (FlowGroupC *)GSCreateGroup(i);
        mpGroups[i]->Init();
    }
    FlowModuleC::CheckDependencyLists();
    FlowModuleC::CheckAntiDependencyLists();
    mUnknown0 = 1;
}

int FlowManagerC::StartGroup(int a, int b)
{
    int result;
    ModuleDependency *pDeps;
    int id;

    if (b == -1) {
        result = mpGroups[a]->Start(-1);
    } else {
        result = mpGroups[a]->Start(b);
    }
    if (result == 1) {
        id = mpGroups[a]->GetActiveStage();
        pDeps = mpGroups[a]->GetStageModuleList(id);
        PreStartModuleList(pDeps);
        result = StartModuleList(pDeps);
    }
    return result;
}

int FlowManagerC::StopGroup(int a)
{
    int result;
    int id;

    if (mpGroups[a]->IsStarted() == 0) {
        return 0;
    }
    id = mpGroups[a]->GetActiveStage();
    result = mpGroups[a]->Stop();
    if (result == 1) {
        result = StopModuleList(mpGroups[a]->GetStageModuleList(id));
    }
    return result;
}

int FlowManagerC::IsGroupStarted(int a)
{
    return mpGroups[a]->IsStarted();
}

int FlowManagerC::GetActiveStage(int a)
{
    return mpGroups[a]->GetActiveStage();
}

int FlowManagerC::QueueTransition(int a, int b)
{
    int id;

    if (mpGroups[a]->GetActiveStage() == b) {
        return 1;
    }
    if (mpGroups[a]->IsStarted() == 0) {
        return 0;
    }
    id = mpGroups[a]->GetActiveStage();
    mPending[mPendingCount].mGroup = a;
    mPending[mPendingCount].mFrom = id;
    mPending[mPendingCount].mTo = b;
    mPendingCount++;
    return 1;
}

int FlowManagerC::GetNumQueuedTransitions()
{
    return mPendingCount;
}

void FlowManagerC::Process()
{
    int i;

    for (i = 0; i < mPendingCount; i++) {
        Transition(mPending[i].mGroup, mPending[i].mFrom, mPending[i].mTo);
    }
    mPendingCount = 0;
    for (i = 0; i < mCount; i++) {
        if (mpGroups[i]->IsStarted() == 1) {
            mpGroups[i]->Process();
        }
    }
}

void FlowManagerC::SetVerboseFlags(int flags)
{
    mFlags = flags;
}

int FlowManagerC::PreStartModuleList(ModuleDependency *pDeps)
{
    int result = 1;
    int i;

    for (i = 0; pDeps[i].mpTarget != 0; i++) {
        result = PreStartModuleList(((FlowModuleC *)pDeps[i].mpTarget)->GetDependencyList());
        FlowModulePreStart((FlowModuleC *)pDeps[i].mpTarget);
    }
    return result;
}

int FlowManagerC::StartModuleList(ModuleDependency *pDeps)
{
    int result = 1;
    int i;
    FlowModuleC *pNode;
    ModuleDependency *pSub;

    for (i = 0; pDeps[i].mpTarget != 0; i++) {
        pSub = ((FlowModuleC *)pDeps[i].mpTarget)->GetDependencyList();
        pNode = (FlowModuleC *)pDeps[i].mpTarget;
        result = StartModuleList(pSub);
        if (pNode->IsStarted() == 0) {
            if (StartModule(pNode) == 0) {
                result = 0;
            }
        }
    }
    return result;
}

int FlowManagerC::StopModuleList(ModuleDependency *pDeps)
{
    int result = 1;
    int i;
    ModuleDependency *pNext;

    for (i = 0; pDeps[i].mpTarget != 0; i++) {
        pNext = ((FlowModuleC *)pDeps[i].mpTarget)->GetDependencyList();
        StopModule((FlowModuleC *)pDeps[i].mpTarget);
        result = StopModuleList(pNext);
    }
    return result;
}

int FlowManagerC::Transition(int group, int from, int to)
{
    ModuleDependency *pFrom;
    ModuleDependency *pTo;
    int result;

    pFrom = mpGroups[group]->GetStageModuleList(from);
    pTo = mpGroups[group]->GetStageModuleList(to);
    PreStartModuleList(pTo);
    StopModuleList(pFrom);
    mpGroups[group]->TransitionStart(to);
    StartModuleList(pTo);
    result = mpGroups[group]->Transition(to);
    mpGroups[group]->TransitionEnd(to);
    return result;
}

int FlowManagerC::StartModule(FlowModuleC *pNode)
{
    int result;

    fn_801D339C(1);
    fn_801D3318(1, pNode->GetModuleName());
    result = FlowModuleStart(pNode, mFlags & 2);
    fn_801D342C(1);
    return result;
}

int FlowManagerC::StopModule(FlowModuleC *pNode)
{
    int result;

    fn_801D339C(1);
    fn_801D3318(1, pNode->GetModuleName());
    result = FlowModuleStop(pNode, mFlags & 2);
    fn_801D342C(1);
    return result;
}
