#include <dolphin/os.h>
#include <dolphin/vi.h>
#include <dolphin/gx.h>
#include <dolphin/pad.h>
#include <dolphin/ai.h>
#include "engine/system.h"
#include "game/fn_801D2B7C.h"

typedef int (*SysResetCallback_801F8868)(void);

extern void fn_801CE2B8(int a);
extern void fn_801CAB30(void);
extern void fn_80239ED4(void);
extern int fn_801CE1E8(void);
extern int fn_8027EFAC(int year);

extern int lbl_803EBE50;
extern int lbl_803EBE54;
extern unsigned char lbl_803EBE60;
extern unsigned char lbl_803EBE61;
extern unsigned char lbl_803EBE62;
extern SysResetCallback_801F8868 lbl_803EBE64;
extern unsigned char lbl_803EBE68;
extern unsigned int lbl_803EBE58;
extern unsigned int lbl_803EBE5C;
extern OSMutex lbl_8039B418;
extern SysTime_8039B430 lbl_8039B430;

void fn_801F8574(void);
void fn_801F8768(void);
void fn_801F87FC(int code);

static void fn_801F7DF4(u32 retraceCount)
{
    fn_801F7AE8();
    fn_801F8574();
}

static void fn_801F7E18(void)
{
    fn_801CE2B8(0);
    fn_80239ED4();
    PADRecalibrate(0xF0000000);
    PADControlMotor(0, 2);
    PADControlMotor(1, 2);
    PADControlMotor(2, 2);
    PADControlMotor(3, 2);
    AIReset();
    GXAbortFrame();
    VISetBlack(TRUE);
    VIFlush();
    VIWaitForRetrace();
}

int fn_801F7E90(void)
{
    lbl_803EBE54 = fn_801F81D4();
    OSSetThreadPriority((OSThread *)lbl_803EBE54, 22);
    VISetPreRetraceCallback(fn_801F7DF4);
    return 0;
}

int fn_801F7ED0(void)
{
    VISetPreRetraceCallback(0);
    return 0;
}

int fn_801F7F60(SysTimer_801F7B1C *pTimer)
{
    if (pTimer->mFlags & 4) {
        if (pTimer->mFlags & 2) {
            pTimer->mFlags &= ~2;
        } else {
            pTimer->mUnk8 += 1 - pTimer->mCount;
        }
        pTimer->mFlags &= ~4;
    }
    return 0;
}

void fn_801F7FA8(Lock_801F8014 *pSection)
{
    if (lbl_803EBE68) {
        lbl_803EBE68 = 0;
        OSInitMutex(&lbl_8039B418);
    }
    lbl_803EBE50++;
    OSInitMutex(&pSection->mMutex);
    pSection->mOwner = fn_801F81D4();
    pSection->mCount = 0;
}

void fn_801F8014(Lock_801F8014 *pSection)
{
    int owner;

    OSLockMutex(&lbl_8039B418);
    owner = pSection->mOwner;
    if (owner != fn_801F81D4() || pSection->mCount == 0) {
        OSUnlockMutex(&lbl_8039B418);
        OSLockMutex(&pSection->mMutex);
        pSection->mOwner = fn_801F81D4();
        pSection->mCount++;
    } else {
        pSection->mCount++;
        OSUnlockMutex(&lbl_8039B418);
    }
}

void fn_801F809C(Lock_801F8014 *pSection)
{
    if (--pSection->mCount == 0) {
        OSUnlockMutex(&pSection->mMutex);
    }
}

void fn_801F80D0(Lock_801F8014 *pSection)
{
    pSection->mOwner = 0;
    lbl_803EBE50--;
}

void fn_801F80E8(OSMutex **ppMutex)
{
    OSMutex *pMutex = fn_801D2B7C(sizeof(OSMutex), 0, 0);

    *ppMutex = pMutex;
    OSInitMutex(pMutex);
}

int fn_801F8128(OSMutex **ppMutex)
{
    OSLockMutex(*ppMutex);
    return 1;
}

void fn_801F8150(OSMutex **ppMutex)
{
    OSUnlockMutex(*ppMutex);
}

void fn_801F8174(OSMutex **ppMutex)
{
    fn_801D2BD0(*ppMutex);
    *ppMutex = 0;
}

void fn_801F81AC(void)
{
    fn_801F8768();
    fn_801CAB30();
    OSYieldThread();
}

int fn_801F81D4(void)
{
    return (int)OSGetCurrentThread();
}

void fn_801F81F4(SysTime_8039B430 *pTime)
{
    unsigned char enabled = OSDisableInterrupts();

    *pTime = lbl_8039B430;
    OSRestoreInterrupts(enabled);
}

void fn_801F8574(void)
{
    unsigned char enabled = OSDisableInterrupts();
    unsigned int ms;
    unsigned int days;

    lbl_803EBE58++;
    switch (fn_801CE1E8()) {
    case 1:
        ms = lbl_803EBE58 * 20;
        break;
    case 0:
    default:
        ms = lbl_803EBE58 * 1000 / 60;
        break;
    }
    lbl_8039B430.mHundredths = ms / 10;
    if (ms > 999) {
        lbl_803EBE58 = 0;
        lbl_803EBE5C++;
        lbl_8039B430.mHundredths = 0;
        if (++lbl_8039B430.mSeconds > 59) {
            lbl_8039B430.mSeconds = 0;
            if (++lbl_8039B430.mMinutes > 59) {
                lbl_8039B430.mMinutes = 0;
                if (++lbl_8039B430.mHours > 23) {
                    lbl_8039B430.mHours = 0;
                    lbl_8039B430.mDays++;
                    switch (lbl_8039B430.mMonth) {
                    case 4:
                    case 6:
                    case 9:
                    case 11:
                        days = 30;
                        break;
                    case 2:
                        days = fn_8027EFAC(lbl_8039B430.mYear) ? 29 : 28;
                        break;
                    case 1:
                    case 3:
                    case 5:
                    case 7:
                    case 8:
                    case 10:
                    case 12:
                        days = 31;
                        break;
                    default:
                        days = 31;
                        break;
                    }
                    if (lbl_8039B430.mDays > days) {
                        lbl_8039B430.mDays = 1;
                        if (++lbl_8039B430.mMonth > 12) {
                            lbl_8039B430.mMonth = 1;
                            lbl_8039B430.mYear++;
                        }
                    }
                }
            }
        }
    }
    OSRestoreInterrupts(enabled);
}

unsigned char fn_801F8758(unsigned char enable)
{
    unsigned char previous = lbl_803EBE61;

    lbl_803EBE61 = enable;
    return previous;
}

void fn_801F8768(void)
{
    unsigned char pressed = OSGetResetButtonState();

    if (lbl_803EBE62 || (!pressed && lbl_803EBE60)) {
        int reset = 1;

        if (lbl_803EBE64) {
            reset = lbl_803EBE64();
        }
        if (reset && lbl_803EBE61) {
            fn_801F87FC(0);
            lbl_803EBE62 = 0;
        } else {
            lbl_803EBE62 = 1;
        }
    }
    lbl_803EBE60 = pressed;
}

void fn_801F87FC(int code)
{
    fn_801F7E18();
    OSResetSystem(0, 1, code);
}

void fn_801F8838(void)
{
    fn_801F7E18();
    OSResetSystem(1, 1, 1);
}

SysResetCallback_801F8868 fn_801F8868(SysResetCallback_801F8868 pCallback)
{
    SysResetCallback_801F8868 pPrevious = lbl_803EBE64;

    lbl_803EBE64 = pCallback;
    return pPrevious;
}
