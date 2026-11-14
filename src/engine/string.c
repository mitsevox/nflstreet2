/* C string library: copy, append, compare (also without case), search, length, bounded copy that
   always terminates, and in-place upper-casing. */

#include <string.h>
#include "engine/ctype.h"

extern const unsigned char lbl_802AEF10[];

#define CTYPE(c) ((lbl_802AEF10 + 1)[(unsigned char)(c)])


char *strcpy(char *pDest, const char *pSource)
{
    char *pOut = pDest;

    for (;;) {
        if ((*pOut++ = *pSource++) == 0) {
            break;
        }
    }
    return pDest;
}

char *strncpy(char *pDest, const char *pSource, size_t size)
{
    char *pOut = pDest;

    if (size == 0 || pDest == pSource) {
        return pDest;
    }
    while ((*pOut++ = *pSource++) != 0 && --size) {
    }
    return pDest;
}

char *strcat(char *pDest, const char *pSource)
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

char *strncat(char *pDest, const char *pSource, size_t size)
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

int strcmp(const char *pString1, const char *pString2)
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

int strncmp(const char *pString1, const char *pString2, size_t size)
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

char *strchr(const char *pString, int c)
{
    while (*pString) {
        if (*pString++ == (char)c) {
            return (char *)pString - 1;
        }
    }
    return 0;
}

char *strrchr(const char *pString, int c)
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

char *strstr(const char *pString, const char *pFind)
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

size_t strlen(const char *pString)
{
    const char *p = pString;

    for (; *p++;) {
    }
    return p - pString - 1;
}

int stricmp(const char *pString1, const char *pString2)
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

int strnicmp(const char *pString1, const char *pString2, size_t size)
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

char *strnzcpy(char *pDest, const char *pSource, size_t size)
{
    char *pOut;

    if (size == 0 || pSource == pDest) {
        return pDest;
    }
    pOut = pDest;
    for (;;) {
        if (--size) {
            if ((*pOut++ = *pSource++) == 0) {
                return pDest;
            }
        } else {
            *pOut = 0;
            return pDest;
        }
    }
}

char *strupr(char *pString)
{
    char *p;

    for (p = pString; *p; p++) {
        if (CTYPE(*p) & 2) {
            *p = toupper(*p);
        }
    }
    return pString;
}
