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
int fn_801DCF0C(int a, int b, int c, void (*pA)(), void (*pB)());
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

extern "C" {
static int fn_8008BFE4()
{
    gFMCAPPORT.fn_8008C870();
    return 0;
}
}

void FMCAPPORT::fn_8008C010()
{
    Desc_80228224 desc;

    desc.mUnknown0 = 1;
    desc.mUnknown2 = 0;
    desc.mUnknown3 = 2;
    desc.mUnknown4[0] = 0;
    desc.mUnknown4[1] = 0;
    desc.mUnknown18 = 640;
    desc.mUnknown16 = 448;
    mpState.mp->mUnknown4088 = fn_80228224(&desc);
    fn_8022865C(mpState.mp->mUnknown4088, 0.0f, 0.0f);
    fn_802286D8(mpState.mp->mUnknown4088, 45.0f, 1.0f, 0.1f, 10.0f);
    mpState.mp->mUnknown4088->mUnknown28 &= ~1;
    fn_8022864C(mpState.mp->mUnknown4088, 0.0f, 0.0f, 1.0f);
}

void FMCAPPORT::fn_8008C0EC()
{
    fn_802283FC(mpState.mp->mUnknown4088);
    mpState.mp->mUnknown4088 = 0;
}

void FMCAPPORT::fn_8008C12C()
{
    fn_801DCF0C(32, 20, 1, 0, 0);
    mpState.mp->mUnknown4092 = fn_801DCFF0(1, 1, 0, 0, 0, 1, 0, -1);
    fn_801DD0C8(mpState.mp->mUnknown4092, 32, 0, fn_8008BFE4);
    fn_802286CC(mpState.mp->mUnknown4088, mpState.mp->mUnknown4092, 0);
    mpState.mp->mUnknown4096 = fn_801DD268(mpState.mp->mUnknown4092, 32, 0, 0);
    fn_801DD3AC(mpState.mp->mUnknown4092, mpState.mp->mUnknown4096, 15);
}

void FMCAPPORT::fn_8008C1FC()
{
    fn_801DD320(mpState.mp->mUnknown4092, mpState.mp->mUnknown4096);
    fn_80228D58(mpState.mp->mUnknown4096);
    fn_80228E18();
    fn_801DD0E8(mpState.mp->mUnknown4092);
    fn_801DCF8C(32);
    mpState.mp->mUnknown4096 = 0;
    mpState.mp->mUnknown4092 = 0;
}

void FMCAPPORT::SetEntry(int id, int unknown4, int unknown8, int unknown12, int unknown16,
                         const FMCAPPORTText *pText20, int unknown48, int unknown52, int unknown56,
                         const FMCAPPORTText *pText60, const FMCAPPORTValues *pValues88, int unknown300)
{
    int index = mpState.mp->mCount;
    unsigned int i;

    for (i = 0; i < mpState.mp->mCount; i++) {
        if (mpState.mp->mEntries[i].mId == id) {
            index = i;
            break;
        }
    }

    mpState.mp->mEntries[index].mId = id;
    mpState.mp->mEntries[index].mUnknown4 = unknown4;
    mpState.mp->mEntries[index].mUnknown8 = unknown8;
    mpState.mp->mEntries[index].mUnknown12 = unknown12;
    mpState.mp->mEntries[index].mUnknown16 = unknown16;
    mpState.mp->mEntries[index].mUnknown48 = unknown48;
    mpState.mp->mEntries[index].mUnknown52 = unknown52;
    mpState.mp->mEntries[index].mUnknown56 = unknown56;
    mpState.mp->mEntries[index].mText20 = *pText20;
    mpState.mp->mEntries[index].mText60 = *pText60;
    mpState.mp->mEntries[index].mValues88 = *pValues88;
    mpState.mp->mEntries[index].mUnknown300 = unknown300;

    if (index == mpState.mp->mCount) {
        mpState.mp->mCount = index + 1;
    }
}

void FMCAPPORT::ClearEntries()
{
    mpState.mp->mCount = 0;
}

int FMCAPPORT::IsBusy()
{
    return mpState.mp && mpState.mp->mState;
}

void FMCAPPORT::Start()
{
    mpState.mp->mState = 2;
    fn_80187E08(1, "Updating Players...", 1, 1);
    mpState.mp->mDelay = 20;
}

void FMCAPPORT::Update()
{
    FMCAPPORTState *state = mpState.mp;
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
            mpState.mp->mState = 0;
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
        fn_8008C010();
        fn_8008C12C();
        fn_8008A9F8(object);
        fn_8008AA48(object);
        fn_80199968(object);
        mpState.mp->mState = 3;
        break;
    }
    case 3:
        if (fn_8008AA7C(object)) {
            mpState.mp->mState = 4;
        }
        break;
    case 4:
        state->mUnknown8 = 0;
        mpState.mp->mState = 5;
        break;
    case 5:
        if (state->mUnknown8) {
            fn_8008C1FC();
            fn_8008C0EC();
            mpState.mp->mState = 6;
        }
        break;
    case 6:
        state->mUnknown4084 = new (0) Class_8008B284;
        fn_8008AAD0(object);
        mpState.mp->mState = 7;
        break;
    case 7:
        if (fn_8008AAF0(object)) {
            fn_8008ABA4(object);
            fn_801999B0(object);
            fn_8008AA9C(object);
            delete mpState.mp->mUnknown4084;
            mpState.mp->mUnknown4084 = 0;
            mpState.mp->mCount--;
            mpState.mp->mState = 2;
        }
        break;
    }
}

void FMCAPPORT::fn_8008C870()
{
    if (mpState.mp->mState == 5 && !mpState.mp->mUnknown8) {
        fn_801999F4(&mpState.mp->mObject);
        mpState.mp->mUnknown8 = 1;
    }
}

ModuleDependency *FMCAPPORT::GetDependencies() { return (ModuleDependency *)sDependencies; }
ModuleDependency *FMCAPPORT::GetLinks() { return 0; }
const char *FMCAPPORT::GetName() { return sName; }

int FMCAPPORT::Init()
{
    int result = 0;

    mpState.mp = (FMCAPPORTState *)fn_801D2BB0(1, sizeof(FMCAPPORTState), 0, 0);
    if (mpState.mp) {
        mpState.mp->mState = 0;
        mpState.mp->mUnknown8 = 0;
        mpState.mp->mCount = 0;
        result = 1;
    }
    return result;
}

int FMCAPPORT::Shutdown()
{
    fn_801D2BD0(mpState.mp);
    mpState.mp = 0;
    return 1;
}
