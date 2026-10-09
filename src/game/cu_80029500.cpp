#include <stdio.h>
#include <string.h>

#include "game/Callees_801D57E0.h"
#include "game/Callees_8002A138.h"
#include "game/cu_8002ACB4.h"
#include "game/cu_80193CEC.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801EEB44.h"
#include "game/fn_801EF390.h"
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

extern StreamOps_8002ACB4 lbl_802D6C24;
extern char lbl_802EBE50[];

void fn_801D646C(void);
void fn_801D6938(SaveFileDesc *, int);
void fn_801D6924(int (*)(char *, int, Comment_80193CEC *), void (*)(void), void (*)(int, int *, int *), void (*)(int));
void fn_801D5824(int, int);
void fn_801D6904(int, int);
void fn_801D64EC(void);
int fn_801F0C50(void *, int);
int fn_801D8618(int, unsigned int, int);
int fn_801D8658(int, unsigned int, int);
int fn_8022F358(int index);
void fn_8022F698(Request_8002AD64 *, StreamOps_8002ACB4 *);
void fn_8022EB94(int *, StreamOps_8002ACB4 *);
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
int fn_80184B00(int, const char *);
void fn_801F81AC(void);

unsigned int fn_80029838(int type);
int fn_800298E8(int type, int index);
void fn_80029DCC(int type, int index);
int fn_80029FD8(int type, int index);
void fn_8002A260(int type, int index, char *buf, int size);
int fn_8002A2A4(int type, int index);
void fn_8002A478(int *pType, int *pIndex);
}

void *lbl_803EA320 = 0;
int lbl_803EA324 = -1;
int lbl_803EA328 = -1;
int lbl_803EA32C = -1;
int lbl_803EA330 = -1;
int lbl_803EA334 = 0;
unsigned char lbl_803EA338 = 0;

SaveType lbl_802CC780[4] = {
    { 0, 0, 0, 0, "All", "All", 0 },
    { 0x3000, 1, 1, 0, "Options", "Options", 0 },
    { 0x2F400, 2, 2, 0, "UserID", "UserID", 0 },
    { 0x100, 0, 2, 0, "Plyr Export", "Player", 0 },
};

SaveFileDesc lbl_802CC7E0[4] = {
    { 0, 0, "GN7E-69", 0 },
    { 1, 0, "GN7E-69", 0 },
    { 0x10, 0, "GN7E-69", 0 },
    { 0x10, 0, "GN7E-69", 0 },
};

extern "C" {

void fn_80029500(int type, int *pOptional, int *pOut)
{
    fn_80193D48(lbl_803EA320, lbl_802CC780[type].mUnknown4, pOptional, pOut);
}

void fn_80029544(int type)
{
    fn_801F010C(lbl_803EA320, lbl_802CC780[type].mUnknown4);
}

void fn_8002957C(SaveSlot *slot, const char *name)
{
    unsigned int len = strlen(name);
    unsigned int i;

    strcpy(slot->mUnknown10, name);
    for (i = len; i < sizeof(slot->mUnknown10); i++) {
        slot->mUnknown10[i] = 0;
    }
}

int fn_800295E0(int type, const char *name, unsigned int index, unsigned int *pIndex)
{
    char buf[0x20];
    int unused = 1;
    unsigned int i;

    for (i = index; i < lbl_802CC780[type].mMaxSlots; i++) {
        SaveSlot *slot = &lbl_802CC780[type].mpSlots[i];
        if (slot->mInUse) {
            fn_8002A260(type, i, buf, 0x20);
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

void fn_800296B0(void)
{
    unsigned int i;

    lbl_803EA320 = fn_801EEB44(lbl_802EBE50, 0x2C);
    fn_801D646C();
    fn_801D654C(0);
    for (i = 0; i <= 3; i++) {
        lbl_802CC7E0[i].mpUnknown10 = lbl_802CC780[i].mpUnknown10;
        lbl_802CC7E0[i].mUnknown4 = fn_80029838(i);
        lbl_802CC780[i].mNumUsed = 0;
        if (lbl_802CC780[i].mMaxSlots) {
            lbl_802CC780[i].mpSlots = (SaveSlot *)fn_801D2B7C(lbl_802CC780[i].mMaxSlots * sizeof(SaveSlot), 0, 0);
            memset(lbl_802CC780[i].mpSlots, 0, lbl_802CC780[i].mMaxSlots * sizeof(SaveSlot));
        }
    }
    fn_801D6938(lbl_802CC7E0, 4);
    fn_801D6924(fn_80193CEC, fn_80193D44, fn_80029500, fn_80029544);
    fn_801D685C("GN7E-69", 0);
    fn_801D5824(1, 0x8000);
    fn_801D6904(1, 1);
}

void fn_800297D0(void)
{
    int i;

    fn_801D64EC();
    fn_801EEFAC(lbl_803EA320);
    for (i = 0; i < 4; i++) {
        if (lbl_802CC780[i].mpSlots) {
            fn_801D2BD0(lbl_802CC780[i].mpSlots);
            lbl_802CC780[i].mpSlots = 0;
        }
    }
}

unsigned int fn_80029838(int type)
{
    return fn_801D8618(type, lbl_802CC780[type].mUnknown0, fn_801F0C50(lbl_803EA320, lbl_802CC780[type].mUnknown4));
}

int fn_80029890(int type)
{
    return fn_801D8658(type, lbl_802CC780[type].mUnknown0, fn_801F0C50(lbl_803EA320, lbl_802CC780[type].mUnknown4));
}

int fn_800298E8(int type, int index)
{
    Request_8002AD64 request;
    int result = -1;

    request.mUnknown10 = 0;
    request.mTarget = (int)&result;
    switch (type) {
    case 3:
        fn_8022F478(fn_8022F358((signed char)index));
        fn_8002AD64(&request, &lbl_802D6C24);
        break;
    case 2:
        fn_8022F478(fn_8022F358((signed char)index));
        fn_8022F698(&request, &lbl_802D6C24);
        break;
    case 1:
        fn_8022EB94(&result, &lbl_802D6C24);
        break;
    }
    return result;
}

void fn_80029990(int type, int index, int value)
{
    SaveSlot *slot = &lbl_802CC780[type].mpSlots[index];

    if (slot->mInUse) {
        slot->mUnknown0 = fn_801D671C();
        slot->mUnknown4 = fn_801D6844();
        slot->mUnknown8 = value;
        fn_801D6B24(slot->mUnknown10, 0x11);
        fn_801D6B4C(slot->mUnknown21, 0x20);
        fn_801D868C(fn_801D673C(slot->mUnknown0), slot->mUnknown0, slot->mUnknown41, 0x20);
        if (lbl_803EA338) {
            slot->mUnknownF = 0;
        }
        slot->mUnknownE = 0;
    }
}

void fn_80029A40(int type, int index, int value, const char *name)
{
    SaveSlot *slot = &lbl_802CC780[type].mpSlots[index];

    if (slot->mInUse) {
        fn_80029DCC(type, index);
    }
    lbl_802CC780[type].mNumUsed++;
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
    if (lbl_803EA338) {
        slot->mUnknownF = 0;
    }
    slot->mUnknownE = 0;
    fn_8002957C(slot, name);
}

int fn_80029B48(int *arg)
{
    int done;

    switch (fn_801D6850()) {
    case 1:
    case 2:
    case 3:
        lbl_803EA334 = fn_800039E4(lbl_803EA334, &done, arg);
        break;
    default:
        done = fn_801D6620(arg);
        break;
    }
    if (done) {
        lbl_803EA334 = 0;
    }
    return done;
}

void fn_80029BBC(int type, char *buf, int size)
{
    strcpy(buf, lbl_802CC780[type].mpUnknownC);
}

void fn_80029BF4(int type, char *buf, int size)
{
    strcpy(buf, lbl_802CC780[type].mpUnknown10);
}

void fn_80029C2C(int type, int index, int update)
{
    SaveSlot *slot = &lbl_802CC780[type].mpSlots[index];

    if (!slot->mInUse) {
        lbl_802CC780[type].mNumUsed++;
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
        slot->mUnknown8 = fn_800298E8(type, index);
    }
}

void fn_80029CE0(int type, int index)
{
    SaveSlot *slot = &lbl_802CC780[type].mpSlots[index];

    slot->mUnknown8 = fn_800298E8(type, index);
}

void fn_80029D28(int type, int index)
{
    SaveSlot *slot = &lbl_802CC780[type].mpSlots[index];

    slot->mUnknown8 = fn_800298E8(type, index) + 1;
}

int fn_80029D74(int type, int index)
{
    int result = 0;

    if (fn_8002A2A4(type, index) && fn_80029FD8(type, index)) {
        result = 1;
    }
    return result;
}

void fn_80029DCC(int type, int index)
{
    SaveSlot *slot = &lbl_802CC780[type].mpSlots[index];

    if (slot->mInUse) {
        lbl_802CC780[type].mNumUsed--;
        slot->mInUse = 0;
    }
}

void fn_80029E10(int type, int index)
{
    SaveSlot *slot = &lbl_802CC780[type].mpSlots[index];

    slot->mUnknown0 = -1;
    slot->mUnknown4 = -1;
    slot->mUnknown8 = -1;
    slot->mUnknownE = 0;
    strcpy(slot->mUnknown21, "unsaved");
    strcpy(slot->mUnknown41, " ");
}

void fn_80029E6C(int type, int index)
{
    SaveSlot *slot = &lbl_802CC780[type].mpSlots[index];

    slot->mUnknown0 = -1;
}

void fn_80029E90(int dstType, int dstIndex, int srcType, int srcIndex)
{
    SaveSlot *dst = &lbl_802CC780[dstType].mpSlots[dstIndex];
    SaveSlot *src = &lbl_802CC780[srcType].mpSlots[srcIndex];

    if (!dst->mInUse) {
        lbl_802CC780[dstType].mNumUsed++;
    }
    *dst = *src;
}

int fn_80029F38(int type, int index)
{
    SaveSlot *slot = &lbl_802CC780[type].mpSlots[index];
    int changed = 0;

    if (lbl_803EA338) {
        if (slot->mUnknownF == 2) {
            slot->mUnknownF = 0;
            if (slot->mUnknown8 != fn_800298E8(type, index)) {
                slot->mUnknownF = 1;
            }
        }
        if (slot->mUnknownF == 1) {
            changed = 1;
        }
    } else if (slot->mUnknown8 != fn_800298E8(type, index)) {
        changed = 1;
    }
    return changed;
}

int fn_80029FD8(int type, int index)
{
    int changed = 0;
    SaveSlot *slot;
    int t;
    int i;

    if (type == 0) {
        for (t = 1; !changed && t <= 3; t++) {
            for (i = 0; !changed && i < lbl_802CC780[t].mMaxSlots; i++) {
                slot = &lbl_802CC780[t].mpSlots[i];
                if (slot->mInUse) {
                    changed = fn_80029F38(t, i);
                }
            }
        }
    } else if (index == 0xFF) {
        for (i = 0; !changed && i < lbl_802CC780[type].mMaxSlots; i++) {
            slot = &lbl_802CC780[type].mpSlots[i];
            if (slot->mInUse) {
                changed = fn_80029F38(type, i);
            }
        }
    } else {
        changed = fn_80029F38(type, index);
    }
    return changed;
}

int fn_8002A130(int a, int b)
{
    return 0;
}

int fn_8002A138(int type, int index)
{
    return strcmp(lbl_802CC780[type].mpSlots[index].mUnknown21, "unsaved") != 0;
}

int fn_8002A190(int type, int index)
{
    SaveSlot *slot = &lbl_802CC780[type].mpSlots[index];

    return slot->mUnknown0;
}

int fn_8002A1B0(int type, int index)
{
    SaveSlot *slot = &lbl_802CC780[type].mpSlots[index];

    return slot->mUnknown4;
}

void fn_8002A1D4(int type, int index, char *name)
{
    SaveSlot *slot = &lbl_802CC780[type].mpSlots[index];

    slot->mUnknownE = 0;
    slot->mUnknown0 = -1;
    slot->mUnknown4 = -1;
    strcpy(slot->mUnknown41, " ");
    fn_8002957C(slot, name);
}

void fn_8002A238(int type, int index, int a, int b)
{
    SaveSlot *slot = &lbl_802CC780[type].mpSlots[index];

    slot->mUnknown0 = a;
    slot->mUnknown4 = b;
}

void fn_8002A260(int type, int index, char *buf, int size)
{
    strcpy(buf, lbl_802CC780[type].mpSlots[index].mUnknown10);
}

int fn_8002A2A4(int type, int index)
{
    int used = 0;
    int i;

    if (type == 0) {
        used = 1;
    } else if (index == 0xFF) {
        for (i = 0; i < lbl_802CC780[type].mMaxSlots; i++) {
            if (lbl_802CC780[type].mpSlots[i].mInUse) {
                used = 1;
            }
        }
    } else {
        SaveSlot *slot = &lbl_802CC780[type].mpSlots[index];
        used = slot->mInUse;
    }
    return used;
}

void fn_8002A330(int type, int n, int *pType, int *pIndex, int all)
{
    int count = 0;
    int t;
    unsigned int i;

    for (t = 1; t <= 3; t++) {
        if (type == t || type == 0) {
            for (i = 0; i < lbl_802CC780[t].mMaxSlots; i++) {
                SaveSlot *slot = &lbl_802CC780[t].mpSlots[i];
                if (slot->mInUse && slot->mUnknownD && (all || fn_80029FD8(t, i))) {
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

void fn_8002A44C(int a, int b)
{
    lbl_803EA324 = a;
    lbl_803EA328 = b;
    fn_801D6754(a);
}

void fn_8002A478(int *a, int *b)
{
    if (a) {
        *a = lbl_803EA324;
    }
    if (b) {
        *b = lbl_803EA328;
    }
}

void fn_8002A49C(int flag)
{
    char date[0x11];
    SaveComment comment;
    char name[0x80];

    fn_80029BBC(lbl_803EA324, name, 0x80);
    fn_801D6B24(date, 0x11);
    memset(&comment, 0, sizeof(comment));
    strcpy(comment.mTitle, "NFL STREET 2");
    sprintf(comment.mComment, "%s-%s", name, date);
    fn_801D676C(&comment);
    fn_801D6760(fn_80029890(lbl_803EA324));
    lbl_803EA334 = 1;
    if (flag) {
        fn_801D6650(4);
    } else {
        fn_801D6650(5);
    }
}

void fn_8002A574(int a, int b)
{
    lbl_803EA32C = a;
    lbl_803EA330 = b;
    fn_801D6754(a);
}

void fn_8002A5A0(int *a, int *b)
{
    if (a) {
        *a = lbl_803EA32C;
    }
    if (b) {
        *b = lbl_803EA330;
    }
}

void fn_8002A5C4(void)
{
    lbl_803EA334 = 7;
    fn_801D6650(3);
}

void fn_8002A5F0(int type, char *name, int unique)
{
    char buf[0x20];
    int curType;
    int curIndex;
    int maxLen;
    int i;

    if (type == 1) {
        fn_80029BF4(1, name, 0x20);
        sprintf(name, "%s", name);
        return;
    }
    fn_8002A478(&curType, &curIndex);
    fn_8002A260(curType, curIndex, name, 0x20);
    maxLen = 12;
    name[maxLen] = 0;
    if (fn_80184B00(type, name) && (!unique || fn_800295E0(type, name, 0, 0))) {
        return;
    }
    if (strlen(name) > maxLen - 1) {
        name[maxLen - 1] = 0;
    }
    for (i = 1; i <= 12; i++) {
        sprintf(buf, "%s%d", name, i);
        if (fn_80184B00(type, buf) && (!unique || fn_800295E0(type, buf, 0, 0))) {
            break;
        }
    }
    if (!fn_80184B00(type, buf) || (unique && !fn_800295E0(type, buf, 0, 0))) {
        if (strlen(name) > maxLen - 1) {
            name[maxLen - 1] = 0;
        }
        for (i = 13; i <= 99; i++) {
            sprintf(buf, "%s%d", name, i);
            if (fn_80184B00(type, buf) && (!unique || fn_800295E0(type, buf, 0, 0))) {
                break;
            }
        }
    }
    strcpy(name, buf);
}

void fn_8002A804(void)
{
    fn_801F81AC();
}

int fn_8002A824(void)
{
    int total = fn_80029838(1);

    total += fn_80029838(2);
    total += fn_80029838(3);
    return total;
}

int fn_8002A86C(int value, int type, const char *name, unsigned int *pIndex)
{
    unsigned int i = 0;
    int found;
    int result;

    do {
        result = fn_800295E0(type, name, i, pIndex) == 0;
        if (result && value != fn_8002A190(type, *pIndex)) {
            found = 0;
            for (i = *pIndex + 1; i < lbl_802CC780[2].mMaxSlots && !found;) {
                if (lbl_802CC780[type].mpSlots[i].mInUse) {
                    found = 1;
                } else {
                    i++;
                }
            }
            if (!found) {
                result = 0;
                for (i = *pIndex + 1; i < lbl_802CC780[3].mMaxSlots && !found;) {
                    if (lbl_802CC780[type].mpSlots[i].mInUse) {
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

}
