#include "engine/cu_801B9F00.h"
#include "engine/cu_801BA818.h"
#include "engine/fn_801F7BD4.h"

typedef int (*Callback_803EBB7C)(void *pUser, int op, unsigned int state);

extern unsigned char lbl_803EBB78;
extern Callback_803EBB7C lbl_803EBB7C;
extern Callback_803EBB7C lbl_803EBB80;
extern int lbl_803EBB84;
extern signed char lbl_803ECEB4;
extern signed char lbl_803ECEB5;
extern void *lbl_8037E840[];
extern unsigned int lbl_8037E84C[];

int fn_801B9D00(int op)
{
    return lbl_803EBB7C(lbl_8037E840[lbl_803ECEB4], op, lbl_8037E84C[lbl_803ECEB4]);
}

int fn_801B9D50(int op)
{
    return lbl_803EBB80(0, op, 0);
}

void fn_801B9D84(unsigned int state)
{
    lbl_8037E84C[++lbl_803ECEB5] = state;
}

void fn_801B9DA8(void *pUser)
{
    lbl_8037E840[++lbl_803ECEB4] = pUser;
}

void fn_801B9DCC(void)
{
    lbl_803ECEB5--;
}

void fn_801B9DDC(void)
{
    lbl_803ECEB4--;
}

int fn_801B9DEC(unsigned int mode)
{
    int err = 0;

    if (lbl_803EBB78 == 0)
        lbl_803EBB78 = 1;
    else
        err = 0x140001;
    lbl_803ECEB5 = -1;
    lbl_803ECEB4 = -1;
    fn_801BA848(0);
    switch (mode) {
    case 0:
        fn_801BC64C(fn_801BC57C);
        break;
    case 1:
    case 2:
        fn_801BC64C(fn_801BC0E8);
        break;
    }
    lbl_803EBB84 = mode;
    fn_801F7BD4(err);
    return err;
}

int fn_801B9E88(void)
{
    int err = 0;

    if (lbl_803EBB78) {
        lbl_803EBB7C = 0;
        lbl_803EBB78 = 0;
    } else {
        err = 0x140002;
    }
    fn_801F7BD4(err);
    return err;
}

void fn_801B9EDC(Object_801BA03C *pList, unsigned short a, unsigned short b, unsigned short count)
{
    pList->mUnknown0 = a;
    pList->mUnknown2 = b;
    pList->mUnknown4 = count;
}

void fn_801B9EEC(Callback_803EBB7C callback, Callback_803EBB7C fallback)
{
    lbl_803EBB7C = callback;
    lbl_803EBB80 = fallback;
}

int fn_801B9EF8(void)
{
    return lbl_803EBB84;
}
