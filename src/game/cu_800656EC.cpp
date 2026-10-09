#include "game/Class_80148A58.h"
#include "game/cu_80064864.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_800B65A0.h"

/* Request latched by fn_8006587C and handed out once through the slot-0 callback fn_80065714. */
struct Request_8030A50C {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    int mUnknown4;
    unsigned char mPending;
};

extern void *lbl_803EA368;

extern "C" {
int fn_8002D060(void *p);
int fn_8009B9A8(int a);
int fn_8009D86C(void);
int fn_800A7FD8(void);
int fn_800B6644(int a);
int fn_800BA6F8(void);
int fn_80178308(void);
int fn_80178320(void);
int fn_801788D8(int *pValue);
int fn_80178AE0(void);

static Request_8030A50C lbl_8030A50C;

void fn_800656EC(void)
{
    lbl_8030A50C.mUnknown0 = 0xFFFF;
    lbl_8030A50C.mUnknown2 = 0xFFFF;
    lbl_8030A50C.mUnknown4 = -1;
    lbl_8030A50C.mPending = 0;
}

int fn_80065714(unsigned short *pA, unsigned short *pB, int *pC)
{
    int result = 0;

    if (lbl_8030A50C.mPending) {
        *pA = lbl_8030A50C.mUnknown0;
        result = 1;
        *pB = lbl_8030A50C.mUnknown2;
        *pC = lbl_8030A50C.mUnknown4;
        fn_800656EC();
    }
    return result;
}

int fn_80065774(int a)
{
    int result = 0;

    if ((fn_800B65A0(fn_80178308()) == 0xFF && fn_800B65A0(fn_80178320()) == 0xFF) || fn_800B6644(a) != 0xFF || a == 8) {
        if (fn_80148A58()) {
            result = fn_80148A58()->vfn_22(a);
        } else {
            result = 1;
        }
    }
    return result;
}

void fn_80065814(void)
{
    fn_800656EC();
}

void fn_80065834(void)
{
    fn_800656EC();
    fn_80064DC0(0, fn_80065714);
}

int fn_80065864(void)
{
    return lbl_8030A50C.mPending == 1;
}

void fn_8006587C(int a, int b, float c)
{
    int mode = fn_800AD9B4();
    int value;

    if (lbl_8030A50C.mPending != 0) {
        return;
    }
    if (b != 0 && b != 0x46) {
        return;
    }
    if (!fn_80065774(a) || fn_8002D060(lbl_803EA368) || fn_8009B9A8(0)) {
        return;
    }
    if (mode == 2 && fn_800A7FD8()) {
        return;
    }
    if (c != 1.0f) {
        return;
    }
    switch (mode) {
    case 1:
    case 7:
        return;
    case 6:
        if (fn_8009D86C() == 6) {
            return;
        }
        break;
    }
    if (fn_80178AE0() == 2 || fn_800BA6F8() || (fn_801788D8(&value) == 1 && mode == 3)) {
        lbl_8030A50C.mUnknown0 = 3;
        lbl_8030A50C.mUnknown2 = 1;
        lbl_8030A50C.mUnknown4 = a;
        lbl_8030A50C.mPending = 1;
    }
}
}
