/* AEMS timer update (saemstimupdt.c): the sound library's timer callback for the AEMS module
   player. While the module state is locked it only counts the missed tick; otherwise it calls
   every client on the module's timer list with its context. */

extern "C" {

typedef struct SndAemsTimerClient_t {
    struct SndAemsTimerClient_t *mpNext;
    int unk_0x4;
    void (*mpCallback)(void *context);
    void *mpContext;
} SndAemsTimerClient_t;

typedef struct SndAemsTimerState_t {
    SndAemsTimerClient_t *mpClients;
    unsigned char unk_0x4[5];
    unsigned char mMissedTicks;
    unsigned char unk_0xA[2];
    int mLocked;
} SndAemsTimerState_t;

extern SndAemsTimerState_t lbl_803A6BCC;

void SNDAEMSI_timerupdate(void *unused)
{
    SndAemsTimerState_t *state = &lbl_803A6BCC;
    SndAemsTimerClient_t *client;

    if (state->mLocked != 0) {
        state->mMissedTicks++;
        return;
    }
    client = lbl_803A6BCC.mpClients;
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
