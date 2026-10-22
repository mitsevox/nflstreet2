#include "engine/periph.h"
#include "engine/fn_801F7BD4.h"
#include "engine/fn_801F8014.h"
#include "game/fn_801D2B7C.h"

extern Lock_801F8014 lbl_8039ADC4;
extern unsigned char lbl_803EBD68;
extern int (*lbl_803ECF50)();
extern unsigned long lbl_803ECF54;
extern unsigned int lbl_803ED5EC;
extern unsigned int lbl_803ED650;
extern unsigned int lbl_803ED654;
extern unsigned char *lbl_803ED65C;

int fn_801D34D0(void *p, unsigned int size, int value, int flags);
int fn_801E15B8(void);
int fn_801E173C(void);

static unsigned int fn_801E11D0(unsigned int size, unsigned int align)
{
    unsigned int pad = size % align;

    if (pad != 0) {
        pad = align - pad;
    }
    return pad;
}

static int fn_801E11E8(Driver_801E11E8 **ppDrivers)
{
    int err = 0;
    unsigned int count = 0;
    Driver_801E11E8 **ppDriver;
    Driver_801E11E8 *pDst;

    if (ppDrivers) {
        for (ppDriver = ppDrivers; *ppDriver; ppDriver++) {
            count++;
        }
    }
    lbl_803ED648 = count;
    lbl_803ED64C = fn_801D2BB0(1, count * sizeof(Driver_801E11E8), 0, 0);
    if (lbl_803ED64C == 0) {
        err = fn_801F7C88();
    } else if (ppDrivers) {
        pDst = lbl_803ED64C;
        for (ppDriver = ppDrivers; *ppDriver; ppDriver++) {
            *pDst++ = **ppDriver;
        }
    }
    fn_801F7BD4(err);
    return err;
}

static void fn_801E12CC(void)
{
    if (lbl_803ED64C) {
        fn_801D2BD0(lbl_803ED64C);
    }
}

static int fn_801E12F8(unsigned int numDevices, unsigned int numBits, unsigned int dataSize)
{
    int err;
    unsigned int i;
    Device_801E12F8 *pDevice;
    unsigned char *pData;
    unsigned long size;

    lbl_803ED650 = numBits;
    lbl_803ED5EC = dataSize;
    lbl_803ED654 = numDevices;
    lbl_803ECF54 = dataSize + ((numBits + 7) >> 3) + 8;
    lbl_803ECF54 += fn_801E11D0(lbl_803ECF54, 4);
    err = 0;
    lbl_803ED658 = fn_801D2BB0(1, numDevices * sizeof(Device_801E12F8), 0, 0);
    if (lbl_803ED658 == 0) {
        err = fn_801F7C88();
    } else {
        lbl_803ED65C = fn_801D2BB0(1, numDevices * lbl_803ECF54, 0, 0);
        if (lbl_803ED65C == 0) {
            err = fn_801F7C88();
            fn_801D2BD0(lbl_803ED658);
        }
    }
    if (err == 0) {
        fn_801D34D0(lbl_803ED658, numDevices * sizeof(Device_801E12F8), 0, 4);
        fn_801D34D0(lbl_803ED65C, numDevices * lbl_803ECF54, 0, 4);
        lbl_803ED660 = 0;
        pDevice = lbl_803ED658;
        pData = lbl_803ED65C;
        size = lbl_803ECF54;
        for (i = 0; i < numDevices; i++) {
            pDevice->mpData = pData;
            pDevice->mIndex = i;
            *(unsigned int *)pData = i;
            pDevice->mStatus = 0;
            pDevice++;
            pData += size;
        }
    }
    fn_801F7BD4(err);
    return err;
}

static void fn_801E1444(void)
{
    if (lbl_803ED658) {
        fn_801D2BD0(lbl_803ED658);
        fn_801D2BD0(lbl_803ED65C);
    }
}

int fn_801E1478(Desc_801E1478 *pDesc)
{
    int err;

    if (lbl_803EBD68 == 0) {
        fn_801F7FA8(&lbl_8039ADC4);
        fn_801F8014(&lbl_8039ADC4);
        err = fn_801E12F8(pDesc->mNumDevices, pDesc->mUnknown04, pDesc->mUnknown08);
        if (err == 0) {
            err = fn_801E11E8(pDesc->mppDrivers);
            if (err == 0) {
                lbl_803ED660 = pDesc->mNumDevices;
                err = fn_801E1A20(pDesc->mpUnknown14);
                if (err == 0) {
                    lbl_803ECF50 = pDesc->mpUnknown0C;
                    lbl_803EBD68 = 1;
                    err = fn_801E1AB4();
                }
            }
        }
        fn_801F809C(&lbl_8039ADC4);
    } else {
        err = 0x180001;
    }
    fn_801F7BD4(err);
    return err;
}

int fn_801E153C(void)
{
    int err = 0;

    if (lbl_803EBD68) {
        fn_801F8014(&lbl_8039ADC4);
        fn_801E173C();
        fn_801E1A80();
        fn_801E1444();
        fn_801E12CC();
        fn_801F809C(&lbl_8039ADC4);
        fn_801F80D0(&lbl_8039ADC4);
        lbl_803EBD68 = 0;
    } else {
        err = 0x180002;
    }
    fn_801F7BD4(err);
    return err;
}

int fn_801E15B8(void)
{
    return lbl_803EBD68 != 0;
}

int fn_801E15D0(unsigned int index)
{
    int err = 0;
    int connected;
    Device_801E12F8 *pDevice;

    if (lbl_803EBD68 == 0) {
        err = 0x180002;
    } else {
        connected = 0;
        if (index < lbl_803ED660) {
            pDevice = &lbl_803ED658[index];
            connected = pDevice->mStatus ? 1 : 0;
            if (connected && !pDevice->mpDriver->mpPoll(pDevice, lbl_803ECF50)) {
                err = 0x180004;
            }
        }
        if (!connected) {
            err = 0x180006;
        }
    }
    fn_801F7BD4(err);
    return err;
}

int fn_801E1688(unsigned int index)
{
    int err = 0;
    int connected;
    Device_801E12F8 *pDevice;

    if (lbl_803EBD68 == 0) {
        err = 0x180002;
    } else {
        connected = 0;
        if (index < lbl_803ED660) {
            pDevice = &lbl_803ED658[index];
            connected = pDevice->mStatus ? 1 : 0;
            if (connected && !pDevice->mpDriver->mpRelease(pDevice)) {
                err = 0x180005;
            }
        }
        if (!connected) {
            err = 0x180006;
        }
    }
    fn_801F7BD4(err);
    return err;
}

int fn_801E173C(void)
{
    int err = 0;
    unsigned int i;

    if (lbl_803EBD68 == 0) {
        err = 0x180002;
    } else {
        for (i = 0; i < lbl_803ED660; i++) {
            if (lbl_803ED658[i].mStatus) {
                err = fn_801E1688(i);
            }
        }
    }
    fn_801F7BD4(err);
    return err;
}

int fn_801E17D0(unsigned int index, void *pBuffer)
{
    int err = 0;
    int connected;
    Device_801E12F8 *pDevice;

    if (lbl_803EBD68 == 0) {
        err = 0x180002;
    } else if (pBuffer != 0) {
        if (index < lbl_803ED660) {
            pDevice = &lbl_803ED658[index];
            connected = pDevice->mStatus ? 1 : 0;
            if (connected && !pDevice->mpDriver->mpGetData(pDevice, pBuffer)) {
                err = 0x180006;
            }
        } else {
            err = 0x180006;
        }
    } else {
        err = 0x180007;
    }
    fn_801F7BD4(err);
    return err;
}

int fn_801E1884(unsigned int index, void *pBuffer)
{
    int err = 0;
    int connected;
    Device_801E12F8 *pDevice;

    if (lbl_803EBD68 == 0) {
        err = 0x180002;
    } else if (pBuffer != 0) {
        if (index < lbl_803ED660) {
            pDevice = &lbl_803ED658[index];
            connected = pDevice->mStatus ? 1 : 0;
            if (connected && pDevice->mpDriver->mpSendData && !pDevice->mpDriver->mpSendData(pDevice, pBuffer)) {
                err = 0x180006;
            }
        } else {
            err = 0x180006;
        }
    } else {
        err = 0x180007;
    }
    fn_801F7BD4(err);
    return err;
}

unsigned long fn_801E1940(void)
{
    return lbl_803ECF54 - 8;
}

unsigned long fn_801E194C(void)
{
    return lbl_803ECF54;
}

unsigned int fn_801E1954(void)
{
    return lbl_803ED660;
}

int fn_801E195C(unsigned int index)
{
    if (index < lbl_803ED660 && fn_801E15B8()) {
        return lbl_803ED658[index].mStatus;
    }
    return 0;
}

unsigned int fn_801E19B4(unsigned int index)
{
    int err = 0;
    unsigned int type = 0;
    Device_801E12F8 *pDevice;

    if (index < lbl_803ED660) {
        pDevice = &lbl_803ED658[index];
        if (pDevice->mStatus) {
            type = pDevice->mType;
        }
    } else {
        err = 0x180006;
    }
    fn_801F7BD4(err);
    return type;
}
