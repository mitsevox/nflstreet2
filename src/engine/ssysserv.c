/* Sound system service clients (ssysserv.c): the list of functions the sound system calls on
   every service pass, with add, remove and the service pass itself. */

#include "engine/sndstrm.h"

void iSNDserveraddclient(void (*client)(void))
{
    lbl_803A6C24.m18C[lbl_803A6C24.m16B] = client;
    lbl_803A6C24.m16B++;
}

void iSNDserverremoveclient(void (*client)(void))
{
    int i;

    for (i = 0; i < lbl_803A6C24.m16B; i++) {
        if (lbl_803A6C24.m18C[i] == client) {
            lbl_803A6C24.m16B--;
            for (; i < lbl_803A6C24.m16B; i++) {
                lbl_803A6C24.m18C[i] = lbl_803A6C24.m18C[i + 1];
            }
            return;
        }
    }
}

extern "C" {

void SNDSYS_service(void)
{
    int i;

    if (lbl_803A6C24.m168 != 0) {
        for (i = 0; i < lbl_803A6C24.m16B; i++) {
            lbl_803A6C24.m18C[i]();
        }
    }
}

}
