#ifndef ENGINE_SPEECH_H
#define ENGINE_SPEECH_H

#include "engine/Resource.h"

namespace EA {
namespace Allocator {
class IAllocator {
public:
    virtual void *Allocate(unsigned int size, unsigned int align, int flags) = 0;
    virtual void Deallocate(void *p) = 0;
    virtual unsigned int MaxAlloc() const = 0;
};
}
}

struct SpchEventKey_t;
struct SpchIGSampleRequest_t;
typedef int (*SpchSampleRequestFunc_t)(SpchIGSampleRequest_t *pRequest);
typedef int (*SpchRuleTestFunc_t)(SpchEventKey_t *pKey, int rule, int value, int game);
typedef void (*SpchRuleNotifyFunc_t)(SpchEventKey_t *pKey, int rule, int value, int game);
typedef int (*SpchRuleCallbackFunc_t)(SpchEventKey_t *pKey);

struct SpchInitParams_t {
    SpchSampleRequestFunc_t mpSampleRequest;
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

extern "C" {
void SpchInit(SpchInitParams_t *pParams);
void SpchShutdown(void);
int SpchLoadBank(ResFile_t *pRes, unsigned int index);
int SpchLoadEventDB(ResFile_t *pRes, unsigned int index, unsigned int key);
void SpchInitRuleCallbacks(SpchRuleTestFunc_t pTest, SpchRuleNotifyFunc_t pNotify);
void SpchSetRuleCallbacks(SpchRuleCallbackFunc_t pFunc);
void SpchClearEventQueue(void);
}

#endif
