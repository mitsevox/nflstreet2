/* Sound memory limits (smemlmt.c): sets the ARAM range the sound library may use, inside the
   library's critical section. */

#include "engine/sndbank.h"

int SNDmemlimits(unsigned int start, unsigned int end)
{
    int result;

    SNDSYS_entercritical();
    result = fn_802751E0(start, end);
    SNDSYS_leavecritical();
    return result;
}
