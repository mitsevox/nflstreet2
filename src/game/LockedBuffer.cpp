/* A heap buffer guarded by a lock, freed on destruction. */
#include "game/fn_801D2B7C.h"
#include "engine/fn_801F8014.h"

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
    Lock_801F8014 mLock;
};

LockedBuffer::~LockedBuffer()
{
    if (mBuffer.IsOpen()) {
        FreeBuffer();
    }
    fn_801F80D0(&mLock);
}

void LockedBuffer::FreeBuffer()
{
    fn_801F8014(&mLock);
    if (mBuffer.IsOpen()) {
        fn_801D2BD0(mBuffer.mpData);
        mBuffer.mUnknown8 = 0;
        mBuffer.mUnknown4 = 0;
        mBuffer.mpData = 0;
        mBuffer.mUnknownC = 0;
    }
    fn_801F809C(&mLock);
}
