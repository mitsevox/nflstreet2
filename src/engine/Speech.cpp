/* Game-side front end of the speech (commentary) library: starts and stops it with its own
   allocator and bank memory, loads banks and event databases, installs the rule callbacks and
   filters and logs the events the game adds. */

#include <stddef.h>
#include <stdarg.h>
#include "engine/Resource.h"
#include "engine/system.h"
#include "game/fn_801D2B7C.h"

namespace EA {
namespace Allocator {

class IAllocator {
public:
    virtual void *Allocate(unsigned int size, unsigned int align, int flags) = 0;
    virtual void Deallocate(void *p) = 0;
    virtual unsigned int MaxAlloc() const = 0;
};

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

struct SpchExtVecs_t {
    void *mVecs[3];
};

struct SpchInitParams_t {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknownC;
    int mUnknown10;
    int mUnknown14;
    unsigned char mUnknown18;
    unsigned char mUnknown19;
    int (*mpUnknown1C)(unsigned int id);
    void *mpUnknown20;
};

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

extern "C" {
extern int (*gSPCH_AddEvent)(int, int, ...);

int SPCH_AddEventV(int id, int count, ...);
int SPCH_GetSampleDataRate(int a, int b, int mode);
void SPCH_SetAllocator(EA::Allocator::TiburonIAllocatorImpl *pAllocator);
int SPCH_Init(int a, int b, int c);
int SPCH_GetBankPtrMemSize(int numBanks);
void SPCH_InitBankMem(int numBanks, void *pMem);
SpchExtVecs_t *SPCH_GetExtVecs(void);
void SpchInit(SpchInitParams_t *pParams);

void *memset(void *dst, int value, size_t n);
void SPCH_ClearEventQueue(void);
void SPCH_InitRuleCallbacks(int (*pA)(void), void (*pB)(void));
void SPCH_SetRuleCallback(void *pFunc);
void SPCH_Deinit(void);
void SPCH_AddBank(void *pData);
void SPCH_AddEventDB(void *pData, int a);

void fn_801F5C34(void);
void fn_801F5C6C(ResFile_t *pRes, unsigned int index);
void fn_801F5C94(ResFile_t *pRes, unsigned int index, int a);
void fn_801F5CCC(int (*pA)(void), void (*pB)(void));
void fn_801F5CEC(void *pFunc);
void fn_801F5D0C(void);
}

static void fn_801F5760(const char *pFormat, ...)
{
}

static int fn_801F57AC(void)
{
    return SysGetSystemTime();
}

static void fn_801F57CC(void)
{
    unsigned int i;

    _SpchLog_EventLog.mNext = 0;
    _SpchLog_EventLog.mCount = 0;
    for (i = 0; i < 8; i++) {
        memset(&_SpchLog_EventLog.mEvents[i], 0, sizeof(SpchLogEvent_t));
    }
}

static void fn_801F5828(int type, int time, int numArgs, unsigned int *pArgs)
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

static int fn_801F58B8(int id, int numArgs, ...)
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
        fn_801F5828(id, result, numArgs, argv);
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
    SPCH_Init(pParams->mUnknown0, pParams->mUnknown4, dataSize);
    pBankMem = fn_801D2B7C(SPCH_GetBankPtrMemSize(pParams->mUnknown14), 0, 0);
    SPCH_InitBankMem(pParams->mUnknown14, pBankMem);
    _pSpch_BankMem = pBankMem;
    SpchExtVecs_t *pVecs = SPCH_GetExtVecs();
    pVecs->mVecs[0] = (void *)fn_801F5760;
    pVecs->mVecs[1] = 0;
    pVecs->mVecs[2] = (void *)fn_801F57AC;
    fn_801F57CC();
    _Spch_pPassFunction = pParams->mpUnknown1C;
    _Spch_pNameFunction = pParams->mpUnknown20;
    if (pParams->mUnknown18) {
        gSPCH_AddEvent = fn_801F58B8;
    }
    bVerboseLogging = pParams->mUnknown19;
    _Spch_Active = 1;
}

void fn_801F5C34(void)
{
    SPCH_Deinit();
    fn_801D2BD0(pIAllocator);
    fn_801D2BD0(_pSpch_BankMem);
    _Spch_Active = 0;
}

void fn_801F5C6C(ResFile_t *pRes, unsigned int index)
{
    SPCH_AddBank((void *)ResLoad(pRes, index, 1));
}

void fn_801F5C94(ResFile_t *pRes, unsigned int index, int a)
{
    SPCH_AddEventDB((void *)ResLoad(pRes, index, 1), a);
}

void fn_801F5CCC(int (*pA)(void), void (*pB)(void))
{
    SPCH_InitRuleCallbacks(pA, pB);
}

void fn_801F5CEC(void *pFunc)
{
    SPCH_SetRuleCallback(pFunc);
}

void fn_801F5D0C(void)
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
