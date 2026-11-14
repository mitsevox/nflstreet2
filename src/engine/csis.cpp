/* CSIS registry of the sound libraries. Loaded sound bank images subscribe
   their function, class and global-variable tables here; handles find entries
   by interface name and hash; classes create reference-counted instances that
   notify constructor, member-data and destructor clients; global variables
   broadcast their new value to their clients. */

#include "engine/csis.h"
#include <stddef.h>
#include <string.h>

namespace Csis {

int gIsInited = 0;
static unsigned short gUniqueKeyId = 0;
SystemList gSystems;
Allocator *gpAllocator;
OSMutex gMutexHandle;

int FunctionHandle::Set(const InterfaceId *id)
{
    System::Lock();
    int result = SetFast(id);
    System::Unlock();
    return result;
}

int FunctionHandle::SetFast(const InterfaceId *id)
{
    int pass = 0;
// FAKEMATCH: goto instead of a loop, so the head address is reloaded on every pass as in the target
retry:
    SystemLink *link = gSystems.mHead;
    while (link) {
        SystemHeader *system = (SystemHeader *)((char *)link - offsetof(SystemHeader, mLink));
        FunctionEntry *entries = system->mEntriesA;
        int count = system->mCountA;
        if (system->mUnknown10 == (short)(id->mHash >> 16) || pass) {
            for (int i = 0; i < count; i++) {
                if ((short)id->mHash == (short)(entries[i].mValue >> 16) &&
                    strcmp(id->mName, entries[i].mName) == 0) {
                    mEntry = &entries[i];
                    mValue = entries[i].mValue;
                    return 0;
                }
            }
        }
        link = system->mLink.mNext;
    }
    if (!pass) {
        pass = 1;
        goto retry;
    }
    return -5;
}

int FunctionHandle::Valid()
{
    if (mValue < 0)
        return mValue;
    if (!mEntry)
        return -6;
    if (mValue == mEntry->mValue)
        return 0;
    mValue = -3;
    mEntry = 0;
    return -3;
}

ClassHandle::ClassHandle()
{
    mValue = -3;
}

int ClassHandle::Set(const InterfaceId *id)
{
    System::Lock();
    int result = SetFast(id);
    System::Unlock();
    return result;
}

int ClassHandle::SetFast(const InterfaceId *id)
{
    int pass = 0;
// FAKEMATCH: goto instead of a loop, so the head address is reloaded on every pass as in the target
retry:
    SystemLink *link = gSystems.mHead;
    while (link) {
        SystemHeader *system = (SystemHeader *)((char *)link - offsetof(SystemHeader, mLink));
        ClassEntry *entries = system->mEntriesB;
        int count = system->mCountB;
        if (system->mUnknown10 == (short)(id->mHash >> 16) || pass) {
            for (int i = 0; i < count; i++) {
                if ((short)id->mHash == (short)(entries[i].mValue >> 16) &&
                    strcmp(id->mName, entries[i].mName) == 0) {
                    mEntry = &entries[i];
                    mValue = entries[i].mValue;
                    return 0;
                }
            }
        }
        link = system->mLink.mNext;
    }
    if (!pass) {
        pass = 1;
        goto retry;
    }
    return -5;
}

int ClassHandle::Valid()
{
    if (mValue < 0)
        return mValue;
    if (!mEntry)
        return -6;
    if (mValue == mEntry->mValue)
        return 0;
    mValue = -3;
    mEntry = 0;
    return -3;
}

int GlobalVariableHandle::SetFast(const InterfaceId *id)
{
    int pass = 0;
// FAKEMATCH: goto instead of a loop, so the head address is reloaded on every pass as in the target
retry:
    SystemLink *link = gSystems.mHead;
    while (link) {
        SystemHeader *system = (SystemHeader *)((char *)link - offsetof(SystemHeader, mLink));
        GlobalVariableEntry *entries = system->mEntriesC;
        int count = system->mCountC;
        if (system->mUnknown10 == (short)(id->mHash >> 16) || pass) {
            for (int i = 0; i < count; i++) {
                if ((short)id->mHash == (short)(entries[i].mValue >> 16) &&
                    strcmp(id->mName, entries[i].mName) == 0) {
                    mEntry = &entries[i];
                    mValue = entries[i].mValue;
                    return 0;
                }
            }
        }
        link = system->mLink.mNext;
    }
    if (!pass) {
        pass = 1;
        goto retry;
    }
    return -5;
}

int GlobalVariableHandle::Valid()
{
    if (mValue < 0)
        return mValue;
    if (!mEntry)
        return -6;
    if (mValue == mEntry->mValue)
        return 0;
    mValue = -3;
    mEntry = 0;
    return -3;
}

void ClassData::SendParameters(Parameter *params)
{
    FunctionClient *client = mCallbacks;
    while (client) {
        client->mCallback(params, client->mContext);
        client = client->mNext;
    }
}

int System::SetAllocator(Allocator *allocator)
{
    gpAllocator = allocator;
    return 0;
}

int System::GetAllocator(Allocator **out)
{
    *out = gpAllocator;
    if (!gpAllocator)
        return -6;
    return 0;
}

int System::Init()
{
    OSInitMutex(&gMutexHandle);
    gSystems.mHead = 0;
    gIsInited = 1;
    return 0;
}

int System::Restore()
{
    gIsInited = 0;
    return 0;
}

int System::Lock()
{
    OSLockMutex(&gMutexHandle);
    return 0;
}

int System::Unlock()
{
    OSUnlockMutex(&gMutexHandle);
    return 0;
}

int System::Subscribe(void *image)
{
    SystemHeader *system = (SystemHeader *)image;
    FunctionEntry *entries = (FunctionEntry *)(system + 1);
    int i;

    system->mEntriesA = entries;
    system->mEntriesB = (ClassEntry *)(entries + system->mCountA);
    system->mEntriesC = (GlobalVariableEntry *)(system->mEntriesB + system->mCountB);

    for (i = 0; i < system->mCountA; i++) {
        system->mEntriesA[i].mName += (int)system;
        gUniqueKeyId++;
        if (gUniqueKeyId > 0x7FFF)
            gUniqueKeyId = 1;
        system->mEntriesA[i].mParts.mId = gUniqueKeyId;
    }
    for (i = 0; i < system->mCountB; i++) {
        system->mEntriesB[i].mName += (int)system;
        gUniqueKeyId++;
        if (gUniqueKeyId > 0x7FFF)
            gUniqueKeyId = 1;
        system->mEntriesB[i].mParts.mId = gUniqueKeyId;
    }
    for (i = 0; i < system->mCountC; i++) {
        system->mEntriesC[i].mName += (int)system;
        gUniqueKeyId++;
        if (gUniqueKeyId > 0x7FFF)
            gUniqueKeyId = 1;
        system->mEntriesC[i].mParts.mId = gUniqueKeyId;
    }

    SystemLink *link = &system->mLink;
    link->mNext = gSystems.mHead;
    link->mPrevious = 0;
    if (gSystems.mHead)
        gSystems.mHead->mPrevious = link;
    gSystems.mHead = link;
    return 0;
}

int System::Unsubscribe(void *image)
{
    SystemHeader *system = (SystemHeader *)image;
    int i;

    for (i = 0; i < system->mCountA; i++)
        system->mEntriesA[i].mValue = -1;
    for (i = 0; i < system->mCountB; i++)
        system->mEntriesB[i].mValue = -1;
    for (i = 0; i < system->mCountC; i++)
        system->mEntriesC[i].mValue = -1;

    SystemLink *link = &system->mLink;
    if (link == gSystems.mHead)
        gSystems.mHead = link->mNext;
    if (link->mPrevious)
        link->mPrevious->mNext = link->mNext;
    if (link->mNext)
        link->mNext->mPrevious = link->mPrevious;
    return 0;
}

int Function::CallFast(FunctionHandle *handle, void *params)
{
    int result = handle->Valid();
    if (result < 0)
        return result;
    FunctionClient *client = handle->mEntry->mNodes;
    if (!client)
        return -4;
    do {
        client->mCallback((Parameter *)params, client->mContext);
        client = client->mNext;
    } while (client);
    return result;
}

int Function::Subscribe(FunctionHandle *handle, FunctionClient *client)
{
    System::Lock();
    int result = SubscribeFast(handle, client);
    System::Unlock();
    return result;
}

int Function::SubscribeFast(FunctionHandle *handle, FunctionClient *client)
{
    int result = handle->Valid();
    if (result < 0)
        return result;
    FunctionEntry *entry = handle->mEntry;
    client->mNext = entry->mNodes;
    client->mPrevious = 0;
    if (entry->mNodes)
        entry->mNodes->mPrevious = client;
    entry->mNodes = client;
    return 0;
}

int Function::UnsubscribeFast(FunctionHandle *handle, FunctionClient *client)
{
    int result = handle->Valid();
    if (result < 0)
        return result;
    FunctionEntry *entry = handle->mEntry;
    if (client == entry->mNodes)
        entry->mNodes = client->mNext;
    if (client->mPrevious)
        client->mPrevious->mNext = client->mNext;
    if (client->mNext)
        client->mNext->mPrevious = client->mPrevious;
    return 0;
}

int Class::CreateInstance(ClassHandle *handle, void *params, Class **out)
{
    System::Lock();
    int result = CreateInstanceFast(handle, params, out);
    System::Unlock();
    return result;
}

int Class::CreateInstanceFast(ClassHandle *handle, void *params, Class **out)
{
    *out = 0;
    int result = handle->Valid();
    if (result < 0)
        return result;
    Class *object = (Class *)gpAllocator->Alloc(sizeof(Class), AllocParams());
    if (!object)
        return -1;
    object->mCallbacks = 0;
    object->mRefCount = 1;
    object->mReleaseNodes = 0;
    ClassEntry *entry = handle->mEntry;
    object->mEntry = entry;
    for (ClassConstructorClient *client = entry->mNodes; client; client = client->mNext)
        client->mCallback(object, (Parameter *)params, client->mContext);
    object->SendParameters((Parameter *)params);
    *out = object;
    return 0;
}

int Class::Release()
{
    System::Lock();
    int result = ReleaseFast();
    System::Unlock();
    return result;
}

int Class::ReleaseFast()
{
    ClassDestructorClient *client = mReleaseNodes;
    while (client) {
        ClassDestructorClient *next = client->mNext;
        client->mCallback(this, client->mContext);
        client = next;
    }
    if (--mRefCount == 0)
        gpAllocator->Free(this, 0);
    return 0;
}

int Class::GetRefCount(int *out)
{
    *out = mRefCount;
    return 0;
}

int Class::AddRef()
{
    mRefCount++;
    return 0;
}

int Class::DecRef()
{
    if (--mRefCount == 0)
        gpAllocator->Free(this, 0);
    return 0;
}

int Class::SetMemberData(void *params)
{
    System::Lock();
    int result = SetMemberDataFast(params);
    System::Unlock();
    return result;
}

int Class::SetMemberDataFast(void *params)
{
    SendParameters((Parameter *)params);
    return 0;
}

int Class::SubscribeConstructorFast(ClassHandle *handle, ClassConstructorClient *client)
{
    int result = handle->Valid();
    if (result < 0)
        return result;
    ClassEntry *entry = handle->mEntry;
    client->mNext = entry->mNodes;
    client->mPrevious = 0;
    if (entry->mNodes)
        entry->mNodes->mPrevious = client;
    entry->mNodes = client;
    return 0;
}

int Class::UnsubscribeConstructorFast(ClassHandle *handle, ClassConstructorClient *client)
{
    int result = handle->Valid();
    if (result < 0)
        return result;
    ClassEntry *entry = handle->mEntry;
    if (client == entry->mNodes)
        entry->mNodes = client->mNext;
    if (client->mPrevious)
        client->mPrevious->mNext = client->mNext;
    if (client->mNext)
        client->mNext->mPrevious = client->mPrevious;
    return 0;
}

int Class::SubscribeDestructorFast(ClassDestructorClient *client)
{
    client->mNext = mReleaseNodes;
    client->mPrevious = 0;
    if (mReleaseNodes)
        mReleaseNodes->mPrevious = client;
    mReleaseNodes = client;
    mRefCount++;
    return 0;
}

int Class::UnsubscribeDestructorFast(ClassDestructorClient *client)
{
    if (client == mReleaseNodes)
        mReleaseNodes = client->mNext;
    if (client->mPrevious)
        client->mPrevious->mNext = client->mNext;
    if (client->mNext)
        client->mNext->mPrevious = client->mPrevious;
    if (--mRefCount == 0)
        gpAllocator->Free(this, 0);
    return 0;
}

int Class::SubscribeMemberDataFast(FunctionClient *client)
{
    client->mNext = mCallbacks;
    client->mPrevious = 0;
    if (mCallbacks)
        mCallbacks->mPrevious = client;
    mCallbacks = client;
    mRefCount++;
    return 0;
}

int Class::UnsubscribeMemberDataFast(FunctionClient *client)
{
    if (client == mCallbacks)
        mCallbacks = client->mNext;
    if (client->mPrevious)
        client->mPrevious->mNext = client->mNext;
    if (client->mNext)
        client->mNext->mPrevious = client->mPrevious;
    if (--mRefCount == 0)
        gpAllocator->Free(this, 0);
    return 0;
}

int GlobalVariable::SetFast(GlobalVariableHandle *handle, void *data)
{
    int result = handle->Valid();
    if (result >= 0) {
        GlobalVariableEntry *entry = handle->mEntry;
        if (*(int *)data == entry->mState)
            return 0;
        entry->mState = *(int *)data;
        for (FunctionClient *client = entry->mNodes; client; client = client->mNext)
            client->mCallback((Parameter *)&entry->mState, client->mContext);
    }
    return result;
}

int GlobalVariable::SubscribeFast(GlobalVariableHandle *handle, FunctionClient *client)
{
    int result = handle->Valid();
    if (result < 0)
        return result;
    GlobalVariableEntry *entry = handle->mEntry;
    client->mNext = entry->mNodes;
    client->mPrevious = 0;
    if (entry->mNodes)
        entry->mNodes->mPrevious = client;
    entry->mNodes = client;
    client->mCallback((Parameter *)&entry->mState, client->mContext);
    return 0;
}

int GlobalVariable::UnsubscribeFast(GlobalVariableHandle *handle, FunctionClient *client)
{
    int result = handle->Valid();
    if (result < 0)
        return result;
    GlobalVariableEntry *entry = handle->mEntry;
    if (client == entry->mNodes)
        entry->mNodes = client->mNext;
    if (client->mPrevious)
        client->mPrevious->mNext = client->mNext;
    if (client->mNext)
        client->mNext->mPrevious = client->mPrevious;
    return 0;
}

}
