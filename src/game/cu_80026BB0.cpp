#include "game/fn_801D2B7C.h"
#include "game/fn_801C1F94.h"
#include "game/cu_80026BB0.h"

struct PadState_801E17D0;

extern "C" {
extern char lbl_802EC198[];
extern char lbl_802EC264[];
extern char lbl_802EC330[];

int fn_801C6280(int a, int b, void *p);
int fn_801C6458(int a, int b);
int fn_801E15D0(int a);
int fn_801E17D0(int a, PadState_801E17D0 *pState);
int fn_801E194C(void);
int fn_801E195C(int a);
unsigned int fn_801E19B4(int a);
void fn_801E1C38(unsigned char a);
int fn_801E1CE0(unsigned char a);
int fn_801EC314(int a, int b, int count, char *p);
float fn_801EC418(int a, int b, char *p);
int fn_8023790C(void);
}

static char *lbl_802CC760[4] = {lbl_802EC198, lbl_802EC198, lbl_802EC198, lbl_802EC198};
static char *lbl_802CC770[4] = {lbl_802EC264, lbl_802EC264, lbl_802EC264, lbl_802EC264};
static unsigned char lbl_80306564[10];
static char *sPadState = 0;
static int (*sCallback)();

extern "C" {

float fn_80026BB0(int slot)
{
    int value = 0;

    if (sCallback) {
        value = sCallback();
    }
    return fn_80027294(value);
}

float fn_80026BE8(float x)
{
    float magnitude = x < 0.0f ? -x : x;

    if (magnitude < 1e-7f) {
        x = 0.0f;
    }
    if (x < 0.0f) {
        if (x > -1.0f / 7.0f) {
            x = -1.0f / 7.0f;
        }
    } else if (x > 0.0f) {
        if (x < 1.0f / 7.0f) {
            x = 1.0f / 7.0f;
        }
    }
    return x;
}

inline void Dequantize(float *pValue, unsigned int step)
{
    float x = step * (1.0f / 7.0f) - 1.0f;
    float magnitude = x < 0.0f ? -x : x;

    if (magnitude >= 1e-7f) {
        *pValue = x;
    } else {
        *pValue = 0.0f;
    }
}

static float DequantizeStep(unsigned int step)
{
    float value;

    Dequantize(&value, step);
    return value;
}

void fn_80026C5C(InputValues *pDst, InputValues *pSrc)
{
    *pDst = *pSrc;
}

int fn_80026CC4(int handle)
{
    int ready = 0;

    fn_801E1C38(handle);
    if (fn_801E1CE0(handle)) {
        ready = fn_801E15D0(handle) == 0;
    }
    if (!ready || fn_801E195C(handle) != 2 || !(fn_801E19B4(handle) >> 16)) {
        return 0;
    }
    return 1;
}

int fn_80026D50(void)
{
    int i;

    sPadState = (char *)fn_801D2B7C(fn_801E194C(), 0, 0);
    for (i = 0; i < 10; i++) {
        lbl_80306564[i] = 0;
    }
    return 34;
}

void fn_80026DA8(void)
{
    fn_801D2BD0(sPadState);
    sPadState = 0;
}

void fn_80026DD4(int slot, InputValues *pPrevious, InputValues *pCurrent)
{
    char *pState = sPadState;
    unsigned int i;
    unsigned int step;
    int handle;
    int ready;

    fn_8023790C();
    handle = fn_801C6458(slot, 0);
    ready = fn_80026CC4(handle);
    if (ready) {
        fn_801E17D0(handle, (PadState_801E17D0 *)pState);
    } else {
        fn_801C1F94(pState, 0, 12);
    }
    if (ready) {
        if (!lbl_80306564[slot]) {
            fn_80026C5C(pPrevious, pCurrent);
        }
        for (i = 0; i <= 22; i++) {
            pCurrent->mValue[i] = fn_801EC418(slot, i, pState + 8);
        }
        for (; i <= 32; i++) {
            step = (unsigned int)((fn_80026BE8(fn_801EC418(slot, i, pState + 8)) + 1.0001f) * 7.0f);
            Dequantize(&pCurrent->mValue[i], step);
        }
        step = (unsigned int)((fn_80026BB0(slot) + 1.0001f) * 7.0f);
        Dequantize(&pCurrent->mValue[33], step);
        if (lbl_80306564[slot]) {
            fn_80026C5C(pPrevious, pCurrent);
            lbl_80306564[slot] = 0;
        }
    } else {
        *pPrevious = *pCurrent;
        fn_801C1F94(pCurrent, 0, sizeof(InputValues));
    }
}

void fn_80027114(int slot, int index)
{
    switch (fn_801E19B4(fn_801C6458(slot, 0)) >> 16) {
    case 2:
        fn_801EC314(slot, 0, 34, lbl_802CC770[index]);
        break;
    case 1:
    default:
        fn_801EC314(slot, 0, 34, lbl_802CC760[index]);
        break;
    }
}

void fn_800271A4(void)
{
    fn_801C6280(-1, 3, lbl_802EC330);
}

void fn_800271D4(void **pHandlers)
{
    unsigned int i;

    for (i = 0; i < 10; i++) {
        pHandlers[i] = (void *)fn_801C6458(i, 2);
        pHandlers[i + 10] = (void *)fn_801C6458(i, 3);
    }
}

void fn_80027230(void **pHandlers)
{
    unsigned int i;

    for (i = 0; i < 10; i++) {
        fn_801C6280(i, 2, pHandlers[i]);
        fn_801C6280(i, 3, pHandlers[i + 10]);
    }
}

void fn_8002728C(int (*pCallback)())
{
    sCallback = pCallback;
}

float fn_80027294(int value)
{
    return (float)((value + 0x7FFFF) & 0xFFFFFF) * (1.0f / 16777216.0f) * 2.0f - 1.0f;
}

int fn_800272EC(float x)
{
    if (x < -1.0f) {
        x = -1.0f;
    } else if (x > 1.0f) {
        x = 1.0f;
    }
    x += 1.0f;
    x *= 0.5f;
    x *= 16777216.0f;
    return (int)x & 0xFFFFFF;
}

void fn_80027358(int slot)
{
    unsigned int i;

    if (slot == -1) {
        for (i = 0; i < 10; i++) {
            lbl_80306564[i] = 1;
        }
    } else {
        lbl_80306564[slot] = 1;
    }
}

char *fn_8002739C(void)
{
    return sPadState;
}

int fn_800273A4(void)
{
    return 34;
}
}
