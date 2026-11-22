/* Game Boy Advance fan link service: wakes the link service when the link is active. */

#include <dolphin/os.h>

static int _GBAFan_iState = 0;
static OSCond _GBAFan_ServiceCond;

void GBAFanServiceLink(void)
{
    if (_GBAFan_iState != 0)
        OSSignalCond(&_GBAFan_ServiceCond);
}
