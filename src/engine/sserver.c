/* Sound server (sserver.c): the variable-rate timer service that calls the registered timer clients
   once per new tick, the 100 Hz server that runs the 100 Hz clients and steps every playing voice's
   volume ramp and envelope, and the library's critical section around the platform mutex. */

#include "engine/sndbank.h"

typedef struct SndTimerClient_t {
    struct SndTimerClient_t *m0;
    unsigned char unk_0x4[4];
    void (*m8)(void *context);
    void *mC;
} SndTimerClient_t;

typedef struct SndTimerClientList_t {
    SndTimerClient_t *m0;

    SndTimerClientList_t() : m0(0) {}
} SndTimerClientList_t;

namespace Snd {
void DefaultMutexLockFn(void);
void DefaultMutexUnlockFn(void);
}

extern SndTimerClientList_t SNDSYSI_timerclients;
extern int SNDSYSI_timertick;

void SNDSYSI_variabletimerservice(void)
{
    static int lastTick = 0;
    SndTimerClient_t *client;

    if (SNDSYSI_timertick != lastTick) {
        lastTick = SNDSYSI_timertick;
        client = SNDSYSI_timerclients.m0;
        while (client != 0) {
            SndTimerClient_t *next = client->m0;

            client->m8(client->mC);
            client = next;
        }
    }
}

SndTimerClientList_t SNDSYSI_timerclients;
int SNDSYSI_timertick;
void (*SNDSYSI_mutexlockfn)(void) = Snd::DefaultMutexLockFn;
void (*SNDSYSI_mutexunlockfn)(void) = Snd::DefaultMutexUnlockFn;

void SNDSYSI_100hzserver(void)
{
    int i;

    lbl_803A6C24.m170++;
    fn_802739F8();
    for (i = 0; i < lbl_803A6C24.m16A; i++) {
        lbl_803A6C24.m174[i]();
    }
    for (i = 0; i < lbl_803A6C24.m16C; i++) {
        Record_803A6DF0 *voice = &lbl_803A6C24.m1CC[i];
        int changed;

        if (voice->m6D != 1) {
            continue;
        }
        if (voice->m0 >= 0 && voice->m80 != 0) {
            if (++voice->m6C >= voice->m6A) {
                voice->m6C = 0;
            }
            voice->m8A = 0;
            fn_80277EC4(i);
            fn_80274B50(i);
        }
        changed = 0;
        if (voice->m7C != 0) {
            changed = 1;
            if (++voice->m6B >= voice->m69) {
                voice->m6B = 0;
            }
        }
        if (voice->m30 != 0.0f) {
            changed = 1;
            voice->m38 += voice->m30;
            if (!(voice->m30 >= 0.0f)) {
                if (!(voice->m38 > voice->m34)) {
                    voice->m38 = voice->m34;
                    voice->m30 = 0.0f;
                }
            } else if (!(voice->m38 < voice->m34)) {
                voice->m38 = voice->m34;
                voice->m30 = 0.0f;
            }
            if (voice->m38 < 0.0f) {
                fn_8026EDC4(voice->m0);
                continue;
            }
        }
        voice->m44--;
        if (voice->m3C != 0) {
            changed = 1;
            voice->m40 += voice->m3C;
        }
        if (voice->m44 == 0) {
            signed char stage = ++voice->m5D;
            SndEnvStage_t *env;

            if (stage >= voice->m5C) {
                fn_8026EDC4(voice->m0);
                continue;
            }
            env = &voice->m70[stage];
            voice->m44 = env->m0;
            if (voice->m44 < 0) {
                voice->m44 = 0x7FFFFFFF;
            }
            voice->m3C = ((env->m4 << 16) - voice->m40) / voice->m44;
        }
        if (changed) {
            fn_80278598(i);
            fn_802747D8(i);
        }
    }
}

namespace Snd {

void DefaultMutexLockFn(void)
{
    fn_8027535C();
}

void DefaultMutexUnlockFn(void)
{
    fn_80275384();
}

}

void SNDSYS_entercritical(void)
{
    SNDSYSI_mutexlockfn();
    lbl_803A6C24.m169++;
}

void SNDSYS_leavecritical(void)
{
    lbl_803A6C24.m169--;
    SNDSYSI_mutexunlockfn();
}
