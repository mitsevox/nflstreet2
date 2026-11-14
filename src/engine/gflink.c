/* Game Boy Advance link status: initializes the GBA library and keeps, for each of the four
   controller ports, whether a GBA answers on it (with a one-second grace period before a
   lost link is reported). */

#include <dolphin/os.h>
#include <dolphin/gba.h>

void *fn_801C1F94();

typedef struct GFLinkPort_t
{
    OSTick mUnknown00;
    char mUnknown04[4];
    int mUnknown08;
    char mUnknown0C[0x260 - 0xC];
} GFLinkPort_t;

extern GFLinkPort_t lbl_803E990C[];

void Init_GFLink(void)
{
    int i;

    GBAInit();
    for (i = 0; i < 4; i++)
        fn_801C1F94(&lbl_803E990C[i], 0, sizeof(GFLinkPort_t));
}

int GetState_GFLink(int channel)
{
    OSTick tick;
    u8 status;

    if (lbl_803E990C[channel].mUnknown08 < 2 || lbl_803E990C[channel].mUnknown08 > 4)
    {
        tick = OSGetTick();
        if (GBAGetStatus(channel, &status) == 0)
        {
            lbl_803E990C[channel].mUnknown00 = tick;
            lbl_803E990C[channel].mUnknown08 = 1;
        }
        else if (OSTicksToSeconds(tick - lbl_803E990C[channel].mUnknown00) != 0)
        {
            lbl_803E990C[channel].mUnknown08 = 0;
        }
    }
    return lbl_803E990C[channel].mUnknown08;
}
