#include "game/Entry_80219044.h"
#include "engine/cu_80227F14.h"
#include "game/fn_801801F0.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801EEB44.h"
#include "game/fn_80218FC4.h"
#include <string.h>

#include "game/Record_802CC680.h"

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

int fn_80024B20(int team, int margin, int flag);
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
int fn_801E17D0(int a, struct PadState_801E17D0 *pState);
int fn_801E194C(void);
int fn_801E195C(int a);
unsigned int fn_801E19B4(int a);
void fn_801E1C38(unsigned char a);
int fn_801E1CE0(unsigned char a);
int fn_801F687C(int a, int b, int c, void *pBuffer, int size);
void fn_801F6AC8(int a, int b, int c, int d, int e);
void fn_801F6B84(int a);
int fn_801F6CE8(int a, int b);
int fn_801F6D54(int a, struct Desc_801F6D54 *pDesc, int b, int c);
int fn_801F8758(int a);
void fn_801F8768(void);
void fn_801F87FC(int a);
int fn_80219044(void *p, int a, int b, int c, struct Entry_80219044 **ppEntries);
void fn_802195E4(void *p, short a, short b);
void fn_80219650(void *p, unsigned short *pA, unsigned short *pB);
int fn_802399F8(void);
int fn_80239A00(void);
void fn_80239CEC(int a, int b);
void (*fn_8023C4D4(void (*pCallback)(void)))(void);
int fn_8023C548(void);
int fn_8023CF60(void);
void fn_8023CFD0(int a);
int fn_8024151C(void);
int fn_80244C60(void);
}

/* Filled by fn_801E17D0; the byte array at +8 is indexed by lbl_803ED5EC + 1. */
struct PadState_801E17D0 {
    unsigned char mUnknown0[8];
    unsigned char mUnknown8[24];
};

/* Second argument of fn_801F6D54. */
struct Desc_801F6D54 {
    void *mpUnknown0;
    int mUnknown4;
};

static char lbl_803EBAE0[] = " ";
static void (*lbl_803EBAE4)(void) = 0;
static unsigned char lbl_803EBAE8 = 0;
static unsigned char lbl_803ECE98;
static void *lbl_803ECE9C;
static Entry_80219044 *lbl_8037DF28[3];
static Entry_80219044 lbl_8037DF34[3];
static char lbl_802F46E0[] = "Screen display has been set to\nProgressive Mode.";
static char lbl_802F4714[] = "Screen display has been set to Interlaced Mode.";
static char lbl_802F4744[] = "|^Continue";

extern "C" {
/* Runs frames until the first id reported by fn_80219650 for p is no longer a. */
static void fn_800241E0(void *p, unsigned short a, unsigned short b, int unused)
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

static void fn_8002425C(void)
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
static void fn_800242AC(void)
{
    unsigned int i = 0;
    PadState_801E17D0 *pState = (PadState_801E17D0 *)fn_801D2B7C(fn_801E194C(), 0, 0);
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
    if (fn_80244C60() && found) {
        void *p;

        fn_801801F0(1);
        p = lbl_803EB688;
        fn_80218FC4(p, 1, 0xE, 0, 0);
        fn_802195E4(p, 1, 0xE);
        fn_800241E0(p, 1, 0xE, -1);
        lbl_8037DF34[0].mUnknown0 = 0;
        lbl_8037DF34[0].mpText = lbl_803EBAE0;
        lbl_8037DF34[0].mLength = strlen(lbl_8037DF34[0].mpText) + 1;
        lbl_8037DF34[1].mUnknown0 = 0;
        if (fn_80063AA0() == 1) {
            lbl_8037DF34[1].mpText = lbl_802F46E0;
        } else {
            lbl_8037DF34[1].mpText = lbl_802F4714;
        }
        lbl_8037DF34[1].mLength = strlen(lbl_8037DF34[1].mpText) + 1;
        lbl_8037DF34[2].mUnknown0 = 0;
        lbl_8037DF34[2].mpText = lbl_802F4744;
        lbl_8037DF34[2].mLength = strlen(lbl_8037DF34[2].mpText) + 1;
        lbl_8037DF28[0] = &lbl_8037DF34[0];
        lbl_8037DF28[1] = &lbl_8037DF34[1];
        lbl_8037DF28[2] = &lbl_8037DF34[2];
        fn_80219044(lbl_803EB688, 1, 3, 3, lbl_8037DF28);
        fn_800241E0(lbl_803EB688, 1, 3, -1);
        fn_801801F0(0);
    } else {
        fn_8023CFD0(0);
    }
}

static void fn_800244A0(void)
{
    if ((unsigned char)fn_8023C548()) {
        lbl_803EBAE8 = 1;
    } else {
        fn_8023C4D4(fn_800244A0);
    }
}

static unsigned char fn_8002499C(int index, int a, int b, int c, int d, void *pBuffer, int e);

void fn_800244E4(void)
{
    fn_8002499C(0, 0, 0, 0, 0, 0, 0);
    fn_8002499C(2, 0, 0, 0, 0, 0, 0);
    fn_8002499C(1, 1, 0, 0, 0, 0, 0);
}

void fn_80024560(void)
{
    void *p = lbl_803EB688;

    fn_801CE248(1);
    fn_8002425C();
    fn_800242AC();
    fn_80218FC4(p, 1, 4, 0, 0);
    fn_802195E4(p, 1, 4);
    fn_800241E0(p, 1, 4, -1);
    fn_801CE248(0);
}

void fn_800245DC(void)
{
    lbl_803EBAE4 = fn_8023C4D4(fn_800244A0);
}

void fn_80024654(void);

void fn_80024608(void)
{
    fn_80024654();
}

void fn_80024628(void)
{
    fn_8023C4D4(lbl_803EBAE4);
    lbl_803EBAE4 = 0;
}

void fn_80024654(void)
{
    int previous = fn_801F8758(1);

    if (previous && !fn_80185274() && lbl_803EBAE8) {
        if (!fn_8023C548()) {
            fn_801F87FC(0);
            lbl_803EBAE8 = 0;
        }
    }
    fn_801F8758(previous);
}

/* Sets the base (+12) and size (+16) words of the eight memory records. */
void fn_800246C0(void)
{
    Record_802CC680 *pState = fn_80025E50(4);
    Record_802CC680 *pDb = fn_80025E50(2);
    Record_802CC680 *pMain = fn_80025E50(1);
    Record_802CC680 *pDebug = fn_80025E50(8);
    Record_802CC680 *pMisc = fn_80025E50(0x20);
    Record_802CC680 *pAuxRam = fn_80025E50(0x10);
    Record_802CC680 *pUnload = fn_80025E50(0x40);
    Record_802CC680 *pSound = fn_80025E50(0x100);
    unsigned int limit = 0x1800000;
    int lo = fn_80239A00();
    int hi = fn_802399F8();
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
    pUnload->mUnknown10 = (char *)fn_80024B20 - lbl_800034A0;
    pAuxRam->mUnknownC = fn_801C1D54();
    pAuxRam->mUnknown10 = 0xAFC000 - pAuxRam->mUnknownC;
}

void fn_80024820(void)
{
    fn_801C1D84();
}

static void fn_80024840(int a)
{
    PadState_801E17D0 state;
    PadState_801E17D0 *pState = &state;
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
                    lbl_803ECE98 = 1;
                }
            }
        }
    }
    status = fn_8024151C();
    if ((unsigned int)(status - 4) <= 2 || status == 11 || status == -1) {
        lbl_803ECE98 = 1;
    }
}

static int fn_8002495C(int a)
{
    fn_80024840(a != 0);
    fn_801F8768();
    return lbl_803ECE98 == 0;
}

/* Returns 1 when fn_80024840 flagged a button press or drive status during playback. */
static unsigned char fn_8002499C(int index, int a, int b, int c, int d, void *pBuffer, int e)
{
    int handle;
    int unknown0;
    int unknown1;
    Desc_801F6D54 desc;
    int frameBuffer;
    int height;

    fn_801D9494(fn_801DA46C);
    if (pBuffer == 0) {
        pBuffer = fn_801D2B7C(0x100000, 0, 0);
    }
    handle = fn_801F687C(2, 2, 2, pBuffer, 0x100000);
    unknown0 = fn_801F6CE8(handle, 2);
    fn_801F6AC8(handle, 1, 0xFFFF, 0x4353, 2);
    lbl_803ECE9C = fn_801EEB44(lbl_802EC09C, 0x2C);
    desc.mpUnknown0 = lbl_803ECE9C;
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
    lbl_803ECE98 = 0;
    fn_801D9360(handle, unknown0, unknown1, fn_8002495C, a == 1);
    fn_801CEA84();
    fn_801F6B84(handle);
    fn_801D2BD0(pBuffer);
    fn_801EEFAC(lbl_803ECE9C);
    return lbl_803ECE98;
}
}
