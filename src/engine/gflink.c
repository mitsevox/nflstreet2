/* Game Boy Advance link status: initializes the GBA library and keeps, for each of the four
   controller ports, whether a GBA answers on it (with a one-second grace period before a
   lost link is reported). The file also defines a character map string and a status byte
   that no function in this build uses. */

#include <dolphin/os.h>
#include <dolphin/gba.h>

void *memset();

typedef struct GFLinkPort_t
{
    OSTick mUnknown00;
    char mUnknown04[4];
    int mUnknown08;
    char mUnknown0C[0x260 - 0xC];
} GFLinkPort_t;

static char *_charMap = " ABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&'()*+,-./0123456789:;<=>?@[\\]^_                  abcdefghijklmnopqrstuvwxyz";
static unsigned char _hackStatus;

GFLinkPort_t _state[4];

void Init_GFLink(void)
{
    int i;

    GBAInit();
    for (i = 0; i < 4; i++)
        memset(&_state[i], 0, sizeof(GFLinkPort_t));
}

int GetState_GFLink(int channel)
{
    OSTick tick;
    u8 status;

    if (_state[channel].mUnknown08 < 2 || _state[channel].mUnknown08 > 4)
    {
        tick = OSGetTick();
        if (GBAGetStatus(channel, &status) == 0)
        {
            _state[channel].mUnknown00 = tick;
            _state[channel].mUnknown08 = 1;
        }
        else if (OSTicksToSeconds(tick - _state[channel].mUnknown00) != 0)
        {
            _state[channel].mUnknown08 = 0;
        }
    }
    return _state[channel].mUnknown08;
}
