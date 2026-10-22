extern void *fn_801D2BB0(int heap, int size, int ident, int flags);
extern int fn_801D2BD0(void *p);
extern void fn_801F522C(int type, void (*pSort)(void *pBase, unsigned int count, int size,
                                                int (*pCompare)(void *, void *),
                                                void (*pSwap)(void *, void *), void *pTemp, int flags));

static void fn_801F53A0(void *pA, void *pB, void *pTemp, int size);

static void fn_801F524C(void *pBase, unsigned int count, int size, int (*pCompare)(void *, void *),
                        void (*pSwap)(void *, void *), void *pTemp, int flags)
{
    void *pBuffer = 0;
    unsigned int pass;
    unsigned int limit;
    unsigned int i;
    int swapped;
    char *p;
    int result;
    int reverse;

    if (pSwap == 0 && size != 4) {
        pBuffer = fn_801D2BB0(1, size, 0, 0);
    }
    reverse = flags & 1;
    limit = count;
    for (pass = 0; pass < count; pass++) {
        swapped = 0;
        p = pBase;
        for (i = 0; i < limit - 1; i++) {
            if (reverse) {
                result = pCompare(p + size, p);
            } else {
                result = pCompare(p, p + size);
            }
            if (result < 0) {
                if (pSwap) {
                    pSwap(p, p + size);
                } else {
                    fn_801F53A0(p, p + size, pBuffer, size);
                }
                swapped = 1;
            }
            p += size;
        }
        if (swapped != 1) {
            break;
        }
        limit--;
    }
    if (pBuffer) {
        fn_801D2BD0(pBuffer);
    }
}

static void fn_801F53A0(void *pA, void *pB, void *pTemp, int size)
{
    if (size == 4) {
        int temp = *(int *)pA;
        *(int *)pA = *(int *)pB;
        *(int *)pB = temp;
    } else {
        memcpy(pTemp, pA, size);
        memcpy(pA, pB, size);
        memcpy(pB, pTemp, size);
    }
}

void fn_801F542C(void)
{
    fn_801F522C(0, fn_801F524C);
}
