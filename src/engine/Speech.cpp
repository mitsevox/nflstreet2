/* Game-side front end of the speech (commentary) library: starts and stops it with its own
   allocator and bank memory, loads banks and event databases, installs the rule callbacks and
   filters and logs the events the game adds. */

#include <stddef.h>
#include <string.h>
#include "engine/Speech.h"
#include "engine/spchlib.h"
#include <stdarg.h>
#include "engine/Resource.h"
#include "engine/system.h"
#include "game/fn_801D2B7C.h"

namespace EA {
namespace Allocator {

class TiburonIAllocatorImpl : public IAllocator {
public:
    TiburonIAllocatorImpl(int heap) : mHeap(heap) {}
    virtual void *Allocate(unsigned int size, unsigned int align, int flags);
    virtual void Deallocate(void *p);
    virtual unsigned int MaxAlloc() const;

    void *operator new(unsigned int size) { return fn_801D2BB0(1, size, 0, 0); }

    int mHeap;
};

}
}

struct SpchLogEvent_t {
    int mId;
    int mNumArgs;
    int mHandle;
    unsigned int mArgs[36];
};

struct SpchLog_t {
    int mNext;
    unsigned int mCount;
    SpchLogEvent_t mEvents[8];
};

static unsigned char _Spch_Active = 0;
static SpchLog_t _SpchLog_EventLog;
static void *_pSpch_BankMem;
static EA::Allocator::TiburonIAllocatorImpl *pIAllocator;
static int (*_Spch_pPassFunction)(unsigned int id);
static void *_Spch_pNameFunction;
static unsigned char bVerboseLogging;

static void _Spch_AbortMessage(const char *pFormat, ...)
{
}

static unsigned int _Spch_GetTick(int unused)
{
    return SysGetSystemTime();
}

static void _SpchLogReset(void)
{
    unsigned int i;

    _SpchLog_EventLog.mNext = 0;
    _SpchLog_EventLog.mCount = 0;
    for (i = 0; i < 8; i++) {
        memset(&_SpchLog_EventLog.mEvents[i], 0, sizeof(SpchLogEvent_t));
    }
}

static void _SpchLogAddEvent(int type, int time, int numArgs, unsigned int *pArgs)
{
    SpchLogEvent_t *pEvent;
    int i;

    pEvent = &_SpchLog_EventLog.mEvents[_SpchLog_EventLog.mNext];
    pEvent->mId = type;
    pEvent->mHandle = time;
    pEvent->mNumArgs = numArgs;
    for (i = 0; i < 36; i++) {
        if (i < numArgs) {
            pEvent->mArgs[i] = pArgs[i];
        } else {
            pEvent->mArgs[i] = 0;
        }
    }
    _SpchLog_EventLog.mNext = (_SpchLog_EventLog.mNext + 1) & 7;
    _SpchLog_EventLog.mCount += (_SpchLog_EventLog.mCount < 8);
}

static int _Spch_AddEvent(int id, int numArgs, ...)
{
    va_list args;
    unsigned int argv[36];
    int result;
    int i;

    result = 0;
    va_start(args, numArgs);
    for (i = 0; i < 36; i++) {
        argv[i] = (i < numArgs) ? va_arg(args, unsigned int) : 0;
    }
    if (_Spch_pPassFunction((unsigned int)id >> 16)) {
        result = SPCH_AddEventV(id, numArgs, argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6],
                             argv[7], argv[8], argv[9], argv[10], argv[11], argv[12], argv[13], argv[14],
                             argv[15], argv[16], argv[17], argv[18], argv[19], argv[20], argv[21], argv[22],
                             argv[23], argv[24], argv[25], argv[26], argv[27], argv[28], argv[29], argv[30],
                             argv[31], argv[32], argv[33], argv[34], argv[35]);
        _SpchLogAddEvent(id, result, numArgs, argv);
    }
    return result;
}

void SpchInit(SpchInitParams_t *pParams)
{
    int dataSize;
    void *pBankMem;

    dataSize = SPCH_GetSampleDataRate(pParams->mUnknown8, pParams->mUnknownC, pParams->mUnknown10);
    pIAllocator = new EA::Allocator::TiburonIAllocatorImpl(1);
    SPCH_SetAllocator(pIAllocator);
    SPCH_Init((int)pParams->mpSampleRequest, pParams->mUnknown4, dataSize);
    pBankMem = fn_801D2B7C(SPCH_GetBankPtrMemSize(pParams->mUnknown14), 0, 0);
    SPCH_InitBankMem(pParams->mUnknown14, (VoxBankSlot_t *)pBankMem);
    _pSpch_BankMem = pBankMem;
    SpchExtVecs_t *pVecs = SPCH_GetExtVecs();
    pVecs->mpAbortMessage = _Spch_AbortMessage;
    pVecs->mpUnknown4 = 0;
    pVecs->mpGetTick = _Spch_GetTick;
    _SpchLogReset();
    _Spch_pPassFunction = pParams->mpUnknown1C;
    _Spch_pNameFunction = pParams->mpUnknown20;
    if (pParams->mUnknown18) {
        gSPCH_AddEvent = _Spch_AddEvent;
    }
    bVerboseLogging = pParams->mUnknown19;
    _Spch_Active = 1;
}

extern "C" void SpchShutdown(void)
{
    SPCH_Deinit();
    fn_801D2BD0(pIAllocator);
    fn_801D2BD0(_pSpch_BankMem);
    _Spch_Active = 0;
}

extern "C" int SpchLoadBank(ResFile_t *pRes, unsigned int index)
{
    return SPCH_AddBank((VoxBankHdr_t *)ResLoad(pRes, index, 1));
}

extern "C" int SpchLoadEventDB(ResFile_t *pRes, unsigned int index, unsigned int a)
{
    return SPCH_AddEventDB((char *)ResLoad(pRes, index, 1), a);
}

extern "C" void SpchInitRuleCallbacks(SpchRuleTestFunc_t pA, SpchRuleNotifyFunc_t pB)
{
    SPCH_InitRuleCallbacks(pA, pB);
}

extern "C" void SpchSetRuleCallbacks(SpchRuleCallbackFunc_t pFunc)
{
    SPCH_SetRuleCallback(pFunc);
}

extern "C" void SpchClearEventQueue(void)
{
    SPCH_ClearEventQueue();
}

namespace EA {
namespace Allocator {

void *TiburonIAllocatorImpl::Allocate(unsigned int size, unsigned int align, int flags)
{
    return fn_801D2BB0(mHeap, size, 0, 0);
}

void TiburonIAllocatorImpl::Deallocate(void *p)
{
    fn_801D2BD0(p);
}

unsigned int TiburonIAllocatorImpl::MaxAlloc() const
{
    return 0x1000000;
}

}
}
