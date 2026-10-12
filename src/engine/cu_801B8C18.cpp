#include "engine/cu_801B8C18.h"
#include "game/Class_801B8D9C.h"
#include <dolphin/os/OSMutex.h>
#include <stddef.h>
#include <string.h>

class Allocator;

struct Link_801B8C18 {
    Link_801B8C18 *mNext;
    Link_801B8C18 *mPrevious;
};

struct Entry_801B8C60 {
    void *mUnknown0;
    const char *mName;
    int mValue;
};

struct Entry_801B8DF0 {
    void *mUnknown0;
    const char *mName;
    int mValue;
};

struct Entry_801B8F2C {
    unsigned char mUnknown0[8];
    const char *mName;
    int mValue;
};

struct Handle_801B8C60 {
    Entry_801B8C60 *mEntry;
    int mValue;
};

struct Handle_801B8F2C {
    Entry_801B8F2C *mEntry;
    int mValue;
};

struct Bank_801B8C18 {
    unsigned char mUnknown0[10];
    unsigned short mCountA;
    unsigned short mCountB;
    unsigned short mCountC;
    short mUnknown10;
    unsigned char mUnknown12[2];
    Entry_801B8C60 *mEntriesA;
    Entry_801B8DF0 *mEntriesB;
    Entry_801B8F2C *mEntriesC;
    Link_801B8C18 mLink;
};

struct Callback_801B9068 {
    Callback_801B9068 *mNext;
    unsigned char mUnknown4[4];
    void (*mCallback)(void *, void *);
    void *mContext;
};

struct Object_801B9068 {
    unsigned char mUnknown0[8];
    Callback_801B9068 *mCallbacks;
};

extern "C" {
extern Link_801B8C18 *lbl_8037E820;
extern Allocator *lbl_8037E824;
extern OSMutex lbl_8037E828;
extern int lbl_802F4838;

int fn_801B9148(void);
int fn_801B9174(void);
int fn_801B8C60(Handle_801B8C60 *out, Struct_803EB878 *desc);
int fn_801B8DF0(Class_801B8D9C *out, Struct_803EB878 *desc);

int fn_801B8C18(Handle_801B8C60 *out, Struct_803EB878 *desc)
{
    fn_801B9148();
    int result = fn_801B8C60(out, desc);
    fn_801B9174();
    return result;
}

int fn_801B8C60(Handle_801B8C60 *out, Struct_803EB878 *desc)
{
    int pass = 0;
    for (;;) {
        Link_801B8C18 *link = lbl_8037E820;
        while (link) {
            Bank_801B8C18 *bank = (Bank_801B8C18 *)((char *)link - offsetof(Bank_801B8C18, mLink));
            Entry_801B8C60 *entries = bank->mEntriesA;
            int count = bank->mCountA;
            if (bank->mUnknown10 == (short)(desc->mHash >> 16) || pass) {
                for (int i = 0; i < count; i++) {
                    Entry_801B8C60 *entry = &entries[i];
                    if ((short)desc->mHash == (short)(entry->mValue >> 16) &&
                        strcmp(desc->mName, entry->mName) == 0) {
                        out->mEntry = entry;
                        out->mValue = entry->mValue;
                        return 0;
                    }
                }
            }
            link = bank->mLink.mNext;
        }
        if (pass)
            break;
        pass = 1;
    }
    return -5;
}

int fn_801B8D4C(Handle_801B8C60 *handle)
{
    if (handle->mValue < 0)
        return handle->mValue;
    if (!handle->mEntry)
        return -6;
    if (handle->mValue != handle->mEntry->mValue) {
        handle->mValue = -3;
        handle->mEntry = 0;
        return -3;
    }
    return 0;
}

}

Class_801B8D9C::Class_801B8D9C()
{
    mValue = -3;
}

extern "C" {

int fn_801B8DA8(Class_801B8D9C *out, Struct_803EB878 *desc)
{
    fn_801B9148();
    int result = fn_801B8DF0(out, desc);
    fn_801B9174();
    return result;
}

int fn_801B8DF0(Class_801B8D9C *out, Struct_803EB878 *desc)
{
    int pass = 0;
    for (;;) {
        Link_801B8C18 *link = lbl_8037E820;
        while (link) {
            Bank_801B8C18 *bank = (Bank_801B8C18 *)((char *)link - offsetof(Bank_801B8C18, mLink));
            Entry_801B8DF0 *entries = bank->mEntriesB;
            int count = bank->mCountB;
            if (bank->mUnknown10 == (short)(desc->mHash >> 16) || pass) {
                for (int i = 0; i < count; i++) {
                    Entry_801B8DF0 *entry = &entries[i];
                    if ((short)desc->mHash == (short)(entry->mValue >> 16) &&
                        strcmp(desc->mName, entry->mName) == 0) {
                        out->mEntry = entry;
                        out->mValue = entry->mValue;
                        return 0;
                    }
                }
            }
            link = bank->mLink.mNext;
        }
        if (pass)
            break;
        pass = 1;
    }
    return -5;
}

int fn_801B8EDC(Class_801B8D9C *handle)
{
    if (handle->mValue < 0)
        return handle->mValue;
    if (!handle->mEntry)
        return -6;
    if (handle->mValue != handle->mEntry->mValue) {
        handle->mValue = -3;
        handle->mEntry = 0;
        return -3;
    }
    return 0;
}

int fn_801B8F2C(Handle_801B8F2C *out, Struct_803EB878 *desc)
{
    int pass = 0;
    for (;;) {
        Link_801B8C18 *link = lbl_8037E820;
        while (link) {
            Bank_801B8C18 *bank = (Bank_801B8C18 *)((char *)link - offsetof(Bank_801B8C18, mLink));
            Entry_801B8F2C *entries = bank->mEntriesC;
            int count = bank->mCountC;
            if (bank->mUnknown10 == (short)(desc->mHash >> 16) || pass) {
                for (int i = 0; i < count; i++) {
                    Entry_801B8F2C *entry = &entries[i];
                    if ((short)desc->mHash == (short)(entry->mValue >> 16) &&
                        strcmp(desc->mName, entry->mName) == 0) {
                        out->mEntry = entry;
                        out->mValue = entry->mValue;
                        return 0;
                    }
                }
            }
            link = bank->mLink.mNext;
        }
        if (pass)
            break;
        pass = 1;
    }
    return -5;
}

int fn_801B9018(Handle_801B8F2C *handle)
{
    if (handle->mValue < 0)
        return handle->mValue;
    if (!handle->mEntry)
        return -6;
    if (handle->mValue != handle->mEntry->mValue) {
        handle->mValue = -3;
        handle->mEntry = 0;
        return -3;
    }
    return 0;
}

void fn_801B9068(Object_801B9068 *object, void *params)
{
    Callback_801B9068 *callback = object->mCallbacks;
    while (callback) {
        callback->mCallback(params, callback->mContext);
        callback = callback->mNext;
    }
}

int fn_801B90BC(Allocator *allocator)
{
    lbl_8037E824 = allocator;
    return 0;
}

int fn_801B90CC(Allocator **out)
{
    *out = lbl_8037E824;
    if (!lbl_8037E824)
        return -6;
    return 0;
}

int fn_801B90F0(void)
{
    OSInitMutex(&lbl_8037E828);
    lbl_8037E820 = 0;
    lbl_802F4838 = 1;
    return 0;
}

int fn_801B9134(void)
{
    lbl_802F4838 = 0;
    return 0;
}

int fn_801B9148(void)
{
    OSLockMutex(&lbl_8037E828);
    return 0;
}

int fn_801B9174(void)
{
    OSUnlockMutex(&lbl_8037E828);
    return 0;
}

}
