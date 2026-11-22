/* Reads the programmed volume for a sound handle. */

#include "engine/cu_802714A8.h"
#include "engine/sndvoice.h"

extern "C" {

int SNDCTRL_getprogvol(int handle)
{
    int volume;

    handle = SNDVOICEI_get(handle);
    if (handle < 0) {
        return -8;
    }

    float level = lbl_803A6C24.m1CC[handle].m38 * 127.0f;
    if (!(level < 0.0f)) {
        volume = (int)(level + 0.5f);
    } else {
        volume = (int)(level - 0.5f);
    }
    return volume;
}

}
