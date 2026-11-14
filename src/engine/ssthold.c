/* Sound stream hold (ssthold.c): changes the hold value of one queued stream request inside
   the sound system's critical section. */

#include "engine/sndstrm.h"

extern "C" {

int SNDSTRM_modifyhold(int id, int hold)
{
    SndStreamRequest_t *request;
    int result;

    SNDSYS_entercritical();
    result = -8;
    request = SNDSTRMI_getrequestptr(id);
    if (request != 0) {
        request->mHold = (short)hold;
        result = 0;
    }
    SNDSYS_leavecritical();
    return result;
}

}
