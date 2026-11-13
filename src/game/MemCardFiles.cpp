/* Memory card save files: the table of the game's save types (options, user
   records, exported players) and the files known on the card for each, with
   their names, descriptions and data checksums. It decides which files have
   unsaved changes, picks unique file names and starts card saves and loads for
   the memory card screens. */

#include "engine/cu_80229270.h"
#include <stdio.h>
#include <string.h>

#include "game/Callees_801D57E0.h"
#include "game/Callees_8002A138.h"
#include "game/PlayerSave.h"
#include "game/MemCardCallbacks.h"
#include "game/fn_801D2B7C.h"
#include "game/ResOpenDevice.h"
#include "game/ResLoad.h"
#include "game/fn_8022F478.h"

struct SaveSlot {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    unsigned char mInUse;
    unsigned char mUnknownD;
    unsigned char mUnknownE;
    unsigned char mUnknownF;
    char mUnknown10[0x11];
    char mUnknown21[0x20];
    char mUnknown41[0xF];
};

struct SaveType {
    unsigned int mUnknown0;
    int mUnknown4;
    unsigned char mMaxSlots;
    unsigned char mNumUsed;
    const char *mpUnknownC;
    const char *mpUnknown10;
    SaveSlot *mpSlots;
};

struct SaveFileDesc {
    int mUnknown0;
    int mUnknown4;
    char mGameCode[8];
    const char *mpUnknown10;
};

struct SaveComment {
    char mTitle[0x20];
    char mComment[0x20];
};

extern "C" {

extern SaveStreamOps_t gChecksumCRC32StreamType;
extern char lbl_802EBE50[];

void fn_801D646C(void);
void fn_801D6938(SaveFileDesc *, int);
void fn_801D6924(int (*)(char *, int, MemCardComment *), void (*)(void), void (*)(int, unsigned char **, unsigned int *), void (*)(int));
int fn_801D5824(int, int);
void fn_801D6904(int, int);
void fn_801D64EC(void);
int ResGetSize(void *, int);
int fn_801D8618(int, unsigned int, int);
int fn_801D8658(int, unsigned int, int);
void fn_8022F698(SaveRequest_t *, SaveStreamOps_t *);
int fn_801D6844(void);
void fn_801D6B4C(char *, int);
int fn_801D673C(int);
void fn_801D868C(int, int, char *, int);
void fn_80186ED8(signed char);
int fn_801D6850(void);
int fn_800039E4(int, int *, int *);
int fn_801D6620(int *);
void fn_801D6754(int);
void fn_801D676C(SaveComment *);
void fn_801D6760(int);
int MemCardUIIsNameFree(int, const char *);
void fn_801F81AC(void);

unsigned int MemCardFilesGetFileSize(int type);
int MemCardFilesComputeChecksum(int type, int index);
void MemCardFilesRemoveSlot(int type, int index);
int MemCardFilesIsChanged(int type, int index);
void MemCardFilesGetSlotName(int type, int index, char *buf, int size);
int MemCardFilesIsUsed(int type, int index);
void MemCardFilesGetSaveTarget(int *pType, int *pIndex);
}

void *_MemCardFiles_pResDevice = 0;
int _MemCardFiles_iSaveType = -1;
int _MemCardFiles_iSaveIndex = -1;
int _MemCardFiles_iLoadType = -1;
int _MemCardFiles_iLoadIndex = -1;
int _MemCardFiles_iOperation = 0;
unsigned char _MemCardFiles_bUseSlotState = 0;

SaveType _MemCardFiles_aTypes[4] = {
    { 0, 0, 0, 0, "All", "All", 0 },
    { 0x3000, 1, 1, 0, "Options", "Options", 0 },
    { 0x2F400, 2, 2, 0, "UserID", "UserID", 0 },
    { 0x100, 0, 2, 0, "Plyr Export", "Player", 0 },
};

SaveFileDesc _MemCardFiles_aFileDescs[4] = {
    { 0, 0, "GN7E-69", 0 },
    { 1, 0, "GN7E-69", 0 },
    { 0x10, 0, "GN7E-69", 0 },
    { 0x10, 0, "GN7E-69", 0 },
};

extern "C" {

void MemCardFilesGetIcon(int type, unsigned char **pOptional, unsigned int *pOut)
{
    MemCardGetIcon(_MemCardFiles_pResDevice, _MemCardFiles_aTypes[type].mUnknown4, pOptional, pOut);
}

void MemCardFilesFreeIcon(int type)
{
    ResUnLoad(_MemCardFiles_pResDevice, _MemCardFiles_aTypes[type].mUnknown4);
}

void MemCardFilesSetSlotName(SaveSlot *slot, const char *name)
{
    unsigned int len = strlen(name);
    unsigned int i;

    strcpy(slot->mUnknown10, name);
    for (i = len; i < sizeof(slot->mUnknown10); i++) {
        slot->mUnknown10[i] = 0;
    }
}

int MemCardFilesFindName(int type, const char *name, unsigned int index, unsigned int *pIndex)
{
    char buf[0x20];
    int unused = 1;
    unsigned int i;

    for (i = index; i < _MemCardFiles_aTypes[type].mMaxSlots; i++) {
        SaveSlot *slot = &_MemCardFiles_aTypes[type].mpSlots[i];
        if (slot->mInUse) {
            MemCardFilesGetSlotName(type, i, buf, 0x20);
            if (strcmp(name, buf) == 0) {
                unused = 0;
                break;
            }
        }
    }
    if (pIndex) {
        *pIndex = i;
    }
    return unused;
}

void MemCardFilesInit(void)
{
    unsigned int i;

    _MemCardFiles_pResDevice = ResOpenDevice(lbl_802EBE50, 0x2C);
    fn_801D646C();
    fn_801D654C(0);
    for (i = 0; i <= 3; i++) {
        _MemCardFiles_aFileDescs[i].mpUnknown10 = _MemCardFiles_aTypes[i].mpUnknown10;
        _MemCardFiles_aFileDescs[i].mUnknown4 = MemCardFilesGetFileSize(i);
        _MemCardFiles_aTypes[i].mNumUsed = 0;
        if (_MemCardFiles_aTypes[i].mMaxSlots) {
            _MemCardFiles_aTypes[i].mpSlots = (SaveSlot *)fn_801D2B7C(_MemCardFiles_aTypes[i].mMaxSlots * sizeof(SaveSlot), 0, 0);
            memset(_MemCardFiles_aTypes[i].mpSlots, 0, _MemCardFiles_aTypes[i].mMaxSlots * sizeof(SaveSlot));
        }
    }
    fn_801D6938(_MemCardFiles_aFileDescs, 4);
    fn_801D6924(MemCardGetNameFromComment, MemCardNullCallback, MemCardFilesGetIcon, MemCardFilesFreeIcon);
    fn_801D685C("GN7E-69", 0);
    fn_801D5824(1, 0x8000);
    fn_801D6904(1, 1);
}

void MemCardFilesShutdown(void)
{
    int i;

    fn_801D64EC();
    ResClose(_MemCardFiles_pResDevice);
    for (i = 0; i < 4; i++) {
        if (_MemCardFiles_aTypes[i].mpSlots) {
            fn_801D2BD0(_MemCardFiles_aTypes[i].mpSlots);
            _MemCardFiles_aTypes[i].mpSlots = 0;
        }
    }
}

unsigned int MemCardFilesGetFileSize(int type)
{
    return fn_801D8618(type, _MemCardFiles_aTypes[type].mUnknown0, ResGetSize(_MemCardFiles_pResDevice, _MemCardFiles_aTypes[type].mUnknown4));
}

int MemCardFilesGetDataSize(int type)
{
    return fn_801D8658(type, _MemCardFiles_aTypes[type].mUnknown0, ResGetSize(_MemCardFiles_pResDevice, _MemCardFiles_aTypes[type].mUnknown4));
}

int MemCardFilesComputeChecksum(int type, int index)
{
    SaveRequest_t request;
    int result = -1;

    request.mUnknown10 = 0;
    request.mTarget = (int)&result;
    switch (type) {
    case 3:
        fn_8022F478(fn_8022F358((signed char)index));
        PlayerSaveOnSave(&request, &gChecksumCRC32StreamType);
        break;
    case 2:
        fn_8022F478(fn_8022F358((signed char)index));
        fn_8022F698(&request, &gChecksumCRC32StreamType);
        break;
    case 1:
        fn_8022EB94(&result, &gChecksumCRC32StreamType);
        break;
    }
    return result;
}

void MemCardFilesUpdateSlot(int type, int index, int value)
{
    SaveSlot *slot = &_MemCardFiles_aTypes[type].mpSlots[index];

    if (slot->mInUse) {
        slot->mUnknown0 = fn_801D671C();
        slot->mUnknown4 = fn_801D6844();
        slot->mUnknown8 = value;
        fn_801D6B24(slot->mUnknown10, 0x11);
        fn_801D6B4C(slot->mUnknown21, 0x20);
        fn_801D868C(fn_801D673C(slot->mUnknown0), slot->mUnknown0, slot->mUnknown41, 0x20);
        if (_MemCardFiles_bUseSlotState) {
            slot->mUnknownF = 0;
        }
        slot->mUnknownE = 0;
    }
}

void MemCardFilesAddSlot(int type, int index, int value, const char *name)
{
    SaveSlot *slot = &_MemCardFiles_aTypes[type].mpSlots[index];

    if (slot->mInUse) {
        MemCardFilesRemoveSlot(type, index);
    }
    _MemCardFiles_aTypes[type].mNumUsed++;
    slot->mInUse = 1;
    slot->mUnknownD = 1;
    if (type == 2 || type == 3) {
        fn_80186ED8(index);
    }
    slot->mUnknown0 = fn_801D671C();
    slot->mUnknown4 = fn_801D6844();
    fn_801D6B74((signed char)slot->mUnknown4, type, slot->mUnknown21, 0x20, 0, 0, 0);
    fn_801D868C(fn_801D673C(slot->mUnknown0), slot->mUnknown0, slot->mUnknown41, 0x20);
    slot->mUnknown8 = value;
    if (_MemCardFiles_bUseSlotState) {
        slot->mUnknownF = 0;
    }
    slot->mUnknownE = 0;
    MemCardFilesSetSlotName(slot, name);
}

int MemCardFilesPollOperation(int *arg)
{
    int done;

    switch (fn_801D6850()) {
    case 1:
    case 2:
    case 3:
        _MemCardFiles_iOperation = fn_800039E4(_MemCardFiles_iOperation, &done, arg);
        break;
    default:
        done = fn_801D6620(arg);
        break;
    }
    if (done) {
        _MemCardFiles_iOperation = 0;
    }
    return done;
}

void MemCardFilesGetTypeName(int type, char *buf, int size)
{
    strcpy(buf, _MemCardFiles_aTypes[type].mpUnknownC);
}

void MemCardFilesGetDefaultName(int type, char *buf, int size)
{
    strcpy(buf, _MemCardFiles_aTypes[type].mpUnknown10);
}

void MemCardFilesResetSlot(int type, int index, int update)
{
    SaveSlot *slot = &_MemCardFiles_aTypes[type].mpSlots[index];

    if (!slot->mInUse) {
        _MemCardFiles_aTypes[type].mNumUsed++;
        slot->mInUse = 1;
        slot->mUnknownD = 1;
    }
    slot->mUnknown0 = -1;
    slot->mUnknown4 = -1;
    slot->mUnknown8 = -1;
    strcpy(slot->mUnknown10, " ");
    strcpy(slot->mUnknown21, "unsaved");
    strcpy(slot->mUnknown41, " ");
    if (update) {
        slot->mUnknown8 = MemCardFilesComputeChecksum(type, index);
    }
}

void MemCardFilesStoreChecksum(int type, int index)
{
    SaveSlot *slot = &_MemCardFiles_aTypes[type].mpSlots[index];

    slot->mUnknown8 = MemCardFilesComputeChecksum(type, index);
}

void MemCardFilesInvalidateChecksum(int type, int index)
{
    SaveSlot *slot = &_MemCardFiles_aTypes[type].mpSlots[index];

    slot->mUnknown8 = MemCardFilesComputeChecksum(type, index) + 1;
}

int MemCardFilesNeedsSave(int type, int index)
{
    int result = 0;

    if (MemCardFilesIsUsed(type, index) && MemCardFilesIsChanged(type, index)) {
        result = 1;
    }
    return result;
}

void MemCardFilesRemoveSlot(int type, int index)
{
    SaveSlot *slot = &_MemCardFiles_aTypes[type].mpSlots[index];

    if (slot->mInUse) {
        _MemCardFiles_aTypes[type].mNumUsed--;
        slot->mInUse = 0;
    }
}

void MemCardFilesClearSlotInfo(int type, int index)
{
    SaveSlot *slot = &_MemCardFiles_aTypes[type].mpSlots[index];

    slot->mUnknown0 = -1;
    slot->mUnknown4 = -1;
    slot->mUnknown8 = -1;
    slot->mUnknownE = 0;
    strcpy(slot->mUnknown21, "unsaved");
    strcpy(slot->mUnknown41, " ");
}

void MemCardFilesClearSlotPort(int type, int index)
{
    SaveSlot *slot = &_MemCardFiles_aTypes[type].mpSlots[index];

    slot->mUnknown0 = -1;
}

void MemCardFilesCopySlot(int dstType, int dstIndex, int srcType, int srcIndex)
{
    SaveSlot *dst = &_MemCardFiles_aTypes[dstType].mpSlots[dstIndex];
    SaveSlot *src = &_MemCardFiles_aTypes[srcType].mpSlots[srcIndex];

    if (!dst->mInUse) {
        _MemCardFiles_aTypes[dstType].mNumUsed++;
    }
    *dst = *src;
}

int MemCardFilesIsSlotChanged(int type, int index)
{
    SaveSlot *slot = &_MemCardFiles_aTypes[type].mpSlots[index];
    int changed = 0;

    if (_MemCardFiles_bUseSlotState) {
        if (slot->mUnknownF == 2) {
            slot->mUnknownF = 0;
            if (slot->mUnknown8 != MemCardFilesComputeChecksum(type, index)) {
                slot->mUnknownF = 1;
            }
        }
        if (slot->mUnknownF == 1) {
            changed = 1;
        }
    } else if (slot->mUnknown8 != MemCardFilesComputeChecksum(type, index)) {
        changed = 1;
    }
    return changed;
}

int MemCardFilesIsChanged(int type, int index)
{
    int changed = 0;
    SaveSlot *slot;
    int t;
    int i;

    if (type == 0) {
        for (t = 1; !changed && t <= 3; t++) {
            for (i = 0; !changed && i < _MemCardFiles_aTypes[t].mMaxSlots; i++) {
                slot = &_MemCardFiles_aTypes[t].mpSlots[i];
                if (slot->mInUse) {
                    changed = MemCardFilesIsSlotChanged(t, i);
                }
            }
        }
    } else if (index == 0xFF) {
        for (i = 0; !changed && i < _MemCardFiles_aTypes[type].mMaxSlots; i++) {
            slot = &_MemCardFiles_aTypes[type].mpSlots[i];
            if (slot->mInUse) {
                changed = MemCardFilesIsSlotChanged(type, i);
            }
        }
    } else {
        changed = MemCardFilesIsSlotChanged(type, index);
    }
    return changed;
}

int MemCardFilesQuerySlot(int a, int b)
{
    return 0;
}

int MemCardFilesIsSlotSaved(int type, int index)
{
    return strcmp(_MemCardFiles_aTypes[type].mpSlots[index].mUnknown21, "unsaved") != 0;
}

int MemCardFilesGetSlotPort(int type, int index)
{
    SaveSlot *slot = &_MemCardFiles_aTypes[type].mpSlots[index];

    return slot->mUnknown0;
}

int MemCardFilesGetSlotFileNumber(int type, int index)
{
    SaveSlot *slot = &_MemCardFiles_aTypes[type].mpSlots[index];

    return slot->mUnknown4;
}

void MemCardFilesRenameSlot(int type, int index, char *name)
{
    SaveSlot *slot = &_MemCardFiles_aTypes[type].mpSlots[index];

    slot->mUnknownE = 0;
    slot->mUnknown0 = -1;
    slot->mUnknown4 = -1;
    strcpy(slot->mUnknown41, " ");
    MemCardFilesSetSlotName(slot, name);
}

void MemCardFilesSetSlotLocation(int type, int index, int a, int b)
{
    SaveSlot *slot = &_MemCardFiles_aTypes[type].mpSlots[index];

    slot->mUnknown0 = a;
    slot->mUnknown4 = b;
}

void MemCardFilesGetSlotName(int type, int index, char *buf, int size)
{
    strcpy(buf, _MemCardFiles_aTypes[type].mpSlots[index].mUnknown10);
}

int MemCardFilesIsUsed(int type, int index)
{
    int used = 0;
    int i;

    if (type == 0) {
        used = 1;
    } else if (index == 0xFF) {
        for (i = 0; i < _MemCardFiles_aTypes[type].mMaxSlots; i++) {
            if (_MemCardFiles_aTypes[type].mpSlots[i].mInUse) {
                used = 1;
            }
        }
    } else {
        SaveSlot *slot = &_MemCardFiles_aTypes[type].mpSlots[index];
        used = slot->mInUse;
    }
    return used;
}

void MemCardFilesGetListedSlot(int type, int n, int *pType, int *pIndex, int all)
{
    int count = 0;
    int t;
    unsigned int i;

    for (t = 1; t <= 3; t++) {
        if (type == t || type == 0) {
            for (i = 0; i < _MemCardFiles_aTypes[t].mMaxSlots; i++) {
                SaveSlot *slot = &_MemCardFiles_aTypes[t].mpSlots[i];
                if (slot->mInUse && slot->mUnknownD && (all || MemCardFilesIsChanged(t, i))) {
                    if (count == n) {
                        *pType = t;
                        *pIndex = i;
                        return;
                    }
                    count++;
                }
            }
        }
    }
}

void MemCardFilesSetSaveTarget(int a, int b)
{
    _MemCardFiles_iSaveType = a;
    _MemCardFiles_iSaveIndex = b;
    fn_801D6754(a);
}

void MemCardFilesGetSaveTarget(int *a, int *b)
{
    if (a) {
        *a = _MemCardFiles_iSaveType;
    }
    if (b) {
        *b = _MemCardFiles_iSaveIndex;
    }
}

void MemCardFilesStartSave(int flag)
{
    char date[0x11];
    SaveComment comment;
    char name[0x80];

    MemCardFilesGetTypeName(_MemCardFiles_iSaveType, name, 0x80);
    fn_801D6B24(date, 0x11);
    memset(&comment, 0, sizeof(comment));
    strcpy(comment.mTitle, "NFL STREET 2");
    sprintf(comment.mComment, "%s-%s", name, date);
    fn_801D676C(&comment);
    fn_801D6760(MemCardFilesGetDataSize(_MemCardFiles_iSaveType));
    _MemCardFiles_iOperation = 1;
    if (flag) {
        fn_801D6650(4);
    } else {
        fn_801D6650(5);
    }
}

void MemCardFilesSetLoadTarget(int a, int b)
{
    _MemCardFiles_iLoadType = a;
    _MemCardFiles_iLoadIndex = b;
    fn_801D6754(a);
}

void MemCardFilesGetLoadTarget(int *a, int *b)
{
    if (a) {
        *a = _MemCardFiles_iLoadType;
    }
    if (b) {
        *b = _MemCardFiles_iLoadIndex;
    }
}

void MemCardFilesStartLoad(void)
{
    _MemCardFiles_iOperation = 7;
    fn_801D6650(3);
}

void MemCardFilesMakeName(int type, char *name, int unique)
{
    char buf[0x20];
    int curType;
    int curIndex;
    int maxLen;
    int i;

    if (type == 1) {
        MemCardFilesGetDefaultName(1, name, 0x20);
        sprintf(name, "%s", name);
        return;
    }
    MemCardFilesGetSaveTarget(&curType, &curIndex);
    MemCardFilesGetSlotName(curType, curIndex, name, 0x20);
    maxLen = 12;
    name[maxLen] = 0;
    if (MemCardUIIsNameFree(type, name) && (!unique || MemCardFilesFindName(type, name, 0, 0))) {
        return;
    }
    if (strlen(name) > maxLen - 1) {
        name[maxLen - 1] = 0;
    }
    for (i = 1; i <= 12; i++) {
        sprintf(buf, "%s%d", name, i);
        if (MemCardUIIsNameFree(type, buf) && (!unique || MemCardFilesFindName(type, buf, 0, 0))) {
            break;
        }
    }
    if (!MemCardUIIsNameFree(type, buf) || (unique && !MemCardFilesFindName(type, buf, 0, 0))) {
        if (strlen(name) > maxLen - 1) {
            name[maxLen - 1] = 0;
        }
        for (i = 13; i <= 99; i++) {
            sprintf(buf, "%s%d", name, i);
            if (MemCardUIIsNameFree(type, buf) && (!unique || MemCardFilesFindName(type, buf, 0, 0))) {
                break;
            }
        }
    }
    strcpy(name, buf);
}

void MemCardFilesIdle(void)
{
    fn_801F81AC();
}

int MemCardFilesGetTotalSize(void)
{
    int total = MemCardFilesGetFileSize(1);

    total += MemCardFilesGetFileSize(2);
    total += MemCardFilesGetFileSize(3);
    return total;
}

#if defined(DECOMP_COMPARE)
int MemCardFilesFindNameOnPort(int value, int type, const char *name, unsigned int *pIndex)
{
    unsigned int i = 0;
    int found;
    int result;

    do {
        result = MemCardFilesFindName(type, name, i, pIndex) == 0;
        if (result && value != MemCardFilesGetSlotPort(type, *pIndex)) {
            found = 0;
            for (i = *pIndex + 1; i < _MemCardFiles_aTypes[2].mMaxSlots && !found;) {
                if (_MemCardFiles_aTypes[type].mpSlots[i].mInUse) {
                    found = 1;
                } else {
                    i++;
                }
            }
            if (!found) {
                result = 0;
                for (i = *pIndex + 1; i < _MemCardFiles_aTypes[3].mMaxSlots && !found;) {
                    if (_MemCardFiles_aTypes[type].mpSlots[i].mInUse) {
                        found = 1;
                    } else {
                        i++;
                    }
                }
            }
        } else {
            found = 0;
        }
    } while (found);
    return result;
}
#endif

}
