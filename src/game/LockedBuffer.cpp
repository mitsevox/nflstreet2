/* A heap buffer guarded by a lock, freed on destruction. */
#include "game/fn_801D2B7C.h"
#include "engine/SysCriticalSection.h"

/* Buffer owned by LockedBuffer; FreeBuffer releases it. */
struct LockedBufferData {
    bool IsOpen() const { return mpData != 0; }

    void *mpData;
    int mUnknown4;
    int mUnknown8;
    unsigned char mUnknownC;
};

class LockedBuffer {
public:
    virtual ~LockedBuffer();
    void FreeBuffer();

    LockedBufferData mBuffer;
    SysCriticalSection_t mLock;
};

LockedBuffer::~LockedBuffer()
{
    if (mBuffer.IsOpen()) {
        FreeBuffer();
    }
    SysShutdownCriticalSectionFunc(&mLock);
}

void LockedBuffer::FreeBuffer()
{
    SysEnterCriticalSectionFunc(&mLock);
    if (mBuffer.IsOpen()) {
        fn_801D2BD0(mBuffer.mpData);
        mBuffer.mUnknown8 = 0;
        mBuffer.mUnknown4 = 0;
        mBuffer.mpData = 0;
        mBuffer.mUnknownC = 0;
    }
    SysExitCriticalSectionFunc(&mLock);
}
