#include "game/AnimFileFormat.h"
#include "game/Object_800D81C8.h"
#include "game/Record_8036B55C.h"

typedef int (*Callback_803EBB7C)(void *context, int value, unsigned int flags);

extern "C" {
extern unsigned char lbl_803EBB78;
extern Callback_803EBB7C lbl_803EBB7C;
extern Callback_803EBB7C lbl_803EBB80;
extern int lbl_803EBB84;
extern signed char lbl_803ECEB4;
extern signed char lbl_803ECEB5;
extern void *lbl_8037E840[];
extern unsigned int lbl_8037E84C[];

void fn_801BA384(Object_801BA03C *pObject, Record_800D81C8 *pEntries, int index);
void fn_801BA848(void (*callback)(AnimFileFormat_t *));
void fn_801BC0E8(void);
void fn_801BC57C(void);
void fn_801BC64C(void (*callback)(void));
void fn_801F7BD4(int err);

void fn_801B9D00(int value)
{
    lbl_803EBB7C(lbl_8037E840[lbl_803ECEB4], value, lbl_8037E84C[lbl_803ECEB4]);
}

void fn_801B9D50(int value)
{
    lbl_803EBB80(0, value, 0);
}

void fn_801B9D84(unsigned int flags)
{
    lbl_8037E84C[++lbl_803ECEB5] = flags;
}

void fn_801B9DA8(void *context)
{
    lbl_8037E840[++lbl_803ECEB4] = context;
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

void fn_801B9EDC(Object_801BA03C *pObject, unsigned short a, unsigned short b, unsigned short count)
{
    pObject->mUnknown0 = a;
    pObject->mUnknown2 = b;
    pObject->mUnknown4 = count;
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

int fn_801B9F00(Object_801BA03C *pObject, Record_800D81C8 *pEntries)
{
    unsigned short count = pObject->mUnknown4;
    unsigned char pass;
    int i;

    for (pass = 0; pass <= 1; pass++) {
        for (i = 0; i < count; i++) {
            if (pEntries[i].mUnknown1 == pass)
                return i;
        }
    }

    float best = 1.0f;
    int selected = -1;
    for (i = 0; i < count; i++) {
        if ((pEntries[i].mUnknown8 & 0x8000) && pEntries[i].mUnknown30.mUnknown0 <= best) {
            best = pEntries[i].mUnknown30.mUnknown0;
            selected = i;
        }
    }
    if (selected == -1)
        return -1;
    fn_801BA384(pObject, pEntries, selected);
    return selected;
}

void fn_801B9FEC(Object_801BA03C *pObject, Record_800D81C8 *pEntries)
{
    char state = 4;
    int i;

    if (pObject->mUnknown0 == 0)
        state = 1;
    for (i = 0; i < pObject->mUnknown4; i++) {
        pEntries[i].mUnknown0Byte = state;
        pEntries[i].mUnknown1 = 0;
        pEntries[i].mUnknown4C.mpUnknown0 = 0;
    }
}

}
