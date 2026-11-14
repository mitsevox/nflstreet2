/* Auxiliary RAM (ARAM) access: sets up the ARAM allocator and request queue at boot and copies blocks
   between main memory and ARAM (replay frames, memory snapshots, resource data), waiting for each
   transfer to finish. */

#include <dolphin/ar.h>
#include <dolphin/os.h>
#include <dolphin/os/OSCache.h>

static u32 _AuxRam_ARBlocks[1];
static volatile int _AuxRam_DMACount;

u32 AuxRamInit(void)
{
    ARInit(_AuxRam_ARBlocks, 1);
    ARQInit();
    return ARGetBaseAddress();
}

void AuxRamShutdown(void)
{
}

/* Each finished request lowers the count that the transfer loops wait on. */
void AuxRamARQCallback(u32 request)
{
    _AuxRam_DMACount--;
}

/* Posts the request again when the count has not changed within about two seconds. */
void AuxRamUpload(u32 dest, void *pSource, u32 length)
{
    ARQRequest request;
    int pending;
    u32 deadline;

    DCFlushRange(pSource, length);
    pending = _AuxRam_DMACount;
retry:
    ARQPostRequest(&request, 1, ARQ_TYPE_MRAM_TO_ARAM, ARQ_PRIORITY_LOW, (u32)pSource, dest, length,
                   AuxRamARQCallback);
    deadline = OSTicksToSeconds(OSGetTime()) + 2;
    while (_AuxRam_DMACount == pending && OSTicksToSeconds(OSGetTime()) < deadline) {
    }
    if (_AuxRam_DMACount == pending) {
        goto retry;
    }
}

void AuxRamDownload(void *pDest, u32 source, u32 length)
{
    ARQRequest request;
    int pending;
    u32 deadline;

    DCInvalidateRange(pDest, length);
    pending = _AuxRam_DMACount;
retry:
    ARQPostRequest(&request, 1, ARQ_TYPE_ARAM_TO_MRAM, ARQ_PRIORITY_LOW, source, (u32)pDest, length,
                   AuxRamARQCallback);
    deadline = OSTicksToSeconds(OSGetTime()) + 2;
    while (_AuxRam_DMACount == pending && OSTicksToSeconds(OSGetTime()) < deadline) {
    }
    if (_AuxRam_DMACount == pending) {
        goto retry;
    }
}
