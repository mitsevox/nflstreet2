extern "C" char *fn_801C2EF0(char *pDest, const char *pSource, int count);

static char lbl_802D4FB0[128] = "The Users String";
static int lbl_803EA630 = 128;

extern "C" int fn_80063BE4(char *pDest, int count)
{
    fn_801C2EF0(pDest, lbl_802D4FB0, count);
    pDest[count] = 0;
    return lbl_803EA630;
}

extern "C" void fn_80063C2C(const char *pSource, int count)
{
    lbl_803EA630 = count;
    fn_801C2EF0(lbl_802D4FB0, pSource, count);
    lbl_802D4FB0[lbl_803EA630] = 0;
}
