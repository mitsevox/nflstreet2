// Flow group: one strand of the game's flow (front end, in-game, system and so on) with its table
// of stages, the module list each stage needs and the allowed transitions. It tracks the active
// stage, switches stages on a transition and runs the group's per-frame processing.
#include "game/FlowGroupC.h"

extern "C" {
void fn_801D3318(int ident, const char *pLabel);
}

FlowGroupC::FlowGroupC() : mUnknown0(0), mUnknown1(0), mId(-1)
{
    mRecordCount = 0;
    mLinkCount = 0;
    mpRecords = 0;
    mpLinks = 0;
}

FlowGroupC::~FlowGroupC()
{
}

void FlowGroupC::Init()
{
    mpRecords = GSGetStageList();
    mpLinks = GSGetTransitionList();
    mOverrideId = -1;
    mRecordCount = 0;
    mOverride = 0;
    while (mpRecords[mRecordCount].mId != -1) {
        mRecordCount++;
    }
    while (mpLinks[mLinkCount].mFromId != -1) {
        mLinkCount++;
    }
    mUnknown0 = 1;
}

int FlowGroupC::Start(int id)
{
    if (id == -1) {
        mId = GetDefaultStage();
    } else {
        mId = id;
    }
    mUnknown1 = 1;
    return 1;
}

int FlowGroupC::Stop()
{
    mId = -1;
    mUnknown1 = 0;
    return 1;
}

int FlowGroupC::IsStarted()
{
    return mUnknown1;
}

int FlowGroupC::GetActiveStage()
{
    if (mOverride != 0) {
        return mOverrideId;
    }
    return mId;
}

int FlowGroupC::GetDefaultStage()
{
    return mpRecords->mId;
}

ModuleDependency *FlowGroupC::GetStageModuleList(int id)
{
    return GSGetStageModuleList(id);
}

void FlowGroupC::Process()
{
    fn_801D3318(-1, GetName());
    GSProcess();
    fn_801D3318(-1, 0);
}

void FlowGroupC::TransitionStart(int id)
{
    TransitionStartCallback();
    mOverrideId = id;
    mOverride = 1;
}

void FlowGroupC::TransitionEnd(int id)
{
    int old = mId;

    mId = id;
    mOverrideId = -1;
    mOverride = 0;
    TransitionEndCallback(old);
}

int FlowGroupC::Transition(int id)
{
    int result;

    fn_801D3318(-1, GetName());
    result = GSTransition(mId, id);
    fn_801D3318(-1, 0);
    return result;
}

const char *FlowGroupC::GetName()
{
    return GSGetGroupName();
}

void FlowGroupC::TransitionStartCallback()
{
}

void FlowGroupC::TransitionEndCallback(int id)
{
}
