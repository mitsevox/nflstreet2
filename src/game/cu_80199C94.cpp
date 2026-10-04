extern "C" {
void fn_801C1D98(void *pDst, char *pSrc, int size);
void fn_801C1E78(char *pDst, void *pSrc, int size);
void *fn_801D2B7C(int size, int a, int b);
void *fn_801D2BB0(int a, int size, int c, int d);
void fn_801D2BD0(void *p);
}

static unsigned int lbl_803EB778 = 0;
static char *lbl_803ECBE8;
static char *lbl_803ECBEC;

extern "C" void fn_80199C94(char *pSrc, int index, int size)
{
    fn_801C1D98(lbl_803ECBEC + index * size, pSrc, size);
}

extern "C" char *fn_80199CC4(int a, int size)
{
    unsigned int slot = lbl_803EB778;

    if (++lbl_803EB778 > 3) {
        lbl_803EB778 = 0;
    }
    return lbl_803ECBE8 + slot * size;
}

extern "C" char *fn_80199CF0(int index, int size)
{
    unsigned int slot = lbl_803EB778;
    char *pDst;

    if (++lbl_803EB778 > 3) {
        lbl_803EB778 = 0;
    }
    pDst = lbl_803ECBE8 + slot * size;
    fn_801C1E78(pDst, lbl_803ECBEC + index * size, size);
    return pDst;
}

extern "C" void fn_80199D58(int count, int size)
{
    lbl_803ECBE8 = (char *)fn_801D2B7C(size * 4, 0, 0);
    lbl_803ECBEC = (char *)fn_801D2BB0(16, count * size, 0, 0);
}

extern "C" void fn_80199DB0(void)
{
    fn_801D2BD0(lbl_803ECBE8);
    lbl_803ECBE8 = 0;
    fn_801D2BD0(lbl_803ECBEC);
    lbl_803ECBEC = 0;
}
