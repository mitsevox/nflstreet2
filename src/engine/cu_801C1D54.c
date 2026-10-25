#include <dolphin/ar.h>
#include <dolphin/os.h>
#include <dolphin/os/OSCache.h>

/* The target reads the bus clock through the absolute low-memory address (lis 0x8000, lwz 0xF8). */
#define BUS_CLOCK_801C1D54 (*(u32 *)0x800000F8)

extern u32 lbl_803ECEC4;
extern volatile int lbl_803ECEC8;

u32 fn_801C1D54(void)
{
    ARInit(&lbl_803ECEC4, 1);
    ARQInit();
    return ARGetBaseAddress();
}

void fn_801C1D84(void)
{
}

void fn_801C1D88(u32 request)
{
    lbl_803ECEC8--;
}

void fn_801C1D98(u32 dest, void *pSource, u32 length)
{
    ARQRequest request;
    int pending;
    u32 deadline;

    DCFlushRange(pSource, length);
    pending = lbl_803ECEC8;
    do {
        ARQPostRequest(&request, 1, ARQ_TYPE_MRAM_TO_ARAM, ARQ_PRIORITY_LOW, (u32)pSource, dest, length,
                       fn_801C1D88);
        deadline = OSGetTime() / (BUS_CLOCK_801C1D54 / 4) + 2;
        while (lbl_803ECEC8 == pending && OSGetTime() / (BUS_CLOCK_801C1D54 / 4) < deadline) {
        }
    } while (lbl_803ECEC8 == pending);
}

void fn_801C1E78(void *pDest, u32 source, u32 length)
{
    ARQRequest request;
    int pending;
    u32 deadline;

    DCInvalidateRange(pDest, length);
    pending = lbl_803ECEC8;
    do {
        ARQPostRequest(&request, 1, ARQ_TYPE_ARAM_TO_MRAM, ARQ_PRIORITY_LOW, source, (u32)pDest, length,
                       fn_801C1D88);
        deadline = OSGetTime() / (BUS_CLOCK_801C1D54 / 4) + 2;
        while (lbl_803ECEC8 == pending && OSGetTime() / (BUS_CLOCK_801C1D54 / 4) < deadline) {
        }
    } while (lbl_803ECEC8 == pending);
}
