/* Console start-up: the intro movies, the progressive-scan display prompt, the reset button while the front end runs, and the layout of the memory pools. */

#include <dolphin/vi.h>
#include "game/Entry_80219044.h"
#include "engine/cu_80227F14.h"
#include "game/fn_801801F0.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801EEB44.h"
#include "game/fn_80218FC4.h"
#include <string.h>
#include <dolphin/os/OSResetSW.h>

#include "game/MemPoolDesc.h"
#include <dolphin/os.h>

extern "C" {
extern char lbl_800034A0[];
extern char lbl_802EC09C[];
extern void *lbl_803EB688;
extern unsigned char lbl_803EBD6C;
extern unsigned char lbl_803EBD6D;
extern unsigned char lbl_803EBD6E;
extern unsigned char lbl_803EBD6F;
extern unsigned char lbl_803EBD70;
extern int lbl_803ED5EC;

int ChallengeGoalCheckMargin(int side, int limit, int flag);
int fn_80063AA0(void);
int fn_80185274(void);
void fn_8018A740(void);
int fn_801C1D54(void);
void fn_801C1D84(void);
int fn_801C601C(int a);
int fn_801C60BC(int a);
void fn_801CAF24(void);
void fn_801CE248(int a);
void fn_801CE82C(void);
int fn_801CE944(int a);
int fn_801CEA08(void);
void fn_801CEA84(void);
void fn_801CEADC(int a);
int fn_801CEC84(void);
void fn_801D6F58(void);
void fn_801D9360(int a, int b, int c, int (*pCallback)(int), int d);
int fn_801D9494(void (*pCallback)(void));
void fn_801DA46C(void);
int fn_801E15D0(int a);
int fn_801E17D0(int a, struct PerDeviceData *pState);
int fn_801E194C(void);
int fn_801E195C(int a);
unsigned int fn_801E19B4(int a);
void fn_801E1C38(unsigned char a);
int fn_801E1CE0(unsigned char a);
int fn_801F687C(int a, int b, int c, void *pBuffer, int size);
void fn_801F6AC8(int a, int b, int c, int d, int e);
void fn_801F6B84(int a);
int fn_801F6CE8(int a, int b);
int fn_801F6D54(int a, struct MovieStreamDesc *pDesc, int b, int c);
int fn_801F8758(int a);
void fn_801F8768(void);
void fn_801F87FC(int a);
int fn_80219044(void *p, int a, int b, int c, struct Entry_80219044 **ppEntries);
void fn_802195E4(void *p, short a, short b);
void fn_80219650(void *p, unsigned short *pA, unsigned short *pB);
void fn_80239CEC(int a, int b);
int fn_8023CF60(void);
void fn_8023CFD0(int a);
int fn_8024151C(void);
}

/* Filled by fn_801E17D0; the byte array at +8 is indexed by lbl_803ED5EC + 1. */
struct PerDeviceData {
    unsigned char mUnknown0[8];
    unsigned char mUnknown8[24];
};

/* Second argument of fn_801F6D54. */
struct MovieStreamDesc {
    void *mpUnknown0;
    int mUnknown4;
};

static char _Boot_szBlankLine[] = " ";
static void (*_Boot_pPrevResetCallback)(void) = 0;
static unsigned char _Boot_bResetPressed = 0;
static unsigned char _Boot_bMovieAbort;
static void *_Boot_pMovieFile;
static Entry_80219044 *_Boot_apMessageLines[3];
static Entry_80219044 _Boot_aMessageLines[3];
static char _Boot_szProgressiveMode[] = "Screen display has been set to\nProgressive Mode.";
static char _Boot_szInterlacedMode[] = "Screen display has been set to Interlaced Mode.";
static char _Boot_szContinue[] = "|^Continue";

extern "C" {
/* Runs frames until the first id reported by fn_80219650 for p is no longer a. */
static void _BootWaitForScreen(void *p, unsigned short a, unsigned short b, int unused)
{
    unsigned short current = a;
    unsigned short other = b;

    while (current == a) {
        fn_8018A740();
        fn_801C601C(-1);
        fn_801C60BC(-1);
        fn_801D6F58();
        fn_802285CC();
        fn_801CAF24();
        fn_801CE82C();
        fn_80219650(p, &current, &other);
    }
}

static void _BootDelay(void)
{
    unsigned int i;

    for (i = 0; i < 60; i++) {
        fn_801C601C(-1);
        fn_801C60BC(-1);
        fn_802285CC();
        fn_801CAF24();
        fn_801CE82C();
    }
}

/* Shows the progressive/interlaced display-mode message. */
static void _BootProgressiveCheck(void)
{
    unsigned int i = 0;
    PerDeviceData *pState = (PerDeviceData *)fn_801D2B7C(fn_801E194C(), 0, 0);
    int found = fn_8023CF60() == 1;

    for (; !found && i < 4; i++) {
        if (fn_801E195C(i) == 2) {
            fn_801E15D0(i);
            fn_801E17D0(i, pState);
            if (lbl_803EBD6D & pState->mUnknown8[lbl_803ED5EC + 1]) {
                found = 1;
            }
        }
    }
    fn_801D2BD0(pState);
    if (VIGetDTVStatus() && found) {
        void *p;

        fn_801801F0(1);
        p = lbl_803EB688;
        fn_80218FC4(p, 1, 0xE, 0, 0);
        fn_802195E4(p, 1, 0xE);
        _BootWaitForScreen(p, 1, 0xE, -1);
        _Boot_aMessageLines[0].mUnknown0 = 0;
        _Boot_aMessageLines[0].mpText = _Boot_szBlankLine;
        _Boot_aMessageLines[0].mLength = strlen(_Boot_aMessageLines[0].mpText) + 1;
        _Boot_aMessageLines[1].mUnknown0 = 0;
        if (fn_80063AA0() == 1) {
            _Boot_aMessageLines[1].mpText = _Boot_szProgressiveMode;
        } else {
            _Boot_aMessageLines[1].mpText = _Boot_szInterlacedMode;
        }
        _Boot_aMessageLines[1].mLength = strlen(_Boot_aMessageLines[1].mpText) + 1;
        _Boot_aMessageLines[2].mUnknown0 = 0;
        _Boot_aMessageLines[2].mpText = _Boot_szContinue;
        _Boot_aMessageLines[2].mLength = strlen(_Boot_aMessageLines[2].mpText) + 1;
        _Boot_apMessageLines[0] = &_Boot_aMessageLines[0];
        _Boot_apMessageLines[1] = &_Boot_aMessageLines[1];
        _Boot_apMessageLines[2] = &_Boot_aMessageLines[2];
        fn_80219044(lbl_803EB688, 1, 3, 3, _Boot_apMessageLines);
        _BootWaitForScreen(lbl_803EB688, 1, 3, -1);
        fn_801801F0(0);
    } else {
        fn_8023CFD0(0);
    }
}

static void _BootResetCallback(void)
{
    if ((unsigned char)OSGetResetButtonState()) {
        _Boot_bResetPressed = 1;
    } else {
        OSSetResetCallback(_BootResetCallback);
    }
}

static unsigned char _BootPlayMovie(int index, int a, int b, int c, int d, void *pBuffer, int e);

void BootPlayIntroMovies(void)
{
    _BootPlayMovie(0, 0, 0, 0, 0, 0, 0);
    _BootPlayMovie(2, 0, 0, 0, 0, 0, 0);
    _BootPlayMovie(1, 1, 0, 0, 0, 0, 0);
}

void BootShowStartupScreens(void)
{
    void *p = lbl_803EB688;

    fn_801CE248(1);
    _BootDelay();
    _BootProgressiveCheck();
    fn_80218FC4(p, 1, 4, 0, 0);
    fn_802195E4(p, 1, 4);
    _BootWaitForScreen(p, 1, 4, -1);
    fn_801CE248(0);
}

void BootInstallResetCallback(void)
{
    _Boot_pPrevResetCallback = OSSetResetCallback(_BootResetCallback);
}

void BootHandleReset(void);

void BootUpdateReset(void)
{
    BootHandleReset();
}

void BootRemoveResetCallback(void)
{
    OSSetResetCallback(_Boot_pPrevResetCallback);
    _Boot_pPrevResetCallback = 0;
}

void BootHandleReset(void)
{
    int previous = fn_801F8758(1);

    if (previous && !fn_80185274() && _Boot_bResetPressed) {
        if (!OSGetResetButtonState()) {
            fn_801F87FC(0);
            _Boot_bResetPressed = 0;
        }
    }
    fn_801F8758(previous);
}

/* Sets the base (+12) and size (+16) words of the eight memory records. */
void BootSetupMemPools(void)
{
    MemPoolDesc_t *pState = MemPoolGetDesc(4);
    MemPoolDesc_t *pDb = MemPoolGetDesc(2);
    MemPoolDesc_t *pMain = MemPoolGetDesc(1);
    MemPoolDesc_t *pDebug = MemPoolGetDesc(8);
    MemPoolDesc_t *pMisc = MemPoolGetDesc(0x20);
    MemPoolDesc_t *pAuxRam = MemPoolGetDesc(0x10);
    MemPoolDesc_t *pUnload = MemPoolGetDesc(0x40);
    MemPoolDesc_t *pSound = MemPoolGetDesc(0x100);
    unsigned int limit = 0x1800000;
    int lo = (int)OSGetArenaLo();
    int hi = (int)OSGetArenaHi();
    unsigned int top = hi - 0x80000000;
    unsigned int end;

    if (limit > top) {
        limit = top;
    }
    end = limit + 0x80000000;
    pSound->mUnknownC = lo;
    pSound->mUnknown10 = 0x3800;
    pState->mUnknownC = pSound->mUnknownC + pSound->mUnknown10;
    pState->mUnknown10 = 0x44000;
    pDb->mUnknown10 = 0x104000;
    pDb->mUnknownC = 0x7E000000;
    pMisc->mUnknownC = pState->mUnknownC + pState->mUnknown10;
    pMisc->mUnknown10 = 0x7000;
    pMain->mUnknownC = pMisc->mUnknownC + pMisc->mUnknown10;
    pMain->mUnknown10 = end - pMain->mUnknownC;
    pDebug->mUnknownC = pMain->mUnknownC + pMain->mUnknown10;
    pDebug->mUnknown10 = hi - pDebug->mUnknownC;
    if (pDebug->mUnknownC + pDebug->mUnknown10 - 0x80000000 > top) {
        pDebug->mUnknown10 = 0;
    }
    pUnload->mUnknownC = (int)lbl_800034A0;
    pUnload->mUnknown10 = (char *)ChallengeGoalCheckMargin - lbl_800034A0;
    pAuxRam->mUnknownC = fn_801C1D54();
    pAuxRam->mUnknown10 = 0xAFC000 - pAuxRam->mUnknownC;
}

void BootShutdownMemPools(void)
{
    fn_801C1D84();
}

static void _BootCheckMovieAbort(int a)
{
    PerDeviceData state;
    PerDeviceData *pState = &state;
    unsigned int i;
    int status;

    for (i = 0; i < 4; i++) {
        fn_801E1C38(i);
        if (fn_801E1CE0(i)) {
            fn_801E15D0(i);
            if (fn_801E19B4(i) >> 16 && fn_801E195C(i) == 2 && a == 1) {
                fn_801E17D0(i, pState);
                if (lbl_803EBD70 & pState->mUnknown8[lbl_803ED5EC + 1]
                    || lbl_803EBD6C & pState->mUnknown8[lbl_803ED5EC + 1]
                    || lbl_803EBD6D & pState->mUnknown8[lbl_803ED5EC + 1]
                    || lbl_803EBD6E & pState->mUnknown8[lbl_803ED5EC + 1]
                    || lbl_803EBD6F & pState->mUnknown8[lbl_803ED5EC + 1]) {
                    _Boot_bMovieAbort = 1;
                }
            }
        }
    }
    status = fn_8024151C();
    if ((unsigned int)(status - 4) <= 2 || status == 11 || status == -1) {
        _Boot_bMovieAbort = 1;
    }
}

static int _BootMovieCallback(int a)
{
    _BootCheckMovieAbort(a != 0);
    fn_801F8768();
    return _Boot_bMovieAbort == 0;
}

/* Returns 1 when _BootCheckMovieAbort flagged a button press or drive status during playback. */
static unsigned char _BootPlayMovie(int index, int a, int b, int c, int d, void *pBuffer, int e)
{
    int handle;
    int unknown0;
    int unknown1;
    MovieStreamDesc desc;
    int frameBuffer;
    int height;

    fn_801D9494(fn_801DA46C);
    if (pBuffer == 0) {
        pBuffer = fn_801D2B7C(0x100000, 0, 0);
    }
    handle = fn_801F687C(2, 2, 2, pBuffer, 0x100000);
    unknown0 = fn_801F6CE8(handle, 2);
    fn_801F6AC8(handle, 1, 0xFFFF, 0x4353, 2);
    _Boot_pMovieFile = fn_801EEB44(lbl_802EC09C, 0x2C);
    desc.mpUnknown0 = _Boot_pMovieFile;
    desc.mUnknown4 = index;
    unknown1 = fn_801F6D54(handle, &desc, 0, 0);
    if (b == 1) {
        fn_801CEADC(1);
    } else {
        fn_801CEADC(0);
    }
    frameBuffer = fn_801CE944(1);
    height = fn_801CEC84();
    fn_80239CEC(frameBuffer, height * (unsigned short)((fn_801CEA08() + 15) & ~15) * 4);
    _Boot_bMovieAbort = 0;
    fn_801D9360(handle, unknown0, unknown1, _BootMovieCallback, a == 1);
    fn_801CEA84();
    fn_801F6B84(handle);
    fn_801D2BD0(pBuffer);
    fn_801EEFAC(_Boot_pMovieFile);
    return _Boot_bMovieAbort;
}
}
