/* Low-level controller ports: registers a driver for each connected controller, notices
   controllers being plugged in or pulled out, and keeps each port's driver data. */

#include <dolphin/si.h>
#include "engine/periph.h"
#include "game/fn_801D2B7C.h"

extern void *lbl_803ED664;

void fn_801CE234(void (*pCallback)(void));
int PADInit(void);
void fn_802856D8(void);
int PerRegisterSingleDevice(unsigned char port);
int PerUnRegisterDevices(void);
void PerCheckConnectSingle(unsigned char port);
unsigned int PerSystemGetDriverDataSize(void);

int PerSystemInit(void *pData)
{
    PADInit();
    fn_802856D8();
    lbl_803ED664 = fn_801D2BB0(1, PerSystemGetDriverDataSize() * 4, 0, 0);
    lbl_803ED660 = 4;
    PerRegisterDevices();
    fn_801E26FC();
    fn_801CE234(fn_801E26FC);
    return 0;
}

int PerSystemShutdown(void)
{
    PerUnRegisterDevices();
    fn_801D2BD0(lbl_803ED664);
    lbl_803ED664 = 0;
    return 0;
}

int PerRegisterDevices(void)
{
    unsigned char port;

    for (port = 0; port < lbl_803ED660; port++) {
        PerRegisterSingleDevice(port);
    }
    return 0;
}

int PerRegisterSingleDevice(unsigned char port)
{
    unsigned char i;
    unsigned char arg;

    for (i = 0; i < lbl_803ED648; i++) {
        arg = port;
        if (lbl_803ED64C[i].mpInit(&lbl_803ED658[port], &arg) == 1) {
            lbl_803ED658[port].mpDriver = &lbl_803ED64C[i];
            break;
        }
    }
    return 0;
}

int PerUnRegisterDevices(void)
{
    unsigned char port;

    for (port = 0; port < lbl_803ED660; port++) {
        PerRegisterSingleDevice(port);
    }
    return 0;
}

void PerCheckConnectAll(void)
{
    unsigned char port;

    for (port = 0; port < lbl_803ED660; port++) {
        PerCheckConnectSingle(port);
    }
}

void PerCheckConnectSingle(unsigned char port)
{
    int status;
    int type;

    status = SIProbe(port);
    if (status == 0x80) {
        return;
    }
    type = fn_801E19B4(port);
    if (status == 8) {
        if (lbl_803ED658[port].mStatus != 0 && !(type & 0x800)) {
            fn_801E1688(port);
            lbl_803ED658[port].mpDriver = 0;
            lbl_803ED658[port].mStatus = 0;
            lbl_803ED658[port].mType = 0;
        }
    } else if (lbl_803ED658[port].mStatus == 0) {
        PerRegisterSingleDevice(port);
    }
}

int PerIsDeviceConnected(unsigned int port)
{
    if (lbl_803ED658[port].mStatus == 0) {
        return 0;
    }
    return 1;
}

void *PerSystemGetLLDriverData(unsigned int port)
{
    return (char *)lbl_803ED664 + PerSystemGetDriverDataSize() * port;
}

unsigned int PerSystemGetDriverDataSize(void)
{
    return 16;
}
