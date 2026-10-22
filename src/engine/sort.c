typedef void (*SortFunc_801F51DC)(void *pBase, unsigned int count, int size, int (*pCompare)(void *, void *),
                                  void (*pSwap)(void *, void *), void *pTemp, int flags);

typedef struct SortType_803E943C {
    SortFunc_801F51DC pSort;
    unsigned char bActive;
} SortType_803E943C;

extern void fn_801F542C(void);
extern void fn_801F5734(void);
extern void fn_801F7BD4(int err);

extern SortType_803E943C lbl_803E943C[2];
extern unsigned char lbl_803EBE20;

static void fn_801F5100(void)
{
    unsigned int i;

    for (i = 0; i < 2; i++) {
        lbl_803E943C[i].bActive = 0;
    }
}

int fn_801F512C(void)
{
    int err = 0;

    if (!lbl_803EBE20) {
        fn_801F5100();
        fn_801F542C();
        fn_801F5734();
        lbl_803EBE20 = 1;
    } else {
        err = 0x170001;
    }
    fn_801F7BD4(err);
    return err;
}

int fn_801F518C(void)
{
    int err = 0;

    if (lbl_803EBE20) {
        lbl_803EBE20 = 0;
    } else {
        err = 0x170002;
    }
    fn_801F7BD4(err);
    return err;
}

void fn_801F51DC(int type, void *pBase, unsigned int count, int size, int (*pCompare)(void *, void *),
                 void (*pSwap)(void *, void *), void *pTemp, int flags)
{
    lbl_803E943C[type].pSort(pBase, count, size, pCompare, pSwap, pTemp, flags);
}

void fn_801F522C(int type, SortFunc_801F51DC pSort)
{
    lbl_803E943C[type].pSort = pSort;
    lbl_803E943C[type].bActive = 1;
}
