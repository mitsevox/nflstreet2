/* High-pass control (shipass.c): sets the high-pass filter value of every voice of a sound handle. */

#include "engine/sndsys.h"

extern "C" {

int SNDCTRL_highpass(int handle, int value)
{
    int index;

    handle = SNDVOICEI_get(handle);
    if (handle >= 0) {
        index = -1;
        while (iSNDpatchkey(handle, &index)) {
            SNDPLATFORM_highpass(index, value);
        }
    }
    return handle;
}

}
