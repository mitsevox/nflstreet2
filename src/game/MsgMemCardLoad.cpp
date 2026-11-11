/* Memory card load screen: opens the memory card file list for this game
   ("GN7E-69"), names each file (a profile name, or "Options" for the options
   file) and hands the chosen file on to be loaded. */

#include "game/Callees_801D57E0.h"
#include "game/MemCardUI.h"
#include "game/MsgGame.h"
#include "game/TextRecord.h"
#include "game/fn_801C1F94.h"
#include <string.h>

struct MemCardLoadEntry_t {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    char mUnknown12[4];
    unsigned char mUnknown16;
    char mUnknown17[3];
};

union MemCardLoadWord_t {
    int mUnknownValue;
    TextRecord_t *mUnknownPointer;
};

struct MemCardLoadArgs_t {
    MemCardLoadWord_t mUnknown0;
    int mUnknown4;
    TextRecord_t *mUnknown8;
};

extern "C" {
int UserRecGetCount();
void MemCardFilesSetLoadTarget(int, int);
void MsgMemCardLoadRegisterCallbacks();
void MsgMemCardLoadResetList(int, int *);
void MsgMemCardLoadRewind();
int MsgMemCardLoadNextEntry(int *, int *, int *, int *);
void MsgMemCardLoadSelectEntry(int, int);
}

static MemCardLoadEntry_t _MsgMemCardLoad_aEntries[16];
static int _MsgMemCardLoad_iNext = 0;
static MemCardListCallbacks_t _MsgMemCardLoad_Callbacks = {
    MsgMemCardLoadResetList, MsgMemCardLoadRewind, MsgMemCardLoadNextEntry, MsgMemCardLoadSelectEntry, 0
};

extern "C" void MsgMemCardLoadOpen()
{
    MsgGameSetMemCardActive(1);
    fn_801D685C("GN7E-69", 0);
    fn_801D65B4(0);
    fn_801D654C(1);
    fn_801D6714(0);
    MsgMemCardLoadRegisterCallbacks();
}

extern "C" void MsgMemCardLoadClose()
{
    MsgGameSetMemCardActive(0);
    fn_801D685C("GN7E-69", 0);
    fn_801D6714(-1);
    fn_801D654C(0);
    MemCardUIClearCallbacks();
}

extern "C" void MsgMemCardLoadResetList(int value, int *pCount)
{
    *pCount = 16;
    fn_801C1F94(_MsgMemCardLoad_aEntries, 0, 320);
}

extern "C" void MsgMemCardLoadRewind()
{
    _MsgMemCardLoad_iNext = 0;
}

extern "C" int MsgMemCardLoadNextEntry(int *p0, int *p4, int *p8, int *p12)
{
    unsigned int i;
    for (i = 0; i < 16; ++i) {
        if (i == _MsgMemCardLoad_iNext) {
            if (_MsgMemCardLoad_aEntries[i].mUnknown16) {
                *p0 = _MsgMemCardLoad_aEntries[i].mUnknown0;
                *p4 = _MsgMemCardLoad_aEntries[i].mUnknown4;
                *p8 = _MsgMemCardLoad_aEntries[i].mUnknown8;
                *p12 = 0;
                ++_MsgMemCardLoad_iNext;
                break;
            }
            _MsgMemCardLoad_iNext = i + 1;
        }
    }
    return i < 16;
}

extern "C" void MsgMemCardLoadSelectEntry(int key, int value)
{
    MemCardFilesSetLoadTarget(key, (key == 2 || key == 3) ? UserRecGetCount() : 0);
    char first[32];
    char second[32];
    fn_801D6B74((signed char)value, key, first, 32, 0, -1, 0);
    fn_801D6C70((signed char)value, key, second, 32);
    fn_801D67E4(first, second);
    fn_801D6838(value);
}

extern "C" int MsgMemCardLoadGetEntryName(int key, int value, TextRecord_t *p)
{
    if (key == 2 || key == 3) {
        char text[32];
        fn_801D6B74((signed char)value, key, text, 32, 0, -1, 0);
        strcpy(p->mUnknown8, text);
    } else if (fn_801D6DA8(0, 1)) {
        strcpy(p->mUnknown8, "???");
    } else {
        strcpy(p->mUnknown8, "Options");
    }
    return 0;
}

extern "C" int MsgMemCardLoadGetCardText(TextRecord_t *p)
{
    return fn_801D57E0(fn_801D671C(), p->mUnknown8, p->mUnknown4);
}

extern "C" void MsgMemCardLoadRegisterCallbacks()
{
    MemCardUISetCallbacks(&_MsgMemCardLoad_Callbacks);
}

extern "C" int MsgMemCardLoadHandleMessage(unsigned int value, MemCardLoadArgs_t *p)
{
    switch (value) {
    case 0x80000012:
        MsgMemCardLoadOpen();
        break;
    case 0x80000014:
        MsgMemCardLoadGetEntryName(p->mUnknown0.mUnknownValue, p->mUnknown4, p->mUnknown8);
        break;
    case 0x80000015:
        MsgMemCardLoadGetCardText(p->mUnknown0.mUnknownPointer);
        break;
    case 0x80000013:
        MsgMemCardLoadClose();
        break;
    default:
        return 0;
    }
    return 1;
}
