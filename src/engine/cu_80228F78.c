/* Partial source for the engine range 0x80228F78-0x80229084 (neutral file name). */

extern int fn_801C3180(const char *pString);
extern char *fn_801C2EB4(char *pDest, const char *pSource);
extern void *fn_8022C938(int size, int a);
extern void fn_8022C988(void *p);
extern int fn_801F8D60(int tag, int a);
extern int fn_801F8EEC(int tag);
extern int fn_8020D2D0(int tag, char *pName, int a, int b);

static int lbl_803EBFB8 = 0;
static char *lbl_803EBFBC = 0;
static int lbl_803EBFC0 = -1;

int fn_80228F78(int a, const char *pName, int b)
{
    lbl_803EBFBC = fn_8022C938(fn_801C3180(pName) + 1, 1);
    fn_801C2EB4(lbl_803EBFBC, pName);
    lbl_803EBFB8 = a;
    lbl_803EBFC0 = b;
    return 0;
}

void fn_80228FD8(void)
{
    fn_8022C988(lbl_803EBFBC);
    lbl_803EBFB8 = 0;
    lbl_803EBFBC = 0;
    lbl_803EBFC0 = -1;
}

int fn_80229010(void)
{
    int err = fn_801F8D60(0x54415453, lbl_803EBFB8);

    if (err == 0) {
        err = fn_8020D2D0(0x54415453, lbl_803EBFBC, lbl_803EBFC0, 0);
    }
    return err;
}

int fn_8022905C(void)
{
    return fn_801F8EEC(0x54415453);
}
