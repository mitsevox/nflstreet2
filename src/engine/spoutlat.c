/* Output latency (spoutlat.c): the driver's output latency, or 0 before the library is started. */

#include "engine/sndbank.h"

int SNDPROFILE_outputlatency(void)
{
    int latency;

    if (lbl_803A6C24.m168 != 0) {
        latency = SNDPLATFORM_outputlatency();
    } else {
        latency = 0;
    }
    return latency;
}
