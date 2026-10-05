#include "engine/cu_80227F14.h"

extern "C" {
void fn_80146DC4(int a);
int fn_801DCF0C(int a, int size, int c, void (*pInit)(void *), void (*pRelease)(void *));
void fn_801DCF8C(int a);
void fn_801DD0C8(int handle, int a, int b, int (*pCallback)(void *));
int fn_801DD268(int handle, int a, int b, int *pDesc);
void fn_801DD320(int handle, int item);
void fn_801DD3AC(int handle, int item, int a);
}

static unsigned char lbl_803EB3A8 = 1;
static int lbl_803ECAF0;

extern "C" {
int fn_80163D9C(void *pItem)
{
    if (lbl_803EB3A8 != 0) {
        fn_80146DC4(0);
    }
    return 0;
}

void fn_80163DD0(int handle)
{
    fn_801DCF0C(26, 20, 1, 0, 0);
    fn_801DD0C8(handle, 26, 0, fn_80163D9C);
    lbl_803ECAF0 = fn_801DD268(handle, 26, 0, 0);
    fn_801DD3AC(handle, lbl_803ECAF0, 13);
}

void fn_80163E54(int handle)
{
    fn_801DD320(handle, lbl_803ECAF0);
    fn_80228D58(lbl_803ECAF0);
    fn_80228E18();
    fn_801DCF8C(26);
    lbl_803ECAF0 = 0;
}
}
