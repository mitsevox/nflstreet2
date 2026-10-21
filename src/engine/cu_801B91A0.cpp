#include "engine/cu_801B8C18.h"
#include "game/Class_801B8D9C.h"

extern "C" {
Class_8037E820 lbl_8037E820;

extern Allocator *lbl_8037E824;
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
