/* Sound system setup (ssys.cpp): the Snd::System, Snd::Memory and Snd::Profile front end the game
   calls before and after starting the sound library. Each setter reads the library options, changes
   one field (bank and voice counts, output mode, ARAM use, abort handler, heaps, profiler hooks) and
   writes them back, or, once the library runs, queues the change; Init clears the queued changes and
   starts the library. */

#include "engine/ssysinit.h"
#include "engine/ssys.h"

extern "C" {
int SNDPLATFORM_ModeSetUp(SNDSYSOPTS *opts, int mode);
}

/* A setting changed while the library runs: its value and whether it is pending. */
typedef struct SndPendingCount_t {
    unsigned char mCount;
    int mPending;
} SndPendingCount_t;

typedef struct SndPendingRate_t {
    int mRate;
    int mPending;
} SndPendingRate_t;

typedef struct SndPendingMode_t {
    int mMode;
    int mPending;
} SndPendingMode_t;

namespace Snd {

/* The main-memory heap and the output mode that Init hands to the library. */
void *pheap = 0;
OutputMode outputmode = OUTPUT_SURROUND;

/* The changes queued while the library runs; Init clears them. */
SndPendingCount_t gVoicesNext[4];
SndPendingRate_t gOutputSampleRateNext[4];
SndPendingMode_t gOutputModeNext;
int heapsize;

/* The front end's result for a sound library error code. */
static inline int _SndSysResult(int error)
{
    switch (error) {
    case 0:
        return 0;
    case -19:
        return -1;
    case -18:
        return -7;
    case -15:
        return -8;
    case -14:
        return -4;
    case -10:
        return -9;
    case -9:
    case -6:
        return -2;
    case -8:
        return -10;
    case -7:
        return -11;
    default:
        return -6;
    }
}

/* Read and write the library options, giving the front end's result. */
static inline int _SndSysGetOpts(SNDSYSOPTS *opts)
{
    return _SndSysResult(SNDSYS_getopts(opts));
}

static inline int _SndSysSetOpts(SNDSYSOPTS *opts)
{
    return _SndSysResult(SNDSYS_setopts(opts));
}

int System::SetMaxBanks(int count)
{
    SNDSYSOPTS opts;

    _SndSysGetOpts(&opts);
    opts.mParams.m8 = count;
    _SndSysSetOpts(&opts);
    return 0;
}

int System::CapOutputMode(OutputMode mode, bool *capable)
{
    SNDSYSOPTS opts;

    *capable = false;
    _SndSysGetOpts(&opts);
    switch (mode) {
    case 2:
    case 3:
    case 4:
    case 5:
        break;
    case 1:
        if (opts.m5 > 1) {
            *capable = true;
        }
        break;
    case 0:
    case 8:
        *capable = true;
        break;
    }
    return 0;
}

int System::SetOutputMode(OutputMode mode)
{
    bool capable;

    CapOutputMode(mode, &capable);
    if (!capable) {
        return -5;
    }
    if (lbl_803A6C24.m168 == 0) {
        outputmode = mode;
    } else {
        gOutputModeNext.mMode = mode;
        gOutputModeNext.mPending = 1;
    }
    return 0;
}

int System::SetVoices(Device device, int count)
{
    SNDSYSOPTS opts;

    _SndSysGetOpts(&opts);
    switch (device) {
    case DEVICE_MAIN:
        if (lbl_803A6C24.m168 == 0) {
            opts.mParams.mE = count;
        } else {
            gVoicesNext[device].mCount = count;
            gVoicesNext[device].mPending = 1;
        }
        break;
    case DEVICE_ARAM:
        if (lbl_803A6C24.m168 == 0) {
            opts.mParams.m12 = count;
        } else {
            gVoicesNext[device].mCount = count;
            gVoicesNext[device].mPending = 1;
        }
        break;
    default:
        return -5;
    }
    if (lbl_803A6C24.m168 == 0) {
        _SndSysSetOpts(&opts);
    }
    return 0;
}

int System::SetSndInitsAram(bool inits)
{
    SNDSYSOPTS opts;

    _SndSysGetOpts(&opts);
    opts.mParams.m21 = inits;
    _SndSysSetOpts(&opts);
    return 0;
}

int System::SetAbortHandler(void (*handler)(const char *message))
{
    SNDSYSOPTS opts;

    _SndSysGetOpts(&opts);
    opts.mMem.mpAbort = handler;
    _SndSysSetOpts(&opts);
    return 0;
}

int System::Init(int arg)
{
    SNDSYSOPTS opts;
    int result;
    int i;

    result = _SndSysGetOpts(&opts);
    if (result < 0) {
        return _SndSysResult(result);
    }
    for (i = 0; i < 4; i++) {
        gVoicesNext[i].mPending = 0;
        gOutputSampleRateNext[i].mPending = 0;
    }
    gOutputModeNext.mPending = 0;
    lbl_803A6C24.m231 = 0;
    lbl_803A6C24.m234 = 0;
    SNDPLATFORM_ModeSetUp(&opts, outputmode);
    _SndSysSetOpts(&opts);
    SNDSYSI_init(pheap, heapsize, arg);
    return 0;
}

bool System::IsInited(void)
{
    return lbl_803A6C24.m168 == 1;
}

int System::Restore(void)
{
    SNDSYS_restore();
    pheap = 0;
    return 0;
}

int Memory::SetHeap(Device device, void *heap, int size)
{
    SNDSYSOPTS opts;

    switch (device) {
    case DEVICE_MAIN:
        pheap = heap;
        heapsize = size;
        break;
    case DEVICE_ARAM:
        _SndSysGetOpts(&opts);
        opts.mParams.m38 = (unsigned int)heap;
        opts.mParams.m3C = size;
        _SndSysSetOpts(&opts);
        break;
    default:
        return -5;
    }
    return 0;
}

int Profile::SetFunctionProfiler(void (*enter)(const char *name), void (*exit)(const char *name))
{
    SNDSYSOPTS opts;

    _SndSysGetOpts(&opts);
    opts.mMem.mpProfileEnter = enter;
    opts.mMem.mpProfileExit = exit;
    _SndSysSetOpts(&opts);
    return 0;
}

}
