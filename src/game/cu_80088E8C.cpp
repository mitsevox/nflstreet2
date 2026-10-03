extern "C" {
void fn_801C1D98(void *pDst, char *pSrc, int size);
void fn_801C1E78(char *pDst, void *pSrc, int size);
void *fn_801D2BB0(int a, int size, int c, int d);
void fn_801D2BD0(void *p);
}

static void *lbl_803EA818 = 0;
static int lbl_803EC870;
static char *lbl_803EC874;

extern "C" void fn_80088E8C(char *pStart, char *pEnd)
{
    fn_801C1E78(lbl_803EC874, lbl_803EA818, lbl_803EC870);
    fn_801D2BD0(lbl_803EA818);
    lbl_803EA818 = 0;
}

extern "C" void fn_80088EC8(char *pStart, char *pEnd)
{
    int size = (pEnd - pStart + 31) & ~31;

    lbl_803EA818 = fn_801D2BB0(16, size, 0, 0);
    fn_801C1D98(lbl_803EA818, pStart, size);
    lbl_803EC870 = size;
    lbl_803EC874 = pStart;
}
