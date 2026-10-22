#ifndef ENGINE_CU_801B8C18_H
#define ENGINE_CU_801B8C18_H

class Class_801B8D9C;

struct Struct_803EB878 {
    const char *mName;
    unsigned int mHash;
};

struct AllocParams {
    AllocParams() : mUnknown0(0), mUnknown4(0), mUnknown8(0) {}

    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
};

class Allocator {
public:
    virtual void *Alloc(int size, const AllocParams &params);
    virtual void Free(void *p, int unknown);
};

struct Link_801B8C18 {
    Link_801B8C18 *mNext;
    Link_801B8C18 *mPrevious;
};

/* Registry of banks; its constructor runs from the global constructor 0x801B9CD4. */
class Class_8037E820 {
public:
    Class_8037E820() : mHead(0) {}

    Link_801B8C18 *mHead;
};

struct Node_801B9410 {
    Node_801B9410 *mNext;
    Node_801B9410 *mPrevious;
    void (*mCallback)(void *params, void *context);
    void *mContext;
};

struct Entry_801B8C60 {
    Node_801B9410 *mNodes;
    const char *mName;
    union {
        int mValue;
        struct {
            short mHash;
            unsigned short mId;
        } mParts;
    };
};

struct Object_801B9068;

struct Node_801B95FC {
    Node_801B95FC *mNext;
    Node_801B95FC *mPrevious;
    void (*mCallback)(Object_801B9068 *object, void *params, void *context);
    void *mContext;
};

struct Entry_801B8DF0 {
    Node_801B95FC *mNodes;
    const char *mName;
    union {
        int mValue;
        struct {
            short mHash;
            unsigned short mId;
        } mParts;
    };
};

struct Node_801B9B30 {
    Node_801B9B30 *mNext;
    Node_801B9B30 *mPrevious;
    void (*mCallback)(int *state, void *context);
    void *mContext;
};

struct Entry_801B8F2C {
    Node_801B9B30 *mNodes;
    int mState;
    const char *mName;
    union {
        int mValue;
        struct {
            short mHash;
            unsigned short mId;
        } mParts;
    };
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
    Callback_801B9068 *mPrevious;
    void (*mCallback)(void *, void *);
    void *mContext;
};

struct Node_801B9724 {
    Node_801B9724 *mNext;
    Node_801B9724 *mPrevious;
    void (*mCallback)(Object_801B9068 *object, void *context);
    void *mContext;
};

/* Reference-counted object created by fn_801B95FC from a second-table entry. */
struct Object_801B9068 {
    Entry_801B8DF0 *mEntry;
    int mRefCount;
    Callback_801B9068 *mCallbacks;
    Node_801B9724 *mReleaseNodes;
};

extern "C" {
extern Class_8037E820 lbl_8037E820;

int fn_801B8D4C(Handle_801B8C60 *handle);
int fn_801B8EDC(Class_801B8D9C *handle);
int fn_801B9018(Handle_801B8F2C *handle);
void fn_801B9068(Object_801B9068 *object, void *params);
int fn_801B90CC(Allocator **out);
int fn_801B9148(void);
int fn_801B9174(void);
int fn_801B95AC(Class_801B8D9C *handle, void *params, Object_801B9068 **out);
int fn_801B96E4(Object_801B9068 *object);
int fn_801B983C(Object_801B9068 *object, void *params);
}

#endif
