/* Filter control (sctlfilt.c): adds a filter definition to every voice of a sound handle. */

#include "engine/sndsys.h"

extern "C" {

int SNDCTRL_filteradd(int handle, Desc_80276798 *desc)
{
    int index;

    handle = fn_8026A288(handle);
    if (handle >= 0) {
        index = -1;
        while (iSNDpatchkey(handle, &index)) {
            fn_802750B8(index, desc);
        }
    }
    return handle;
}

}
