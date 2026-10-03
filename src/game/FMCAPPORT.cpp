#include "game/FMCAPPORT.h"

void *operator new(unsigned int size, int unknown);

extern "C" {
Object_80228224 *fn_80228224(Desc_80228224 *pDesc);
void fn_802283FC(Object_80228224 *pObject);
void fn_8022864C(Object_80228224 *pObject, float a, float b, float c);
void fn_8022865C(Object_80228224 *pObject, float a, float b);
void fn_802286CC(Object_80228224 *pObject, int handle, int unknown);
void fn_802286D8(Object_80228224 *pObject, float a, float b, float c, float d);
void fn_80228D58(int handle);
void fn_80228E18(void);
int fn_801DCF0C(int a, int b, int c, int d, int e);
void fn_801DCF8C(int a);
int fn_801DCFF0(int a, int b, int c, int d, int e, int f, int g, int h);
void fn_801DD0C8(int handle, int a, int b, int (*pCallback)());
void fn_801DD0E8(int handle);
int fn_801DD268(int handle, int a, int b, int c);
void fn_801DD320(int handle, int a);
void fn_801DD3AC(int handle, int a, int b);
void *fn_801D2BB0(int a, int size, int c, int d);
void fn_801D2BD0(void *p);
void fn_80187DD8(int a);
void fn_80187E08(int a, const char *pText, int b, int c);
void fn_8008A9F8(Object_8008A9F8 *pObject);
void fn_8008AA48(Object_8008A9F8 *pObject);
int fn_8008AA7C(Object_8008A9F8 *pObject);
void fn_8008AA9C(Object_8008A9F8 *pObject);
void fn_8008AAD0(Object_8008A9F8 *pObject);
int fn_8008AAF0(Object_8008A9F8 *pObject);
void fn_8008ABA4(Object_8008A9F8 *pObject);
void fn_80199968(Object_8008A9F8 *pObject);
void fn_801999B0(Object_8008A9F8 *pObject);
void fn_801999F4(Object_8008A9F8 *pObject);
}

static const char *sName = "FMCAPPORT";
static void *sDependencies[] = { 0 };
FMCAPPORT gFMCAPPORT;

static int Callback_8008BFE4()
{
    gFMCAPPORT.Method_8008C870();
    return 0;
}

void FMCAPPORT::Method_8008C010()
{
    Desc_80228224 desc;

    desc.mUnknown0 = 1;
    desc.mUnknown2 = 0;
    desc.mUnknown3 = 2;
    desc.mUnknown4 = 0;
    desc.mUnknown8 = 0;
    desc.mUnknown18 = 640;
    desc.mUnknown16 = 448;
    mState.mp->mUnknown4088 = fn_80228224(&desc);
    fn_8022865C(mState.mp->mUnknown4088, 0.0f, 0.0f);
    fn_802286D8(mState.mp->mUnknown4088, 45.0f, 1.0f, 0.1f, 10.0f);
    mState.mp->mUnknown4088->mUnknown28 &= ~1;
    fn_8022864C(mState.mp->mUnknown4088, 0.0f, 0.0f, 1.0f);
}

void FMCAPPORT::Method_8008C0EC()
{
    fn_802283FC(mState.mp->mUnknown4088);
    mState.mp->mUnknown4088 = 0;
}

void FMCAPPORT::Method_8008C12C()
{
    fn_801DCF0C(32, 20, 1, 0, 0);
    mState.mp->mUnknown4092 = fn_801DCFF0(1, 1, 0, 0, 0, 1, 0, -1);
    fn_801DD0C8(mState.mp->mUnknown4092, 32, 0, Callback_8008BFE4);
    fn_802286CC(mState.mp->mUnknown4088, mState.mp->mUnknown4092, 0);
    mState.mp->mUnknown4096 = fn_801DD268(mState.mp->mUnknown4092, 32, 0, 0);
    fn_801DD3AC(mState.mp->mUnknown4092, mState.mp->mUnknown4096, 15);
}

void FMCAPPORT::Method_8008C1FC()
{
    fn_801DD320(mState.mp->mUnknown4092, mState.mp->mUnknown4096);
    fn_80228D58(mState.mp->mUnknown4096);
    fn_80228E18();
    fn_801DD0E8(mState.mp->mUnknown4092);
    fn_801DCF8C(32);
    mState.mp->mUnknown4096 = 0;
    mState.mp->mUnknown4092 = 0;
}

void FMCAPPORT::SetEntry(int id, int unknown4, int unknown8, int unknown12, int unknown16,
                         const FMCAPPORTText *pText20, int unknown48, int unknown52, int unknown56,
                         const FMCAPPORTText *pText60, const FMCAPPORTValues *pValues88, int unknown300)
{
    int index = mState.mp->mCount;
    unsigned int i;

    for (i = 0; i < mState.mp->mCount; i++) {
        if (mState.mp->mEntries[i].mId == id) {
            index = i;
            break;
        }
    }

    mState.mp->mEntries[index].mId = id;
    mState.mp->mEntries[index].mUnknown4 = unknown4;
    mState.mp->mEntries[index].mUnknown8 = unknown8;
    mState.mp->mEntries[index].mUnknown12 = unknown12;
    mState.mp->mEntries[index].mUnknown16 = unknown16;
    mState.mp->mEntries[index].mUnknown48 = unknown48;
    mState.mp->mEntries[index].mUnknown52 = unknown52;
    mState.mp->mEntries[index].mUnknown56 = unknown56;
    mState.mp->mEntries[index].mText20 = *pText20;
    mState.mp->mEntries[index].mText60 = *pText60;
    mState.mp->mEntries[index].mValues88 = *pValues88;
    mState.mp->mEntries[index].mUnknown300 = unknown300;

    if (index == mState.mp->mCount) {
        mState.mp->mCount = index + 1;
    }
}

void FMCAPPORT::ClearEntries()
{
    mState.mp->mCount = 0;
}

int FMCAPPORT::IsBusy()
{
    return mState.mp && mState.mp->mState;
}

void FMCAPPORT::Start()
{
    mState.mp->mState = 2;
    fn_80187E08(1, "Updating Players...", 1, 1);
    mState.mp->mDelay = 20;
}

void FMCAPPORT::Update()
{
    FMCAPPORTState *state = mState.mp;
    Object_8008A9F8 *object = &state->mObject;

    switch (state->mState) {
    case 0:
        break;
    case 2:
        if (state->mDelay != 0) {
            state->mDelay--;
        } else if (state->mCount != 0) {
            state->mState = 1;
        } else {
            fn_80187DD8(0);
            mState.mp->mState = 0;
        }
        break;
    case 1: {
        int index = state->mCount - 1;
        FMCAPPORTEntry *entry;

        object->mUnknown0 = state->mEntries[index].mId;
        entry = &state->mEntries[index];
        object->mUnknown44 = entry->mUnknown4;
        object->mUnknown48 = entry->mUnknown48;
        object->mUnknown12 = entry->mUnknown8;
        object->mUnknown16 = entry->mUnknown12;
        object->mUnknown20 = entry->mUnknown52;
        object->mUnknown24 = -1;
        object->mUnknown28 = -1;
        object->mUnknown32 = entry->mUnknown16;
        object->mUnknown36 = entry->mUnknown56;
        object->mUnknown40 = -1;
        object->mText289 = entry->mText20;
        object->mText314 = entry->mText60;
        object->mValues52 = entry->mValues88;
        object->mValues52.mValues[entry->mUnknown300 + 1] = 1.0f;
        object->mUnknown364 = entry->mUnknown300;
        Method_8008C010();
        Method_8008C12C();
        fn_8008A9F8(object);
        fn_8008AA48(object);
        fn_80199968(object);
        mState.mp->mState = 3;
        break;
    }
    case 3:
        if (fn_8008AA7C(object)) {
            mState.mp->mState = 4;
        }
        break;
    case 4:
        state->mUnknown8 = 0;
        mState.mp->mState = 5;
        break;
    case 5:
        if (state->mUnknown8) {
            Method_8008C1FC();
            Method_8008C0EC();
            mState.mp->mState = 6;
        }
        break;
    case 6:
        state->mUnknown4084 = new (0) Class_8008B284;
        fn_8008AAD0(object);
        mState.mp->mState = 7;
        break;
    case 7:
        if (fn_8008AAF0(object)) {
            fn_8008ABA4(object);
            fn_801999B0(object);
            fn_8008AA9C(object);
            delete mState.mp->mUnknown4084;
            mState.mp->mUnknown4084 = 0;
            mState.mp->mCount--;
            mState.mp->mState = 2;
        }
        break;
    }
}

void FMCAPPORT::Method_8008C870()
{
    if (mState.mp->mState == 5 && !mState.mp->mUnknown8) {
        fn_801999F4(&mState.mp->mObject);
        mState.mp->mUnknown8 = 1;
    }
}

ModuleDependency *FMCAPPORT::GetDependencies() { return (ModuleDependency *)sDependencies; }
ModuleDependency *FMCAPPORT::GetLinks() { return 0; }
const char *FMCAPPORT::GetName() { return sName; }

int FMCAPPORT::Init()
{
    int result = 0;

    mState.mp = (FMCAPPORTState *)fn_801D2BB0(1, sizeof(FMCAPPORTState), 0, 0);
    if (mState.mp) {
        mState.mp->mState = 0;
        mState.mp->mUnknown8 = 0;
        mState.mp->mCount = 0;
        result = 1;
    }
    return result;
}

int FMCAPPORT::Shutdown()
{
    fn_801D2BD0(mState.mp);
    mState.mp = 0;
    return 1;
}
