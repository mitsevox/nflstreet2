// Memory card screens: the UI script functions behind the save, load, delete,
// format and card-check screens. They pick the card slot, select save files,
// start card operations and hand the results back to the screen scripts.
#include "game/fn_8007F6F8.h"
#include "game/FELoop.h"
#include "game/cu_8007F12C.h"
#include "game/Callees_801D57E0.h"
#include "game/MemCardUI.h"
#include "game/Callees_8002A138.h"
#include "game/fn_8007F828.h"
#include "game/TextRecord.h"
#include "game/MemCardMsg.h"
#include "game/UISGameMsg.h"

struct MemCardUIName_t {
    char mUnknown0[8];
    const char *mpUnknown8;
};

struct MemCardUIArgs_t {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknownC;
    char mUnknown10[3];
    unsigned char mUnknown13;
};

extern "C" {
unsigned int fn_801D6724(void);
unsigned int fn_801D6730(void);
void fn_801D6754(int a);
void fn_801D689C(const char *pSuffix, const char *pPrefix, int unused, int selector, char *pOut, int size);
int fn_801D6AC8(int a);
int fn_801D6B14(int a);
unsigned int fn_801D85A8(int a);
int fn_801D4400(int *pA, int *pB);
int fn_801D46E8(int slot);
char *fn_801C2EF0(char *pDst, const char *pSrc, int size);
int fn_801F7ABC(void);
void fn_801F8838(void);
void FeatClearEAGameSaves(void);
void FeatSetEAGameSave(short a);
void FeatGetEAGameCode(short a, char *pBuf);
unsigned int fn_80029838(int a);
int fn_80029B48(int a);
void fn_80029E6C(int a, int b);
void fn_8002A238(int a, int b, int slot, int index);
void fn_8002A260(int a, int b, char *pBuf, int size);
void fn_8002A44C(int a, int b);
void fn_8002A49C(int a);
void fn_8002A5C4(void);
void fn_8002A5F0(int a, char *pBuf, int b);
int fn_8002A824(void);
void fn_80187FD0(void);
void fn_80187FDC(void);
int fn_80029D74(int type, int index);
void fn_80029CE0(int type, int index);
void fn_80029D28(int type, int index);
int fn_8002A130(int a, int b);
int fn_8002A2A4(int type, int index);
int fn_8002A86C(int value, int type, const char *name, unsigned int *pIndex);
int MemCardUtilGetSaveType(int a);
void MemCardGetNewSaveSpace(int *pA, int *pB);
int fn_801D6850(void);
}

static void (*_MemCardUI_pEnterCallback)(int, int *) = 0;
static void (*_MemCardUI_pExitCallback)() = 0;
static int (*_MemCardUI_pCheckCallback)(int *, int *, int *, int *) = 0;
static void (*_MemCardUI_pLoadCallback)(int, int) = 0;
static int (*_MemCardUI_pSelectCallback)(int, int) = 0;
static unsigned char _MemCardUI_bUnused = 0;
static unsigned char _MemCardUI_bTimeMarked = 0;
static int _MemCardUI_iPortStep = 0;
static unsigned char _MemCardUI_bProbePending = 0;
static int _MemCardUI_iSavePort = -1;
static unsigned char _MemCardUI_bScriptFlag = 0;
static unsigned char _MemCardUI_bResetLock = 0;
static unsigned char _MemCardUI_bTeamFlag = 0;
static int _MemCardUI_iMarkTime;

extern "C" {

int MemCardUIEmptyHandler(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult)
{
    return 0;
}

void MemCardUIStart(int a, int *pB, int *pC)
{
    int unused;

    fn_801D65B4(0);
    fn_801D654C(1);
    fn_801D6714(0);
    FeatClearEAGameSaves();
    if (_MemCardUI_pEnterCallback != 0) {
        _MemCardUI_pEnterCallback(a, &unused);
    }
    *pB = fn_8002A824();
    *pC = 3;
}

void MemCardUIStartNoSizes(int a, int *pB)
{
    fn_801D65B4(0);
    fn_801D654C(1);
    fn_801D6714(0);
    if (_MemCardUI_pEnterCallback != 0) {
        _MemCardUI_pEnterCallback(a, pB);
    }
}

void MemCardUIResetIdle(void)
{
    fn_801D65B4(0);
    fn_801D654C(1);
    fn_801D6714(0);
}

void MemCardUIExit(void)
{
    if (fn_801D671C() >= 0 && fn_801D671C() <= 1) {
        fn_801D6680(fn_801D671C());
    }
    fn_801D6714(-1);
    if (_MemCardUI_pExitCallback != 0) {
        _MemCardUI_pExitCallback();
    }
}

int MemCardUIRunCheckCallback(int *p0, int *p4, int *p8, int *p12)
{
    int result = 0;

    if (_MemCardUI_pCheckCallback != 0) {
        result = _MemCardUI_pCheckCallback(p0, p4, p8, p12);
    }
    if (result != 0) {
        result = 1;
    } else {
        if (fn_801D671C() >= 0 && fn_801D671C() <= 1) {
            fn_801D6680(fn_801D671C());
        }
        result = 0;
    }
    return result;
}

int MemCardUIFindNthFile(int a, int count)
{
    int i;

    for (i = 0; i < fn_801D6B14(a); i++) {
        if (fn_801D6B74((signed char)i, a, 0, 0, 0, 0, 0) != 0) {
            count--;
        }
        if (count < 0) {
            break;
        }
    }
    return i;
}

int MemCardUIProbePort(unsigned int slot)
{
    if (slot <= 1 && slot != fn_801D671C()) {
        fn_801D6714(slot);
        fn_801D6650(8);
        return 1;
    }
    return 0;
}

int MemCardUIProbeNextPort(int a)
{
    if (a != 0) {
        if (fn_801D671C() != 0) {
            return 0;
        }
        fn_801D6714(1);
    }
    fn_801D6650(8);
    return 1;
}

void MemCardUIGetMessageText(int value, MemCardMsgText_t *pA, MemCardMsgText_t *pB, MemCardMsgText_t *pC)
{
    MemCardMsgGetText(value, pA, pB, pC);
}

void MemCardUIUnmountAndClearChanges(void)
{
    int a = 0;
    int b = 0;

    if (fn_801D671C() >= 0 && fn_801D671C() <= 1) {
        fn_801D6680(fn_801D671C());
    }
    fn_801D4400(&a, &b);
}

int MemCardUIHasPortChanged(void)
{
    int a = 0;
    int b = 0;
    int result = fn_801D4400(&a, &b);
    int slot = fn_801D671C();

    if (result != 0) {
        result = ((a | b) >> slot) & 1;
    }
    return result;
}

void MemCardUIUnmountPort(void)
{
    if (fn_801D671C() >= 0 && fn_801D671C() <= 1) {
        fn_801D6680(fn_801D671C());
    }
}

void MemCardUIStartFormat(void)
{
    fn_801D6650(2);
}

void MemCardUIStartMount(void)
{
    int a;
    int b;

    fn_801D4400(&a, &b);
    fn_801D6650(9);
}

void MemCardUIStartCheck(void)
{
    fn_801D6650(11);
}

void MemCardUIDeleteFile(int a, int index)
{
    char other[32];
    char name[32];

    fn_801D6754(a);
    fn_801D6B74((signed char)index, a, name, 32, 0, -1, 0);
    fn_801D6C70((signed char)index, a, other, 32);
    fn_801D67E4(name, other);
    fn_801D6838(index);
    fn_801D6650(6);
}

int MemCardUIGetFileCount(int a)
{
    fn_801D6754(a);
    return fn_801D6AC8(a);
}

void MemCardUIScanFiles(int a)
{
    fn_801D685C("GN7E-69", 0);
    fn_801D6650(7);
}

int MemCardUILoadFile(int a, int index)
{
    char other[32];
    char name[32];

    fn_801D6754(a);
    if (fn_801D6B74((signed char)index, a, name, 32, 0, -1, 0) != 0) {
        fn_801D6C70((signed char)index, a, other, 32);
        fn_801D67E4(name, other);
        fn_801D6838(index);
        if (_MemCardUI_pLoadCallback != 0) {
            _MemCardUI_pLoadCallback(a, index);
        }
        fn_8002A5C4();
        return 1;
    }
    return 0;
}

int MemCardUISelectFile(int a, int index)
{
    char other[32];
    char name[32];
    int result = 0;

    fn_801D6754(a);
    fn_801D6B74((signed char)index, a, name, 32, 0, -1, 0);
    fn_801D6C70((signed char)index, a, other, 32);
    fn_801D67E4(0, other);
    fn_801D6838(index);
    if (_MemCardUI_pSelectCallback != 0) {
        result = _MemCardUI_pSelectCallback(a, index);
    }
    return result;
}

int MemCardUIPollResult(int a)
{
    return fn_80029B48(a);
}

int MemCardUISelectMarkedFile(int a, int index)
{
    char name[17];
    int result = fn_801D6DA8(index, a);

    if (result != 0) {
        fn_801D6B74((signed char)index, a, name, 17, 0, 0, 0);
        fn_801D67E4(name, 0);
    }
    return result;
}

void MemCardUIQueryFreeSpace(void)
{
    fn_801D6650(12);
}

void MemCardUIRequeryFreeSpace(void)
{
    fn_801D6650(13);
}

void MemCardUIScanOtherGame(int a)
{
    if (a <= 5) {
        char name[8];

        FeatGetEAGameCode(a, name);
        fn_801D685C(name, 1);
        fn_801D6650(10);
    }
}

void MemCardUIRestoreGameCode(void)
{
    fn_801D46E8(fn_801D671C());
    fn_801D685C("GN7E-69", 0);
}

void MemCardUIRescanFiles(void)
{
    fn_801D6650(14);
}

int MemCardUIGetOtherGameIndex(int a)
{
    if (a <= 5) {
        return a;
    }
    return -1;
}

void MemCardUIMarkOtherGameFound(int a, int b)
{
    if (b > 0) {
        FeatSetEAGameSave(a);
    }
}

void MemCardUIResetGame(void)
{
    fn_80187FD0();
    fn_80187FDC();
}

void MemCardUIReturnToMenu(void)
{
    fn_801F8838();
}

int MemCardUIIsNameFree(int a, const char *pName)
{
    unsigned char flag;

    return fn_801D6CF4(pName, a, &flag) == -1;
}

int MemCardUISaveFile(int a, int index, int b)
{
    char path[32];
    char name[32];
    int ok = 0;
    unsigned char flag = 0;

    fn_8002A44C(a, b);
    fn_8002A260(a, b, path, 32);
    if (a == 1) {
        ok = fn_801D6CF4("Options", 1, &flag) >= 0;
    } else if (fn_8002A138(a, b) != 0) {
        ok = fn_801D6CF4(path, a, &flag) >= 0;
    } else if (fn_801D6B74((signed char)index, a, 0, 0, 0, -1, &flag) == 0 || flag != 0) {
        fn_8002A5F0(a, path, 0);
    }
    fn_801D689C(path, "GN7E-69", (signed char)index, a, name, 32);
    fn_801D67E4(path, name);
    fn_801D6838(index);
    fn_8002A49C(ok);
    return 1;
}

int MemCardUISaveOverFile(int a, int index, int b)
{
    char name[32];
    char other[32];
    int result;

    fn_8002A44C(a, b);
    result = fn_801D6B74((signed char)index, a, name, 32, 0, -1, 0);
    if (result != 0) {
        fn_801D6C70((signed char)index, a, other, 32);
        fn_801D67E4(name, other);
        fn_801D6838(index);
        fn_8002A49C(result);
    }
    return result;
}

void MemCardUIFinish(void)
{
    if (fn_801D671C() >= 0 && fn_801D671C() <= 1) {
        fn_801D6680(fn_801D671C());
    }
    fn_801D6714(-1);
    if (_MemCardUI_pExitCallback != 0) {
        _MemCardUI_pExitCallback();
    }
}

int MemCardUICheckSaveSpace(int a, int b, int *pError)
{
    int ok = 1;
    int index = 0;
    int i;

    if (fn_801D6730() < fn_801D85A8(a)) {
        *pError = 0x73;
        ok = 0;
    }
    if (fn_801D6724() < fn_80029838(a)) {
        *pError = 0x40;
        ok = 0;
    }
    if (ok) {
        for (i = 0; i < fn_801D6B14(a); i++) {
            if (fn_801D6B74((signed char)i, a, 0, 0, 0, 0, 0) == 0) {
                break;
            }
        }
        if (i < fn_801D6B14(a)) {
            index = i;
        } else {
            *pError = 0x13;
            ok = 0;
        }
        if (ok) {
            fn_8002A238(a, b, fn_801D671C(), index);
        }
    }
    return ok;
}

void MemCardUIReleaseSlot(int a, int b)
{
    if (fn_8007F828(12) == 1) {
        fn_8007F6F8(12, 0);
        fn_80029E6C(a, b);
    }
}

void MemCardUIGetTitle(TextRecord_t *pRecord)
{
    char name[32];

    fn_801D6B24(name, 32);
    fn_801C2EF0(pRecord->mUnknown8, name, pRecord->mUnknown4);
}

void MemCardUIProbeSlot(int slot)
{
    fn_801D6714(slot);
    fn_801D6650(8);
}

int MemCardUIStepPort(int slot, int step, int *pSlot)
{
    unsigned int next = slot + step;

    if (step != 0 && next > 1) {
        next = step < 0;
    }
    *pSlot = next;
    return 1;
}

void MemCardUIBeginPortScan(int a, int slot)
{
    fn_801D65B4(0);
    fn_801D654C(1);
    _MemCardUI_iPortStep = a;
    if (a == 0) {
        _MemCardUI_bProbePending = 1;
    }
    fn_801D6714(slot);
}

void MemCardUIStartScan(int a, int *pB, int c, int d, int e)
{
    fn_801D6754(c);
    if (e != 0) {
        MemCardUIBeginPortScan(d, 0);
    } else {
        MemCardUIBeginPortScan(d, fn_801D671C());
    }
    if (_MemCardUI_pEnterCallback != 0) {
        _MemCardUI_pEnterCallback(a, pB);
    }
}

int MemCardUIProbeNext(int *pSlot)
{
    int slot;

    if (_MemCardUI_bProbePending) {
        fn_801D6650(8);
        _MemCardUI_bProbePending = 0;
        *pSlot = fn_801D671C();
    } else if (MemCardUIStepPort(fn_801D671C(), _MemCardUI_iPortStep, &slot) != 0) {
        fn_801D6714(slot);
        fn_801D6650(8);
        *pSlot = slot;
        return 1;
    } else {
        return 0;
    }
    return 1;
}

void MemCardUIGetSlotName(int a, TextRecord_t *pRecord)
{
    fn_801D57E0(a, pRecord->mUnknown8, pRecord->mUnknown4);
}

void MemCardUIGetSavePort(int a, int b, int *pOut)
{
    int result = fn_8002A190(a, b);

    if (result == -1) {
        result = 0;
    }
    *pOut = result;
}

int MemCardUIGetPort(void)
{
    return fn_801D671C();
}

void MemCardUISetPort(int slot)
{
    fn_801D6714(slot);
}

void MemCardUISetTitleFromSlot(int a, int b)
{
    char name[24];

    fn_8002A260(a, b, name, 32);
    fn_801D67E4(name, 0);
}

void MemCardUISetCallbacks(MemCardListCallbacks_t *pCallbacks)
{
    _MemCardUI_pEnterCallback = pCallbacks->mUnknown0;
    _MemCardUI_pExitCallback = pCallbacks->mUnknown4;
    _MemCardUI_pCheckCallback = pCallbacks->mUnknown8;
    _MemCardUI_pLoadCallback = pCallbacks->mUnknown12;
    _MemCardUI_pSelectCallback = pCallbacks->mUnknown16;
}

void MemCardUIClearCallbacks()
{
    _MemCardUI_pEnterCallback = 0;
    _MemCardUI_pExitCallback = 0;
    _MemCardUI_pCheckCallback = 0;
    _MemCardUI_pLoadCallback = 0;
    _MemCardUI_pSelectCallback = 0;
}

int MemCardUIIsTimeMarkCurrent(void)
{
    return fn_801F7ABC() == _MemCardUI_iMarkTime;
}

void MemCardUISetTimeMark(int enable)
{
    if (enable != 0) {
        if (!_MemCardUI_bTimeMarked) {
            _MemCardUI_iMarkTime = fn_801F7ABC();
        }
        _MemCardUI_bTimeMarked = 1;
    } else {
        _MemCardUI_bTimeMarked = 0;
    }
}

void MemCardUISetScriptFlag(unsigned char value)
{
    _MemCardUI_bScriptFlag = value;
}

unsigned char MemCardUIGetScriptFlag(void)
{
    return _MemCardUI_bScriptFlag;
}

int MemCardUIIsResetLocked(void)
{
    return _MemCardUI_bResetLock;
}

unsigned char MemCardUIGetTeamFlag(void)
{
    return _MemCardUI_bTeamFlag;
}

int MemCardUIHandleFunction(unsigned int id, MemCardUIArgs_t *pParams, int c, int *pResult)
{
    switch (id) {
    case 331:
        MemCardUISetTimeMark(0);
        break;
    case 332:
        *pResult = MemCardUIIsTimeMarkCurrent();
        break;
    case 333:
        MemCardUISetTimeMark(1);
        break;
    case 335:
        MemCardUIStart(pParams->mUnknown0, (int *)pParams->mUnknown4, (int *)pParams->mUnknown8);
        break;
    case 338:
        MemCardUIStartNoSizes(pParams->mUnknown0, (int *)pParams->mUnknown4);
        break;
    case 340:
        MemCardUIExit();
        break;
    case 297:
        MemCardUIResetIdle();
        break;
    case 336:
        *pResult = MemCardUIProbeNextPort(pParams->mUnknown0);
        break;
    case 337:
        *pResult = MemCardUIProbePort(pParams->mUnknown0);
        break;
    case 339:
        MemCardUIGetMessageText(pParams->mUnknown0, (MemCardMsgText_t *)pParams->mUnknown4,
                     (MemCardMsgText_t *)pParams->mUnknown8, (MemCardMsgText_t *)pParams->mUnknownC);
        break;
    case 341:
        *pResult = MemCardUIRunCheckCallback((int *)pParams->mUnknown0, (int *)pParams->mUnknown4, (int *)pParams->mUnknown8,
                               (int *)pParams->mUnknownC);
        break;
    case 342:
        *pResult = MemCardUISelectMarkedFile(pParams->mUnknown0, pParams->mUnknown4);
        break;
    case 343:
        MemCardUILoadFile(pParams->mUnknown0, pParams->mUnknown4);
        break;
    case 348:
        *pResult = MemCardUtilGetSaveType(pParams->mUnknown0);
        break;
    case 349:
        MemCardUIUnmountAndClearChanges();
        break;
    case 350:
        *pResult = MemCardUIHasPortChanged();
        break;
    case 351:
        MemCardUIStartFormat();
        break;
    case 352:
        MemCardUIUnmountPort();
        break;
    case 353:
        *pResult = MemCardUIPollResult(pParams->mUnknown0);
        break;
    case 356:
        MemCardUIStartMount();
        break;
    case 354:
        MemCardUIStartCheck();
        break;
    case 355:
        MemCardUIQueryFreeSpace();
        break;
    case 357:
        MemCardUIRequeryFreeSpace();
        break;
    case 358:
        MemCardUIScanFiles(pParams->mUnknown0);
        break;
    case 359:
        *pResult = MemCardUISelectFile(pParams->mUnknown0, pParams->mUnknown4);
        break;
    case 360:
        *pResult = MemCardUIGetFileCount(pParams->mUnknown0);
        break;
    case 361:
        *pResult = MemCardUIFindNthFile(pParams->mUnknown0, pParams->mUnknown4);
        break;
    case 362:
        MemCardUIDeleteFile(pParams->mUnknown0, pParams->mUnknown4);
        break;
    case 363:
        MemCardUIScanOtherGame(pParams->mUnknown0);
        break;
    case 147:
        MemCardUIRescanFiles();
        break;
    case 381:
        *pResult = MemCardUIGetOtherGameIndex(pParams->mUnknown0);
        break;
    case 382:
        MemCardUIMarkOtherGameFound(pParams->mUnknown0, pParams->mUnknown4);
        break;
    case 364:
        MemCardUIResetGame();
        break;
    case 408:
        MemCardUIReturnToMenu();
        break;
    case 365:
        MemCardUIRestoreGameCode();
        break;
    case 376:
        MemCardUIFinish();
        break;
    case 377:
        *pResult = MemCardUISaveOverFile(pParams->mUnknown0, pParams->mUnknown4, pParams->mUnknown8);
        break;
    case 404:
        *pResult = MemCardUISaveFile(pParams->mUnknown0, pParams->mUnknown4, pParams->mUnknown8);
        break;
    case 383:
        *pResult = MemCardUICheckSaveSpace(pParams->mUnknown0, pParams->mUnknown4, (int *)pParams->mUnknown8);
        break;
    case 384:
        MemCardUIReleaseSlot(pParams->mUnknown0, pParams->mUnknown4);
        break;
    case 394:
        _MemCardUI_bScriptFlag = pParams->mUnknown0;
        break;
    case 395:
        *pResult = _MemCardUI_bScriptFlag;
        break;
    case 504:
        *pResult = 0;
        if (FELoopIsMainFEActive() != 0) {
            int type = pParams->mUnknown0;
            int index = pParams->mUnknown4;
            char name[17];

            fn_801D6754(type);
            *pResult = fn_80029D74(type, index);
            if (*pResult != 0) {
                fn_8002A44C(type, index);
                fn_8002A260(type, index, name, sizeof(name));
                if (fn_8002A138(type, index) == 0) {
                    fn_8002A5F0(type, name, 0);
                }
                fn_801D67E4(name, 0);
            }
        }
        break;
    case 344:
        *pResult = 1;
        break;
    case 345:
        *pResult = 1;
        break;
    case 346:
        *pResult = 1;
        break;
    case 347:
        *pResult = 1;
        break;
    case 506:
        *pResult = 1;
        break;
    case 513:
        fn_80029CE0(pParams->mUnknown0, pParams->mUnknown4);
        break;
    case 524:
        MemCardUIGetSavePort(pParams->mUnknown0, pParams->mUnknown4, &_MemCardUI_iSavePort);
        *pResult = fn_8002A130(pParams->mUnknown0, pParams->mUnknown4);
        break;
    case 530:
        MemCardGetNewSaveSpace((int *)pParams->mUnknown0, (int *)pParams->mUnknown4);
        break;
    case 531:
        if (fn_801D671C() >= 0 && fn_801D671C() <= 1) {
            fn_801D6680(fn_801D671C());
        }
        fn_801D6714(-1);
        if (fn_801D6850() == 1) {
            fn_8007F374();
        }
        break;
    case 532:
        fn_801D654C(0);
        if (fn_801D6850() == 1) {
            fn_8007F328(0);
        }
        break;
    case 316:
        fn_801D654C(0);
        break;
    case 307:
        *pResult = 3000;
        break;
    case 306:
        *pResult = 0;
        break;
    case 323:
        *pResult = fn_8002A2A4(pParams->mUnknown0, pParams->mUnknown4);
        break;
    case 533:
        fn_80029D28(pParams->mUnknown0, pParams->mUnknown4);
        break;
    case 34:
        MemCardUIGetTitle((TextRecord_t *)pParams->mUnknown0);
        break;
    case 318:
        MemCardUISetTitleFromSlot(pParams->mUnknown0, pParams->mUnknown4);
        break;
    case 39:
        *pResult = fn_8002A86C(pParams->mUnknown0, pParams->mUnknown4, ((MemCardUIName_t *)pParams->mUnknown8)->mpUnknown8,
                               (unsigned int *)pParams->mUnknownC);
        break;
    case 92:
        MemCardUIProbeSlot(pParams->mUnknown0);
        break;
    case 131:
        MemCardUIStartScan(pParams->mUnknown0, (int *)pParams->mUnknown4, pParams->mUnknown8, pParams->mUnknownC,
                    pParams->mUnknown13);
        break;
    case 130:
        *pResult = MemCardUIProbeNext((int *)pParams->mUnknown0);
        break;
    case 186:
        MemCardUIGetSlotName(pParams->mUnknown0, (TextRecord_t *)pParams->mUnknown4);
        break;
    case 159:
        MemCardUIBeginPortScan(pParams->mUnknown0, pParams->mUnknown4);
        break;
    case 185:
        MemCardUIGetSavePort(pParams->mUnknown0, pParams->mUnknown4, (int *)pParams->mUnknown8);
        break;
    case 247:
        *pResult = MemCardUIGetPort();
        break;
    case 246:
        MemCardUISetPort(pParams->mUnknown0);
        break;
    case 196:
        MemCardUIStepPort(pParams->mUnknown0, pParams->mUnknown4, (int *)pParams->mUnknown8);
        break;
    case 402:
        _MemCardUI_bResetLock = pParams->mUnknown0;
        break;
    case 403:
        _MemCardUI_bTeamFlag = pParams->mUnknown0;
    default:
        return 0;
    }
    return 1;
}
}
