#include <string.h>

static char lbl_802D4FB0[128] = "The Users String";
static int lbl_803EA630 = 128;

extern "C" int fn_80063BE4(char *pDest, int count)
{
    strncpy(pDest, lbl_802D4FB0, count);
    pDest[count] = 0;
    return lbl_803EA630;
}

extern "C" void fn_80063C2C(const char *pSource, int count)
{
    lbl_803EA630 = count;
    strncpy(lbl_802D4FB0, pSource, count);
    lbl_802D4FB0[lbl_803EA630] = 0;
}
