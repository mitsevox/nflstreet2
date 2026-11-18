/* 100 Hz clients (sclnt100.c): adds and removes the functions the sound server calls every tick. */

#include "engine/sndbank.h"

void SNDSYS_add100hzclient(void (*client)(void))
{
    if (lbl_803A6C24.m168 != 0) {
        lbl_803A6C24.m174[lbl_803A6C24.m16A] = client;
        lbl_803A6C24.m16A++;
    }
}

void SNDSYS_remove100hzclient(void (*client)(void))
{
    int i;

    if (lbl_803A6C24.m168 != 0) {
        SNDSYS_entercritical();
        for (i = 0; i < lbl_803A6C24.m16A; i++) {
            if (lbl_803A6C24.m174[i] == client) {
                lbl_803A6C24.m16A--;
                for (; i < lbl_803A6C24.m16A; i++) {
                    lbl_803A6C24.m174[i] = lbl_803A6C24.m174[i + 1];
                }
                break;
            }
        }
        SNDSYS_leavecritical();
    }
}
