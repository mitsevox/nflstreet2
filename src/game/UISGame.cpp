/* UI Studio set-up for the game: opens the UI resource cache (uis_all.dat), creates the
   three UI Studio views (viewport, camera, draw object and UI Studio instance each) and
   registers the game callbacks and screen object types with them, feeds controller input
   to the main instance with auto-repeat for held directions, and tears it all down again
   when the UIS module shuts down. */
#include "game/UISModelObj.h"
#include "game/ResBank.h"
#include "game/FELoop.h"
#include "game/InGame.h"
#include "game/fn_8007F828.h"
#include "game/GameModeType.h"
#include "game/CamAddCameraToViewport.h"
#include "game/fn_801D2B7C.h"
#include "engine/viewporttypes.h"

extern "C" {
#include "engine/viewport.h"
}

/* One of the eight 56-byte records at 0x80362FC0. */
struct UISGameRepeat_t {
    float mUnknown0[10];
    unsigned char mUnknown40[10];
    unsigned short mUnknown50;
    unsigned char mUnknown52;
    unsigned char mUnknown53;
    unsigned char mUnknown54;
    unsigned char mUnknown55;
};

extern "C" {
extern char gMainFEGroup[];
extern char lbl_802EBE5C[];
extern char lbl_802EBE78[];
extern char lbl_802EBE98[];
extern float gFrameTimeScale;

double fabs(double);

void BootHandleReset(void);
int MainFEGroupIsFirstStart(void *p);
void fn_8000FCD4(int a);
void fn_80047670(int handle);
void fn_80047698(void);
void InGameStateReset(void);
void InGameStateClearActive(void);
void ScreenMsgDispatch(void);
void SndgUpdate(int a);
void CamSetupAspect(void);
float CamGetAspect(void);
void BannerSetTickMs(unsigned int a);
void BannerEnd(void);
void GameEventFlagsInit(void);
void GameEventFlagsShutdown(void);
void TeamLogoUpdatePending(void);
int UISGameLoadItem(int a, int b);
void UISGameFreeItem(int a, int b);
void UISGameDrawDone(void);
void UISGameRepeatResetCB(void);
void UISGameObjSlot7(void);
void UISGameRefKey(int a);
void UISGameEnableDraw(void *p);
void UISGameSetEvent20Pending(unsigned char value);
unsigned char UISGameIsEvent20Pending(void);
void UISGameSetDrawMode(int a);
void UISViewObjAction(void);
void UISModelObjAction(void);
void UISSoundObjAction(void);
void UISTextTableAction(void);
void UISHeldObjSet(int a);
unsigned char UISHeldObjEnable(unsigned char value);
unsigned char UISHeldObjIsEnabled(void);
void DbgScreenRenderCallback(Viewport_t *pObject);
void ScreenTransInit(Viewport_t *pObject, int a);
void ScreenTransShutdown(void);
void PlyrIconQueueReset(void);
void UISResListSetup(void);
void *CamCreate(int a, int b);
void CamDestroy(void *p);
void CamSetZScale(void *p, float a);
void CamFreeSetPos(void *p, float a, float b, float c);
void CamFreeSetAngle(void *p, int a, int b, int c);
void fn_801CD2A4(void);
void fn_801CE82C(void);
void fn_801CE910(void);
void fn_801CE9E0(int a);
int fn_801CEA08(void);
int fn_801CEA14(void);
int fn_801CEB4C(void);
int fn_801CEC74(void);
int fn_801CEC7C(void);
int GlibRenderGetBin(int index);
void GlibRenderSelectBin(int a);
float fn_801CFD28(int a);
void fn_801D339C(int a);
void fn_801D342C(int a);
int ObjNewType_(int a, int b, int c, void (*pA)(), void (*pB)());
int ObjDelType(int a);
int ObjNewList(int a, int b, int c, int d, int e, int f, int g, int h);
void ObjSetListObjFunc(int handle, int a, int b, int (*pCallback)(int, int));
void ObjDelList(int handle);
int ObjNewInList(int handle, int a, int b, int c);
void ObjRemoveFromList(int handle, int a);
int fn_802188A0(int a, int b, int c, int d, int e, int f);
void fn_802188D4(void *p, int a, int b, int c, int d, int e, int f, unsigned int g);
void fn_80218A34(void *p);
void fn_80218AA8(void *p, void (*pCallback)());
void fn_80218AB0(void *p, int (*pA)(int, int), void (*pB)(int, int));
void fn_80218ABC(void *p, void (*pCallback)());
void fn_80218AC4(void *p, void (*pCallback)());
void fn_80218ACC(void *p, void (*pCallback)());
void fn_80218AD4(void *p, int index, void (*pCallback)());
void fn_80218CB8(void *p, int a);
void fn_8021992C(void *p, int a);
void fn_80219650(void *p, unsigned short *pA, unsigned short *pB);
void fn_802196B4(void *p, int a, int b, int c, float *pD, unsigned char e);
void fn_80219A54(void *p, int a);
int fn_80219AF8(void *p, int a, int b, int c);
int fn_8021A020(void *p);
int fn_8021D828(void *p, unsigned short a, unsigned short b);
void fn_8021D880(void (*pCallback)());
void fn_8021DF9C(void *p);
void *fn_8021EA44(int index);
void fn_8021ED88(void *p);
void fn_8021EF6C(void (*pCallback)());
void fn_8021EFD8(void);
void fn_80220CDC(int a);
void fn_80220CFC(int a);
void fn_80220D04(void);
void fn_802212C8(void);
void fn_80222220(void);
void fn_80223460(void);
void fn_80225654(void);
void fn_802363B0(Viewport_t *pObject);
void fn_802363E0(Viewport_t *pObject);
int fn_80236EC0(int a);
}

static ResBank_t *_UISGame_pCache = 0;
static Viewport_t *_UISGame_pMainVpt = 0;
static void *_UISGame_pMainCam = 0;
static int _UISGame_pMainObjList = 0;
static int _UISGame_pMainObj = 0;
static Viewport_t *_UISGame_pSubVpt = 0;
static void *_UISGame_pSubCam = 0;
static int _UISGame_pSubObjList = 0;
static int _UISGame_pSubObj = 0;
static Viewport_t *_UISGame_pSub2Vpt = 0;
static void *_UISGame_pSub2Cam = 0;
static int _UISGame_pSub2ObjList = 0;
static int _UISGame_pSub2Obj = 0;
static unsigned char _UISGame_bInputFlag = 0;
static unsigned char _UISGame_bEvent20Pending = 0;
int gUISGameUnusedWord = 0;
static int _UISGame_iLockedPad = -1;
static int _UISGame_iDrawMask = 7;
unsigned char gUISGameUnusedByte = 1;
extern "C" {
void *gUISMainInfo = 0;
void *gUISSub2Info = 0;
void *gUISSubInfo = 0;
}
int gUISGameUnusedWord2 = 0;
static char *_UISGame_pszAllFile = lbl_802EBE5C;
char *gUISGameFontFile = lbl_802EBE98;
static int _UISGame_iLastPad = -1;

static char *_UISGame_apszKeyFiles[15];
static UISGameRepeat_t _UISGame_aRepeat[8];

extern "C" {

void UISGameInitHook(void) {}

void UISGameShutdownHook(void) {}

void UISGameRuntimeError(void) {}

void UISGameObjNew(void) {}

void UISGameObjDelete(void) {}

void UISGameFreeTable(void)
{
    fn_8021DF9C(fn_8021EA44(1));
}

void UISGameSetCallbacks(void *p)
{
    fn_80218AB0(p, UISGameLoadItem, UISGameFreeItem);
    fn_80218AC4(p, fn_802212C8);
    fn_80218AA8(p, ScreenMsgDispatch);
    fn_80218ABC(p, UISGameDrawDone);
    fn_80218ACC(p, UISGameRepeatResetCB);
    fn_80218AD4(p, 0, fn_8021EFD8);
    fn_80218AD4(p, 1, UISSoundObjAction);
    fn_80218AD4(p, 2, fn_80223460);
    fn_80218AD4(p, 3, UISViewObjAction);
    fn_80218AD4(p, 4, fn_80225654);
    fn_80218AD4(p, 5, UISTextTableAction);
    fn_80218AD4(p, 6, UISModelObjAction);
    fn_80218AD4(p, 7, UISGameObjSlot7);
    fn_80218AD4(p, 8, fn_80222220);
}

int UISGameDrawObj(int a, int b)
{
    int saved;

    UISGameSetDrawMode(0);
    TeamLogoUpdatePending();
    fn_801CE9E0(0);
    fn_801CD2A4();
    if (FELoopIsMainFEActive()) {
        fn_8021ED88(fn_8021EA44(1));
    }
    saved = fn_80236EC0(0);
    if (a == _UISGame_pMainObj) {
        if (gUISMainInfo && (_UISGame_iDrawMask & 1)) {
            fn_8021992C(gUISMainInfo, b);
            PlyrIconQueueReset();
        }
        if (gUISSubInfo && (_UISGame_iDrawMask & 2)) {
            fn_8021992C(gUISSubInfo, b);
        }
        if (gUISSub2Info && (_UISGame_iDrawMask & 4)) {
            fn_8021992C(gUISSub2Info, b);
        }
    }
    fn_80236EC0(saved);
    fn_801CE9E0(1);
    return 0;
}

int UISGameLoadItem(int a, int b)
{
    int result;

    fn_801D339C(-1);
    ResBankOpenFile(_UISGame_pCache, a);
    ResBankLoad(_UISGame_pCache, a, b, 0);
    result = ResBankGetData(_UISGame_pCache, a, b);
    fn_801D342C(-1);
    return result;
}

void UISGameFreeItem(int a, int b)
{
    ResBankUnload(_UISGame_pCache, a, b);
    ResBankCloseFile(_UISGame_pCache, a);
}

void UISGameDrawDone(void)
{
    fn_801CE910();
}

int UISGameIsInputPad(int a)
{
    int result = 1;

    if (_UISGame_iLockedPad != -1) {
        result = _UISGame_iLockedPad == a;
    }
    return result;
}

int UISGameRepeatIndex(unsigned int id)
{
    switch (id) {
    case 2:
        return 0;
    case 3:
        return 1;
    case 4:
        return 2;
    case 5:
        return 3;
    case 10:
        return 4;
    case 11:
        return 5;
    case 12:
        return 6;
    case 13:
        return 7;
    }
    return 8;
}

void UISGameRepeatClearSlot(unsigned int index, int record)
{
    _UISGame_aRepeat[record].mUnknown0[index] = 0.0f;
    _UISGame_aRepeat[record].mUnknown40[index] = _UISGame_aRepeat[record].mUnknown54;
    if (index < 16) {
        _UISGame_aRepeat[record].mUnknown50 &= ~(1 << index);
    } else {
        _UISGame_aRepeat[record].mUnknown50 = 0;
    }
}

void UISGameRepeatReset(void)
{
    unsigned int record;
    unsigned int index;

    for (record = 0; record < 8; record++) {
        for (index = 0; index < 10; index++) {
            UISGameRepeatClearSlot(index, record);
        }
    }
}

void UISGameRemapInput(int *pA, unsigned int *pId, float *pValue)
{
    unsigned int id = *pId;
    int a = *pA;
    float value = *pValue;
    float magnitude;

    switch (id) {
    case 0x29:
    case 0x33:
        id = 2;
        break;
    case 0x2A:
    case 0x34:
        id = 3;
        break;
    case 0x28:
    case 0x35:
        id = 4;
        break;
    case 0x27:
    case 0x36:
        id = 5;
        break;
    case 0x2F:
    case 0x3B:
        id = 10;
        break;
    case 0x30:
    case 0x3C:
        id = 11;
        break;
    case 0x31:
    case 0x3D:
        id = 12;
        break;
    case 0x32:
    case 0x3E:
        id = 13;
        break;
    case 0x8B:
        UISGameRepeatClearSlot(a, 3);
        UISGameRepeatClearSlot(a, 2);
        break;
    case 0x8C:
        UISGameRepeatClearSlot(a, 0);
        UISGameRepeatClearSlot(a, 1);
        break;
    case 0x10:
        if (value > 0.0f) {
            id = 5;
        } else {
            id = 4;
        }
        if ((value > 0.0f && _UISGame_aRepeat[3].mUnknown0[a] == 0.0f)
            || (value < 0.0f && _UISGame_aRepeat[2].mUnknown0[a] == 0.0f)) {
            value = 1.0f;
        }
        magnitude = fabs(value);
        if (magnitude < 0.5f) {
            magnitude = 0.5f;
        } else if (magnitude > 1.0f) {
            magnitude = 1.0f;
        }
        value = magnitude;
        break;
    case 0x11:
        if (value > 0.0f) {
            id = 2;
        } else {
            id = 3;
        }
        if ((value > 0.0f && _UISGame_aRepeat[0].mUnknown0[a] == 0.0f)
            || (value < 0.0f && _UISGame_aRepeat[1].mUnknown0[a] == 0.0f)) {
            value = 1.0f;
        }
        magnitude = fabs(value);
        if (magnitude < 0.5f) {
            magnitude = 0.5f;
        } else if (magnitude > 1.0f) {
            magnitude = 1.0f;
        }
        value = magnitude;
        break;
    }
    *pA = a;
    *pId = id;
    *pValue = value;
}

int UISGameRepeatInput(int *pA, unsigned int *pId, float *pValue)
{
    unsigned short unknown0;
    unsigned short unknown1;
    int a = *pA;
    unsigned int id = *pId;
    float value = *pValue;
    unsigned int record;
    int result = 0;

    UISGameRemapInput(&a, &id, &value);
    record = UISGameRepeatIndex(id);
    if (record < 8) {
        UISGameRepeat_t *pRecord = &_UISGame_aRepeat[record];

        if (value > 0.0f) {
            result = pRecord->mUnknown0[a] == 0.0f;
            pRecord->mUnknown0[a] += value * pRecord->mUnknown52;
            if (pRecord->mUnknown0[a] > pRecord->mUnknown40[a]) {
                pRecord->mUnknown0[a] -= pRecord->mUnknown40[a];
                if (pRecord->mUnknown40[a] > pRecord->mUnknown53) {
                    pRecord->mUnknown40[a] -= pRecord->mUnknown55;
                    if (pRecord->mUnknown40[a] < pRecord->mUnknown53) {
                        pRecord->mUnknown40[a] = pRecord->mUnknown53;
                    }
                }
                result = 1;
            }
        } else if (pRecord->mUnknown0[a] > 0.0f) {
            UISGameRepeatClearSlot(a, record);
            result = 1;
        }
    } else {
        result = 1;
    }
    if (id - 12 <= 1 && result == 1) {
        result = 0;
        fn_80219650(gUISMainInfo, &unknown0, &unknown1);
        if (unknown0 == 3) {
            result = unknown1 == 2;
        }
    }
    *pA = a;
    *pId = id;
    *pValue = value;
    return result;
}

void UISGameRepeatResetCB(void)
{
    UISGameRepeatReset();
}

void UISGameSetProjection(Viewport_t *pObject)
{
    float near = 0.1f;
    float far = 1500.0f;

    VptSetPerspective(pObject, 45.0f, CamGetAspect(), near, far);
}

void UISGameObjSlot7(void) {}

void UISGameCreateMain(void)
{
    ViewportDesc_t desc;

    desc.mUnknown0 = 5;
    desc.mUnknown2 = 0;
    desc.mUnknown3 = 2;
    desc.mUnknown4[0] = 0;
    desc.mUnknown4[1] = 0;
    desc.mUnknown16 = fn_801CEA14();
    desc.mUnknown18 = fn_801CEA08();
    if (!FELoopIsMainFEActive() && (fn_8007F828(6) == 1 || fn_801CEB4C() == 1)) {
        desc.mUnknown16 = fn_801CEC74();
        desc.mUnknown18 = fn_801CEC7C();
    }
    _UISGame_pMainVpt = VptOpen(&desc);
    UISGameSetProjection(_UISGame_pMainVpt);
    _UISGame_pMainVpt->mUnknown28 &= ~1;
    VptSetEraseColor(_UISGame_pMainVpt, 0.0f, 0.0f, 0.0f);
    _UISGame_pMainCam = CamCreate(0, 0);
    CamFreeSetAngle(_UISGame_pMainCam, 0, 0x800000, 0x800000);
    CamFreeSetPos(_UISGame_pMainCam, 427.0f, 240.0f, -(240.0f / fn_801CFD28(0x100000)));
    CamAddCameraToViewport(_UISGame_pMainVpt, _UISGame_pMainCam);
    if (FELoopIsMainFEActive()) {
        CamSetZScale(_UISGame_pMainCam, 1.0f);
    } else {
        CamSetZScale(_UISGame_pMainCam, 4.0f);
    }
    VptSetCallback(_UISGame_pMainVpt, 2, DbgScreenRenderCallback, 31);
    _UISGame_pMainObjList = ObjNewList(1, 336, 0, 0, 0, 1, 0, -1);
    ObjSetListObjFunc(_UISGame_pMainObjList, 21, 0, UISGameDrawObj);
    VptSetObjectList(_UISGame_pMainVpt, _UISGame_pMainObjList, 0);
    _UISGame_pMainObj = ObjNewInList(_UISGame_pMainObjList, 21, 0, 0);
    if (!FELoopIsMainFEActive()) {
        ScreenTransInit(_UISGame_pMainVpt, 0);
    }
    gUISMainInfo = fn_801D2B7C(fn_802188A0(12, 9, 160, 7, 640, 160), 0, 0);
    fn_802188D4(gUISMainInfo, 12, 9, 160, 7, 640, 160, (unsigned int)(gFrameTimeScale * 16.666668f));
    UISGameSetCallbacks(gUISMainInfo);
    UISGameEnableDraw(gUISMainInfo);
}

void UISGameCreateSub(void)
{
    ViewportDesc_t desc;

    desc.mUnknown0 = 5;
    desc.mUnknown2 = 0;
    desc.mUnknown3 = 2;
    desc.mUnknown4[0] = 0;
    desc.mUnknown4[1] = 0;
    desc.mUnknown16 = fn_801CEA14();
    desc.mUnknown18 = fn_801CEA08();
    if (!FELoopIsMainFEActive() && (fn_8007F828(6) == 1 || fn_801CEB4C() == 1)) {
        desc.mUnknown16 = fn_801CEC74();
        desc.mUnknown18 = fn_801CEC7C();
    }
    _UISGame_pSubVpt = VptOpen(&desc);
    UISGameSetProjection(_UISGame_pSubVpt);
    _UISGame_pSubVpt->mUnknown28 &= ~1;
    VptSetEraseColor(_UISGame_pSubVpt, 0.0f, 0.0f, 0.0f);
    _UISGame_pSubCam = CamCreate(0, 0);
    CamFreeSetAngle(_UISGame_pSubCam, 0, 0x800000, 0x800000);
    CamFreeSetPos(_UISGame_pSubCam, 320.0f, 240.0f, -(240.0f / fn_801CFD28(0x100000)));
    CamAddCameraToViewport(_UISGame_pSubVpt, _UISGame_pSubCam);
    CamSetZScale(_UISGame_pSubCam, 4.0f);
    _UISGame_pSubObjList = ObjNewList(1, 336, 0, 0, 0, 1, 0, -1);
    ObjSetListObjFunc(_UISGame_pSubObjList, 21, 0, UISGameDrawObj);
    VptSetObjectList(_UISGame_pSubVpt, _UISGame_pSubObjList, 0);
    _UISGame_pSubObj = ObjNewInList(_UISGame_pSubObjList, 21, 0, 0);
    gUISSubInfo = fn_801D2B7C(fn_802188A0(6, 9, 64, 1, 128, 128), 0, 0);
    fn_802188D4(gUISSubInfo, 6, 9, 64, 1, 128, 128, (unsigned int)(gFrameTimeScale * 16.666668f));
    UISGameSetCallbacks(gUISSubInfo);
    UISGameEnableDraw(gUISSubInfo);
}

void UISGameCreateSub2(void)
{
    ViewportDesc_t desc;

    desc.mUnknown0 = 5;
    desc.mUnknown2 = 0;
    desc.mUnknown3 = 2;
    desc.mUnknown4[0] = 0;
    desc.mUnknown4[1] = 0;
    desc.mUnknown16 = fn_801CEA14();
    desc.mUnknown18 = fn_801CEA08();
    if (!FELoopIsMainFEActive() && (fn_8007F828(6) == 1 || fn_801CEB4C() == 1)) {
        desc.mUnknown16 = fn_801CEC74();
        desc.mUnknown18 = fn_801CEC7C();
    }
    _UISGame_pSub2Vpt = VptOpen(&desc);
    UISGameSetProjection(_UISGame_pSub2Vpt);
    _UISGame_pSub2Vpt->mUnknown28 &= ~1;
    VptSetEraseColor(_UISGame_pSub2Vpt, 0.0f, 0.0f, 0.0f);
    _UISGame_pSub2Cam = CamCreate(0, 0);
    CamFreeSetAngle(_UISGame_pSub2Cam, 0, 0x800000, 0x800000);
    CamFreeSetPos(_UISGame_pSub2Cam, 320.0f, 240.0f, -(240.0f / fn_801CFD28(0x100000)));
    CamAddCameraToViewport(_UISGame_pSub2Vpt, _UISGame_pSub2Cam);
    CamSetZScale(_UISGame_pSub2Cam, 4.0f);
    _UISGame_pSub2ObjList = ObjNewList(1, 336, 0, 0, 0, 1, 0, -1);
    ObjSetListObjFunc(_UISGame_pSub2ObjList, 21, 0, UISGameDrawObj);
    VptSetObjectList(_UISGame_pSub2Vpt, _UISGame_pSub2ObjList, 0);
    _UISGame_pSub2Obj = ObjNewInList(_UISGame_pSub2ObjList, 21, 0, 0);
    gUISSub2Info = fn_801D2B7C(fn_802188A0(6, 9, 64, 1, 128, 128), 0, 0);
    fn_802188D4(gUISSub2Info, 6, 9, 64, 1, 128, 128, (unsigned int)(gFrameTimeScale * 16.666668f));
    UISGameSetCallbacks(gUISSub2Info);
    UISGameEnableDraw(gUISSub2Info);
}

void UISGameTableEvent(void) {}

void UISGameInit(void)
{
    ResBankDesc_t desc;
    int i;
    int flag = MainFEGroupIsFirstStart(gMainFEGroup);
    int result = 0;

    _UISGame_iDrawMask = 0;
    fn_8021D880(UISGameRuntimeError);
    ObjNewType_(21, 20, 4, UISGameObjNew, UISGameObjDelete);
    desc.mUnknown0 = 1;
    desc.mUnknown4 = 15;
    desc.mUnknown8 = _UISGame_pszAllFile;
    UISResListSetup();
    fn_8021EF6C(UISGameTableEvent);
    if (!flag) {
        UISGameInitHook();
    }
    if (InGameIsPlaying()) {
        for (i = 0; i < 15; i++) {
            _UISGame_apszKeyFiles[i] = 0;
        }
        _UISGame_apszKeyFiles[1] = lbl_802EBE78;
        desc.mUnknown12 = _UISGame_apszKeyFiles;
    } else if (flag) {
        for (i = 0; i < 15; i++) {
            _UISGame_apszKeyFiles[i] = 0;
        }
        _UISGame_apszKeyFiles[1] = lbl_802EBE78;
        desc.mUnknown12 = _UISGame_apszKeyFiles;
    } else {
        desc.mUnknown12 = 0;
    }
    _UISGame_pCache = ResBankCreate(&desc);
    if (!FELoopIsMainFEActive()) {
        CamSetupAspect();
    }
    UISGameCreateSub();
    if (FELoopIsMainFEActive()) {
        UISGameCreateSub2();
    }
    UISGameCreateMain();
    UISModelObjInit();
    if (FELoopIsMainFEActive() && !flag) {
        fn_801D339C(-1);
        fn_801D342C(-1);
    }
    result = UISGameLoadItem(14, 0);
    fn_80218CB8(gUISMainInfo, result);
    if (FELoopIsMainFEActive()) {
        if (!flag) {
            UISGameRefKey(0);
            UISGameRefKey(1);
            UISGameRefKey(5);
            UISGameRefKey(6);
            UISGameRefKey(7);
            UISGameRefKey(8);
            UISGameRefKey(11);
            UISGameRefKey(12);
            UISGameRefKey(13);
            fn_802363B0(_UISGame_pMainVpt);
        }
        UISHeldObjEnable(1);
    } else if (InGameIsPlaying()) {
        GameModeTypeGet();
        fn_80047670(_UISGame_pMainObjList);
        BannerSetTickMs((unsigned int)(gFrameTimeScale * 16.666668f));
        UISHeldObjEnable(0);
        InGameStateReset();
        GameEventFlagsInit();
    }
    fn_80220D04();
    {
        unsigned char record;
        unsigned char index;

        for (record = 0; record < 8; record++) {
            for (index = 0; index < 10; index++) {
                _UISGame_aRepeat[record].mUnknown0[index] = 0.0f;
                _UISGame_aRepeat[record].mUnknown40[index] = 100;
            }
            _UISGame_aRepeat[record].mUnknown55 = 15;
            _UISGame_aRepeat[record].mUnknown54 = 100;
            _UISGame_aRepeat[record].mUnknown53 = 23;
            _UISGame_aRepeat[record].mUnknown52 = 5;
            _UISGame_aRepeat[record].mUnknown50 = 0;
        }
    }
}

void UISGameDestroyMain(void)
{
    UISGameShutdownHook();
    fn_80218A34(gUISMainInfo);
    fn_801D2BD0(gUISMainInfo);
    gUISMainInfo = 0;
    if (!FELoopIsMainFEActive()) {
        ScreenTransShutdown();
    }
    VptRemoveCallback(_UISGame_pMainVpt, DbgScreenRenderCallback);
    ObjRemoveFromList(_UISGame_pMainObjList, _UISGame_pMainObj);
    VptTrashObject(_UISGame_pMainObj);
    VptFlushObjectTrashSync();
    _UISGame_pMainObj = 0;
    ObjDelList(_UISGame_pMainObjList);
    _UISGame_pMainObjList = 0;
    CamDestroy(_UISGame_pMainCam);
    _UISGame_pMainCam = 0;
    VptClose(_UISGame_pMainVpt);
    _UISGame_pMainVpt = 0;
}

void UISGameDestroySub(void)
{
    fn_80218A34(gUISSubInfo);
    fn_801D2BD0(gUISSubInfo);
    gUISSubInfo = 0;
    ObjRemoveFromList(_UISGame_pSubObjList, _UISGame_pSubObj);
    VptTrashObject(_UISGame_pSubObj);
    VptFlushObjectTrashSync();
    _UISGame_pSubObj = 0;
    ObjDelList(_UISGame_pSubObjList);
    _UISGame_pSubObjList = 0;
    CamDestroy(_UISGame_pSubCam);
    _UISGame_pSubCam = 0;
    VptClose(_UISGame_pSubVpt);
    _UISGame_pSubVpt = 0;
}

void UISGameDestroySub2(void)
{
    fn_80218A34(gUISSub2Info);
    fn_801D2BD0(gUISSub2Info);
    gUISSub2Info = 0;
    ObjRemoveFromList(_UISGame_pSub2ObjList, _UISGame_pSub2Obj);
    VptTrashObject(_UISGame_pSub2Obj);
    VptFlushObjectTrashSync();
    _UISGame_pSub2Obj = 0;
    ObjDelList(_UISGame_pSub2ObjList);
    _UISGame_pSub2ObjList = 0;
    CamDestroy(_UISGame_pSub2Cam);
    _UISGame_pSub2Cam = 0;
    VptClose(_UISGame_pSub2Vpt);
    _UISGame_pSub2Vpt = 0;
}

void UISGameShutdown(void)
{
    int flag = MainFEGroupIsFirstStart(gMainFEGroup);

    if (FELoopIsMainFEActive()) {
        if (!flag) {
            fn_802363E0(_UISGame_pMainVpt);
        }
    } else if (InGameIsPlaying()) {
        fn_80047698();
        BannerEnd();
        InGameStateClearActive();
        GameEventFlagsShutdown();
    }
    if (FELoopIsMainFEActive()) {
        UISGameDestroySub2();
    }
    UISGameDestroySub();
    UISGameDestroyMain();
    UISGameFreeTable();
    UISModelObjShutdown();
    ResBankDestroy(_UISGame_pCache);
    _UISGame_pCache = 0;
    ObjDelType(21);
}

void UISGameSetLastPad(int a)
{
    _UISGame_iLastPad = a;
}

void UISGameHandleInput(int a, unsigned int id, float value)
{
    unsigned short unknown0 = 0;
    unsigned short unknown1 = 0;

    if (UISGameIsInputPad(a)) {
        _UISGame_iLastPad = a;
        switch (id) {
        case 8:
            id = 6;
            break;
        case 6:
            id = 8;
            break;
        case 0x39:
            id = 0x37;
            break;
        case 0x37:
            id = 0x39;
            break;
        }
        if (id == 8) {
            if (value == 1.0f && UISHeldObjIsEnabled()) {
                fn_80219650(gUISMainInfo, &unknown0, &unknown1);
                if (fn_8021D828(gUISMainInfo, unknown0, unknown1) && fn_8021A020(gUISMainInfo)) {
                    int result;

                    fn_80219A54(gUISMainInfo, 1);
                    result = fn_80219AF8(gUISMainInfo, unknown0, unknown1, 5);
                    if (result) {
                        UISHeldObjSet(result);
                    }
                }
            }
            if (value == 0.0f) {
                UISHeldObjSet(0);
            }
        }
        if (UISGameRepeatInput(&a, &id, &value)) {
            if ((id == 7 || id == 0) && FELoopIsMainFEActive()) {
                fn_8000FCD4(a);
            }
            fn_802196B4(gUISMainInfo, a, id, 1, &value, _UISGame_bInputFlag);
        }
    }
    if (UISGameIsEvent20Pending()) {
        fn_802196B4(gUISMainInfo, -1, 20, 1, &value, 1);
        UISGameSetEvent20Pending(0);
    }
}

void UISGameRefKey(int a)
{
    ResBankOpenFile(_UISGame_pCache, a);
}

void UISGameLoadKeyItem(int a, int b)
{
    ResBankOpenFile(_UISGame_pCache, a);
    ResBankLoad(_UISGame_pCache, a, b, 0);
}

void UISGameFreeKeyItem(int a, int b)
{
    ResBankUnload(_UISGame_pCache, a, b);
}

void UISGameRefreshAll(void)
{
    if (gUISMainInfo) {
        fn_80219A54(gUISMainInfo, 1);
    }
    if (gUISSub2Info) {
        fn_80219A54(gUISSub2Info, 1);
    }
    if (gUISSubInfo) {
        fn_80219A54(gUISSubInfo, 1);
    }
}

void UISGameLockPad(int a)
{
    _UISGame_iLockedPad = a;
}

int UISGameUnlockPad(void)
{
    int value = _UISGame_iLockedPad;

    _UISGame_iLockedPad = -1;
    return value;
}

void UISGamePresentFrame(void)
{
    if (!VptIsProcessing()) {
        if (FELoopIsMainFEActive()) {
            BootHandleReset();
        }
        VptProcessViewports();
        SndgUpdate(1);
        fn_801CE82C();
    }
}

void UISGameSetAspect(Viewport_t *pObject, int mode)
{
    float aspect = 4.0f / 3.0f;

    switch (mode) {
    case 0:
        break;
    case 1:
    case 2:
        aspect = 16.0f / 9.0f;
        break;
    }
    VptSetPerspective(pObject, 45.0f, aspect, 0.1f, 1500.0f);
}

Viewport_t *UISGameGetMainViewport(void)
{
    return _UISGame_pMainVpt;
}

void UISGameEnableDraw(void *p)
{
    if (p == gUISMainInfo) {
        _UISGame_iDrawMask |= 1;
    } else if (p == gUISSubInfo) {
        _UISGame_iDrawMask |= 2;
    } else if (p == gUISSub2Info) {
        _UISGame_iDrawMask |= 4;
    }
}

void UISGameSetEvent20Pending(unsigned char value)
{
    _UISGame_bEvent20Pending = value;
}

unsigned char UISGameIsEvent20Pending(void)
{
    return _UISGame_bEvent20Pending;
}

void UISGameSetInputFlag(unsigned char value)
{
    _UISGame_bInputFlag = value;
}

void UISGameSetDrawMode(int a)
{
    fn_80220CDC(a);
    fn_80220CFC(a);
    GlibRenderSelectBin(GlibRenderGetBin(14));
}
}
