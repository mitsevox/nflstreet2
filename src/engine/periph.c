/* Controller peripherals: keeps the list of input drivers and the array of device slots with
   their data records, and polls, reads, writes and releases each connected controller through
   its driver. */

#include "engine/periph.h"
#include "engine/fn_801F7BD4.h"
#include "engine/fn_801F8014.h"
#include "game/fn_801D2B7C.h"

unsigned char Per_ModuleActive = 0;
unsigned char Per_BtnMask[8] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };

static int (*_Per_SeqFunction)();
static unsigned long _Per_DataTSize;
static Lock_801F8014 _Per_CS;

int MemFill(void *p, unsigned int size, int value, int flags);
int PerIsActive(void);
int PerReleaseDevices(void);

static unsigned int _PerCalcPad(unsigned int size, unsigned int align)
{
    unsigned int pad = size % align;

    if (pad != 0) {
        pad = align - pad;
    }
    return pad;
}

static int _PerCreateDriverList(PerDriver_t **ppDrivers)
{
    int err = 0;
    unsigned int count = 0;
    PerDriver_t **ppDriver;
    PerDriver_t *pDst;

    if (ppDrivers) {
        for (ppDriver = ppDrivers; *ppDriver; ppDriver++) {
            count++;
        }
    }
    Per_NumDrivers = count;
    Per_DriverArray = fn_801D2BB0(1, count * sizeof(PerDriver_t), 0, 0);
    if (Per_DriverArray == 0) {
        err = fn_801F7C88();
    } else if (ppDrivers) {
        pDst = Per_DriverArray;
        for (ppDriver = ppDrivers; *ppDriver; ppDriver++) {
            *pDst++ = **ppDriver;
        }
    }
    fn_801F7BD4(err);
    return err;
}

static void _PerDestroyDriverList(void)
{
    if (Per_DriverArray) {
        fn_801D2BD0(Per_DriverArray);
    }
}

static int _PerCreateDeviceArray(unsigned int numDevices, unsigned int numBits, unsigned int dataSize)
{
    int err;
    unsigned int i;
    PerDevice_t *pDevice;
    unsigned char *pData;

    Per_MaxButtons = numBits;
    Per_MaxAxis = dataSize;
    Per_MaxDevices = numDevices;
    _Per_DataTSize = dataSize + ((numBits + 7) >> 3) + 8;
    _Per_DataTSize += _PerCalcPad(_Per_DataTSize, 4);
    err = 0;
    Per_DeviceArray = fn_801D2BB0(1, numDevices * sizeof(PerDevice_t), 0, 0);
    if (Per_DeviceArray == 0) {
        err = fn_801F7C88();
    } else {
        Per_DeviceDataBuffer = fn_801D2BB0(1, numDevices * _Per_DataTSize, 0, 0);
        if (Per_DeviceDataBuffer == 0) {
            err = fn_801F7C88();
            fn_801D2BD0(Per_DeviceArray);
        }
    }
    if (err == 0) {
        MemFill(Per_DeviceArray, numDevices * sizeof(PerDevice_t), 0, 4);
        MemFill(Per_DeviceDataBuffer, numDevices * _Per_DataTSize, 0, 4);
        Per_NumDevices = 0;
        pDevice = Per_DeviceArray;
        pData = Per_DeviceDataBuffer;
        for (i = 0; i < numDevices; i++) {
            pDevice->mpData = pData;
            pDevice->mIndex = i;
            ((PerData_t *)pData)->mIndex = i;
            pDevice->mStatus = 0;
            pDevice++;
            pData += _Per_DataTSize;
        }
    }
    fn_801F7BD4(err);
    return err;
}

static void _PerDestroyDeviceArray(void)
{
    if (Per_DeviceArray) {
        fn_801D2BD0(Per_DeviceArray);
        fn_801D2BD0(Per_DeviceDataBuffer);
    }
}

int PerInit(PerInitParms_t *pDesc)
{
    int err;

    if (Per_ModuleActive == 0) {
        fn_801F7FA8(&_Per_CS);
        fn_801F8014(&_Per_CS);
        err = _PerCreateDeviceArray(pDesc->mNumDevices, pDesc->mUnknown04, pDesc->mUnknown08);
        if (err == 0) {
            err = _PerCreateDriverList(pDesc->mppDrivers);
            if (err == 0) {
                Per_NumDevices = pDesc->mNumDevices;
                err = PerSystemInit(pDesc->mpUnknown14);
                if (err == 0) {
                    _Per_SeqFunction = pDesc->mpUnknown0C;
                    Per_ModuleActive = 1;
                    err = PerRegisterDevices();
                }
            }
        }
        fn_801F809C(&_Per_CS);
    } else {
        err = 0x180001;
    }
    fn_801F7BD4(err);
    return err;
}

int PerShutdown(void)
{
    int err = 0;

    if (Per_ModuleActive) {
        fn_801F8014(&_Per_CS);
        PerReleaseDevices();
        PerSystemShutdown();
        _PerDestroyDeviceArray();
        _PerDestroyDriverList();
        fn_801F809C(&_Per_CS);
        fn_801F80D0(&_Per_CS);
        Per_ModuleActive = 0;
    } else {
        err = 0x180002;
    }
    fn_801F7BD4(err);
    return err;
}

int PerIsActive(void)
{
    return Per_ModuleActive != 0;
}

int PerPollSingleDevice(unsigned int index)
{
    int err = 0;
    unsigned char connected;
    PerDevice_t *pDevice;

    if (Per_ModuleActive == 0) {
        err = 0x180002;
    } else {
        connected = 0;
        if (index < Per_NumDevices) {
            pDevice = &Per_DeviceArray[index];
            connected = pDevice->mStatus ? 1 : 0;
            if (connected && !pDevice->mpDriver->mpPoll(pDevice, _Per_SeqFunction)) {
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

int PerReleaseSingleDevice(unsigned int index)
{
    int err = 0;
    unsigned char connected;
    PerDevice_t *pDevice;

    if (Per_ModuleActive == 0) {
        err = 0x180002;
    } else {
        connected = 0;
        if (index < Per_NumDevices) {
            pDevice = &Per_DeviceArray[index];
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

int PerReleaseDevices(void)
{
    int err = 0;
    unsigned int i;

    if (Per_ModuleActive == 0) {
        err = 0x180002;
    } else {
        for (i = 0; i < Per_NumDevices; i++) {
            if (Per_DeviceArray[i].mStatus) {
                err = PerReleaseSingleDevice(i);
            }
        }
    }
    fn_801F7BD4(err);
    return err;
}

int PerGetDeviceData(unsigned int index, void *pBuffer)
{
    int err = 0;
    int connected;
    PerDevice_t *pDevice;

    if (Per_ModuleActive == 0) {
        err = 0x180002;
    } else if (pBuffer != 0) {
        if (index < Per_NumDevices) {
            pDevice = &Per_DeviceArray[index];
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

int PerSendDeviceData(unsigned int index, void *pBuffer)
{
    int err = 0;
    int connected;
    PerDevice_t *pDevice;

    if (Per_ModuleActive == 0) {
        err = 0x180002;
    } else if (pBuffer != 0) {
        if (index < Per_NumDevices) {
            pDevice = &Per_DeviceArray[index];
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

unsigned long PerGetDataSize(void)
{
    return _Per_DataTSize - 8;
}

unsigned long PerSizeofPerDataT(void)
{
    return _Per_DataTSize;
}

unsigned int PerGetNumDevices(void)
{
    return Per_NumDevices;
}

int PerGetDeviceStatus(unsigned int index)
{
    if (index < Per_NumDevices && PerIsActive()) {
        return Per_DeviceArray[index].mStatus;
    }
    return 0;
}

unsigned int PerGetDeviceTypeT(unsigned int index)
{
    int err = 0;
    unsigned int type = 0;
    PerDevice_t *pDevice;

    if (index < Per_NumDevices) {
        pDevice = &Per_DeviceArray[index];
        if (pDevice->mStatus) {
            type = pDevice->mType;
        }
    } else {
        err = 0x180006;
    }
    fn_801F7BD4(err);
    return type;
}
