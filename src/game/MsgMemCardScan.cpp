/* Memory card scan: walks this game's files on the memory card, keeping the best
   options file and the two best profile files, and looks for a connected device
   of one type. */

#include "game/Callees_801D57E0.h"
#include "game/MemCardUI.h"
#include "game/MsgGame.h"
#include "game/fn_801C1F94.h"

struct MemCardScanEntry_t {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    unsigned int mUnknown12;
    unsigned char mUnknown16;
    char mUnknown17[3];
};

union MemCardScanArg_t {
    int mUnknownValue;
    int *mUnknownPointer;
};

extern "C" {
int UserRecGetCount();
void fn_80186ED8(signed char);
void MemCardFilesSetLoadTarget(int, int);
void MemCardFilesStartLoad();
int PerPollSingleDevice(int a);
unsigned int PerGetNumDevices();
int PerGetDeviceStatus(int a);
unsigned int PerGetDeviceTypeT(int a);
void PerCheckConnectSingle(unsigned char a);
unsigned int fn_801D6CB8(int, int);
void MsgMemCardScanResetList(int, int *);
void MsgMemCardScanRewind();
int MsgMemCardScanNextEntry(int *, int *, int *, int *);
void MsgMemCardScanSelectEntry(int, int);
int MsgMemCardScanConsiderFile(int, int);
}

static MemCardScanEntry_t _MsgMemCardScan_aBest[3];
static int _MsgMemCardScan_iNext = 0;
static int _MsgMemCardScan_iDevice = -1;
static MemCardListCallbacks_t _MsgMemCardScan_Callbacks = {
    MsgMemCardScanResetList, MsgMemCardScanRewind, MsgMemCardScanNextEntry, MsgMemCardScanSelectEntry, MsgMemCardScanConsiderFile
};

extern "C" void MsgMemCardScanOpen()
{
    MsgGameSetMemCardActive(1);
    fn_801D685C("GN7E-69", 0);
    fn_801D65B4(0);
    fn_801D654C(1);
    fn_801D6714(0);
    MemCardUISetCallbacks(&_MsgMemCardScan_Callbacks);
}

extern "C" int MsgMemCardScanCheckDevices()
{
    int stop = 1;
    for (unsigned char i = 0; !stop && i < PerGetNumDevices(); ++i) {
        PerGetDeviceStatus(i);
    }
    return !stop;
}

extern "C" void MsgMemCardScanFindDevice(int *pFound)
{
    int found = 0;
    unsigned int count = PerGetNumDevices();
    for (unsigned int i = 0; i < count; ++i) {
        PerCheckConnectSingle(i);
        if (PerGetDeviceTypeT(i) >> 16) {
            PerPollSingleDevice(i);
            if (PerGetDeviceTypeT(i) & 0x800) {
                _MsgMemCardScan_iDevice = i;
                found = 1;
                break;
            }
        }
    }
    *pFound = found;
}

extern "C" void MsgMemCardScanIgnore()
{
}

extern "C" void MsgMemCardScanIgnoreArg(int *p)
{
}

extern "C" int MsgMemCardScanGetStatus()
{
    return 0;
}

extern "C" void MsgMemCardScanIgnoreFlag(unsigned char value)
{
}

extern "C" void MsgMemCardScanClose()
{
    MsgGameSetMemCardActive(0);
    fn_801D685C("GN7E-69", 0);
    fn_801D6714(-1);
    fn_801D654C(0);
    MemCardUIClearCallbacks();
    for (signed char i = UserRecGetCount() - 1; i >= 0; --i) {
        fn_80186ED8(i);
    }
}

extern "C" void MsgMemCardScanResetList(int value, int *pCount)
{
    *pCount = 9999;
    fn_801C1F94(_MsgMemCardScan_aBest, 0, sizeof(_MsgMemCardScan_aBest));
}

extern "C" void MsgMemCardScanRewind()
{
    _MsgMemCardScan_iNext = 0;
}

extern "C" int MsgMemCardScanNextEntry(int *p0, int *p4, int *p8, int *p12)
{
    unsigned int i;
    for (i = 0; i < 3; ++i) {
        if (i == _MsgMemCardScan_iNext) {
            if (_MsgMemCardScan_aBest[i].mUnknown16) {
                *p0 = _MsgMemCardScan_aBest[i].mUnknown0;
                *p4 = _MsgMemCardScan_aBest[i].mUnknown4;
                *p8 = _MsgMemCardScan_aBest[i].mUnknown8;
                *p12 = 0;
                ++_MsgMemCardScan_iNext;
                break;
            }
            _MsgMemCardScan_iNext = i + 1;
        }
    }
    return i < 3;
}

extern "C" void MsgMemCardScanSelectEntry(int key, int value)
{
    int index = 0;
    if (key == 2) {
        index = _MsgMemCardScan_iNext - 2;
    }
    MemCardFilesSetLoadTarget(key, index);
}

extern "C" int MsgMemCardScanConsiderFile(int key, int value)
{
    unsigned int score = fn_801D6CB8((signed char)value, key);
    int changed = 0;

    if (key == 1) {
        if (!_MsgMemCardScan_aBest[0].mUnknown16 || score > _MsgMemCardScan_aBest[0].mUnknown12) {
            _MsgMemCardScan_aBest[0].mUnknown16 = 1;
            _MsgMemCardScan_aBest[0].mUnknown12 = score;
            _MsgMemCardScan_aBest[0].mUnknown0 = fn_801D671C();
            _MsgMemCardScan_aBest[0].mUnknown4 = key;
            _MsgMemCardScan_aBest[0].mUnknown8 = value;
        }
    } else if (key == 2) {
        int insert = 0;
        for (unsigned int i = 1; i < 3; ++i) {
            if (!_MsgMemCardScan_aBest[i].mUnknown16) {
                insert = 1;
            } else if (score > _MsgMemCardScan_aBest[i].mUnknown12) {
                insert = 1;
                for (unsigned int j = 2; j > i; --j) {
                    _MsgMemCardScan_aBest[j] = _MsgMemCardScan_aBest[j - 1];
                }
            }
            if (insert) {
                _MsgMemCardScan_aBest[i].mUnknown16 = 1;
                _MsgMemCardScan_aBest[i].mUnknown12 = score;
                _MsgMemCardScan_aBest[i].mUnknown0 = fn_801D671C();
                _MsgMemCardScan_aBest[i].mUnknown4 = key;
                _MsgMemCardScan_aBest[i].mUnknown8 = value;
                break;
            }
        }
        changed = 0;
    }
    if (changed) {
        MemCardFilesSetLoadTarget(key, 0);
        MemCardFilesStartLoad();
    }
    return 0;
}

extern "C" int MsgMemCardScanHandleMessage(unsigned int id, MemCardScanArg_t *pParams, int c, int *pResult)
{
    switch (id) {
    case 0x80000001:
        MsgMemCardScanOpen();
        break;
    case 0x80000002:
        *pResult = MsgMemCardScanCheckDevices();
        break;
    case 0x80000003:
        *pResult = MsgMemCardScanGetStatus();
        break;
    case 0x80000004:
        MsgMemCardScanIgnoreFlag(pParams->mUnknownValue);
        break;
    case 0x80000005:
        MsgMemCardScanClose();
        break;
    case 0x80000007:
        MsgMemCardScanFindDevice(pParams->mUnknownPointer);
        break;
    case 0x80000008:
        MsgMemCardScanIgnore();
        break;
    case 0x80000009:
        MsgMemCardScanIgnoreArg(pParams->mUnknownPointer);
        break;
    case 0x80000006:
        *pResult = 0;
        break;
    default:
        return 0;
    }
    return 1;
}
