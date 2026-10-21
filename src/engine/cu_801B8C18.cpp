#include "engine/cu_801B8C18.h"
#include "game/Class_801B8D9C.h"
#include <dolphin/os/OSMutex.h>
#include <stddef.h>
#include <string.h>

extern "C" {
extern Allocator *lbl_8037E824;
extern OSMutex lbl_8037E828;
extern int lbl_802F4838;

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
        Link_801B8C18 *link = lbl_8037E820.mHead;
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
        Link_801B8C18 *link = lbl_8037E820.mHead;
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
        Link_801B8C18 *link = lbl_8037E820.mHead;
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
    lbl_8037E820.mHead = 0;
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

Class_8037E820 lbl_8037E820;

extern unsigned short lbl_802F483C;

int fn_801B94CC(Handle_801B8C60 *handle, Node_801B9410 *node);
int fn_801B95FC(Class_801B8D9C *handle, void *params, Object_801B9068 **out);
int fn_801B9724(Object_801B9068 *object);
int fn_801B9884(Object_801B9068 *object, void *params);

int fn_801B91A0(Bank_801B8C18 *bank)
{
    Entry_801B8C60 *entries = (Entry_801B8C60 *)(bank + 1);
    int i;

    bank->mEntriesA = entries;
    bank->mEntriesB = (Entry_801B8DF0 *)(entries + bank->mCountA);
    bank->mEntriesC = (Entry_801B8F2C *)(bank->mEntriesB + bank->mCountB);

    for (i = 0; i < bank->mCountA; i++) {
        bank->mEntriesA[i].mName = (const char *)bank + (int)bank->mEntriesA[i].mName;
        if (++lbl_802F483C & 0x8000)
            lbl_802F483C = 1;
        bank->mEntriesA[i].mParts.mId = lbl_802F483C;
    }
    for (i = 0; i < bank->mCountB; i++) {
        bank->mEntriesB[i].mName = (const char *)bank + (int)bank->mEntriesB[i].mName;
        if (++lbl_802F483C & 0x8000)
            lbl_802F483C = 1;
        bank->mEntriesB[i].mParts.mId = lbl_802F483C;
    }
    for (i = 0; i < bank->mCountC; i++) {
        bank->mEntriesC[i].mName = (const char *)bank + (int)bank->mEntriesC[i].mName;
        if (++lbl_802F483C & 0x8000)
            lbl_802F483C = 1;
        bank->mEntriesC[i].mParts.mId = lbl_802F483C;
    }

    bank->mLink.mNext = lbl_8037E820.mHead;
    bank->mLink.mPrevious = 0;
    if (lbl_8037E820.mHead)
        lbl_8037E820.mHead->mPrevious = &bank->mLink;
    lbl_8037E820.mHead = &bank->mLink;
    return 0;
}

int fn_801B9328(Bank_801B8C18 *bank)
{
    int i;

    for (i = 0; i < bank->mCountA; i++)
        bank->mEntriesA[i].mValue = -1;
    for (i = 0; i < bank->mCountB; i++)
        bank->mEntriesB[i].mValue = -1;
    for (i = 0; i < bank->mCountC; i++)
        bank->mEntriesC[i].mValue = -1;

    if (lbl_8037E820.mHead == &bank->mLink)
        lbl_8037E820.mHead = bank->mLink.mNext;
    if (bank->mLink.mPrevious)
        bank->mLink.mPrevious->mNext = bank->mLink.mNext;
    if (bank->mLink.mNext)
        bank->mLink.mNext->mPrevious = bank->mLink.mPrevious;
    return 0;
}

int fn_801B9410(Handle_801B8C60 *handle, void *params)
{
    int result = fn_801B8D4C(handle);
    if (result < 0)
        return result;
    Node_801B9410 *node = handle->mEntry->mNodes;
    if (!node)
        return -4;
    do {
        node->mCallback(params, node->mContext);
        node = node->mNext;
    } while (node);
    return result;
}

int fn_801B9484(Handle_801B8C60 *handle, Node_801B9410 *node)
{
    fn_801B9148();
    int result = fn_801B94CC(handle, node);
    fn_801B9174();
    return result;
}

int fn_801B94CC(Handle_801B8C60 *handle, Node_801B9410 *node)
{
    int result = fn_801B8D4C(handle);
    if (result < 0)
        return result;
    Entry_801B8C60 *entry = handle->mEntry;
    node->mNext = entry->mNodes;
    node->mPrevious = 0;
    if (entry->mNodes)
        entry->mNodes->mPrevious = node;
    entry->mNodes = node;
    return 0;
}

int fn_801B9530(Handle_801B8C60 *handle, Node_801B9410 *node)
{
    int result = fn_801B8D4C(handle);
    if (result < 0)
        return result;
    Entry_801B8C60 *entry = handle->mEntry;
    if (node == entry->mNodes)
        entry->mNodes = node->mNext;
    if (node->mPrevious)
        node->mPrevious->mNext = node->mNext;
    if (node->mNext)
        node->mNext->mPrevious = node->mPrevious;
    return 0;
}

int fn_801B95AC(Class_801B8D9C *handle, void *params, Object_801B9068 **out)
{
    fn_801B9148();
    int result = fn_801B95FC(handle, params, out);
    fn_801B9174();
    return result;
}

int fn_801B95FC(Class_801B8D9C *handle, void *params, Object_801B9068 **out)
{
    *out = 0;
    int result = fn_801B8EDC(handle);
    if (result < 0)
        return result;
    Object_801B9068 *object = (Object_801B9068 *)lbl_8037E824->Alloc(sizeof(Object_801B9068), AllocParams());
    if (!object)
        return -1;
    object->mCallbacks = 0;
    object->mRefCount = 1;
    object->mReleaseNodes = 0;
    Entry_801B8DF0 *entry = handle->mEntry;
    object->mEntry = entry;
    for (Node_801B95FC *node = entry->mNodes; node; node = node->mNext)
        node->mCallback(object, params, node->mContext);
    fn_801B9068(object, params);
    *out = object;
    return 0;
}

int fn_801B96E4(Object_801B9068 *object)
{
    fn_801B9148();
    int result = fn_801B9724(object);
    fn_801B9174();
    return result;
}

int fn_801B9724(Object_801B9068 *object)
{
    Node_801B9724 *node = object->mReleaseNodes;
    while (node) {
        Node_801B9724 *next = node->mNext;
        node->mCallback(object, node->mContext);
        node = next;
    }
    if (--object->mRefCount == 0)
        lbl_8037E824->Free(object, 0);
    return 0;
}

int fn_801B97B8(Object_801B9068 *object, int *out)
{
    *out = object->mRefCount;
    return 0;
}

int fn_801B97C8(Object_801B9068 *object)
{
    object->mRefCount++;
    return 0;
}

int fn_801B97E0(Object_801B9068 *object)
{
    if (--object->mRefCount == 0)
        lbl_8037E824->Free(object, 0);
    return 0;
}

int fn_801B983C(Object_801B9068 *object, void *params)
{
    fn_801B9148();
    int result = fn_801B9884(object, params);
    fn_801B9174();
    return result;
}

int fn_801B9884(Object_801B9068 *object, void *params)
{
    fn_801B9068(object, params);
    return 0;
}

int fn_801B98A8(Class_801B8D9C *handle, Node_801B95FC *node)
{
    int result = fn_801B8EDC(handle);
    if (result < 0)
        return result;
    Entry_801B8DF0 *entry = handle->mEntry;
    node->mNext = entry->mNodes;
    node->mPrevious = 0;
    if (entry->mNodes)
        entry->mNodes->mPrevious = node;
    entry->mNodes = node;
    return 0;
}

int fn_801B990C(Class_801B8D9C *handle, Node_801B95FC *node)
{
    int result = fn_801B8EDC(handle);
    if (result < 0)
        return result;
    Entry_801B8DF0 *entry = handle->mEntry;
    if (node == entry->mNodes)
        entry->mNodes = node->mNext;
    if (node->mPrevious)
        node->mPrevious->mNext = node->mNext;
    if (node->mNext)
        node->mNext->mPrevious = node->mPrevious;
    return 0;
}

int fn_801B9988(Object_801B9068 *object, Node_801B9724 *node)
{
    node->mNext = object->mReleaseNodes;
    node->mPrevious = 0;
    if (object->mReleaseNodes)
        object->mReleaseNodes->mPrevious = node;
    object->mReleaseNodes = node;
    object->mRefCount++;
    return 0;
}

int fn_801B99C4(Object_801B9068 *object, Node_801B9724 *node)
{
    if (node == object->mReleaseNodes)
        object->mReleaseNodes = node->mNext;
    if (node->mPrevious)
        node->mPrevious->mNext = node->mNext;
    if (node->mNext)
        node->mNext->mPrevious = node->mPrevious;
    if (--object->mRefCount == 0)
        lbl_8037E824->Free(object, 0);
    return 0;
}

int fn_801B9A5C(Object_801B9068 *object, Callback_801B9068 *node)
{
    node->mNext = object->mCallbacks;
    node->mPrevious = 0;
    if (object->mCallbacks)
        object->mCallbacks->mPrevious = node;
    object->mCallbacks = node;
    object->mRefCount++;
    return 0;
}

int fn_801B9A98(Object_801B9068 *object, Callback_801B9068 *node)
{
    if (node == object->mCallbacks)
        object->mCallbacks = node->mNext;
    if (node->mPrevious)
        node->mPrevious->mNext = node->mNext;
    if (node->mNext)
        node->mNext->mPrevious = node->mPrevious;
    if (--object->mRefCount == 0)
        lbl_8037E824->Free(object, 0);
    return 0;
}

int fn_801B9B30(Handle_801B8F2C *handle, int *state)
{
    int result = fn_801B9018(handle);
    if (result >= 0) {
        Entry_801B8F2C *entry = handle->mEntry;
        if (*state == entry->mState)
            return 0;
        entry->mState = *state;
        for (Node_801B9B30 *node = entry->mNodes; node; node = node->mNext)
            node->mCallback(&entry->mState, node->mContext);
    }
    return result;
}

int fn_801B9BB8(Handle_801B8F2C *handle, Node_801B9B30 *node)
{
    int result = fn_801B9018(handle);
    if (result < 0)
        return result;
    Entry_801B8F2C *entry = handle->mEntry;
    node->mNext = entry->mNodes;
    node->mPrevious = 0;
    if (entry->mNodes)
        entry->mNodes->mPrevious = node;
    entry->mNodes = node;
    node->mCallback(&entry->mState, node->mContext);
    return 0;
}

int fn_801B9C30(Handle_801B8F2C *handle, Node_801B9B30 *node)
{
    int result = fn_801B9018(handle);
    if (result < 0)
        return result;
    Entry_801B8F2C *entry = handle->mEntry;
    if (node == entry->mNodes)
        entry->mNodes = node->mNext;
    if (node->mPrevious)
        node->mPrevious->mNext = node->mNext;
    if (node->mNext)
        node->mNext->mPrevious = node->mPrevious;
    return 0;
}

}
