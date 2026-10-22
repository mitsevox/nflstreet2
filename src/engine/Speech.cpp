#include <stddef.h>
#include "engine/Resource.h"
#include "engine/system.h"
#include "game/fn_801D2B7C.h"

struct SpchLogEvent_8039AEF8 {
    int mUnk0;
    int mNumArgs;
    int mUnk8;
    unsigned int mArgs[36];
};

struct SpchLog_8039AEF0 {
    int mNext;
    unsigned int mCount;
    SpchLogEvent_8039AEF8 mEvents[8];
};

extern "C" {
extern SpchLog_8039AEF0 lbl_8039AEF0;
extern void *lbl_803ECF8C;
extern void *lbl_803ECF90;
extern unsigned char lbl_803EBE28;

void *memset(void *dst, int value, size_t n);
void fn_801AF060(void);
void fn_801AF5E4(int (*pA)(void), void (*pB)(void));
void fn_801AF630(void *pFunc);
void fn_801AF718(void);
void fn_801B2A08(void *pData);
void fn_80266CB8(void *pData, int a);

void fn_801F5C34(void);
void fn_801F5C6C(Res_801EDC2C *pRes, unsigned int index);
void fn_801F5C94(Res_801EDC2C *pRes, unsigned int index, int a);
void fn_801F5CCC(int (*pA)(void), void (*pB)(void));
void fn_801F5CEC(void *pFunc);
void fn_801F5D0C(void);
}

/* Leading-underscore NASCAR 2005 names with no reference from outside this
   unit: file-local, with the C++ linkage their mangled NASCAR names show. */

static void fn_801F5760(const char *pFormat, ...)
{
}

static int fn_801F57AC(void)
{
    return fn_801F7ABC();
}

static void fn_801F57CC(void)
{
    unsigned int i;

    lbl_8039AEF0.mNext = 0;
    lbl_8039AEF0.mCount = 0;
    for (i = 0; i < 8; i++) {
        memset(&lbl_8039AEF0.mEvents[i], 0, sizeof(SpchLogEvent_8039AEF8));
    }
}

static void fn_801F5828(int type, int time, int numArgs, unsigned int *pArgs)
{
    SpchLogEvent_8039AEF8 *pEvent;
    int i;

    pEvent = &lbl_8039AEF0.mEvents[lbl_8039AEF0.mNext];
    pEvent->mUnk0 = type;
    pEvent->mUnk8 = time;
    pEvent->mNumArgs = numArgs;
    for (i = 0; i < 36; i++) {
        if (i < numArgs) {
            pEvent->mArgs[i] = pArgs[i];
        } else {
            pEvent->mArgs[i] = 0;
        }
    }
    lbl_8039AEF0.mNext = (lbl_8039AEF0.mNext + 1) & 7;
    lbl_8039AEF0.mCount += (lbl_8039AEF0.mCount < 8);
}

void fn_801F5C34(void)
{
    fn_801AF718();
    fn_801D2BD0(lbl_803ECF90);
    fn_801D2BD0(lbl_803ECF8C);
    lbl_803EBE28 = 0;
}

void fn_801F5C6C(Res_801EDC2C *pRes, unsigned int index)
{
    fn_801B2A08((void *)fn_801EF390(pRes, index, 1));
}

void fn_801F5C94(Res_801EDC2C *pRes, unsigned int index, int a)
{
    fn_80266CB8((void *)fn_801EF390(pRes, index, 1), a);
}

void fn_801F5CCC(int (*pA)(void), void (*pB)(void))
{
    fn_801AF5E4(pA, pB);
}

void fn_801F5CEC(void *pFunc)
{
    fn_801AF630(pFunc);
}

void fn_801F5D0C(void)
{
    fn_801AF060();
}
