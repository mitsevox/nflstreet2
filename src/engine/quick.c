extern void *fn_801D2BB0(int a, int size, int c, int d);
extern int fn_801D2BD0(void *p);
extern void fn_801F522C(int type, void (*pSort)(void *pBase, unsigned int count, int size,
                                                int (*pCompare)(void *, void *),
                                                void (*pSwap)(void *, void *), void *pTemp, int flags));

static void fn_801F56A8(void *pA, void *pB, void *pTemp, int size);

static void fn_801F5458(char *pBase, unsigned int count, int size, int (*pCompare)(void *, void *),
                        void (*pSwap)(void *, void *), void *pTemp, int flags)
{
    char *pStore;
    char *p;
    unsigned int i;
    unsigned int nLess;
    int result;
    int reverse;

    if (count <= 1) {
        return;
    }
    pStore = pBase + ((count - 1) >> 1) * size;
    if (pSwap) {
        pSwap(pBase, pStore);
    } else {
        fn_801F56A8(pBase, pStore, pTemp, size);
    }
    pStore = pBase;
    nLess = 0;
    reverse = flags & 1;
    for (i = 1, p = pStore + size; i < count; i++, p += size) {
        if (reverse) {
            result = pCompare(p, pBase);
        } else {
            result = pCompare(pBase, p);
        }
        if (result < 0) {
            pStore += size;
            nLess++;
            if (pStore != p) {
                if (pSwap) {
                    pSwap(pStore, p);
                } else {
                    fn_801F56A8(pStore, p, pTemp, size);
                }
            }
        }
    }
    if (pBase != pStore) {
        if (pSwap) {
            pSwap(pBase, pStore);
        } else {
            fn_801F56A8(pBase, pStore, pTemp, size);
        }
    }
    if (nLess > 1) {
        fn_801F5458(pBase, nLess, size, pCompare, pSwap, pTemp, flags);
    }
    if (nLess + 1 < count) {
        fn_801F5458(pStore + size, count - (nLess + 1), size, pCompare, pSwap, pTemp, flags);
    }
}

static void fn_801F5614(void *pBase, unsigned int count, int size, int (*pCompare)(void *, void *),
                        void (*pSwap)(void *, void *), void *pTemp, int flags)
{
    void *pBuffer = 0;

    if (pSwap == 0 && size != 4) {
        pBuffer = fn_801D2BB0(1, size, 0, 0);
    }
    fn_801F5458(pBase, count, size, pCompare, pSwap, pBuffer, flags);
    if (pBuffer) {
        fn_801D2BD0(pBuffer);
    }
}

static void fn_801F56A8(void *pA, void *pB, void *pTemp, int size)
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

void fn_801F5734(void)
{
    fn_801F522C(1, fn_801F5614);
}
