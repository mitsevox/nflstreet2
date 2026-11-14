#ifndef ENGINE_CSIS_H
#define ENGINE_CSIS_H

/* CSIS, the registry through which the sound libraries and the game exchange
   functions, classes and global variables by name: loaded systems (sound bank
   images) are subscribed into one list, and handles look their entries up by
   interface id. */

#include <dolphin/os/OSMutex.h>

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

namespace Csis {

struct Parameter;
class Class;

/* Name of an interface and its hash; the high half of the hash selects the system. */
struct InterfaceId {
    const char *mName;
    unsigned int mHash;
};

/* Link of a subscribed system in the system list. */
struct SystemLink {
    SystemLink *mNext;
    SystemLink *mPrevious;
};

/* List of the subscribed systems; its constructor runs from the global constructor. */
class SystemList {
public:
    SystemList() : mHead(0) {}

    SystemLink *mHead;
};

struct FunctionClient {
    FunctionClient *mNext;
    FunctionClient *mPrevious;
    void (*mCallback)(Parameter *params, void *context);
    void *mContext;
};

struct ClassConstructorClient {
    ClassConstructorClient *mNext;
    ClassConstructorClient *mPrevious;
    void (*mCallback)(Class *object, Parameter *params, void *context);
    void *mContext;
};

struct ClassDestructorClient {
    ClassDestructorClient *mNext;
    ClassDestructorClient *mPrevious;
    void (*mCallback)(Class *object, void *context);
    void *mContext;
};

/* Entry of a system's function table. */
struct FunctionEntry {
    FunctionClient *mNodes;
    const char *mName;
    union {
        int mValue;
        struct {
            short mHash;
            unsigned short mId;
        } mParts;
    };
};

/* Entry of a system's class table. */
struct ClassEntry {
    ClassConstructorClient *mNodes;
    const char *mName;
    union {
        int mValue;
        struct {
            short mHash;
            unsigned short mId;
        } mParts;
    };
};

/* Entry of a system's global variable table. */
struct GlobalVariableEntry {
    FunctionClient *mNodes;
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

class FunctionHandle {
public:
    int Set(const InterfaceId *id);
    int SetFast(const InterfaceId *id);
    int Valid();

    FunctionEntry *mEntry;
    int mValue;
};

class ClassHandle {
public:
    ClassHandle();
    int Set(const InterfaceId *id);
    int SetFast(const InterfaceId *id);
    int Valid();

    ClassEntry *mEntry;
    int mValue;
};

class GlobalVariableHandle {
public:
    int SetFast(const InterfaceId *id);
    int Valid();

    GlobalVariableEntry *mEntry;
    int mValue;
};

/* Header of a subscribed system image: three entry tables follow it. */
struct SystemHeader {
    unsigned char mUnknown0[10];
    unsigned short mCountA;
    unsigned short mCountB;
    unsigned short mCountC;
    short mUnknown10;
    unsigned char mUnknown12[2];
    FunctionEntry *mEntriesA;
    ClassEntry *mEntriesB;
    GlobalVariableEntry *mEntriesC;
    SystemLink mLink;
};

/* Instance data of a class: the class entry, the reference count and the
   member-data and destructor client lists. */
class ClassData {
public:
    void SendParameters(Parameter *params);

    ClassEntry *mEntry;
    int mRefCount;
    FunctionClient *mCallbacks;
    ClassDestructorClient *mReleaseNodes;
};

/* Reference-counted instance created from a class entry. */
class Class : public ClassData {
public:
    static int CreateInstance(ClassHandle *handle, void *params, Class **out);
    static int CreateInstanceFast(ClassHandle *handle, void *params, Class **out);
    int Release();
    int ReleaseFast();
    int GetRefCount(int *out);
    int AddRef();
    int DecRef();
    int SetMemberData(void *params);
    int SetMemberDataFast(void *params);
    static int SubscribeConstructorFast(ClassHandle *handle, ClassConstructorClient *client);
    static int UnsubscribeConstructorFast(ClassHandle *handle, ClassConstructorClient *client);
    int SubscribeDestructorFast(ClassDestructorClient *client);
    int UnsubscribeDestructorFast(ClassDestructorClient *client);
    int SubscribeMemberDataFast(FunctionClient *client);
    int UnsubscribeMemberDataFast(FunctionClient *client);
};

class System {
public:
    static int SetAllocator(Allocator *allocator);
    static int GetAllocator(Allocator **out);
    static int Init();
    static int Restore();
    static int Lock();
    static int Unlock();
    static int Subscribe(void *system);
    static int Unsubscribe(void *system);
};

class Function {
public:
    static int CallFast(FunctionHandle *handle, void *params);
    static int Subscribe(FunctionHandle *handle, FunctionClient *client);
    static int SubscribeFast(FunctionHandle *handle, FunctionClient *client);
    static int UnsubscribeFast(FunctionHandle *handle, FunctionClient *client);
};

class GlobalVariable {
public:
    static int SetFast(GlobalVariableHandle *handle, void *data);
    static int SubscribeFast(GlobalVariableHandle *handle, FunctionClient *client);
    static int UnsubscribeFast(GlobalVariableHandle *handle, FunctionClient *client);
};

extern int gIsInited;
extern SystemList gSystems;
extern Allocator *gpAllocator;
extern OSMutex gMutexHandle;

}

#endif
