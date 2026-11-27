/* AEMS timer update (saemstimupdt.c): the sound library's timer callback for the AEMS module
   player. While the module state is locked it only counts the missed tick; otherwise it calls
   every client on the module's timer list with its context. */

#include "engine/sndaems_state.h"

extern "C" {

void SNDAEMSI_timerupdate(void *unused)
{
    SndAemsState_t *state = &sndaems;
    SndAemsTimerClient_t *client;

    if (state->mLocked != 0) {
        state->mMissedTicks++;
        return;
    }
    client = sndaems.mpTimerClients;
    while (client != 0) {
        register SndAemsTimerClient_t *next asm("r0") = client->mpNext;
        register void *arg asm("r3") = (void *)client->mpCallback;

        asm volatile("mflr 22\n\tmtlr %0" : : "r"(arg) : "r22");
        arg = client->mpContext;
        asm volatile("mr 20,%1\n\tmr 21,31\n\tblrl\n\tmr 31,21\n\tmr %0,20\n\tmtlr 22"
                     : "=r"(next)
                     : "r"(next), "r"(arg)
                     : "r20", "r21", "r22");
        client = next;
    }
}

}
