/* Sound control (slowpass.c): sets the low-pass filter value on every voice that a sound handle is
   playing. */

#include "engine/sndsys.h"

extern "C" {

int SNDCTRL_lowpass(int handle, int value)
{
    int index;

    handle = fn_8026A288(handle);
    if (handle >= 0) {
        index = -1;
        while (iSNDpatchkey(handle, &index)) {
            fn_80274D34(index, value);
        }
    }
    return handle;
}

}
