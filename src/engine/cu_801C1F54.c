extern const unsigned char lbl_802AEF10[];

#define CTYPE(c) ((lbl_802AEF10 + 1)[(unsigned char)(c)])

int fn_801C1F54(int c)
{
    if (CTYPE(c) & 2) {
        c -= 'a' - 'A';
    }
    return c;
}

int fn_801C1F74(int c)
{
    if (CTYPE(c) & 1) {
        c += 'a' - 'A';
    }
    return c;
}

void *fn_801C1F94(void *pDst, int value, int size)
{
    char *p = pDst;

    while (size--) {
        *p++ = value;
    }
    return pDst;
}

void *fn_801C1FBC(void *pDst, const void *pSrc, int size)
{
    char *d = pDst;
    const char *s = pSrc;

    while (size--) {
        *d++ = *s++;
    }
    return pDst;
}

int fn_801C1FEC(const void *pBuf1, const void *pBuf2, int size)
{
    const unsigned char *a = pBuf1;
    const unsigned char *b = pBuf2;

    while (size--) {
        if (*a != *b) {
            return *a - *b;
        }
        a++;
        b++;
    }
    return 0;
}
