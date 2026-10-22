extern const unsigned char lbl_802AEF10[];

#define CTYPE(c) ((lbl_802AEF10 + 1)[(unsigned char)(c)])

int fn_801C1F54(int c);

char *fn_801C2EB4(char *pDest, const char *pSource)
{
    char *pOut = pDest;

    for (;;) {
        if ((*pOut++ = *pSource++) == 0) {
            break;
        }
    }
    return pDest;
}

char *fn_801C2EF0(char *pDest, const char *pSource, int size)
{
    char *pOut = pDest;

    if (size == 0 || pDest == pSource) {
        return pDest;
    }
    while ((*pOut++ = *pSource++) != 0 && --size) {
    }
    return pDest;
}

char *fn_801C2F2C(char *pDest, const char *pSource)
{
    char *pOut = pDest;

    for (; *pOut++;) {
    }
    pOut--;
    for (;;) {
        if ((*pOut++ = *pSource++) == 0) {
            break;
        }
    }
    return pDest;
}

char *fn_801C2F88(char *pDest, const char *pSource, int size)
{
    char *pStart = pDest;

    while (*pDest) {
        pDest++;
    }
    while (size--) {
        if ((*pDest++ = *pSource++) == 0) {
            break;
        }
        if (size == 0) {
            *pDest = 0;
        }
    }
    return pStart;
}

int fn_801C2FE4(const char *pString1, const char *pString2)
{
    if (pString1 == pString2) {
        return 0;
    }
    while (*pString1 == *pString2++) {
        if (*pString1++ == 0) {
            return 0;
        }
    }
    return *pString1 - pString2[-1];
}

int fn_801C302C(const char *pString1, const char *pString2, int size)
{
    if (size == 0 || pString1 == pString2) {
        return 0;
    }
    while (*pString1 == *pString2++) {
        if (--size == 0) {
            return 0;
        }
        if (*pString1++ == 0) {
            return 0;
        }
    }
    return *pString1 - pString2[-1];
}

char *fn_801C3084(const char *pString, int c)
{
    while (*pString) {
        if (*pString++ == (char)c) {
            return (char *)pString - 1;
        }
    }
    return 0;
}

char *fn_801C30C0(const char *pString, int c)
{
    char ch = c;
    const char *pLast = 0;

    while (*pString) {
        if (*pString == ch) {
            pLast = pString;
        }
        pString++;
    }
    if (*pString == ch) {
        pLast = pString;
    }
    return (char *)pLast;
}

char *fn_801C310C(const char *pString, const char *pFind)
{
    const char *p;
    const char *f;

    for (; *pString; pString++) {
        p = pString;
        f = pFind;
        while (*f && *p == *f) {
            if (f[1] == 0) {
                return (char *)pString;
            }
            f++;
            p++;
        }
    }
    return 0;
}

int fn_801C3180(const char *pString)
{
    const char *p = pString;

    for (; *p++;) {
    }
    return p - pString - 1;
}

int fn_801C31B0(const char *pString1, const char *pString2)
{
    char c1;
    char c2;

    do {
        c1 = *pString1++;
        c2 = *pString2++;
        if ((unsigned int)(c1 - 'A') <= 'Z' - 'A') {
            c1 += 'a' - 'A';
        }
        if ((unsigned int)(c2 - 'A') <= 'Z' - 'A') {
            c2 += 'a' - 'A';
        }
        if (c1 != c2) {
            return c1 - c2;
        }
    } while (c1);
    return 0;
}

int fn_801C3214(const char *pString1, const char *pString2, int size)
{
    const char *pEnd = pString1 + size;
    char c1;
    char c2;

    do {
        c1 = *pString1++;
        if (pString1 > pEnd) {
            break;
        }
        c2 = *pString2++;
        if ((unsigned int)(c1 - 'A') <= 'Z' - 'A') {
            c1 += 'a' - 'A';
        }
        if ((unsigned int)(c2 - 'A') <= 'Z' - 'A') {
            c2 += 'a' - 'A';
        }
        if (c1 != c2) {
            return c1 - c2;
        }
    } while (c1);
    return 0;
}

char *fn_801C32CC(char *pString)
{
    char *p;

    for (p = pString; *p; p++) {
        if (CTYPE(*p) & 2) {
            *p = fn_801C1F54(*p);
        }
    }
    return pString;
}
