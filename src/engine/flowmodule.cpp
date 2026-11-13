// Flow module: the base of every game system the flow manager starts and stops (sound, files,
// rendering, front end and so on). Each module registers itself in a global list when it is
// constructed, keeps a start count so modules shared by several stages start once, and reports
// its dependency list and name to the flow manager.
#include "game/Module.h"

unsigned char FlowModuleC::s_bLockModuleList = 0;
unsigned int FlowModuleC::s_uNumModules = 0;
static FlowModuleC *_FlowModule_aModuleList[500];

FlowModuleC::FlowModuleC()
{
    _FlowModule_aModuleList[s_uNumModules] = this;
    s_uNumModules++;
    mUnknown0 = 0;
    mUnknown8 = 0;
    mUnknown4 = 0;
}

FlowModuleC::~FlowModuleC()
{
    unsigned int i;
    int found = 0;

    for (i = 0; i < s_uNumModules; i++) {
        if (_FlowModule_aModuleList[i] == this) {
            found = 1;
        }
        if (found) {
            if (i != s_uNumModules - 1) {
                _FlowModule_aModuleList[i] = _FlowModule_aModuleList[i + 1];
            } else {
                _FlowModule_aModuleList[i] = 0;
            }
        }
    }
    s_uNumModules--;
}

extern "C" int FlowModulePreStart(FlowModuleC *pNode)
{
    pNode->mUnknown4++;
    return pNode->mUnknown4 > 0;
}

extern "C" int FlowModuleStart(FlowModuleC *pNode, unsigned char flags)
{
    int result;

    pNode->GSPreModuleStart(pNode);
    result = pNode->Init();
    if (result == 1) {
        pNode->mUnknown8 = result;
    }
    pNode->GSPostModuleStart(pNode);
    return result;
}

extern "C" int FlowModuleStop(FlowModuleC *pNode, unsigned char flags)
{
    int result;

    if (--pNode->mUnknown4 == 0) {
        pNode->GSPreModuleStop(pNode);
        if (pNode->mUnknown8 == 1) {
            result = pNode->Shutdown();
        } else {
            result = 1;
        }
        if (result == 1) {
            pNode->mUnknown8 = 0;
        }
        pNode->GSPostModuleStop(pNode);
    } else {
        result = 1;
    }
    return result;
}

int FlowModuleC::IsStarted()
{
    return mUnknown8;
}

ModuleDependency *FlowModuleC::GetDependencyList()
{
    return GetDependencies();
}

const char *FlowModuleC::GetModuleName()
{
    return GetName();
}

void FlowModuleC::LockModuleList(unsigned char bLock)
{
    s_bLockModuleList = bLock;
}

void FlowModuleC::CheckDependencyLists()
{
}

void FlowModuleC::CheckAntiDependencyLists()
{
}

FlowModuleCounterC::~FlowModuleCounterC()
{
}

void FlowModuleCounterC::Visit(FlowModuleC *pNode)
{
    if (pNode->IsStarted() == 0) {
        mCount++;
    }
}
