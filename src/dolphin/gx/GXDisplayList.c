#include <libc/string.h>

#include <dolphin/gx/GXDispList.h>
#include <dolphin/gx/GXCommandList.h>
#include <dolphin/gx/GXFifo.h>
#include <dolphin/os.h>

#include "__gx.h"

static __GXFifoObj DisplayListFifo;
static volatile __GXFifoObj* OldCPUFifo;
static GXData __savedGXdata;

void GXBeginDisplayList(void* list, u32 size)
{
    __GXFifoObj* CPUFifo = (__GXFifoObj*)GXGetCPUFifo();

    if (__GXData->dirtyState != 0)
    {
        __GXSetDirtyState();
    }

    if (__GXData->dlSaveContext != 0)
    {
        memcpy(&__savedGXdata, __GXData, sizeof(__savedGXdata));
    }

    DisplayListFifo.base = (u8*)list;
    DisplayListFifo.top = (u8*)list + size - 4;
    DisplayListFifo.size = size;
    DisplayListFifo.count = 0;
    DisplayListFifo.rdPtr = list;
    DisplayListFifo.wrPtr = list;
    __GXData->inDispList = 1;
    GXSaveCPUFifo((GXFifoObj*)CPUFifo);
    OldCPUFifo = CPUFifo;
    GXSetCPUFifo((GXFifoObj*)&DisplayListFifo);
}

u32 GXEndDisplayList(void)
{
    u32 ov;
    BOOL enabled;
    u32 cpenable;

    GXGetCPUFifo();
    ov = (GX_GET_PI_REG(5) >> 26) & 1;
    GXSaveCPUFifo((GXFifoObj*)&DisplayListFifo);
    enabled = OSDisableInterrupts();

    if (__GXData->dlSaveContext != 0)
    {
        cpenable = __GXData->cpEnable;
        memcpy(__GXData, &__savedGXdata, sizeof(__savedGXdata));
        __GXData->cpEnable = cpenable;
    }

    GXSetCPUFifo((GXFifoObj*)OldCPUFifo);
    OSRestoreInterrupts(enabled);
    __GXData->inDispList = 0;

    if (!ov)
    {
        return DisplayListFifo.count;
    }
    return 0;
}

void GXCallDisplayList(const void* list, u32 nbytes)
{
    CHECK_GXBEGIN(254, "GXCallDisplayList");

    if (__GXData->dirtyState != 0)
    {
        __GXSetDirtyState();
    }

#if DEBUG
    __GXShadowDispList(list, nbytes);
#endif

    if (*(u32*)&__GXData->vNumNot == 0)
    { // checks both vNum and bpSent
        __GXSendFlushPrim();
    }

    GX_WRITE_U8(GX_CMD_CALL_DL);
    GX_WRITE_U32(list);
    GX_WRITE_U32(nbytes);
}
