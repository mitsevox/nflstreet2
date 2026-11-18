/* Low-level controller ports: registers a driver for each connected controller, notices
   controllers being plugged in or pulled out, and keeps each port's driver data. */

#include <dolphin/si.h>
#include "engine/periph.h"
#include "game/fn_801D2B7C.h"

extern void *lbl_803ED664;

void fn_801CE234(void (*pCallback)(void));
int PADInit(void);
void Init_GFLink(void);
int PerRegisterSingleDevice(unsigned char port);
int PerUnRegisterDevices(void);
void PerCheckConnectSingle(unsigned char port);
unsigned int PerSystemGetDriverDataSize(void);

int PerSystemInit(void *pData)
{
    PADInit();
    Init_GFLink();
    lbl_803ED664 = fn_801D2BB0(1, PerSystemGetDriverDataSize() * 4, 0, 0);
    Per_NumDevices = 4;
    PerRegisterDevices();
    PerJoyDriverPollPADs();
    fn_801CE234(PerJoyDriverPollPADs);
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

    for (port = 0; port < Per_NumDevices; port++) {
        PerRegisterSingleDevice(port);
    }
    return 0;
}

int PerRegisterSingleDevice(unsigned char port)
{
    unsigned char i;
    unsigned char arg;

    for (i = 0; i < Per_NumDrivers; i++) {
        arg = port;
        if (Per_DriverArray[i].mpInit(&Per_DeviceArray[port], &arg) == 1) {
            Per_DeviceArray[port].mpDriver = &Per_DriverArray[i];
            break;
        }
    }
    return 0;
}

int PerUnRegisterDevices(void)
{
    unsigned char port;

    for (port = 0; port < Per_NumDevices; port++) {
        PerRegisterSingleDevice(port);
    }
    return 0;
}

void PerCheckConnectAll(void)
{
    unsigned char port;

    for (port = 0; port < Per_NumDevices; port++) {
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
    type = PerGetDeviceTypeT(port);
    if (status == 8) {
        if (Per_DeviceArray[port].mStatus != 0 && !(type & 0x800)) {
            PerReleaseSingleDevice(port);
            Per_DeviceArray[port].mpDriver = 0;
            Per_DeviceArray[port].mStatus = 0;
            Per_DeviceArray[port].mType = 0;
        }
    } else if (Per_DeviceArray[port].mStatus == 0) {
        PerRegisterSingleDevice(port);
    }
}

int PerIsDeviceConnected(unsigned int port)
{
    if (Per_DeviceArray[port].mStatus == 0) {
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
