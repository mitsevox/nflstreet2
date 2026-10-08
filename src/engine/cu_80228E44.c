/* Partial source for the engine range 0x80228E44-0x80228F78 (neutral file name). */

/* 28-byte pool entry; only the byte at +8 is written here. */
typedef struct Entry_80228E44 {
    unsigned char mUnknown0[8];
    unsigned char mUnknown8;
    unsigned char mUnknown9[19];
} Entry_80228E44;

extern void *fn_801D2BB0(int a, int size, int c, int d);
extern int fn_801D2BD0(void *p);
extern void fn_801F7BD4(int err);
extern int fn_801F7C88(void);

static unsigned short lbl_803EBFA8 = 0;
static Entry_80228E44 *lbl_803EBFAC = 0;
static int lbl_803EBFB0 = -1;
static unsigned char lbl_803EBFB4 = 0;

int fn_80228E44(unsigned short *pCount)
{
    int err = 0;
    unsigned int i;

    if (lbl_803EBFB4 == 0) {
        lbl_803EBFA8 = *pCount;
        lbl_803EBFB0 = err;
        lbl_803EBFAC = fn_801D2BB0(1, lbl_803EBFA8 * sizeof(Entry_80228E44), 0, 0);
        if (lbl_803EBFAC == 0) {
            err = fn_801F7C88();
        } else {
            for (i = 0; i < lbl_803EBFA8; i++) {
                lbl_803EBFAC[i].mUnknown8 = 0xFF;
            }
            lbl_803EBFB4 = 1;
        }
    } else {
        err = 0x80001;
    }
    fn_801F7BD4(err);
    return err;
}

int fn_80228F0C(void)
{
    int err = 0;

    if (lbl_803EBFB4) {
        lbl_803EBFB0 = -1;
        lbl_803EBFA8 = 0;
        fn_801D2BD0(lbl_803EBFAC);
        lbl_803EBFB4 = 0;
        lbl_803EBFAC = 0;
    } else {
        err = 0x80002;
    }
    fn_801F7BD4(err);
    return err;
}
