/* Game Boy Advance fan link service: wakes the link service when the link is active. */

#include <dolphin/os.h>

extern int lbl_803EC590;
extern OSCond lbl_803ED4BC;

void GBAFanServiceLink(void)
{
    if (lbl_803EC590 != 0)
        OSSignalCond(&lbl_803ED4BC);
}
