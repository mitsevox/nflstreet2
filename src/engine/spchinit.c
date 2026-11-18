/* Starts and stops the play-by-play speech library: clears the callbacks, records the game's
   settings, seeds the random choices and resets the event, choice and bank tables. */

#include "engine/spchlib.h"

extern "C" {

void iSPCH_InitCallbacks(void)
{
    gCallbacks.mUnknown0 = 0;
    gCallbacks.mUnknown4 = 0;
    gCallbacks.mUnknown8 = 0;
    gCallbacks.mCallback = 0;
    gCallbacks.mUnknown10 = 0;
}

void SPCH_SetRuleCallback(int (*callback)(SpchEventKey_t *key))
{
    if (gSPCH_Initialized == 0x01789A34) {
        gCallbacks.mCallback = callback;
    }
}

int SPCH_Init(int a, int b, int c)
{
    int i;

    spchlibauthor[0] = 'S';
    if (gSPCH_Allocator != 0) {
        iSPCH_InitCallbacks();
        gDataRate = c;
        gCallbacks.mUnknown0 = a;
        gSPCH_AddEvent = fn_801AEC58;
        gGameNum = b;
        iSPCH_InitRandom(b);
        fn_801B118C();
        fn_801B192C(0);
        for (i = 0; i <= 7; i++) {
            gFilterSetting[i] = 0;
        }
        fn_801AE808();
        fn_801AF544();
        fn_801B2450();
        fn_801AE8DC();
        gSPCH_Initialized = 0x01789A34;
        return 1;
    }
    return 0;
}

void SPCH_Deinit(void)
{
    if (gSPCH_Initialized == 0x01789A34) {
        gSPCH_Initialized = 0;
        iSPCH_InitCallbacks();
        fn_801B2468();
        fn_801AE808();
    }
}

}
