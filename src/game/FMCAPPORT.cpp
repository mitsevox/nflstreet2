/* FMCAPPORT front-end module: takes the queued create-a-player portrait jobs one at a
   time, renders the player's head with its own camera, captures the frame, quantizes it
   and saves the portrait ("Updating Players..."). */

#include "game/fn_801D2B7C.h"
#include "engine/viewport.h"
#include "game/FMCAPPORT.h"

void *operator new(unsigned int size, int unknown);

extern "C" {
int ObjNewType_(int a, int b, int c, void (*pA)(), void (*pB)());
int ObjDelType(int a);
int ObjNewList(int a, int b, int c, int d, int e, int f, int g, int h);
void ObjSetListObjFunc(int handle, int a, int b, int (*pCallback)());
void ObjDelList(int handle);
int ObjNewInList(int handle, int a, int b, int c);
void ObjRemoveFromList(int handle, int a);
void ObjSetPriority(int handle, int a, int b);
void *fn_801D2BB0(int a, int size, int c, int d);
void GameTextShowPleaseWait(int a);
void GameTextShowBusyDialog(int a, const char *pText, int b, int c);
void PortraitJobAllocImage(PortraitJob_t *pObject);
void PortraitJobLoad(PortraitJob_t *pObject);
int PortraitJobIsLoaded(PortraitJob_t *pObject);
void PortraitJobUnload(PortraitJob_t *pObject);
void PortraitJobQuantize(PortraitJob_t *pObject);
int PortraitJobIsDone(PortraitJob_t *pObject);
void PortraitJobSave(PortraitJob_t *pObject);
void PortraitRenderInit(PortraitJob_t *pObject);
void PortraitRenderShutdown(PortraitJob_t *pObject);
void PortraitRenderDraw(PortraitJob_t *pObject);
}

static const char *sName = "FMCAPPORT";
static void *sDependencies[] = { 0 };
FMCAPPORT gFMCAPPORT;

extern "C" {
static int _FMCAPPORTDrawCallback()
{
    gFMCAPPORT.CaptureFrame();
    return 0;
}
}

void FMCAPPORT::CreateCamera()
{
    ViewportDesc_t desc;

    desc.mUnknown0 = 1;
    desc.mUnknown2 = 0;
    desc.mUnknown3 = 2;
    desc.mUnknown4[0] = 0;
    desc.mUnknown4[1] = 0;
    desc.mUnknown18 = 640;
    desc.mUnknown16 = 448;
    mpState.mp->mUnknown4088 = VptOpen(&desc);
    VptSetPos(mpState.mp->mUnknown4088, 0.0f, 0.0f);
    VptSetPerspective(mpState.mp->mUnknown4088, 45.0f, 1.0f, 0.1f, 10.0f);
    mpState.mp->mUnknown4088->mUnknown28 &= ~1;
    VptSetEraseColor(mpState.mp->mUnknown4088, 0.0f, 0.0f, 1.0f);
}

void FMCAPPORT::DestroyCamera()
{
    VptClose(mpState.mp->mUnknown4088);
    mpState.mp->mUnknown4088 = 0;
}

void FMCAPPORT::CreateRenderPass()
{
    ObjNewType_(32, 20, 1, 0, 0);
    mpState.mp->mUnknown4092 = ObjNewList(1, 1, 0, 0, 0, 1, 0, -1);
    ObjSetListObjFunc(mpState.mp->mUnknown4092, 32, 0, _FMCAPPORTDrawCallback);
    VptSetObjectList(mpState.mp->mUnknown4088, mpState.mp->mUnknown4092, 0);
    mpState.mp->mUnknown4096 = ObjNewInList(mpState.mp->mUnknown4092, 32, 0, 0);
    ObjSetPriority(mpState.mp->mUnknown4092, mpState.mp->mUnknown4096, 15);
}

void FMCAPPORT::DestroyRenderPass()
{
    ObjRemoveFromList(mpState.mp->mUnknown4092, mpState.mp->mUnknown4096);
    VptTrashObject(mpState.mp->mUnknown4096);
    VptFlushObjectTrashSync();
    ObjDelList(mpState.mp->mUnknown4092);
    ObjDelType(32);
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
    GameTextShowBusyDialog(1, "Updating Players...", 1, 1);
    mpState.mp->mDelay = 20;
}

void FMCAPPORT::Update()
{
    FMCAPPORTState *state = mpState.mp;
    PortraitJob_t *object = &state->mObject;

    switch (state->mState) {
    case 0:
        break;
    case 2:
        if (state->mDelay != 0) {
            state->mDelay--;
        } else if (state->mCount != 0) {
            state->mState = 1;
        } else {
            GameTextShowPleaseWait(0);
            mpState.mp->mState = 0;
        }
        break;
    case 1: {
        int index = state->mCount - 1;
        FMCAPPORTEntry *entry;

        object->mUnknown0 = state->mEntries[index].mId;
        entry = &state->mEntries[index];
        object->mUnknown44[0] = entry->mUnknown4;
        object->mUnknown44[1] = entry->mUnknown48;
        object->mUnknown12[0] = entry->mUnknown8;
        object->mUnknown12[1] = entry->mUnknown12;
        object->mUnknown12[2] = entry->mUnknown52;
        object->mUnknown12[3] = -1;
        object->mUnknown28[0] = -1;
        object->mUnknown28[1] = entry->mUnknown16;
        object->mUnknown28[2] = entry->mUnknown56;
        object->mUnknown28[3] = -1;
        object->mText264[1] = entry->mText20;
        object->mText264[2] = entry->mText60;
        object->mValues52 = entry->mValues88;
        object->mValues52.mValues[entry->mUnknown300 + 1] = 1.0f;
        object->mUnknown364 = entry->mUnknown300;
        CreateCamera();
        CreateRenderPass();
        PortraitJobAllocImage(object);
        PortraitJobLoad(object);
        PortraitRenderInit(object);
        mpState.mp->mState = 3;
        break;
    }
    case 3:
        if (PortraitJobIsLoaded(object)) {
            mpState.mp->mState = 4;
        }
        break;
    case 4:
        state->mUnknown8 = 0;
        mpState.mp->mState = 5;
        break;
    case 5:
        if (state->mUnknown8) {
            DestroyRenderPass();
            DestroyCamera();
            mpState.mp->mState = 6;
        }
        break;
    case 6:
        state->mObject.mpUnknown1636 = new (0) ColorQuantizer;
        PortraitJobQuantize(object);
        mpState.mp->mState = 7;
        break;
    case 7:
        if (PortraitJobIsDone(object)) {
            PortraitJobSave(object);
            PortraitRenderShutdown(object);
            PortraitJobUnload(object);
            delete mpState.mp->mObject.mpUnknown1636;
            mpState.mp->mObject.mpUnknown1636 = 0;
            mpState.mp->mCount--;
            mpState.mp->mState = 2;
        }
        break;
    }
}

void FMCAPPORT::CaptureFrame()
{
    if (mpState.mp->mState == 5 && !mpState.mp->mUnknown8) {
        PortraitRenderDraw(&mpState.mp->mObject);
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
