/* Controller input: reads each pad into 34 remapped stick and button values per frame and saves or restores the pad handlers. */

#include "game/fn_801D2B7C.h"
#include "game/fn_801C1F94.h"
#include "game/PadInput.h"

struct PerDeviceData_t;

extern "C" {
extern char lbl_802EC198[];
extern char lbl_802EC264[];
extern char lbl_802EC330[];

int fn_801C6280(int a, int b, void *p);
int fn_801C6458(int a, int b);
int fn_801E15D0(int a);
int fn_801E17D0(int a, PerDeviceData_t *pState);
int fn_801E194C(void);
int fn_801E195C(int a);
unsigned int fn_801E19B4(int a);
void fn_801E1C38(unsigned char a);
int fn_801E1CE0(unsigned char a);
int fn_801EC314(int a, int b, int count, char *p);
float fn_801EC418(int a, int b, char *p);
int fn_8023790C(void);
}

static char *_PadInput_apRemapStandard[4] = {lbl_802EC198, lbl_802EC198, lbl_802EC198, lbl_802EC198};
static char *_PadInput_apRemapType2[4] = {lbl_802EC264, lbl_802EC264, lbl_802EC264, lbl_802EC264};
static unsigned char _PadInput_abResetSlot[10];
static char *_PadInput_pDeviceData = 0;
static int (*_PadInput_pAxisCallback)();

extern "C" {

float PadInputGetCallbackAxis(int slot)
{
    int value = 0;

    if (_PadInput_pAxisCallback) {
        value = _PadInput_pAxisCallback();
    }
    return PadInputAxisFromFixed(value);
}

float PadInputSnapAxis(float x)
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

void PadInputCopyValues(InputValues *pDst, InputValues *pSrc)
{
    *pDst = *pSrc;
}

int PadInputIsDeviceReady(int handle)
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

int PadInputInit(void)
{
    int i;

    _PadInput_pDeviceData = (char *)fn_801D2B7C(fn_801E194C(), 0, 0);
    for (i = 0; i < 10; i++) {
        _PadInput_abResetSlot[i] = 0;
    }
    return 34;
}

void PadInputShutdown(void)
{
    fn_801D2BD0(_PadInput_pDeviceData);
    _PadInput_pDeviceData = 0;
}

void PadInputRead(int slot, InputValues *pPrevious, InputValues *pCurrent)
{
    char *pState = _PadInput_pDeviceData;
    unsigned int i;
    unsigned int step;
    int handle;
    int ready;

    fn_8023790C();
    handle = fn_801C6458(slot, 0);
    ready = PadInputIsDeviceReady(handle);
    if (ready) {
        fn_801E17D0(handle, (PerDeviceData_t *)pState);
    } else {
        fn_801C1F94(pState, 0, 12);
    }
    if (ready) {
        if (!_PadInput_abResetSlot[slot]) {
            PadInputCopyValues(pPrevious, pCurrent);
        }
        for (i = 0; i <= 22; i++) {
            pCurrent->mValue[i] = fn_801EC418(slot, i, pState + 8);
        }
        for (; i <= 32; i++) {
            step = (unsigned int)((PadInputSnapAxis(fn_801EC418(slot, i, pState + 8)) + 1.0001f) * 7.0f);
            Dequantize(&pCurrent->mValue[i], step);
        }
        step = (unsigned int)((PadInputGetCallbackAxis(slot) + 1.0001f) * 7.0f);
        Dequantize(&pCurrent->mValue[33], step);
        if (_PadInput_abResetSlot[slot]) {
            PadInputCopyValues(pPrevious, pCurrent);
            _PadInput_abResetSlot[slot] = 0;
        }
    } else {
        *pPrevious = *pCurrent;
        fn_801C1F94(pCurrent, 0, sizeof(InputValues));
    }
}

void PadInputSetupRemap(int slot, int index)
{
    switch (fn_801E19B4(fn_801C6458(slot, 0)) >> 16) {
    case 2:
        fn_801EC314(slot, 0, 34, _PadInput_apRemapType2[index]);
        break;
    case 1:
    default:
        fn_801EC314(slot, 0, 34, _PadInput_apRemapStandard[index]);
        break;
    }
}

void PadInputSetDefaultHandler(void)
{
    fn_801C6280(-1, 3, lbl_802EC330);
}

void PadInputSaveHandlers(void **pHandlers)
{
    unsigned int i;

    for (i = 0; i < 10; i++) {
        pHandlers[i] = (void *)fn_801C6458(i, 2);
        pHandlers[i + 10] = (void *)fn_801C6458(i, 3);
    }
}

void PadInputRestoreHandlers(void **pHandlers)
{
    unsigned int i;

    for (i = 0; i < 10; i++) {
        fn_801C6280(i, 2, pHandlers[i]);
        fn_801C6280(i, 3, pHandlers[i + 10]);
    }
}

void PadInputSetAxisCallback(int (*pCallback)())
{
    _PadInput_pAxisCallback = pCallback;
}

float PadInputAxisFromFixed(int value)
{
    return (float)((value + 0x7FFFF) & 0xFFFFFF) * (1.0f / 16777216.0f) * 2.0f - 1.0f;
}

int PadInputAxisToFixed(float x)
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

void PadInputResetSlot(int slot)
{
    unsigned int i;

    if (slot == -1) {
        for (i = 0; i < 10; i++) {
            _PadInput_abResetSlot[i] = 1;
        }
    } else {
        _PadInput_abResetSlot[slot] = 1;
    }
}

char *PadInputGetDeviceData(void)
{
    return _PadInput_pDeviceData;
}

int PadInputGetValueCount(void)
{
    return 34;
}
}
