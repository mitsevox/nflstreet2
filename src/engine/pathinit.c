/* PATH interactive-music library start-up (pathinit.c): initializes and shuts down the library,
   routes its memory through the installed allocator, keeps the debug callbacks and loads, destroys
   and sizes the music projects (map files). */

#include "engine/pathlib.h"

extern "C" {
AllocParams lbl_8037E814;
}

extern "C" int fn_801B2AD4(void)
{
    if (++lbl_803EBB24 != 1) {
        --lbl_803EBB24;
        return -18;
    }
    for (int i = 3; i >= 0; --i)
        lbl_802F47D0[i] = 0;
    lbl_803EBB38 = 1;
    lbl_803EBB40 = 256;
    --lbl_803EBB24;
    lbl_803EBB48 = 0;
    lbl_803EBB28 = 0;
    lbl_803EBB54 = 0;
    lbl_803EBB39 = 0;
    lbl_803EBB50 = 0;
    lbl_803EBB4C = 0;
    return 0;
}

extern "C" int fn_801B2B58(void)
{
    if (!lbl_803EBB38)
        return -14;
    fn_801B2F28(0x0F000000);
    if (fn_801B42C0(0x0F000000) == 0) {
        SNDSYS_entercritical();
        delete lbl_803EBB64;
        delete lbl_803EBB60;
        SNDSYS_leavecritical();
        lbl_803EBB60 = 0;
        lbl_803EBB68 = 0;
        lbl_803EBB64 = 0;
        lbl_803EBB38 = 0;
    }
    return lbl_803EBB38 == 0;
}

extern "C" void *fn_801B2C40(int size)
{
    void *result;
    if (lbl_803EBB68)
        result = lbl_803EBB68->Alloc(size, lbl_8037E814);
    else
        result = 0;
    return result;
}

extern "C" void fn_801B2C94(void *p)
{
    if (lbl_803EBB68)
        lbl_803EBB68->Free(p, 0);
}

extern "C" void fn_801B2F18(void (*a)(int, int), void (*b)(int, int), void (*c)(int, int))
{
    lbl_803EBB2C = a;
    lbl_803EBB30 = b;
    lbl_803EBB34 = c;
}

extern "C" void *fn_801B3234(int flags)
{
    Node_801B3FE0 *p = fn_801B4174(flags);
    Class_801B44BC *result;
    if (p)
        result = p->mUnknown100;
    else
        result = 0;
    return result;
}
