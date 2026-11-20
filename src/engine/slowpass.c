/* Sound control (slowpass.c): sets the low-pass filter value on every voice that a sound handle is
   playing. */

#include "engine/sndsys.h"

extern "C" {

int SNDCTRL_lowpass(int handle, int value)
{
    int index;

    handle = SNDVOICEI_get(handle);
    if (handle >= 0) {
        index = -1;
        while (iSNDpatchkey(handle, &index)) {
            SNDPLATFORM_lowpass(index, value);
        }
    }
    return handle;
}

}
